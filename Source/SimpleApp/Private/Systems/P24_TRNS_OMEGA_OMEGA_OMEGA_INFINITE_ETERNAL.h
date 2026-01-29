#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P24_TRNS_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOmegaOmegaInfiniteEternalTranscendenceActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOmegaOmegaInfiniteEternalTranscendenceDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnOmegaOmegaInfiniteEternalTranscendenceLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOmegaOmegaInfiniteEternalTranscendenceMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOmegaOmegaInfiniteEternalTranscendencePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOmegaOmegaInfiniteEternalTranscendencePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOmegaOmegaInfiniteEternalTranscendenceAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP24_TRNS_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL : public UActorComponent
{
    GENERATED_BODY()

public:
    UP24_TRNS_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL();

    // Omega Omega Infinite Eternal Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Omega Infinite Eternal Transcendence")
    int32 OmegaOmegaInfiniteEternalTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Omega Infinite Eternal Transcendence")
    int32 MaxOmegaOmegaInfiniteEternalTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Omega Infinite Eternal Transcendence")
    bool bIsOmegaOmegaInfiniteEternalTranscendenceActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Omega Infinite Eternal Transcendence")
    float OmegaOmegaInfiniteEternalTranscendencePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Omega Infinite Eternal Transcendence")
    float OmegaOmegaInfiniteEternalTranscendenceThreshold;

    // Omega Omega Infinite Eternal Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Omega Infinite Eternal Transcendence")
    float OmegaOmegaInfiniteEternalRealityDominion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Omega Infinite Eternal Transcendence")
    float OmegaOmegaInfiniteEternalTranscendenceRecursion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Omega Infinite Eternal Transcendence")
    float OmegaOmegaInfiniteEternalInfiniteConsciousness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Omega Infinite Eternal Transcendence")
    float OmegaOmegaInfiniteEternalConceptualEvolution;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Omega Infinite Eternal Transcendence")
    float OmegaOmegaInfiniteEternalTranscendenceAuthority;

    // Omega Omega Infinite Eternal Transcendence Events
    UPROPERTY(BlueprintAssignable, Category = "Omega Omega Infinite Eternal Transcendence")
    FOnOmegaOmegaInfiniteEternalTranscendenceActivated OnOmegaOmegaInfiniteEternalTranscendenceActivated;

    UPROPERTY(BlueprintAssignable, Category = "Omega Omega Infinite Eternal Transcendence")
    FOnOmegaOmegaInfiniteEternalTranscendenceDeactivated OnOmegaOmegaInfiniteEternalTranscendenceDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Omega Omega Infinite Eternal Transcendence")
    FOnOmegaOmegaInfiniteEternalTranscendenceLevelChanged OnOmegaOmegaInfiniteEternalTranscendenceLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Omega Omega Infinite Eternal Transcendence")
    FOnOmegaOmegaInfiniteEternalTranscendenceMaxLevelReached OnOmegaOmegaInfiniteEternalTranscendenceMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Omega Omega Infinite Eternal Transcendence")
    FOnOmegaOmegaInfiniteEternalTranscendencePowerUsed OnOmegaOmegaInfiniteEternalTranscendencePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Omega Omega Infinite Eternal Transcendence")
    FOnOmegaOmegaInfiniteEternalTranscendencePowerFailed OnOmegaOmegaInfiniteEternalTranscendencePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Omega Omega Infinite Eternal Transcendence")
    FOnOmegaOmegaInfiniteEternalTranscendenceAbilityPerformed OnOmegaOmegaInfiniteEternalTranscendenceAbilityPerformed;

    // Omega Omega Infinite Eternal Transcendence Functions
    UFUNCTION(BlueprintCallable, Category = "Omega Omega Infinite Eternal Transcendence")
    void ActivateOmegaOmegaInfiniteEternalTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Omega Omega Infinite Eternal Transcendence")
    void DeactivateOmegaOmegaInfiniteEternalTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Omega Omega Infinite Eternal Transcendence")
    void SetOmegaOmegaInfiniteEternalTranscendenceLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Omega Omega Infinite Eternal Transcendence")
    void UseOmegaOmegaInfiniteEternalTranscendencePower();

    UFUNCTION(BlueprintCallable, Category = "Omega Omega Infinite Eternal Transcendence")
    void PerformOmegaOmegaInfiniteEternalTranscendenceAbility();

    UFUNCTION(BlueprintCallable, Category = "Omega Omega Infinite Eternal Transcendence")
    bool IsOmegaOmegaInfiniteEternalTranscendenceActive() const;

    UFUNCTION(BlueprintCallable, Category = "Omega Omega Infinite Eternal Transcendence")
    int32 GetOmegaOmegaInfiniteEternalTranscendenceLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Omega Omega Infinite Eternal Transcendence")
    float GetOmegaOmegaInfiniteEternalTranscendencePowerCost() const;

    // Omega Omega Infinite Eternal Transcendence Abilities
    UFUNCTION(BlueprintCallable, Category = "Omega Omega Infinite Eternal Transcendence")
    void ExerciseOmegaOmegaInfiniteEternalRealityDominion();

    UFUNCTION(BlueprintCallable, Category = "Omega Omega Infinite Eternal Transcendence")
    void TranscendOmegaOmegaInfiniteEternalRecursion();

    UFUNCTION(BlueprintCallable, Category = "Omega Omega Infinite Eternal Transcendence")
    void AccessOmegaOmegaInfiniteEternalInfiniteConsciousness();

    UFUNCTION(BlueprintCallable, Category = "Omega Omega Infinite Eternal Transcendence")
    void EvolveConceptually();

    UFUNCTION(BlueprintCallable, Category = "Omega Omega Infinite Eternal Transcendence")
    void WieldOmegaOmegaInfiniteEternalTranscendenceAuthority();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateOmegaOmegaInfiniteEternalTranscendence() const;
    void UpdateOmegaOmegaInfiniteEternalTranscendenceStats();
    void OnOmegaOmegaInfiniteEternalTranscendenceStateChanged();
};
