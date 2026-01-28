#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COMPLETE_THETA_OMEGA_STATE_SYSTEM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnThetaOmegaStateActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnThetaOmegaStateDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnThetaOmegaStateChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnThetaOmegaStateMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnThetaOmegaStatePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnThetaOmegaStatePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnThetaOmegaStateAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UCOMPLETE_THETA_OMEGA_STATE_SYSTEM : public UActorComponent
{
    GENERATED_BODY()

public:
    UCOMPLETE_THETA_OMEGA_STATE_SYSTEM();

    // Theta-Omega State Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Theta-Omega State")
    int32 ThetaOmegaStateLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Theta-Omega State")
    int32 MaxThetaOmegaStateLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Theta-Omega State")
    bool bIsThetaOmegaStateActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Theta-Omega State")
    float ThetaOmegaStatePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Theta-Omega State")
    float ThetaOmegaStateThreshold;

    // Theta-Omega State Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Theta-Omega State")
    float ThetaPhaseUltimacy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Theta-Omega State")
    float OmegaPhaseFinality;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Theta-Omega State")
    float UltraStateTransition;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Theta-Omega State")
    float SubatomicStateSupremacy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Theta-Omega State")
    float FinalStateUltimacy;

    // Theta-Omega State Events
    UPROPERTY(BlueprintAssignable, Category = "Theta-Omega State")
    FOnThetaOmegaStateActivated OnThetaOmegaStateActivated;

    UPROPERTY(BlueprintAssignable, Category = "Theta-Omega State")
    FOnThetaOmegaStateDeactivated OnThetaOmegaStateDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Theta-Omega State")
    FOnThetaOmegaStateChanged OnThetaOmegaStateChanged;

    UPROPERTY(BlueprintAssignable, Category = "Theta-Omega State")
    FOnThetaOmegaStateMaxLevelReached OnThetaOmegaStateMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Theta-Omega State")
    FOnThetaOmegaStatePowerUsed OnThetaOmegaStatePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Theta-Omega State")
    FOnThetaOmegaStatePowerFailed OnThetaOmegaStatePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Theta-Omega State")
    FOnThetaOmegaStateAbilityPerformed OnThetaOmegaStateAbilityPerformed;

    // Theta-Omega State Functions
    UFUNCTION(BlueprintCallable, Category = "Theta-Omega State")
    void ActivateThetaOmegaState();

    UFUNCTION(BlueprintCallable, Category = "Theta-Omega State")
    void DeactivateThetaOmegaState();

    UFUNCTION(BlueprintCallable, Category = "Theta-Omega State")
    void SetThetaOmegaStateLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Theta-Omega State")
    void UseThetaOmegaStatePower();

    UFUNCTION(BlueprintCallable, Category = "Theta-Omega State")
    void PerformThetaOmegaStateAbility();

    UFUNCTION(BlueprintCallable, Category = "Theta-Omega State")
    bool IsThetaOmegaStateActive() const;

    UFUNCTION(BlueprintCallable, Category = "Theta-Omega State")
    int32 GetThetaOmegaStateLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Theta-Omega State")
    float GetThetaOmegaStatePowerCost() const;

    // Theta-Omega State Abilities
    UFUNCTION(BlueprintCallable, Category = "Theta-Omega State")
    void ExerciseThetaPhaseUltimacy();

    UFUNCTION(BlueprintCallable, Category = "Theta-Omega State")
    void AchieveOmegaPhaseFinality();

    UFUNCTION(BlueprintCallable, Category = "Theta-Omega State")
    void ControlUltraStateTransitions();

    UFUNCTION(BlueprintCallable, Category = "Theta-Omega State")
    void DominateSubatomicStates();

    UFUNCTION(BlueprintCallable, Category = "Theta-Omega State")
    void WieldFinalStateUltimacy;

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateThetaOmegaState() const;
    void UpdateThetaOmegaStateStats();
    void OnThetaOmegaStateChanged();
};
