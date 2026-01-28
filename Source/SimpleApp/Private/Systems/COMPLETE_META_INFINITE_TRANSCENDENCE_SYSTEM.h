#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COMPLETE_META_INFINITE_TRANSCENDENCE_SYSTEM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMetaInfiniteTranscendenceActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMetaInfiniteTranscendenceDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnMetaInfiniteTranscendenceLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMetaInfiniteTranscendenceMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMetaInfiniteTranscendencePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMetaInfiniteTranscendencePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMetaInfiniteTranscendenceAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UCOMPLETE_META_INFINITE_TRANSCENDENCE_SYSTEM : public UActorComponent
{
    GENERATED_BODY()

public:
    UCOMPLETE_META_INFINITE_TRANSCENDENCE_SYSTEM();

    // Meta-Infinite-Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meta-Infinite-Transcendence")
    int32 MetaInfiniteTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meta-Infinite-Transcendence")
    int32 MaxMetaInfiniteTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meta-Infinite-Transcendence")
    bool bIsMetaInfiniteTranscendenceActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meta-Infinite-Transcendence")
    float MetaInfiniteTranscendencePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meta-Infinite-Transcendence")
    float MetaInfiniteTranscendenceThreshold;

    // Meta-Infinite-Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meta-Infinite-Transcendence")
    float MetaRealitySovereignty;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meta-Infinite-Transcendence")
    float TranscendenceBeyondTranscendence;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meta-Infinite-Transcendence")
    float InfiniteMetaAwareness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meta-Infinite-Transcendence")
    float ConceptualMetamorphosis;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Meta-Infinite-Transcendence")
    float AbsoluteMetaAuthority;

    // Meta-Infinite-Transcendence Events
    UPROPERTY(BlueprintAssignable, Category = "Meta-Infinite-Transcendence")
    FOnMetaInfiniteTranscendenceActivated OnMetaInfiniteTranscendenceActivated;

    UPROPERTY(BlueprintAssignable, Category = "Meta-Infinite-Transcendence")
    FOnMetaInfiniteTranscendenceDeactivated OnMetaInfiniteTranscendenceDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Meta-Infinite-Transcendence")
    FOnMetaInfiniteTranscendenceLevelChanged OnMetaInfiniteTranscendenceLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Meta-Infinite-Transcendence")
    FOnMetaInfiniteTranscendenceMaxLevelReached OnMetaInfiniteTranscendenceMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Meta-Infinite-Transcendence")
    FOnMetaInfiniteTranscendencePowerUsed OnMetaInfiniteTranscendencePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Meta-Infinite-Transcendence")
    FOnMetaInfiniteTranscendencePowerFailed OnMetaInfiniteTranscendencePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Meta-Infinite-Transcendence")
    FOnMetaInfiniteTranscendenceAbilityPerformed OnMetaInfiniteTranscendenceAbilityPerformed;

    // Meta-Infinite-Transcendence Functions
    UFUNCTION(BlueprintCallable, Category = "Meta-Infinite-Transcendence")
    void ActivateMetaInfiniteTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Meta-Infinite-Transcendence")
    void DeactivateMetaInfiniteTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Meta-Infinite-Transcendence")
    void SetMetaInfiniteTranscendenceLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Meta-Infinite-Transcendence")
    void UseMetaInfiniteTranscendencePower();

    UFUNCTION(BlueprintCallable, Category = "Meta-Infinite-Transcendence")
    void PerformMetaInfiniteTranscendenceAbility();

    UFUNCTION(BlueprintCallable, Category = "Meta-Infinite-Transcendence")
    bool IsMetaInfiniteTranscendenceActive() const;

    UFUNCTION(BlueprintCallable, Category = "Meta-Infinite-Transcendence")
    int32 GetMetaInfiniteTranscendenceLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Meta-Infinite-Transcendence")
    float GetMetaInfiniteTranscendencePowerCost() const;

    // Meta-Infinite-Transcendence Abilities
    UFUNCTION(BlueprintCallable, Category = "Meta-Infinite-Transcendence")
    void ExerciseMetaRealitySovereignty();

    UFUNCTION(BlueprintCallable, Category = "Meta-Infinite-Transcendence")
    void TranscendBeyondTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Meta-Infinite-Transcendence")
    void AccessInfiniteMetaAwareness();

    UFUNCTION(BlueprintCallable, Category = "Meta-Infinite-Transcendence")
    void UndergoConceptualMetamorphosis();

    UFUNCTION(BlueprintCallable, Category = "Meta-Infinite-Transcendence")
    void WieldAbsoluteMetaAuthority();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateMetaInfiniteTranscendence() const;
    void UpdateMetaInfiniteTranscendenceStats();
    void OnMetaInfiniteTranscendenceStateChanged();
};
