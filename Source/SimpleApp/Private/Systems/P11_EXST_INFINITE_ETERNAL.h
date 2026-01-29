#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P11_EXST_INFINITE_ETERNAL.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInfiniteEternalExistenceActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInfiniteEternalExistenceDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnInfiniteEternalExistenceLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInfiniteEternalExistenceMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInfiniteEternalExistencePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInfiniteEternalExistencePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInfiniteEternalExistenceAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP11_EXST_INFINITE_ETERNAL : public UActorComponent
{
    GENERATED_BODY()

public:
    UP11_EXST_INFINITE_ETERNAL();

    // Infinite Eternal Existence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Eternal Existence")
    int32 InfiniteEternalExistenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Eternal Existence")
    int32 MaxInfiniteEternalExistenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Eternal Existence")
    bool bIsInfiniteEternalExistenceActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Eternal Existence")
    float InfiniteEternalExistencePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Eternal Existence")
    float InfiniteEternalExistenceThreshold;

    // Infinite Eternal Existence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Eternal Existence")
    float InfiniteEternalLifeForce;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Eternal Existence")
    float InfiniteEternalPerpetuation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Eternal Existence")
    float InfiniteEternalInfiniteContinuum;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Eternal Existence")
    float InfiniteEternalTimelessPerpetuation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Eternal Existence")
    float InfiniteEternalSelfSufficiency;

    // Infinite Eternal Existence Events
    UPROPERTY(BlueprintAssignable, Category = "Infinite Eternal Existence")
    FOnInfiniteEternalExistenceActivated OnInfiniteEternalExistenceActivated;

    UPROPERTY(BlueprintAssignable, Category = "Infinite Eternal Existence")
    FOnInfiniteEternalExistenceDeactivated OnInfiniteEternalExistenceDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Infinite Eternal Existence")
    FOnInfiniteEternalExistenceLevelChanged OnInfiniteEternalExistenceLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Infinite Eternal Existence")
    FOnInfiniteEternalExistenceMaxLevelReached OnInfiniteEternalExistenceMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Infinite Eternal Existence")
    FOnInfiniteEternalExistencePowerUsed OnInfiniteEternalExistencePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Infinite Eternal Existence")
    FOnInfiniteEternalExistencePowerFailed OnInfiniteEternalExistencePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Infinite Eternal Existence")
    FOnInfiniteEternalExistenceAbilityPerformed OnInfiniteEternalExistenceAbilityPerformed;

    // Infinite Eternal Existence Functions
    UFUNCTION(BlueprintCallable, Category = "Infinite Eternal Existence")
    void ActivateInfiniteEternalExistence();

    UFUNCTION(BlueprintCallable, Category = "Infinite Eternal Existence")
    void DeactivateInfiniteEternalExistence();

    UFUNCTION(BlueprintCallable, Category = "Infinite Eternal Existence")
    void SetInfiniteEternalExistenceLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Infinite Eternal Existence")
    void UseInfiniteEternalExistencePower();

    UFUNCTION(BlueprintCallable, Category = "Infinite Eternal Existence")
    void PerformInfiniteEternalExistenceAbility();

    UFUNCTION(BlueprintCallable, Category = "Infinite Eternal Existence")
    bool IsInfiniteEternalExistenceActive() const;

    UFUNCTION(BlueprintCallable, Category = "Infinite Eternal Existence")
    int32 GetInfiniteEternalExistenceLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Infinite Eternal Existence")
    float GetInfiniteEternalExistencePowerCost() const;

    // Infinite Eternal Existence Abilities
    UFUNCTION(BlueprintCallable, Category = "Infinite Eternal Existence")
    void ChannelInfiniteEternalLifeForce();

    UFUNCTION(BlueprintCallable, Category = "Infinite Eternal Existence")
    void AchieveInfiniteEternalPerpetuation();

    UFUNCTION(BlueprintCallable, Category = "Infinite Eternal Existence")
    void MaintainInfiniteEternalInfiniteContinuum();

    UFUNCTION(BlueprintCallable, Category = "Infinite Eternal Existence")
    void PerpetuateInfiniteEternalTimelessly();

    UFUNCTION(BlueprintCallable, Category = "Infinite Eternal Existence")
    void AchieveInfiniteEternalSelfSufficiency();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateInfiniteEternalExistence() const;
    void UpdateInfiniteEternalExistenceStats();
    void OnInfiniteEternalExistenceStateChanged();
};
