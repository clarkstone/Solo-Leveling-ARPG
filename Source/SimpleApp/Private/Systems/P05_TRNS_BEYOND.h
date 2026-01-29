#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P05_TRNS_BEYOND.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeyondTranscendenceActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeyondTranscendenceDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnBeyondTranscendenceLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBeyondTranscendenceMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeyondTranscendencePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBeyondTranscendencePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBeyondTranscendenceAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP05_TRNS_BEYOND : public UActorComponent
{
    GENERATED_BODY()

public:
    UP05_TRNS_BEYOND();

    // Beyond Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beyond Transcendence")
    int32 BeyondTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beyond Transcendence")
    int32 MaxBeyondTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beyond Transcendence")
    bool bIsBeyondTranscendenceActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beyond Transcendence")
    float BeyondTranscendencePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beyond Transcendence")
    float BeyondTranscendenceThreshold;

    // Beyond Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beyond Transcendence")
    float BeyondTranscendencePower;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beyond Transcendence")
    float BeyondRealityDominion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beyond Transcendence")
    float BeyondTranscendenceRecursion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beyond Transcendence)
    float BeyondInfiniteConsciousness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beyond Transcendence")
    float BeyondConceptualEvolution;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Beyond Transcendence")
    float BeyondTranscendenceAuthority;

    // Beyond Transcendence Events
    UPROPERTY(BlueprintAssignable, Category = "Beyond Transcendence")
    FOnBeyondTranscendenceActivated OnBeyondTranscendenceActivated;

    UPROPERTY(BlueprintAssignable, Category = "Beyond Transcendence")
    FOnBeyondTranscendenceDeactivated OnBeyondTranscendenceDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Beyond Transcendence")
    FOnBeyondTranscendenceLevelChanged OnBeyondTranscendenceLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Beyond Transcendence")
    FOnBeyondTranscendenceMaxLevelReached OnBeyondTranscendenceMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Beyond Transcendence")
    FOnBeyondTranscendencePowerUsed OnBeyondTranscendencePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Beyond Transcendence")
    FOnBeyondTranscendencePowerFailed OnBeyondTranscendencePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Beyond Transcendence")
    FOnBeyondTranscendenceAbilityPerformed OnBeyondTranscendenceAbilityPerformed;

    // Beyond Transcendence Functions
    UFUNCTION(BlueprintCallable, Category = "Beyond Transcendence")
    void ActivateBeyondTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Beyond Transcendence")
    void DeactivateBeyondTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Beyond Transcendence")
    void SetBeyondTranscendenceLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Beyond Transcendence")
    void UseBeyondTranscendencePower();

    UFUNCTION(BlueprintCallable, Category = "Beyond Transcendence")
    void PerformBeyondTranscendenceAbility();

    UFUNCTION(BlueprintCallable, Category = "Beyond Transcendence")
    bool IsBeyondTranscendenceActive() const;

    UFUNCTION(BlueprintCallable, Category = "Beyond Transcendence")
    int32 GetBeyondTranscendenceLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Beyond Transcendence")
    float GetBeyondTranscendencePowerCost() const;

    // Beyond Transcendence Abilities
    UFUNCTION(BlueprintCallable, Category = "Beyond Transcendence")
    void ExerciseBeyondRealityDominion();

    UFUNCTION(BlueprintCallable, Category = "Beyond Transcendence")
    void TranscendBeyondRecursion();

    UFUNCTION(BlueprintCallable, Category = "Beyond Transcendence")
    void AccessBeyondConsciousness();

    UFUNCTION(BlueprintCallable, Category = "Beyond Transcendence")
    void EvolveBeyondConceptually();

    UFUNCTION(BlueprintCallable, Category = "Beyond Transcendence")
    void WieldBeyondTranscendenceAuthority();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateBeyondTranscendence() const;
    void UpdateBeyondTranscendenceStats();
    void OnBeyondTranscendenceStateChanged();
};
