#include "COMPLETE_PLANCK_QUANTUM_SYSTEM.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCOMPLETE_PLANCK_QUANTUM_SYSTEM::UCOMPLETE_PLANCK_QUANTUM_SYSTEM()
{
    PrimaryComponentTick.bCanEverTick = false;
    PlanckQuantumLevel = 0;
    MaxPlanckQuantumLevel = 100;
    bIsPlanckQuantumActive = false;
    PlanckQuantumPowerCost = 50.0f;
    PlanckQuantumThreshold = 100.0f;
    
    // Initialize planck-quantum properties
    PlanckQuantumLifeEssence = 0.0f;
    QuantumPlanckRenewal = 0.0f;
    PlanckQuantumEternalContinuum = 0.0f;
    TimelessPlanckQuantumPerpetuation = 0.0f;
    AbsolutePlanckQuantumSufficiency = 0.0f;
}

void UCOMPLETE_PLANCK_QUANTUM_SYSTEM::BeginPlay()
{
    Super::BeginPlay();
    UpdatePlanckQuantumStats();
}

void UCOMPLETE_PLANCK_QUANTUM_SYSTEM::ActivatePlanckQuantum()
{
    if (!bIsPlanckQuantumActive && CanActivatePlanckQuantum())
    {
        bIsPlanckQuantumActive = true;
        OnPlanckQuantumActivated.Broadcast(PlanckQuantumLevel);
        OnPlanckQuantumStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Planck-Quantum System Activated at Level: %d"), PlanckQuantumLevel);
    }
}

void UCOMPLETE_PLANCK_QUANTUM_SYSTEM::DeactivatePlanckQuantum()
{
    if (bIsPlanckQuantumActive)
    {
        bIsPlanckQuantumActive = false;
        OnPlanckQuantumDeactivated.Broadcast(PlanckQuantumLevel);
        OnPlanckQuantumStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Planck-Quantum System Deactivated."));
    }
}

void UCOMPLETE_PLANCK_QUANTUM_SYSTEM::SetPlanckQuantumLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxPlanckQuantumLevel)
    {
        int32 OldLevel = PlanckQuantumLevel;
        PlanckQuantumLevel = NewLevel;
        UpdatePlanckQuantumStats();
        OnPlanckQuantumLevelChanged.Broadcast(OldLevel, PlanckQuantumLevel);
        UE_LOG(LogTemp, Warning, TEXT("Planck-Quantum Level set to: %d"), PlanckQuantumLevel);
        
        if (PlanckQuantumLevel >= MaxPlanckQuantumLevel)
        {
            OnPlanckQuantumMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Planck-Quantum Max Level Reached!"));
        }
    }
}

void UCOMPLETE_PLANCK_QUANTUM_SYSTEM::UsePlanckQuantumPower()
{
    if (bIsPlanckQuantumActive && PlanckQuantumLevel > 0)
    {
        OnPlanckQuantumPowerUsed.Broadcast(PlanckQuantumPowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Planck-Quantum Power Used: %.2f"), PlanckQuantumPowerCost);
    }
    else
    {
        OnPlanckQuantumPowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Planck-Quantum Power Use Failed: System not active or insufficient level."));
    }
}

void UCOMPLETE_PLANCK_QUANTUM_SYSTEM::PerformPlanckQuantumAbility()
{
    if (bIsPlanckQuantumActive && PlanckQuantumLevel >= PlanckQuantumThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Planck-Quantum Ability at Level %d!"), PlanckQuantumLevel);
        OnPlanckQuantumAbilityPerformed.Broadcast(PlanckQuantumLevel);
        UsePlanckQuantumPower();
        
        // Perform planck-quantum ability based on level
        switch (PlanckQuantumLevel / 20)
        {
            case 0:
                ChannelPlanckQuantumLifeEssence();
                break;
            case 1:
                RenewPlanckQuantum();
                break;
            case 2:
                MaintainPlanckQuantumEternalContinuum();
                break;
            case 3:
                PerpetuateTimelesslyPlanckQuantum();
                break;
            case 4:
            case 5:
                AchieveAbsolutePlanckQuantumSufficiency();
                break;
            default:
                AchieveAbsolutePlanckQuantumSufficiency();
                break;
        }
    }
    else if (PlanckQuantumLevel < PlanckQuantumThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Planck-Quantum Level too low to perform ability. Required: %.0f, Current: %d"), PlanckQuantumThreshold, PlanckQuantumLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Planck-Quantum is not active, cannot perform ability."));
    }
}

bool UCOMPLETE_PLANCK_QUANTUM_SYSTEM::IsPlanckQuantumActive() const
{
    return bIsPlanckQuantumActive;
}

int32 UCOMPLETE_PLANCK_QUANTUM_SYSTEM::GetPlanckQuantumLevel() const
{
    return PlanckQuantumLevel;
}

float UCOMPLETE_PLANCK_QUANTUM_SYSTEM::GetPlanckQuantumPowerCost() const
{
    return PlanckQuantumPowerCost;
}

void UCOMPLETE_PLANCK_QUANTUM_SYSTEM::ChannelPlanckQuantumLifeEssence()
{
    if (bIsPlanckQuantumActive)
    {
        float LifeEssencePower = PlanckQuantumLifeEssence * (PlanckQuantumLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Channeling Planck-Quantum Life Essence with power: %.2f"), LifeEssencePower);
        // Apply planck-quantum life essence effects
    }
}

void UCOMPLETE_PLANCK_QUANTUM_SYSTEM::RenewPlanckQuantum()
{
    if (bIsPlanckQuantumActive)
    {
        float RenewalPower = QuantumPlanckRenewal * (PlanckQuantumLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Renewing Planck-Quantum with power: %.2f"), RenewalPower);
        // Apply planck-quantum renewal effects
    }
}

void UCOMPLETE_PLANCK_QUANTUM_SYSTEM::MaintainPlanckQuantumEternalContinuum()
{
    if (bIsPlanckQuantumActive)
    {
        float ContinuumPower = PlanckQuantumEternalContinuum * (PlanckQuantumLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Maintaining Planck-Quantum Eternal Continuum with power: %.2f"), ContinuumPower);
        // Apply planck-quantum eternal continuum effects
    }
}

void UCOMPLETE_PLANCK_QUANTUM_SYSTEM::PerpetuateTimelesslyPlanckQuantum()
{
    if (bIsPlanckQuantumActive)
    {
        float PerpetuationPower = TimelessPlanckQuantumPerpetuation * (PlanckQuantumLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Perpetuating Timelessly Planck-Quantum with power: %.2f"), PerpetuationPower);
        // Apply timeless planck-quantum perpetuation effects
    }
}

void UCOMPLETE_PLANCK_QUANTUM_SYSTEM::AchieveAbsolutePlanckQuantumSufficiency()
{
    if (bIsPlanckQuantumActive)
    {
        float SufficiencyPower = AbsolutePlanckQuantumSufficiency * (PlanckQuantumLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Absolute Planck-Quantum Sufficiency with power: %.2f"), SufficiencyPower);
        // Apply absolute planck-quantum sufficiency effects
    }
}

bool UCOMPLETE_PLANCK_QUANTUM_SYSTEM::CanActivatePlanckQuantum() const
{
    return PlanckQuantumLevel > 0;
}

void UCOMPLETE_PLANCK_QUANTUM_SYSTEM::UpdatePlanckQuantumStats()
{
    // Update planck-quantum properties based on level
    PlanckQuantumLifeEssence = PlanckQuantumLevel * 16.5f;
    QuantumPlanckRenewal = PlanckQuantumLevel * 16.3f;
    PlanckQuantumEternalContinuum = PlanckQuantumLevel * 16.4f;
    TimelessPlanckQuantumPerpetuation = PlanckQuantumLevel * 16.2f;
    AbsolutePlanckQuantumSufficiency = PlanckQuantumLevel * 17.0f;
}

void UCOMPLETE_PLANCK_QUANTUM_SYSTEM::OnPlanckQuantumStateChanged()
{
    // Handle state change effects
    if (bIsPlanckQuantumActive)
    {
        // Apply planck-quantum activation effects
        UE_LOG(LogTemp, Warning, TEXT("Planck-Quantum state changed to ACTIVE"));
    }
    else
    {
        // Remove planck-quantum effects
        UE_LOG(LogTemp, Warning, TEXT("Planck-Quantum state changed to INACTIVE"));
    }
}
