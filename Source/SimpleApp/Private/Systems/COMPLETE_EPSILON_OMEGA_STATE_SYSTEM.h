#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COMPLETE_EPSILON_OMEGA_STATE_SYSTEM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEpsilonOmegaStateActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEpsilonOmegaStateDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnEpsilonOmegaStateChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEpsilonOmegaStateMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEpsilonOmegaStatePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEpsilonOmegaStatePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEpsilonOmegaStateAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UCOMPLETE_EPSILON_OMEGA_STATE_SYSTEM : public UActorComponent
{
    GENERATED_BODY()

public:
    UCOMPLETE_EPSILON_OMEGA_STATE_SYSTEM();

    // Epsilon-Omega State Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Epsilon-Omega State")
    int32 EpsilonOmegaStateLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Epsilon-Omega State")
    int32 MaxEpsilonOmegaStateLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Epsilon-Omega State")
    bool bIsEpsilonOmegaStateActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Epsilon-Omega State")
    float EpsilonOmegaStatePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Epsilon-Omega State")
    float EpsilonOmegaStateThreshold;

    // Epsilon-Omega State Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Epsilon-Omega State")
    float EpsilonPhaseMastery;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Epsilon-Omega State")
    float OmegaPhaseDominance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Epsilon-Omega State")
    float StateTransitionControl;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Epsilon-Omega State")
    float QuantumStateManipulation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Epsilon-Omega State")
    float UltimateStateAuthority;

    // Epsilon-Omega State Events
    UPROPERTY(BlueprintAssignable, Category = "Epsilon-Omega State")
    FOnEpsilonOmegaStateActivated OnEpsilonOmegaStateActivated;

    UPROPERTY(BlueprintAssignable, Category = "Epsilon-Omega State")
    FOnEpsilonOmegaStateDeactivated OnEpsilonOmegaStateDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Epsilon-Omega State")
    FOnEpsilonOmegaStateChanged OnEpsilonOmegaStateChanged;

    UPROPERTY(BlueprintAssignable, Category = "Epsilon-Omega State")
    FOnEpsilonOmegaStateMaxLevelReached OnEpsilonOmegaStateMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Epsilon-Omega State")
    FOnEpsilonOmegaStatePowerUsed OnEpsilonOmegaStatePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Epsilon-Omega State")
    FOnEpsilonOmegaStatePowerFailed OnEpsilonOmegaStatePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Epsilon-Omega State")
    FOnEpsilonOmegaStateAbilityPerformed OnEpsilonOmegaStateAbilityPerformed;

    // Epsilon-Omega State Functions
    UFUNCTION(BlueprintCallable, Category = "Epsilon-Omega State")
    void ActivateEpsilonOmegaState();

    UFUNCTION(BlueprintCallable, Category = "Epsilon-Omega State")
    void DeactivateEpsilonOmegaState();

    UFUNCTION(BlueprintCallable, Category = "Epsilon-Omega State")
    void SetEpsilonOmegaStateLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Epsilon-Omega State")
    void UseEpsilonOmegaStatePower();

    UFUNCTION(BlueprintCallable, Category = "Epsilon-Omega State")
    void PerformEpsilonOmegaStateAbility();

    UFUNCTION(BlueprintCallable, Category = "Epsilon-Omega State")
    bool IsEpsilonOmegaStateActive() const;

    UFUNCTION(BlueprintCallable, Category = "Epsilon-Omega State")
    int32 GetEpsilonOmegaStateLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Epsilon-Omega State")
    float GetEpsilonOmegaStatePowerCost() const;

    // Epsilon-Omega State Abilities
    UFUNCTION(BlueprintCallable, Category = "Epsilon-Omega State")
    void MasterEpsilonPhase();

    UFUNCTION(BlueprintCallable, Category = "Epsilon-Omega State")
    void DominateOmegaPhase();

    UFUNCTION(BlueprintCallable, Category = "Epsilon-Omega State")
    void ControlStateTransitions();

    UFUNCTION(BlueprintCallable, Category = "Epsilon-Omega State")
    void ManipulateQuantumStates();

    UFUNCTION(BlueprintCallable, Category = "Epsilon-Omega State")
    void ExerciseUltimateStateAuthority();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateEpsilonOmegaState() const;
    void UpdateEpsilonOmegaStateStats();
    void OnEpsilonOmegaStateChanged();
};
