#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COMPLETE_MU_OMEGA_STATE_SYSTEM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMuOmegaStateActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMuOmegaStateDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnMuOmegaStateChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMuOmegaStateMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMuOmegaStatePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMuOmegaStatePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMuOmegaStateAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UCOMPLETE_MU_OMEGA_STATE_SYSTEM : public UActorComponent
{
    GENERATED_BODY()

public:
    UCOMPLETE_MU_OMEGA_STATE_SYSTEM();

    // Mu-Omega State Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mu-Omega State")
    int32 MuOmegaStateLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mu-Omega State")
    int32 MaxMuOmegaStateLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mu-Omega State")
    bool bIsMuOmegaStateActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mu-Omega State")
    float MuOmegaStatePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mu-Omega State")
    float MuOmegaStateThreshold;

    // Mu-Omega State Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mu-Omega State")
    float MuPhaseFinalUltimateAbsoluteSupremeUltimacy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mu-Omega State")
    float OmegaPhaseFinalUltimateAbsoluteFinality;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mu-Omega State")
    float FinalStateTransitions;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mu-Omega State")
    float PlanckQuantumStateSupremacy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mu-Omega State")
    float FinalStateUltimateAbsoluteUltimacy;

    // Mu-Omega State Events
    UPROPERTY(BlueprintAssignable, Category = "Mu-Omega State")
    FOnMuOmegaStateActivated OnMuOmegaStateActivated;

    UPROPERTY(BlueprintAssignable, Category = "Mu-Omega State")
    FOnMuOmegaStateDeactivated OnMuOmegaStateDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Mu-Omega State")
    FOnMuOmegaStateChanged OnMuOmegaStateChanged;

    UPROPERTY(BlueprintAssignable, Category = "Mu-Omega State")
    FOnMuOmegaStateMaxLevelReached OnMuOmegaStateMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Mu-Omega State")
    FOnMuOmegaStatePowerUsed OnMuOmegaStatePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Mu-Omega State")
    FOnMuOmegaStatePowerFailed OnMuOmegaStatePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Mu-Omega State")
    FOnMuOmegaStateAbilityPerformed OnMuOmegaStateAbilityPerformed;

    // Mu-Omega State Functions
    UFUNCTION(BlueprintCallable, Category = "Mu-Omega State")
    void ActivateMuOmegaState();

    UFUNCTION(BlueprintCallable, Category = "Mu-Omega State")
    void DeactivateMuOmegaState();

    UFUNCTION(BlueprintCallable, Category = "Mu-Omega State")
    void SetMuOmegaStateLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Mu-Omega State")
    void UseMuOmegaStatePower();

    UFUNCTION(BlueprintCallable, Category = "Mu-Omega State")
    void PerformMuOmegaStateAbility();

    UFUNCTION(BlueprintCallable, Category = "Mu-Omega State")
    bool IsMuOmegaStateActive() const;

    UFUNCTION(BlueprintCallable, Category = "Mu-Omega State")
    int32 GetMuOmegaStateLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Mu-Omega State")
    float GetMuOmegaStatePowerCost() const;

    // Mu-Omega State Abilities
    UFUNCTION(BlueprintCallable, Category = "Mu-Omega State")
    void ExerciseMuPhaseFinalUltimateAbsoluteSupremeUltimacy();

    UFUNCTION(BlueprintCallable, Category = "Mu-Omega State")
    void AchieveOmegaPhaseFinalUltimateAbsoluteFinality();

    UFUNCTION(BlueprintCallable, Category = "Mu-Omega State")
    void ControlFinalStateTransitions();

    UFUNCTION(BlueprintCallable, Category = "Mu-Omega State")
    void DominatePlanckQuantumStates();

    UFUNCTION(BlueprintCallable, Category = "Mu-Omega State")
    void WieldFinalStateUltimateAbsoluteUltimacy();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateMuOmegaState() const;
    void UpdateMuOmegaStateStats();
    void OnMuOmegaStateChanged();
};
