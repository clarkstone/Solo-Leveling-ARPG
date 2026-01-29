#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "P10_VOID_ETERNAL.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEternalVoidActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEternalVoidDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnEternalVoidLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEternalVoidMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEternalVoidPowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEternalVoidPowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEternalVoidAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UP10_VOID_ETERNAL : public UActorComponent
{
    GENERATED_BODY()

public:
    UP10_VOID_ETERNAL();

    // Eternal Void Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal Void")
    int32 EternalVoidLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal Void")
    int32 MaxEternalVoidLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal Void")
    bool bIsEternalVoidActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal Void")
    float EternalVoidPowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal Void")
    float EternalVoidThreshold;

    // Eternal Void Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal Void")
    float EternalVoidMastery;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal Void")
    float EternalUltimateAnnihilation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal Void")
    float EternalPerfectVoidEmptiness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal Void")
    float EternalConceptualUltimateOblivion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eternal Void")
    float EternalExistenceUltimateNegation;

    // Eternal Void Events
    UPROPERTY(BlueprintAssignable, Category = "Eternal Void")
    FOnEternalVoidActivated OnEternalVoidActivated;

    UPROPERTY(BlueprintAssignable, Category = "Eternal Void")
    FOnEternalVoidDeactivated OnEternalVoidDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Eternal Void")
    FOnEternalVoidLevelChanged OnEternalVoidLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Eternal Void")
    FOnEternalVoidMaxLevelReached OnEternalVoidMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Eternal Void")
    FOnEternalVoidPowerUsed OnEternalVoidPowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Eternal Void")
    FOnEternalVoidPowerFailed OnEternalVoidPowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Eternal Void")
    FOnEternalVoidAbilityPerformed OnEternalVoidAbilityPerformed;

    // Eternal Void Functions
    UFUNCTION(BlueprintCallable, Category = "Eternal Void")
    void ActivateEternalVoid();

    UFUNCTION(BlueprintCallable, Category = "Eternal Void")
    void DeactivateEternalVoid();

    UFUNCTION(BlueprintCallable, Category = "Eternal Void")
    void SetEternalVoidLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Eternal Void")
    void UseEternalVoidPower();

    UFUNCTION(BlueprintCallable, Category = "Eternal Void")
    void PerformEternalVoidAbility();

    UFUNCTION(BlueprintCallable, Category = "Eternal Void")
    bool IsEternalVoidActive() const;

    UFUNCTION(BlueprintCallable, Category = "Eternal Void")
    int32 GetEternalVoidLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Eternal Void")
    float GetEternalVoidPowerCost() const;

    // Eternal Void Abilities
    UFUNCTION(BlueprintCallable, Category = "Eternal Void")
    void MasterEternalVoid();

    UFUNCTION(BlueprintCallable, Category = "Eternal Void")
    void AnnihilateEternally();

    UFUNCTION(BlueprintCallable, Category = "Eternal Void")
    void AchieveEternalPerfectVoidEmptiness();

    UFUNCTION(BlueprintCallable, Category = "Eternal Void")
    void InduceEternalConceptualUltimateOblivion();

    UFUNCTION(BlueprintCallable, Category = "Eternal Void")
    void NegateEternalUltimateExistence();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateEternalVoid() const;
    void UpdateEternalVoidStats();
    void OnEternalVoidStateChanged();
};
