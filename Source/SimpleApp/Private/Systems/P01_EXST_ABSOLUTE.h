#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P01_EXST_ABSOLUTE.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbsoluteExistenceActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbsoluteExistenceDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnAbsoluteExistenceLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbsoluteExistenceMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbsoluteExistencePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbsoluteExistencePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbsoluteExistenceAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP01_EXST_ABSOLUTE : public UActorComponent
{
    GENERATED_BODY()

public:
    UP01_EXST_ABSOLUTE();

    // Absolute Existence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute Existence")
    int32 AbsoluteExistenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute Existence")
    int32 MaxAbsoluteExistenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute Existence")
    bool bIsAbsoluteExistenceActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute Existence")
    float AbsoluteExistencePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute Existence")
    float AbsoluteExistenceThreshold;

    // Absolute Existence Properties
    UPROPERTY(EditAnywhere, BlueprintEssence, Category = "Absolute Existence")
    float AbsoluteLifeForce;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute Existence")
    float EternalPerpetuation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute Existence")
    float InfiniteContinuum;

    UPROPERTY(EditAnywhere, BlueprintWriteOnly, Category = "Absolute Existence")
    float TimelessPerpetuation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute Existence")
    float AbsoluteSelfSufficiency;

    // Absolute Existence Events
    UPROPERTY(BlueprintAssignable, Category = "Absolute Existence")
    FOnAbsoluteExistenceActivated OnAbsoluteExistenceActivated;

    UPROPERTY(BlueprintAssignable, Category = "Absolute Existence")
    FOnAbsoluteExistenceDeactivated OnAbsoluteExistenceDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Absolute Existence")
    FOnAbsoluteExistenceLevelChanged OnAbsoluteExistenceLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Absolute Existence")
    FOnAbsoluteExistenceMaxLevelReached OnAbsoluteExistenceMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Absolute Existence")
    FOnAbsoluteExistencePowerUsed OnAbsoluteExistencePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Absolute Existence")
    FOnAbsoluteExistencePowerFailed OnAbsoluteExistencePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Absolute Existence")
    FOnAbsoluteExistenceAbilityPerformed OnAbsoluteExistenceAbilityPerformed;

    // Absolute Existence Functions
    UFUNCTION(BlueprintCallable, Category = "Absolute Existence")
    void ActivateAbsoluteExistence();

    UFUNCTION(BlueprintCallable, Category = "Absolute Existence")
    void DeactivateAbsoluteExistence();

    UFUNCTION(BlueprintCallable, Category = "Absolute Existence")
    void SetAbsoluteExistenceLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Absolute Existence")
    void UseAbsoluteExistencePower();

    UFUNCTION(BlueprintCallable, Category = "Absolute Existence")
    void PerformAbsoluteExistenceAbility();

    UFUNCTION(BlueprintCallable, Category = "Absolute Existence")
    bool IsAbsoluteExistenceActive() const;

    UFUNCTION(BlueprintCallable, Category = "Absolute Existence")
    int32 GetAbsoluteExistenceLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Absolute Existence")
    float GetAbsoluteExistencePowerCost() const;

    // Absolute Existence Abilities
    UFUNCTION(BlueprintCallable, Category = "Absolute Existence")
    void ChannelAbsoluteLifeForce();

    UFUNCTION(BlueprintCallable, Category = "Absolute Existence")
    void AchieveEternalPerpetuation();

    UFUNCTION(BlueprintCallable, Category = "Absolute Existence")
    void MaintainInfiniteContinuum();

    UFUNCTION(BlueprintCallable, Category = "Absolute Existence")
    void PerpetuateTimelessly();

    UFUNCTION(BlueprintCallable, Category = "Absolute Existence")
    void AchieveAbsoluteSelfSufficiency();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateAbsoluteExistence() const;
    void UpdateAbsoluteExistenceStats();
    void OnAbsoluteExistenceStateChanged();
};
