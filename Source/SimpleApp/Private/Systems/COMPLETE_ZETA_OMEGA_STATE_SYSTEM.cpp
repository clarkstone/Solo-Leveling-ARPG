#include "COMPLETE_ZETA_OMEGA_STATE_SYSTEM.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCOMPLETE_ZETA_OMEGA_STATE_SYSTEM::UCOMPLETE_ZETA_OMEGA_STATE_SYSTEM()
{
    PrimaryComponentTick.bCanEverTick = false;
    ZetaOmegaStateLevel = 0;
    MaxZetaOmegaStateLevel = 100;
    bIsZetaOmegaStateActive = false;
    ZetaOmegaStatePowerCost = 20.0f;
    ZetaOmegaStateThreshold = 70.0f;
    
    // Initialize zeta-omega state properties
    ZetaPhaseSupremacy = 0.0f;
    OmegaPhaseUltimacy = 0.0f;
    MetaStateTransition = 0.0f;
    QuantumStateSupremacy = 0.0f;
    FinalStateAuthority = 0.0f;
}

void UCOMPLETE_ZETA_OMEGA_STATE_SYSTEM::BeginPlay()
{
    Super::BeginPlay();
    UpdateZetaOmegaStateStats();
}

void UCOMPLETE_ZETA_OMEGA_STATE_SYSTEM::ActivateZetaOmegaState()
{
    if (!bIsZetaOmegaStateActive && CanActivateZetaOmegaState())
    {
        bIsZetaOmegaStateActive = true;
        OnZetaOmegaStateActivated.Broadcast(ZetaOmegaStateLevel);
        OnZetaOmegaStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Zeta-Omega State System Activated at Level: %d"), ZetaOmegaStateLevel);
    }
}

void UCOMPLETE_ZETA_OMEGA_STATE_SYSTEM::DeactivateZetaOmegaState()
{
    if (bIsZetaOmegaStateActive)
    {
        bIsZetaOmegaStateActive = false;
        OnZetaOmegaStateDeactivated.Broadcast(ZetaOmegaStateLevel);
        OnZetaOmegaStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Zeta-Omega State System Deactivated."));
    }
}

void UCOMPLETE_ZETA_OMEGA_STATE_SYSTEM::SetZetaOmegaStateLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxZetaOmegaStateLevel)
    {
        int32 OldLevel = ZetaOmegaStateLevel;
        ZetaOmegaStateLevel = NewLevel;
        UpdateZetaOmegaStateStats();
        OnZetaOmegaStateChanged.Broadcast(OldLevel, ZetaOmegaStateLevel);
        UE_LOG(LogTemp, Warning, TEXT("Zeta-Omega State Level set to: %d"), ZetaOmegaStateLevel);
        
        if (ZetaOmegaStateLevel >= MaxZetaOmegaStateLevel)
        {
            OnZetaOmegaStateMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Zeta-Omega State Max Level Reached!"));
        }
    }
}

void UCOMPLETE_ZETA_OMEGA_STATE_SYSTEM::UseZetaOmegaStatePower()
{
    if (bIsZetaOmegaStateActive && ZetaOmegaStateLevel > 0)
    {
        OnZetaOmegaStatePowerUsed.Broadcast(ZetaOmegaStatePowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Zeta-Omega State Power Used: %.2f"), ZetaOmegaStatePowerCost);
    }
    else
    {
        OnZetaOmegaStatePowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Zeta-Omega State Power Use Failed: System not active or insufficient level."));
    }
}

void UCOMPLETE_ZETA_OMEGA_STATE_SYSTEM::PerformZetaOmegaStateAbility()
{
    if (bIsZetaOmegaStateActive && ZetaOmegaStateLevel >= ZetaOmegaStateThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Zeta-Omega State Ability at Level %d!"), ZetaOmegaStateLevel);
        OnZetaOmegaStateAbilityPerformed.Broadcast(ZetaOmegaStateLevel);
        UseZetaOmegaStatePower();
        
        // Perform zeta-omega state ability based on level
        switch (ZetaOmegaStateLevel / 20)
        {
            case 0:
                ExerciseZetaPhaseSupremacy();
                break;
            case 1:
                AchieveOmegaPhaseUltimacy();
                break;
            case 2:
                ControlMetaStateTransitions();
                break;
            case 3:
                DominateQuantumStates();
                break;
            case 4:
            case 5:
                WieldFinalStateAuthority();
                break;
            default:
                WieldFinalStateAuthority();
                break;
        }
    }
    else if (ZetaOmegaStateLevel < ZetaOmegaStateThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Zeta-Omega State Level too low to perform ability. Required: %.0f, Current: %d"), ZetaOmegaStateThreshold, ZetaOmegaStateLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Zeta-Omega State is not active, cannot perform ability."));
    }
}

bool UCOMPLETE_ZETA_OMEGA_STATE_SYSTEM::IsZetaOmegaStateActive() const
{
    return bIsZetaOmegaStateActive;
}

int32 UCOMPLETE_ZETA_OMEGA_STATE_SYSTEM::GetZetaOmegaStateLevel() const
{
    return ZetaOmegaStateLevel;
}

float UCOMPLETE_ZETA_OMEGA_STATE_SYSTEM::GetZetaOmegaStatePowerCost() const
{
    return ZetaOmegaStatePowerCost;
}

void UCOMPLETE_ZETA_OMEGA_STATE_SYSTEM::ExerciseZetaPhaseSupremacy()
{
    if (bIsZetaOmegaStateActive)
    {
        float SupremacyPower = ZetaPhaseSupremacy * (ZetaOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Exercising Zeta Phase Supremacy with power: %.2f"), SupremacyPower);
        // Apply zeta phase supremacy effects
    }
}

void UCOMPLETE_ZETA_OMEGA_STATE_SYSTEM::AchieveOmegaPhaseUltimacy()
{
    if (bIsZetaOmegaStateActive)
    {
        float UltimacyPower = OmegaPhaseUltimacy * (ZetaOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Omega Phase Ultimacy with power: %.2f"), UltimacyPower);
        // Apply omega phase ultimacy effects
    }
}

void UCOMPLETE_ZETA_OMEGA_STATE_SYSTEM::ControlMetaStateTransitions()
{
    if (bIsZetaOmegaStateActive)
    {
        float TransitionPower = MetaStateTransition * (ZetaOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Controlling Meta-State Transitions with power: %.2f"), TransitionPower);
        // Apply meta-state transition control effects
    }
}

void UCOMPLETE_ZETA_OMEGA_STATE_SYSTEM::DominateQuantumStates()
{
    if (bIsZetaOmegaStateActive)
    {
        float QuantumPower = QuantumStateSupremacy * (ZetaOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Dominating Quantum States with power: %.2f"), QuantumPower);
        // Apply quantum state domination effects
    }
}

void UCOMPLETE_ZETA_OMEGA_STATE_SYSTEM::WieldFinalStateAuthority()
{
    if (bIsZetaOmegaStateActive)
    {
        float AuthorityPower = FinalStateAuthority * (ZetaOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Wielding Final State Authority with power: %.2f"), AuthorityPower);
        // Apply final state authority effects
    }
}

bool UCOMPLETE_ZETA_OMEGA_STATE_SYSTEM::CanActivateZetaOmegaState() const
{
    return ZetaOmegaStateLevel > 0;
}

void UCOMPLETE_ZETA_OMEGA_STATE_SYSTEM::UpdateZetaOmegaStateStats()
{
    // Update zeta-omega state properties based on level
    ZetaPhaseSupremacy = ZetaOmegaStateLevel * 4.8f;
    OmegaPhaseUltimacy = ZetaOmegaStateLevel * 4.6f;
    MetaStateTransition = ZetaOmegaStateLevel * 4.5f;
    QuantumStateSupremacy = ZetaOmegaStateLevel * 4.4f;
    FinalStateAuthority = ZetaOmegaStateLevel * 5.0f;
}

void UCOMPLETE_ZETA_OMEGA_STATE_SYSTEM::OnZetaOmegaStateChanged()
{
    // Handle state change effects
    if (bIsZetaOmegaStateActive)
    {
        // Apply zeta-omega state activation effects
        UE_LOG(LogTemp, Warning, TEXT("Zeta-Omega State state changed to ACTIVE"));
    }
    else
    {
        // Remove zeta-omega state effects
        UE_LOG(LogTemp, Warning, TEXT("Zeta-Omega State state changed to INACTIVE"));
    }
}
