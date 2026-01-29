#include "P17_OMEGA_STATE_SYSTEM.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP17_OMEGA_STATE_SYSTEM::UP17_OMEGA_STATE_SYSTEM()
{
    PrimaryComponentTick.bCanEverTick = false;
    OmegaStateLevel = 0;
    MaxOmegaStateLevel = 100;
    bIsOmegaStateActive = false;
    OmegaStatePowerCost = 90.0f;
    OmegaStateThreshold = 90.0f;
    
    // Initialize omega state properties
    OmegaPhaseUltimacy = 0.0f;
    FinalStateAuthority = 0.0f;
    StateTransitions = 0.0f;
    UltimateConsciousness = 0.0f;
    FinalUltimacy = 0.0f;
}

void UP17_OMEGA_STATE_SYSTEM::BeginPlay()
{
    Super::BeginPlay();
    UpdateOmegaStateStats();
}

void UP17_OMEGA_STATE_SYSTEM::ActivateOmegaState()
{
    if (!bIsOmegaStateActive && CanActivateOmegaState())
    {
        bIsOmegaStateActive = true;
        OnOmegaStateActivated.Broadcast(OmegaStateLevel);
        OnOmegaStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Omega State System Activated at Level: %d"), OmegaStateLevel);
    }
}

void UP17_OMEGA_STATE_SYSTEM::DeactivateOmegaState()
{
    if (bIsOmegaStateActive)
    {
        bIsOmegaStateActive = false;
        OnOmegaStateDeactivated.Broadcast(OmegaStateLevel);
        OnOmegaStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Omega State System Deactivated."));
    }
}

void UP17_OMEGA_STATE_SYSTEM::SetOmegaStateLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxOmegaStateLevel)
    {
        int32 OldLevel = OmegaStateLevel;
        OmegaStateLevel = NewLevel;
        UpdateOmegaStateStats();
        OnOmegaStateChanged(OldLevel, OmegaStateLevel);
        UE_LOG(LogTemp, Warning, TEXT("Omega State Level set to: %d"), OmegaStateLevel);
        
        if (OmegaStateLevel >= MaxOmegaStateLevel)
        {
            OnOmegaStateMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Omega State Max Level Reached!"));
        }
    }
}

void UP17_OMEGA_STATE_SYSTEM::UseOmegaStatePower()
{
    if (bIsOmegaStateActive && OmegaStateLevel > 0)
    {
        OnOmegaStatePowerUsed.Broadcast(OmegaStatePowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Omega State Power Used: %.2f"), OmegaStatePowerCost);
    }
    else
    {
        OnOmegaStatePowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Omega State Power Use Failed: System not active or insufficient level."));
    }
}

void UP17_OMEGA_STATE_SYSTEM::PerformOmegaStateAbility()
{
    if (bIsOmegaStateActive && OmegaStateLevel >= OmegaStateThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Omega State Ability at Level %d!"), OmegaStateLevel);
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
    else if (OmegaStateLevel < OmegaStateThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Omega State Level too low to perform ability. Required: %.0f, Current: %d"), OmegaStateThreshold, OmegaStateLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Omega State is not active, cannot perform ability."));
    }
}

bool UP17_OMEGA_STATE_SYSTEM::IsOmegaStateActive() const
{
    return bIsOmegaStateActive;
}

int32 UP17_OMEGA_STATE_SYSTEM::GetOmegaStateLevel() const
{
    return OmegaStateLevel;
}

float UP17_OMEGA_STATE_SYSTEM::GetOmegaStatePowerCost() const
{
    return OmegaStatePowerCost;
}

void UP17_OMEGA_STATE_SYSTEM::ExerciseOmegaPhaseUltimacy()
{
    if (bIsOmegaStateActive)
    {
        float UltimacyPower = OmegaPhaseUltimacy * (OmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Exercising Omega Phase Ultimacy with power: %.2f"), UltimacyPower);
        // Apply omega phase ultimacy effects
    }
}

void UP17_OMEGA_STATE_SYSTEM::AchieveOmegaPhaseFinalUltimacy()
{
    if (bIsOmegaStateActive)
    {
        float UltimacyPower = OmegaPhaseUltimacy * (OmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Omega Phase Final Ultimacy with power: %.2f"), UltimacyPower);
        // Apply omega phase final ultimacy effects
    }
}

void UP17_OMEGA_STATE_SYSTEM::ControlFinalStateTransitions()
{
    if (bIsOmegaStateActive)
    {
        float TransitionPower = StateTransitions * (OmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Controlling Final State Transitions with power: %.2f"), TransitionPower);
        // Apply final state transition control effects
    }
}

void UP17_OMEGA_STATE_SYSTEM::AccessUltimateConsciousness()
{
    if (bIsOmegaStateActive)
    {
        float ConsciousnessPower = UltimateConsciousness * (OmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Accessing Ultimate Consciousness with power: %.2f"), ConsciousnessPower);
        // Apply ultimate consciousness effects
    }
}

void UP17_OMEGA_STATE_SYSTEM::WieldFinalUltimacy()
{
    if (bIsOmegaStateActive)
    {
        float UltimacyPower = FinalUltimacy * (OmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Wielding Final Ultimacy with power: %.2f"), UltimacyPower);
        // Apply final ultimacy effects
    }
}

bool UP17_OMEGA_STATE_SYSTEM::CanActivateOmegaState() const
{
    return OmegaStateLevel > 0;
}

void UP17_OMEGA_STATE_SYSTEM::UpdateOmegaStateStats()
{
    // Update omega state properties based on level
    OmegaPhaseUltimacy = OmegaStateLevel * 9.0f;
    FinalStateAuthority = OmegaStateLevel * 9.2f;
    StateTransitions = OmegaStateLevel * 8.8f;
    UltimateConsciousness = OmegaStateLevel * 8.9f;
    FinalUltimacy = OmegaStateLevel * 9.1f;
}

void UP17_OMEGA_STATE_SYSTEM::OnOmegaStateChanged()
{
    // Handle state change effects
    if (bIsOmegaStateActive)
    {
        // Apply omega state activation effects
        UE_LOG(LogTemp, Warning, TEXT("Omega State state changed to ACTIVE"));
    }
    else
    {
        // Remove omega state effects
        UE_LOG(LogTemp, Warning, TEXT("Omega State state changed to INACTIVE"));
    }
}
