#include "COMPLETE_MU_OMEGA_STATE_SYSTEM.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCOMPLETE_MU_OMEGA_STATE_SYSTEM::UCOMPLETE_MU_OMEGA_STATE_SYSTEM()
{
    PrimaryComponentTick.bCanEverTick = false;
    MuOmegaStateLevel = 0;
    MaxMuOmegaStateLevel = 100;
    bIsMuOmegaStateActive = false;
    MuOmegaStatePowerCost = 60.0f;
    MuOmegaStateThreshold = 100.0f;
    
    // Initialize mu-omega state properties
    MuPhaseFinalUltimateAbsoluteSupremeUltimacy = 0.0f;
    OmegaPhaseFinalUltimateAbsoluteFinality = 0.0f;
    FinalStateTransitions = 0.0f;
    PlanckQuantumStateSupremacy = 0.0f;
    FinalStateUltimateAbsoluteUltimacy = 0.0f;
}

void UCOMPLETE_MU_OMEGA_STATE_SYSTEM::BeginPlay()
{
    Super::BeginPlay();
    UpdateMuOmegaStateStats();
}

void UCOMPLETE_MU_OMEGA_STATE_SYSTEM::ActivateMuOmegaState()
{
    if (!bIsMuOmegaStateActive && CanActivateMuOmegaState())
    {
        bIsMuOmegaStateActive = true;
        OnMuOmegaStateActivated.Broadcast(MuOmegaStateLevel);
        OnMuOmegaStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Mu-Omega State System Activated at Level: %d"), MuOmegaStateLevel);
    }
}

void UCOMPLETE_MU_OMEGA_STATE_SYSTEM::DeactivateMuOmegaState()
{
    if (bIsMuOmegaStateActive)
    {
        bIsMuOmegaStateActive = false;
        OnMuOmegaStateDeactivated.Broadcast(MuOmegaStateLevel);
        OnMuOmegaStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Mu-Omega State System Deactivated."));
    }
}

void UCOMPLETE_MU_OMEGA_STATE_SYSTEM::SetMuOmegaStateLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxMuOmegaStateLevel)
    {
        int32 OldLevel = MuOmegaStateLevel;
        MuOmegaStateLevel = NewLevel;
        UpdateMuOmegaStateStats();
        OnMuOmegaStateChanged.Broadcast(OldLevel, MuOmegaStateLevel);
        UE_LOG(LogTemp, Warning, TEXT("Mu-Omega State Level set to: %d"), MuOmegaStateLevel);
        
        if (MuOmegaStateLevel >= MaxMuOmegaStateLevel)
        {
            OnMuOmegaStateMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Mu-Omega State Max Level Reached!"));
        }
    }
}

void UCOMPLETE_MU_OMEGA_STATE_SYSTEM::UseMuOmegaStatePower()
{
    if (bIsMuOmegaStateActive && MuOmegaStateLevel > 0)
    {
        OnMuOmegaStatePowerUsed.Broadcast(MuOmegaStatePowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Mu-Omega State Power Used: %.2f"), MuOmegaStatePowerCost);
    }
    else
    {
        OnMuOmegaStatePowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Mu-Omega State Power Use Failed: System not active or insufficient level."));
    }
}

void UCOMPLETE_MU_OMEGA_STATE_SYSTEM::PerformMuOmegaStateAbility()
{
    if (bIsMuOmegaStateActive && MuOmegaStateLevel >= MuOmegaStateThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Mu-Omega State Ability at Level %d!"), MuOmegaStateLevel);
        OnMuOmegaStateAbilityPerformed.Broadcast(MuOmegaStateLevel);
        UseMuOmegaStatePower();
        
        // Perform mu-omega state ability based on level
        switch (MuOmegaStateLevel / 20)
        {
            case 0:
                ExerciseMuPhaseFinalUltimateAbsoluteSupremeUltimacy();
                break;
            case 1:
                AchieveOmegaPhaseFinalUltimateAbsoluteFinality();
                break;
            case 2:
                ControlFinalStateTransitions();
                break;
            case 3:
                DominatePlanckQuantumStates();
                break;
            case 4:
            case 5:
                WieldFinalStateUltimateAbsoluteUltimacy();
                break;
            default:
                WieldFinalStateUltimateAbsoluteUltimacy();
                break;
        }
    }
    else if (MuOmegaStateLevel < MuOmegaStateThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Mu-Omega State Level too low to perform ability. Required: %.0f, Current: %d"), MuOmegaStateThreshold, MuOmegaStateLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Mu-Omega State is not active, cannot perform ability."));
    }
}

bool UCOMPLETE_MU_OMEGA_STATE_SYSTEM::IsMuOmegaStateActive() const
{
    return bIsMuOmegaStateActive;
}

int32 UCOMPLETE_MU_OMEGA_STATE_SYSTEM::GetMuOmegaStateLevel() const
{
    return MuOmegaStateLevel;
}

float UCOMPLETE_MU_OMEGA_STATE_SYSTEM::GetMuOmegaStatePowerCost() const
{
    return MuOmegaStatePowerCost;
}

void UCOMPLETE_MU_OMEGA_STATE_SYSTEM::ExerciseMuPhaseFinalUltimateAbsoluteSupremeUltimacy()
{
    if (bIsMuOmegaStateActive)
    {
        float UltimacyPower = MuPhaseFinalUltimateAbsoluteSupremeUltimacy * (MuOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Exercising Mu Phase Final-Ultimate-Absolute-Supreme Ultimacy with power: %.2f"), UltimacyPower);
        // Apply mu phase final-ultimate-absolute-supreme ultimacy effects
    }
}

void UCOMPLETE_MU_OMEGA_STATE_SYSTEM::AchieveOmegaPhaseFinalUltimateAbsoluteFinality()
{
    if (bIsMuOmegaStateActive)
    {
        float FinalityPower = OmegaPhaseFinalUltimateAbsoluteFinality * (MuOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Omega Phase Final-Ultimate-Absolute Finality with power: %.2f"), FinalityPower);
        // Apply omega phase final-ultimate-absolute finality effects
    }
}

void UCOMPLETE_MU_OMEGA_STATE_SYSTEM::ControlFinalStateTransitions()
{
    if (bIsMuOmegaStateActive)
    {
        float TransitionPower = FinalStateTransitions * (MuOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Controlling Final State Transitions with power: %.2f"), TransitionPower);
        // Apply final state transition control effects
    }
}

void UCOMPLETE_MU_OMEGA_STATE_SYSTEM::DominatePlanckQuantumStates()
{
    if (bIsMuOmegaStateActive)
    {
        float PlanckPower = PlanckQuantumStateSupremacy * (MuOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Dominating Planck-Quantum States with power: %.2f"), PlanckPower);
        // Apply planck-quantum state domination effects
    }
}

void UCOMPLETE_MU_OMEGA_STATE_SYSTEM::WieldFinalStateUltimateAbsoluteUltimacy()
{
    if (bIsMuOmegaStateActive)
    {
        float FinalStatePower = FinalStateUltimateAbsoluteUltimacy * (MuOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Wielding Final State Ultimate-Absolute Ultimacy with power: %.2f"), FinalStatePower);
        // Apply final state ultimate-absolute ultimacy effects
    }
}

bool UCOMPLETE_MU_OMEGA_STATE_SYSTEM::CanActivateMuOmegaState() const
{
    return MuOmegaStateLevel > 0;
}

void UCOMPLETE_MU_OMEGA_STATE_SYSTEM::UpdateMuOmegaStateStats()
{
    // Update mu-omega state properties based on level
    MuPhaseFinalUltimateAbsoluteSupremeUltimacy = MuOmegaStateLevel * 26.5f;
    OmegaPhaseFinalUltimateAbsoluteFinality = MuOmegaStateLevel * 26.3f;
    FinalStateTransitions = MuOmegaStateLevel * 26.2f;
    PlanckQuantumStateSupremacy = MuOmegaStateLevel * 26.1f;
    FinalStateUltimateAbsoluteUltimacy = MuOmegaStateLevel * 27.0f;
}

void UCOMPLETE_MU_OMEGA_STATE_SYSTEM::OnMuOmegaStateChanged()
{
    // Handle state change effects
    if (bIsMuOmegaStateActive)
    {
        // Apply mu-omega state activation effects
        UE_LOG(LogTemp, Warning, TEXT("Mu-Omega State state changed to ACTIVE"));
    }
    else
    {
        // Remove mu-omega state effects
        UE_LOG(LogTemp, Warning, TEXT("Mu-Omega State state changed to INACTIVE"));
    }
}
