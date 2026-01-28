#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COMPLETE_ULTRA_HYPER_META_INFINITE_TRANSCENDENCE_SYSTEM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltraHyperMetaInfiniteTranscendenceActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltraHyperMetaInfiniteTranscendenceDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnUltraHyperMetaInfiniteTranscendenceLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUltraHyperMetaInfiniteTranscendenceMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltraHyperMetaInfiniteTranscendencePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUltraHyperMetaInfiniteTranscendencePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltraHyperMetaInfiniteTranscendenceAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UCOMPLETE_ULTRA_HYPER_META_INFINITE_TRANSCENDENCE_SYSTEM : public UActorComponent
{
    GENERATED_BODY()

public:
    UCOMPLETE_ULTRA_HYPER_META_INFINITE_TRANSCENDENCE_SYSTEM();

    // Ultra-Hyper-Meta-Infinite-Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra-Hyper-Meta-Infinite-Transcendence")
    int32 UltraHyperMetaInfiniteTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra-Hyper-Meta-Infinite-Transcendence")
    int32 MaxUltraHyperMetaInfiniteTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra-Hyper-Meta-Infinite-Transcendence")
    bool bIsUltraHyperMetaInfiniteTranscendenceActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra-Hyper-Meta-Infinite-Transcendence")
    float UltraHyperMetaInfiniteTranscendencePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra-Hyper-Meta-Infinite-Transcendence")
    float UltraHyperMetaInfiniteTranscendenceThreshold;

    // Ultra-Hyper-Meta-Infinite-Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra-Hyper-Meta-Infinite-Transcendence")
    float UltraHyperRealitySupremacy;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra-Hyper-Meta-Infinite-Transcendence")
    float TranscendenceUltimateRecursion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra-Hyper-Meta-Infinite-Transcendence")
    float HyperMetaInfiniteConsciousness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra-Hyper-Meta-Infinite-Transcendence")
    float ConceptualUltraHyperEvolution;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra-Hyper-Meta-Infinite-Transcendence")
    float UltimateUltraHyperAuthority;

    // Ultra-Hyper-Meta-Infinite-Transcendence Events
    UPROPERTY(BlueprintAssignable, Category = "Ultra-Hyper-Meta-Infinite-Transcendence")
    FOnUltraHyperMetaInfiniteTranscendenceActivated OnUltraHyperMetaInfiniteTranscendenceActivated;

    UPROPERTY(BlueprintAssignable, Category = "Ultra-Hyper-Meta-Infinite-Transcendence")
    FOnUltraHyperMetaInfiniteTranscendenceDeactivated OnUltraHyperMetaInfiniteTranscendenceDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Ultra-Hyper-Meta-Infinite-Transcendence")
    FOnUltraHyperMetaInfiniteTranscendenceLevelChanged OnUltraHyperMetaInfiniteTranscendenceLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Ultra-Hyper-Meta-Infinite-Transcendence")
    FOnUltraHyperMetaInfiniteTranscendenceMaxLevelReached OnUltraHyperMetaInfiniteTranscendenceMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Ultra-Hyper-Meta-Infinite-Transcendence")
    FOnUltraHyperMetaInfiniteTranscendencePowerUsed OnUltraHyperMetaInfiniteTranscendencePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Ultra-Hyper-Meta-Infinite-Transcendence")
    FOnUltraHyperMetaInfiniteTranscendencePowerFailed OnUltraHyperMetaInfiniteTranscendencePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Ultra-Hyper-Meta-Infinite-Transcendence")
    FOnUltraHyperMetaInfiniteTranscendenceAbilityPerformed OnUltraHyperMetaInfiniteTranscendenceAbilityPerformed;

    // Ultra-Hyper-Meta-Infinite-Transcendence Functions
    UFUNCTION(BlueprintCallable, Category = "Ultra-Hyper-Meta-Infinite-Transcendence")
    void ActivateUltraHyperMetaInfiniteTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Ultra-Hyper-Meta-Infinite-Transcendence")
    void DeactivateUltraHyperMetaInfiniteTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Ultra-Hyper-Meta-Infinite-Transcendence")
    void SetUltraHyperMetaInfiniteTranscendenceLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Ultra-Hyper-Meta-Infinite-Transcendence")
    void UseUltraHyperMetaInfiniteTranscendencePower();

    UFUNCTION(BlueprintCallable, Category = "Ultra-Hyper-Meta-Infinite-Transcendence")
    void PerformUltraHyperMetaInfiniteTranscendenceAbility();

    UFUNCTION(BlueprintCallable, Category = "Ultra-Hyper-Meta-Infinite-Transcendence")
    bool IsUltraHyperMetaInfiniteTranscendenceActive() const;

    UFUNCTION(BlueprintCallable, Category = "Ultra-Hyper-Meta-Infinite-Transcendence")
    int32 GetUltraHyperMetaInfiniteTranscendenceLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Ultra-Hyper-Meta-Infinite-Transcendence")
    float GetUltraHyperMetaInfiniteTranscendencePowerCost() const;

    // Ultra-Hyper-Meta-Infinite-Transcendence Abilities
    UFUNCTION(BlueprintCallable, Category = "Ultra-Hyper-Meta-Infinite-Transcendence")
    void ExerciseUltraHyperRealitySupremacy();

    UFUNCTION(BlueprintCallable, Category = "Ultra-Hyper-Meta-Infinite-Transcendence")
    void TranscendUltimateRecursion();

    UFUNCTION(BlueprintCallable, Category = "Ultra-Hyper-Meta-Infinite-Transcendence")
    void AccessHyperMetaInfiniteConsciousness();

    UFUNCTION(BlueprintCallable, Category = "Ultra-Hyper-Meta-Infinite-Transcendence")
    void EvolveConceptuallyUltraHyper();

    UFUNCTION(BlueprintCallable, Category = "Ultra-Hyper-Meta-Infinite-Transcendence")
    void WieldUltimateUltraHyperAuthority();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateUltraHyperMetaInfiniteTranscendence() const;
    void UpdateUltraHyperMetaInfiniteTranscendenceStats();
    void OnUltraHyperMetaInfiniteTranscendenceStateChanged();
};
