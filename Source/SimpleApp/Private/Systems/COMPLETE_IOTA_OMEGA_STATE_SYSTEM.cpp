#include "COMPLETE_IOTA_OMEGA_STATE_SYSTEM.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCOMPLETE_IOTA_OMEGA_STATE_SYSTEM::UCOMPLETE_IOTA_OMEGA_STATE_SYSTEM()
{
    PrimaryComponentTick.bCanEverTick = false;
    IotaOmegaStateLevel = 0;
    MaxIotaOmegaStateLevel = 100;
    bIsIotaOmegaStateActive = false;
    IotaOmegaStatePowerCost = 35.0f;
    IotaOmegaStateThreshold = 90.0f;
    
    // Initialize iota-omega state properties
    IotaPhaseSupremeUltimacy = 0.0f;
    OmegaPhaseAbsoluteFinality = 0.0f;
    SupremeStateTransition = 0.0f;
    QuantumSubatomicStateSupremacy = 0.0f;
    FinalStateAbsoluteUltimacy = 0.0f;
}

void UCOMPLETE_IOTA_OMEGA_STATE_SYSTEM::BeginPlay()
{
    Super::BeginPlay();
    UpdateIotaOmegaStateStats();
}

void UCOMPLETE_IOTA_OMEGA_STATE_SYSTEM::ActivateIotaOmegaState()
{
    if (!bIsIotaOmegaStateActive && CanActivateIotaOmegaState())
    {
        bIsIotaOmegaStateActive = true;
        OnIotaOmegaStateActivated.Broadcast(IotaOmegaStateLevel);
        OnIotaOmegaStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Iota-Omega State System Activated at Level: %d"), IotaOmegaStateLevel);
    }
}

void UCOMPLETE_IOTA_OMEGA_STATE_SYSTEM::DeactivateIotaOmegaState()
{
    if (bIsIotaOmegaStateActive)
    {
        bIsIotaOmegaStateActive = false;
        OnIotaOmegaStateDeactivated.Broadcast(IotaOmegaStateLevel);
        OnIotaOmegaStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Iota-Omega State System Deactivated."));
    }
}

void UCOMPLETE_IOTA_OMEGA_STATE_SYSTEM::SetIotaOmegaStateLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxIotaOmegaStateLevel)
    {
        int32 OldLevel = IotaOmegaStateLevel;
        IotaOmegaStateLevel = NewLevel;
        UpdateIotaOmegaStateStats();
        OnIotaOmegaStateChanged.Broadcast(OldLevel, IotaOmegaStateLevel);
        UE_LOG(LogTemp, Warning, TEXT("Iota-Omega State Level set to: %d"), IotaOmegaStateLevel);
        
        if (IotaOmegaStateLevel >= MaxIotaOmegaStateLevel)
        {
            OnIotaOmegaStateMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Iota-Omega State Max Level Reached!"));
        }
    }
}

void UCOMPLETE_IOTA_OMEGA_STATE_SYSTEM::UseIotaOmegaStatePower()
{
    if (bIsIotaOmegaStateActive && IotaOmegaStateLevel > 0)
    {
        OnIotaOmegaStatePowerUsed.Broadcast(IotaOmegaStatePowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Iota-Omega State Power Used: %.2f"), IotaOmegaStatePowerCost);
    }
    else
    {
        OnIotaOmegaStatePowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Iota-Omega State Power Use Failed: System not active or insufficient level."));
    }
}

void UCOMPLETE_IOTA_OMEGA_STATE_SYSTEM::PerformIotaOmegaStateAbility()
{
    if (bIsIotaOmegaStateActive && IotaOmegaStateLevel >= IotaOmegaStateThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Iota-Omega State Ability at Level %d!"), IotaOmegaStateLevel);
        OnIotaOmegaStateAbilityPerformed.Broadcast(IotaOmegaStateLevel);
        UseIotaOmegaStatePower();
        
        // Perform iota-omega state ability based on level
        switch (IotaOmegaStateLevel / 20)
        {
            case 0:
                ExerciseIotaPhaseSupremeUltimacy();
                break;
            case 1:
                AchieveOmegaPhaseAbsoluteFinality();
                break;
            case 2:
                ControlSupremeStateTransitions();
                break;
            case 3:
                DominateQuantumSubatomicStates();
                break;
            case 4:
            case 5:
                WieldFinalStateAbsoluteUltimacy();
                break;
            default:
                WieldFinalStateAbsoluteUltimacy();
                break;
        }
    }
    else if (IotaOmegaStateLevel < IotaOmegaStateThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Iota-Omega State Level too low to perform ability. Required: %.0f, Current: %d"), IotaOmegaStateThreshold, IotaOmegaStateLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Iota-Omega State is not active, cannot perform ability."));
    }
}

bool UCOMPLETE_IOTA_OMEGA_STATE_SYSTEM::IsIotaOmegaStateActive() const
{
    return bIsIotaOmegaStateActive;
}

int32 UCOMPLETE_IOTA_OMEGA_STATE_SYSTEM::GetIotaOmegaStateLevel() const
{
    return IotaOmegaStateLevel;
}

float UCOMPLETE_IOTA_OMEGA_STATE_SYSTEM::GetIotaOmegaStatePowerCost() const
{
    return IotaOmegaStatePowerCost;
}

void UCOMPLETE_IOTA_OMEGA_STATE_SYSTEM::ExerciseIotaPhaseSupremeUltimacy()
{
    if (bIsIotaOmegaStateActive)
    {
        float UltimacyPower = IotaPhaseSupremeUltimacy * (IotaOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Exercising Iota Phase Supreme Ultimacy with power: %.2f"), UltimacyPower);
        // Apply iota phase supreme ultimacy effects
    }
}

void UCOMPLETE_IOTA_OMEGA_STATE_SYSTEM::AchieveOmegaPhaseAbsoluteFinality()
{
    if (bIsIotaOmegaStateActive)
    {
        float FinalityPower = OmegaPhaseAbsoluteFinality * (IotaOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Omega Phase Absolute Finality with power: %.2f"), FinalityPower);
        // Apply omega phase absolute finality effects
    }
}

void UCOMPLETE_IOTA_OMEGA_STATE_SYSTEM::ControlSupremeStateTransitions()
{
    if (bIsIotaOmegaStateActive)
    {
        float TransitionPower = SupremeStateTransition * (IotaOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Controlling Supreme State Transitions with power: %.2f"), TransitionPower);
        // Apply supreme state transition control effects
    }
}

void UCOMPLETE_IOTA_OMEGA_STATE_SYSTEM::DominateQuantumSubatomicStates()
{
    if (bIsIotaOmegaStateActive)
    {
        float SubatomicPower = QuantumSubatomicStateSupremacy * (IotaOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Dominating Quantum-Subatomic States with power: %.2f"), SubatomicPower);
        // Apply quantum-subatomic state domination effects
    }
}

void UCOMPLETE_IOTA_OMEGA_STATE_SYSTEM::WieldFinalStateAbsoluteUltimacy()
{
    if (bIsIotaOmegaStateActive)
    {
        float FinalStatePower = FinalStateAbsoluteUltimacy * (IotaOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Wielding Final State Absolute Ultimacy with power: %.2f"), FinalStatePower);
        // Apply final state absolute ultimacy effects
    }
}

bool UCOMPLETE_IOTA_OMEGA_STATE_SYSTEM::CanActivateIotaOmegaState() const
{
    return IotaOmegaStateLevel > 0;
}

void UCOMPLETE_IOTA_OMEGA_STATE_SYSTEM::UpdateIotaOmegaStateStats()
{
    // Update iota-omega state properties based on level
    IotaPhaseSupremeUltimacy = IotaOmegaStateLevel * 11.5f;
    OmegaPhaseAbsoluteFinality = IotaOmegaStateLevel * 11.3f;
    SupremeStateTransition = IotaOmegaStateLevel * 11.2f;
    QuantumSubatomicStateSupremacy = IotaOmegaStateLevel * 11.1f;
    FinalStateAbsoluteUltimacy = IotaOmegaStateLevel * 12.0f;
}

void UCOMPLETE_IOTA_OMEGA_STATE_SYSTEM::OnIotaOmegaStateChanged()
{
    // Handle state change effects
    if (bIsIotaOmegaStateActive)
    {
        // Apply iota-omega state activation effects
        UE_LOG(LogTemp, Warning, TEXT("Iota-Omega State state changed to ACTIVE"));
    }
    else
    {
        // Remove iota-omega state effects
        UE_LOG(LogTemp, Warning, TEXT("Iota-Omega State state changed to INACTIVE"));
    }
}
