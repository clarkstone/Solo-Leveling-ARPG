#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P03_CORE_VFX.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVisualEffectsActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVisualEffectsDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnVisualEffectsLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnVisualEffectsMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVisualEffectsPowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnVisualEffectsPowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVisualEffectsAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP03_CORE_VFX : public UActorComponent
{
    GENERATED_BODY()

public:
    UP03_CORE_VFX();

    // Visual Effects Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual Effects")
    int32 VisualEffectsLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual Effects")
    int32 MaxVisualEffectsLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual Effects")
    bool bIsVisualEffectsActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual Effects")
    float VisualEffectsPowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual Effects")
    float VFXPower;

    // Visual Effects Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visual Effects")
    float VFXPower;

    // Visual Effects Events
    UPROPERTY(BlueprintAssignable, Category = "Visual Effects")
    FOnVisualEffectsActivated OnVisualEffectsActivated;

    UPROPERTY(BlueprintAssignable, Category = "Visual Effects")
    FOnVisualEffectsDeactivated OnVisualEffectsDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Visual Effects")
    FOnVisualEffectsLevelChanged OnVisualEffectsLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Visual Effects")
    FOnVisualEffectsMaxLevelReached OnVisualEffectsMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Visual Effects")
    FOnVisualEffectsPowerUsed OnVisualEffectsPowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Visual Effects")
    FOnVisualEffectsPowerFailed OnVisualEffectsPowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Visual Effects")
    FOnVisualEffectsAbilityPerformed OnVisualEffectsAbilityPerformed);

    // Visual Effects Functions
    UFUNCTION(BlueprintCallable, Category = "Visual Effects")
    void ActivateVisualEffects();

    UFUNCTION(BlueprintCallable, Category = "Visual Effects")
    void DeactivateVisualEffects();

    UFUNCTION(BlueprintCallable, Category = "Visual Effects")
    void SetVisualEffectsLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Visual Effects")
    void UseVisualEffectsPower();

    UFUNCTION(BlueprintCallable, Category = "Visual Effects")
    void PerformVisualEffectsAbility();

    UFUNCTION(BlueprintCallable, Category = "Visual Effects")
    bool IsVisualEffectsActive() const;

    UFUNCTION(BlueprintCallable, Category = "Visual Effects")
    int32 GetVisualEffectsLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Visual Effects")
    float GetVisualEffectsPowerCost() const;

    // Visual Effects Abilities
    UFUNCTION(BlueprintCallable, Category = "Visual Effects")
    void ManipulateVisualReality();

    UFUNCTION(BlueprintCallable, Category = "Visual Effects")
    void ControlVisualTime();

    UFUNCTION(BlueprintCallable, Category = "Visual Effects")
    void AlterVisualPerception();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateVisualEffects() const;
    void UpdateVisualEffectsStats();
    void OnVisualEffectsStateChanged();
};
