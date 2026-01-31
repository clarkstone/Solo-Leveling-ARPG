#include "NPCSystem.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "AIController.h"

UNPCSystem::UNPCSystem()
{
    LastUpdateTime = 0.0f;
    bIsInDialogue = false;
    CurrentDialogueNPC = TEXT("");
}

void UNPCSystem::BeginPlay()
{
    Super::BeginPlay();
    Initialize();
}

void UNPCSystem::Initialize()
{
    InitializeNPCDatabase();
    InitializeRelationships();
    LoadNPCData();
    
    UE_LOG(LogTemp, Warning, TEXT("NPC System initialized"));
}

void UNPCSystem::InitializeNPCDatabase()
{
    // Initialize main characters from Solo Leveling
    FNPCRelationship ChaHaeIn;
    ChaHaeIn.NPCName = TEXT("Cha Hae-In");
    ChaHaeIn.AffinityLevel = 0.0f;
    ChaHaeIn.bIsRomanceOption = true;
    ChaHaeIn.bIsRival = false;
    ChaHaeIn.bIsFriend = false;
    ChaHaeIn.InteractionCount = 0;
    PlayerRelationships.Add(TEXT("Cha Hae-In"), ChaHaeIn);
    
    FNPCRelationship ThomasAndre;
    ThomasAndre.NPCName = TEXT("Thomas Andre");
    ThomasAndre.AffinityLevel = 0.0f;
    ThomasAndre.bIsRomanceOption = false;
    ThomasAndre.bIsRival = false;
    ThomasAndre.bIsFriend = true;
    ThomasAndre.InteractionCount = 0;
    PlayerRelationships.Add(TEXT("Thomas Andre"), ThomasAndre);
    
    FNPCRelationship LiuZhigang;
    LiuZhigang.NPCName = TEXT("Liu Zhigang");
    LiuZhigang.AffinityLevel = 0.0f;
    LiuZhigang.bIsRomanceOption = false;
    LiuZhigang.bIsRival = false;
    LiuZhigang.bIsFriend = true;
    LiuZhigang.InteractionCount = 0;
    PlayerRelationships.Add(TEXT("Liu Zhigang"), LiuZhigang);
    
    UE_LOG(LogTemp, Warning, TEXT("NPC database initialized"));
}

void UNPCSystem::RegisterNPC(FString NPCID, ANPC* NPC)
{
    if (NPC)
    {
        AllNPCs.Add(NPCID, NPC);
        
        // Add to type-based mapping
        ENPCType NPCType = NPC->GetNPCType();
        if (!NPCsByType.Contains(NPCType))
        {
            TArray<FString> TypeArray;
            NPCsByType.Add(NPCType, TypeArray);
        }
        NPCsByType[NPCType].Add(NPCID);
        
        UE_LOG(LogTemp, Warning, TEXT("NPC registered: %s"), *NPCID);
    }
}

void UNPCSystem::StartDialogue(FString NPCID, FString DialogueID)
{
    if (AllNPCs.Contains(NPCID))
    {
        ANPC* NPC = AllNPCs[NPCID];
        
        if (NPC)
        {
            bIsInDialogue = true;
            CurrentDialogueNPC = NPCID;
            
            // Set NPC to dialogue state
            SetNPCState(NPCID, ENPCState::NS_Dialogue);
            
            // Get dialogue data
            if (NPCDialogues.Contains(NPCID))
            {
                for (const FNPCDialogue& Dialogue : NPCDialogues[NPCID])
                {
                    if (Dialogue.DialogueID == DialogueID)
                    {
                        OnDialogueStarted.Broadcast(NPCID, Dialogue);
                        break;
                    }
                }
            }
            
            // Update relationship
            UpdateRelationship(NPCID, 0.1f);
            
            UE_LOG(LogTemp, Warning, TEXT("Dialogue started with %s: %s"), *NPCID, *DialogueID);
        }
    }
}

void UNPCSystem::ProcessDialogueChoice(FString NPCID, int32 ChoiceIndex)
{
    if (AllNPCs.Contains(NPCID) && NPCDialogues.Contains(NPCID))
    {
        TArray<FNPCDialogue>& Dialogues = NPCDialogues[NPCID];
        
        if (ChoiceIndex >= 0 && ChoiceIndex < Dialogues.Num())
        {
            FNPCDialogue& Dialogue = Dialogues[ChoiceIndex];
            
            // Process choice consequences
            if (ChoiceIndex < Dialogue.ChoiceConsequences.Num())
            {
                FString Consequence = Dialogue.ChoiceConsequences[ChoiceIndex];
                ProcessDialogueConsequences(NPCID, Consequence);
            }
            
            UE_LOG(LogTemp, Warning, TEXT("Dialogue choice processed: %s, Choice %d"), *NPCID, ChoiceIndex);
        }
    }
}

void UNPCSystem::EndDialogue(FString NPCID)
{
    if (CurrentDialogueNPC == NPCID)
    {
        bIsInDialogue = false;
        CurrentDialogueNPC = TEXT("");
        
        // Set NPC back to idle state
        SetNPCState(NPCID, ENPCState::NS_Idle);
        
        OnDialogueEnded.Broadcast(NPCID);
        
        UE_LOG(LogTemp, Warning, TEXT("Dialogue ended with %s"), *NPCID);
    }
}

void UNPCSystem::UpdateRelationship(FString NPCID, float AffinityChange)
{
    if (PlayerRelationships.Contains(NPCID))
    {
        FNPCRelationship& Relationship = PlayerRelationships[NPCID];
        Relationship.AffinityLevel += AffinityChange;
        Relationship.AffinityLevel = FMath::Clamp(Relationship.AffinityLevel, -100.0f, 100.0f);
        Relationship.InteractionCount++;
        
        OnRelationshipChanged.Broadcast(NPCID, Relationship.AffinityLevel);
        
        UE_LOG(LogTemp, Warning, TEXT("Relationship updated: %s (%.2f)"), *NPCID, Relationship.AffinityLevel);
    }
}

float UNPCSystem::GetRelationshipLevel(FString NPCID)
{
    if (PlayerRelationships.Contains(NPCID))
    {
        return PlayerRelationships[NPCID].AffinityLevel;
    }
    
    return 0.0f;
}

void UNPCSystem::UnlockDialogue(FString NPCID, FString DialogueID)
{
    if (PlayerRelationships.Contains(NPCID))
    {
        FNPCRelationship& Relationship = PlayerRelationships[NPCID];
        
        if (!Relationship.UnlockedDialogues.Contains(DialogueID))
        {
            Relationship.UnlockedDialogues.Add(DialogueID);
            
            UE_LOG(LogTemp, Warning, TEXT("Dialogue unlocked: %s - %s"), *NPCID, *DialogueID);
        }
    }
}

bool UNPCSystem::IsDialogueUnlocked(FString NPCID, FString DialogueID)
{
    if (PlayerRelationships.Contains(NPCID))
    {
        return PlayerRelationships[NPCID].UnlockedDialogues.Contains(DialogueID);
    }
    
    return false;
}

void UNPCSystem::OnWorldEventTriggered(FWorldEventData EventData)
{
    // Update NPC behaviors based on world events
    if (EventData.EventName == TEXT("GateOutbreak"))
    {
        // NPCs react to gate outbreak
        for (auto& NPCPair : AllNPCs)
        {
            ANPC* NPC = NPCPair.Value;
            if (NPC)
            {
                SetNPCState(NPCPair.Key, ENPCState::NS_Emergency);
            }
        }
    }
}

void UNPCSystem::OnPlayerLevelUp(int32 NewLevel)
{
    // Update NPC reactions to player level up
    for (auto& RelationshipPair : PlayerRelationships)
    {
        UpdateRelationship(RelationshipPair.Key, 0.5f);
    }
    
    UE_LOG(LogTemp, Warning, TEXT("NPCs reacted to player level up: %d"), NewLevel);
}

void UNPCSystem::OnQuestCompleted(FString QuestID)
{
    // Update NPC reactions to quest completion
    UE_LOG(LogTemp, Warning, TEXT("NPCs reacted to quest completion: %s"), *QuestID);
}

void UNPCSystem::OnGuildJoined(FString GuildName)
{
    // Update NPC reactions to guild joining
    UE_LOG(LogTemp, Warning, TEXT("NPCs reacted to guild joining: %s"), *GuildName);
}

void UNPCSystem::SetNPCState(FString NPCID, ENPCState NewState)
{
    if (AllNPCs.Contains(NPCID))
    {
        ANPC* NPC = AllNPCs[NPCID];
        if (NPC)
        {
            NPC->SetNPCState(NewState);
            
            UE_LOG(LogTemp, Warning, TEXT("NPC state set: %s -> %d"), *NPCID, (int32)NewState);
        }
    }
}

ENPCState UNPCSystem::GetNPCState(FString NPCID)
{
    if (AllNPCs.Contains(NPCID))
    {
        ANPC* NPC = AllNPCs[NPCID];
        if (NPC)
        {
            return NPC->GetNPCState();
        }
    }
    
    return ENPCState::NS_Idle;
}

void UNPCSystem::UpdateNPCAI()
{
    // Update AI for all registered NPCs
    for (auto& NPCPair : AllNPCs)
    {
        ANPC* NPC = NPCPair.Value;
        if (NPC)
        {
            NPC->UpdateAI();
        }
    }
}

void UNPCSystem::UpdateNPCSchedules()
{
    // Update NPC schedules based on time of day
    float CurrentTime = GetWorld()->GetTimeSeconds();
    
    for (auto& NPCPair : AllNPCs)
    {
        FString NPCID = NPCPair.Key;
        ANPC* NPC = NPCPair.Value;
        
        if (NPC && NPCSchedules.Contains(NPCID))
        {
            for (const FNPCSchedule& Schedule : NPCSchedules[NPCID])
            {
                if (CurrentTime >= Schedule.StartTime && CurrentTime <= Schedule.EndTime)
                {
                    SetNPCState(NPCID, Schedule.ScheduledState);
                    break;
                }
            }
        }
    }
}

void UNPCSystem::UpdateNPCBehaviors()
{
    // Update NPC behaviors based on relationships and world state
    for (auto& RelationshipPair : PlayerRelationships)
    {
        FString NPCID = RelationshipPair.Key;
        FNPCRelationship& Relationship = RelationshipPair.Value;
        
        if (Relationship.AffinityLevel > 50.0f)
        {
            // Friendly behavior
            if (AllNPCs.Contains(NPCID))
            {
                ANPC* NPC = AllNPCs[NPCID];
                if (NPC)
                {
                    NPC->SetBehaviorFriendly();
                }
            }
        }
        else if (Relationship.AffinityLevel < -50.0f)
        {
            // Hostile behavior
            if (AllNPCs.Contains(NPCID))
            {
                ANPC* NPC = AllNPCs[NPCID];
                if (NPC)
                {
                    NPC->SetBehaviorHostile();
                }
            }
        }
    }
}

void UNPCSystem::ProcessDialogueConsequences(FString NPCID, FString ChoiceID)
{
    // Process consequences of dialogue choices
    if (ChoiceID == TEXT("Positive"))
    {
        UpdateRelationship(NPCID, 5.0f);
    }
    else if (ChoiceID == TEXT("Negative"))
    {
        UpdateRelationship(NPCID, -5.0f);
    }
    else if (ChoiceID == TEXT("Romance"))
    {
        if (PlayerRelationships.Contains(NPCID))
        {
            FNPCRelationship& Relationship = PlayerRelationships[NPCID];
            if (Relationship.bIsRomanceOption)
            {
                UpdateRelationship(NPCID, 10.0f);
            }
        }
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Dialogue consequence processed: %s - %s"), *NPCID, *ChoiceID);
}

void UNPCSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    UpdateNPCAI();
    UpdateNPCSchedules();
    UpdateNPCBehaviors();
}

void UNPCSystem::LoadNPCData()
{
    // Load NPC data from files or database
    UE_LOG(LogTemp, Warning, TEXT("Loading NPC data..."));
}
