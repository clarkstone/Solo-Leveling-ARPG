#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COMPLETE_SUPREME_ULTRA_HYPER_META_INFINITE_TRANSCENDENCE_SYSTEM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSupremeUltraHyperMetaInfiniteTranscendenceActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSupremeUltraHyperMetaInfiniteTranscendenceDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnSupremeUltraHyperMetaInfiniteTranscendenceLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSupremeUltraHyperMetaInfiniteTranscendenceMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSupremeUltraHyperMetaInfiniteTranscendencePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSupremeUltraHyperMetaInfiniteTranscendencePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSupremeUltraHyperMetaInfiniteTranscendenceAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UCOMPLETE_SUPREME_ULTRA_HYPER_META_INFINITE_TRANSCENDENCE_SYSTEM : public UActorComponent
{
    GENERATED_BODY()

public:
    UCOMPLETE_SUPREME_ULTRA_HYPER_META_INFINITE_TRANSCENDENCE_SYSTEM();

    // Supreme-Ultra-Hyper-Meta-Infinite-Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    int32 SupremeUltraHyperMetaInfiniteTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    int32 MaxSupremeUltraHyperMetaInfiniteTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    bool bIsSupremeUltraHyperMetaInfiniteTranscendenceActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    float SupremeUltraHyperMetaInfiniteTranscendencePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    float SupremeUltraHyperMetaInfiniteTranscendenceThreshold;

    // Supreme-Ultra-Hyper-Meta-Infinite-Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    float SupremeUltraHyperRealityDominion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    float TranscendenceAbsoluteUltimateRecursion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    float UltraHyperMetaInfiniteSupremeConsciousness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    float ConceptualSupremeUltraHyperEvolution;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    float UltimateSupremeUltraHyperAuthority;

    // Supreme-Ultra-Hyper-Meta-Infinite-Transcendence Events
    UPROPERTY(BlueprintAssignable, Category = "Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    FOnSupremeUltraHyperMetaInfiniteTranscendenceActivated OnSupremeUltraHyperMetaInfiniteTranscendenceActivated;

    UPROPERTY(BlueprintAssignable, Category = "Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    FOnSupremeUltraHyperMetaInfiniteTranscendenceDeactivated OnSupremeUltraHyperMetaInfiniteTranscendenceDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    FOnSupremeUltraHyperMetaInfiniteTranscendenceLevelChanged OnSupremeUltraHyperMetaInfiniteTranscendenceLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    FOnSupremeUltraHyperMetaInfiniteTranscendenceMaxLevelReached OnSupremeUltraHyperMetaInfiniteTranscendenceMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    FOnSupremeUltraHyperMetaInfiniteTranscendencePowerUsed OnSupremeUltraHyperMetaInfiniteTranscendencePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    FOnSupremeUltraHyperMetaInfiniteTranscendencePowerFailed OnSupremeUltraHyperMetaInfiniteTranscendencePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    FOnSupremeUltraHyperMetaInfiniteTranscendenceAbilityPerformed OnSupremeUltraHyperMetaInfiniteTranscendenceAbilityPerformed;

    // Supreme-Ultra-Hyper-Meta-Infinite-Transcendence Functions
    UFUNCTION(BlueprintCallable, Category = "Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void ActivateSupremeUltraHyperMetaInfiniteTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void DeactivateSupremeUltraHyperMetaInfiniteTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void SetSupremeUltraHyperMetaInfiniteTranscendenceLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void UseSupremeUltraHyperMetaInfiniteTranscendencePower();

    UFUNCTION(BlueprintCallable, Category = "Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void PerformSupremeUltraHyperMetaInfiniteTranscendenceAbility();

    UFUNCTION(BlueprintCallable, Category = "Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    bool IsSupremeUltraHyperMetaInfiniteTranscendenceActive() const;

    UFUNCTION(BlueprintCallable, Category = "Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    int32 GetSupremeUltraHyperMetaInfiniteTranscendenceLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    float GetSupremeUltraHyperMetaInfiniteTranscendencePowerCost() const;

    // Supreme-Ultra-Hyper-Meta-Infinite-Transcendence Abilities
    UFUNCTION(BlueprintCallable, Category = "Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void ExerciseSupremeUltraHyperRealityDominion();

    UFUNCTION(BlueprintCallable, Category = "Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void TranscendAbsoluteUltimateRecursion();

    UFUNCTION(BlueprintCallable, Category = "Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void AccessUltraHyperMetaInfiniteSupremeConsciousness();

    UFUNCTION(BlueprintCallable, Category = "Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void EvolveConceptuallySupremeUltraHyper();

    UFUNCTION(BlueprintCallable, Category = "Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void WieldUltimateSupremeUltraHyperAuthority();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateSupremeUltraHyperMetaInfiniteTranscendence() const;
    void UpdateSupremeUltraHyperMetaInfiniteTranscendenceStats();
    void OnSupremeUltraHyperMetaInfiniteTranscendenceStateChanged();
};
