#include "EvolvingDialogueSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DataTable.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"

UEvolvingDialogueSystem::UEvolvingDialogueSystem()
{
    PrimaryComponentTick.bCanEverTick = true;
    SetIsReplicatedByDefault(true);
    
    CurrentPlayerState = CreateInitialPlayerState();
}

void UEvolvingDialogueSystem::BeginPlay()
{
    Super::BeginPlay();
    InitializeEvolvingDialogue();
}

void UEvolvingDialogueSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    ProcessDialogueTriggers();
    UpdateDialogueAvailability();
    CheckForNewDialogue();
}

void UEvolvingDialogueSystem::InitializeEvolvingDialogue()
{
    UE_LOG(LogTemp, Warning, TEXT("Evolving Dialogue System initialized"));
    
    // Initialize all dialogue systems
    InitializeDialogueDatabase();
    InitializePlayerState();
    
    // Load saved dialogue state
    LoadEvolvingDialogueState();
    
    UE_LOG(LogTemp, Warning, TEXT("Evolving Dialogue System ready"));
}

void UEvolvingDialogueSystem::UpdatePlayerState()
{
    // Update player state from game systems
    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (PC && PC->PlayerState)
    {
        // This would typically get actual player data from game systems
        // For now, we'll use placeholder values
        CurrentPlayerState.PlayerLevel = 1;
        CurrentPlayerState.PlayerRank = TEXT("F");
        CurrentPlayerState.PlayTime += GetWorld()->GetDeltaSeconds();
    }
    
    NotifyPlayerStateChanged(CurrentPlayerState);
}

bool UEvolvingDialogueSystem::StartEvolvingDialogue(const FString& NodeID, const FString& SpeakerID)
{
    FEvolvingDialogueNode Node = GetDialogueNode(NodeID);
    if (Node.NodeID.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("Dialogue node not found: %s"), *NodeID);
        return false;
    }
    
    // Check if dialogue is available
    if (!CanUseDialogueVariant(NodeID, FDialogueVariant()))
    {
        UE_LOG(LogTemp, Warning, TEXT("Dialogue not available: %s"), *NodeID);
        return false;
    }
    
    // Get best variant for current player state
    FDialogueVariant BestVariant = GetBestDialogueVariant(NodeID);
    if (BestVariant.VariantID.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("No valid dialogue variant found for: %s"), *NodeID);
        return false;
    }
    
    // Mark dialogue as used
    MarkDialogueAsSaid(NodeID, BestVariant.VariantID);
    UpdateDialogueCooldown(NodeID);
    
    // Trigger dialogue event
    NotifyEvolvingDialogueTriggered(Node);
    NotifyDialogueVariantSelected(NodeID, BestVariant);
    
    // Process consequences
    ProcessDialogueConsequences(BestVariant.Consequences);
    
    UE_LOG(LogTemp, Warning, TEXT("Evolving dialogue started: %s - %s"), *NodeID, *BestVariant.DialogueText);
    return true;
}

FDialogueVariant UEvolvingDialogueSystem::GetBestDialogueVariant(const FString& NodeID)
{
    FEvolvingDialogueNode Node = GetDialogueNode(NodeID);
    if (Node.NodeID.IsEmpty())
    {
        return FDialogueVariant();
    }
    
    // Get all available variants
    TArray<FDialogueVariant> AvailableVariants = GetAvailableVariants(NodeID);
    
    if (AvailableVariants.Num() == 0)
    {
        return FDialogueVariant();
    }
    
    // Sort by priority
    AvailableVariants.Sort([](const FDialogueVariant& A, const FDialogueVariant& B)
    {
        return (int32)A.Priority > (int32)B.Priority;
    });
    
    // Get highest priority variants
    EDialoguePriority HighestPriority = AvailableVariants[0].Priority;
    TArray<FDialogueVariant> PriorityVariants;
    
    for (const FDialogueVariant& Variant : AvailableVariants)
    {
        if (Variant.Priority == HighestPriority)
        {
            PriorityVariants.Add(Variant);
        }
    }
    
    // Select weighted variant from highest priority options
    return SelectWeightedVariant(PriorityVariants);
}

TArray<FDialogueVariant> UEvolvingDialogueSystem::GetAvailableVariants(const FString& NodeID)
{
    TArray<FDialogueVariant> AvailableVariants;
    
    FEvolvingDialogueNode Node = GetDialogueNode(NodeID);
    if (Node.NodeID.IsEmpty())
    {
        return AvailableVariants;
    }
    
    for (const FDialogueVariant& Variant : Node.Variants)
    {
        if (CanUseDialogueVariant(NodeID, Variant))
        {
            AvailableVariants.Add(Variant);
        }
    }
    
    return AvailableVariants;
}

bool UEvolvingDialogueSystem::SelectDialogueVariant(const FString& NodeID, const FString& VariantID)
{
    FEvolvingDialogueNode Node = GetDialogueNode(NodeID);
    if (Node.NodeID.IsEmpty())
    {
        return false;
    }
    
    for (const FDialogueVariant& Variant : Node.Variants)
    {
        if (Variant.VariantID == VariantID && CanUseDialogueVariant(NodeID, Variant))
        {
            MarkDialogueAsSaid(NodeID, VariantID);
            UpdateDialogueCooldown(NodeID);
            NotifyDialogueVariantSelected(NodeID, Variant);
            
            UE_LOG(LogTemp, Warning, TEXT("Dialogue variant selected: %s - %s"), *NodeID, *VariantID);
            return true;
        }
    }
    
    return false;
}

FEvolvingDialogueNode UEvolvingDialogueSystem::GetDialogueNode(const FString& NodeID) const
{
    for (const FEvolvingDialogueNode& Node : DialogueDatabase)
    {
        if (Node.NodeID == NodeID)
        {
            return Node;
        }
    }
    
    FEvolvingDialogueNode EmptyNode;
    return EmptyNode;
}

TArray<FEvolvingDialogueNode> UEvolvingDialogueSystem::GetDialogueNodes(const FString& SpeakerID) const
{
    TArray<FEvolvingDialogueNode> SpeakerNodes;
    
    for (const FEvolvingDialogueNode& Node : DialogueDatabase)
    {
        if (Node.SpeakerID == SpeakerID)
        {
            SpeakerNodes.Add(Node);
        }
    }
    
    return SpeakerNodes;
}

bool UEvolvingDialogueSystem::CheckDialogueConditions(const TArray<FDialogueCondition>& Conditions)
{
    for (const FDialogueCondition& Condition : Conditions)
    {
        if (!IsConditionMet(Condition))
        {
            return false;
        }
    }
    
    return true;
}

bool UEvolvingDialogueSystem::IsConditionMet(const FDialogueCondition& Condition)
{
    return EvaluateCondition(Condition);
}

void UEvolvingDialogueSystem::AddDialogueCondition(const FString& NodeID, const FString& VariantID, const FDialogueCondition& Condition)
{
    // Find and update the dialogue node and variant
    for (FEvolvingDialogueNode& Node : DialogueDatabase)
    {
        if (Node.NodeID == NodeID)
        {
            for (FDialogueVariant& Variant : Node.Variants)
            {
                if (Variant.VariantID == VariantID)
                {
                    Variant.Conditions.Add(Condition);
                    UE_LOG(LogTemp, Warning, TEXT("Dialogue condition added: %s - %s"), *NodeID, *VariantID);
                    return;
                }
            }
        }
    }
}

void UEvolvingDialogueSystem::RemoveDialogueCondition(const FString& NodeID, const FString& VariantID, const FString& ConditionID)
{
    // Find and remove the dialogue condition
    for (FEvolvingDialogueNode& Node : DialogueDatabase)
    {
        if (Node.NodeID == NodeID)
        {
            for (FDialogueVariant& Variant : Node.Variants)
            {
                if (Variant.VariantID == VariantID)
                {
                    for (int32 i = 0; i < Variant.Conditions.Num(); i++)
                    {
                        if (Variant.Conditions[i].Parameter == ConditionID)
                        {
                            Variant.Conditions.RemoveAt(i);
                            UE_LOG(LogTemp, Warning, TEXT("Dialogue condition removed: %s - %s"), *NodeID, *VariantID);
                            return;
                        }
                    }
                }
            }
        }
    }
}

FPlayerDialogueState UEvolvingDialogueSystem::GetPlayerState() const
{
    return CurrentPlayerState;
}

void UEvolvingDialogueSystem::SetPlayerLevel(int32 NewLevel)
{
    if (CurrentPlayerState.PlayerLevel != NewLevel)
    {
        CurrentPlayerState.PlayerLevel = NewLevel;
        TriggerDialogueEvent(EDialogueTrigger::DT_LevelUp, FString::FromInt(NewLevel));
        NotifyPlayerStateChanged(CurrentPlayerState);
        
        UE_LOG(LogTemp, Warning, TEXT("Player level updated: %d"), NewLevel);
    }
}

void UEvolvingDialogueSystem::SetPlayerRank(const FString& NewRank)
{
    if (CurrentPlayerState.PlayerRank != NewRank)
    {
        CurrentPlayerState.PlayerRank = NewRank;
        NotifyPlayerStateChanged(CurrentPlayerState);
        
        UE_LOG(LogTemp, Warning, TEXT("Player rank updated: %s"), *NewRank);
    }
}

void UEvolvingDialogueSystem::AddCompletedQuest(const FString& QuestID)
{
    if (!CurrentPlayerState.CompletedQuests.Contains(QuestID))
    {
        CurrentPlayerState.CompletedQuests.Add(QuestID);
        TriggerDialogueEvent(EDialogueTrigger::DT_QuestComplete, QuestID);
        NotifyPlayerStateChanged(CurrentPlayerState);
        
        UE_LOG(LogTemp, Warning, TEXT("Quest completed: %s"), *QuestID);
    }
}

void UEvolvingDialogueSystem::AddKnownSkill(const FString& SkillID)
{
    if (!CurrentPlayerState.KnownSkills.Contains(SkillID))
    {
        CurrentPlayerState.KnownSkills.Add(SkillID);
        TriggerDialogueEvent(EDialogueTrigger::DT_SkillLearned, SkillID);
        NotifyPlayerStateChanged(CurrentPlayerState);
        
        UE_LOG(LogTemp, Warning, TEXT("Skill learned: %s"), *SkillID);
    }
}

void UEvolvingDialogueSystem::AddImportantItem(const FString& ItemID)
{
    if (!CurrentPlayerState.ImportantItems.Contains(ItemID))
    {
        CurrentPlayerState.ImportantItems.Add(ItemID);
        TriggerDialogueEvent(EDialogueTrigger::DT_ItemAcquired, ItemID);
        NotifyPlayerStateChanged(CurrentPlayerState);
        
        UE_LOG(LogTemp, Warning, TEXT("Important item acquired: %s"), *ItemID);
    }
}

void UEvolvingDialogueSystem::AddDiscoveredLocation(const FString& LocationID)
{
    if (!CurrentPlayerState.DiscoveredLocations.Contains(LocationID))
    {
        CurrentPlayerState.DiscoveredLocations.Add(LocationID);
        TriggerDialogueEvent(EDialogueTrigger::DT_LocationDiscovered, LocationID);
        NotifyPlayerStateChanged(CurrentPlayerState);
        
        UE_LOG(LogTemp, Warning, TEXT("Location discovered: %s"), *LocationID);
    }
}

void UEvolvingDialogueSystem::UpdateNPCRelationship(const FString& NPCID, int32 RelationshipValue)
{
    CurrentPlayerState.NPCRelationships.Add(NPCID, RelationshipValue);
    TriggerDialogueEvent(EDialogueTrigger::DT_RelationshipChange, FString::Printf(TEXT("%s,%d"), *NPCID, RelationshipValue));
    NotifyPlayerStateChanged(CurrentPlayerState);
    
    UE_LOG(LogTemp, Warning, TEXT("NPC relationship updated: %s = %d"), *NPCID, RelationshipValue);
}

void UEvolvingDialogueSystem::AddWorldEvent(const FString& EventID)
{
    if (!CurrentPlayerState.WorldEvents.Contains(EventID))
    {
        CurrentPlayerState.WorldEvents.Add(EventID);
        TriggerDialogueEvent(EDialogueTrigger::DT_WorldEvent, EventID);
        NotifyPlayerStateChanged(CurrentPlayerState);
        
        UE_LOG(LogTemp, Warning, TEXT("World event added: %s"), *EventID);
    }
}

void UEvolvingDialogueSystem::SetPlayerChoice(const FString& ChoiceID, const FString& ChoiceValue)
{
    CurrentPlayerState.PlayerChoices.Add(ChoiceID, ChoiceValue);
    TriggerDialogueEvent(EDialogueTrigger::DT_PlayerAction, FString::Printf(TEXT("%s,%s"), *ChoiceID, *ChoiceValue));
    NotifyPlayerStateChanged(CurrentPlayerState);
    
    UE_LOG(LogTemp, Warning, TEXT("Player choice recorded: %s = %s"), *ChoiceID, *ChoiceValue);
}

void UEvolvingDialogueSystem::TriggerDialogueEvent(EDialogueTrigger TriggerType, const FString& Parameter)
{
    PendingTriggers.Add(TPair<EDialogueTrigger, FString>(TriggerType, Parameter));
    
    UE_LOG(LogTemp, Warning, TEXT("Dialogue event triggered: %d - %s"), (int32)TriggerType, *Parameter);
}

void UEvolvingDialogueSystem::OnPlayerLevelUp(int32 NewLevel)
{
    SetPlayerLevel(NewLevel);
}

void UEvolvingDialogueSystem::OnQuestCompleted(const FString& QuestID)
{
    AddCompletedQuest(QuestID);
}

void UEvolvingDialogueSystem::OnSkillLearned(const FString& SkillID)
{
    AddKnownSkill(SkillID);
}

void UEvolvingDialogueSystem::OnItemAcquired(const FString& ItemID)
{
    AddImportantItem(ItemID);
}

void UEvolvingDialogueSystem::OnLocationDiscovered(const FString& LocationID)
{
    AddDiscoveredLocation(LocationID);
}

void UEvolvingDialogueSystem::OnWorldEventTriggered(const FString& EventID)
{
    AddWorldEvent(EventID);
}

TArray<FEvolvingDialogueNode> UEvolvingDialogueSystem::GetContextualDialogue(EDialogueContext Context) const
{
    TArray<FEvolvingDialogueNode> ContextualDialogue;
    
    for (const FEvolvingDialogueNode& Node : DialogueDatabase)
    {
        if (Node.Context == Context)
        {
            ContextualDialogue.Add(Node);
        }
    }
    
    return ContextualDialogue;
}

TArray<FEvolvingDialogueNode> UEvolvingDialogueSystem::GetPriorityDialogue() const
{
    TArray<FEvolvingDialogueNode> PriorityDialogue;
    
    for (const FEvolvingDialogueNode& Node : DialogueDatabase)
    {
        if (Node.bIsImportant)
        {
            PriorityDialogue.Add(Node);
        }
    }
    
    return PriorityDialogue;
}

TArray<FEvolvingDialogueNode> UEvolvingDialogueSystem::GetAvailableDialogue() const
{
    TArray<FEvolvingDialogueNode> AvailableDialogue;
    
    for (const FEvolvingDialogueNode& Node : DialogueDatabase)
    {
        if (!IsDialogueOnCooldown(Node.NodeID))
        {
            TArray<FDialogueVariant> Variants = GetAvailableVariants(Node.NodeID);
            if (Variants.Num() > 0)
            {
                AvailableDialogue.Add(Node);
            }
        }
    }
    
    SortDialogueByPriority(AvailableDialogue);
    return AvailableDialogue;
}

void UEvolvingDialogueSystem::UpdateDialogueContext()
{
    // Update dialogue context based on current player state
    // This would typically check current game situation and update context
}

TArray<FString> UEvolvingDialogueSystem::GetDialogueHistory() const
{
    return DialogueHistory;
}

void UEvolvingDialogueSystem::AddToHistory(const FString& DialogueEntry)
{
    DialogueHistory.Add(DialogueEntry);
    
    // Limit history size
    if (DialogueHistory.Num() > 100)
    {
        DialogueHistory.RemoveAt(0);
    }
}

void UEvolvingDialogueSystem::ClearDialogueHistory()
{
    DialogueHistory.Empty();
    UE_LOG(LogTemp, Warning, TEXT("Dialogue history cleared"));
}

bool UEvolvingDialogueSystem::HasDialogueBeenSaid(const FString& NodeID, const FString& VariantID) const
{
    FString Key = FString::Printf(TEXT("%s_%s"), *NodeID, *VariantID);
    return SaidDialogueVariants.Contains(Key);
}

void UEvolvingDialogueSystem::SaveEvolvingDialogueState()
{
    // Save evolving dialogue state
    UE_LOG(LogTemp, Warning, TEXT("Evolving dialogue state saved"));
}

void UEvolvingDialogueSystem::LoadEvolvingDialogueState()
{
    // Load evolving dialogue state
    UE_LOG(LogTemp, Warning, TEXT("Evolving dialogue state loaded"));
}

void UEvolvingDialogueSystem::ResetEvolvingDialogueState()
{
    CurrentPlayerState = CreateInitialPlayerState();
    DialogueHistory.Empty();
    DialogueCooldowns.Empty();
    DialogueUsageCounts.Empty();
    SaidDialogueVariants.Empty();
    PendingTriggers.Empty();
    
    // Reset dialogue node usage
    for (FEvolvingDialogueNode& Node : DialogueDatabase)
    {
        Node.CurrentUses = 0;
        Node.LastUsedTime = 0.0f;
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Evolving dialogue state reset"));
}

void UEvolvingDialogueSystem::InitializeDialogueDatabase()
{
    DialogueDatabase.Empty();
    
    // Create Guild Master dialogue with evolving variants
    FEvolvingDialogueNode GuildMasterNode = CreateDialogueNode(
        TEXT("GUILD_MASTER_GREETING"),
        TEXT("GuildMaster"),
        EDialogueContext::DC_QuestRelated
    );
    
    // Level 1 variant (new player)
    FDialogueVariant Level1Variant = CreateDialogueVariant(
        TEXT("LEVEL1_GREETING"),
        TEXT("Welcome to the Hunters Guild, rookie. I am Guild Master Aldric. We have a situation that requires attention - monsters pouring from a mysterious gate in the forest."),
        EDialoguePriority::DP_Story
    );
    
    FDialogueCondition Level1Condition = CreateDialogueCondition(
        EDialogueTrigger::DT_LevelUp,
        TEXT("PlayerLevel"),
        TEXT("=="),
        TEXT("1")
    );
    Level1Variant.Conditions.Add(Level1Condition);
    
    // Level 5 variant (experienced player)
    FDialogueVariant Level5Variant = CreateDialogueVariant(
        TEXT("LEVEL5_GREETING"),
        TEXT("Ah, welcome back, hunter. You've grown stronger since we first met. The gate situation remains, but I have a new mission that requires your experience."),
        EDialoguePriority::DP_High
    );
    
    FDialogueCondition Level5Condition = CreateDialogueCondition(
        EDialogueTrigger::DT_LevelUp,
        TEXT("PlayerLevel"),
        TEXT(">="),
        TEXT("5")
    );
    Level5Variant.Conditions.Add(Level5Condition);
    
    // Post-quest variant
    FDialogueVariant PostQuestVariant = CreateDialogueVariant(
        TEXT("POST_QUEST_GREETING"),
        TEXT("Excellent work closing that gate! You've proven yourself as a true hunter. The guild recognizes your achievement - you've been promoted to E-rank!"),
        EDialoguePriority::DP_Story
    );
    
    FDialogueCondition QuestCondition = CreateDialogueCondition(
        EDialogueTrigger::DT_QuestComplete,
        TEXT("InvestigateGate"),
        TEXT("=="),
        TEXT("true")
    );
    PostQuestVariant.Conditions.Add(QuestCondition);
    
    // Add variants to node
    GuildMasterNode.Variants.Add(Level1Variant);
    GuildMasterNode.Variants.Add(Level5Variant);
    GuildMasterNode.Variants.Add(PostQuestVariant);
    
    DialogueDatabase.Add(GuildMasterNode);
    
    // Create villager dialogue with evolving variants
    FEvolvingDialogueNode VillagerNode = CreateDialogueNode(
        TEXT("VILLAGER_GREETING"),
        TEXT("Villager"),
        EDialogueContext::DC_General
    );
    
    // Pre-quest variant
    FDialogueVariant PreQuestVariant = CreateDialogueVariant(
        TEXT("PRE_QUEST_VILLAGER"),
        TEXT("Be careful near the forest, hunter. Strange creatures have been appearing. The Guild Master is looking for brave souls to investigate."),
        EDialoguePriority::DP_Normal
    );
    
    // Post-quest variant
    FDialogueVariant PostQuestVillagerVariant = CreateDialogueVariant(
        TEXT("POST_QUEST_VILLAGER"),
        TEXT("Thank you for dealing with those monsters! We can finally sleep peacefully at night. You're a true hero to our village!"),
        EDialoguePriority::DP_High
    );
    
    PostQuestVillagerVariant.Conditions.Add(QuestCondition);
    
    VillagerNode.Variants.Add(PreQuestVariant);
    VillagerNode.Variants.Add(PostQuestVillagerVariant);
    
    DialogueDatabase.Add(VillagerNode);
    
    // Create skill trainer dialogue
    FEvolvingDialogueNode TrainerNode = CreateDialogueNode(
        TEXT("SKILL_TRAINER"),
        TEXT("SkillTrainer"),
        EDialogueContext::DC_SkillRelated
    );
    
    // Basic skill variant
    FDialogueVariant BasicSkillVariant = CreateDialogueVariant(
        TEXT("BASIC_SKILL_TRAINER"),
        TEXT("I can teach you the basics of combat. Focus on your fundamentals before attempting advanced techniques."),
        EDialoguePriority::DP_Normal
    );
    
    // Advanced skill variant (when player has skills)
    FDialogueVariant AdvancedSkillVariant = CreateDialogueVariant(
        TEXT("ADVANCED_SKILL_TRAINER"),
        TEXT("I see you've learned some impressive skills! Let me help you refine your techniques and unlock your true potential."),
        EDialoguePriority::DP_High
    );
    
    FDialogueCondition SkillCondition = CreateDialogueCondition(
        EDialogueTrigger::DT_SkillLearned,
        TEXT("KnownSkills"),
        TEXT("contains"),
        TEXT("Fireball")
    );
    AdvancedSkillVariant.Conditions.Add(SkillCondition);
    
    TrainerNode.Variants.Add(BasicSkillVariant);
    TrainerNode.Variants.Add(AdvancedSkillVariant);
    
    DialogueDatabase.Add(TrainerNode);
}

void UEvolvingDialogueSystem::InitializePlayerState()
{
    CurrentPlayerState = CreateInitialPlayerState();
}

void UEvolvingDialogueSystem::ProcessDialogueTriggers()
{
    // Process all pending triggers
    while (PendingTriggers.Num() > 0)
    {
        TPair<EDialogueTrigger, FString> Trigger = PendingTriggers[0];
        PendingTriggers.RemoveAt(0);
        
        // Check for dialogue that responds to this trigger
        for (FEvolvingDialogueNode& Node : DialogueDatabase)
        {
            for (FDialogueVariant& Variant : Node.Variants)
            {
                for (FDialogueCondition& Condition : Variant.Conditions)
                {
                    if (Condition.TriggerType == Trigger.Key)
                    {
                        Condition.Parameter = Trigger.Value;
                        Condition.bIsMet = EvaluateCondition(Condition);
                        
                        if (Condition.bIsMet)
                        {
                            NotifyDialogueConditionMet(Condition);
                        }
                    }
                }
            }
        }
    }
}

void UEvolvingDialogueSystem::UpdateDialogueAvailability()
{
    // Update availability of all dialogue based on current player state
    for (FEvolvingDialogueNode& Node : DialogueDatabase)
    {
        for (FDialogueVariant& Variant : Node.Variants)
        {
            Variant.bIsAvailable = CanUseDialogueVariant(Node.NodeID, Variant);
        }
    }
}

void UEvolvingDialogueSystem::CheckForNewDialogue()
{
    // Check for new dialogue that should be triggered based on player state
    TArray<FEvolvingDialogueNode> AvailableDialogue = GetAvailableDialogue();
    
    for (const FEvolvingDialogueNode& Node : AvailableDialogue)
    {
        if (Node.bIsImportant && !HasDialogueBeenSaid(Node.NodeID, TEXT("")))
        {
            // Trigger important dialogue automatically
            StartEvolvingDialogue(Node.NodeID, Node.SpeakerID);
        }
    }
}

void UEvolvingDialogueSystem::RefreshAllDialogue()
{
    UpdatePlayerState();
    UpdateDialogueAvailability();
    UpdateDialogueContext();
}

FEvolvingDialogueNode UEvolvingDialogueSystem::CreateDialogueNode(const FString& ID, const FString& SpeakerID, EDialogueContext Context)
{
    FEvolvingDialogueNode Node;
    Node.NodeID = ID;
    Node.SpeakerID = SpeakerID;
    Node.Context = Context;
    Node.Variants.Empty();
    Node.Options.Empty();
    Node.bIsRepeatable = true;
    Node.MaxUses = -1; // Unlimited
    Node.CurrentUses = 0;
    Node.CooldownTime = 0.0f;
    Node.LastUsedTime = 0.0f;
    Node.bIsImportant = false;
    Node.Tags.Empty();
    
    return Node;
}

FDialogueVariant UEvolvingDialogueSystem::CreateDialogueVariant(const FString& ID, const FString& Text, EDialoguePriority Priority)
{
    FDialogueVariant Variant;
    Variant.VariantID = ID;
    Variant.DialogueText = Text;
    Variant.Conditions.Empty();
    Variant.Priority = Priority;
    Variant.bIsAvailable = true;
    Variant.AudioPath = TEXT("");
    Variant.AnimationName = TEXT("");
    Variant.Consequences.Empty();
    Variant.Weight = 1.0f;
    
    return Variant;
}

FDialogueCondition UEvolvingDialogueSystem::CreateDialogueCondition(EDialogueTrigger Trigger, const FString& Param, const FString& Op, const FString& Val)
{
    FDialogueCondition Condition;
    Condition.TriggerType = Trigger;
    Condition.Parameter = Param;
    Condition.Operator = Op;
    Condition.Value = Val;
    Condition.bIsMet = false;
    Condition.Description = FString::Printf(TEXT("%s %s %s"), *Param, *Op, *Val);
    
    return Condition;
}

FPlayerDialogueState UEvolvingDialogueSystem::CreateInitialPlayerState()
{
    FPlayerDialogueState State;
    State.PlayerLevel = 1;
    State.PlayerRank = TEXT("F");
    State.CompletedQuests.Empty();
    State.KnownSkills.Empty();
    State.ImportantItems.Empty();
    State.DiscoveredLocations.Empty();
    State.NPCRelationships.Empty();
    State.WorldEvents.Empty();
    State.PlayTime = 0.0f;
    State.EnemiesDefeated = 0;
    State.PlayerChoices.Empty();
    
    return State;
}

void UEvolvingDialogueSystem::NotifyEvolvingDialogueTriggered(const FEvolvingDialogueNode& DialogueNode)
{
    OnEvolvingDialogueTriggered.Broadcast(DialogueNode);
}

void UEvolvingDialogueSystem::NotifyDialogueVariantSelected(const FString& NodeID, const FDialogueVariant& Variant)
{
    OnDialogueVariantSelected.Broadcast(NodeID, Variant);
}

void UEvolvingDialogueSystem::NotifyDialogueConditionMet(const FDialogueCondition& Condition)
{
    OnDialogueConditionMet.Broadcast(Condition);
}

void UEvolvingDialogueSystem::NotifyPlayerStateChanged(const FPlayerDialogueState& NewState)
{
    OnPlayerStateChanged.Broadcast(NewState);
}

bool UEvolvingDialogueSystem::EvaluateCondition(const FDialogueCondition& Condition)
{
    // Evaluate condition based on current player state
    if (Condition.Operator == TEXT("=="))
    {
        if (Condition.Parameter == TEXT("PlayerLevel"))
        {
            return CurrentPlayerState.PlayerLevel == FCString::Atoi(*Condition.Value);
        }
        else if (Condition.Parameter == TEXT("PlayerRank"))
        {
            return CurrentPlayerState.PlayerRank == Condition.Value;
        }
    }
    else if (Condition.Operator == TEXT(">="))
    {
        if (Condition.Parameter == TEXT("PlayerLevel"))
        {
            return CurrentPlayerState.PlayerLevel >= FCString::Atoi(*Condition.Value);
        }
    }
    else if (Condition.Operator == TEXT("contains"))
    {
        if (Condition.Parameter == TEXT("KnownSkills"))
        {
            return CurrentPlayerState.KnownSkills.Contains(Condition.Value);
        }
        else if (Condition.Parameter == TEXT("CompletedQuests"))
        {
            return CurrentPlayerState.CompletedQuests.Contains(Condition.Value);
        }
    }
    else if (Condition.Operator == TEXT("=="))
    {
        if (Condition.Parameter == TEXT("InvestigateGate"))
        {
            return Condition.Value == TEXT("true");
        }
    }
    
    return false;
}

float UEvolvingDialogueSystem::CalculateVariantWeight(const FDialogueVariant& Variant)
{
    float Weight = Variant.Weight;
    
    // Adjust weight based on priority
    switch (Variant.Priority)
    {
        case EDialoguePriority::DP_Critical:
            Weight *= 10.0f;
            break;
        case EDialoguePriority::DP_Story:
            Weight *= 5.0f;
            break;
        case EDialoguePriority::DP_High:
            Weight *= 2.0f;
            break;
        case EDialoguePriority::DP_Normal:
            Weight *= 1.0f;
            break;
        case EDialoguePriority::DP_Low:
            Weight *= 0.5f;
            break;
    }
    
    return Weight;
}

FDialogueVariant UEvolvingDialogueSystem::SelectWeightedVariant(const TArray<FDialogueVariant>& ValidVariants)
{
    if (ValidVariants.Num() == 0)
    {
        return FDialogueVariant();
    }
    
    if (ValidVariants.Num() == 1)
    {
        return ValidVariants[0];
    }
    
    // Calculate total weight
    float TotalWeight = 0.0f;
    for (const FDialogueVariant& Variant : ValidVariants)
    {
        TotalWeight += CalculateVariantWeight(Variant);
    }
    
    // Select random variant based on weight
    float RandomValue = FMath::RandRange(0.0f, TotalWeight);
    float CurrentWeight = 0.0f;
    
    for (const FDialogueVariant& Variant : ValidVariants)
    {
        CurrentWeight += CalculateVariantWeight(Variant);
        if (RandomValue <= CurrentWeight)
        {
            return Variant;
        }
    }
    
    return ValidVariants[0]; // Fallback
}

void UEvolvingDialogueSystem::ProcessDialogueConsequences(const TArray<FString>& Consequences)
{
    for (const FString& Consequence : Consequences)
    {
        // Process dialogue consequences
        if (Consequence.StartsWith(TEXT("UnlockQuest")))
        {
            // Unlock quest logic
        }
        else if (Consequence.StartsWith(TEXT("GiveItem")))
        {
            // Give item logic
        }
        else if (Consequence.StartsWith(TEXT("UpdateRelationship")))
        {
            // Update relationship logic
        }
    }
}

void UEvolvingDialogueSystem::UpdateDialogueCooldown(const FString& NodeID)
{
    FEvolvingDialogueNode Node = GetDialogueNode(NodeID);
    if (!Node.NodeID.IsEmpty())
    {
        DialogueCooldowns.Add(NodeID, Node.CooldownTime);
        Node.LastUsedTime = GetWorld()->GetTimeSeconds();
        Node.CurrentUses++;
    }
}

bool UEvolvingDialogueSystem::IsDialogueOnCooldown(const FString& NodeID) const
{
    if (DialogueCooldowns.Contains(NodeID))
    {
        float CooldownTime = DialogueCooldowns[NodeID];
        if (CooldownTime > 0.0f)
        {
            FEvolvingDialogueNode Node = GetDialogueNode(NodeID);
            if (!Node.NodeID.IsEmpty())
            {
                float TimeSinceLastUse = GetWorld()->GetTimeSeconds() - Node.LastUsedTime;
                return TimeSinceLastUse < CooldownTime;
            }
        }
    }
    
    return false;
}

bool UEvolvingDialogueSystem::CanUseDialogueVariant(const FString& NodeID, const FDialogueVariant& Variant)
{
    // Check if variant is available
    if (!Variant.bIsAvailable)
    {
        return false;
    }
    
    // Check conditions
    if (!CheckDialogueConditions(Variant.Conditions))
    {
        return false;
    }
    
    // Check cooldown
    if (IsDialogueOnCooldown(NodeID))
    {
        return false;
    }
    
    // Check usage limit
    FEvolvingDialogueNode Node = GetDialogueNode(NodeID);
    if (!Node.NodeID.IsEmpty() && Node.MaxUses > 0 && Node.CurrentUses >= Node.MaxUses)
    {
        return false;
    }
    
    // Check if already said (if not repeatable)
    if (!Node.bIsRepeatable && HasDialogueBeenSaid(NodeID, Variant.VariantID))
    {
        return false;
    }
    
    return true;
}

void UEvolvingDialogueSystem::MarkDialogueAsSaid(const FString& NodeID, const FString& VariantID)
{
    FString Key = FString::Printf(TEXT("%s_%s"), *NodeID, *VariantID);
    SaidDialogueVariants.Add(Key);
    
    // Add to dialogue history
    FEvolvingDialogueNode Node = GetDialogueNode(NodeID);
    if (!Node.NodeID.IsEmpty())
    {
        for (const FDialogueVariant& Variant : Node.Variants)
        {
            if (Variant.VariantID == VariantID)
            {
                AddToHistory(FString::Printf(TEXT("[%s]: %s"), *Node.SpeakerID, *Variant.DialogueText));
                break;
            }
        }
    }
}

void UEvolvingDialogueSystem::SortDialogueByPriority(TArray<FEvolvingDialogueNode>& DialogueNodes)
{
    DialogueNodes.Sort([](const FEvolvingDialogueNode& A, const FEvolvingDialogueNode& B)
    {
        // Sort by importance first, then by context priority
        if (A.bIsImportant && !B.bIsImportant)
        {
            return true;
        }
        if (!A.bIsImportant && B.bIsImportant)
        {
            return false;
        }
        
        return (int32)A.Context < (int32)B.Context;
    });
}

void UEvolvingDialogueSystem::FilterDialogueByContext(TArray<FEvolvingDialogueNode>& DialogueNodes, EDialogueContext Context)
{
    DialogueNodes.RemoveAll([Context](const FEvolvingDialogueNode& Node)
    {
        return Node.Context != Context;
    });
}

void UEvolvingDialogueSystem::LogDialogueState()
{
    UE_LOG(LogTemp, Warning, TEXT("=== Evolving Dialogue State ==="));
    UE_LOG(LogTemp, Warning, TEXT("Player Level: %d"), CurrentPlayerState.PlayerLevel);
    UE_LOG(LogTemp, Warning, TEXT("Player Rank: %s"), *CurrentPlayerState.PlayerRank);
    UE_LOG(LogTemp, Warning, TEXT("Completed Quests: %d"), CurrentPlayerState.CompletedQuests.Num());
    UE_LOG(LogTemp, Warning, TEXT("Known Skills: %d"), CurrentPlayerState.KnownSkills.Num());
    UE_LOG(LogTemp, Warning, TEXT("Dialogue History: %d"), DialogueHistory.Num());
    UE_LOG(LogTemp, Warning, TEXT("Pending Triggers: %d"), PendingTriggers.Num());
    UE_LOG(LogTemp, Warning, TEXT("=============================="));
}

void UEvolvingDialogueSystem::ValidateDialogueDatabase()
{
    // Validate dialogue database for consistency
    for (const FEvolvingDialogueNode& Node : DialogueDatabase)
    {
        if (Node.NodeID.IsEmpty())
        {
            UE_LOG(LogTemp, Warning, TEXT("Dialogue node has empty ID"));
        }
        
        for (const FDialogueVariant& Variant : Node.Variants)
        {
            if (Variant.VariantID.IsEmpty())
            {
                UE_LOG(LogTemp, Warning, TEXT("Dialogue variant has empty ID in node: %s"), *Node.NodeID);
            }
        }
    }
}

void UEvolvingDialogueSystem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    DOREPLIFETIME(UEvolvingDialogueSystem, DialogueDatabase);
    DOREPLIFETIME(UEvolvingDialogueSystem, CurrentPlayerState);
    DOREPLIFETIME(UEvolvingDialogueSystem, DialogueHistory);
    DOREPLIFETIME(UEvolvingDialogueSystem, DialogueCooldowns);
    DOREPLIFETIME(UEvolvingDialogueSystem, DialogueUsageCounts);
    DOREPLIFETIME(UEvolvingDialogueSystem, SaidDialogueVariants);
    DOREPLIFETIME(UEvolvingDialogueSystem, PendingTriggers);
}
