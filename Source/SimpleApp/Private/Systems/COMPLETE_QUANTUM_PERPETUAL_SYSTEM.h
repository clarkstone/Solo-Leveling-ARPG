#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COMPLETE_QUANTUM_PERPETUAL_SYSTEM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuantumPerpetualActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuantumPerpetualDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnQuantumPerpetualLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuantumPerpetualMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuantumPerpetualPowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuantumPerpetualPowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuantumPerpetualAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UCOMPLETE_QUANTUM_PERPETUAL_SYSTEM : public UActorComponent
{
    GENERATED_BODY()

public:
    UCOMPLETE_QUANTUM_PERPETUAL_SYSTEM();

    // Quantum-Perpetual Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum-Perpetual")
    int32 QuantumPerpetualLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum-Perpetual")
    int32 MaxQuantumPerpetualLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum-Perpetual")
    bool bIsQuantumPerpetualActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum-Perpetual")
    float QuantumPerpetualPowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum-Perpetual")
    float QuantumPerpetualThreshold;

    // Quantum-Perpetual Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum-Perpetual")
    float QuantumLifeEssence;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum-Perpetual")
    float PerpetualQuantumRenewal;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum-Perpetual")
    float QuantumEternalContinuum;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum-Perpetual")
    float TimelessQuantumPerpetuation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum-Perpetual")
    float AbsoluteQuantumSufficiency;

    // Quantum-Perpetual Events
    UPROPERTY(BlueprintAssignable, Category = "Quantum-Perpetual")
    FOnQuantumPerpetualActivated OnQuantumPerpetualActivated;

    UPROPERTY(BlueprintAssignable, Category = "Quantum-Perpetual")
    FOnQuantumPerpetualDeactivated OnQuantumPerpetualDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Quantum-Perpetual")
    FOnQuantumPerpetualLevelChanged OnQuantumPerpetualLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Quantum-Perpetual")
    FOnQuantumPerpetualMaxLevelReached OnQuantumPerpetualMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Quantum-Perpetual")
    FOnQuantumPerpetualPowerUsed OnQuantumPerpetualPowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Quantum-Perpetual")
    FOnQuantumPerpetualPowerFailed OnQuantumPerpetualPowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Quantum-Perpetual")
    FOnQuantumPerpetualAbilityPerformed OnQuantumPerpetualAbilityPerformed;

    // Quantum-Perpetual Functions
    UFUNCTION(BlueprintCallable, Category = "Quantum-Perpetual")
    void ActivateQuantumPerpetual();

    UFUNCTION(BlueprintCallable, Category = "Quantum-Perpetual")
    void DeactivateQuantumPerpetual();

    UFUNCTION(BlueprintCallable, Category = "Quantum-Perpetual")
    void SetQuantumPerpetualLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Quantum-Perpetual")
    void UseQuantumPerpetualPower();

    UFUNCTION(BlueprintCallable, Category = "Quantum-Perpetual")
    void PerformQuantumPerpetualAbility();

    UFUNCTION(BlueprintCallable, Category = "Quantum-Perpetual")
    bool IsQuantumPerpetualActive() const;

    UFUNCTION(BlueprintCallable, Category = "Quantum-Perpetual")
    int32 GetQuantumPerpetualLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Quantum-Perpetual")
    float GetQuantumPerpetualPowerCost() const;

    // Quantum-Perpetual Abilities
    UFUNCTION(BlueprintCallable, Category = "Quantum-Perpetual")
    void ChannelQuantumLifeEssence();

    UFUNCTION(BlueprintCallable, Category = "Quantum-Perpetual")
    void RenewPerpetuallyQuantum();

    UFUNCTION(BlueprintCallable, Category = "Quantum-Perpetual")
    void MaintainQuantumEternalContinuum();

    UFUNCTION(BlueprintCallable, Category = "Quantum-Perpetual")
    void PerpetuateTimelesslyQuantum();

    UFUNCTION(BlueprintCallable, Category = "Quantum-Perpetual")
    void AchieveAbsoluteQuantumSufficiency();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateQuantumPerpetual() const;
    void UpdateQuantumPerpetualStats();
    void OnQuantumPerpetualStateChanged();
};
