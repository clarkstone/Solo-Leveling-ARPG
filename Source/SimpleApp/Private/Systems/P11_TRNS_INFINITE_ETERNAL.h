#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P11_TRNS_INFINITE_ETERNAL.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInfiniteEternalTranscendenceActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInfiniteEternalTranscendenceDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnInfiniteEternalTranscendenceLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInfiniteEternalTranscendenceMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInfiniteEternalTranscendencePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInfiniteEternalTranscendencePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInfiniteEternalTranscendenceAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP11_TRNS_INFINITE_ETERNAL : public UActorComponent
{
    GENERATED_BODY()

public:
    UP11_TRNS_INFINITE_ETERNAL();

    // Infinite Eternal Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Eternal Transcendence")
    int32 InfiniteEternalTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Eternal Transcendence")
    int32 MaxInfiniteEternalTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Eternal Transcendence")
    bool bIsInfiniteEternalTranscendenceActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Eternal Transcendence")
    float InfiniteEternalTranscendencePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Eternal Transcendence")
    float InfiniteEternalTranscendenceThreshold;

    // Infinite Eternal Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Eternal Transcendence")
    float InfiniteEternalRealityDominion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Eternal Transcendence")
    float InfiniteEternalTranscendenceRecursion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Eternal Transcendence")
    float InfiniteEternalInfiniteConsciousness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Eternal Transcendence")
    float InfiniteEternalConceptualEvolution;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Eternal Transcendence")
    float InfiniteEternalTranscendenceAuthority;

    // Infinite Eternal Transcendence Events
    UPROPERTY(BlueprintAssignable, Category = "Infinite Eternal Transcendence")
    FOnInfiniteEternalTranscendenceActivated OnInfiniteEternalTranscendenceActivated;

    UPROPERTY(BlueprintAssignable, Category = "Infinite Eternal Transcendence")
    FOnInfiniteEternalTranscendenceDeactivated OnInfiniteEternalTranscendenceDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Infinite Eternal Transcendence")
    FOnInfiniteEternalTranscendenceLevelChanged OnInfiniteEternalTranscendenceLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Infinite Eternal Transcendence")
    FOnInfiniteEternalTranscendenceMaxLevelReached OnInfiniteEternalTranscendenceMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Infinite Eternal Transcendence")
    FOnInfiniteEternalTranscendencePowerUsed OnInfiniteEternalTranscendencePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Infinite Eternal Transcendence")
    FOnInfiniteEternalTranscendencePowerFailed OnInfiniteEternalTranscendencePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Infinite Eternal Transcendence")
    FOnInfiniteEternalTranscendenceAbilityPerformed OnInfiniteEternalTranscendenceAbilityPerformed;

    // Infinite Eternal Transcendence Functions
    UFUNCTION(BlueprintCallable, Category = "Infinite Eternal Transcendence")
    void ActivateInfiniteEternalTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Infinite Eternal Transcendence")
    void DeactivateInfiniteEternalTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Infinite Eternal Transcendence")
    void SetInfiniteEternalTranscendenceLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Infinite Eternal Transcendence")
    void UseInfiniteEternalTranscendencePower();

    UFUNCTION(BlueprintCallable, Category = "Infinite Eternal Transcendence")
    void PerformInfiniteEternalTranscendenceAbility();

    UFUNCTION(BlueprintCallable, Category = "Infinite Eternal Transcendence")
    bool IsInfiniteEternalTranscendenceActive() const;

    UFUNCTION(BlueprintCallable, Category = "Infinite Eternal Transcendence")
    int32 GetInfiniteEternalTranscendenceLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Infinite Eternal Transcendence")
    float GetInfiniteEternalTranscendencePowerCost() const;

    // Infinite Eternal Transcendence Abilities
    UFUNCTION(BlueprintCallable, Category = "Infinite Eternal Transcendence")
    void ExerciseInfiniteEternalRealityDominion();

    UFUNCTION(BlueprintCallable, Category = "Infinite Eternal Transcendence")
    void TranscendInfiniteEternalRecursion();

    UFUNCTION(BlueprintCallable, Category = "Infinite Eternal Transcendence")
    void AccessInfiniteEternalInfiniteConsciousness();

    UFUNCTION(BlueprintCallable, Category = "Infinite Eternal Transcendence")
    void EvolveConceptually();

    UFUNCTION(BlueprintCallable, Category = "Infinite Eternal Transcendence")
    void WieldInfiniteEternalTranscendenceAuthority();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateInfiniteEternalTranscendence() const;
    void UpdateInfiniteEternalTranscendenceStats();
    void OnInfiniteEternalTranscendenceStateChanged();
};
