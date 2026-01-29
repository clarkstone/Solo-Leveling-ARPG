#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P03_CORE_WORLD_EXP.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWorldExpansionActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWorldExpansionDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnWorldExpansionLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWorldExpansionMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWorldExpansionPowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWorldExpansionPowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWorldExpansionAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP03_CORE_WORLD_EXP : public UActorComponent
{
    GENERATED_BODY()

public:
    UP03_CORE_WORLD_EXP();

    // World Expansion Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Expansion")
    int32 WorldExpansionLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Expansion")
    int32 MaxWorldExpansionLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Expansion")
    bool bIsWorldExpansionActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Expansion")
    float WorldExpansionPowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Expansion")
    float WorldExpansionThreshold;

    // World Expansion Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Expansion")
    float WorldCreation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Expansion")
    float DimensionalExpansion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Expansion")
    float RealityManipulation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Expansion")
    float WorldControl;

    // World Expansion Events
    UPROPERTY(BlueprintAssignable, Category = "World Expansion")
    FOnWorldExpansionActivated OnWorldExpansionActivated;

    UPROPERTY(BlueprintAssignable, Category = "World Expansion")
    FOnWorldExpansionDeactivated OnWorldExpansionDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "World Expansion")
    FOnWorldExpansionLevelChanged OnWorldExpansionLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "World Expansion")
    FOnWorldExpansionMaxLevelReached OnWorldExpansionMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "World Expansion")
    FOnWorldExpansionPowerUsed OnWorldExpansionPowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "World Expansion")
    FOnWorldExpansionPowerFailed OnWorldExpansionPowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "World Expansion")
    FOnWorldExpansionAbilityPerformed OnWorldExpansionAbilityPerformed;

    // World Expansion Functions
    UFUNCTION(BlueprintCallable, Category = "World Expansion")
    void ActivateWorldExpansion();

    UFUNCTION(BlueprintCallable, Category = "World Expansion")
    void DeactivateWorldExpansion();

    UFUNCTION(BlueprintCallable, Category = "World Expansion")
    void SetWorldExpansionLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "World Expansion")
    void UseWorldExpansionPower();

    UFUNCTION(BlueprintCallable, Category = "World Expansion")
    void PerformWorldExpansionAbility();

    UFUNCTION(BlueprintCallable, Category = "World Expansion")
    bool IsWorldExpansionActive() const;

    UFUNCTION(BlueprintCallable, Category = "World Expansion")
    int32 GetWorldExpansionLevel() const;

    UFUNCTION(BlueprintCallable, Category = "World Expansion")
    float GetWorldExpansionPowerCost() const;

    // World Expansion Abilities
    UFUNCTION(BlueprintCallable, Category = "World Expansion")
    void CreateWorlds();

    UFUNCTION(BlueprintCallable, Category = "World Expansion")
    void ExpandDimensions();

    UFUNCTION(BlueprintCallable, Category = "World Expansion")
    void ManipulateReality();

    UFUNCTION(BlueprintCallable, Category = "World Expansion")
    void ControlWorld();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateWorldExpansion() const;
    void UpdateWorldExpansionStats();
    void OnWorldExpansionStateChanged();
};
