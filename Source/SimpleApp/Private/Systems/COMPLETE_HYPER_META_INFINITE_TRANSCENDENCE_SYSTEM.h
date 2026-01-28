#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COMPLETE_HYPER_META_INFINITE_TRANSCENDENCE_SYSTEM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHyperMetaInfiniteTranscendenceActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHyperMetaInfiniteTranscendenceDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnHyperMetaInfiniteTranscendenceLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHyperMetaInfiniteTranscendenceMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHyperMetaInfiniteTranscendencePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHyperMetaInfiniteTranscendencePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHyperMetaInfiniteTranscendenceAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UCOMPLETE_HYPER_META_INFINITE_TRANSCENDENCE_SYSTEM : public UActorComponent
{
    GENERATED_BODY()

public:
    UCOMPLETE_HYPER_META_INFINITE_TRANSCENDENCE_SYSTEM();

    // Hyper-Meta-Infinite-Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper-Meta-Infinite-Transcendence")
    int32 HyperMetaInfiniteTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper-Meta-Infinite-Transcendence")
    int32 MaxHyperMetaInfiniteTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper-Meta-Infinite-Transcendence")
    bool bIsHyperMetaInfiniteTranscendenceActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper-Meta-Infinite-Transcendence")
    float HyperMetaInfiniteTranscendencePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper-Meta-Infinite-Transcendence")
    float HyperMetaInfiniteTranscendenceThreshold;

    // Hyper-Meta-Infinite-Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper-Meta-Infinite-Transcendence")
    float HyperRealityDominion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper-Meta-Infinite-Transcendence")
    float TranscendenceInfiniteRecursion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper-Meta-Infinite-Transcendence")
    float MetaInfiniteAwareness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper-Meta-Infinite-Transcendence")
    float ConceptualHyperEvolution;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper-Meta-Infinite-Transcendence")
    float UltimateHyperAuthority;

    // Hyper-Meta-Infinite-Transcendence Events
    UPROPERTY(BlueprintAssignable, Category = "Hyper-Meta-Infinite-Transcendence")
    FOnHyperMetaInfiniteTranscendenceActivated OnHyperMetaInfiniteTranscendenceActivated;

    UPROPERTY(BlueprintAssignable, Category = "Hyper-Meta-Infinite-Transcendence")
    FOnHyperMetaInfiniteTranscendenceDeactivated OnHyperMetaInfiniteTranscendenceDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Hyper-Meta-Infinite-Transcendence")
    FOnHyperMetaInfiniteTranscendenceLevelChanged OnHyperMetaInfiniteTranscendenceLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Hyper-Meta-Infinite-Transcendence")
    FOnHyperMetaInfiniteTranscendenceMaxLevelReached OnHyperMetaInfiniteTranscendenceMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Hyper-Meta-Infinite-Transcendence")
    FOnHyperMetaInfiniteTranscendencePowerUsed OnHyperMetaInfiniteTranscendencePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Hyper-Meta-Infinite-Transcendence")
    FOnHyperMetaInfiniteTranscendencePowerFailed OnHyperMetaInfiniteTranscendencePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Hyper-Meta-Infinite-Transcendence")
    FOnHyperMetaInfiniteTranscendenceAbilityPerformed OnHyperMetaInfiniteTranscendenceAbilityPerformed;

    // Hyper-Meta-Infinite-Transcendence Functions
    UFUNCTION(BlueprintCallable, Category = "Hyper-Meta-Infinite-Transcendence")
    void ActivateHyperMetaInfiniteTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Hyper-Meta-Infinite-Transcendence")
    void DeactivateHyperMetaInfiniteTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Hyper-Meta-Infinite-Transcendence")
    void SetHyperMetaInfiniteTranscendenceLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Hyper-Meta-Infinite-Transcendence")
    void UseHyperMetaInfiniteTranscendencePower();

    UFUNCTION(BlueprintCallable, Category = "Hyper-Meta-Infinite-Transcendence")
    void PerformHyperMetaInfiniteTranscendenceAbility();

    UFUNCTION(BlueprintCallable, Category = "Hyper-Meta-Infinite-Transcendence")
    bool IsHyperMetaInfiniteTranscendenceActive() const;

    UFUNCTION(BlueprintCallable, Category = "Hyper-Meta-Infinite-Transcendence")
    int32 GetHyperMetaInfiniteTranscendenceLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Hyper-Meta-Infinite-Transcendence")
    float GetHyperMetaInfiniteTranscendencePowerCost() const;

    // Hyper-Meta-Infinite-Transcendence Abilities
    UFUNCTION(BlueprintCallable, Category = "Hyper-Meta-Infinite-Transcendence")
    void ExerciseHyperRealityDominion();

    UFUNCTION(BlueprintCallable, Category = "Hyper-Meta-Infinite-Transcendence")
    void TranscendInfiniteRecursion();

    UFUNCTION(BlueprintCallable, Category = "Hyper-Meta-Infinite-Transcendence")
    void AccessMetaInfiniteAwareness();

    UFUNCTION(BlueprintCallable, Category = "Hyper-Meta-Infinite-Transcendence")
    void EvolveConceptuallyHyper();

    UFUNCTION(BlueprintCallable, Category = "Hyper-Meta-Infinite-Transcendence")
    void WieldUltimateHyperAuthority();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateHyperMetaInfiniteTranscendence() const;
    void UpdateHyperMetaInfiniteTranscendenceStats();
    void OnHyperMetaInfiniteTranscendenceStateChanged();
};
