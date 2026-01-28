#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COMPLETE_INFINITE_TRANSCENDENCE_SYSTEM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInfiniteTranscendenceActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInfiniteTranscendenceDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnInfiniteTranscendenceLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInfiniteTranscendenceMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInfiniteTranscendencePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInfiniteTranscendencePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInfiniteTranscendenceAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UCOMPLETE_INFINITE_TRANSCENDENCE_SYSTEM : public UActorComponent
{
    GENERATED_BODY()

public:
    UCOMPLETE_INFINITE_TRANSCENDENCE_SYSTEM();

    // Infinite-Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite-Transcendence")
    int32 InfiniteTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite-Transcendence")
    int32 MaxInfiniteTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite-Transcendence")
    bool bIsInfiniteTranscendenceActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite-Transcendence")
    float InfiniteTranscendencePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite-Transcendence")
    float InfiniteTranscendenceThreshold;

    // Infinite-Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite-Transcendence")
    float InfiniteRealityManipulation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite-Transcendence")
    float EternalExistenceControl;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite-Transcendence")
    float OmniversalAwareness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite-Transcendence")
    float InfiniteTimeMastery;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite-Transcendence")
    float AbsoluteConceptualAuthority;

    // Infinite-Transcendence Events
    UPROPERTY(BlueprintAssignable, Category = "Infinite-Transcendence")
    FOnInfiniteTranscendenceActivated OnInfiniteTranscendenceActivated;

    UPROPERTY(BlueprintAssignable, Category = "Infinite-Transcendence")
    FOnInfiniteTranscendenceDeactivated OnInfiniteTranscendenceDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Infinite-Transcendence")
    FOnInfiniteTranscendenceLevelChanged OnInfiniteTranscendenceLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Infinite-Transcendence")
    FOnInfiniteTranscendenceMaxLevelReached OnInfiniteTranscendenceMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Infinite-Transcendence")
    FOnInfiniteTranscendencePowerUsed OnInfiniteTranscendencePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Infinite-Transcendence")
    FOnInfiniteTranscendencePowerFailed OnInfiniteTranscendencePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Infinite-Transcendence")
    FOnInfiniteTranscendenceAbilityPerformed OnInfiniteTranscendenceAbilityPerformed;

    // Infinite-Transcendence Functions
    UFUNCTION(BlueprintCallable, Category = "Infinite-Transcendence")
    void ActivateInfiniteTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Infinite-Transcendence")
    void DeactivateInfiniteTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Infinite-Transcendence")
    void SetInfiniteTranscendenceLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Infinite-Transcendence")
    void UseInfiniteTranscendencePower();

    UFUNCTION(BlueprintCallable, Category = "Infinite-Transcendence")
    void PerformInfiniteTranscendenceAbility();

    UFUNCTION(BlueprintCallable, Category = "Infinite-Transcendence")
    bool IsInfiniteTranscendenceActive() const;

    UFUNCTION(BlueprintCallable, Category = "Infinite-Transcendence")
    int32 GetInfiniteTranscendenceLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Infinite-Transcendence")
    float GetInfiniteTranscendencePowerCost() const;

    // Infinite-Transcendence Abilities
    UFUNCTION(BlueprintCallable, Category = "Infinite-Transcendence")
    void ManipulateInfiniteReality();

    UFUNCTION(BlueprintCallable, Category = "Infinite-Transcendence")
    void ControlEternalExistence();

    UFUNCTION(BlueprintCallable, Category = "Infinite-Transcendence")
    void AccessOmniversalAwareness();

    UFUNCTION(BlueprintCallable, Category = "Infinite-Transcendence")
    void MasterInfiniteTime();

    UFUNCTION(BlueprintCallable, Category = "Infinite-Transcendence")
    void ExerciseConceptualAuthority();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateInfiniteTranscendence() const;
    void UpdateInfiniteTranscendenceStats();
    void OnInfiniteTranscendenceStateChanged();
};
