#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P07_VOID_ULTRA_V2.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltraVoidActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltraVoidDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnUltraVoidLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUltraVoidMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltraVoidPowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUltraVoidPowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltraVoidAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP07_VOID_ULTRA_V2 : public UActorComponent
{
    GENERATED_BODY()

public:
    UP07_VOID_ULTRA_V2();

    // Ultra Void Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Void")
    int32 UltraVoidLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Void")
    int32 MaxUltraVoidLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Void")
    bool bIsUltraVoidActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Void")
    float UltraVoidPowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Void")
    float UltraVoidThreshold;

    // Ultra Void Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Void")
    float VoidMastery;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Void")
    float UltimateAnnihilation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Void")
    float PerfectVoidEmptiness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Void")
    float ConceptualUltimateOblivion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ultra Void")
    float ExistenceUltimateNegation;

    // Ultra Void Events
    UPROPERTY(BlueprintAssignable, Category = "Ultra Void")
    FOnUltraVoidActivated OnUltraVoidActivated;

    UPROPERTY(BlueprintAssignable, Category = "Ultra Void")
    FOnUltraVoidDeactivated OnUltraVoidDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Ultra Void")
    FOnUltraVoidLevelChanged OnUltraVoidLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Ultra Void")
    FOnUltraVoidMaxLevelReached OnUltraVoidMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Ultra Void")
    FOnUltraVoidPowerUsed OnUltraVoidPowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Ultra Void")
    FOnUltraVoidPowerFailed OnUltraVoidPowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Ultra Void")
    FOnUltraVoidAbilityPerformed OnUltraVoidAbilityPerformed;

    // Ultra Void Functions
    UFUNCTION(BlueprintCallable, Category = "Ultra Void")
    void ActivateUltraVoid();

    UFUNCTION(BlueprintCallable, Category = "Ultra Void")
    void DeactivateUltraVoid();

    UFUNCTION(BlueprintCallable, Category = "Ultra Void")
    void SetUltraVoidLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Ultra Void")
    void UseUltraVoidPower();

    UFUNCTION(BlueprintCallable, Category = "Ultra Void")
    void PerformUltraVoidAbility();

    UFUNCTION(BlueprintCallable, Category = "Ultra Void")
    bool IsUltraVoidActive() const;

    UFUNCTION(BlueprintCallable, Category = "Ultra Void")
    int32 GetUltraVoidLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Ultra Void")
    float GetUltraVoidPowerCost() const;

    // Ultra Void Abilities
    UFUNCTION(BlueprintCallable, Category = "Ultra Void")
    void MasterUltraVoid();

    UFUNCTION(BlueprintCallable, Category = "Ultra Void")
    void AnnihilateUltimately();

    UFUNCTION(BlueprintCallable, Category = "Ultra Void")
    void AchievePerfectVoidEmptiness();

    UFUNCTION(BlueprintCallable, Category = "Ultra Void")
    void InduceConceptualUltimateOblivion();

    UFUNCTION(BlueprintCallable, Category = "Ultra Void")
    void NegateUltimateExistence();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateUltraVoid() const;
    void UpdateUltraVoidStats();
    void OnUltraVoidStateChanged();
};
