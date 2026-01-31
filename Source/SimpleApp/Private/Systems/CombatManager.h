#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "CombatManager.generated.h"

UENUM(BlueprintType)
enum class ECombatState : uint8
{
    CS_Idle,
    CS_Engaged,
    CS_Cooldown,
    CS_Victory,
    CS_Defeat
};

USTRUCT(BlueprintType)
struct FCombatData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector ImpactLocation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Damage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsCritical;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsPerfectTiming;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName AttackType;
};

USTRUCT(BlueprintType)
struct FComboData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> ComboSequence;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DamageMultiplier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float TimingWindow;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bRequiresSpecificWeapon;
};

UCLASS()
class SIMPLEAPP_API UCombatManager : public UActorComponent
{
    GENERATED_BODY()

public:
    UCombatManager();

    // Combat State
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
    ECombatState CurrentState;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
    bool bIsInCombat;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
    int32 ActiveEnemyCount;

    // Combat Configuration
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float CombatEngagementRange;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float CombatCooldownTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    float PerfectTimingWindow;

    // Combo System
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
    TArray<FName> CurrentCombo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
    TArray<FComboData> AvailableCombos;

    // Power System Integration
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
    TArray<class UPowerSystemComponent*> ActivePowerSystems;

    // Override UActorComponent functions
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Initialization
    UFUNCTION(BlueprintCallable, Category = "Combat")
    void Initialize();

    // Combat Management
    UFUNCTION(BlueprintCallable, Category = "Combat")
    void StartCombat();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void EndCombat();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void UpdateCombatState(float DeltaTime);

    // Attack System
    UFUNCTION(BlueprintCallable, Category = "Combat")
    void ProcessAttack(FCombatData CombatData);

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void ProcessPerfectTiming(FName ActionName);

    UFUNCTION(BlueprintCallable, Category = "Combat")
    bool CheckPerfectTiming(FName ActionName);

    // Combo System
    UFUNCTION(BlueprintCallable, Category = "Combat")
    void AddComboMove(FName MoveName);

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void ExecuteCombo();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void ResetCombo();

    // Power System Integration
    UFUNCTION(BlueprintCallable, Category = "Combat")
    void UpdatePowerSystemStates(TArray<UPowerSystemComponent*> Systems);

    UFUNCTION(BlueprintCallable, Category = "Combat")
    void UsePowerSystemAbility(FName AbilityName);

    // Combat Analysis
    UFUNCTION(BlueprintCallable, Category = "Combat")
    void AnalyzeCombatSituation();

    UFUNCTION(BlueprintCallable, Category = "Combat")
    FCombatSituation GetCombatSituation();

    // Events
    UPROPERTY(BlueprintAssignable, Category = "Combat Events")
    FOnCombatStarted OnCombatStarted;

    UPROPERTY(BlueprintAssignable, Category = "Combat Events")
    FOnCombatEnded OnCombatEnded;

    UPROPERTY(BlueprintAssignable, Category = "Combat Events")
    FOnAttackExecuted OnAttackExecuted;

    UPROPERTY(BlueprintAssignable, Category = "Combat Events")
    FOnComboExecuted OnComboExecuted;

    UPROPERTY(BlueprintAssignable, Category = "Combat Events")
    FOnPerfectTimingExecuted OnPerfectTimingExecuted;

protected:
    // Internal Combat Systems
    void UpdateCombatFlow();
    void ProcessCombatResults();
    void UpdateCombatStatistics();

    // Combo Management
    void ValidateCombo();
    void CalculateComboDamage();

    // Power System Integration
    void SyncPowerSystemsWithCombat();
    void CalculatePowerSystemSynergy();

private:
    // Internal State
    float LastAttackTime;
    float ComboTimer;
    float CombatTimer;
    bool bCanAttack;
    bool bIsInCombo;

    // Combat Statistics
    int32 TotalAttacks;
    int32 PerfectTimings;
    int32 CombosExecuted;
    float TotalDamageDealt;

    // Helper Functions
    void InitializeComboSystem();
    void UpdateCombatMetrics();
    void ProcessCombatFlow();
};
