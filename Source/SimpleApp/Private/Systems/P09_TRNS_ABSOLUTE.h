#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P09_TRNS_ABSOLUTE.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbsoluteTranscendenceActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbsoluteTranscendenceDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnAbsoluteTranscendenceLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbsoluteTranscendenceMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbsoluteTranscendencePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbsoluteTranscendencePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbsoluteTranscendenceAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP09_TRNS_ABSOLUTE : public UActorComponent
{
    GENERATED_BODY()

public:
    UP09_TRNS_ABSOLUTE();

    // Absolute Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute Transcendence")
    int32 AbsoluteTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute Transcendence")
    int32 MaxAbsoluteTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute Transcendence")
    bool bIsAbsoluteTranscendenceActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute Transcendence")
    float AbsoluteTranscendencePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute Transcendence")
    float AbsoluteTranscendenceThreshold;

    // Absolute Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute Transcendence")
    float AbsoluteRealityDominion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute Transcendence")
    float AbsoluteTranscendenceRecursion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute Transcendence")
    float AbsoluteInfiniteConsciousness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute Transcendence")
    float AbsoluteConceptualEvolution;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute Transcendence")
    float AbsoluteTranscendenceAuthority;

    // Absolute Transcendence Events
    UPROPERTY(BlueprintAssignable, Category = "Absolute Transcendence")
    FOnAbsoluteTranscendenceActivated OnAbsoluteTranscendenceActivated;

    UPROPERTY(BlueprintAssignable, Category = "Absolute Transcendence")
    FOnAbsoluteTranscendenceDeactivated OnAbsoluteTranscendenceDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Absolute Transcendence")
    FOnAbsoluteTranscendenceLevelChanged OnAbsoluteTranscendenceLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Absolute Transcendence")
    FOnAbsoluteTranscendenceMaxLevelReached OnAbsoluteTranscendenceMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Absolute Transcendence")
    FOnAbsoluteTranscendencePowerUsed OnAbsoluteTranscendencePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Absolute Transcendence")
    FOnAbsoluteTranscendencePowerFailed OnAbsoluteTranscendencePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Absolute Transcendence")
    FOnAbsoluteTranscendenceAbilityPerformed OnAbsoluteTranscendenceAbilityPerformed;

    // Absolute Transcendence Functions
    UFUNCTION(BlueprintCallable, Category = "Absolute Transcendence")
    void ActivateAbsoluteTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Absolute Transcendence")
    void DeactivateAbsoluteTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Absolute Transcendence")
    void SetAbsoluteTranscendenceLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Absolute Transcendence")
    void UseAbsoluteTranscendencePower();

    UFUNCTION(BlueprintCallable, Category = "Absolute Transcendence")
    void PerformAbsoluteTranscendenceAbility();

    UFUNCTION(BlueprintCallable, Category = "Absolute Transcendence")
    bool IsAbsoluteTranscendenceActive() const;

    UFUNCTION(BlueprintCallable, Category = "Absolute Transcendence")
    int32 GetAbsoluteTranscendenceLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Absolute Transcendence")
    float GetAbsoluteTranscendencePowerCost() const;

    // Absolute Transcendence Abilities
    UFUNCTION(BlueprintCallable, Category = "Absolute Transcendence")
    void ExerciseAbsoluteRealityDominion();

    UFUNCTION(BlueprintCallable, Category = "Absolute Transcendence")
    void TranscendAbsoluteRecursion();

    UFUNCTION(BlueprintCallable, Category = "Absolute Transcendence")
    void AccessAbsoluteInfiniteConsciousness();

    UFUNCTION(BlueprintCallable, Category = "Absolute Transcendence")
    void EvolveConceptually();

    UFUNCTION(BlueprintCallable, Category = "Absolute Transcendence")
    void WieldAbsoluteTranscendenceAuthority();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateAbsoluteTranscendence() const;
    void UpdateAbsoluteTranscendenceStats();
    void OnAbsoluteTranscendenceStateChanged();
};
