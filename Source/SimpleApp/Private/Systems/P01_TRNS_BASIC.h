#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P01_TRNS_BASIC.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBasicTranscendenceActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBasicTranscendenceDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnBasicTranscendenceLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBasicTranscendenceMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBasicTranscendencePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBasicTranscendencePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBasicTranscendenceAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP01_TRNS_BASIC : public UActorComponent
{
    GENERATED_BODY()

public:
    UP01_TRNS_BASIC();

    // Basic Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic Transcendence")
    int32 BasicTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic Transcendence")
    int32 MaxBasicTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic Transcendence")
    bool bIsBasicTranscendenceActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic Transcendence")
    float BasicTranscendencePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic Transcendence")
    float BasicTranscendenceThreshold;

    // Basic Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic Transcendence")
    float TranscendencePower;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic Transcendence")
    float RealityManipulation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic Transcendence")
    float EssenceControl;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic Transcendence")
    float DimensionalShift;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic Transcendence")
    float TimeControl;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic Transcendence")
    float ExistenceOverride;

    // Basic Transcendence Events
    UPROPERTY(BlueprintAssignable, Category = "Basic Transcendence")
    FOnBasicTranscendenceActivated OnBasicTranscendenceActivated;

    UPROPERTY(BlueprintAssignable, Category = "Basic Transcendence")
    FOnBasicTranscendenceDeactivated OnBasicTranscendenceDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Basic Transcendence")
    FOnBasicTranscendenceLevelChanged OnBasicTranscendenceLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Basic Transcendence")
    FOnBasicTranscendenceMaxLevelReached OnBasicTranscendenceMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Basic Transcendence")
    FOnBasicTranscendencePowerUsed OnBasicTranscendencePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Basic Transcendence")
    FOnBasicTranscendencePowerFailed OnBasicTranscendencePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Basic Transcendence")
    FOnBasicTranscendenceAbilityPerformed OnBasicTranscendenceAbilityPerformed;

    // Basic Transcendence Functions
    UFUNCTION(BlueprintCallable, Category = "Basic Transcendence")
    void ActivateBasicTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Basic Transcendence")
    void DeactivateBasicTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Basic Transcendence")
    void SetBasicTranscendenceLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Basic Transcendence")
    void UseBasicTranscendencePower();

    UFUNCTION(BlueprintCallable, Category = "Basic Transcendence")
    void PerformBasicTranscendenceAbility();

    UFUNCTION(BlueprintCallable, Category = "Basic Transcendence")
    bool IsBasicTranscendenceActive() const;

    UFUNCTION(BlueprintCallable, Category = "Basic Transcendence")
    int32 GetBasicTranscendenceLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Basic Transcendence")
    float GetBasicTranscendencePowerCost() const;

    // Basic Transcendence Abilities
    UFUNCTION(BlueprintCallable, Category = "Basic Transcendence")
    void ManipulateReality();

    UFUNCTION(BlueprintCallable, Category = "Basic Transcendence")
    void ControlEssence();

    UFUNCTION(BlueprintCallable, Category = "Basic Transcendence")
    void ShiftDimensions();

    UFUNCTION(BlueprintCallable, Category = "Basic Transcendence")
    void ControlTime();

    UFUNCTION(BlueprintCallable, Category = "Basic Transcendence")
    void OverrideExistence();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateBasicTranscendence() const;
    void UpdateBasicTranscendenceStats();
    void OnBasicTranscendenceStateChanged();
};
