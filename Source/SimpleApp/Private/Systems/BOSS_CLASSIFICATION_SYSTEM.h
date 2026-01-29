#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "BOSS_CLASSIFICATION_SYSTEM.generated.h"

// Boss Types Enum
UENUM(BlueprintType)
enum class EBossType : uint8
{
    BT_SubBoss        = 0,    // Mid-quest mini-bosses
    BT_AreaBoss       = 1,    // Region/dungeon finales
    BT_UniqueBoss     = 2     // Seven Colossi - one-time world bosses
};

// Spawn Condition Types
UENUM(BlueprintType)
enum class ESpawnCondition : uint8
{
    SC_Static          = 0,    // Fixed location
    SC_Triggered       = 1,    // Player action/quest required
    SC_Hidden          = 2,    // Secret area discovery
    SC_UniqueScenario  = 3,    // Complex unknown conditions
    SC_Random          = 4,    // Anywhere, anytime (Colossi)
    SC_Temporal        = 5     // Time/environment triggered
};

// Boss Phase States
UENUM(BlueprintType)
enum class EBossPhase : uint8
{
    BP_Phase1          = 0,    // Initial phase
    BP_Phase2          = 1,    // Second phase
    BP_Phase3          = 2,    // Third phase
    BP_EnragePhase     = 3,    // Berserk phase
    BP_FinalPhase      = 4     // Final desperation phase
};

// Boss Difficulty Scaling
USTRUCT(BlueprintType)
struct FBossDifficultyScaling
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BaseHP = 10000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BaseAttackPower = 500.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float LevelCap = 50.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float PartySizeMultiplier = 1.2f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float PlayerLevelScaling = 1.1f;
};

// Boss Loot Rewards
USTRUCT(BlueprintType)
struct FBossLootRewards
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 ExperienceReward = 10000;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 GoldReward = 5000;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> UniqueItems;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> RareMaterials;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> LegendaryItems;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName SpecialKeyItem;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool GrantsNewSkill = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName GrantedSkill;
};

// Boss Data Structure
USTRUCT(BlueprintType)
struct FBossData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName BossID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString BossName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EBossType BossType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ESpawnCondition SpawnCondition;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString LoreDescription;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> Weaknesses;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> Immunities;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FBossDifficultyScaling DifficultyScaling;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FBossLootRewards LootRewards;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool IsWorldChanging = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool HasBeenDefeated = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool RespawnEnabled = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float RespawnTimeHours = 24.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector SpawnLocation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FRotator SpawnRotation;
};

// Boss Encounter Events
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBossEncountered, const FBossData&, BossData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBossPhaseChanged, EBossPhase, NewPhase);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBossDefeated, const FBossData&, BossData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnBossLootDropped, const FBossLootRewards&, LootRewards, const FString&, DefeatMethod);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UBOSS_CLASSIFICATION_SYSTEM : public UActorComponent
{
    GENERATED_BODY()

public:
    UBOSS_CLASSIFICATION_SYSTEM();

    // Boss Management Functions
    UFUNCTION(BlueprintCallable, Category = "Boss Classification")
    bool SpawnBoss(FName BossID, FVector SpawnLocation, FRotator SpawnRotation);

    UFUNCTION(BlueprintCallable, Category = "Boss Classification")
    bool CheckSpawnConditions(FName BossID, AActor* TriggeringActor);

    UFUNCTION(BlueprintCallable, Category = "Boss Classification")
    void StartBossEncounter(FName BossID);

    UFUNCTION(BlueprintCallable, Category = "Boss Classification")
    void AdvanceBossPhase();

    UFUNCTION(BlueprintCallable, Category = "Boss Classification")
    void HandleBossDefeated(const FString& DefeatMethod);

    UFUNCTION(BlueprintCallable, Category = "Boss Classification")
    void ScaleBossDifficulty(FName BossID, int32 PlayerCount, int32 AveragePlayerLevel);

    UFUNCTION(BlueprintCallable, Category = "Boss Classification")
    FBossData GetBossData(FName BossID);

    UFUNCTION(BlueprintCallable, Category = "Boss Classification")
    bool IsBossDefeated(FName BossID);

    UFUNCTION(BlueprintCallable, Category = "Boss Classification")
    TArray<FBossData> GetAvailableBosses();

    UFUNCTION(BlueprintCallable, Category = "Boss Classification")
    TArray<FBossData> GetUniqueBosses();

    UFUNCTION(BlueprintCallable, Category = "Boss Classification")
    bool CanRespawnBoss(FName BossID);

    // Boss Classification Functions
    UFUNCTION(BlueprintCallable, Category = "Boss Classification")
    bool IsSubBoss(FName BossID);

    UFUNCTION(BlueprintCallable, Category = "Boss Classification")
    bool IsAreaBoss(FName BossID);

    UFUNCTION(BlueprintCallable, Category = "Boss Classification")
    bool IsUniqueBoss(FName BossID);

    // Spawn Condition Functions
    UFUNCTION(BlueprintCallable, Category = "Boss Classification")
    bool CheckStaticSpawn(FName BossID);

    UFUNCTION(BlueprintCallable, Category = "Boss Classification")
    bool CheckTriggeredSpawn(FName BossID, AActor* TriggeringActor);

    UFUNCTION(BlueprintCallable, Category = "Boss Classification")
    bool CheckHiddenSpawn(FName BossID, AActor* DiscoveringActor);

    UFUNCTION(BlueprintCallable, Category = "Boss Classification")
    bool CheckUniqueScenario(FName BossID, AActor* TriggeringActor);

    UFUNCTION(BlueprintCallable, Category = "Boss Classification")
    bool CheckRandomSpawn(FName BossID);

    UFUNCTION(BlueprintCallable, Category = "Boss Classification")
    bool CheckTemporalSpawn(FName BossID);

    // Loot Distribution Functions
    UFUNCTION(BlueprintCallable, Category = "Boss Classification")
    FBossLootRewards CalculateLoot(FName BossID, const FString& DefeatMethod);

    UFUNCTION(BlueprintCallable, Category = "Boss Classification")
    void DistributeLoot(const FBossLootRewards& LootRewards, AActor* DefeatingActor);

    UFUNCTION(BlueprintCallable, Category = "Boss Classification")
    bool IsLootMethodValid(const FString& DefeatMethod, FName BossID);

    // World State Functions
    UFUNCTION(BlueprintCallable, Category = "Boss Classification")
    void ApplyWorldChanges(const FBossData& BossData);

    UFUNCTION(BlueprintCallable, Category = "Boss Classification")
    void UnlockNewAreas(const FBossData& BossData);

    UFUNCTION(BlueprintCallable, Category = "Boss Classification")
    void TriggerStoryProgression(const FBossData& BossData);

    // Boss Events
    UPROPERTY(BlueprintAssignable, Category = "Boss Classification")
    FOnBossEncountered OnBossEncountered;

    UPROPERTY(BlueprintAssignable, Category = "Boss Classification")
    FOnBossPhaseChanged OnBossPhaseChanged;

    UPROPERTY(BlueprintAssignable, Category = "Boss Classification")
    FOnBossDefeated OnBossDefeated;

    UPROPERTY(BlueprintAssignable, Category = "Boss Classification")
    FOnBossLootDropped OnBossLootDropped;

    // Boss Database
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss Classification")
    UDataTable* BossDatabase;

    // Active Boss Tracking
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Boss Classification")
    TMap<FName, FBossData> ActiveBosses;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Boss Classification")
    TMap<FName, EBossPhase> CurrentBossPhases;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Boss Classification")
    TSet<FName> DefeatedUniqueBosses;

protected:
    virtual void BeginPlay() override;

private:
    void LoadBossDatabase();
    void SaveBossState();
    FBossData* FindBossData(FName BossID);
    bool ValidateBossDefeatMethod(const FString& Method, const FBossData& BossData);
    void ProcessUniqueBossDefeat(FName BossID);
    void HandleColossusDefeat(FName BossID);
};
