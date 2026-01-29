#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P04_EXST_HYPER.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHyperExistenceActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHyperExistenceDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnHyperExistenceLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHyperExistenceMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHyperExistencePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHyperExistencePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHyperExistenceAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP04_EXST_HYPER : public UActorComponent
{
    GENERATED_BODY()

public:
    UP04_EXST_HYPER();

    // Hyper Existence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper Existence")
    int32 HyperExistenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper Existence")
    int32 MaxHyperExistenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper Existence")
    bool bIsHyperExistenceActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper Existence")
    float HyperExistencePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper Existence")
    float HyperExistenceThreshold;

    // Hyper Existence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper Existence")
    float HyperLifeForce;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper Existence")
    float HyperPerpetuation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper Existence")
    float HyperInfiniteContinuum;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper Existence")
    float HyperTimelessPerpetuation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hyper Existence")
    float HyperSelfSufficiency;

    // Hyper Existence Events
    UPROPERTY(BlueprintAssignable, Category = "Hyper Existence")
    FOnHyperExistenceActivated OnHyperExistenceActivated;

    UPROPERTY(BlueprintAssignable, Category = "Hyper Existence")
    FOnHyperExistenceDeactivated OnHyperExistenceDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Hyper Existence")
    FOnHyperExistenceLevelChanged OnHyperExistenceLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Hyper Existence")
    FOnHyperExistenceMaxLevelReached OnHyperExistenceMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Hyper Existence")
    FOnHyperExistencePowerUsed OnHyperExistencePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Hyper Existence")
    FOnHyperExistencePowerFailed OnHyperExistencePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Hyper Existence")
    FOnHyperExistenceAbilityPerformed OnHyperExistenceAbilityPerformed;

    // Hyper Existence Functions
    UFUNCTION(BlueprintCallable, Category = "Hyper Existence")
    void ActivateHyperExistence();

    UFUNCTION(BlueprintCallable, Category = "Hyper Existence")
    void DeactivateHyperExistence();

    UFUNCTION(BlueprintCallable, Category = "Hyper Existence")
    void SetHyperExistenceLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Hyper Existence")
    void UseHyperExistencePower();

    UFUNCTION(BlueprintCallable, Category = "Hyper Existence")
    void PerformHyperExistenceAbility();

    UFUNCTION(BlueprintCallable, Category = "Hyper Existence")
    bool IsHyperExistenceActive() const;

    UFUNCTION(BlueprintCallable, Category = "Hyper Existence")
    int32 GetHyperExistenceLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Hyper Existence")
    float GetHyperExistencePowerCost() const;

    // Hyper Existence Abilities
    UFUNCTION(BlueprintCallable, Category = "Hyper Existence")
    void ChannelHyperLifeForce();

    UFUNCTION(BlueprintCallable, Category = "Hyper Existence")
    void AchieveHyperPerpetuation();

    UFUNCTION(BlueprintCallable, Category = "Hyper Existence")
    void MaintainHyperInfiniteContinuum();

    UFUNCTION(BlueprintCallable, Category = "Hyper Existence")
    void PerpetuateHyperTimelessly();

    UFUNCTION(BlueprintCallable, Category = "Hyper Existence")
    void AchieveHyperSelfSufficiency();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateHyperExistence() const;
    void UpdateHyperExistenceStats();
    void OnHyperExistenceStateChanged();
};
