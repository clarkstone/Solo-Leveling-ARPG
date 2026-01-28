#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COMPLETE_SUBATOMIC_QUANTUM_SYSTEM_V2.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSubatomicQuantumActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSubatomicQuantumDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnSubatomicQuantumLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSubatomicQuantumMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSubatomicQuantumPowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSubatomicQuantumPowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSubatomicQuantumAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UCOMPLETE_SUBATOMIC_QUANTUM_SYSTEM : public UActorComponent
{
    GENERATED_BODY()

public:
    UCOMPLETE_SUBATOMIC_QUANTUM_SYSTEM();

    // Subatomic-Quantum Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subatomic-Quantum")
    int32 SubatomicQuantumLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subatomic-Quantum")
    int32 MaxSubatomicQuantumLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subatomic-Quantum")
    bool bIsSubatomicQuantumActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subatomic-Quantum")
    float SubatomicQuantumPowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subatomic-Quantum")
    float SubatomicQuantumThreshold;

    // Subatomic-Quantum Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subatomic-Quantum")
    float SubatomicQuantumLifeEssence;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subatomic-Quantum")
    float QuantumSubatomicRenewal;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subatomic-Quantum")
    float SubatomicQuantumEternalContinuum;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subatomic-Quantum")
    float TimelessSubatomicQuantumPerpetuation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Subatomic-Quantum")
    float AbsoluteSubatomicQuantumSufficiency;

    // Subatomic-Quantum Events
    UPROPERTY(BlueprintAssignable, Category = "Subatomic-Quantum")
    FOnSubatomicQuantumActivated OnSubatomicQuantumActivated;

    UPROPERTY(BlueprintAssignable, Category = "Subatomic-Quantum")
    FOnSubatomicQuantumDeactivated OnSubatomicQuantumDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Subatomic-Quantum")
    FOnSubatomicQuantumLevelChanged OnSubatomicQuantumLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Subatomic-Quantum")
    FOnSubatomicQuantumMaxLevelReached OnSubatomicQuantumMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Subatomic-Quantum")
    FOnSubatomicQuantumPowerUsed OnSubatomicQuantumPowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Subatomic-Quantum")
    FOnSubatomicQuantumPowerFailed OnSubatomicQuantumPowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Subatomic-Quantum")
    FOnSubatomicQuantumAbilityPerformed OnSubatomicQuantumAbilityPerformed;

    // Subatomic-Quantum Functions
    UFUNCTION(BlueprintCallable, Category = "Subatomic-Quantum")
    void ActivateSubatomicQuantum();

    UFUNCTION(BlueprintCallable, Category = "Subatomic-Quantum")
    void DeactivateSubatomicQuantum();

    UFUNCTION(BlueprintCallable, Category = "Subatomic-Quantum")
    void SetSubatomicQuantumLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Subatomic-Quantum")
    void UseSubatomicQuantumPower();

    UFUNCTION(BlueprintCallable, Category = "Subatomic-Quantum")
    void PerformSubatomicQuantumAbility();

    UFUNCTION(BlueprintCallable, Category = "Subatomic-Quantum")
    bool IsSubatomicQuantumActive() const;

    UFUNCTION(BlueprintCallable, Category = "Subatomic-Quantum")
    int32 GetSubatomicQuantumLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Subatomic-Quantum")
    float GetSubatomicQuantumPowerCost() const;

    // Subatomic-Quantum Abilities
    UFUNCTION(BlueprintCallable, Category = "Subatomic-Quantum")
    void ChannelSubatomicQuantumLifeEssence();

    UFUNCTION(BlueprintCallable, Category = "Subatomic-Quantum")
    void RenewSubatomicQuantum();

    UFUNCTION(BlueprintCallable, Category = "Subatomic-Quantum")
    void MaintainSubatomicQuantumEternalContinuum();

    UFUNCTION(BlueprintCallable, Category = "Subatomic-Quantum")
    void PerpetuateTimelesslySubatomicQuantum();

    UFUNCTION(BlueprintCallable, Category = "Subatomic-Quantum")
    void AchieveAbsoluteSubatomicQuantumSufficiency();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivateSubatomicQuantum() const;
    void UpdateSubatomicQuantumStats();
    void OnSubatomicQuantumStateChanged();
};
