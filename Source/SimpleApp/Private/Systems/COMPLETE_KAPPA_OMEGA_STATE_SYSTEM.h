#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COMPLETE_KAPPA_OMEGA_STATE_SYSTEM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnKappaOmegaStateActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnKappaOmegaStateDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnKappaOmegaStateChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnKappaOmegaStateMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnKappaOmegaStatePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnKappaOmegaStatePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnKappaOmegaStateAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UCOMPLETE_KAPPA_OMEGA_STATE_SYSTEM : public UActorComponent
{
    GENERATED_BODY()

public:
    UCOMPLETE_KAPPA_OMEGA_STATE_SYSTEM();

    // Kappa-Omega State Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Kappa-Omega State")
    int32 KappaOmegaStateLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Kappa-Omega State")
    int32 MaxKappaOmegaStateLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Kappa-Omega State")
    bool bIsKappaOmegaStateActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Kappa-Omega State")
    float KappaOmegaStatePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Kappa-Omega State")
    float KappaOmegaStateThreshold;

    // Kappa-Omega State Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Kappa-Omega State")
    float KappaPhaseAbsoluteSupremeUltimacy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Kappa-Omega State")
    float OmegaPhaseFinalAbsoluteFinality;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Kappa-Omega State")
    float AbsoluteStateTransition;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Kappa-Omega State")
    float SubatomicQuantumStateSupremacy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Kappa-Omega State")
    float FinalStateAbsoluteUltimacy;

    // Kappa-Omega State Events
    UPROPERTY(BlueprintAssignable, Category = "Kappa-Omega State")
    FOnKappaOmegaStateActivated OnKappaOmegaStateActivated;

    UPROPERTY(BlueprintAssignable, Category = "Kappa-Omega State")
    FOnKappaOmegaStateDeactivated OnKappaOmegaStateDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Kappa-Omega State")
    FOnKappaOmegaStateChanged OnKappaOmegaStateChanged;

    UPROPERTY(BlueprintAssignable, Category = "Kappa-Omega State")
    FOnKappaOmegaStateMaxLevelReached OnKappaOmegaStateMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Kappa-Omega State")
    FOnKappaOmegaStatePowerUsed OnKappaOmegaStatePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Kappa-Omega State")
    FOnKappaOmegaStatePowerFailed OnKappaOmegaStatePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Kappa-Omega State")
    FOnKappaOmegaStateAbilityPerformed OnKappaOmegaStateAbilityPerformed;

    // Kappa-Omega State Functions
    UFUNCTION(BlueprintCallable, Category = "Kappa-Omega State")
    void ActivateKappaOmegaState();

    UFUNCTION(BlueprintCallable, Category = "Kappa-Omega State")
    void DeactivateKappaOmegaState();

    UFUNCTION(BlueprintCallable, Category = "Kappa-Omega State")
    void SetKappaOmegaStateLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Kappa-Omega State")
    void UseKappaOmegaStatePower();

    UFUNCTION(BlueprintCallable, Category = "Kappa-Omega State")
    void PerformKappaOmegaStateAbility();

    UFUNCTION(BlueprintCallable, Category = "Kappa-Omega State")
    bool IsKappaOmegaStateActive() const;

    UFUNCTION(BlueprintCallable, Category = "Kappa-Omega State")
    int32 GetKappaOmegaStateLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Kappa-Omega State")
    float GetKappaOmegaStatePowerCost() const;

    // Kappa-Omega State Abilities
    UFUNCTION(BlueprintCallable, Category = "Kappa-Omega State")
    void ExerciseKappaPhaseAbsoluteSupremeUltimacy();

    UFUNCTION(BlueprintCallable, Category = "Kappa-Omega State")
    void AchieveOmegaPhaseFinalAbsoluteFinality();

    UFUNCTION(BlueprintCallable, Category = "Kappa-Omega State")
    void ControlAbsoluteStateTransitions();

    UFUNCTION(BlueprintCallable, Category = "Kappa-Omega State")
    void DominateSubatomicQuantumStates();

    UFUNCTION(BlueprintCallable, Category = "Kappa-Omega State")
    void WieldFinalStateAbsoluteUltimacy();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateKappaOmegaState() const;
    void UpdateKappaOmegaStateStats();
    void OnKappaOmegaStateChanged();
};
