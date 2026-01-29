#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P12_TRNS_OMEGA_INFINITE_ETERNAL.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOmegaInfiniteEternalTranscendenceActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOmegaInfiniteEternalTranscendenceDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnOmegaInfiniteEternalTranscendenceLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOmegaInfiniteEternalTranscendenceMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOmegaInfiniteEternalTranscendencePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOmegaInfiniteEternalTranscendencePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOmegaInfiniteEternalTranscendenceAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP12_TRNS_OMEGA_INFINITE_ETERNAL : public UActorComponent
{
    GENERATED_BODY()

public:
    UP12_TRNS_OMEGA_INFINITE_ETERNAL();

    // Omega Infinite Eternal Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Infinite Eternal Transcendence")
    int32 OmegaInfiniteEternalTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Infinite Eternal Transcendence")
    int32 MaxOmegaInfiniteEternalTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Infinite Eternal Transcendence")
    bool bIsOmegaInfiniteEternalTranscendenceActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Infinite Eternal Transcendence")
    float OmegaInfiniteEternalTranscendencePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Infinite Eternal Transcendence")
    float OmegaInfiniteEternalTranscendenceThreshold;

    // Omega Infinite Eternal Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Infinite Eternal Transcendence")
    float OmegaInfiniteEternalRealityDominion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Infinite Eternal Transcendence")
    float OmegaInfiniteEternalTranscendenceRecursion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Infinite Eternal Transcendence")
    float OmegaInfiniteEternalInfiniteConsciousness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Infinite Eternal Transcendence")
    float OmegaInfiniteEternalConceptualEvolution;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Infinite Eternal Transcendence")
    float OmegaInfiniteEternalTranscendenceAuthority;

    // Omega Infinite Eternal Transcendence Events
    UPROPERTY(BlueprintAssignable, Category = "Omega Infinite Eternal Transcendence")
    FOnOmegaInfiniteEternalTranscendenceActivated OnOmegaInfiniteEternalTranscendenceActivated;

    UPROPERTY(BlueprintAssignable, Category = "Omega Infinite Eternal Transcendence")
    FOnOmegaInfiniteEternalTranscendenceDeactivated OnOmegaInfiniteEternalTranscendenceDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Omega Infinite Eternal Transcendence")
    FOnOmegaInfiniteEternalTranscendenceLevelChanged OnOmegaInfiniteEternalTranscendenceLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Omega Infinite Eternal Transcendence")
    FOnOmegaInfiniteEternalTranscendenceMaxLevelReached OnOmegaInfiniteEternalTranscendenceMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Omega Infinite Eternal Transcendence")
    FOnOmegaInfiniteEternalTranscendencePowerUsed OnOmegaInfiniteEternalTranscendencePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Omega Infinite Eternal Transcendence")
    FOnOmegaInfiniteEternalTranscendencePowerFailed OnOmegaInfiniteEternalTranscendencePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Omega Infinite Eternal Transcendence")
    FOnOmegaInfiniteEternalTranscendenceAbilityPerformed OnOmegaInfiniteEternalTranscendenceAbilityPerformed;

    // Omega Infinite Eternal Transcendence Functions
    UFUNCTION(BlueprintCallable, Category = "Omega Infinite Eternal Transcendence")
    void ActivateOmegaInfiniteEternalTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Omega Infinite Eternal Transcendence")
    void DeactivateOmegaInfiniteEternalTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Omega Infinite Eternal Transcendence")
    void SetOmegaInfiniteEternalTranscendenceLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Omega Infinite Eternal Transcendence")
    void UseOmegaInfiniteEternalTranscendencePower();

    UFUNCTION(BlueprintCallable, Category = "Omega Infinite Eternal Transcendence")
    void PerformOmegaInfiniteEternalTranscendenceAbility();

    UFUNCTION(BlueprintCallable, Category = "Omega Infinite Eternal Transcendence")
    bool IsOmegaInfiniteEternalTranscendenceActive() const;

    UFUNCTION(BlueprintCallable, Category = "Omega Infinite Eternal Transcendence")
    int32 GetOmegaInfiniteEternalTranscendenceLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Omega Infinite Eternal Transcendence")
    float GetOmegaInfiniteEternalTranscendencePowerCost() const;

    // Omega Infinite Eternal Transcendence Abilities
    UFUNCTION(BlueprintCallable, Category = "Omega Infinite Eternal Transcendence")
    void ExerciseOmegaInfiniteEternalRealityDominion();

    UFUNCTION(BlueprintCallable, Category = "Omega Infinite Eternal Transcendence")
    void TranscendOmegaInfiniteEternalRecursion();

    UFUNCTION(BlueprintCallable, Category = "Omega Infinite Eternal Transcendence")
    void AccessOmegaInfiniteEternalInfiniteConsciousness();

    UFUNCTION(BlueprintCallable, Category = "Omega Infinite Eternal Transcendence")
    void EvolveConceptually();

    UFUNCTION(BlueprintCallable, Category = "Omega Infinite Eternal Transcendence")
    void WieldOmegaInfiniteEternalTranscendenceAuthority();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateOmegaInfiniteEternalTranscendence() const;
    void UpdateOmegaInfiniteEternalTranscendenceStats();
    void OnOmegaInfiniteEternalTranscendenceStateChanged();
};
