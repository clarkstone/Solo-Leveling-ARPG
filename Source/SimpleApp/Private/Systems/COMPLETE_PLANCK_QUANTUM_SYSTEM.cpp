#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "COMPLETE_PLANCK_QUANTUM_SYSTEM.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlanckQuantumActivated, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlanckQuantumDeactivated, int32, CurrentLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParam(FOnPlanckQuantumLevelChanged, int32, OldLevel, int32, NewLevel);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlanckQuantumMaxLevelReached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlanckQuantumPowerUsed, float, PowerCost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlanckQuantumPowerFailed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlanckQuantumAbilityPerformed, int32, AbilityLevel);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SIMPLEAPP_API UCOMPLETE_PLANCK_QUANTUM_SYSTEM : public UActorComponent
{
    GENERATED_BODY()

public:
    UCOMPLETE_PLANCK_QUANTUM_SYSTEM();

    // Planck-Quantum Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planck-Quantum")
    int32 PlanckQuantumLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planck-Quantum")
    int32 MaxPlanckQuantumLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planck-Quantum")
    bool bIsPlanckQuantumActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planck-Quantum")
    float PlanckQuantumPowerCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planck-Quantum")
    float PlanckQuantumThreshold;

    // Planck-Quantum Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planck-Quantum")
    float PlanckQuantumLifeEssence;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planck-Quantum")
    float QuantumPlanckRenewal;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planck-Quantum")
    float PlanckQuantumEternalContinuum;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planck-Quantum")
    float TimelessPlanckQuantumPerpetuation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Planck-Quantum")
    float AbsolutePlanckQuantumSufficiency;

    // Planck-Quantum Events
    UPROPERTY(BlueprintAssignable, Category = "Planck-Quantum")
    FOnPlanckQuantumActivated OnPlanckQuantumActivated;

    UPROPERTY(BlueprintAssignable, Category = "Planck-Quantum")
    FOnPlanckQuantumDeactivated OnPlanckQuantumDeactivated;

    UPROPERTY(BlueprintAssignable, Category = "Planck-Quantum")
    FOnPlanckQuantumLevelChanged OnPlanckQuantumLevelChanged;

    UPROPERTY(BlueprintAssignable, Category = "Planck-Quantum")
    FOnPlanckQuantumMaxLevelReached OnPlanckQuantumMaxLevelReached;

    UPROPERTY(BlueprintAssignable, Category = "Planck-Quantum")
    FOnPlanckQuantumPowerUsed OnPlanckQuantumPowerUsed;

    UPROPERTY(BlueprintAssignable, Category = "Planck-Quantum")
    FOnPlanckQuantumPowerFailed OnPlanckQuantumPowerFailed;

    UPROPERTY(BlueprintAssignable, Category = "Planck-Quantum")
    FOnPlanckQuantumAbilityPerformed OnPlanckQuantumAbilityPerformed;

    // Planck-Quantum Functions
    UFUNCTION(BlueprintCallable, Category = "Planck-Quantum")
    void ActivatePlanckQuantum();

    UFUNCTION(BlueprintCallable, Category = "Planck-Quantum")
    void DeactivatePlanckQuantum();

    UFUNCTION(BlueprintCallable, Category = "Planck-Quantum")
    void SetPlanckQuantumLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Planck-Quantum")
    void UsePlanckQuantumPower();

    UFUNCTION(BlueprintCallable, Category = "Planck-Quantum")
    void PerformPlanckQuantumAbility();

    UFUNCTION(BlueprintCallable, Category = "Planck-Quantum")
    bool IsPlanckQuantumActive() const;

    UFUNCTION(BlueprintCallable, Category = "Planck-Quantum")
    int32 GetPlanckQuantumLevel() const;

    UFUNCTION(BlueprintCallable, Category = "Planck-Quantum")
    float GetPlanckQuantumPowerCost() const;

    // Planck-Quantum Abilities
    UFUNCTION(BlueprintCallable, Category = "Planck-Quantum")
    void ChannelPlanckQuantumLifeEssence();

    UFUNCTION(BlueprintCallable, Category = "Planck-Quantum")
    void RenewPlanckQuantum();

    UFUNCTION(BlueprintCallable, Category = "Planck-Quantum")
    void MaintainPlanckQuantumEternalContinuum();

    UFUNCTION(BlueprintCallable, Category = "Planck-Quantum")
    void PerpetuateTimelesslyPlanckQuantum();

    UFUNCTION(BlueprintCallable, Category = "Planck-Quantum")
    void AchieveAbsolutePlanckQuantumSufficiency();

protected:
    virtual void BeginPlay() override;

private:
    bool CanActivatePlanckQuantum() const;
    void UpdatePlanckQuantumStats();
    void OnPlanckQuantumStateChanged();
};
