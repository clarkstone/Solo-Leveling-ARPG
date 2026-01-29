#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P25_OMEGA_STATE_SYSTEM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOmegaStateActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOmegaStateDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnOmegaStateChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOmegaStateMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOmegaStatePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOmegaStatePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOmegaStateAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP25_OMEGA_STATE_SYSTEM : public UActorComponent
{
    GENERATED_BODY()

public:
    UP25_OMEGA_STATE_SYSTEM();

    // Omega State Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega State")
    int32 OmegaStateLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega State")
    int32 MaxOmegaStateLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega State")
    bool bIsOmegaStateActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega State")
    float OmegaStatePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega State")
    float OmegaStateThreshold;

    // Omega State Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega State")
    float OmegaPhaseUltimacy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega State")
    float FinalStateAuthority;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega State")
    float StateTransitions;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega State")
    float UltimateConsciousness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega State")
    float FinalUltimacy;

    // Omega State Events
    UPROPERTY(BlueprintAssignable, Category = "Omega State")
    FOnOmegaStateActivated OnOmegaStateActivated;

    UPROPERTY(BlueprintAssignable, Category = "Omega State")
    FOnOmegaStateDeactivated OnOmegaStateDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Omega State")
    FOnOmegaStateChanged OnOmegaStateChanged;

    UPROPERTY(BlueprintAssignable, Category = "Omega State")
    FOnOmegaStateChanged OnOmegaStateChanged;

    UPROPERTY(BlueprintAssignable, Category = "Omega State")
    FOnOmegaStateMaxLevelReached OnOmegaStateMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Omega State")
    FOnOmegaStatePowerUsed OnOmegaStatePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Omega State")
    FOnOmegaStatePowerFailed OnOmegaStatePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Omega State")
    FOnOmegaStateAbilityPerformed OnOmegaStateAbilityPerformed;

    // Omega State Functions
    UFUNCTION(BlueprintCallable, Category = "Omega State")
    void ActivateOmegaState();

    UFUNCTION(BlueprintCallable, Category = "Omega State")
    void DeactivateOmegaState();

    UFUNCTION(BlueprintCallable, Category = "Omega State")
    void SetOmegaStateLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Omega State")
    void UseOmegaStatePower();

    UFUNCTION(BlueprintCallable, Category = "Omega State")
    void PerformOmegaStateAbility();

    UFUNCTION(BlueprintCallable, Category = "Omega State")
    bool IsOmegaStateActive() const;

    UFUNCTION(BlueprintCallable, Category = "Omega State")
    int32 GetOmegaStateLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Omega State")
    float GetOmegaStatePowerCost() const;

    // Omega State Abilities
    UFUNCTION(BlueprintCallable, Category = "Omega State")
    void ExerciseOmegaPhaseUltimacy();

    UFUNCTION(BlueprintCallable, Category = "Omega State")
    void AchieveOmegaPhaseFinalUltimacy();

    UFUNCTION(BlueprintCallable, Category = "Omega State")
    void ControlFinalStateTransitions();

    UFUNCTION(BlueprintCallable, Category = "Omega State")
    void AccessUltimateConsciousness();

    UFUNCTION(BlueprintCallable, Category = "Omega State")
    void WieldFinalUltimacy();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateOmegaState() const;
    void UpdateOmegaStateStats();
    void OnOmegaStateChanged();
};
