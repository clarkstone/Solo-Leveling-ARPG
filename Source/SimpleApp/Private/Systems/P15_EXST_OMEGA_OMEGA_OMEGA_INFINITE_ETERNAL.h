#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P15_EXST_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOmegaOmegaInfiniteEternalExistenceActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOmegaOmegaInfiniteEternalExistenceDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnOmegaOmegaInfiniteEternalExistenceLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOmegaOmegaInfiniteEternalExistenceMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOmegaOmegaInfiniteEternalExistencePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOmegaOmegaInfiniteEternalExistencePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOmegaOmegaInfiniteEternalExistenceAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP15_EXST_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL : public UActorComponent
{
    GENERATED_BODY()

public:
    UP15_EXST_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL();

    // Omega Omega Infinite Eternal Existence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Omega Infinite Eternal Existence")
    int32 OmegaOmegaInfiniteEternalExistenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Omega Infinite Eternal Existence")
    int32 MaxOmegaOmegaInfiniteEternalExistenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Omega Infinite Eternal Existence")
    bool bIsOmegaOmegaInfiniteEternalExistenceActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Omega Infinite Eternal Existence")
    float OmegaOmegaInfiniteEternalExistencePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Omega Infinite Eternal Existence")
    float OmegaOmegaInfiniteEternalExistenceThreshold;

    // Omega Omega Infinite Eternal Existence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Omega Infinite Eternal Existence")
    float OmegaOmegaInfiniteEternalLifeForce;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Omega Infinite Eternal Existence")
    float OmegaOmegaInfiniteEternalPerpetuation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Omega Infinite Eternal Existence")
    float OmegaOmegaInfiniteEternalInfiniteContinuum;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Omega Infinite Eternal Existence")
    float OmegaOmegaInfiniteEternalTimelessPerpetuation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Omega Infinite Eternal Existence")
    float OmegaOmegaInfiniteEternalSelfSufficiency;

    // Omega Omega Infinite Eternal Existence Events
    UPROPERTY(BlueprintAssignable, Category = "Omega Omega Infinite Eternal Existence")
    FOnOmegaOmegaInfiniteEternalExistenceActivated OnOmegaOmegaInfiniteEternalExistenceActivated;

    UPROPERTY(BlueprintAssignable, Category = "Omega Omega Infinite Eternal Existence")
    FOnOmegaOmegaInfiniteEternalExistenceDeactivated OnOmegaOmegaInfiniteEternalExistenceDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Omega Omega Infinite Eternal Existence")
    FOnOmegaOmegaInfiniteEternalExistenceLevelChanged OnOmegaOmegaInfiniteEternalExistenceLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Omega Omega Infinite Eternal Existence")
    FOnOmegaOmegaInfiniteEternalExistenceMaxLevelReached OnOmegaOmegaInfiniteEternalExistenceMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Omega Omega Infinite Eternal Existence")
    FOnOmegaOmegaInfiniteEternalExistencePowerUsed OnOmegaOmegaInfiniteEternalExistencePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Omega Omega Infinite Eternal Existence")
    FOnOmegaOmegaInfiniteEternalExistencePowerFailed OnOmegaOmegaInfiniteEternalExistencePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Omega Omega Infinite Eternal Existence")
    FOnOmegaOmegaInfiniteEternalExistenceAbilityPerformed OnOmegaOmegaInfiniteEternalExistenceAbilityPerformed;

    // Omega Omega Infinite Eternal Existence Functions
    UFUNCTION(BlueprintCallable, Category = "Omega Omega Infinite Eternal Existence")
    void ActivateOmegaOmegaInfiniteEternalExistence();

    UFUNCTION(BlueprintCallable, Category = "Omega Omega Infinite Eternal Existence")
    void DeactivateOmegaOmegaInfiniteEternalExistence();

    UFUNCTION(BlueprintCallable, Category = "Omega Omega Infinite Eternal Existence")
    void SetOmegaOmegaInfiniteEternalExistenceLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Omega Omega Infinite Eternal Existence")
    void UseOmegaOmegaInfiniteEternalExistencePower();

    UFUNCTION(BlueprintCallable, Category = "Omega Omega Infinite Eternal Existence")
    void PerformOmegaOmegaInfiniteEternalExistenceAbility();

    UFUNCTION(BlueprintCallable, Category = "Omega Omega Infinite Eternal Existence")
    bool IsOmegaOmegaInfiniteEternalExistenceActive() const;

    UFUNCTION(BlueprintCallable, Category = "Omega Omega Infinite Eternal Existence")
    int32 GetOmegaOmegaInfiniteEternalExistenceLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Omega Omega Infinite Eternal Existence")
    float GetOmegaOmegaInfiniteEternalExistencePowerCost() const;

    // Omega Omega Infinite Eternal Existence Abilities
    UFUNCTION(BlueprintCallable, Category = "Omega Omega Infinite Eternal Existence")
    void ChannelOmegaOmegaInfiniteEternalLifeForce();

    UFUNCTION(BlueprintCallable, Category = "Omega Omega Infinite Eternal Existence")
    void AchieveOmegaOmegaInfiniteEternalPerpetuation();

    UFUNCTION(BlueprintCallable, Category = "Omega Omega Infinite Eternal Existence")
    void MaintainOmegaOmegaInfiniteEternalInfiniteContinuum();

    UFUNCTION(BlueprintCallable, Category = "Omega Omega Infinite Eternal Existence")
    void PerpetuateOmegaOmegaInfiniteEternalTimelessly();

    UFUNCTION(BlueprintCallable, Category = "Omega Omega Infinite Eternal Existence")
    void AchieveOmegaOmegaInfiniteEternalSelfSufficiency();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateOmegaOmegaInfiniteEternalExistence() const;
    void UpdateOmegaOmegaInfiniteEternalExistenceStats();
    void OnOmegaOmegaInfiniteEternalExistenceStateChanged();
};
