#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P23_VOID_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOmegaOmegaInfiniteEternalVoidActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOmegaOmegaInfiniteEternalVoidDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnOmegaOmegaInfiniteEternalVoidLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOmegaOmegaInfiniteEternalVoidMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOmegaOmegaInfiniteEternalVoidPowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOmegaOmegaInfiniteEternalVoidPowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOmegaOmegaInfiniteEternalVoidAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP23_VOID_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL : public UActorComponent
{
    GENERATED_BODY()

public:
    UP23_VOID_OMEGA_OMEGA_OMEGA_INFINITE_ETERNAL();

    // Omega Omega Infinite Eternal Void Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Omega Infinite Eternal Void")
    int32 OmegaOmegaInfiniteEternalVoidLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Omega Infinite Eternal Void")
    int32 MaxOmegaOmegaInfiniteEternalVoidLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Omega Infinite Eternal Void")
    bool bIsOmegaOmegaInfiniteEternalVoidActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Omega Infinite Eternal Void")
    float OmegaOmegaInfiniteEternalVoidPowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Omega Infinite Eternal Void")
    float OmegaOmegaInfiniteEternalVoidThreshold;

    // Omega Omega Infinite Eternal Void Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Omega Infinite Eternal Void")
    float OmegaOmegaInfiniteEternalVoidMastery;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Omega Infinite Eternal Void")
    float OmegaOmegaInfiniteEternalUltimateAnnihilation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Omega Infinite Eternal Void")
    float OmegaOmegaInfiniteEternalPerfectVoidEmptiness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Omega Infinite Eternal Void")
    float OmegaOmegaInfiniteEternalConceptualUltimateOblivion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Omega Omega Infinite Eternal Void")
    float OmegaOmegaInfiniteEternalExistenceUltimateNegation;

    // Omega Omega Infinite Eternal Void Events
    UPROPERTY(BlueprintAssignable, Category = "Omega Omega Infinite Eternal Void")
    FOnOmegaOmegaInfiniteEternalVoidActivated OnOmegaOmegaInfiniteEternalVoidActivated;

    UPROPERTY(BlueprintAssignable, Category = "Omega Omega Infinite Eternal Void")
    FOnOmegaOmegaInfiniteEternalVoidDeactivated OnOmegaInfiniteEternalVoidDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Omega Omega Infinite Eternal Void")
    FOnOmegaOmegaInfiniteEternalVoidLevelChanged OnOmegaOmegaInfiniteEternalVoidLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Omega Omega Infinite Eternal Void")
    FOnOmegaOmegaInfiniteEternalVoidMaxLevelReached OnOmegaOmegaInfiniteEternalVoidMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Omega Omega Infinite Eternal Void")
    FOnOmegaOmegaInfiniteEternalVoidPowerUsed OnOmegaOmegaInfiniteEternalVoidPowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Omega Omega Infinite Eternal Void")
    FOnOmegaOmegaInfiniteEternalVoidPowerFailed OnOmegaOmegaInfiniteEternalVoidPowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Omega Omega Infinite Eternal Void")
    FOnOmegaOmegaInfiniteEternalVoidAbilityPerformed OnOmegaOmegaInfiniteEternalVoidAbilityPerformed;

    // Omega Omega Infinite Eternal Void Functions
    UFUNCTION(BlueprintCallable, Category = "Omega Omega Infinite Eternal Void")
    void ActivateOmegaOmegaInfiniteEternalVoid();

    UFUNCTION(BlueprintCallable, Category = "Omega Omega Infinite Eternal Void")
    void DeactivateOmegaOmegaInfiniteEternalVoid();

    UFUNCTION(BlueprintCallable, Category = "Omega Omega Infinite Eternal Void")
    void SetOmegaOmegaInfiniteEternalVoidLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Omega Omega Infinite Eternal Void")
    void UseOmegaOmegaInfiniteEternalVoidPower();

    UFUNCTION(BlueprintCallable, Category = "Omega Omega Infinite Eternal Void")
    void PerformOmegaOmegaInfiniteEternalVoidAbility();

    UFUNCTION(BlueprintCallable, Category = "Omega Omega Infinite Eternal Void")
    bool IsOmegaOmegaInfiniteEternalVoidActive() const;

    UFUNCTION(BlueprintCallable, Category = "Omega Omega Infinite Eternal Void")
    int32 GetOmegaOmegaInfiniteEternalVoidLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Omega Omega Infinite Eternal Void")
    float GetOmegaOmegaInfiniteEternalVoidPowerCost() const;

    // Omega Omega Infinite Eternal Void Abilities
    UFUNCTION(BlueprintCallable, Category = "Omega Omega Infinite Eternal Void")
    void MasterOmegaOmegaInfiniteEternalVoid();

    UFUNCTION(BlueprintCallable, Category = "Omega Omega Infinite Eternal Void")
    void AnnihilateOmegaOmegaInfiniteEternally();

    UFUNCTION(BlueprintCallable, Category = "Omega Omega Infinite Eternal Void")
    void AchieveOmegaOmegaInfiniteEternalPerfectVoidEmptiness();

    UFUNCTION(BlueprintCallable, Category = "Omega Omega Infinite Eternal Void")
    void InduceOmegaOmegaInfiniteEternalConceptualUltimateOblivion();

    UFUNCTION(BlueprintCallable, Category = "Omega Omega Infinite Eternal Void")
    void NegateOmegaOmegaInfiniteEternalUltimateExistence();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateOmegaOmegaInfiniteEternalVoid() const;
    void UpdateOmegaOmegaInfiniteEternalVoidStats();
    void OnOmegaOmegaInfiniteEternalVoidStateChanged();
};
