#include "COMPLETE_QUANTUM_SUBATOMIC_SYSTEM.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCOMPLETE_QUANTUM_SUBATOMIC_SYSTEM::UCOMPLETE_QUANTUM_SUBATOMIC_SYSTEM()
{
    PrimaryComponentTick.bCanEverTick = false;
    QuantumSubatomicLevel = 0;
    MaxQuantumSubatomicLevel = 100;
    bIsQuantumSubatomicActive = false;
    QuantumSubatomicPowerCost = 35.0f;
    QuantumSubatomicThreshold = 90.0f;
    
    // Initialize quantum-subatomic properties
    QuantumSubatomicLifeEssence = 0.0f;
    SubatomicQuantumRenewal = 0.0f;
    QuantumSubatomicEternalContinuum = 0.0f;
    TimelessQuantumSubatomicPerpetuation = 0.0f;
    AbsoluteQuantumSubatomicSufficiency = 0.0f;
}

void UCOMPLETE_QUANTUM_SUBATOMIC_SYSTEM::BeginPlay()
{
    Super::BeginPlay();
    UpdateQuantumSubatomicStats();
}

void UCOMPLETE_QUANTUM_SUBATOMIC_SYSTEM::ActivateQuantumSubatomic()
{
    if (!bIsQuantumSubatomicActive && CanActivateQuantumSubatomic())
    {
        bIsQuantumSubatomicActive = true;
        OnQuantumSubatomicActivated.Broadcast(QuantumSubatomicLevel);
        OnQuantumSubatomicStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Quantum-Subatomic System Activated at Level: %d"), QuantumSubatomicLevel);
    }
}

void UCOMPLETE_QUANTUM_SUBATOMIC_SYSTEM::DeactivateQuantumSubatomic()
{
    if (bIsQuantumSubatomicActive)
    {
        bIsQuantumSubatomicActive = false;
        OnQuantumSubatomicDeactivated.Broadcast(QuantumSubatomicLevel);
        OnQuantumSubatomicStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Quantum-Subatomic System Deactivated."));
    }
}

void UCOMPLETE_QUANTUM_SUBATOMIC_SYSTEM::SetQuantumSubatomicLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxQuantumSubatomicLevel)
    {
        int32 OldLevel = QuantumSubatomicLevel;
        QuantumSubatomicLevel = NewLevel;
        UpdateQuantumSubatomicStats();
        OnQuantumSubatomicLevelChanged.Broadcast(OldLevel, QuantumSubatomicLevel);
        UE_LOG(LogTemp, Warning, TEXT("Quantum-Subatomic Level set to: %d"), QuantumSubatomicLevel);
        
        if (QuantumSubatomicLevel >= MaxQuantumSubatomicLevel)
        {
            OnQuantumSubatomicMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Quantum-Subatomic Max Level Reached!"));
        }
    }
}

void UCOMPLETE_QUANTUM_SUBATOMIC_SYSTEM::UseQuantumSubatomicPower()
{
    if (bIsQuantumSubatomicActive && QuantumSubatomicLevel > 0)
    {
        OnQuantumSubatomicPowerUsed.Broadcast(QuantumSubatomicPowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Quantum-Subatomic Power Used: %.2f"), QuantumSubatomicPowerCost);
    }
    else
    {
        OnQuantumSubatomicPowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Quantum-Subatomic Power Use Failed: System not active or insufficient level."));
    }
}

void UCOMPLETE_QUANTUM_SUBATOMIC_SYSTEM::PerformQuantumSubatomicAbility()
{
    if (bIsQuantumSubatomicActive && QuantumSubatomicLevel >= QuantumSubatomicThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Quantum-Subatomic Ability at Level %d!"), QuantumSubatomicLevel);
        OnQuantumSubatomicAbilityPerformed.Broadcast(QuantumSubatomicLevel);
        UseQuantumSubatomicPower();
        
        // Perform quantum-subatomic ability based on level
        switch (QuantumSubatomicLevel / 20)
        {
            case 0:
                ChannelQuantumSubatomicLifeEssence();
                break;
            case 1:
                RenewQuantumSubatomically();
                break;
            case 2:
                MaintainQuantumSubatomicEternalContinuum();
                break;
            case 3:
                PerpetuateTimelesslyQuantumSubatomic();
                break;
            case 4:
            case 5:
                AchieveAbsoluteQuantumSubatomicSufficiency();
                break;
            default:
                AchieveAbsoluteQuantumSubatomicSufficiency();
                break;
        }
    }
    else if (QuantumSubatomicLevel < QuantumSubatomicThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Quantum-Subatomic Level too low to perform ability. Required: %.0f, Current: %d"), QuantumSubatomicThreshold, QuantumSubatomicLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Quantum-Subatomic is not active, cannot perform ability."));
    }
}

bool UCOMPLETE_QUANTUM_SUBATOMIC_SYSTEM::IsQuantumSubatomicActive() const
{
    return bIsQuantumSubatomicActive;
}

int32 UCOMPLETE_QUANTUM_SUBATOMIC_SYSTEM::GetQuantumSubatomicLevel() const
{
    return QuantumSubatomicLevel;
}

float UCOMPLETE_QUANTUM_SUBATOMIC_SYSTEM::GetQuantumSubatomicPowerCost() const
{
    return QuantumSubatomicPowerCost;
}

void UCOMPLETE_QUANTUM_SUBATOMIC_SYSTEM::ChannelQuantumSubatomicLifeEssence()
{
    if (bIsQuantumSubatomicActive)
    {
        float LifeEssencePower = QuantumSubatomicLifeEssence * (QuantumSubatomicLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Channeling Quantum-Subatomic Life Essence with power: %.2f"), LifeEssencePower);
        // Apply quantum-subatomic life essence effects
    }
}

void UCOMPLETE_QUANTUM_SUBATOMIC_SYSTEM::RenewQuantumSubatomically()
{
    if (bIsQuantumSubatomicActive)
    {
        float RenewalPower = SubatomicQuantumRenewal * (QuantumSubatomicLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Renewing Quantum-Subatomically with power: %.2f"), RenewalPower);
        // Apply quantum-subatomic renewal effects
    }
}

void UCOMPLETE_QUANTUM_SUBATOMIC_SYSTEM::MaintainQuantumSubatomicEternalContinuum()
{
    if (bIsQuantumSubatomicActive)
    {
        float ContinuumPower = QuantumSubatomicEternalContinuum * (QuantumSubatomicLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Maintaining Quantum-Subatomic Eternal Continuum with power: %.2f"), ContinuumPower);
        // Apply quantum-subatomic eternal continuum effects
    }
}

void UCOMPLETE_QUANTUM_SUBATOMIC_SYSTEM::PerpetuateTimelesslyQuantumSubatomic()
{
    if (bIsQuantumSubatomicActive)
    {
        float PerpetuationPower = TimelessQuantumSubatomicPerpetuation * (QuantumSubatomicLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Perpetuating Timelessly Quantum-Subatomic with power: %.2f"), PerpetuationPower);
        // Apply timeless quantum-subatomic perpetuation effects
    }
}

void UCOMPLETE_QUANTUM_SUBATOMIC_SYSTEM::AchieveAbsoluteQuantumSubatomicSufficiency()
{
    if (bIsQuantumSubatomicActive)
    {
        float SufficiencyPower = AbsoluteQuantumSubatomicSufficiency * (QuantumSubatomicLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Absolute Quantum-Subatomic Sufficiency with power: %.2f"), SufficiencyPower);
        // Apply absolute quantum-subatomic sufficiency effects
    }
}

bool UCOMPLETE_QUANTUM_SUBATOMIC_SYSTEM::CanActivateQuantumSubatomic() const
{
    return QuantumSubatomicLevel > 0;
}

void UCOMPLETE_QUANTUM_SUBATOMIC_SYSTEM::UpdateQuantumSubatomicStats()
{
    // Update quantum-subatomic properties based on level
    QuantumSubatomicLifeEssence = QuantumSubatomicLevel * 9.6f;
    SubatomicQuantumRenewal = QuantumSubatomicLevel * 9.4f;
    QuantumSubatomicEternalContinuum = QuantumSubatomicLevel * 9.5f;
    TimelessQuantumSubatomicPerpetuation = QuantumSubatomicLevel * 9.3f;
    AbsoluteQuantumSubatomicSufficiency = QuantumSubatomicLevel * 10.1f;
}

void UCOMPLETE_QUANTUM_SUBATOMIC_SYSTEM::OnQuantumSubatomicStateChanged()
{
    // Handle state change effects
    if (bIsQuantumSubatomicActive)
    {
        // Apply quantum-subatomic activation effects
        UE_LOG(LogTemp, Warning, TEXT("Quantum-Subatomic state changed to ACTIVE"));
    }
    else
    {
        // Remove quantum-subatomic effects
        UE_LOG(LogTemp, Warning, TEXT("Quantum-Subatomic state changed to INACTIVE"));
    }
}
