#include "COMPLETE_THETA_OMEGA_STATE_SYSTEM.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCOMPLETE_THETA_OMEGA_STATE_SYSTEM::UCOMPLETE_THETA_OMEGA_STATE_SYSTEM()
{
    PrimaryComponentTick.bCanEverTick = false;
    ThetaOmegaStateLevel = 0;
    MaxThetaOmegaStateLevel = 100;
    bIsThetaOmegaStateActive = false;
    ThetaOmegaStatePowerCost = 30.0f;
    ThetaOmegaStateThreshold = 85.0f;
    
    // Initialize theta-omega state properties
    ThetaPhaseUltimacy = 0.0f;
    OmegaPhaseFinality = 0.0f;
    UltraStateTransition = 0.0f;
    SubatomicStateSupremacy = 0.0f;
    FinalStateUltimacy = 0.0f;
}

void UCOMPLETE_THETA_OMEGA_STATE_SYSTEM::BeginPlay()
{
    Super::BeginPlay();
    UpdateThetaOmegaStateStats();
}

void UCOMPLETE_THETA_OMEGA_STATE_SYSTEM::ActivateThetaOmegaState()
{
    if (!bIsThetaOmegaStateActive && CanActivateThetaOmegaState())
    {
        bIsThetaOmegaStateActive = true;
        OnThetaOmegaStateActivated.Broadcast(ThetaOmegaStateLevel);
        OnThetaOmegaStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Theta-Omega State System Activated at Level: %d"), ThetaOmegaStateLevel);
    }
}

void UCOMPLETE_THETA_OMEGA_STATE_SYSTEM::DeactivateThetaOmegaState()
{
    if (bIsThetaOmegaStateActive)
    {
        bIsThetaOmegaStateActive = false;
        OnThetaOmegaStateDeactivated.Broadcast(ThetaOmegaStateLevel);
        OnThetaOmegaStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Theta-Omega State System Deactivated."));
    }
}

void UCOMPLETE_THETA_OMEGA_STATE_SYSTEM::SetThetaOmegaStateLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxThetaOmegaStateLevel)
    {
        int32 OldLevel = ThetaOmegaStateLevel;
        ThetaOmegaStateLevel = NewLevel;
        UpdateThetaOmegaStateStats();
        OnThetaOmegaStateChanged.Broadcast(OldLevel, ThetaOmegaStateLevel);
        UE_LOG(LogTemp, Warning, TEXT("Theta-Omega State Level set to: %d"), ThetaOmegaStateLevel);
        
        if (ThetaOmegaStateLevel >= MaxThetaOmegaStateLevel)
        {
            OnThetaOmegaStateMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Theta-Omega State Max Level Reached!"));
        }
    }
}

void UCOMPLETE_THETA_OMEGA_STATE_SYSTEM::UseThetaOmegaStatePower()
{
    if (bIsThetaOmegaStateActive && ThetaOmegaStateLevel > 0)
    {
        OnThetaOmegaStatePowerUsed.Broadcast(ThetaOmegaStatePowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Theta-Omega State Power Used: %.2f"), ThetaOmegaStatePowerCost);
    }
    else
    {
        OnThetaOmegaStatePowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Theta-Omega State Power Use Failed: System not active or insufficient level."));
    }
}

void UCOMPLETE_THETA_OMEGA_STATE_SYSTEM::PerformThetaOmegaStateAbility()
{
    if (bIsThetaOmegaStateActive && ThetaOmegaStateLevel >= ThetaOmegaStateThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Theta-Omega State Ability at Level %d!"), ThetaOmegaStateLevel);
        OnThetaOmegaStateAbilityPerformed.Broadcast(ThetaOmegaStateLevel);
        UseThetaOmegaStatePower();
        
        // Perform theta-omega state ability based on level
        switch (ThetaOmegaStateLevel / 20)
        {
            case 0:
                ExerciseThetaPhaseUltimacy();
                break;
            case 1:
                AchieveOmegaPhaseFinality();
                break;
            case 2:
                ControlUltraStateTransitions();
                break;
            case 3:
                DominateSubatomicStates();
                break;
            case 4:
            case 5:
                WieldFinalStateUltimacy();
                break;
            default:
                WieldFinalStateUltimacy();
                break;
        }
    }
    else if (ThetaOmegaStateLevel < ThetaOmegaStateThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Theta-Omega State Level too low to perform ability. Required: %.0f, Current: %d"), ThetaOmegaStateThreshold, ThetaOmegaStateLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Theta-Omega State is not active, cannot perform ability."));
    }
}

bool UCOMPLETE_THETA_OMEGA_STATE_SYSTEM::IsThetaOmegaStateActive() const
{
    return bIsThetaOmegaStateActive;
}

int32 UCOMPLETE_THETA_OMEGA_STATE_SYSTEM::GetThetaOmegaStateLevel() const
{
    return ThetaOmegaStateLevel;
}

float UCOMPLETE_THETA_OMEGA_STATE_SYSTEM::GetThetaOmegaStatePowerCost() const
{
    return ThetaOmegaStatePowerCost;
}

void UCOMPLETE_THETA_OMEGA_STATE_SYSTEM::ExerciseThetaPhaseUltimacy()
{
    if (bIsThetaOmegaStateActive)
    {
        float UltimacyPower = ThetaPhaseUltimacy * (ThetaOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Exercising Theta Phase Ultimacy with power: %.2f"), UltimacyPower);
        // Apply theta phase ultimacy effects
    }
}

void UCOMPLETE_THETA_OMEGA_STATE_SYSTEM::AchieveOmegaPhaseFinality()
{
    if (bIsThetaOmegaStateActive)
    {
        float FinalityPower = OmegaPhaseFinality * (ThetaOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Omega Phase Finality with power: %.2f"), FinalityPower);
        // Apply omega phase finality effects
    }
}

void UCOMPLETE_THETA_OMEGA_STATE_SYSTEM::ControlUltraStateTransitions()
{
    if (bIsThetaOmegaStateActive)
    {
        float TransitionPower = UltraStateTransition * (ThetaOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Controlling Ultra State Transitions with power: %.2f"), TransitionPower);
        // Apply ultra state transition control effects
    }
}

void UCOMPLETE_THETA_OMEGA_STATE_SYSTEM::DominateSubatomicStates()
{
    if (bIsThetaOmegaStateActive)
    {
        float SubatomicPower = SubatomicStateSupremacy * (ThetaOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Dominating Subatomic States with power: %.2f"), SubatomicPower);
        // Apply subatomic state domination effects
    }
}

void UCOMPLETE_THETA_OMEGA_STATE_SYSTEM::WieldFinalStateUltimacy()
{
    if (bIsThetaOmegaStateActive)
    {
        float FinalStatePower = FinalStateUltimacy * (ThetaOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Wielding Final State Ultimacy with power: %.2f"), FinalStatePower);
        // Apply final state ultimacy effects
    }
}

bool UCOMPLETE_THETA_OMEGA_STATE_SYSTEM::CanActivateThetaOmegaState() const
{
    return ThetaOmegaStateLevel > 0;
}

void UCOMPLETE_THETA_OMEGA_STATE_SYSTEM::UpdateThetaOmegaStateStats()
{
    // Update theta-omega state properties based on level
    ThetaPhaseUltimacy = ThetaOmegaStateLevel * 8.5f;
    OmegaPhaseFinality = ThetaOmegaStateLevel * 8.3f;
    UltraStateTransition = ThetaOmegaStateLevel * 8.2f;
    SubatomicStateSupremacy = ThetaOmegaStateLevel * 8.1f;
    FinalStateUltimacy = ThetaOmegaStateLevel * 9.0f;
}

void UCOMPLETE_THETA_OMEGA_STATE_SYSTEM::OnThetaOmegaStateChanged()
{
    // Handle state change effects
    if (bIsThetaOmegaStateActive)
    {
        // Apply theta-omega state activation effects
        UE_LOG(LogTemp, Warning, TEXT("Theta-Omega State state changed to ACTIVE"));
    }
    else
    {
        // Remove theta-omega state effects
        UE_LOG(LogTemp, Warning, TEXT("Theta-Omega State state changed to INACTIVE"));
    }
}
