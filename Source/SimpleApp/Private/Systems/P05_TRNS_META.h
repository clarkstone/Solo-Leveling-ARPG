#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P05_TRNS_META.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMetaTranscendenceActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMetaTranscendenceDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnMetaTranscendenceLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMetaTranscendenceMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMetaTranscendencePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMetaTranscendencePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMetaTranscendenceAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP05_TRNS_META : public UActorComponent
{
    GENERATED_BODY()

public:
    UP05_TRNS_META();

    // Meta Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meta Transcendence")
    int32 MetaTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meta Transcendence")
    int32 MaxMetaTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meta Transcendence")
    bool bIsMetaTranscendenceActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meta Transcendence")
    float MetaTranscendencePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meta Transcendence")
    float MetaTranscendenceThreshold;

    // Meta Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meta Transcendence")
    float MetaRealityDominion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meta Transcendence")
    float TranscendenceRecursion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meta Transcendence")
    float MetaInfiniteConsciousness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meta Transcendence")
    float ConceptualEvolution;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meta Transcendence")
    float MetaTranscendenceAuthority;

    // Meta Transcendence Events
    UPROPERTY(BlueprintAssignable, Category = "Meta Transcendence")
    FOnMetaTranscendenceActivated OnMetaTranscendenceActivated;

    UPROPERTY(BlueprintAssignable, Category = "Meta Transcendence")
    FOnMetaTranscendenceDeactivated OnMetaTranscendenceDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Meta Transcendence")
    FOnMetaTranscendenceLevelChanged OnMetaTranscendenceLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Meta Transcendence")
    FOnMetaTranscendenceMaxLevelReached OnMetaTranscendenceMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Meta Transcendence")
    FOnMetaTranscendencePowerUsed OnMetaTranscendencePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Meta Transcendence")
    FOnMetaTranscendencePowerFailed OnMetaTranscendencePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Meta Transcendence")
    FOnMetaTranscendenceAbilityPerformed OnMetaTranscendenceAbilityPerformed);

    // Meta Transcendence Functions
    UFUNCTION(BlueprintCallable, Category = "Meta Transcendence")
    void ActivateMetaTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Meta Transcendence")
    void DeactivateMetaTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Meta Transcendence")
    void SetMetaTranscendenceLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Meta Transcendence")
    void UseMetaTranscendencePower();

    UFUNCTION(BlueprintCallable, Category = "Meta Transcendence")
    void PerformMetaTranscendenceAbility();

    UFUNCTION(BlueprintCallable, Category = "Meta Transcendence")
    bool IsMetaTranscendenceActive() const;

    UFUNCTION(BlueprintCallable, Category = "Meta Transcendence")
    int32 GetMetaTranscendenceLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Meta Transcendence")
    float GetMetaTranscendencePowerCost() const;

    // Meta Transcendence Abilities
    UFUNCTION(BlueprintCallable, Category = "Meta Transcendence")
    void ExerciseMetaRealityDominion();

    UFUNCTION(BlueprintCallable, Category = "Meta Transcendence")
    void TranscendRecursion();

    UFUNCTION(BlueprintCallable, Category = "Meta Transcendence")
    void AccessMetaInfiniteConsciousness();

    UFUNCTION(BlueprintCallable, Category = "Meta Transcendence")
    void EvolveConceptually();

    UFUNCTION(BlueprintCallable, Category = "Meta Transcendence")
    void WieldMetaTranscendenceAuthority();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateMetaTranscendence() const;
    void UpdateMetaTranscendenceStats();
    void OnMetaTranscendenceStateChanged();
};
