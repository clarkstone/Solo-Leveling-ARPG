#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COMPLETE_LAMBDA_OMEGA_STATE_SYSTEM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLambdaOmegaStateActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLambdaOmegaStateDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnLambdaOmegaStateChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLambdaOmegaStateMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLambdaOmegaStatePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLambdaOmegaStatePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLambdaOmegaStateAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UCOMPLETE_LAMBDA_OMEGA_STATE_SYSTEM : public UActorComponent
{
    GENERATED_BODY()

public:
    UCOMPLETE_LAMBDA_OMEGA_STATE_SYSTEM();

    // Lambda-Omega State Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda-Omega State")
    int32 LambdaOmegaStateLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda-Omega State")
    int32 MaxLambdaOmegaStateLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda-Omega State")
    bool bIsLambdaOmegaStateActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda-Omega State")
    float LambdaOmegaStatePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda-Omega State")
    float LambdaOmegaStateThreshold;

    // Lambda-Omega State Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda-Omega State")
    float LambdaPhaseUltimateAbsoluteSupremeUltimacy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda-Omega State")
    float OmegaPhaseFinalUltimateAbsoluteFinality;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda-Omega State")
    float UltimateAbsoluteStateTransition;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda-Omega State")
    float PlanckQuantumStateSupremacy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lambda-Omega State")
    float FinalStateUltimateAbsoluteUltimacy;

    // Lambda-Omega State Events
    UPROPERTY(BlueprintAssignable, Category = "Lambda-Omega State")
    FOnLambdaOmegaStateActivated OnLambdaOmegaStateActivated;

    UPROPERTY(BlueprintAssignable, Category = "Lambda-Omega State")
    FOnLambdaOmegaStateDeactivated OnLambdaOmegaStateDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Lambda-Omega State")
    FOnLambdaOmegaStateChanged OnLambdaOmegaStateChanged;

    UPROPERTY(BlueprintAssignable, Category = "Lambda-Omega State")
    FOnLambdaOmegaStateMaxLevelReached OnLambdaOmegaStateMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Lambda-Omega State")
    FOnLambdaOmegaStatePowerUsed OnLambdaOmegaStatePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Lambda-Omega State")
    FOnLambdaOmegaStatePowerFailed OnLambdaOmegaStatePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Lambda-Omega State")
    FOnLambdaOmegaStateAbilityPerformed OnLambdaOmegaStateAbilityPerformed;

    // Lambda-Omega State Functions
    UFUNCTION(BlueprintCallable, Category = "Lambda-Omega State")
    void ActivateLambdaOmegaState();

    UFUNCTION(BlueprintCallable, Category = "Lambda-Omega State")
    void DeactivateLambdaOmegaState();

    UFUNCTION(BlueprintCallable, Category = "Lambda-Omega State")
    void SetLambdaOmegaStateLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Lambda-Omega State")
    void UseLambdaOmegaStatePower();

    UFUNCTION(BlueprintCallable, Category = "Lambda-Omega State")
    void PerformLambdaOmegaStateAbility();

    UFUNCTION(BlueprintCallable, Category = "Lambda-Omega State")
    bool IsLambdaOmegaStateActive() const;

    UFUNCTION(BlueprintCallable, Category = "Lambda-Omega State")
    int32 GetLambdaOmegaStateLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Lambda-Omega State")
    float GetLambdaOmegaStatePowerCost() const;

    // Lambda-Omega State Abilities
    UFUNCTION(BlueprintCallable, Category = "Lambda-Omega State")
    void ExerciseLambdaPhaseUltimateAbsoluteSupremeUltimacy();

    UFUNCTION(BlueprintCallable, Category = "Lambda-Omega State")
    void AchieveOmegaPhaseFinalUltimateAbsoluteFinality();

    UFUNCTION(BlueprintCallable, Category = "Lambda-Omega State")
    void ControlUltimateAbsoluteStateTransitions();

    UFUNCTION(BlueprintCallable, Category = "Lambda-Omega State")
    void DominatePlanckQuantumStates();

    UFUNCTION(BlueprintCallable, Category = "Lambda-Omega State")
    void WieldFinalStateUltimateAbsoluteUltimacy();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateLambdaOmegaState() const;
    void UpdateLambdaOmegaStateStats();
    void OnLambdaOmegaStateChanged();
};
