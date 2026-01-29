#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P07_TRNS_ULTRA_META.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltraMetaTranscendenceActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltraMetaTranscendenceDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnUltraMetaTranscendenceLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUltraMetaTranscendenceMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltraMetaTranscendencePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUltraMetaTranscendencePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltraMetaTranscendenceAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP07_TRNS_ULTRA_META : public UActorComponent
{
    GENERATED_BODY()

public:
    UP07_TRNS_ULTRA_META();

    // Ultra Meta Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Meta Transcendence")
    int32 UltraMetaTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Meta Transcendence")
    int32 MaxUltraMetaTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Meta Transcendence")
    bool bIsUltraMetaTranscendenceActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Meta Transcendence")
    float UltraMetaTranscendencePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Meta Transcendence")
    float UltraMetaTranscendenceThreshold;

    // Ultra Meta Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Meta Transcendence")
    float UltraMetaRealityDominion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Meta Transcendence")
    float UltraTranscendenceRecursion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Meta Transcendence")
    float UltraMetaInfiniteConsciousness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Meta Transcendence")
    float UltraConceptualEvolution;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Meta Transcendence")
    float UltraMetaTranscendenceAuthority;

    // Ultra Meta Transcendence Events
    UPROPERTY(BlueprintAssignable, Category = "Ultra Meta Transcendence")
    FOnUltraMetaTranscendenceActivated OnUltraMetaTranscendenceActivated;

    UPROPERTY(BlueprintAssignable, Category = "Ultra Meta Transcendence")
    FOnUltraMetaTranscendenceDeactivated OnUltraMetaTranscendenceDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Ultra Meta Transcendence")
    FOnUltraMetaTranscendenceLevelChanged OnUltraMetaTranscendenceLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Ultra Meta Transcendence")
    FOnUltraMetaTranscendenceMaxLevelReached OnUltraMetaTranscendenceMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Ultra Meta Transcendence")
    FOnUltraMetaTranscendencePowerUsed OnUltraMetaTranscendencePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Ultra Meta Transcendence")
    FOnUltraMetaTranscendencePowerFailed OnUltraMetaTranscendencePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Ultra Meta Transcendence")
    FOnUltraMetaTranscendenceAbilityPerformed OnUltraMetaTranscendenceAbilityPerformed;

    // Ultra Meta Transcendence Functions
    UFUNCTION(BlueprintCallable, Category = "Ultra Meta Transcendence")
    void ActivateUltraMetaTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Ultra Meta Transcendence")
    void DeactivateUltraMetaTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Ultra Meta Transcendence")
    void SetUltraMetaTranscendenceLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Ultra Meta Transcendence")
    void UseUltraMetaTranscendencePower();

    UFUNCTION(BlueprintCallable, Category = "Ultra Meta Transcendence")
    void PerformUltraMetaTranscendenceAbility();

    UFUNCTION(BlueprintCallable, Category = "Ultra Meta Transcendence")
    bool IsUltraMetaTranscendenceActive() const;

    UFUNCTION(BlueprintCallable, Category = "Ultra Meta Transcendence")
    int32 GetUltraMetaTranscendenceLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Ultra Meta Transcendence")
    float GetUltraMetaTranscendencePowerCost() const;

    // Ultra Meta Transcendence Abilities
    UFUNCTION(BlueprintCallable, Category = "Ultra Meta Transcendence")
    void ExerciseUltraMetaRealityDominion();

    UFUNCTION(BlueprintCallable, Category = "Ultra Meta Transcendence")
    void TranscendUltraMetaRecursion();

    UFUNCTION(BlueprintCallable, Category = "Ultra Meta Transcendence)
    void AccessUltraMetaInfiniteConsciousness();

    UFUNCTION(BlueprintCallable, Category = "Ultra Meta Transcendence)
    void EvolveUltraMetaConceptually();

    UFUNCTION(BlueprintCallable, Category = "Ultra Meta Transcendence")
    void WieldUltraMetaTranscendenceAuthority();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateUltraMetaTranscendence() const;
    void UpdateUltraMetaTranscendenceStats();
    void OnUltraMetaTranscendenceStateChanged();
};
