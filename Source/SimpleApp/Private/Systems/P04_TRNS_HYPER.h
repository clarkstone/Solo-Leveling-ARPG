#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P04_TRNS_HYPER.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHyperTranscendenceActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHyperTranscendenceDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnHyperTranscendenceLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHyperTranscendenceMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHyperTranscendencePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHyperTranscendencePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHyperTranscendenceAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP04_TRNS_HYPER : public UActorComponent
{
    GENERATED_BODY()

public:
    UP04_TRNS_HYPER();

    // Hyper Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper Transcendence")
    int32 HyperTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper Transcendence")
    int32 MaxHyperTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper Transcendence")
    bool bIsHyperTranscendenceActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper Transcendence")
    float HyperTranscendencePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper Transcendence")
    float HyperTranscendenceThreshold;

    // Hyper Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper Transcendence")
    float HyperTranscendencePower;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper Transcendence")
    float HyperRealityDominion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper Transcendence")
    float HyperTranscendenceRecursion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper Transcendence")
    float HyperInfiniteConsciousness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper Transcendence")
    float HyperConceptualEvolution;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper Transcendence")
    float HyperTranscendenceAuthority;

    // Hyper Transcendence Events
    UPROPERTY(BlueprintAssignable, Category = "Hyper Transcendence")
    FOnHyperTranscendenceActivated OnHyperTranscendenceActivated;

    UPROPERTY(BlueprintAssignable, Category = "Hyper Transcendence")
    FOnHyperTranscendenceDeactivated OnHyperTranscendenceDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Hyper Transcendence")
    FOnHyperTranscendenceLevelChanged OnHyperTranscendenceLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Hyper Transcendence")
    FOnHyperTranscendenceMaxLevelReached OnHyperTranscendenceMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Hyper Transcendence")
    FOnHyperTranscendencePowerUsed OnHyperTranscendencePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Hyper Transcendence")
    FOnHyperTranscendencePowerFailed OnHyperTranscendencePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Hyper Transcendence")
    FOnHyperTranscendenceAbilityPerformed OnHyperTranscendenceAbilityPerformed;

    // Hyper Transcendence Functions
    UFUNCTION(BlueprintCallable, Category = "Hyper Transcendence")
    void ActivateHyperTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Hyper Transcendence")
    void DeactivateHyperTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Hyper Transcendence")
    void SetHyperTranscendenceLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Hyper Transcendence")
    void UseHyperTranscendencePower();

    UFUNCTION(BlueprintCallable, Category = "Hyper Transcendence")
    void PerformHyperTranscendenceAbility();

    UFUNCTION(BlueprintCallable, Category = "Hyper Transcendence")
    bool IsHyperTranscendenceActive() const;

    UFUNCTION(BlueprintCallable, Category = "Hyper Transcendence")
    int32 GetHyperTranscendenceLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Hyper Transcendence")
    float GetHyperTranscendencePowerCost() const;

    // Hyper Transcendence Abilities
    UFUNCTION(BlueprintCallable, Category = "Hyper Transcendence")
    void ExerciseHyperRealityDominion();

    UFUNCTION(BlueprintCallable, Category = "Hyper Transcendence")
    void TranscendHyperRecursion();

    UFUNCTION(BlueprintCallable, Category = "Hyper Transcendence")
    void AccessHyperInfiniteConsciousness();

    UFUNCTION(BlueprintCallable, Category = "Hyper Transcendence")
    void EvolveHyperConceptually();

    UFUNCTION(BlueprintCallable, Category = "Hyper Transcendence")
    void WieldHyperTranscendenceAuthority();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateHyperTranscendence() const;
    void UpdateHyperTranscendenceStats();
    void OnHyperTranscendenceStateChanged();
};
