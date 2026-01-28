#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COMPLETE_ABSOLUTE_VOID_NULL_SYSTEM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbsoluteVoidNullActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbsoluteVoidNullDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnAbsoluteVoidNullLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbsoluteVoidNullMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbsoluteVoidNullPowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbsoluteVoidNullPowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbsoluteVoidNullAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UCOMPLETE_ABSOLUTE_VOID_NULL_SYSTEM : public UActorComponent
{
    GENERATED_BODY()

public:
    UCOMPLETE_ABSOLUTE_VOID_NULL_SYSTEM();

    // Absolute-Void-Null Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute-Void-Null")
    int32 AbsoluteVoidNullLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute-Void-Null")
    int32 MaxAbsoluteVoidNullLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute-Void-Null")
    bool bIsAbsoluteVoidNullActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute-Void-Null")
    float AbsoluteVoidNullPowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute-Void-Null")
    float AbsoluteVoidNullThreshold;

    // Absolute-Void-Null Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute-Void-Null")
    float AbsoluteVoidNullMastery;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute-Void-Null")
    float SupremeVoidAnnihilation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute-Void-Null")
    float PerfectNullVoidEmptiness;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute-Void-Null")
    float ConceptualVoidNullOblivion;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Absolute-Void-Null")
    float ExistenceVoidNullNegation;

    // Absolute-Void-Null Events
    UPROPERTY(BlueprintAssignable, Category = "Absolute-Void-Null")
    FOnAbsoluteVoidNullActivated OnAbsoluteVoidNullActivated;

    UPROPERTY(BlueprintAssignable, Category = "Absolute-Void-Null")
    FOnAbsoluteVoidNullDeactivated OnAbsoluteVoidNullDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Absolute-Void-Null")
    FOnAbsoluteVoidNullLevelChanged OnAbsoluteVoidNullLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Absolute-Void-Null")
    FOnAbsoluteVoidNullMaxLevelReached OnAbsoluteVoidNullMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Absolute-Void-Null")
    FOnAbsoluteVoidNullPowerUsed OnAbsoluteVoidNullPowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Absolute-Void-Null")
    FOnAbsoluteVoidNullPowerFailed OnAbsoluteVoidNullPowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Absolute-Void-Null")
    FOnAbsoluteVoidNullAbilityPerformed OnAbsoluteVoidNullAbilityPerformed;

    // Absolute-Void-Null Functions
    UFUNCTION(BlueprintCallable, Category = "Absolute-Void-Null")
    void ActivateAbsoluteVoidNull();

    UFUNCTION(BlueprintCallable, Category = "Absolute-Void-Null")
    void DeactivateAbsoluteVoidNull();

    UFUNCTION(BlueprintCallable, Category = "Absolute-Void-Null")
    void SetAbsoluteVoidNullLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Absolute-Void-Null")
    void UseAbsoluteVoidNullPower();

    UFUNCTION(BlueprintCallable, Category = "Absolute-Void-Null")
    void PerformAbsoluteVoidNullAbility();

    UFUNCTION(BlueprintCallable, Category = "Absolute-Void-Null")
    bool IsAbsoluteVoidNullActive() const;

    UFUNCTION(BlueprintCallable, Category = "Absolute-Void-Null")
    int32 GetAbsoluteVoidNullLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Absolute-Void-Null")
    float GetAbsoluteVoidNullPowerCost() const;

    // Absolute-Void-Null Abilities
    UFUNCTION(BlueprintCallable, Category = "Absolute-Void-Null")
    void MasterAbsoluteVoidNull();

    UFUNCTION(BlueprintCallable, Category = "Absolute-Void-Null")
    void AnnihilateVoidNullSupremely();

    UFUNCTION(BlueprintCallable, Category = "Absolute-Void-Null")
    void AchievePerfectNullVoidEmptiness();

    UFUNCTION(BlueprintCallable, Category = "Absolute-Void-Null")
    void InduceConceptualVoidNullOblivion();

    UFUNCTION(BlueprintCallable, Category = "Absolute-Void-Null")
    void NegateExistenceVoidNull();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateAbsoluteVoidNull() const;
    void UpdateAbsoluteVoidNullStats();
    void OnAbsoluteVoidNullStateChanged();
};
