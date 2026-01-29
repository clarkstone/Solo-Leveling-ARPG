#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P08_TRNS_SUPREME.generated.h"

DECLARE_DYNAMIC_MULTICAST_DEGREED_ONEParam(FOnSupremeTranscendenceActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSupremeTranscendenceDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnSupremeTranscendenceLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSupremeTranscendenceMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSupremeTranscendencePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSupremeTranscendencePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSupremeTranscendenceAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP08_TRNS_SUPREME : public UActorComponent
{
    GENERATED_BODY()

public:
    UP08_TRNS_SUPREME();

    // Supreme Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme Transcendence")
    int32 SupremeTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme Transcendence")
    int32 MaxSupremeTranscendenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme Transcendence")
    bool bIsSupremeTranscendenceActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme Transcendence")
    float SupremeTranscendencePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme Transcendence")
    float SupremeTranscendenceThreshold;

    // Supreme Transcendence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme Transcendence")
    float SupremeRealityDominion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme Transcendence")
    float SupremeTranscendenceRecursion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme Transcendence")
    float SupremeInfiniteConsciousness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme Transcendence")
    float SupremeConceptualEvolution;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme Transcendence")
    float SupremeTranscendenceAuthority;

    // Supreme Transcendence Events
    UPROPERTY(BlueprintAssignable, Category = "Supreme Transcendence")
    FOnSupremeTranscendenceActivated OnSupremeTranscendenceActivated;

    UPROPERTY(BlueprintAssignable, Category = "Supreme Transcendence")
    FOnSupremeTranscendenceDeactivated OnSupremeTranscendenceDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Supreme Transcendence")
    FOnSupremeTranscendenceLevelChanged OnSupremeTranscendenceLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Supreme Transcendence")
    FOnSupremeTranscendenceMaxLevelReached OnSupremeTranscendenceMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Supreme Transcendence")
    FOnSupremeTranscendencePowerUsed OnSupremeTranscendencePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Supreme Transcendence")
    FOnSupremeTranscendencePowerFailed OnSupremeTranscendencePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Supreme Transcendence")
    FOnSupremeTranscendenceAbilityPerformed OnSupremeTranscendenceAbilityPerformed);

    // Supreme Transcendence Functions
    UFUNCTION(BlueprintCallable, Category = "Supreme Transcendence")
    void ActivateSupremeTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Supreme Transcendence")
    void DeactivateSupremeTranscendence();

    UFUNCTION(BlueprintCallable, Category = "Supreme Transcendence")
    void SetSupremeTranscendenceLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Supreme Transcendence")
    void UseSupremeTranscendencePower();

    UFUNCTION(BlueprintCallable, Category = "Supreme Transcendence")
    void PerformSupremeTranscendenceAbility();

    UFUNCTION(BlueprintCallable, Category = "Supreme Transcendence")
    bool IsSupremeTranscendenceActive() const;

    UFUNCTION(BlueprintCallable, Category = "Supreme Transcendence")
    int32 GetSupremeTranscendenceLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Supreme Transcendence")
    float GetSupremeTranscendencePowerCost() const;

    // Supreme Transcendence Abilities
    UFUNCTION(BlueprintCallable, Category = "Supreme Transcendence")
    void ExerciseSupremeRealityDominion();

    UFUNCTION(BlueprintCallable, Category = "Supreme Transcendence")
    void TranscendSupremeRecursion();

    UFUNCTION(BlueprintCallable, Category = "Supreme Transcendence")
    void AccessSupremeInfiniteConsciousness();

    UFUNCTION(BlueprintCallable, Category = "Supreme Transcendence")
    void EvolveConceptually();

    UFUNCTION(BlueprintCallable, Category = "Supreme Transcendence")
    void WieldSupremeTranscendenceAuthority();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateSupremeTranscendence() const;
    void UpdateSupremeTranscendenceStats();
    void OnSupremeTranscendenceStateChanged();
};
