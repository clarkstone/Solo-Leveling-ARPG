#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P04_TRNS_INFINITE.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInfiniteTranscendenceActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInfiniteTranscendenceDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnInfiniteTranscendenceLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInfiniteTranscendenceMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInfiniteTranscendencePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInfiniteTranscendencePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInfiniteTranscendenceAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP04_TRNS_INFINITE : public UActorComponent
{
    GENERATED_BODY()

public:
    UP04_TRNS_INFINITE();

    // Infinite Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Transcendence")
    int32 InfiniteTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Transcendence")
    int32 MaxInfiniteTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Transcendence")
    bool bIsInfiniteTranscendenceActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Transcendence")
    float InfiniteTranscendencePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Transcendence")
    float InfiniteTranscendenceThreshold;

    // Infinite Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Transcendence")
    float InfiniteTranscendencePower;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Transcendence")
    float InfiniteRealityDominion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Transcendence")
    float InfiniteTranscendenceRecursion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Transcendence")
    float InfiniteInfiniteConsciousness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Transcendence")
    float InfiniteConceptualEvolution;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Transcendence")
    float InfiniteTranscendenceAuthority;

    // Infinite Transcendence Events
    UPROPERTY(BlueprintAssignable, Category = "Infinite Transcendence")
    FOnInfiniteTranscendenceActivated OnInfiniteTranscendenceActivated;

    UPROPERTY(BlueprintAssignable, Category = "Infinite Transcendence")
    FOnInfiniteTranscendenceDeactivated OnInfiniteTranscendenceDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Infinite Transcendence")
    FOnInfiniteTranscendenceLevelChanged OnInfiniteTranscendenceLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Infinite Transcendence")
    FOnInfiniteTranscendenceMaxLevelReached OnInfiniteTranscendenceMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Infinite Transcendence")
    FOnInfiniteTranscendencePowerUsed OnInfiniteTranscendencePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Infinite Transcendence")
    FOnInfiniteTranscendencePowerFailed OnInfiniteTranscendencePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Infinite Transcendence")
    FOnInfiniteTranscendenceAbilityPerformed OnInfiniteTranscendenceAbilityPerformed;

    // Infinite Transcendence Functions
    UFUNCTION(BlueprintCallable, Category = "Infinite Transcendence")
    void ActivateInfiniteTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Infinite Transcendence")
    void DeactivateInfiniteTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Infinite Transcendence")
    void SetInfiniteTranscendenceLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Infinite Transcendence")
    void UseInfiniteTranscendencePower();

    UFUNCTION(BlueprintCallable, Category = "Infinite Transcendence")
    void PerformInfiniteTranscendenceAbility();

    UFUNCTION(BlueprintCallable, Category = "Infinite Transcendence")
    bool IsInfiniteTranscendenceActive() const;

    UFUNCTION(BlueprintCallable, Category = "Infinite Transcendence")
    int32 GetInfiniteTranscendenceLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Infinite Transcendence")
    float GetInfiniteTranscendencePowerCost() const;

    // Infinite Transcendence Abilities
    UFUNCTION(BlueprintCallable, Category = "Infinite Transcendence")
    void ExerciseInfiniteRealityDominion();

    UFUNCTION(BlueprintCallable, Category = "Infinite Transcendence")
    void TranscendInfiniteRecursion();

    UFUNCTION(BlueprintCallable, Category = "Infinite Transcendence")
    void AccessInfiniteConsciousness();

    UFUNCTION(BlueprintCallable, Category = "Infinite Transcendence")
    void EvolveInfiniteConceptually();

    UFUNCTION(BlueprintCallable, Category = "Infinite Transcendence")
    void WieldInfiniteTranscendenceAuthority();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateInfiniteTranscendence() const;
    void UpdateInfiniteTranscendenceStats();
    void OnInfiniteTranscendenceStateChanged();
};
