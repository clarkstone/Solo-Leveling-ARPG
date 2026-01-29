#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P01_VOID_ULTIMATE.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltimateVoidActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltimateVoidDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnUltimateVoidLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUltimateVoidMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltimateVoidPowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUltimateVoidPowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltimateVoidAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP01_VOID_ULTIMATE : public UActorComponent
{
    GENERATED_BODY()

public:
    UP01_VOID_ULTIMATE();

    // Ultimate Void Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Void")
    int32 UltimateVoidLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Void")
    int32 MaxUltimateVoidLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Void")
    bool bIsUltimateVoidActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Void")
    float UltimateVoidPowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Void")
    float UltimateVoidThreshold;

    // Ultimate Void Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Void")
    float VoidMastery;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Void")
    float UltimateAnnihilation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Void")
    float PerfectVoidEmptiness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Void")
    float ConceptualUltimateOblivion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultimate Void")
    float ExistenceUltimateNegation;

    // Ultimate Void Events
    UPROPERTY(BlueprintAssignable, Category = "Ultimate Void")
    FOnUltimateVoidActivated OnUltimateVoidActivated;

    UPROPERTY(BlueprintAssignable, Category = "Ultimate Void")
    FOnUltimateVoidDeactivated OnUltimateVoidDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Ultimate Void")
    FOnUltimateVoidLevelChanged OnUltimateVoidLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Ultimate Void")
    FOnUltimateVoidMaxLevelReached OnUltimateVoidMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Ultimate Void")
    FOnUltimateVoidPowerUsed OnUltimateVoidPowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Ultimate Void")
    FOnUltimateVoidPowerFailed OnUltimateVoidPowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Ultimate Void")
    FOnUltimateVoidAbilityPerformed OnUltimateVoidAbilityPerformed;

    // Ultimate Void Functions
    UFUNCTION(BlueprintCallable, Category = "Ultimate Void")
    void ActivateUltimateVoid();

    UFUNCTION(BlueprintCallable, Category = "Ultimate Void")
    void DeactivateUltimateVoid();

    UFUNCTION(BlueprintCallable, Category = "Ultimate Void")
    void SetUltimateVoidLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Ultimate Void")
    void UseUltimateVoidPower();

    UFUNCTION(BlueprintCallable, Category = "Ultimate Void")
    void PerformUltimateVoidAbility();

    UFUNCTION(BlueprintCallable, Category = "Ultimate Void")
    bool IsUltimateVoidActive() const;

    UFUNCTION(BlueprintCallable, Category = "Ultimate Void")
    int32 GetUltimateVoidLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Ultimate Void")
    float GetUltimateVoidPowerCost() const;

    // Ultimate Void Abilities
    UFUNCTION(BlueprintCallable, Category = "Ultimate Void")
    void MasterUltimateVoid();

    UFUNCTION(BlueprintCallable, Category = "Ultimate Void")
    void AnnihilateUltimately();

    UFUNCTION(BlueprintCallable, Category = "Ultimate Void")
    void AchievePerfectVoidEmptiness();

    UFUNCTION(BlueprintCallable, Category = "Ultimate Void")
    void InduceConceptualUltimateOblivion();

    UFUNCTION(BlueprintCallable, Category = "Ultimate Void")
    void NegateUltimateExistence();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateUltimateVoid() const;
    void UpdateUltimateVoidStats();
    void OnUltimateVoidStateChanged();
};
