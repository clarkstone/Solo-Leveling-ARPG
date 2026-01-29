#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P08_VOID_SUPREME.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSupremeVoidActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSupremeVoidDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnSupremeVoidLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSupremeVoidMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSupremeVoidPowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSupremeVoidPowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSupremeVoidAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP08_VOID_SUPREME : public UActorComponent
{
    GENERATED_BODY()

public:
    UP08_VOID_SUPREME();

    // Supreme Void Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme Void")
    int32 SupremeVoidLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme Void")
    int32 MaxSupremeVoidLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme Void")
    bool bIsSupremeVoidActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme Void")
    float SupremeVoidPowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme Void")
    float SupremeVoidThreshold;

    // Supreme Void Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme Void")
    float SupremeVoidMastery;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme Void")
    float SupremeUltimateAnnihilation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme Void")
    float SupremePerfectVoidEmptiness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme Void")
    float SupremeConceptualUltimateOblivion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supreme Void")
    float SupremeExistenceUltimateNegation;

    // Supreme Void Events
    UPROPERTY(BlueprintAssignable, Category = "Supreme Void")
    FOnSupremeVoidActivated OnSupremeVoidActivated;

    UPROPERTY(BlueprintAssignable, Category = "Supreme Void")
    FOnSupremeVoidDeactivated OnSupremeVoidDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Supreme Void")
    FOnSupremeVoidLevelChanged OnSupremeVoidLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Supreme Void")
    FOnSupremeVoidMaxLevelReached OnSupremeVoidMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Supreme Void")
    FOnSupremeVoidPowerUsed OnSupremeVoidPowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Supreme Void")
    FOnSupremeVoidPowerFailed OnSupremeVoidPowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Supreme Void")
    FOnSupremeVoidAbilityPerformed OnSupremeVoidAbilityPerformed;

    // Supreme Void Functions
    UFUNCTION(BlueprintCallable, Category = "Supreme Void")
    void ActivateSupremeVoid();

    UFUNCTION(BlueprintCallable, Category = "Supreme Void")
    void DeactivateSupremeVoid();

    UFUNCTION(BlueprintCallable, Category = "Supreme Void")
    void SetSupremeVoidLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Supreme Void")
    void UseSupremeVoidPower();

    UFUNCTION(BlueprintCallable, Category = "Supreme Void")
    void PerformSupremeVoidAbility();

    UFUNCTION(BlueprintCallable, Category = "Supreme Void")
    bool IsSupremeVoidActive() const;

    UFUNCTION(BlueprintCallable, Category = "Supreme Void")
    int32 GetSupremeVoidLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Supreme Void")
    float GetSupremeVoidPowerCost() const;

    // Supreme Void Abilities
    UFUNCTION(BlueprintCallable, Category = "Supreme Void")
    void MasterSupremeVoid();

    UFUNCTION(BlueprintCallable, Category = "Supreme Void")
    void AnnihilateSupremely();

    UFUNCTION(BlueprintCallable, Category = "Supreme Void")
    void AchieveSupremePerfectVoidEmptiness();

    UFUNCTION(BlueprintCallable, Category = "Supreme Void")
    void InduceSupremeConceptualUltimateOblivion();

    UFUNCTION(BlueprintCallable, Category = "Supreme Void")
    void NegateSupremeUltimateExistence();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateSupremeVoid() const;
    void UpdateSupremeVoidStats();
    void OnSupremeVoidStateChanged();
};
