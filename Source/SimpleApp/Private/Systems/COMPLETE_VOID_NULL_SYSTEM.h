#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COMPLETE_VOID_NULL_SYSTEM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVoidNullActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVoidNullDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnVoidNullLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnVoidNullMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVoidNullPowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnVoidNullPowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVoidNullAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UCOMPLETE_VOID_NULL_SYSTEM : public UActorComponent
{
    GENERATED_BODY()

public:
    UCOMPLETE_VOID_NULL_SYSTEM();

    // Void-Null Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Void-Null")
    int32 VoidNullLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Void-Null")
    int32 MaxVoidNullLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Void-Null")
    bool bIsVoidNullActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Void-Null")
    float VoidNullPowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Void-Null")
    float VoidNullThreshold;

    // Void-Null Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Void-Null")
    float VoidNullMastery;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Void-Null")
    float UltimateVoidAnnihilation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Void-Null")
    float PerfectNullEmptiness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Void-Null")
    float ConceptualVoidOblivion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Void-Null")
    float ExistenceVoidNegation;

    // Void-Null Events
    UPROPERTY(BlueprintAssignable, Category = "Void-Null")
    FOnVoidNullActivated OnVoidNullActivated;

    UPROPERTY(BlueprintAssignable, Category = "Void-Null")
    FOnVoidNullDeactivated OnVoidNullDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Void-Null")
    FOnVoidNullLevelChanged OnVoidNullLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Void-Null")
    FOnVoidNullMaxLevelReached OnVoidNullMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Void-Null")
    FOnVoidNullPowerUsed OnVoidNullPowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Void-Null")
    FOnVoidNullPowerFailed OnVoidNullPowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Void-Null")
    FOnVoidNullAbilityPerformed OnVoidNullAbilityPerformed;

    // Void-Null Functions
    UFUNCTION(BlueprintCallable, Category = "Void-Null")
    void ActivateVoidNull();

    UFUNCTION(BlueprintCallable, Category = "Void-Null")
    void DeactivateVoidNull();

    UFUNCTION(BlueprintCallable, Category = "Void-Null")
    void SetVoidNullLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Void-Null")
    void UseVoidNullPower();

    UFUNCTION(BlueprintCallable, Category = "Void-Null")
    void PerformVoidNullAbility();

    UFUNCTION(BlueprintCallable, Category = "Void-Null")
    bool IsVoidNullActive() const;

    UFUNCTION(BlueprintCallable, Category = "Void-Null")
    int32 GetVoidNullLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Void-Null")
    float GetVoidNullPowerCost() const;

    // Void-Null Abilities
    UFUNCTION(BlueprintCallable, Category = "Void-Null")
    void MasterVoidNull();

    UFUNCTION(BlueprintCallable, Category = "Void-Null")
    void AnnihilateVoidUltimately();

    UFUNCTION(BlueprintCallable, Category = "Void-Null")
    void AchievePerfectNullEmptiness();

    UFUNCTION(BlueprintCallable, Category = "Void-Null")
    void InduceConceptualVoidOblivion();

    UFUNCTION(BlueprintCallable, Category = "Void-Null")
    void NegateExistenceVoid();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateVoidNull() const;
    void UpdateVoidNullStats();
    void OnVoidNullStateChanged();
};
