#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COMPLETE_ZETA_OMEGA_STATE_SYSTEM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnZetaOmegaStateActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnZetaOmegaStateDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnZetaOmegaStateChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnZetaOmegaStateMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnZetaOmegaStatePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnZetaOmegaStatePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnZetaOmegaStateAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UCOMPLETE_ZETA_OMEGA_STATE_SYSTEM : public UActorComponent
{
    GENERATED_BODY()

public:
    UCOMPLETE_ZETA_OMEGA_STATE_SYSTEM();

    // Zeta-Omega State Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zeta-Omega State")
    int32 ZetaOmegaStateLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zeta-Omega State")
    int32 MaxZetaOmegaStateLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zeta-Omega State")
    bool bIsZetaOmegaStateActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zeta-Omega State")
    float ZetaOmegaStatePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zeta-Omega State")
    float ZetaOmegaStateThreshold;

    // Zeta-Omega State Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zeta-Omega State")
    float ZetaPhaseSupremacy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zeta-Omega State")
    float OmegaPhaseUltimacy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zeta-Omega State")
    float MetaStateTransition;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zeta-Omega State")
    float QuantumStateSupremacy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Zeta-Omega State")
    float FinalStateAuthority;

    // Zeta-Omega State Events
    UPROPERTY(BlueprintAssignable, Category = "Zeta-Omega State")
    FOnZetaOmegaStateActivated OnZetaOmegaStateActivated;

    UPROPERTY(BlueprintAssignable, Category = "Zeta-Omega State")
    FOnZetaOmegaStateDeactivated OnZetaOmegaStateDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Zeta-Omega State")
    FOnZetaOmegaStateChanged OnZetaOmegaStateChanged;

    UPROPERTY(BlueprintAssignable, Category = "Zeta-Omega State")
    FOnZetaOmegaStateMaxLevelReached OnZetaOmegaStateMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Zeta-Omega State")
    FOnZetaOmegaStatePowerUsed OnZetaOmegaStatePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Zeta-Omega State")
    FOnZetaOmegaStatePowerFailed OnZetaOmegaStatePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Zeta-Omega State")
    FOnZetaOmegaStateAbilityPerformed OnZetaOmegaStateAbilityPerformed;

    // Zeta-Omega State Functions
    UFUNCTION(BlueprintCallable, Category = "Zeta-Omega State")
    void ActivateZetaOmegaState();

    UFUNCTION(BlueprintCallable, Category = "Zeta-Omega State")
    void DeactivateZetaOmegaState();

    UFUNCTION(BlueprintCallable, Category = "Zeta-Omega State")
    void SetZetaOmegaStateLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Zeta-Omega State")
    void UseZetaOmegaStatePower();

    UFUNCTION(BlueprintCallable, Category = "Zeta-Omega State")
    void PerformZetaOmegaStateAbility();

    UFUNCTION(BlueprintCallable, Category = "Zeta-Omega State")
    bool IsZetaOmegaStateActive() const;

    UFUNCTION(BlueprintCallable, Category = "Zeta-Omega State")
    int32 GetZetaOmegaStateLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Zeta-Omega State")
    float GetZetaOmegaStatePowerCost() const;

    // Zeta-Omega State Abilities
    UFUNCTION(BlueprintCallable, Category = "Zeta-Omega State")
    void ExerciseZetaPhaseSupremacy();

    UFUNCTION(BlueprintCallable, Category = "Zeta-Omega State")
    void AchieveOmegaPhaseUltimacy();

    UFUNCTION(BlueprintCallable, Category = "Zeta-Omega State")
    void ControlMetaStateTransitions();

    UFUNCTION(BlueprintCallable, Category = "Zeta-Omega State")
    void DominateQuantumStates();

    UFUNCTION(BlueprintCallable, Category = "Zeta-Omega State")
    void WieldFinalStateAuthority();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateZetaOmegaState() const;
    void UpdateZetaOmegaStateStats();
    void OnZetaOmegaStateChanged();
};
