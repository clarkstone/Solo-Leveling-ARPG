#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COMPLETE_PERPETUAL_EXISTENCE_SYSTEM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPerpetualExistenceActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPerpetualExistenceDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnPerpetualExistenceLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPerpetualExistenceMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPerpetualExistencePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPerpetualExistencePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPerpetualExistenceAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UCOMPLETE_PERPETUAL_EXISTENCE_SYSTEM : public UActorComponent
{
    GENERATED_BODY()

public:
    UCOMPLETE_PERPETUAL_EXISTENCE_SYSTEM();

    // Perpetual-Existence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Perpetual-Existence")
    int32 PerpetualExistenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Perpetual-Existence")
    int32 MaxPerpetualExistenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Perpetual-Existence")
    bool bIsPerpetualExistenceActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Perpetual-Existence")
    float PerpetualExistencePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Perpetual-Existence")
    float PerpetualExistenceThreshold;

    // Perpetual-Existence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Perpetual-Existence")
    float PerpetualLifeEssence;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Perpetual-Existence")
    float InfiniteSelfRenewal;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Perpetual-Existence")
    float EternalContinuum;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Perpetual-Existence")
    float TimelessPerpetuation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Perpetual-Existence")
    float AbsoluteSelfSufficiency;

    // Perpetual-Existence Events
    UPROPERTY(BlueprintAssignable, Category = "Perpetual-Existence")
    FOnPerpetualExistenceActivated OnPerpetualExistenceActivated;

    UPROPERTY(BlueprintAssignable, Category = "Perpetual-Existence")
    FOnPerpetualExistenceDeactivated OnPerpetualExistenceDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Perpetual-Existence")
    FOnPerpetualExistenceLevelChanged OnPerpetualExistenceLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Perpetual-Existence")
    FOnPerpetualExistenceMaxLevelReached OnPerpetualExistenceMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Perpetual-Existence")
    FOnPerpetualExistencePowerUsed OnPerpetualExistencePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Perpetual-Existence")
    FOnPerpetualExistencePowerFailed OnPerpetualExistencePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Perpetual-Existence")
    FOnPerpetualExistenceAbilityPerformed OnPerpetualExistenceAbilityPerformed;

    // Perpetual-Existence Functions
    UFUNCTION(BlueprintCallable, Category = "Perpetual-Existence")
    void ActivatePerpetualExistence();

    UFUNCTION(BlueprintCallable, Category = "Perpetual-Existence")
    void DeactivatePerpetualExistence();

    UFUNCTION(BlueprintCallable, Category = "Perpetual-Existence")
    void SetPerpetualExistenceLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Perpetual-Existence")
    void UsePerpetualExistencePower();

    UFUNCTION(BlueprintCallable, Category = "Perpetual-Existence")
    void PerformPerpetualExistenceAbility();

    UFUNCTION(BlueprintCallable, Category = "Perpetual-Existence")
    bool IsPerpetualExistenceActive() const;

    UFUNCTION(BlueprintCallable, Category = "Perpetual-Existence")
    int32 GetPerpetualExistenceLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Perpetual-Existence")
    float GetPerpetualExistencePowerCost() const;

    // Perpetual-Existence Abilities
    UFUNCTION(BlueprintCallable, Category = "Perpetual-Existence")
    void ChannelPerpetualLifeEssence();

    UFUNCTION(BlueprintCallable, Category = "Perpetual-Existence")
    void RenewInfinitely();

    UFUNCTION(BlueprintCallable, Category = "Perpetual-Existence")
    void MaintainEternalContinuum();

    UFUNCTION(BlueprintCallable, Category = "Perpetual-Existence")
    void PerpetuateTimelessly();

    UFUNCTION(BlueprintCallable, Category = "Perpetual-Existence")
    void AchieveAbsoluteSelfSufficiency();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivatePerpetualExistence() const;
    void UpdatePerpetualExistenceStats();
    void OnPerpetualExistenceStateChanged();
};
