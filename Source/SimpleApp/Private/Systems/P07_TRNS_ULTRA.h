#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P07_TRNS_ULTRA.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltraTranscendenceActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltraTranscendenceDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnUltraTranscendenceLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUltraTranscendenceMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltraTranscendencePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUltraTranscendencePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltraTranscendenceAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP07_TRNS_ULTRA : public UActorComponent
{
    GENERATED_BODY()

public:
    UP07_TRNS_ULTRA();

    // Ultra Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Transcendence")
    int32 UltraTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Transcendence")
    int32 MaxUltraTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Transcendence")
    bool bIsUltraTranscendenceActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Transcendence")
    float UltraTranscendencePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Transcendence")
    float UltraTranscendenceThreshold;

    // Ultra Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Transcendence")
    float UltraTranscendencePower;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Transcendence")
    float UltraRealityDominion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Transcendence")
    float UltraTranscendenceRecursion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Transcendence")
    float UltraInfiniteConsciousness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Transcendence")
    float UltraConceptualEvolution;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Transcendence")
    float UltraTranscendenceAuthority;

    // Ultra Transcendence Events
    UPROPERTY(BlueprintAssignable, Category = "Ultra Transcendence")
    FOnUltraTranscendenceActivated OnUltraTranscendenceActivated;

    UPROPERTY(BlueprintAssignable, Category = "Ultra Transcendence")
    FOnUltraTranscendenceDeactivated OnUltraTranscendenceDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Ultra Transcendence")
    FOnUltraTranscendenceLevelChanged OnUltraTranscendenceLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Ultra Transcendence")
    FOnUltraTranscendenceMaxLevelReached OnUltraTranscendenceMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Ultra Transcendence")
    FOnUltraTranscendencePowerUsed OnUltraTranscendencePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Ultra Transcendence")
    FOnUltraTranscendencePowerFailed OnUltraTranscendencePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Ultra Transcendence")
    FOnUltraTranscendenceAbilityPerformed OnUltraTranscendenceAbilityPerformed;

    // Ultra Transcendence Functions
    UFUNCTION(BlueprintCallable, Category = "Ultra Transcendence")
    void ActivateUltraTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Ultra Transcendence")
    void DeactivateUltraTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Ultra Transcendence")
    void SetUltraTranscendenceLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Ultra Transcendence")
    void UseUltraTranscendencePower();

    UFUNCTION(BlueprintCallable, Category = "Ultra Transcendence")
    void PerformUltraTranscendenceAbility();

    UFUNCTION(BlueprintCallable, Category = "Ultra Transcendence")
    bool IsUltraTranscendenceActive() const;

    UFUNCTION(BlueprintCallable, Category = "Ultra Transcendence")
    int32 GetUltraTranscendenceLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Ultra Transcendence")
    float GetUltraTranscendencePowerCost() const;

    // Ultra Transcendence Abilities
    UFUNCTION(BlueprintCallable, Category = "Ultra Transcendence")
    void ExerciseUltraRealityDominion();

    UFUNCTION(BlueprintCallable, Category = "Ultra Transcendence")
    void TranscendUltraRecursion();

    UFUNCTION(BlueprintCallable, Category = "Ultra Transcendence")
    void AccessUltraInfiniteConsciousness();

    UFUNCTION(BlueprintCallable, Category = "Ultra Transcendence")
    void EvolveUltraConceptually();

    UFUNCTION(BlueprintCallable, Category = "Ultra Transcendence")
    void WieldUltraTranscendenceAuthority();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateUltraTranscendence() const;
    void UpdateUltraTranscendenceStats();
    void OnUltraTranscendenceStateChanged();
};
