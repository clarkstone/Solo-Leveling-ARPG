#include "NarrativeSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DataTable.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "Net/UnrealNetwork.h"

UNarrativeSystem::UNarrativeSystem()
{
    PrimaryComponentTick.bCanEverTick = true;
    SetIsReplicatedByDefault(true);
    
    bDialogueActive = false;
    CurrentChapter = TEXT("Chapter 1: The Beginning");
}

void UNarrativeSystem::BeginPlay()
{
    Super::BeginPlay();
    InitializeNarrativeSystem();
}

void UNarrativeSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    UpdateQuestProgress();
    CheckQuestCompletion();
    TriggerStoryEvents();
    UpdateNPCAttitudes();
}

void UNarrativeSystem::InitializeNarrativeSystem()
{
    UE_LOG(LogTemp, Warning, TEXT("Narrative System initialized"));
    
    // Initialize all narrative systems
    InitializeDialogueDatabase();
    InitializeQuestDatabase();
    InitializeLoreDatabase();
    
    // Load saved narrative state
    LoadNarrativeState();
    
    UE_LOG(LogTemp, Warning, TEXT("Narrative System ready"));
}

bool UNarrativeSystem::StartDialogue(const FString& DialogueID, const FString& SpeakerID)
{
    if (bDialogueActive)
    {
        UE_LOG(LogTemp, Warning, TEXT("Dialogue already active"));
        return false;
    }
    
    // Find dialogue node in database
    for (const FDialogueNode& Node : DialogueDatabase)
    {
        if (Node.NodeID == DialogueID)
        {
            // Check if dialogue conditions are met
            if (!Node.Options.IsEmpty())
            {
                bool bHasValidOptions = false;
                for (const FDialogueOption& Option : Node.Options)
                {
                    if (!Option.bIsHidden && ValidateDialogueCondition(Option.ConditionScript))
                    {
                        bHasValidOptions = true;
                        break;
                    }
                }
                
                if (!bHasValidOptions)
                {
                    UE_LOG(LogTemp, Warning, TEXT("No valid dialogue options for: %s"), *DialogueID);
                    return false;
                }
            }
            
            CurrentDialogue = Node;
            CurrentSpeakerID = SpeakerID;
            bDialogueActive = true;
            
            NotifyDialogueStarted(CurrentDialogue);
            
            UE_LOG(LogTemp, Warning, TEXT("Dialogue started: %s"), *DialogueID);
            return true;
        }
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Dialogue not found: %s"), *DialogueID);
    return false;
}

bool UNarrativeSystem::SelectDialogueOption(int32 OptionID)
{
    if (!bDialogueActive)
    {
        UE_LOG(LogTemp, Warning, TEXT("No dialogue active"));
        return false;
    }
    
    for (const FDialogueOption& Option : CurrentDialogue.Options)
    {
        if (Option.OptionID == OptionID && !Option.bIsHidden)
        {
            // Check option conditions
            if (Option.bRequiresCondition && !ValidateDialogueCondition(Option.ConditionScript))
            {
                UE_LOG(LogTemp, Warning, TEXT("Dialogue option conditions not met: %d"), OptionID);
                return false;
            }
            
            NotifyDialogueOptionSelected(Option);
            ProcessDialogueChoice(Option);
            
            UE_LOG(LogTemp, Warning, TEXT("Dialogue option selected: %d"), OptionID);
            return true;
        }
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Dialogue option not found: %d"), OptionID);
    return false;
}

void UNarrativeSystem::EndDialogue()
{
    if (!bDialogueActive)
    {
        return;
    }
    
    FString EndedNodeID = CurrentDialogue.NodeID;
    bDialogueActive = false;
    CurrentDialogue = FDialogueNode();
    CurrentSpeakerID = TEXT("");
    
    NotifyDialogueEnded(EndedNodeID);
    
    UE_LOG(LogTemp, Warning, TEXT("Dialogue ended"));
}

FDialogueNode UNarrativeSystem::GetCurrentDialogue() const
{
    return CurrentDialogue;
}

bool UNarrativeSystem::IsDialogueActive() const
{
    return bDialogueActive;
}

TArray<FDialogueOption> UNarrativeSystem::GetAvailableOptions() const
{
    TArray<FDialogueOption> AvailableOptions;
    
    if (!bDialogueActive)
    {
        return AvailableOptions;
    }
    
    for (const FDialogueOption& Option : CurrentDialogue.Options)
    {
        if (!Option.bIsHidden && (!Option.bRequiresCondition || ValidateDialogueCondition(Option.ConditionScript)))
        {
            AvailableOptions.Add(Option);
        }
    }
    
    return AvailableOptions;
}

bool UNarrativeSystem::HasDialogueCondition(const FString& Condition) const
{
    return ValidateDialogueCondition(Condition);
}

TArray<FQuest> UNarrativeSystem::GetAvailableQuests() const
{
    TArray<FQuest> AvailableQuests;
    
    for (const FQuest& Quest : QuestDatabase)
    {
        if (Quest.Status == EQuestStatus::QS_NotStarted && CanStartQuest(Quest.QuestID))
        {
            AvailableQuests.Add(Quest);
        }
    }
    
    return AvailableQuests;
}

TArray<FQuest> UNarrativeSystem::GetActiveQuests() const
{
    TArray<FQuest> ActiveQuestList;
    
    for (const auto& QuestPair : ActiveQuests)
    {
        ActiveQuestList.Add(QuestPair.Value);
    }
    
    return ActiveQuestList;
}

TArray<FQuest> UNarrativeSystem::GetCompletedQuests() const
{
    TArray<FQuest> CompletedQuestList;
    
    for (const auto& QuestPair : CompletedQuests)
    {
        CompletedQuestList.Add(QuestPair.Value);
    }
    
    return CompletedQuestList;
}

bool UNarrativeSystem::StartQuest(const FString& QuestID)
{
    if (!CanStartQuest(QuestID))
    {
        UE_LOG(LogTemp, Warning, TEXT("Cannot start quest: %s"), *QuestID);
        return false;
    }
    
    for (const FQuest& QuestTemplate : QuestDatabase)
    {
        if (QuestTemplate.QuestID == QuestID)
        {
            FQuest NewQuest = QuestTemplate;
            NewQuest.Status = EQuestStatus::QS_Active;
            
            ActiveQuests.Add(QuestID, NewQuest);
            
            // Update quest in database
            for (FQuest& Quest : QuestDatabase)
            {
                if (Quest.QuestID == QuestID)
                {
                    Quest.Status = EQuestStatus::QS_Active;
                    break;
                }
            }
            
            NotifyQuestStarted(NewQuest);
            
            UE_LOG(LogTemp, Warning, TEXT("Quest started: %s"), *QuestID);
            return true;
        }
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Quest not found: %s"), *QuestID);
    return false;
}

bool UNarrativeSystem::CompleteQuest(const FString& QuestID)
{
    if (!ActiveQuests.Contains(QuestID))
    {
        UE_LOG(LogTemp, Warning, TEXT("Quest not active: %s"), *QuestID);
        return false;
    }
    
    FQuest CompletedQuest = ActiveQuests[QuestID];
    CompletedQuest.Status = EQuestStatus::QS_Completed;
    
    // Move to completed quests
    CompletedQuests.Add(QuestID, CompletedQuest);
    ActiveQuests.Remove(QuestID);
    
    // Update quest in database
    for (FQuest& Quest : QuestDatabase)
    {
        if (Quest.QuestID == QuestID)
        {
            Quest.Status = EQuestStatus::QS_Completed;
            break;
        }
    }
    
    // Grant rewards
    GrantQuestRewards(CompletedQuest);
    
    NotifyQuestCompleted(CompletedQuest);
    
    UE_LOG(LogTemp, Warning, TEXT("Quest completed: %s"), *QuestID);
    return true;
}

bool UNarrativeSystem::UpdateQuestObjective(const FString& QuestID, const FString& ObjectiveID, int32 Progress)
{
    if (!ActiveQuests.Contains(QuestID))
    {
        return false;
    }
    
    FQuest& Quest = ActiveQuests[QuestID];
    
    for (FQuestObjective& Objective : Quest.Objectives)
    {
        if (Objective.ObjectiveID == ObjectiveID)
        {
            Objective.CurrentCount += Progress;
            
            if (Objective.CurrentCount >= Objective.RequiredCount)
            {
                Objective.bIsCompleted = true;
            }
            
            // Update quest in database
            for (FQuest& DBQuest : QuestDatabase)
            {
                if (DBQuest.QuestID == QuestID)
                {
                    for (FQuestObjective& DBObjective : DBQuest.Objectives)
                    {
                        if (DBObjective.ObjectiveID == ObjectiveID)
                        {
                            DBObjective.CurrentCount = Objective.CurrentCount;
                            DBObjective.bIsCompleted = Objective.bIsCompleted;
                            break;
                        }
                    }
                    break;
                }
            }
            
            NotifyQuestUpdated(Quest);
            
            UE_LOG(LogTemp, Warning, TEXT("Quest objective updated: %s - %s (%d/%d)"), 
                   *QuestID, *ObjectiveID, Objective.CurrentCount, Objective.RequiredCount);
            return true;
        }
    }
    
    return false;
}

FQuest UNarrativeSystem::GetQuest(const FString& QuestID) const
{
    // Check active quests first
    if (ActiveQuests.Contains(QuestID))
    {
        return ActiveQuests[QuestID];
    }
    
    // Check completed quests
    if (CompletedQuests.Contains(QuestID))
    {
        return CompletedQuests[QuestID];
    }
    
    // Check database
    for (const FQuest& Quest : QuestDatabase)
    {
        if (Quest.QuestID == QuestID)
        {
            return Quest;
        }
    }
    
    FQuest EmptyQuest;
    return EmptyQuest;
}

EQuestStatus UNarrativeSystem::GetQuestStatus(const FString& QuestID) const
{
    FQuest Quest = GetQuest(QuestID);
    return Quest.Status;
}

bool UNarrativeSystem::CanStartQuest(const FString& QuestID) const
{
    for (const FQuest& Quest : QuestDatabase)
    {
        if (Quest.QuestID == QuestID)
        {
            // Check level requirement
            AActor* OwnerActor = GetOwner();
            if (!OwnerActor)
            {
                return false;
            }
            
            // This would typically check player level
            // For now, we'll assume level requirement is met
            
            // Check prerequisites
            return ValidateQuestPrerequisites(QuestID);
        }
    }
    
    return false;
}

void UNarrativeSystem::AbandonQuest(const FString& QuestID)
{
    if (ActiveQuests.Contains(QuestID))
    {
        ActiveQuests.Remove(QuestID);
        
        // Update quest in database
        for (FQuest& Quest : QuestDatabase)
        {
            if (Quest.QuestID == QuestID)
            {
                Quest.Status = EQuestStatus::QS_Abandoned;
                break;
            }
        }
        
        UE_LOG(LogTemp, Warning, TEXT("Quest abandoned: %s"), *QuestID);
    }
}

TArray<FLoreEntry> UNarrativeSystem::GetDiscoveredLore() const
{
    TArray<FLoreEntry> DiscoveredEntries;
    
    for (const FLoreEntry& Lore : LoreDatabase)
    {
        if (Lore.bIsDiscovered)
        {
            DiscoveredEntries.Add(Lore);
        }
    }
    
    return DiscoveredEntries;
}

TArray<FLoreEntry> UNarrativeSystem::GetLoreByType(ELoreType LoreType) const
{
    TArray<FLoreEntry> TypedLore;
    
    for (const FLoreEntry& Lore : LoreDatabase)
    {
        if (Lore.LoreType == LoreType && Lore.bIsDiscovered)
        {
            TypedLore.Add(Lore);
        }
    }
    
    return TypedLore;
}

bool UNarrativeSystem::DiscoverLore(const FString& LoreID)
{
    if (DiscoveredLore.Contains(LoreID))
    {
        UE_LOG(LogTemp, Warning, TEXT("Lore already discovered: %s"), *LoreID);
        return false;
    }
    
    for (FLoreEntry& Lore : LoreDatabase)
    {
        if (Lore.LoreID == LoreID && !Lore.bIsDiscovered)
        {
            Lore.bIsDiscovered = true;
            DiscoveredLore.Add(LoreID);
            
            NotifyLoreDiscovered(Lore);
            
            UE_LOG(LogTemp, Warning, TEXT("Lore discovered: %s"), *LoreID);
            return true;
        }
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Lore not found: %s"), *LoreID);
    return false;
}

FLoreEntry UNarrativeSystem::GetLoreEntry(const FString& LoreID) const
{
    for (const FLoreEntry& Lore : LoreDatabase)
    {
        if (Lore.LoreID == LoreID)
        {
            return Lore;
        }
    }
    
    FLoreEntry EmptyLore;
    return EmptyLore;
}

bool UNarrativeSystem::IsLoreDiscovered(const FString& LoreID) const
{
    return DiscoveredLore.Contains(LoreID);
}

TArray<FString> UNarrativeSystem::GetRelatedLore(const FString& LoreID) const
{
    FLoreEntry Lore = GetLoreEntry(LoreID);
    return Lore.RelatedLore;
}

void UNarrativeSystem::UpdateStoryProgress(const FString& StoryEvent)
{
    StoryFlags.Add(StoryEvent);
    UpdateWorldState(StoryEvent);
    
    UE_LOG(LogTemp, Warning, TEXT("Story progress updated: %s"), *StoryEvent);
}

FString UNarrativeSystem::GetCurrentStoryChapter() const
{
    return CurrentChapter;
}

TArray<FString> UNarrativeSystem::GetStoryFlags() const
{
    return StoryFlags;
}

bool UNarrativeSystem::HasStoryFlag(const FString& Flag) const
{
    return StoryFlags.Contains(Flag);
}

void UNarrativeSystem::SetStoryFlag(const FString& Flag, bool bValue)
{
    if (bValue)
    {
        if (!StoryFlags.Contains(Flag))
        {
            StoryFlags.Add(Flag);
        }
    }
    else
    {
        StoryFlags.Remove(Flag);
    }
}

void UNarrativeSystem::UpdateNPCRelationship(const FString& NPCID, int32 RelationshipChange)
{
    if (!NPCRelationships.Contains(NPCID))
    {
        NPCRelationships.Add(NPCID, 0);
    }
    
    NPCRelationships[NPCID] += RelationshipChange;
    
    UE_LOG(LogTemp, Warning, TEXT("NPC relationship updated: %s (%d)"), *NPCID, NPCRelationships[NPCID]);
}

int32 UNarrativeSystem::GetNPCRelationship(const FString& NPCID) const
{
    if (NPCRelationships.Contains(NPCID))
    {
        return NPCRelationships[NPCID];
    }
    
    return 0;
}

TArray<FString> UNarrativeSystem::GetNPCsWithRelationship(int32 MinRelationship) const
{
    TArray<FString> FriendlyNPCs;
    
    for (const auto& RelationshipPair : NPCRelationships)
    {
        if (RelationshipPair.Value >= MinRelationship)
        {
            FriendlyNPCs.Add(RelationshipPair.Key);
        }
    }
    
    return FriendlyNPCs;
}

void UNarrativeSystem::SaveNarrativeState()
{
    SaveDialogueState();
    SaveQuestState();
    SaveLoreState();
    
    UE_LOG(LogTemp, Warning, TEXT("Narrative state saved"));
}

void UNarrativeSystem::LoadNarrativeState()
{
    LoadDialogueState();
    LoadQuestState();
    LoadLoreState();
    
    UE_LOG(LogTemp, Warning, TEXT("Narrative state loaded"));
}

void UNarrativeSystem::ResetNarrativeState()
{
    bDialogueActive = false;
    CurrentDialogue = FDialogueNode();
    CurrentSpeakerID = TEXT("");
    ActiveQuests.Empty();
    CompletedQuests.Empty();
    StoryFlags.Empty();
    CurrentChapter = TEXT("Chapter 1: The Beginning");
    NPCRelationships.Empty();
    DiscoveredLore.Empty();
    
    // Reset quest database
    for (FQuest& Quest : QuestDatabase)
    {
        Quest.Status = EQuestStatus::QS_NotStarted;
        for (FQuestObjective& Objective : Quest.Objectives)
        {
            Objective.CurrentCount = 0;
            Objective.bIsCompleted = false;
        }
    }
    
    // Reset lore database
    for (FLoreEntry& Lore : LoreDatabase)
    {
        Lore.bIsDiscovered = false;
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Narrative state reset"));
}

void UNarrativeSystem::InitializeDialogueDatabase()
{
    DialogueDatabase.Empty();
    
    // Create starting dialogue for Guild Master
    FDialogueNode GuildMasterGreeting = CreateDialogueNode(
        TEXT("GUILD_MASTER_GREETING"),
        TEXT("Guild Master"),
        TEXT("Welcome, hunter. We have a situation that requires your attention. Monsters have been pouring out from a mysterious gate in the forest. We need someone to investigate and close it.")
    );
    
    // Add dialogue options
    FDialogueOption AcceptQuest;
    AcceptQuest.OptionText = TEXT("I'll investigate the gate.");
    AcceptQuest.OptionID = 1;
    AcceptQuest.NextDialogueID = TEXT("GUILD_MASTER_ACCEPT");
    AcceptQuest.ConsequenceScript = TEXT("StartQuest(InvestigateGate)");
    
    FDialogueOption AskQuestions;
    AskQuestions.OptionText = TEXT("Tell me more about this gate.");
    AskQuestions.OptionID = 2;
    AskQuestions.NextDialogueID = TEXT("GUILD_MASTER_EXPLAIN");
    
    GuildMasterGreeting.Options.Add(AcceptQuest);
    GuildMasterGreeting.Options.Add(AskQuestions);
    
    DialogueDatabase.Add(GuildMasterGreeting);
    
    // Create explanation dialogue
    FDialogueNode GuildMasterExplain = CreateDialogueNode(
        TEXT("GUILD_MASTER_EXPLAIN"),
        TEXT("Guild Master"),
        TEXT("The gate appeared three days ago. It's unlike anything we've seen before - dark, swirling energy that seems to be corrupting the forest around it. We've already lost two hunters who went to investigate.")
    );
    
    FDialogueOption BackToGreeting;
    BackToGreeting.OptionText = TEXT("I understand. I'll handle it.");
    BackToGreeting.OptionID = 1;
    BackToGreeting.NextDialogueID = TEXT("GUILD_MASTER_ACCEPT");
    BackToGreeting.ConsequenceScript = TEXT("StartQuest(InvestigateGate)");
    
    GuildMasterExplain.Options.Add(BackToGreeting);
    
    DialogueDatabase.Add(GuildMasterExplain);
    
    // Create acceptance dialogue
    FDialogueNode GuildMasterAccept = CreateDialogueNode(
        TEXT("GUILD_MASTER_ACCEPT"),
        TEXT("Guild Master"),
        TEXT("Excellent! The gate is located to the east of here, in the dark forest. Be careful - the monsters coming through are unlike anything we've faced before. Return here when you've closed the gate.")
    );
    
    DialogueDatabase.Add(GuildMasterAccept);
}

void UNarrativeSystem::InitializeQuestDatabase()
{
    QuestDatabase.Empty();
    
    // Create main quest
    FQuest InvestigateGate = CreateQuest(
        TEXT("InvestigateGate"),
        TEXT("Investigate the Mysterious Gate"),
        TEXT("The Guild Master has tasked you with investigating a mysterious gate that has appeared in the forest, unleashing dangerous monsters.")
    );
    
    InvestigateGate.bIsMainQuest = true;
    InvestigateGate.RequiredLevel = 1;
    InvestigateGate.QuestGiverID = TEXT("GuildMaster");
    
    // Add objectives
    FQuestObjective FindGate;
    FindGate.ObjectiveID = TEXT("FindGate");
    FindGate.Description = TEXT("Locate the mysterious gate in the forest");
    FindGate.ObjectiveType = TEXT("Explore");
    FindGate.RequiredCount = 1;
    FindGate.CurrentCount = 0;
    FindGate.bIsCompleted = false;
    FindGate.LocationHint = TEXT("Search in the dark forest to the east");
    
    FQuestObjective CloseGate;
    CloseGate.ObjectiveID = TEXT("CloseGate");
    CloseGate.Description = TEXT("Close the mysterious gate");
    CloseGate.ObjectiveType = TEXT("Interact");
    CloseGate.RequiredCount = 1;
    CloseGate.CurrentCount = 0;
    CloseGate.bIsCompleted = false;
    CloseGate.LocationHint = TEXT("Interact with the gate mechanism");
    
    FQuestObjective DefeatBoss;
    DefeatBoss.ObjectiveID = TEXT("DefeatBoss");
    DefeatBoss.Description = TEXT("Defeat the Shadow Monarch's Avatar");
    DefeatBoss.ObjectiveType = TEXT("Kill");
    DefeatBoss.RequiredCount = 1;
    DefeatBoss.CurrentCount = 0;
    DefeatBoss.bIsCompleted = false;
    
    InvestigateGate.Objectives.Add(FindGate);
    InvestigateGate.Objectives.Add(CloseGate);
    InvestigateGate.Objectives.Add(DefeatBoss);
    
    // Add rewards
    FQuestReward RankUpReward;
    RankUpReward.RewardType = TEXT("Rank");
    RankUpReward.RewardID = TEXT("E");
    RankUpReward.Quantity = 1;
    RankUpReward.Description = TEXT("Promoted to E-rank hunter");
    RankUpReward.bIsGuaranteed = true;
    
    FQuestReward GoldReward;
    GoldReward.RewardType = TEXT("Gold");
    GoldReward.RewardID = TEXT("Gold");
    GoldReward.Quantity = 500;
    GoldReward.Description = TEXT("500 gold coins");
    GoldReward.bIsGuaranteed = true;
    
    InvestigateGate.Rewards.Add(RankUpReward);
    InvestigateGate.Rewards.Add(GoldReward);
    
    QuestDatabase.Add(InvestigateGate);
}

void UNarrativeSystem::InitializeLoreDatabase()
{
    LoreDatabase.Empty();
    
    // Create lore entries
    FLoreEntry HunterRanks = CreateLoreEntry(
        TEXT("HunterRanks"),
        TEXT("Hunter Ranks System"),
        TEXT("The Hunters Guild ranks hunters from F (lowest) to S (highest). Rank determines the types of missions available and the respect received from other hunters. Promotion requires completing dangerous missions and proving one's strength."),
        ELoreType::LT_Faction
    );
    
    FLoreEntry ShadowGates = CreateLoreEntry(
        TEXT("ShadowGates"),
        TEXT("The Shadow Gates"),
        TEXT("Mysterious portals that connect our world to the Shadow Realm. They appear without warning and unleash dangerous creatures. Few who enter return to tell the tale. The Guild believes they are a growing threat that must be contained."),
        ELoreType::LT_World
    );
    
    FLoreEntry ShadowMonarch = CreateLoreEntry(
        TEXT("ShadowMonarch"),
        TEXT("The Shadow Monarch"),
        TEXT("A legendary figure said to command the shadows and rule over the Shadow Realm. Some believe the Monarch is responsible for the gates, while others think they are fighting against the same threat. The truth remains shrouded in mystery."),
        ELoreType::LT_Character
    );
    
    LoreDatabase.Add(HunterRanks);
    LoreDatabase.Add(ShadowGates);
    LoreDatabase.Add(ShadowMonarch);
}

void UNarrativeSystem::ProcessDialogueChoice(const FDialogueOption& Option)
{
    // Process consequences
    if (!Option.ConsequenceScript.IsEmpty())
    {
        ProcessConsequences(Option.ConsequenceScript);
    }
    
    // Navigate to next dialogue or end
    if (!Option.NextDialogueID.IsEmpty())
    {
        StartDialogue(Option.NextDialogueID, CurrentSpeakerID);
    }
    else
    {
        EndDialogue();
    }
}

void UNarrativeSystem::CheckQuestCompletion()
{
    TArray<FString> QuestsToComplete;
    
    for (auto& QuestPair : ActiveQuests)
    {
        FQuest& Quest = QuestPair.Value;
        bool bAllObjectivesComplete = true;
        
        for (const FQuestObjective& Objective : Quest.Objectives)
        {
            if (!Objective.bIsOptional && !Objective.bIsCompleted)
            {
                bAllObjectivesComplete = false;
                break;
            }
        }
        
        if (bAllObjectivesComplete)
        {
            QuestsToComplete.Add(Quest.QuestID);
        }
    }
    
    for (const FString& QuestID : QuestsToComplete)
    {
        CompleteQuest(QuestID);
    }
}

void UNarrativeSystem::UpdateQuestProgress()
{
    // This would typically check for automatic quest updates
    // For now, we'll leave this as a placeholder for future implementation
}

void UNarrativeSystem::TriggerStoryEvents()
{
    // Check for story flag conditions and trigger appropriate events
    // This would typically handle branching storylines
}

void UNarrativeSystem::UpdateNPCAttitudes()
{
    // Update NPC attitudes based on player actions and story progress
    // This would affect dialogue options and availability
}

FDialogueNode UNarrativeSystem::CreateDialogueNode(const FString& ID, const FString& Speaker, const FString& Text)
{
    FDialogueNode Node;
    Node.NodeID = ID;
    Node.SpeakerName = Speaker;
    Node.DialogueText = Text;
    Node.DialogueType = EDialogueType::DT_Simple;
    Node.Options.Empty();
    Node.AudioPath = TEXT("");
    Node.AnimationName = TEXT("");
    Node.DisplayDuration = 5.0f;
    Node.bIsImportant = false;
    Node.TriggeredEvents.Empty();
    Node.QuestUpdate = TEXT("");
    
    return Node;
}

FQuest UNarrativeSystem::CreateQuest(const FString& ID, const FString& Name, const FString& Description)
{
    FQuest Quest;
    Quest.QuestID = ID;
    Quest.QuestName = Name;
    Quest.Description = Description;
    Quest.Status = EQuestStatus::QS_NotStarted;
    Quest.Objectives.Empty();
    Quest.Rewards.Empty();
    Quest.QuestGiverID = TEXT("");
    Quest.RequiredLevel = 1;
    Quest.PrerequisiteQuests.Empty();
    Quest.bIsMainQuest = false;
    Quest.bIsRepeatable = false;
    Quest.TimeLimit = 0;
    Quest.StartDialogueID = TEXT("");
    Quest.CompleteDialogueID = TEXT("");
    Quest.QuestIcon = nullptr;
    Quest.Tags.Empty();
    
    return Quest;
}

FLoreEntry UNarrativeSystem::CreateLoreEntry(const FString& ID, const FString& Title, const FString& Content, ELoreType Type)
{
    FLoreEntry Lore;
    Lore.LoreID = ID;
    Lore.Title = Title;
    Lore.Content = Content;
    Lore.LoreType = Type;
    Lore.SourceID = TEXT("");
    Lore.bIsDiscovered = false;
    Lore.DiscoveryCondition = TEXT("");
    Lore.RelatedLore.Empty();
    Lore.LoreIcon = nullptr;
    Lore.AudioNarration = TEXT("");
    
    return Lore;
}

void UNarrativeSystem::NotifyDialogueStarted(const FDialogueNode& DialogueNode)
{
    OnDialogueStarted.Broadcast(DialogueNode);
}

void UNarrativeSystem::NotifyDialogueOptionSelected(const FDialogueOption& SelectedOption)
{
    OnDialogueOptionSelected.Broadcast(SelectedOption);
}

void UNarrativeSystem::NotifyDialogueEnded(const FString& NodeID)
{
    OnDialogueEnded.Broadcast(NodeID);
}

void UNarrativeSystem::NotifyQuestStarted(const FQuest& Quest)
{
    OnQuestStarted.Broadcast(Quest);
}

void UNarrativeSystem::NotifyQuestCompleted(const FQuest& Quest)
{
    OnQuestCompleted.Broadcast(Quest);
}

void UNarrativeSystem::NotifyQuestUpdated(const FQuest& Quest)
{
    OnQuestUpdated.Broadcast(Quest);
}

void UNarrativeSystem::NotifyLoreDiscovered(const FLoreEntry& LoreEntry)
{
    OnLoreDiscovered.Broadcast(LoreEntry);
}

bool UNarrativeSystem::ValidateDialogueCondition(const FString& Condition) const
{
    if (Condition.IsEmpty())
    {
        return true;
    }
    
    // Simple condition parsing for now
    // In a full implementation, this would be more sophisticated
    if (Condition.Contains(TEXT("HasStoryFlag")))
    {
        // Extract flag name and check
        return true; // Placeholder
    }
    else if (Condition.Contains(TEXT("GetNPCRelationship")))
    {
        // Extract NPC ID and check relationship
        return true; // Placeholder
    }
    
    return true;
}

bool UNarrativeSystem::ValidateQuestPrerequisites(const FString& QuestID) const
{
    for (const FQuest& Quest : QuestDatabase)
    {
        if (Quest.QuestID == QuestID)
        {
            for (const FString& PrerequisiteID : Quest.PrerequisiteQuests)
            {
                if (!CompletedQuests.Contains(PrerequisiteID))
                {
                    return false;
                }
            }
            return true;
        }
    }
    
    return false;
}

void UNarrativeSystem::GrantQuestRewards(const FQuest& Quest)
{
    for (const FQuestReward& Reward : Quest.Rewards)
    {
        if (Reward.bIsGuaranteed)
        {
            // Grant reward logic here
            UE_LOG(LogTemp, Warning, TEXT("Quest reward granted: %s x%d"), *Reward.RewardID, Reward.Quantity);
            
            // Update story progress for rank-up
            if (Reward.RewardType == TEXT("Rank") && Reward.RewardID == TEXT("E"))
            {
                UpdateStoryProgress(TEXT("RankE"));
                CurrentChapter = TEXT("Chapter 2: E-Rank Hunter");
            }
        }
    }
}

void UNarrativeSystem::ProcessConsequences(const FString& ConsequenceScript)
{
    // Simple consequence processing
    if (ConsequenceScript.Contains(TEXT("StartQuest")))
    {
        // Extract quest ID and start quest
        FString QuestID = TEXT("InvestigateGate"); // Placeholder extraction
        StartQuest(QuestID);
    }
    else if (ConsequenceScript.Contains(TEXT("DiscoverLore")))
    {
        // Extract lore ID and discover lore
        FString LoreID = TEXT("HunterRanks"); // Placeholder extraction
        DiscoverLore(LoreID);
    }
}

void UNarrativeSystem::UpdateWorldState(const FString& Event)
{
    // Update world state based on events
    // This would affect NPC behavior, world conditions, etc.
}

void UNarrativeSystem::SaveDialogueState()
{
    // Save dialogue state
}

void UNarrativeSystem::SaveQuestState()
{
    // Save quest state
}

void UNarrativeSystem::SaveLoreState()
{
    // Save lore state
}

void UNarrativeSystem::LoadDialogueState()
{
    // Load dialogue state
}

void UNarrativeSystem::LoadQuestState()
{
    // Load quest state
}

void UNarrativeSystem::LoadLoreState()
{
    // Load lore state
}

void UNarrativeSystem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    DOREPLIFETIME(UNarrativeSystem, DialogueDatabase);
    DOREPLIFETIME(UNarrativeSystem, QuestDatabase);
    DOREPLIFETIME(UNarrativeSystem, LoreDatabase);
    DOREPLIFETIME(UNarrativeSystem, CurrentDialogue);
    DOREPLIFETIME(UNarrativeSystem, bDialogueActive);
    DOREPLIFETIME(UNarrativeSystem, ActiveQuests);
    DOREPLIFETIME(UNarrativeSystem, CompletedQuests);
    DOREPLIFETIME(UNarrativeSystem, StoryFlags);
    DOREPLIFETIME(UNarrativeSystem, CurrentChapter);
    DOREPLIFETIME(UNarrativeSystem, NPCRelationships);
    DOREPLIFETIME(UNarrativeSystem, DiscoveredLore);
}
