#include "P07_OMEGA_STATE_SYSTEM_V2.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP07_OMEGA_STATE_SYSTEM_V2::UP07_OMEGA_STATE_SYSTEM_V2()
{
    PrimaryComponentTick.bCanEverTick = false;
    OmegaStateLevel = 0;
    MaxOmegaStateLevel = 100;
    bIsOmegaStateActive = false;
    OmegaStatePowerCost = 45.0f;
    OmegaStateThreshold = 40.0f;
    
    // Initialize omega state properties
    OmegaPhaseUltimacy = 0.0f;
    FinalStateAuthority = 0.0f;
    StateTransitions = 0.0f;
    UltimateConsciousness = 0.0f;
    FinalUltimacy = 0.0f;
}

void UP07_OMEGA_STATE_SYSTEM_V2::BeginPlay()
{
    Super::BeginPlay();
    UpdateOmegaStateStats();
}

void UP07_OMEGA_STATE_SYSTEM_V2::ActivateOmegaState()
{
    if (!bIsOmegaStateActive && CanActivateOmegaState())
    {
        bIsOmegaStateActive = true;
        OnOmegaStateActivated.Broadcast(OmegaStateLevel);
        OnOmegaStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Omega State V2 System Activated at Level: %d"), OmegaStateLevel);
    }
}

void UP07_OMEGA_STATE_SYSTEM_V2::DeactivateOmegaState()
{
    if (bIsOmegaStateActive)
    {
        bIsOmegaStateActive = false;
        OnOmegaStateDeactivated.Broadcast(OmegaStateLevel);
        OnOmegaStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Omega State V2 System Deactivated."));
    }
}

void UP07_OMEGA_STATE_SYSTEM_V2::SetOmegaStateLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxOmegaStateLevel)
    {
        int32 OldLevel = OmegaStateLevel;
        OmegaStateLevel = NewLevel;
        UpdateOmegaStateStats();
        OnOmegaStateChanged(OldLevel, OmegaStateLevel);
        UE_LOG(LogTemp, Warning, TEXT("Omega State V2 Level set to: %d"), OmegaStateLevel);
        
        if (OmegaStateLevel >= MaxOmegaStateLevel)
        {
            OnOmegaStateMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Omega State V2 Max Level Reached!"));
        }
    }
}

void UP07_OMEGA_STATE_SYSTEM_V2::UseOmegaStatePower()
{
    if (bIsOmegaStateActive && OmegaStateLevel > 0)
    {
        OnOmegaStatePowerUsed.Broadcast(OmegaStatePowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Omega State V2 Power Used: %.2f"), OmegaStatePowerCost);
    }
    else
    {
        OnOmegaStatePowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Omega State Power Use Failed: System not active or insufficient level."));
    }
}

void UP07_OMEGA_STATE_SYSTEM_V2::PerformOmegaStateAbility()
{
    if (bIsOmegaStateActive && OmegaStateLevel >= OmegaStateThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Omega State V2 Ability at Level %d!"), OmegaStateLevel);
        OnOmegaStateAbilityPerformed.Broadcast(OmegaStateLevel);
        UseOmegaStatePower();
        
        // Perform omega state ability based on level
        switch (OmegaStateLevel / 20)
        {
            case 0:
                ExerciseOmegaPhaseUltimacy();
                    break;
            case 1:
                AchieveOmegaPhaseFinalUltimacy();
                    break;
            case 2:
                ControlFinalStateTransitions();
                    break;
            case 3:
                AccessUltimateConsciousness();
                    break;
            case 4:
            case 5:
                WieldFinalUltimacy();
                    break;
            default:
                WieldFinalUltimacy();
                    break;
        }
    }
    }
    }
    else if (OmegaStateLevel < OmegaStateThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Omega State Level too low to perform ability. Required: %.0f, Current: %d"), OmegaStateThreshold, OmegaStateLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Omega State is not active, cannot perform ability."));
    }
}

bool UP07_OMEGA_STATE_SYSTEM_V2::IsOmegaStateActive() const
{
    return bIsOmegaStateActive;
}

int32 UP07_OMEGA_STATE_SYSTEM_V2::GetOmegaStateLevel() const
{
    return OmegaStateLevel;
}

float UP07_OMEGA_STATE_SYSTEM_V2::GetOmegaStatePowerCost() const
{
    return OmegaStatePowerCost;
}

void UP07_OMEGA_STATE_SYSTEM_V2::ExerciseOmegaPhaseUltimacy()
{
    if (bIsOmegaStateActive)
    {
        float UltimacyPower = OmegaPhaseUltimacy * (OmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Exercising Omega Phase Ultimacy V2 with power: %.2f"), UltimacyPower);
        // Apply omega phase ultimacy effects
    }
}

void UP07_OMEGA_STATE_SYSTEM_V2::AchieveOmegaPhaseFinalUltimacy()
{
    if (bIsOmegaStateActive)
    {
        float UltimacyPower = OmegaPhaseUltimacy * (OmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Omega Phase Final Ultimacy V2 with power: %.2f"), UltimacyPower);
        // Apply omega phase final ultimacy effects
    }
}

void UP07_OMEGA_STATE_SYSTEM_V2::ControlFinalStateTransitions()
{
    if (bIsOmegaStateActive)
    {
        float TransitionPower = StateTransitions * (OmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Controlling Final State Transitions V2 with power: %.2f"), TransitionPower);
        // Apply final state transition control effects
    }
}

void UP07_OMEGA_STATE_SYSTEM_V2::AccessUltimateConsciousness()
{
    if (bIsOmegaStateActive)
    {
        float ConsciousnessPower = UltimateConsciousness * (OmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Accessing Ultimate Consciousness V2 with power: %.2f"), ConsciousnessPower);
        // Apply ultimate consciousness effects
    }
}

void UP07_OMEGA_STATE_SYSTEM_V2::WieldFinalUltimacy()
{
    if (bIsOmegaStateActive)
    {
        float UltimacyPower = FinalUltimacy * (OmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Wielding Final Ultimacy V2 with power: %.2f"), UltimacyPower);
        // Apply final ultimacy effects
    }
}

bool UP07_OMEGA_STATE_SYSTEM_V2::CanActivateOmegaState() const
{
    return OmegaStateLevel > 0;
}

void UP07_OMEGA_STATE_SYSTEM_V2::UpdateOmegaStateStats()
{
    // Update omega state properties based on level
    OmegaPhaseUltimacy = OmegaStateLevel * 4.5f;
    FinalStateAuthority = OmegaStateLevel * 4.7f;
    StateTransitions = OmegaStateLevel * 4.3f;
    UltimateConsciousness = OmegaStateLevel * 4.4f;
    FinalUltimacy = OmegaStateLevel * 4.6f;
}

void UP07_OMEGA_STATE_SYSTEM_V2::OnOmegaStateChanged()
{
    // Handle state change effects
    if (bIsOmegaStateActive)
    {
        // Apply omega state activation effects
        UE_LOG(LogTemp, Warning, TEXT("Omega State V2 state changed to ACTIVE"));
    }
    else
    {
        // Remove omega state effects
        UE_LOG(LogTemp, Warning, TEXT("Omega State V2 state changed to INACTIVE"));
    }
}
