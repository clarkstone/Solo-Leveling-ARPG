#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COMPLETE_QUANTUM_STRING_SYSTEM_V2.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuantumStringActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuantumStringDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnQuantumStringLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuantumStringMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuantumStringPowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuantumStringPowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuantumStringAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UCOMPLETE_QUANTUM_STRING_SYSTEM : public UActorComponent
{
    GENERATED_BODY()

public:
    UCOMPLETE_QUANTUM_STRING_SYSTEM();

    // Quantum-String Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum-String")
    int32 QuantumStringLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum-String")
    int32 MaxQuantumStringLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum-String")
    bool bIsQuantumStringActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum-String")
    float QuantumStringPowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum-String")
    float QuantumStringThreshold;

    // Quantum-String Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum-String")
    float QuantumStringLifeEssence;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum-String")
    float StringQuantumRenewal;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum-String")
    float QuantumStringEternalContinuum;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum-String")
    float TimelessQuantumStringPerpetuation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum-String")
    float AbsoluteQuantumStringSufficiency;

    // Quantum-String Events
    UPROPERTY(BlueprintAssignable, Category = "Quantum-String")
    FOnQuantumStringActivated OnQuantumStringActivated;

    UPROPERTY(BlueprintAssignable, Category = "Quantum-String")
    FOnQuantumStringDeactivated OnQuantumStringDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Quantum-String")
    FOnQuantumStringLevelChanged OnQuantumStringLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Quantum-String")
    FOnQuantumStringMaxLevelReached OnQuantumStringMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Quantum-String")
    FOnQuantumStringPowerUsed OnQuantumStringPowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Quantum-String")
    FOnQuantumStringPowerFailed OnQuantumStringPowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Quantum-String")
    FOnQuantumStringAbilityPerformed OnQuantumStringAbilityPerformed;

    // Quantum-String Functions
    UFUNCTION(BlueprintCallable, Category = "Quantum-String")
    void ActivateQuantumString();

    UFUNCTION(BlueprintCallable, Category = "Quantum-String")
    void DeactivateQuantumString();

    UFUNCTION(BlueprintCallable, Category = "Quantum-String")
    void SetQuantumStringLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Quantum-String")
    void UseQuantumStringPower();

    UFUNCTION(BlueprintCallable, Category = "Quantum-String")
    void PerformQuantumStringAbility();

    UFUNCTION(BlueprintCallable, Category = "Quantum-String")
    bool IsQuantumStringActive() const;

    UFUNCTION(BlueprintCallable, Category = "Quantum-String")
    int32 GetQuantumStringLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Quantum-String")
    float GetQuantumStringPowerCost() const;

    // Quantum-String Abilities
    UFUNCTION(BlueprintCallable, Category = "Quantum-String")
    void ChannelQuantumStringLifeEssence();

    UFUNCTION(BlueprintCallable, Category = "Quantum-String")
    void RenewQuantumString();

    UFUNCTION(BlueprintCallable, Category = "Quantum-String")
    void MaintainQuantumStringEternalContinuum();

    UFUNCTION(BlueprintCallable, Category = "Quantum-String")
    void PerpetuateTimelesslyQuantumString();

    UFUNCTION(BlueprintCallable, Category = "Quantum-String")
    void AchieveAbsoluteQuantumStringSufficiency();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateQuantumString() const;
    void UpdateQuantumStringStats();
    void OnQuantumStringStateChanged();
};
