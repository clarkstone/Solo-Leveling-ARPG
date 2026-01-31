#include "QuestSystem.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

UQuestSystem::UQuestSystem()
{
    LastUpdateTime = 0.0f;
    bIsProcessingQuests = false;
}

void UQuestSystem::BeginPlay()
{
    Super::BeginPlay();
    Initialize();
}

void UQuestSystem::Initialize()
{
    InitializeQuestDatabase();
    LoadQuestDatabase();
    GenerateDailyQuests();
    
    UE_LOG(LogTemp, Warning, TEXT("Quest System initialized"));
}

void UQuestSystem::InitializeQuestDatabase()
{
    // Initialize main story quests
    FQuestData FirstGate;
    FirstGate.QuestID = TEXT("MainQuest_001");
    FirstGate.QuestTitle = TEXT("First Gate");
    FirstGate.QuestDescription = TEXT("Enter your first gate and defeat the monsters inside");
    FirstGate.QuestType = EQuestType::QT_Main;
    FirstGate.QuestStatus = EQuestStatus::QS_NotStarted;
    FirstGate.QuestLevel = 1;
    FirstGate.QuestGiver = TEXT("Hunter Association");
    
    // Add objectives
    FQuestObjective KillMonsters;
    KillMonsters.ObjectiveID = TEXT("KillMonsters");
    KillMonsters.Description = TEXT("Kill 10 monsters in the gate");
    KillMonsters.TargetType = TEXT("Monster");
    KillMonsters.RequiredCount = 10;
    KillMonsters.CurrentCount = 0;
    KillMonsters.bIsCompleted = false;
    KillMonsters.bIsOptional = false;
    FirstGate.Objectives.Add(KillMonsters);
    
    // Add rewards
    FQuestReward ExperienceReward;
    ExperienceReward.ExperienceReward = 100.0f;
    ExperienceReward.GoldReward = 50.0f;
    FirstGate.Rewards.Add(ExperienceReward);
    
    QuestDatabase.Add(TEXT("MainQuest_001"), FirstGate);
    
    // Initialize side quests
    FQuestData MonsterHunt;
    MonsterHunt.QuestID = TEXT("SideQuest_001");
    MonsterHunt.QuestTitle = TEXT("Monster Hunt");
    MonsterHunt.QuestDescription = TEXT("Hunt down dangerous monsters in the area");
    MonsterHunt.QuestType = EQuestType::QT_Side;
    MonsterHunt.QuestStatus = EQuestStatus::QS_NotStarted;
    MonsterHunt.QuestLevel = 5;
    MonsterHunt.bIsRepeatable = true;
    MonsterHunt.MaxCompletions = 3;
    
    QuestDatabase.Add(TEXT("SideQuest_001"), MonsterHunt);
    
    UE_LOG(LogTemp, Warning, TEXT("Quest database initialized"));
}

bool UQuestSystem::StartQuest(FString QuestID)
{
    if (QuestDatabase.Contains(QuestID))
    {
        FQuestData QuestData = QuestDatabase[QuestID];
        
        if (QuestData.QuestStatus == EQuestStatus::QS_NotStarted)
        {
            // Check prerequisites
            if (ValidateQuestPrerequisites(QuestData))
            {
                QuestData.QuestStatus = EQuestStatus::QS_InProgress;
                QuestDatabase[QuestID] = QuestData;
                ActiveQuests.Add(QuestData);
                
                if (QuestData.QuestType == EQuestType::QT_Main)
                {
                    CurrentMainQuest = QuestID;
                }
                
                OnQuestStarted.Broadcast(QuestData);
                UE_LOG(LogTemp, Warning, TEXT("Quest started: %s"), *QuestData.QuestTitle);
                return true;
            }
        }
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Cannot start quest: %s"), *QuestID);
    return false;
}

bool UQuestSystem::CompleteQuest(FString QuestID)
{
    if (QuestDatabase.Contains(QuestID))
    {
        FQuestData QuestData = QuestDatabase[QuestID];
        
        if (QuestData.QuestStatus == EQuestStatus::QS_InProgress)
        {
            // Check if all objectives are completed
            if (ValidateQuestProgress(QuestData))
            {
                QuestData.QuestStatus = EQuestStatus::QS_Completed;
                QuestDatabase[QuestID] = QuestData;
                
                // Remove from active quests
                for (int32 i = 0; i < ActiveQuests.Num(); i++)
                {
                    if (ActiveQuests[i].QuestID == QuestID)
                    {
                        ActiveQuests.RemoveAt(i);
                        break;
                    }
                }
                
                // Add to completed quests
                CompletedQuests.Add(QuestData);
                
                // Grant rewards
                GrantQuestRewards(QuestID);
                
                OnQuestCompleted.Broadcast(QuestData);
                UE_LOG(LogTemp, Warning, TEXT("Quest completed: %s"), *QuestData.QuestTitle);
                return true;
            }
        }
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Cannot complete quest: %s"), *QuestID);
    return false;
}

void UQuestSystem::UpdateQuestProgress(FString QuestID, FString ObjectiveID, int32 Progress)
{
    if (QuestDatabase.Contains(QuestID))
    {
        FQuestData& QuestData = QuestDatabase[QuestID];
        
        for (FQuestObjective& Objective : QuestData.Objectives)
        {
            if (Objective.ObjectiveID == ObjectiveID)
            {
                Objective.CurrentCount += Progress;
                
                if (Objective.CurrentCount >= Objective.RequiredCount)
                {
                    Objective.bIsCompleted = true;
                    OnObjectiveCompleted.Broadcast(QuestID, ObjectiveID);
                    UE_LOG(LogTemp, Warning, TEXT("Objective completed: %s"), *Objective.Description);
                }
                
                // Check if quest is complete
                CheckQuestCompletion();
                
                OnQuestUpdated.Broadcast(QuestData);
                break;
            }
        }
    }
}

void UQuestSystem::OnMonsterKilled(FString MonsterType, int32 Count)
{
    // Update all active quests with monster kill objectives
    for (FQuestData& QuestData : ActiveQuests)
    {
        for (FQuestObjective& Objective : QuestData.Objectives)
        {
            if (Objective.TargetType == TEXT("Monster") && !Objective.bIsCompleted)
            {
                UpdateQuestProgress(QuestData.QuestID, Objective.ObjectiveID, Count);
            }
        }
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Monster killed: %s x%d"), *MonsterType, Count);
}

void UQuestSystem::OnItemCollected(FString ItemName, int32 Count)
{
    // Update all active quests with item collection objectives
    for (FQuestData& QuestData : ActiveQuests)
    {
        for (FQuestObjective& Objective : QuestData.Objectives)
        {
            if (Objective.TargetType == TEXT("Item") && !Objective.bIsCompleted)
            {
                UpdateQuestProgress(QuestData.QuestID, Objective.ObjectiveID, Count);
            }
        }
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Item collected: %s x%d"), *ItemName, Count);
}

void UQuestSystem::OnLocationVisited(FString LocationName)
{
    // Update all active quests with location objectives
    for (FQuestData& QuestData : ActiveQuests)
    {
        for (FQuestObjective& Objective : QuestData.Objectives)
        {
            if (Objective.TargetType == TEXT("Location") && !Objective.bIsCompleted)
            {
                UpdateQuestProgress(QuestData.QuestID, Objective.ObjectiveID, 1);
            }
        }
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Location visited: %s"), *LocationName);
}

void UQuestSystem::OnPowerSystemUsed(FString PowerSystemName)
{
    // Update all active quests with power system objectives
    for (FQuestData& QuestData : ActiveQuests)
    {
        for (FQuestObjective& Objective : QuestData.Objectives)
        {
            if (Objective.TargetType == TEXT("PowerSystem") && !Objective.bIsCompleted)
            {
                UpdateQuestProgress(QuestData.QuestID, Objective.ObjectiveID, 1);
            }
        }
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Power system used: %s"), *PowerSystemName);
}

void UQuestSystem::GrantQuestRewards(FString QuestID)
{
    if (QuestDatabase.Contains(QuestID))
    {
        FQuestData QuestData = QuestDatabase[QuestID];
        
        for (FQuestReward& Reward : QuestData.Rewards)
        {
            ProcessReward(Reward);
        }
        
        UE_LOG(LogTemp, Warning, TEXT("Quest rewards granted for: %s"), *QuestData.QuestTitle);
    }
}

void UQuestSystem::ProcessReward(FQuestReward Reward)
{
    // Grant experience
    if (Reward.ExperienceReward > 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Experience granted: %.1f"), Reward.ExperienceReward);
    }
    
    // Grant gold
    if (Reward.GoldReward > 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("Gold granted: %.1f"), Reward.GoldReward);
    }
    
    // Grant items
    if (!Reward.ItemName.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("Item granted: %s x%d"), *Reward.ItemName, Reward.ItemQuantity);
    }
    
    // Unlock power systems
    if (!Reward.PowerSystemUnlock.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("Power system unlocked: %s"), *Reward.PowerSystemUnlock);
    }
}

void UQuestSystem::GenerateDailyQuests()
{
    // Generate daily quests based on player level and progress
    UE_LOG(LogTemp, Warning, TEXT("Daily quests generated"));
}

bool UQuestSystem::ValidateQuestPrerequisites(FQuestData& QuestData)
{
    // Check if all prerequisite quests are completed
    for (const FString& PrerequisiteQuest : QuestData.PrerequisiteQuests)
    {
        bool bFound = false;
        for (const FQuestData& CompletedQuest : CompletedQuests)
        {
            if (CompletedQuest.QuestID == PrerequisiteQuest)
            {
                bFound = true;
                break;
            }
        }
        
        if (!bFound)
        {
            return false;
        }
    }
    
    return true;
}

bool UQuestSystem::ValidateQuestProgress(FQuestData& QuestData)
{
    // Check if all required objectives are completed
    for (const FQuestObjective& Objective : QuestData.Objectives)
    {
        if (!Objective.bIsOptional && !Objective.bIsCompleted)
        {
            return false;
        }
    }
    
    return true;
}

void UQuestSystem::CheckQuestCompletion()
{
    // Check if any active quests are completed
    TArray<FString> QuestsToComplete;
    
    for (const FQuestData& QuestData : ActiveQuests)
    {
        if (ValidateQuestProgress(QuestData))
        {
            QuestsToComplete.Add(QuestData.QuestID);
        }
    }
    
    // Complete quests
    for (const FString& QuestID : QuestsToComplete)
    {
        CompleteQuest(QuestID);
    }
}

void UQuestSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    UpdateQuestStates();
    CheckQuestCompletion();
}

void UQuestSystem::UpdateQuestStates()
{
    // Update quest states based on game events
    // This would be called by other systems when relevant events occur
}

void UQuestSystem::LoadQuestDatabase()
{
    // Load quest data from files or database
    UE_LOG(LogTemp, Warning, TEXT("Loading quest database..."));
}
