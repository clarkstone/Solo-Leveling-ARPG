#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P01_OMEGA_ULTIMATE.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltimateOmegaStateActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltimateOmegaStateDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnUltimateOmegaStateChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUltimateOmegaStateMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltimateOmegaStatePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUltimateOmegaStatePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltimateOmegaStateAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP01_OMEGA_ULTIMATE : public UActorComponent
{
    GENERATED_BODY()

public:
    UP01_OMEGA_ULTIMATE();

    // Ultimate Omega State Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Omega State")
    int32 UltimateOmegaStateLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Omega State")
    int32 MaxUltimateOmegaStateLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Omega State")
    bool bIsUltimateOmegaStateActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Omega State")
    float UltimateOmegaStatePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Omega State")
    float UltimateOmegaStateThreshold;

    // Ultimate Omega State Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Omega State")
    float OmegaPhaseUltimacy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Omega State")
    float FinalStateAuthority;

    UPROPERTY(EditAnywhere, BlueprintWriteOnly, Category = "Ultimate Omega State")
    float StateTransitions;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate State")
    float UltimateConsciousness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Omega State")
    float FinalUltimacy;

    // Ultimate Omega State Events
    UPROPERTY(BlueprintAssignable, Category = "Ultimate Omega State")
    FOnUltimateOmegaStateActivated OnUltimateOmegaStateActivated;

    UPROPERTY(BlueprintAssignable, Category = "Ultimate Omega State")
    FOnUltimateOmegaStateDeactivated OnUltimateOmegaStateDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Ultimate Omega State")
    FOnUltimateOmegaStateChanged OnUltimateOmegaStateChanged;

    UPROPERTY(BlueprintAssignable, Category = "Ultimate Omega State")
    FOnUltimateOmegaStateMaxLevelReached OnUltimateOmegaStateMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Ultimate Omega State")
    FOnUltimateOmegaStatePowerUsed OnUltimateOmegaStatePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Ultimate Omega State")
    FOnUltimateOmegaStatePowerFailed OnUltimateOmegaStatePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Ultimate Omega State")
    FOnUltimateOmegaStateAbilityPerformed OnUltimateOmegaStateAbilityPerformed;

    // Ultimate Omega State Functions
    UFUNCTION(BlueprintCallable, Category = "Ultimate Omega State")
    void ActivateUltimateOmegaState();

    UFUNCTION(BlueprintCallable, Category = "Ultimate Omega State")
    void DeactivateUltimateOmegaState();

    UFUNCTION(BlueprintCallable, Category = "Ultimate Omega State")
    void SetUltimateOmegaStateLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Ultimate Omega State")
    void UseUltimateOmegaStatePower();

    UFUNCTION(BlueprintCallable, Category = "Ultimate Omega State")
    void PerformUltimateOmegaStateAbility();

    UFUNCTION(BlueprintCallable, Category = "Ultimate Omega State")
    bool IsUltimateOmegaStateActive() const;

    UFUNCTION(BlueprintCallable, Category = "Ultimate Omega State")
    int32 GetUltimateOmegaStateLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Ultimate Omega State")
    float GetUltimateOmegaStatePowerCost() const;

    // Ultimate Omega State Abilities
    UFUNCTION(BlueprintCallable, Category = "Ultimate Omega State")
    void AchieveOmegaPhaseUltimacy();

    UFUNCTION(BlueprintCallable, Category = "Ultimate Omega State")
    void WieldFinalStateAuthority();

    UFUNCTION(BlueprintCallable, Category = "Ultimate Omega State")
    void ControlStateTransitions();

    UFUNCTION(BlueprintCallable, Category = "Ultimate Omega State")
    void AccessUltimateConsciousness();

    UFUNCTION(BlueprintCallable, Category = "Ultimate Omega State")
    void WieldFinalUltimacy();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateUltimateOmegaState() const;
    void UpdateUltimateOmegaStateStats();
    void OnUltimateOmegaStateChanged();
};
