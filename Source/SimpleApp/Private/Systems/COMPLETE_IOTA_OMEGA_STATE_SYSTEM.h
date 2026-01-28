#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COMPLETE_IOTA_OMEGA_STATE_SYSTEM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIotaOmegaStateActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIotaOmegaStateDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnIotaOmegaStateChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnIotaOmegaStateMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIotaOmegaStatePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnIotaOmegaStatePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIotaOmegaStateAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UCOMPLETE_IOTA_OMEGA_STATE_SYSTEM : public UActorComponent
{
    GENERATED_BODY()

public:
    UCOMPLETE_IOTA_OMEGA_STATE_SYSTEM();

    // Iota-Omega State Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Iota-Omega State")
    int32 IotaOmegaStateLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Iota-Omega State")
    int32 MaxIotaOmegaStateLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Iota-Omega State")
    bool bIsIotaOmegaStateActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Iota-Omega State")
    float IotaOmegaStatePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Iota-Omega State")
    float IotaOmegaStateThreshold;

    // Iota-Omega State Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Iota-Omega State")
    float IotaPhaseSupremeUltimacy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Iota-Omega State")
    float OmegaPhaseAbsoluteFinality;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Iota-Omega State")
    float SupremeStateTransition;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Iota-Omega State")
    float QuantumSubatomicStateSupremacy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Iota-Omega State")
    float FinalStateAbsoluteUltimacy;

    // Iota-Omega State Events
    UPROPERTY(BlueprintAssignable, Category = "Iota-Omega State")
    FOnIotaOmegaStateActivated OnIotaOmegaStateActivated;

    UPROPERTY(BlueprintAssignable, Category = "Iota-Omega State")
    FOnIotaOmegaStateDeactivated OnIotaOmegaStateDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Iota-Omega State")
    FOnIotaOmegaStateChanged OnIotaOmegaStateChanged;

    UPROPERTY(BlueprintAssignable, Category = "Iota-Omega State")
    FOnIotaOmegaStateMaxLevelReached OnIotaOmegaStateMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Iota-Omega State")
    FOnIotaOmegaStatePowerUsed OnIotaOmegaStatePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Iota-Omega State")
    FOnIotaOmegaStatePowerFailed OnIotaOmegaStatePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Iota-Omega State")
    FOnIotaOmegaStateAbilityPerformed OnIotaOmegaStateAbilityPerformed;

    // Iota-Omega State Functions
    UFUNCTION(BlueprintCallable, Category = "Iota-Omega State")
    void ActivateIotaOmegaState();

    UFUNCTION(BlueprintCallable, Category = "Iota-Omega State")
    void DeactivateIotaOmegaState();

    UFUNCTION(BlueprintCallable, Category = "Iota-Omega State")
    void SetIotaOmegaStateLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Iota-Omega State")
    void UseIotaOmegaStatePower();

    UFUNCTION(BlueprintCallable, Category = "Iota-Omega State")
    void PerformIotaOmegaStateAbility();

    UFUNCTION(BlueprintCallable, Category = "Iota-Omega State")
    bool IsIotaOmegaStateActive() const;

    UFUNCTION(BlueprintCallable, Category = "Iota-Omega State")
    int32 GetIotaOmegaStateLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Iota-Omega State")
    float GetIotaOmegaStatePowerCost() const;

    // Iota-Omega State Abilities
    UFUNCTION(BlueprintCallable, Category = "Iota-Omega State")
    void ExerciseIotaPhaseSupremeUltimacy();

    UFUNCTION(BlueprintCallable, Category = "Iota-Omega State")
    void AchieveOmegaPhaseAbsoluteFinality();

    UFUNCTION(BlueprintCallable, Category = "Iota-Omega State")
    void ControlSupremeStateTransitions();

    UFUNCTION(BlueprintCallable, Category = "Iota-Omega State")
    void DominateQuantumSubatomicStates();

    UFUNCTION(BlueprintCallable, Category = "Iota-Omega State")
    void WieldFinalStateAbsoluteUltimacy;

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateIotaOmegaState() const;
    void UpdateIotaOmegaStateStats();
    void OnIotaOmegaStateChanged();
};
