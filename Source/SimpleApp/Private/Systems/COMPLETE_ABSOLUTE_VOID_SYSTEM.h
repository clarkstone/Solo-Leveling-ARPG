#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COMPLETE_ABSOLUTE_VOID_SYSTEM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbsoluteVoidActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbsoluteVoidDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnAbsoluteVoidLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbsoluteVoidMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbsoluteVoidPowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbsoluteVoidPowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbsoluteVoidAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UCOMPLETE_ABSOLUTE_VOID_SYSTEM : public UActorComponent
{
    GENERATED_BODY()

public:
    UCOMPLETE_ABSOLUTE_VOID_SYSTEM();

    // Absolute-Void Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute-Void")
    int32 AbsoluteVoidLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute-Void")
    int32 MaxAbsoluteVoidLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute-Void")
    bool bIsAbsoluteVoidActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute-Void")
    float AbsoluteVoidPowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute-Void")
    float AbsoluteVoidThreshold;

    // Absolute-Void Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute-Void")
    float AbsoluteVoidMastery;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute-Void")
    float UltimateAnnihilation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute-Void")
    float PerfectEmptiness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute-Void")
    float ConceptualOblivion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute-Void")
    float ExistenceNegation;

    // Absolute-Void Events
    UPROPERTY(BlueprintAssignable, Category = "Absolute-Void")
    FOnAbsoluteVoidActivated OnAbsoluteVoidActivated;

    UPROPERTY(BlueprintAssignable, Category = "Absolute-Void")
    FOnAbsoluteVoidDeactivated OnAbsoluteVoidDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Absolute-Void")
    FOnAbsoluteVoidLevelChanged OnAbsoluteVoidLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Absolute-Void")
    FOnAbsoluteVoidMaxLevelReached OnAbsoluteVoidMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Absolute-Void")
    FOnAbsoluteVoidPowerUsed OnAbsoluteVoidPowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Absolute-Void")
    FOnAbsoluteVoidPowerFailed OnAbsoluteVoidPowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Absolute-Void")
    FOnAbsoluteVoidAbilityPerformed OnAbsoluteVoidAbilityPerformed;

    // Absolute-Void Functions
    UFUNCTION(BlueprintCallable, Category = "Absolute-Void")
    void ActivateAbsoluteVoid();

    UFUNCTION(BlueprintCallable, Category = "Absolute-Void")
    void DeactivateAbsoluteVoid();

    UFUNCTION(BlueprintCallable, Category = "Absolute-Void")
    void SetAbsoluteVoidLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Absolute-Void")
    void UseAbsoluteVoidPower();

    UFUNCTION(BlueprintCallable, Category = "Absolute-Void")
    void PerformAbsoluteVoidAbility();

    UFUNCTION(BlueprintCallable, Category = "Absolute-Void")
    bool IsAbsoluteVoidActive() const;

    UFUNCTION(BlueprintCallable, Category = "Absolute-Void")
    int32 GetAbsoluteVoidLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Absolute-Void")
    float GetAbsoluteVoidPowerCost() const;

    // Absolute-Void Abilities
    UFUNCTION(BlueprintCallable, Category = "Absolute-Void")
    void MasterAbsoluteVoid();

    UFUNCTION(BlueprintCallable, Category = "Absolute-Void")
    void AnnihilateUltimately();

    UFUNCTION(BlueprintCallable, Category = "Absolute-Void")
    void AchievePerfectEmptiness();

    UFUNCTION(BlueprintCallable, Category = "Absolute-Void")
    void InduceConceptualOblivion();

    UFUNCTION(BlueprintCallable, Category = "Absolute-Void")
    void NegateExistence();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateAbsoluteVoid() const;
    void UpdateAbsoluteVoidStats();
    void OnAbsoluteVoidStateChanged();
};
