#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COMPLETE_QUANTUM_SUBATOMIC_SYSTEM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuantumSubatomicActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuantumSubatomicDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnQuantumSubatomicLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuantumSubatomicMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuantumSubatomicPowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuantumSubatomicPowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuantumSubatomicAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UCOMPLETE_QUANTUM_SUBATOMIC_SYSTEM : public UActorComponent
{
    GENERATED_BODY()

public:
    UCOMPLETE_QUANTUM_SUBATOMIC_SYSTEM();

    // Quantum-Subatomic Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum-Subatomic")
    int32 QuantumSubatomicLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum-Subatomic")
    int32 MaxQuantumSubatomicLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum-Subatomic")
    bool bIsQuantumSubatomicActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum-Subatomic")
    float QuantumSubatomicPowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum-Subatomic")
    float QuantumSubatomicThreshold;

    // Quantum-Subatomic Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum-Subatomic")
    float QuantumSubatomicLifeEssence;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum-Subatomic")
    float SubatomicQuantumRenewal;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum-Subatomic")
    float QuantumSubatomicEternalContinuum;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum-Subatomic")
    float TimelessQuantumSubatomicPerpetuation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quantum-Subatomic")
    float AbsoluteQuantumSubatomicSufficiency;

    // Quantum-Subatomic Events
    UPROPERTY(BlueprintAssignable, Category = "Quantum-Subatomic")
    FOnQuantumSubatomicActivated OnQuantumSubatomicActivated;

    UPROPERTY(BlueprintAssignable, Category = "Quantum-Subatomic")
    FOnQuantumSubatomicDeactivated OnQuantumSubatomicDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Quantum-Subatomic")
    FOnQuantumSubatomicLevelChanged OnQuantumSubatomicLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Quantum-Subatomic")
    FOnQuantumSubatomicMaxLevelReached OnQuantumSubatomicMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Quantum-Subatomic")
    FOnQuantumSubatomicPowerUsed OnQuantumSubatomicPowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Quantum-Subatomic")
    FOnQuantumSubatomicPowerFailed OnQuantumSubatomicPowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Quantum-Subatomic")
    FOnQuantumSubatomicAbilityPerformed OnQuantumSubatomicAbilityPerformed;

    // Quantum-Subatomic Functions
    UFUNCTION(BlueprintCallable, Category = "Quantum-Subatomic")
    void ActivateQuantumSubatomic();

    UFUNCTION(BlueprintCallable, Category = "Quantum-Subatomic")
    void DeactivateQuantumSubatomic();

    UFUNCTION(BlueprintCallable, Category = "Quantum-Subatomic")
    void SetQuantumSubatomicLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Quantum-Subatomic")
    void UseQuantumSubatomicPower();

    UFUNCTION(BlueprintCallable, Category = "Quantum-Subatomic")
    void PerformQuantumSubatomicAbility();

    UFUNCTION(BlueprintCallable, Category = "Quantum-Subatomic")
    bool IsQuantumSubatomicActive() const;

    UFUNCTION(BlueprintCallable, Category = "Quantum-Subatomic")
    int32 GetQuantumSubatomicLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Quantum-Subatomic")
    float GetQuantumSubatomicPowerCost() const;

    // Quantum-Subatomic Abilities
    UFUNCTION(BlueprintCallable, Category = "Quantum-Subatomic")
    void ChannelQuantumSubatomicLifeEssence();

    UFUNCTION(BlueprintCallable, Category = "Quantum-Subatomic")
    void RenewQuantumSubatomically();

    UFUNCTION(BlueprintCallable, Category = "Quantum-Subatomic")
    void MaintainQuantumSubatomicEternalContinuum();

    UFUNCTION(BlueprintCallable, Category = "Quantum-Subatomic")
    void PerpetuateTimelesslyQuantumSubatomic();

    UFUNCTION(BlueprintCallable, Category = "Quantum-Subatomic")
    void AchieveAbsoluteQuantumSubatomicSufficiency();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateQuantumSubatomic() const;
    void UpdateQuantumSubatomicStats();
    void OnQuantumSubatomicStateChanged();
};
