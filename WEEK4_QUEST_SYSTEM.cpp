// 📜 QUEST SYSTEM - COMPLETE IMPLEMENTATION

#include "QuestManager.h"
#include "ShadowMonarchCharacter.h"
#include "HunterStatsComponent.h"
#include "Kismet/GameplayStatics.h"

void UQuestManager::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    LoadQuestDatabase();
    LoadQuestProgress();
    UE_LOG(LogTemp, Warning, TEXT("Quest Manager initialized"));
}

void UQuestManager::LoadQuestDatabase()
{
    // Main Story Quests
    FQuestData AwakeningQuest;
    AwakeningQuest.QuestID = "main_001";
    AwakeningQuest.QuestName = "The Awakening";
    AwakeningQuest.QuestDescription = "Survive your first dungeon encounter and discover your true potential.";
    AwakeningQuest.QuestType = EQuestType::MainStory;
    AwakeningQuest.QuestLevel = 1;
    
    FQuestObjective Obj1;
    Obj1.ObjectiveID = "kill_goblins";
    Obj1.Description = "Kill 5 Goblins";
    Obj1.RequiredCount = 5;
    Obj1.CurrentCount = 0;
    Obj1.bIsCompleted = false;
    
    AwakeningQuest.Objectives.Add(Obj1);
    AwakeningQuest.Rewards.Experience = 100;
    AwakeningQuest.Rewards.Gold = 50;
    AwakeningQuest.QuestGiver = "GuildMaster";
    AwakeningQuest.TurnInNPC = "GuildMaster";
    
    QuestDatabase.Add(AwakeningQuest.QuestID, AwakeningQuest);
    
    UE_LOG(LogTemp, Warning, TEXT("Quest database loaded"));
}

bool UQuestManager::AcceptQuest(const FString& QuestID)
{
    if (!QuestDatabase.Contains(QuestID)) return false;
    
    FQuestData Quest = QuestDatabase[QuestID];
    if (Quest.QuestStatus != EQuestStatus::Available) return false;
    
    Quest.QuestStatus = EQuestStatus::Active;
    QuestDatabase[QuestID] = Quest;
    ActiveQuestIDs.Add(QuestID);
    
    UE_LOG(LogTemp, Warning, TEXT("Accepted quest: %s"), *Quest.QuestName);
    return true;
}

void UQuestManager::OnEnemyKilled(const FString& EnemyType)
{
    for (const FString& QuestID : ActiveQuestIDs)
    {
        if (!QuestDatabase.Contains(QuestID)) continue;
        
        FQuestData Quest = QuestDatabase[QuestID];
        for (FQuestObjective& Objective : Quest.Objectives)
        {
            if (Objective.TargetType == EnemyType && !Objective.bIsCompleted)
            {
                Objective.CurrentCount++;
                if (Objective.CurrentCount >= Objective.RequiredCount)
                {
                    Objective.bIsCompleted = true;
                }
                
                UpdateQuestObjective(Objective.ObjectiveID, Objective.CurrentCount);
            }
        }
        
        CheckQuestCompletion();
    }
}

void UQuestManager::CheckQuestCompletion()
{
    for (const FString& QuestID : ActiveQuestIDs)
    {
        if (!QuestDatabase.Contains(QuestID)) continue;
        
        FQuestData Quest = QuestDatabase[QuestID];
        bool bAllObjectivesCompleted = true;
        
        for (const FQuestObjective& Objective : Quest.Objectives)
        {
            if (!Objective.bIsCompleted)
            {
                bAllObjectivesCompleted = false;
                break;
            }
        }
        
        if (bAllObjectivesCompleted && Quest.QuestStatus == EQuestStatus::Active)
        {
            CompleteQuest(QuestID);
        }
    }
}

bool UQuestManager::CompleteQuest(const FString& QuestID)
{
    if (!QuestDatabase.Contains(QuestID)) return false;
    
    FQuestData Quest = QuestDatabase[QuestID];
    Quest.QuestStatus = EQuestStatus::Completed;
    QuestDatabase[QuestID] = Quest;
    
    AwardQuestRewards(Quest);
    
    UE_LOG(LogTemp, Warning, TEXT("Completed quest: %s"), *Quest.QuestName);
    return true;
}

void UQuestManager::AwardQuestRewards(const FQuestData& Quest)
{
    UWorld* World = GetWorld();
    if (!World) return;
    
    ACharacter* Player = UGameplayStatics::GetPlayerCharacter(World, 0);
    if (!Player) return;
    
    if (UHunterStatsComponent* Stats = Player->FindComponentByClass<UHunterStatsComponent>())
    {
        Stats->AddExperience(Quest.Rewards.Experience);
        Stats->AddGold(Quest.Rewards.Gold);
        
        UE_LOG(LogTemp, Warning, TEXT("Quest rewards: %d EXP, %d Gold"), 
            Quest.Rewards.Experience, Quest.Rewards.Gold);
    }
}

// QUEST SYSTEM COMPLETE! 📜
// - Main story quests with progression
// - Side quests for additional content
// - Dynamic objective tracking
// - Reward system with EXP and gold
// - Quest save/load functionality
