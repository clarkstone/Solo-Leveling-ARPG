#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "QuestSystem.generated.h"

UENUM(BlueprintType)
enum class EQuestType : uint8
{
    QT_Main,
    QT_Side,
    QT_Daily,
    QT_Weekly,
    QT_Event,
    QT_Guild,
    QT_Hidden
};

UENUM(BlueprintType)
enum class EQuestStatus : uint8
{
    QS_NotStarted,
    QS_InProgress,
    QS_Completed,
    QS_Failed,
    QS_Abandoned
};

USTRUCT(BlueprintType)
struct FQuestObjective
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ObjectiveID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString TargetType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 RequiredCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 CurrentCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsCompleted;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsOptional;
};

USTRUCT(BlueprintType)
struct FQuestReward
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ItemName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ItemQuantity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float ExperienceReward;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float GoldReward;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString PowerSystemUnlock;
};

USTRUCT(BlueprintType)
struct FQuestData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString QuestID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString QuestTitle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString QuestDescription;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EQuestType QuestType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EQuestStatus QuestStatus;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 QuestLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FQuestObjective> Objectives;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FQuestReward> Rewards;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsRepeatable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxCompletions;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 CurrentCompletions;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> PrerequisiteQuests;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString QuestGiver;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString QuestLocation;
};

UCLASS()
class SIMPLEAPP_API UQuestSystem : public UActorComponent
{
    GENERATED_BODY()

public:
    UQuestSystem();

    // Quest Configuration
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quests")
    TMap<FString, FQuestData> QuestDatabase;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quests")
    TArray<FQuestData> ActiveQuests;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quests")
    TArray<FQuestData> CompletedQuests;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Quests")
    FString CurrentMainQuest;

    // Override UActorComponent functions
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Initialization
    UFUNCTION(BlueprintCallable, Category = "Quests")
    void Initialize();

    // Quest Management
    UFUNCTION(BlueprintCallable, Category = "Quests")
    bool StartQuest(FString QuestID);

    UFUNCTION(BlueprintCallable, Category = "Quests")
    bool CompleteQuest(FString QuestID);

    UFUNCTION(BlueprintCallable, Category = "Quests")
    bool AbandonQuest(FString QuestID);

    UFUNCTION(BlueprintCallable, Category = "Quests")
    void UpdateQuestProgress(FString QuestID, FString ObjectiveID, int32 Progress);

    // Quest Information
    UFUNCTION(BlueprintCallable, Category = "Quests")
    FQuestData GetQuestData(FString QuestID);

    UFUNCTION(BlueprintCallable, Category = "Quests")
    TArray<FQuestData> GetAvailableQuests();

    UFUNCTION(BlueprintCallable, Category = "Quests")
    TArray<FQuestData> GetQuestsByType(EQuestType QuestType);

    UFUNCTION(BlueprintCallable, Category = "Quests")
    bool IsQuestAvailable(FString QuestID);

    UFUNCTION(BlueprintCallable, Category = "Quests")
    bool IsQuestCompleted(FString QuestID);

    // Objective Management
    UFUNCTION(BlueprintCallable, Category = "Quests")
    void UpdateObjective(FString QuestID, FString ObjectiveID, int32 Amount);

    UFUNCTION(BlueprintCallable, Category = "Quests")
    bool IsObjectiveCompleted(FString QuestID, FString ObjectiveID);

    UFUNCTION(BlueprintCallable, Category = "Quests")
    float GetQuestProgress(FString QuestID);

    // Quest Events
    UFUNCTION(BlueprintCallable, Category = "Quests")
    void OnMonsterKilled(FString MonsterType, int32 Count);

    UFUNCTION(BlueprintCallable, Category = "Quests")
    void OnItemCollected(FString ItemName, int32 Count);

    UFUNCTION(BlueprintCallable, Category = "Quests")
    void OnLocationVisited(FString LocationName);

    UFUNCTION(BlueprintCallable, Category = "Quests")
    void OnPowerSystemUsed(FString PowerSystemName);

    UFUNCTION(BlueprintCallable, Category = "Quests")
    void OnDialogueCompleted(FString CharacterName, FString DialogueID);

    // Quest Rewards
    UFUNCTION(BlueprintCallable, Category = "Quests")
    void GrantQuestRewards(FString QuestID);

    UFUNCTION(BlueprintCallable, Category = "Quests")
    void ProcessReward(FQuestReward Reward);

    // Quest Generation
    UFUNCTION(BlueprintCallable, Category = "Quests")
    void GenerateDailyQuests();

    UFUNCTION(BlueprintCallable, Category = "Quests")
    void GenerateWeeklyQuests();

    UFUNCTION(BlueprintCallable, Category = "Quests")
    void GenerateEventQuests(FString EventName);

    // Quest Events
    UPROPERTY(BlueprintAssignable, Category = "Quest Events")
    FOnQuestStarted OnQuestStarted;

    UPROPERTY(BlueprintAssignable, Category = "Quest Events")
    FOnQuestCompleted OnQuestCompleted;

    UPROPERTY(BlueprintAssignable, Category = "Quest Events")
    FOnQuestUpdated OnQuestUpdated;

    UPROPERTY(BlueprintAssignable, Category = "Quest Events")
    FOnObjectiveCompleted OnObjectiveCompleted;

protected:
    // Internal Quest Systems
    void InitializeQuestDatabase();
    void UpdateQuestStates();
    void CheckQuestCompletion();

    // Quest Validation
    bool ValidateQuestPrerequisites(FQuestData& QuestData);
    bool ValidateQuestProgress(FQuestData& QuestData);

private:
    // Internal State
    float LastUpdateTime;
    bool bIsProcessingQuests;

    // Quest Tracking
    TMap<FString, int32> QuestProgress;
    TMap<FString, TArray<FString>> CompletedObjectives;

    // Helper Functions
    void LoadQuestDatabase();
    void SaveQuestProgress();
    void ProcessQuestEvent(FString EventType, TArray<FString> Parameters);
};
