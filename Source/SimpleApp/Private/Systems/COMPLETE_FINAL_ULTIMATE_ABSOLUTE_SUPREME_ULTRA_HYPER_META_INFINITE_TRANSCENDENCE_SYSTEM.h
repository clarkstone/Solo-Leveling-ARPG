#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COMPLETE_FINAL_ULTIMATE_ABSOLUTE_SUPREME_ULTRA_HYPER_META_INFINITE_TRANSCENDENCE_SYSTEM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFinalUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFinalUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnFinalUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFinalUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFinalUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendencePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFinalUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendencePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFinalUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UCOMPLETE_FINAL_ULTIMATE_ABSOLUTE_SUPREME_ULTRA_HYPER_META_INFINITE_TRANSCENDENCE_SYSTEM : public UActorComponent
{
    GENERATED_BODY()

public:
    UCOMPLETE_FINAL_ULTIMATE_ABSOLUTE_SUPREME_ULTRA_HYPER_META_INFINITE_TRANSCENDENCE_SYSTEM();

    // Final-Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Final-Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    int32 FinalUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Final-Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    int32 MaxFinalUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Final-Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    bool bIsFinalUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Final-Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    float FinalUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendencePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Final-Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    float FinalUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceThreshold;

    // Final-Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Final-Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    float FinalUltimateAbsoluteSupremeUltraHyperRealityAbsoluteDominion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Final-Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    float TranscendenceFinalUltimateAbsoluteUltimateRecursion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Final-Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    float UltimateSupremeUltraHyperMetaInfiniteFinalSupremeConsciousness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Final-Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    float ConceptualFinalUltimateAbsoluteSupremeUltraHyperEvolution;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Final-Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    float FinalUltimateAbsoluteSupremeUltimateAuthority;

    // Final-Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence Events
    UPROPERTY(BlueprintAssignable, Category = "Final-Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    FOnFinalUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceActivated OnFinalUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceActivated;

    UPROPERTY(BlueprintAssignable, Category = "Final-Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    FOnFinalUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceDeactivated OnFinalUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Final-Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    FOnFinalUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceLevelChanged OnFinalUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Final-Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    FOnFinalUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceMaxLevelReached OnFinalUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Final-Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    FOnFinalUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendencePowerUsed OnFinalUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendencePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Final-Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    FOnFinalUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendencePowerFailed OnFinalUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendencePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Final-Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    FOnFinalUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceAbilityPerformed OnFinalUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceAbilityPerformed;

    // Final-Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence Functions
    UFUNCTION(BlueprintCallable, Category = "Final-Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void ActivateFinalUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Final-Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void DeactivateFinalUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Final-Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void SetFinalUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Final-Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void UseFinalUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendencePower();

    UFUNCTION(BlueprintCallable, Category = "Final-Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void PerformFinalUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceAbility();

    UFUNCTION(BlueprintCallable, Category = "Final-Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    bool IsFinalUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceActive() const;

    UFUNCTION(BlueprintCallable, Category = "Final-Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    int32 GetFinalUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Final-Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    float GetFinalUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendencePowerCost() const;

    // Final-Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence Abilities
    UFUNCTION(BlueprintCallable, Category = "Final-Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void ExerciseFinalUltimateAbsoluteSupremeUltraHyperRealityAbsoluteDominion();

    UFUNCTION(BlueprintCallable, Category = "Final-Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void TranscendFinalUltimateAbsoluteUltimateRecursion();

    UFUNCTION(BlueprintCallable, Category = "Final-Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void AccessFinalSupremeUltraHyperMetaInfiniteFinalSupremeConsciousness();

    UFUNCTION(BlueprintCallable, Category = "Final-Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void EvolveConceptuallyFinalUltimateAbsoluteSupremeUltraHyper();

    UFUNCTION(BlueprintCallable, Category = "Final-Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void WieldFinalUltimateAbsoluteSupremeUltimateAuthority();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateFinalUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendence() const;
    void UpdateFinalUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceStats();
    void OnFinalUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceStateChanged();
};
