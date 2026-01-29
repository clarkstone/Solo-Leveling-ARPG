#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P04_EXST_INFINITE.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInfiniteExistenceActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInfiniteExistenceDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnInfiniteExistenceLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInfiniteExistenceMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInfiniteExistencePowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInfiniteExistencePowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInfiniteExistenceAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP04_EXST_INFINITE : public UActorComponent
{
    GENERATED_BODY()

public:
    UP04_EXST_INFINITE();

    // Infinite Existence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Existence")
    int32 InfiniteExistenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Existence")
    int32 MaxInfiniteExistenceLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Existence")
    bool bIsInfiniteExistenceActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Existence")
    float InfiniteExistencePowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Existence")
    float InfiniteExistenceThreshold;

    // Infinite Existence Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Existence")
    float InfiniteLifeForce;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Existence")
    float InfinitePerpetuation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Existence")
    float InfiniteContinuum;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Existence")
    float InfiniteTimelessPerpetuation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Existence")
    float InfiniteSelfSufficiency;

    // Infinite Existence Events
    UPROPERTY(BlueprintAssignable, Category = "Infinite Existence")
    FOnInfiniteExistenceActivated OnInfiniteExistenceActivated;

    UPROPERTY(BlueprintAssignable, Category = "Infinite Existence")
    FOnInfiniteExistenceDeactivated OnInfiniteExistenceDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Infinite Existence")
    FOnInfiniteExistenceLevelChanged OnInfiniteExistenceLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Infinite Existence")
    FOnInfiniteExistenceMaxLevelReached OnInfiniteExistenceMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Infinite Existence")
    FOnInfiniteExistencePowerUsed OnInfiniteExistencePowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Infinite Existence")
    FOnInfiniteExistencePowerFailed OnInfiniteExistencePowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Infinite Existence")
    FOnInfiniteExistenceAbilityPerformed OnInfiniteExistenceAbilityPerformed;

    // Infinite Existence Functions
    UFUNCTION(BlueprintCallable, Category = "Infinite Existence")
    void ActivateInfiniteExistence();

    UFUNCTION(BlueprintCallable, Category = "Infinite Existence")
    void DeactivateInfiniteExistence();

    UFUNCTION(BlueprintCallable, Category = "Infinite Existence")
    void SetInfiniteExistenceLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Infinite Existence")
    void UseInfiniteExistencePower();

    UFUNCTION(BlueprintCallable, Category = "Infinite Existence")
    void PerformInfiniteExistenceAbility();

    UFUNCTION(BlueprintCallable, Category = "Infinite Existence")
    bool IsInfiniteExistenceActive() const;

    UFUNCTION(BlueprintCallable, Category = "Infinite Existence")
    int32 GetInfiniteExistenceLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Infinite Existence")
    float GetInfiniteExistencePowerCost() const;

    // Infinite Existence Abilities
    UFUNCTION(BlueprintCallable, Category = "Infinite Existence")
    void ChannelInfiniteLifeForce();

    UFUNCTION(BlueprintCallable, Category = "Infinite Existence")
    void AchieveInfinitePerpetuation();

    UFUNCTION(BlueprintCallable, Category = "Infinite Existence")
    void MaintainInfiniteContinuum();

    UFUNCTION(BlueprintCallable, Category = "Infinite Existence")
    void PerpetuateInfiniteTimelessly();

    UFUNCTION(BlueprintCallable, Category = "Infinite Existence")
    void AchieveInfiniteSelfSufficiency();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateInfiniteExistence() const;
    void UpdateInfiniteExistenceStats();
    void OnInfiniteExistenceStateChanged();
};
