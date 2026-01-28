#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COMPLETE_NULL_ABSOLUTE_VOID_SYSTEM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNullAbsoluteVoidActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNullAbsoluteVoidDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnNullAbsoluteVoidLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNullAbsoluteVoidMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNullAbsoluteVoidPowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNullAbsoluteVoidPowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNullAbsoluteVoidAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UCOMPLETE_NULL_ABSOLUTE_VOID_SYSTEM : public UActorComponent
{
    GENERATED_BODY()

public:
    UCOMPLETE_NULL_ABSOLUTE_VOID_SYSTEM();

    // Null-Absolute-Void Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Null-Absolute-Void")
    int32 NullAbsoluteVoidLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Null-Absolute-Void")
    int32 MaxNullAbsoluteVoidLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Null-Absolute-Void")
    bool bIsNullAbsoluteVoidActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Null-Absolute-Void")
    float NullAbsoluteVoidPowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Null-Absolute-Void")
    float NullAbsoluteVoidThreshold;

    // Null-Absolute-Void Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Null-Absolute-Void")
    float NullAbsoluteVoidMastery;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Null-Absolute-Void")
    float AbsoluteVoidAnnihilation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Null-Absolute-Void")
    float PerfectNullEmptiness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Null-Absolute-Void")
    float ConceptualNullOblivion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Null-Absolute-Void")
    float ExistenceNullNegation;

    // Null-Absolute-Void Events
    UPROPERTY(BlueprintAssignable, Category = "Null-Absolute-Void")
    FOnNullAbsoluteVoidActivated OnNullAbsoluteVoidActivated;

    UPROPERTY(BlueprintAssignable, Category = "Null-Absolute-Void")
    FOnNullAbsoluteVoidDeactivated OnNullAbsoluteVoidDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Null-Absolute-Void")
    FOnNullAbsoluteVoidLevelChanged OnNullAbsoluteVoidLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Null-Absolute-Void")
    FOnNullAbsoluteVoidMaxLevelReached OnNullAbsoluteVoidMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Null-Absolute-Void")
    FOnNullAbsoluteVoidPowerUsed OnNullAbsoluteVoidPowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Null-Absolute-Void")
    FOnNullAbsoluteVoidPowerFailed OnNullAbsoluteVoidPowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Null-Absolute-Void")
    FOnNullAbsoluteVoidAbilityPerformed OnNullAbsoluteVoidAbilityPerformed;

    // Null-Absolute-Void Functions
    UFUNCTION(BlueprintCallable, Category = "Null-Absolute-Void")
    void ActivateNullAbsoluteVoid();

    UFUNCTION(BlueprintCallable, Category = "Null-Absolute-Void")
    void DeactivateNullAbsoluteVoid();

    UFUNCTION(BlueprintCallable, Category = "Null-Absolute-Void")
    void SetNullAbsoluteVoidLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Null-Absolute-Void")
    void UseNullAbsoluteVoidPower();

    UFUNCTION(BlueprintCallable, Category = "Null-Absolute-Void")
    void PerformNullAbsoluteVoidAbility();

    UFUNCTION(BlueprintCallable, Category = "Null-Absolute-Void")
    bool IsNullAbsoluteVoidActive() const;

    UFUNCTION(BlueprintCallable, Category = "Null-Absolute-Void")
    int32 GetNullAbsoluteVoidLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Null-Absolute-Void")
    float GetNullAbsoluteVoidPowerCost() const;

    // Null-Absolute-Void Abilities
    UFUNCTION(BlueprintCallable, Category = "Null-Absolute-Void")
    void MasterNullAbsoluteVoid();

    UFUNCTION(BlueprintCallable, Category = "Null-Absolute-Void")
    void AnnihilateNullAbsolutely();

    UFUNCTION(BlueprintCallable, Category = "Null-Absolute-Void")
    void AchievePerfectNullEmptiness();

    UFUNCTION(BlueprintCallable, Category = "Null-Absolute-Void")
    void InduceConceptualNullOblivion();

    UFUNCTION(BlueprintCallable, Category = "Null-Absolute-Void")
    void NegateExistenceNull();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateNullAbsoluteVoid() const;
    void UpdateNullAbsoluteVoidStats();
    void OnNullAbsoluteVoidStateChanged();
};
