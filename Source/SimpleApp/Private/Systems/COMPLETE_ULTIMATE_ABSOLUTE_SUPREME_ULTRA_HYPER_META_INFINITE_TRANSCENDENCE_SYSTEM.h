#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COMPLETE_ULTIMATE_ABSOLUTE_SUPREME_ULTRA_HYPER_META_INFINITE_TRANSCENDENCE_SYSTEM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendencePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendencePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UCOMPLETE_ULTIMATE_ABSOLUTE_SUPREME_ULTRA_HYPER_META_INFINITE_TRANSCENDENCE_SYSTEM : public UActorComponent
{
    GENERATED_BODY()

public:
    UCOMPLETE_ULTIMATE_ABSOLUTE_SUPREME_ULTRA_HYPER_META_INFINITE_TRANSCENDENCE_SYSTEM();

    // Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    int32 UltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    int32 MaxUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    bool bIsUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    float UltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendencePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    float UltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceThreshold;

    // Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    float UltimateAbsoluteSupremeUltraHyperRealityAbsoluteDominion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    float TranscendenceUltimateAbsoluteUltimateRecursion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    float UltraHyperMetaInfiniteUltimateSupremeConsciousness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    float ConceptualUltimateAbsoluteSupremeUltraHyperEvolution;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    float UltimateUltimateAbsoluteSupremeUltraHyperAuthority;

    // Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence Events
    UPROPERTY(BlueprintAssignable, Category = "Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    FOnUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceActivated OnUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceActivated;

    UPROPERTY(BlueprintAssignable, Category = "Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    FOnUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceDeactivated OnUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    FOnUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceLevelChanged OnUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    FOnUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceMaxLevelReached OnUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    FOnUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendencePowerUsed OnUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendencePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    FOnUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendencePowerFailed OnUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendencePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    FOnUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceAbilityPerformed OnUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceAbilityPerformed;

    // Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence Functions
    UFUNCTION(BlueprintCallable, Category = "Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void ActivateUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void DeactivateUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void SetUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void UseUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendencePower();

    UFUNCTION(BlueprintCallable, Category = "Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void PerformUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceAbility();

    UFUNCTION(BlueprintCallable, Category = "Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    bool IsUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceActive() const;

    UFUNCTION(BlueprintCallable, Category = "Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    int32 GetUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    float GetUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendencePowerCost() const;

    // Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence Abilities
    UFUNCTION(BlueprintCallable, Category = "Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void ExerciseUltimateAbsoluteSupremeUltraHyperRealityAbsoluteDominion();

    UFUNCTION(BlueprintCallable, Category = "Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void TranscendUltimateAbsoluteUltimateRecursion();

    UFUNCTION(BlueprintCallable, Category = "Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void AccessUltimateSupremeUltraHyperMetaInfiniteSupremeConsciousness();

    UFUNCTION(BlueprintCallable, Category = "Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void EvolveConceptuallyUltimateAbsoluteSupremeUltraHyper();

    UFUNCTION(BlueprintCallable, Category = "Ultimate-Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void WieldUltimateAbsoluteSupremeUltraHyperAuthority();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendence() const;
    void UpdateUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceStats();
    void OnUltimateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceStateChanged();
};
