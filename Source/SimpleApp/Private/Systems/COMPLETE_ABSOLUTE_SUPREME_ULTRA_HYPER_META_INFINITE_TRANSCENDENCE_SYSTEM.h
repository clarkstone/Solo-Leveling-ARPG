#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COMPLETE_ABSOLUTE_SUPREME_ULTRA_HYPER_META_INFINITE_TRANSCENDENCE_SYSTEM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbsoluteSupremeUltraHyperMetaInfiniteTranscendencePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbsoluteSupremeUltraHyperMetaInfiniteTranscendencePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UCOMPLETE_ABSOLUTE_SUPREME_ULTRA_HYPER_META_INFINITE_TRANSCENDENCE_SYSTEM : public UActorComponent
{
    GENERATED_BODY()

public:
    UCOMPLETE_ABSOLUTE_SUPREME_ULTRA_HYPER_META_INFINITE_TRANSCENDENCE_SYSTEM();

    // Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    int32 AbsoluteSupremeUltraHyperMetaInfiniteTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    int32 MaxAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    bool bIsAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    float AbsoluteSupremeUltraHyperMetaInfiniteTranscendencePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    float AbsoluteSupremeUltraHyperMetaInfiniteTranscendenceThreshold;

    // Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    float AbsoluteSupremeUltraHyperRealityAbsoluteDominion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    float TranscendenceSupremeAbsoluteUltimateRecursion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    float UltraHyperMetaInfiniteAbsoluteSupremeConsciousness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    float ConceptualAbsoluteSupremeUltraHyperEvolution;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    float UltimateAbsoluteSupremeUltraHyperAuthority;

    // Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence Events
    UPROPERTY(BlueprintAssignable, Category = "Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    FOnAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceActivated OnAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceActivated;

    UPROPERTY(BlueprintAssignable, Category = "Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    FOnAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceDeactivated OnAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    FOnAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceLevelChanged OnAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    FOnAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceMaxLevelReached OnAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    FOnAbsoluteSupremeUltraHyperMetaInfiniteTranscendencePowerUsed OnAbsoluteSupremeUltraHyperMetaInfiniteTranscendencePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    FOnAbsoluteSupremeUltraHyperMetaInfiniteTranscendencePowerFailed OnAbsoluteSupremeUltraHyperMetaInfiniteTranscendencePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    FOnAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceAbilityPerformed OnAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceAbilityPerformed;

    // Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence Functions
    UFUNCTION(BlueprintCallable, Category = "Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void ActivateAbsoluteSupremeUltraHyperMetaInfiniteTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void DeactivateAbsoluteSupremeUltraHyperMetaInfiniteTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void SetAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void UseAbsoluteSupremeUltraHyperMetaInfiniteTranscendencePower();

    UFUNCTION(BlueprintCallable, Category = "Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void PerformAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceAbility();

    UFUNCTION(BlueprintCallable, Category = "Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    bool IsAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceActive() const;

    UFUNCTION(BlueprintCallable, Category = "Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    int32 GetAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    float GetAbsoluteSupremeUltraHyperMetaInfiniteTranscendencePowerCost() const;

    // Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence Abilities
    UFUNCTION(BlueprintCallable, Category = "Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void ExerciseAbsoluteSupremeUltraHyperRealityAbsoluteDominion();

    UFUNCTION(BlueprintCallable, Category = "Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void TranscendSupremeAbsoluteUltimateRecursion();

    UFUNCTION(BlueprintCallable, Category = "Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void AccessUltraHyperMetaInfiniteAbsoluteSupremeConsciousness();

    UFUNCTION(BlueprintCallable, Category = "Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void EvolveConceptuallyAbsoluteSupremeUltraHyper();

    UFUNCTION(BlueprintCallable, Category = "Absolute-Supreme-Ultra-Hyper-Meta-Infinite-Transcendence")
    void WieldUltimateAbsoluteSupremeUltraHyperAuthority();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateAbsoluteSupremeUltraHyperMetaInfiniteTranscendence() const;
    void UpdateAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceStats();
    void OnAbsoluteSupremeUltraHyperMetaInfiniteTranscendenceStateChanged();
};
