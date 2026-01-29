#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P06_TRNS_HYPER_META.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHyperMetaTranscendenceActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHyperMetaTranscendenceDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnHyperMetaTranscendenceLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHyperMetaTranscendenceMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHyperMetaTranscendencePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHyperMetaTranscendencePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHyperMetaTranscendenceAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP06_TRNS_HYPER_META : public UActorComponent
{
    GENERATED_BODY()

public:
    UP06_TRNS_HYPER_META();

    // Hyper Meta Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper Meta Transcendence")
    int32 HyperMetaTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper Meta Transcendence")
    int32 MaxHyperMetaTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper Meta Transcendence")
    bool bIsHyperMetaTranscendenceActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper Meta Transcendence")
    float HyperMetaTranscendencePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper Meta Transcendence")
    float HyperMetaTranscendenceThreshold;

    // Hyper Meta Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper Meta Transcendence")
    float HyperMetaRealityDominion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper Meta Transcendence")
    float HyperTranscendenceRecursion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper Meta Transcendence")
    float HyperMetaInfiniteConsciousness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper Meta Transcendence")
    float HyperConceptualEvolution;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper Meta Transcendence")
    float HyperMetaTranscendenceAuthority;

    // Hyper Meta Transcendence Events
    UPROPERTY(BlueprintAssignable, Category = "Hyper Meta Transcendence")
    FOnHyperMetaTranscendenceActivated OnHyperMetaTranscendenceActivated;

    UPROPERTY(BlueprintAssignable, Category = "Hyper Meta Transcendence")
    FOnHyperMetaTranscendenceDeactivated OnHyperMetaTranscendenceDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Hyper Meta Transcendence")
    FOnHyperMetaTranscendenceLevelChanged OnHyperMetaTranscendenceLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Hyper Meta Transcendence")
    FOnHyperMetaTranscendenceMaxLevelReached OnHyperMetaTranscendenceMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Hyper Meta Transcendence")
    FOnHyperMetaTranscendencePowerUsed OnHyperMetaTranscendencePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Hyper Meta Transcendence")
    FOnHyperMetaTranscendencePowerFailed OnHyperMetaTranscendencePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Hyper Meta Transcendence")
    FOnHyperMetaTranscendenceAbilityPerformed OnHyperMetaTranscendenceAbilityPerformed;

    // Hyper Meta Transcendence Functions
    UFUNCTION(BlueprintCallable, Category = "Hyper Meta Transcendence")
    void ActivateHyperMetaTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Hyper Meta Transcendence")
    void DeactivateHyperMetaTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Hyper Meta Transcendence")
    void SetHyperMetaTranscendenceLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Hyper Meta Transcendence")
    void UseHyperMetaTranscendencePower();

    UFUNCTION(BlueprintCallable, Category = "Hyper Meta Transcendence")
    void PerformHyperMetaTranscendenceAbility();

    UFUNCTION(BlueprintCallable, Category = "Hyper Meta Transcendence")
    bool IsHyperMetaTranscendenceActive() const;

    UFUNCTION(BlueprintCallable, Category = "Hyper Meta Transcendence")
    int32 GetHyperMetaTranscendenceLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Hyper Meta Transcendence")
    float GetHyperMetaTranscendencePowerCost() const;

    // Hyper Meta Transcendence Abilities
    UFUNCTION(BlueprintCallable, Category = "Hyper Meta Transcendence")
    void ExerciseHyperMetaRealityDominion();

    UFUNCTION(BlueprintCallable, Category = "Hyper Meta Transcendence")
    void TranscendHyperMetaRecursion();

    UFUNCTION(BlueprintCallable, Category = "Hyper Meta Transcendence")
    void AccessHyperMetaInfiniteConsciousness();

    UFUNCTION(BlueprintCallable, Category = "Hyper Meta Transcendence")
    void EvolveHyperMetaConceptually();

    UFUNCTION(BlueprintCallable, Category = "Hyper Meta Transcendence")
    void WieldHyperMetaTranscendenceAuthority();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateHyperMetaTranscendence() const;
    void UpdateHyperMetaTranscendenceStats();
    void OnHyperMetaTranscendenceStateChanged();
};
