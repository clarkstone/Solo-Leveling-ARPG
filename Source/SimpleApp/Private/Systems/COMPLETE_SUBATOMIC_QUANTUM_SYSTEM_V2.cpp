#include "COMPLETE_SUBATOMIC_QUANTUM_SYSTEM_V2.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCOMPLETE_SUBATOMIC_QUANTUM_SYSTEM::UCOMPLETE_SUBATOMIC_QUANTUM_SYSTEM()
{
    PrimaryComponentTick.bCanEverTick = false;
    SubatomicQuantumLevel = 0;
    MaxSubatomicQuantumLevel = 100;
    bIsSubatomicQuantumActive = false;
    SubatomicQuantumPowerCost = 40.0f;
    SubatomicQuantumThreshold = 95.0f;
    
    // Initialize subatomic-quantum properties
    SubatomicQuantumLifeEssence = 0.0f;
    QuantumSubatomicRenewal = 0.0f;
    SubatomicQuantumEternalContinuum = 0.0f;
    TimelessSubatomicQuantumPerpetuation = 0.0f;
    AbsoluteSubatomicQuantumSufficiency = 0.0f;
}

void UCOMPLETE_SUBATOMIC_QUANTUM_SYSTEM::BeginPlay()
{
    Super::BeginPlay();
    UpdateSubatomicQuantumStats();
}

void UCOMPLETE_SUBATOMIC_QUANTUM_SYSTEM::ActivateSubatomicQuantum()
{
    if (!bIsSubatomicQuantumActive && CanActivateSubatomicQuantum())
    {
        bIsSubatomicQuantumActive = true;
        OnSubatomicQuantumActivated.Broadcast(SubatomicQuantumLevel);
        OnSubatomicQuantumStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Subatomic-Quantum System Activated at Level: %d"), SubatomicQuantumLevel);
    }
}

void UCOMPLETE_SUBATOMIC_QUANTUM_SYSTEM::DeactivateSubatomicQuantum()
{
    if (bIsSubatomicQuantumActive)
    {
        bIsSubatomicQuantumActive = false;
        OnSubatomicQuantumDeactivated.Broadcast(SubatomicQuantumLevel);
        OnSubatomicQuantumStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Subatomic-Quantum System Deactivated."));
    }
}

void UCOMPLETE_SUBATOMIC_QUANTUM_SYSTEM::SetSubatomicQuantumLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxSubatomicQuantumLevel)
    {
        int32 OldLevel = SubatomicQuantumLevel;
        SubatomicQuantumLevel = NewLevel;
        UpdateSubatomicQuantumStats();
        OnSubatomicQuantumLevelChanged.Broadcast(OldLevel, SubatomicQuantumLevel);
        UE_LOG(LogTemp, Warning, TEXT("Subatomic-Quantum Level set to: %d"), SubatomicQuantumLevel);
        
        if (SubatomicQuantumLevel >= MaxSubatomicQuantumLevel)
        {
            OnSubatomicQuantumMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Subatomic-Quantum Max Level Reached!"));
        }
    }
}

void UCOMPLETE_SUBATOMIC_QUANTUM_SYSTEM::UseSubatomicQuantumPower()
{
    if (bIsSubatomicQuantumActive && SubatomicQuantumLevel > 0)
    {
        OnSubatomicQuantumPowerUsed.Broadcast(SubatomicQuantumPowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Subatomic-Quantum Power Used: %.2f"), SubatomicQuantumPowerCost);
    }
    else
    {
        OnSubatomicQuantumPowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Subatomic-Quantum Power Use Failed: System not active or insufficient level."));
    }
}

void UCOMPLETE_SUBATOMIC_QUANTUM_SYSTEM::PerformSubatomicQuantumAbility()
{
    if (bIsSubatomicQuantumActive && SubatomicQuantumLevel >= SubatomicQuantumThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Subatomic-Quantum Ability at Level %d!"), SubatomicQuantumLevel);
        OnSubatomicQuantumAbilityPerformed.Broadcast(SubatomicQuantumLevel);
        UseSubatomicQuantumPower();
        
        // Perform subatomic-quantum ability based on level
        switch (SubatomicQuantumLevel / 20)
        {
            case 0:
                ChannelSubatomicQuantumLifeEssence();
                break;
            case 1:
                RenewSubatomicQuantum();
                break;
            case 2:
                MaintainSubatomicQuantumEternalContinuum();
                break;
            case 3:
                PerpetuateTimelesslySubatomicQuantum();
                break;
            case 4:
            case 5:
                AchieveAbsoluteSubatomicQuantumSufficiency();
                break;
            default:
                AchieveAbsoluteSubatomicQuantumSufficiency();
                break;
        }
    }
    else if (SubatomicQuantumLevel < SubatomicQuantumThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Subatomic-Quantum Level too low to perform ability. Required: %.0f, Current: %d"), SubatomicQuantumThreshold, SubatomicQuantumLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Subatomic-Quantum is not active, cannot perform ability."));
    }
}

bool UCOMPLETE_SUBATOMIC_QUANTUM_SYSTEM::IsSubatomicQuantumActive() const
{
    return bIsSubatomicQuantumActive;
}

int32 UCOMPLETE_SUBATOMIC_QUANTUM_SYSTEM::GetSubatomicQuantumLevel() const
{
    return SubatomicQuantumLevel;
}

float UCOMPLETE_SUBATOMIC_QUANTUM_SYSTEM::GetSubatomicQuantumPowerCost() const
{
    return SubatomicQuantumPowerCost;
}

void UCOMPLETE_SUBATOMIC_QUANTUM_SYSTEM::ChannelSubatomicQuantumLifeEssence()
{
    if (bIsSubatomicQuantumActive)
    {
        float LifeEssencePower = SubatomicQuantumLifeEssence * (SubatomicQuantumLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Channeling Subatomic-Quantum Life Essence with power: %.2f"), LifeEssencePower);
        // Apply subatomic-quantum life essence effects
    }
}

void UCOMPLETE_SUBATOMIC_QUANTUM_SYSTEM::RenewSubatomicQuantum()
{
    if (bIsSubatomicQuantumActive)
    {
        float RenewalPower = QuantumSubatomicRenewal * (SubatomicQuantumLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Renewing Subatomic-Quantum with power: %.2f"), RenewalPower);
        // Apply subatomic-quantum renewal effects
    }
}

void UCOMPLETE_SUBATOMIC_QUANTUM_SYSTEM::MaintainSubatomicQuantumEternalContinuum()
{
    if (bIsSubatomicQuantumActive)
    {
        float ContinuumPower = SubatomicQuantumEternalContinuum * (SubatomicQuantumLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Maintaining Subatomic-Quantum Eternal Continuum with power: %.2f"), ContinuumPower);
        // Apply subatomic-quantum eternal continuum effects
    }
}

void UCOMPLETE_SUBATOMIC_QUANTUM_SYSTEM::PerpetuateTimelesslySubatomicQuantum()
{
    if (bIsSubatomicQuantumActive)
    {
        float PerpetuationPower = TimelessSubatomicQuantumPerpetuation * (SubatomicQuantumLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Perpetuating Timelessly Subatomic-Quantum with power: %.2f"), PerpetuationPower);
        // Apply timeless subatomic-quantum perpetuation effects
    }
}

void UCOMPLETE_SUBATOMIC_QUANTUM_SYSTEM::AchieveAbsoluteSubatomicQuantumSufficiency()
{
    if (bIsSubatomicQuantumActive)
    {
        float SufficiencyPower = AbsoluteSubatomicQuantumSufficiency * (SubatomicQuantumLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Absolute Subatomic-Quantum Sufficiency with power: %.2f"), SufficiencyPower);
        // Apply absolute subatomic-quantum sufficiency effects
    }
}

bool UCOMPLETE_SUBATOMIC_QUANTUM_SYSTEM::CanActivateSubatomicQuantum() const
{
    return SubatomicQuantumLevel > 0;
}

void UCOMPLETE_SUBATOMIC_QUANTUM_SYSTEM::UpdateSubatomicQuantumStats()
{
    // Update subatomic-quantum properties based on level
    SubatomicQuantumLifeEssence = SubatomicQuantumLevel * 12.6f;
    QuantumSubatomicRenewal = SubatomicQuantumLevel * 12.4f;
    SubatomicQuantumEternalContinuum = SubatomicQuantumLevel * 12.5f;
    TimelessSubatomicQuantumPerpetuation = SubatomicQuantumLevel * 12.3f;
    AbsoluteSubatomicQuantumSufficiency = SubatomicQuantumLevel * 13.1f;
}

void UCOMPLETE_SUBATOMIC_QUANTUM_SYSTEM::OnSubatomicQuantumStateChanged()
{
    // Handle state change effects
    if (bIsSubatomicQuantumActive)
    {
        // Apply subatomic-quantum activation effects
        UE_LOG(LogTemp, Warning, TEXT("Subatomic-Quantum state changed to ACTIVE"));
    }
    else
    {
        // Remove subatomic-quantum effects
        UE_LOG(LogTemp, Warning, TEXT("Subatomic-Quantum state changed to INACTIVE"));
    }
}
