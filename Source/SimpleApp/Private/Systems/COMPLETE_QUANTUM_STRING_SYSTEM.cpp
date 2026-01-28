#include "COMPLETE_QUANTUM_STRING_SYSTEM.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCOMPLETE_QUANTUM_STRING_SYSTEM::UCOMPLETE_QUANTUM_STRING_SYSTEM()
{
    PrimaryComponentTick.bCanEverTick = false;
    QuantumStringLevel = 0;
    MaxQuantumStringLevel = 100;
    bIsQuantumStringActive = false;
    QuantumStringPowerCost = 55.0f;
    QuantumStringThreshold = 100.0f;
    
    // Initialize quantum-string properties
    QuantumStringLifeEssence = 0.0f;
    StringQuantumRenewal = 0.0f;
    QuantumStringEternalContinuum = 0.0f;
    TimelessQuantumStringPerpetuation = 0.0f;
    AbsoluteQuantumStringSufficiency = 0.0f;
}

void UCOMPLETE_QUANTUM_STRING_SYSTEM::BeginPlay()
{
    Super::BeginPlay();
    UpdateQuantumStringStats();
}

void UCOMPLETE_QUANTUM_STRING_SYSTEM::ActivateQuantumString()
{
    if (!bIsQuantumStringActive && CanActivateQuantumString())
    {
        bIsQuantumStringActive = true;
        OnQuantumStringActivated.Broadcast(QuantumStringLevel);
        OnQuantumStringStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Quantum-String System Activated at Level: %d"), QuantumStringLevel);
    }
}

void UCOMPLETE_QUANTUM_STRING_SYSTEM::DeactivateQuantumString()
{
    if (bIsQuantumStringActive)
    {
        bIsQuantumStringActive = false;
        OnQuantumStringDeactivated.Broadcast(QuantumStringLevel);
        OnQuantumStringStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Quantum-String System Deactivated."));
    }
}

void UCOMPLETE_QUANTUM_STRING_SYSTEM::SetQuantumStringLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxQuantumStringLevel)
    {
        int32 OldLevel = QuantumStringLevel;
        QuantumStringLevel = NewLevel;
        UpdateQuantumStringStats();
        OnQuantumStringLevelChanged.Broadcast(OldLevel, QuantumStringLevel);
        UE_LOG(LogTemp, Warning, TEXT("Quantum-String Level set to: %d"), QuantumStringLevel);
        
        if (QuantumStringLevel >= MaxQuantumStringLevel)
        {
            OnQuantumStringMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Quantum-String Max Level Reached!"));
        }
    }
}

void UCOMPLETE_QUANTUM_STRING_SYSTEM::UseQuantumStringPower()
{
    if (bIsQuantumStringActive && QuantumStringLevel > 0)
    {
        OnQuantumStringPowerUsed.Broadcast(QuantumStringPowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Quantum-String Power Used: %.2f"), QuantumStringPowerCost);
    }
    else
    {
        OnQuantumStringPowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Quantum-String Power Use Failed: System not active or insufficient level."));
    }
}

void UCOMPLETE_QUANTUM_STRING_SYSTEM::PerformQuantumStringAbility()
{
    if (bIsQuantumStringActive && QuantumStringLevel >= QuantumStringThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Quantum-String Ability at Level %d!"), QuantumStringLevel);
        OnQuantumStringAbilityPerformed.Broadcast(QuantumStringLevel);
        UseQuantumStringPower();
        
        // Perform quantum-string ability based on level
        switch (QuantumStringLevel / 20)
        {
            case 0:
                ChannelQuantumStringLifeEssence();
                break;
            case 1:
                RenewQuantumString();
                break;
            case 2:
                MaintainQuantumStringEternalContinuum();
                break;
            case 3:
                PerpetuateTimelesslyQuantumString();
                break;
            case 4:
            case 5:
                AchieveAbsoluteQuantumStringSufficiency();
                break;
            default:
                AchieveAbsoluteQuantumStringSufficiency();
                break;
        }
    }
    else if (QuantumStringLevel < QuantumStringThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Quantum-String Level too low to perform ability. Required: %.0f, Current: %d"), QuantumStringThreshold, QuantumStringLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Quantum-String is not active, cannot perform ability."));
    }
}

bool UCOMPLETE_QUANTUM_STRING_SYSTEM::IsQuantumStringActive() const
{
    return bIsQuantumStringActive;
}

int32 UCOMPLETE_QUANTUM_STRING_SYSTEM::GetQuantumStringLevel() const
{
    return QuantumStringLevel;
}

float UCOMPLETE_QUANTUM_STRING_SYSTEM::GetQuantumStringPowerCost() const
{
    return QuantumStringPowerCost;
}

void UCOMPLETE_QUANTUM_STRING_SYSTEM::ChannelQuantumStringLifeEssence()
{
    if (bIsQuantumStringActive)
    {
        float LifeEssencePower = QuantumStringLifeEssence * (QuantumStringLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Channeling Quantum-String Life Essence with power: %.2f"), LifeEssencePower);
        // Apply quantum-string life essence effects
    }
}

void UCOMPLETE_QUANTUM_STRING_SYSTEM::RenewQuantumString()
{
    if (bIsQuantumStringActive)
    {
        float RenewalPower = StringQuantumRenewal * (QuantumStringLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Renewing Quantum-String with power: %.2f"), RenewalPower);
        // Apply quantum-string renewal effects
    }
}

void UCOMPLETE_QUANTUM_STRING_SYSTEM::MaintainQuantumStringEternalContinuum()
{
    if (bIsQuantumStringActive)
    {
        float ContinuumPower = QuantumStringEternalContinuum * (QuantumStringLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Maintaining Quantum-String Eternal Continuum with power: %.2f"), ContinuumPower);
        // Apply quantum-string eternal continuum effects
    }
}

void UCOMPLETE_QUANTUM_STRING_SYSTEM::PerpetuateTimelesslyQuantumString()
{
    if (bIsQuantumStringActive)
    {
        float PerpetuationPower = TimelessQuantumStringPerpetuation * (QuantumStringLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Perpetuating Timelessly Quantum-String with power: %.2f"), PerpetuationPower);
        // Apply timeless quantum-string perpetuation effects
    }
}

void UCOMPLETE_QUANTUM_STRING_SYSTEM::AchieveAbsoluteQuantumStringSufficiency()
{
    if (bIsQuantumStringActive)
    {
        float SufficiencyPower = AbsoluteQuantumStringSufficiency * (QuantumStringLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Absolute Quantum-String Sufficiency with power: %.2f"), SufficiencyPower);
        // Apply absolute quantum-string sufficiency effects
    }
}

bool UCOMPLETE_QUANTUM_STRING_SYSTEM::CanActivateQuantumString() const
{
    return QuantumStringLevel > 0;
}

void UCOMPLETE_QUANTUM_STRING_SYSTEM::UpdateQuantumStringStats()
{
    // Update quantum-string properties based on level
    QuantumStringLifeEssence = QuantumStringLevel * 20.5f;
    StringQuantumRenewal = QuantumStringLevel * 20.3f;
    QuantumStringEternalContinuum = QuantumStringLevel * 20.4f;
    TimelessQuantumStringPerpetuation = QuantumStringLevel * 20.2f;
    AbsoluteQuantumStringSufficiency = QuantumStringLevel * 21.0f;
}

void UCOMPLETE_QUANTUM_STRING_SYSTEM::OnQuantumStringStateChanged()
{
    // Handle state change effects
    if (bIsQuantumStringActive)
    {
        // Apply quantum-string activation effects
        UE_LOG(LogTemp, Warning, TEXT("Quantum-String state changed to ACTIVE"));
    }
    else
    {
        // Remove quantum-string effects
        UE_LOG(LogTemp, Warning, TEXT("Quantum-String state changed to INACTIVE"));
    }
}
