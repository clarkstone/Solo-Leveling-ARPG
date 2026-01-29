#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P12_EXST_OMEGA_INFINITE_ETERNAL.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOmegaInfiniteEternalExistenceActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOmegaInfiniteEternalExistenceDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnOmegaInfiniteEternalExistenceLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOmegaInfiniteEternalExistenceMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOmegaInfiniteEternalExistencePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOmegaInfiniteEternalExistencePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOmegaInfiniteEternalExistenceAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP12_EXST_OMEGA_INFINITE_ETERNAL : public UActorComponent
{
    GENERATED_BODY()

public:
    UP12_EXST_OMEGA_INFINITE_ETERNAL();

    // Omega Infinite Eternal Existence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Infinite Eternal Existence")
    int32 OmegaInfiniteEternalExistenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Infinite Eternal Existence")
    int32 MaxOmegaInfiniteEternalExistenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Infinite Eternal Existence")
    bool bIsOmegaInfiniteEternalExistenceActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Infinite Eternal Existence")
    float OmegaInfiniteEternalExistencePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Infinite Eternal Existence")
    float OmegaInfiniteEternalExistenceThreshold;

    // Omega Infinite Eternal Existence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Infinite Eternal Existence")
    float OmegaInfiniteEternalLifeForce;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Infinite Eternal Existence")
    float OmegaInfiniteEternalPerpetuation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Infinite Eternal Existence")
    float OmegaInfiniteEternalInfiniteContinuum;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Infinite Eternal Existence")
    float OmegaInfiniteEternalTimelessPerpetuation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Infinite Eternal Existence")
    float OmegaInfiniteEternalSelfSufficiency;

    // Omega Infinite Eternal Existence Events
    UPROPERTY(BlueprintAssignable, Category = "Omega Infinite Eternal Existence")
    FOnOmegaInfiniteEternalExistenceActivated OnOmegaInfiniteEternalExistenceActivated;

    UPROPERTY(BlueprintAssignable, Category = "Omega Infinite Eternal Existence")
    FOnOmegaInfiniteEternalExistenceDeactivated OnOmegaInfiniteEternalExistenceDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Omega Infinite Eternal Existence")
    FOnOmegaInfiniteEternalExistenceLevelChanged OnOmegaInfiniteEternalExistenceLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Omega Infinite Eternal Existence")
    FOnOmegaInfiniteEternalExistenceMaxLevelReached OnOmegaInfiniteEternalExistenceMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Omega Infinite Eternal Existence")
    FOnOmegaInfiniteEternalExistencePowerUsed OnOmegaInfiniteEternalExistencePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Omega Infinite Eternal Existence")
    FOnOmegaInfiniteEternalExistencePowerFailed OnOmegaInfiniteEternalExistencePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Omega Infinite Eternal Existence")
    FOnOmegaInfiniteEternalExistenceAbilityPerformed OnOmegaInfiniteEternalExistenceAbilityPerformed;

    // Omega Infinite Eternal Existence Functions
    UFUNCTION(BlueprintCallable, Category = "Omega Infinite Eternal Existence")
    void ActivateOmegaInfiniteEternalExistence();

    UFUNCTION(BlueprintCallable, Category = "Omega Infinite Eternal Existence")
    void DeactivateOmegaInfiniteEternalExistence();

    UFUNCTION(BlueprintCallable, Category = "Omega Infinite Eternal Existence")
    void SetOmegaInfiniteEternalExistenceLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Omega Infinite Eternal Existence")
    void UseOmegaInfiniteEternalExistencePower();

    UFUNCTION(BlueprintCallable, Category = "Omega Infinite Eternal Existence")
    void PerformOmegaInfiniteEternalExistenceAbility();

    UFUNCTION(BlueprintCallable, Category = "Omega Infinite Eternal Existence")
    bool IsOmegaInfiniteEternalExistenceActive() const;

    UFUNCTION(BlueprintCallable, Category = "Omega Infinite Eternal Existence")
    int32 GetOmegaInfiniteEternalExistenceLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Omega Infinite Eternal Existence")
    float GetOmegaInfiniteEternalExistencePowerCost() const;

    // Omega Infinite Eternal Existence Abilities
    UFUNCTION(BlueprintCallable, Category = "Omega Infinite Eternal Existence")
    void ChannelOmegaInfiniteEternalLifeForce();

    UFUNCTION(BlueprintCallable, Category = "Omega Infinite Eternal Existence")
    void AchieveOmegaInfiniteEternalPerpetuation();

    UFUNCTION(BlueprintCallable, Category = "Omega Infinite Eternal Existence")
    void MaintainOmegaInfiniteEternalInfiniteContinuum();

    UFUNCTION(BlueprintCallable, Category = "Omega Infinite Eternal Existence")
    void PerpetuateOmegaInfiniteEternalTimelessly();

    UFUNCTION(BlueprintCallable, Category = "Omega Infinite Eternal Existence")
    void AchieveOmegaInfiniteEternalSelfSufficiency();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateOmegaInfiniteEternalExistence() const;
    void UpdateOmegaInfiniteEternalExistenceStats();
    void OnOmegaInfiniteEternalExistenceStateChanged();
};
