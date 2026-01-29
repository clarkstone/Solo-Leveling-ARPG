#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P12_VOID_OMEGA_INFINITE_ETERNAL.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOmegaInfiniteEternalVoidActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOmegaInfiniteEternalVoidDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnOmegaInfiniteEternalVoidLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOmegaInfiniteEternalVoidMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOmegaInfiniteEternalVoidPowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOmegaInfiniteEternalVoidPowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOmegaInfiniteEternalVoidAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP12_VOID_OMEGA_INFINITE_ETERNAL : public UActorComponent
{
    GENERATED_BODY()

public:
    UP12_VOID_OMEGA_INFINITE_ETERNAL();

    // Omega Infinite Eternal Void Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Infinite Eternal Void")
    int32 OmegaInfiniteEternalVoidLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Infinite Eternal Void")
    int32 MaxOmegaInfiniteEternalVoidLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Infinite Eternal Void")
    bool bIsOmegaInfiniteEternalVoidActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Infinite Eternal Void")
    float OmegaInfiniteEternalVoidPowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Infinite Eternal Void")
    float OmegaInfiniteEternalVoidThreshold;

    // Omega Infinite Eternal Void Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Infinite Eternal Void")
    float OmegaInfiniteEternalVoidMastery;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Infinite Eternal Void")
    float OmegaInfiniteEternalUltimateAnnihilation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Infinite Eternal Void")
    float OmegaInfiniteEternalPerfectVoidEmptiness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Infinite Eternal Void")
    float OmegaInfiniteEternalConceptualUltimateOblivion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Infinite Eternal Void")
    float OmegaInfiniteEternalExistenceUltimateNegation;

    // Omega Infinite Eternal Void Events
    UPROPERTY(BlueprintAssignable, Category = "Omega Infinite Eternal Void")
    FOnOmegaInfiniteEternalVoidActivated OnOmegaInfiniteEternalVoidActivated;

    UPROPERTY(BlueprintAssignable, Category = "Omega Infinite Eternal Void")
    FOnOmegaInfiniteEternalVoidDeactivated OnOmegaInfiniteEternalVoidDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Omega Infinite Eternal Void")
    FOnOmegaInfiniteEternalVoidLevelChanged OnOmegaInfiniteEternalVoidLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Omega Infinite Eternal Void")
    FOnOmegaInfiniteEternalVoidMaxLevelReached OnOmegaInfiniteEternalVoidMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Omega Infinite Eternal Void")
    FOnOmegaInfiniteEternalVoidPowerUsed OnOmegaInfiniteEternalVoidPowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Omega Infinite Eternal Void")
    FOnOmegaInfiniteEternalVoidPowerFailed OnOmegaInfiniteEternalVoidPowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Omega Infinite Eternal Void")
    FOnOmegaInfiniteEternalVoidAbilityPerformed OnOmegaInfiniteEternalVoidAbilityPerformed;

    // Omega Infinite Eternal Void Functions
    UFUNCTION(BlueprintCallable, Category = "Omega Infinite Eternal Void")
    void ActivateOmegaInfiniteEternalVoid();

    UFUNCTION(BlueprintCallable, Category = "Omega Infinite Eternal Void")
    void DeactivateOmegaInfiniteEternalVoid();

    UFUNCTION(BlueprintCallable, Category = "Omega Infinite Eternal Void")
    void SetOmegaInfiniteEternalVoidLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Omega Infinite Eternal Void")
    void UseOmegaInfiniteEternalVoidPower();

    UFUNCTION(BlueprintCallable, Category = "Omega Infinite Eternal Void")
    void PerformOmegaInfiniteEternalVoidAbility();

    UFUNCTION(BlueprintCallable, Category = "Omega Infinite Eternal Void")
    bool IsOmegaInfiniteEternalVoidActive() const;

    UFUNCTION(BlueprintCallable, Category = "Omega Infinite Eternal Void")
    int32 GetOmegaInfiniteEternalVoidLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Omega Infinite Eternal Void")
    float GetOmegaInfiniteEternalVoidPowerCost() const;

    // Omega Infinite Eternal Void Abilities
    UFUNCTION(BlueprintCallable, Category = "Omega Infinite Eternal Void")
    void MasterOmegaInfiniteEternalVoid();

    UFUNCTION(BlueprintCallable, Category = "Omega Infinite Eternal Void")
    void AnnihilateOmegaInfiniteEternally();

    UFUNCTION(BlueprintCallable, Category = "Omega Infinite Eternal Void")
    void AchieveOmegaInfiniteEternalPerfectVoidEmptiness();

    UFUNCTION(BlueprintCallable, Category = "Omega Infinite Eternal Void")
    void InduceOmegaInfiniteEternalConceptualUltimateOblivion();

    UFUNCTION(BlueprintCallable, Category = "Omega Infinite Eternal Void")
    void NegateOmegaInfiniteEternalUltimateExistence();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateOmegaInfiniteEternalVoid() const;
    void UpdateOmegaInfiniteEternalVoidStats();
    void OnOmegaInfiniteEternalVoidStateChanged();
};
