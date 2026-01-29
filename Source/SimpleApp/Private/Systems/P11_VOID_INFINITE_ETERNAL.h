#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P11_VOID_INFINITE_ETERNAL.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInfiniteEternalVoidActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInfiniteEternalVoidDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnInfiniteEternalVoidLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInfiniteEternalVoidMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInfiniteEternalVoidPowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInfiniteEternalVoidPowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInfiniteEternalVoidAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP11_VOID_INFINITE_ETERNAL : public UActorComponent
{
    GENERATED_BODY()

public:
    UP11_VOID_INFINITE_ETERNAL();

    // Infinite Eternal Void Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Eternal Void")
    int32 InfiniteEternalVoidLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Eternal Void")
    int32 MaxInfiniteEternalVoidLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Eternal Void")
    bool bIsInfiniteEternalVoidActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Eternal Void")
    float InfiniteEternalVoidPowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Eternal Void")
    float InfiniteEternalVoidThreshold;

    // Infinite Eternal Void Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Eternal Void")
    float InfiniteEternalVoidMastery;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Eternal Void")
    float InfiniteEternalUltimateAnnihilation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Eternal Void")
    float InfiniteEternalPerfectVoidEmptiness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Eternal Void")
    float InfiniteEternalConceptualUltimateOblivion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Infinite Eternal Void")
    float InfiniteEternalExistenceUltimateNegation;

    // Infinite Eternal Void Events
    UPROPERTY(BlueprintAssignable, Category = "Infinite Eternal Void")
    FOnInfiniteEternalVoidActivated OnInfiniteEternalVoidActivated;

    UPROPERTY(BlueprintAssignable, Category = "Infinite Eternal Void")
    FOnInfiniteEternalVoidDeactivated OnInfiniteEternalVoidDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Infinite Eternal Void")
    FOnInfiniteEternalVoidLevelChanged OnInfiniteEternalVoidLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Infinite Eternal Void")
    FOnInfiniteEternalVoidMaxLevelReached OnInfiniteEternalVoidMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Infinite Eternal Void")
    FOnInfiniteEternalVoidPowerUsed OnInfiniteEternalVoidPowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Infinite Eternal Void")
    FOnInfiniteEternalVoidPowerFailed OnInfiniteEternalVoidPowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Infinite Eternal Void")
    FOnInfiniteEternalVoidAbilityPerformed OnInfiniteEternalVoidAbilityPerformed;

    // Infinite Eternal Void Functions
    UFUNCTION(BlueprintCallable, Category = "Infinite Eternal Void")
    void ActivateInfiniteEternalVoid();

    UFUNCTION(BlueprintCallable, Category = "Infinite Eternal Void")
    void DeactivateInfiniteEternalVoid();

    UFUNCTION(BlueprintCallable, Category = "Infinite Eternal Void")
    void SetInfiniteEternalVoidLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Infinite Eternal Void")
    void UseInfiniteEternalVoidPower();

    UFUNCTION(BlueprintCallable, Category = "Infinite Eternal Void")
    void PerformInfiniteEternalVoidAbility();

    UFUNCTION(BlueprintCallable, Category = "Infinite Eternal Void")
    bool IsInfiniteEternalVoidActive() const;

    UFUNCTION(BlueprintCallable, Category = "Infinite Eternal Void")
    int32 GetInfiniteEternalVoidLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Infinite Eternal Void")
    float GetInfiniteEternalVoidPowerCost() const;

    // Infinite Eternal Void Abilities
    UFUNCTION(BlueprintCallable, Category = "Infinite Eternal Void")
    void MasterInfiniteEternalVoid();

    UFUNCTION(BlueprintCallable, Category = "Infinite Eternal Void")
    void AnnihilateInfiniteEternally();

    UFUNCTION(BlueprintCallable, Category = "Infinite Eternal Void")
    void AchieveInfiniteEternalPerfectVoidEmptiness();

    UFUNCTION(BlueprintCallable, Category = "Infinite Eternal Void")
    void InduceInfiniteEternalConceptualUltimateOblivion();

    UFUNCTION(BlueprintCallable, Category = "Infinite Eternal Void")
    void NegateInfiniteEternalUltimateExistence();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateInfiniteEternalVoid() const;
    void UpdateInfiniteEternalVoidStats();
    void OnInfiniteEternalVoidStateChanged();
};
