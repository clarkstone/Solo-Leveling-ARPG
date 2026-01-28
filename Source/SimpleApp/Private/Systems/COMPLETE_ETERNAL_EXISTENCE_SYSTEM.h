#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COMPLETE_ETERNAL_EXISTENCE_SYSTEM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEternalExistenceActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEternalExistenceDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnEternalExistenceLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEternalExistenceMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEternalExistencePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEternalExistencePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEternalExistenceAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UCOMPLETE_ETERNAL_EXISTENCE_SYSTEM : public UActorComponent
{
    GENERATED_BODY()

public:
    UCOMPLETE_ETERNAL_EXISTENCE_SYSTEM();

    // Eternal-Existence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal-Existence")
    int32 EternalExistenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal-Existence")
    int32 MaxEternalExistenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal-Existence")
    bool bIsEternalExistenceActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal-Existence")
    float EternalExistencePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal-Existence")
    float EternalExistenceThreshold;

    // Eternal-Existence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal-Existence")
    float EternalLifeForce;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal-Existence")
    float InfiniteSustenance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal-Existence")
    float PerpetualRenewal;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal-Existence")
    float TimelessExistence;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal-Existence")
    float AbsoluteImmortality;

    // Eternal-Existence Events
    UPROPERTY(BlueprintAssignable, Category = "Eternal-Existence")
    FOnEternalExistenceActivated OnEternalExistenceActivated;

    UPROPERTY(BlueprintAssignable, Category = "Eternal-Existence")
    FOnEternalExistenceDeactivated OnEternalExistenceDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Eternal-Existence")
    FOnEternalExistenceLevelChanged OnEternalExistenceLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Eternal-Existence")
    FOnEternalExistenceMaxLevelReached OnEternalExistenceMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Eternal-Existence")
    FOnEternalExistencePowerUsed OnEternalExistencePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Eternal-Existence")
    FOnEternalExistencePowerFailed OnEternalExistencePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Eternal-Existence")
    FOnEternalExistenceAbilityPerformed OnEternalExistenceAbilityPerformed;

    // Eternal-Existence Functions
    UFUNCTION(BlueprintCallable, Category = "Eternal-Existence")
    void ActivateEternalExistence();

    UFUNCTION(BlueprintCallable, Category = "Eternal-Existence")
    void DeactivateEternalExistence();

    UFUNCTION(BlueprintCallable, Category = "Eternal-Existence")
    void SetEternalExistenceLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Eternal-Existence")
    void UseEternalExistencePower();

    UFUNCTION(BlueprintCallable, Category = "Eternal-Existence")
    void PerformEternalExistenceAbility();

    UFUNCTION(BlueprintCallable, Category = "Eternal-Existence")
    bool IsEternalExistenceActive() const;

    UFUNCTION(BlueprintCallable, Category = "Eternal-Existence")
    int32 GetEternalExistenceLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Eternal-Existence")
    float GetEternalExistencePowerCost() const;

    // Eternal-Existence Abilities
    UFUNCTION(BlueprintCallable, Category = "Eternal-Existence")
    void ChannelEternalLifeForce();

    UFUNCTION(BlueprintCallable, Category = "Eternal-Existence")
    void SustainInfiniteExistence();

    UFUNCTION(BlueprintCallable, Category = "Eternal-Existence")
    void RenewPerpetually();

    UFUNCTION(BlueprintCallable, Category = "Eternal-Existence")
    void ExistTimelessly();

    UFUNCTION(BlueprintCallable, Category = "Eternal-Existence")
    void AchieveAbsoluteImmortality();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateEternalExistence() const;
    void UpdateEternalExistenceStats();
    void OnEternalExistenceStateChanged();
};
