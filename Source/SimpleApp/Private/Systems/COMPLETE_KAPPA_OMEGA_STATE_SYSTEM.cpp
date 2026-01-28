#include "COMPLETE_KAPPA_OMEGA_STATE_SYSTEM.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCOMPLETE_KAPPA_OMEGA_STATE_SYSTEM::UCOMPLETE_KAPPA_OMEGA_STATE_SYSTEM()
{
    PrimaryComponentTick.bCanEverTick = false;
    KappaOmegaStateLevel = 0;
    MaxKappaOmegaStateLevel = 100;
    bIsKappaOmegaStateActive = false;
    KappaOmegaStatePowerCost = 40.0f;
    KappaOmegaStateThreshold = 95.0f;
    
    // Initialize kappa-omega state properties
    KappaPhaseAbsoluteSupremeUltimacy = 0.0f;
    OmegaPhaseFinalAbsoluteFinality = 0.0f;
    AbsoluteStateTransition = 0.0f;
    SubatomicQuantumStateSupremacy = 0.0f;
    FinalStateAbsoluteUltimacy = 0.0f;
}

void UCOMPLETE_KAPPA_OMEGA_STATE_SYSTEM::BeginPlay()
{
    Super::BeginPlay();
    UpdateKappaOmegaStateStats();
}

void UCOMPLETE_KAPPA_OMEGA_STATE_SYSTEM::ActivateKappaOmegaState()
{
    if (!bIsKappaOmegaStateActive && CanActivateKappaOmegaState())
    {
        bIsKappaOmegaStateActive = true;
        OnKappaOmegaStateActivated.Broadcast(KappaOmegaStateLevel);
        OnKappaOmegaStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Kappa-Omega State System Activated at Level: %d"), KappaOmegaStateLevel);
    }
}

void UCOMPLETE_KAPPA_OMEGA_STATE_SYSTEM::DeactivateKappaOmegaState()
{
    if (bIsKappaOmegaStateActive)
    {
        bIsKappaOmegaStateActive = false;
        OnKappaOmegaStateDeactivated.Broadcast(KappaOmegaStateLevel);
        OnKappaOmegaStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Kappa-Omega State System Deactivated."));
    }
}

void UCOMPLETE_KAPPA_OMEGA_STATE_SYSTEM::SetKappaOmegaStateLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxKappaOmegaStateLevel)
    {
        int32 OldLevel = KappaOmegaStateLevel;
        KappaOmegaStateLevel = NewLevel;
        UpdateKappaOmegaStateStats();
        OnKappaOmegaStateChanged.Broadcast(OldLevel, KappaOmegaStateLevel);
        UE_LOG(LogTemp, Warning, TEXT("Kappa-Omega State Level set to: %d"), KappaOmegaStateLevel);
        
        if (KappaOmegaStateLevel >= MaxKappaOmegaStateLevel)
        {
            OnKappaOmegaStateMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Kappa-Omega State Max Level Reached!"));
        }
    }
}

void UCOMPLETE_KAPPA_OMEGA_STATE_SYSTEM::UseKappaOmegaStatePower()
{
    if (bIsKappaOmegaStateActive && KappaOmegaStateLevel > 0)
    {
        OnKappaOmegaStatePowerUsed.Broadcast(KappaOmegaStatePowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Kappa-Omega State Power Used: %.2f"), KappaOmegaStatePowerCost);
    }
    else
    {
        OnKappaOmegaStatePowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Kappa-Omega State Power Use Failed: System not active or insufficient level."));
    }
}

void UCOMPLETE_KAPPA_OMEGA_STATE_SYSTEM::PerformKappaOmegaStateAbility()
{
    if (bIsKappaOmegaStateActive && KappaOmegaStateLevel >= KappaOmegaStateThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Kappa-Omega State Ability at Level %d!"), KappaOmegaStateLevel);
        OnKappaOmegaStateAbilityPerformed.Broadcast(KappaOmegaStateLevel);
        UseKappaOmegaStatePower();
        
        // Perform kappa-omega state ability based on level
        switch (KappaOmegaStateLevel / 20)
        {
            case 0:
                ExerciseKappaPhaseAbsoluteSupremeUltimacy();
                break;
            case 1:
                AchieveOmegaPhaseFinalAbsoluteFinality();
                break;
            case 2:
                ControlAbsoluteStateTransitions();
                break;
            case 3:
                DominateSubatomicQuantumStates();
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
    else if (KappaOmegaStateLevel < KappaOmegaStateThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Kappa-Omega State Level too low to perform ability. Required: %.0f, Current: %d"), KappaOmegaStateThreshold, KappaOmegaStateLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Kappa-Omega State is not active, cannot perform ability."));
    }
}

bool UCOMPLETE_KAPPA_OMEGA_STATE_SYSTEM::IsKappaOmegaStateActive() const
{
    return bIsKappaOmegaStateActive;
}

int32 UCOMPLETE_KAPPA_OMEGA_STATE_SYSTEM::GetKappaOmegaStateLevel() const
{
    return KappaOmegaStateLevel;
}

float UCOMPLETE_KAPPA_OMEGA_STATE_SYSTEM::GetKappaOmegaStatePowerCost() const
{
    return KappaOmegaStatePowerCost;
}

void UCOMPLETE_KAPPA_OMEGA_STATE_SYSTEM::ExerciseKappaPhaseAbsoluteSupremeUltimacy()
{
    if (bIsKappaOmegaStateActive)
    {
        float UltimacyPower = KappaPhaseAbsoluteSupremeUltimacy * (KappaOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Exercising Kappa Phase Absolute Supreme Ultimacy with power: %.2f"), UltimacyPower);
        // Apply kappa phase absolute supreme ultimacy effects
    }
}

void UCOMPLETE_KAPPA_OMEGA_STATE_SYSTEM::AchieveOmegaPhaseFinalAbsoluteFinality()
{
    if (bIsKappaOmegaStateActive)
    {
        float FinalityPower = OmegaPhaseFinalAbsoluteFinality * (KappaOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Omega Phase Absolute Finality with power: %.2f"), FinalityPower);
        // Apply omega phase absolute finality effects
    }
}

void UCOMPLETE_KAPPA_OMEGA_STATE_SYSTEM::ControlAbsoluteStateTransitions()
{
    if (bIsKappaOmegaStateActive)
    {
        float TransitionPower = AbsoluteStateTransition * (KappaOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Controlling Absolute State Transitions with power: %.2f"), TransitionPower);
        // Apply absolute state transition control effects
    }
}

void UCOMPLETE_KAPPA_OMEGA_STATE_SYSTEM::DominateSubatomicQuantumStates()
{
    if (bIsKappaOmegaStateActive)
    {
        float SubatomicPower = SubatomicQuantumStateSupremacy * (KappaOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Dominating Subatomic-Quantum States with power: %.2f"), SubatomicPower);
        // Apply subatomic-quantum state domination effects
    }
}

void UCOMPLETE_KAPPA_OMEGA_STATE_SYSTEM::WieldFinalStateAbsoluteUltimacy()
{
    if (bIsKappaOmegaStateActive)
    {
        float FinalStatePower = FinalStateAbsoluteUltimacy * (KappaOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Wielding Final State Absolute Ultimacy with power: %.2f"), FinalStatePower);
        // Apply final state absolute ultimacy effects
    }
}

bool UCOMPLETE_KAPPA_OMEGA_STATE_SYSTEM::CanActivateKappaOmegaState() const
{
    return KappaOmegaStateLevel > 0;
}

void UCOMPLETE_KAPPA_OMEGA_STATE_SYSTEM::UpdateKappaOmegaStateStats()
{
    // Update kappa-omega state properties based on level
    KappaPhaseAbsoluteSupremeUltimacy = KappaOmegaStateLevel * 14.5f;
    OmegaPhaseFinalAbsoluteFinality = KappaOmegaStateLevel * 14.3f;
    AbsoluteStateTransition = KappaOmegaStateLevel * 14.2f;
    SubatomicQuantumStateSupremacy = KappaOmegaStateLevel * 14.1f;
    FinalStateAbsoluteUltimacy = KappaOmegaStateLevel * 15.0f;
}

void UCOMPLETE_KAPPA_OMEGA_STATE_SYSTEM::OnKappaOmegaStateChanged()
{
    // Handle state change effects
    if (bIsKappaOmegaStateActive)
    {
        // Apply kappa-omega state activation effects
        UE_LOG(LogTemp, Warning, TEXT("Kappa-Omega State state changed to ACTIVE"));
    }
    else
    {
        // Remove kappa-omega state effects
        UE_LOG(LogTemp, Warning, TEXT("Kappa-Omega State state changed to INACTIVE"));
    }
}
