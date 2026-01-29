#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P10_EXST_ETERNAL.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEternalExistenceActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEternalExistenceDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnEternalExistenceLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEternalExistenceMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEternalExistencePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEternalExistencePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEternalExistenceAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP10_EXST_ETERNAL : public UActorComponent
{
    GENERATED_BODY()

public:
    UP10_EXST_ETERNAL();

    // Eternal Existence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal Existence")
    int32 EternalExistenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal Existence")
    int32 MaxEternalExistenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal Existence")
    bool bIsEternalExistenceActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal Existence")
    float EternalExistencePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal Existence")
    float EternalExistenceThreshold;

    // Eternal Existence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal Existence")
    float EternalLifeForce;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal Existence")
    float EternalPerpetuation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal Existence")
    float EternalInfiniteContinuum;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal Existence")
    float EternalTimelessPerpetuation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal Existence")
    float EternalSelfSufficiency;

    // Eternal Existence Events
    UPROPERTY(BlueprintAssignable, Category = "Eternal Existence")
    FOnEternalExistenceActivated OnEternalExistenceActivated;

    UPROPERTY(BlueprintAssignable, Category = "Eternal Existence")
    FOnEternalExistenceDeactivated OnEternalExistenceDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Eternal Existence")
    FOnEternalExistenceLevelChanged OnEternalExistenceLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Eternal Existence")
    FOnEternalExistenceMaxLevelReached OnEternalExistenceMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Eternal Existence")
    FOnEternalExistencePowerUsed OnEternalExistencePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Eternal Existence")
    FOnEternalExistencePowerFailed OnEternalExistencePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Eternal Existence")
    FOnEternalExistenceAbilityPerformed OnEternalExistenceAbilityPerformed;

    // Eternal Existence Functions
    UFUNCTION(BlueprintCallable, Category = "Eternal Existence")
    void ActivateEternalExistence();

    UFUNCTION(BlueprintCallable, Category = "Eternal Existence")
    void DeactivateEternalExistence();

    UFUNCTION(BlueprintCallable, Category = "Eternal Existence")
    void SetEternalExistenceLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Eternal Existence")
    void UseEternalExistencePower();

    UFUNCTION(BlueprintCallable, Category = "Eternal Existence")
    void PerformEternalExistenceAbility();

    UFUNCTION(BlueprintCallable, Category = "Eternal Existence")
    bool IsEternalExistenceActive() const;

    UFUNCTION(BlueprintCallable, Category = "Eternal Existence")
    int32 GetEternalExistenceLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Eternal Existence")
    float GetEternalExistencePowerCost() const;

    // Eternal Existence Abilities
    UFUNCTION(BlueprintCallable, Category = "Eternal Existence")
    void ChannelEternalLifeForce();

    UFUNCTION(BlueprintCallable, Category = "Eternal Existence")
    void AchieveEternalPerpetuation();

    UFUNCTION(BlueprintCallable, Category = "Eternal Existence")
    void MaintainEternalInfiniteContinuum();

    UFUNCTION(BlueprintCallable, Category = "Eternal Existence")
    void PerpetuateEternalTimelessly();

    UFUNCTION(BlueprintCallable, Category = "Eternal Existence")
    void AchieveEternalSelfSufficiency();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateEternalExistence() const;
    void UpdateEternalExistenceStats();
    void OnEternalExistenceStateChanged();
};
