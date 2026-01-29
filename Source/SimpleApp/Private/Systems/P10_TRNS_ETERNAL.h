#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P10_TRNS_ETERNAL.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEternalTranscendenceActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEternalTranscendenceDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnEternalTranscendenceLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEternalTranscendenceMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEternalTranscendencePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEternalTranscendencePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEternalTranscendenceAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP10_TRNS_ETERNAL : public UActorComponent
{
    GENERATED_BODY()

public:
    UP10_TRNS_ETERNAL();

    // Eternal Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal Transcendence")
    int32 EternalTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal Transcendence")
    int32 MaxEternalTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal Transcendence")
    bool bIsEternalTranscendenceActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal Transcendence")
    float EternalTranscendencePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal Transcendence")
    float EternalTranscendenceThreshold;

    // Eternal Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal Transcendence")
    float EternalRealityDominion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal Transcendence")
    float EternalTranscendenceRecursion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal Transcendence")
    float EternalInfiniteConsciousness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal Transcendence")
    float EternalConceptualEvolution;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal Transcendence")
    float EternalTranscendenceAuthority;

    // Eternal Transcendence Events
    UPROPERTY(BlueprintAssignable, Category = "Eternal Transcendence")
    FOnEternalTranscendenceActivated OnEternalTranscendenceActivated;

    UPROPERTY(BlueprintAssignable, Category = "Eternal Transcendence")
    FOnEternalTranscendenceDeactivated OnEternalTranscendenceDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Eternal Transcendence")
    FOnEternalTranscendenceLevelChanged OnEternalTranscendenceLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Eternal Transcendence")
    FOnEternalTranscendenceMaxLevelReached OnEternalTranscendenceMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Eternal Transcendence")
    FOnEternalTranscendencePowerUsed OnEternalTranscendencePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Eternal Transcendence")
    FOnEternalTranscendencePowerFailed OnEternalTranscendencePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Eternal Transcendence")
    FOnEternalTranscendenceAbilityPerformed OnEternalTranscendenceAbilityPerformed;

    // Eternal Transcendence Functions
    UFUNCTION(BlueprintCallable, Category = "Eternal Transcendence")
    void ActivateEternalTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Eternal Transcendence")
    void DeactivateEternalTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Eternal Transcendence")
    void SetEternalTranscendenceLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Eternal Transcendence")
    void UseEternalTranscendencePower();

    UFUNCTION(BlueprintCallable, Category = "Eternal Transcendence")
    void PerformEternalTranscendenceAbility();

    UFUNCTION(BlueprintCallable, Category = "Eternal Transcendence")
    bool IsEternalTranscendenceActive() const;

    UFUNCTION(BlueprintCallable, Category = "Eternal Transcendence")
    int32 GetEternalTranscendenceLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Eternal Transcendence")
    float GetEternalTranscendencePowerCost() const;

    // Eternal Transcendence Abilities
    UFUNCTION(BlueprintCallable, Category = "Eternal Transcendence")
    void ExerciseEternalRealityDominion();

    UFUNCTION(BlueprintCallable, Category = "Eternal Transcendence")
    void TranscendEternalRecursion();

    UFUNCTION(BlueprintCallable, Category = "Eternal Transcendence")
    void AccessEternalInfiniteConsciousness();

    UFUNCTION(BlueprintCallable, Category = "Eternal Transcendence")
    void EvolveConceptually();

    UFUNCTION(BlueprintCallable, Category = "Eternal Transcendence")
    void WieldEternalTranscendenceAuthority();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateEternalTranscendence() const;
    void UpdateEternalTranscendenceStats();
    void OnEternalTranscendenceStateChanged();
};
