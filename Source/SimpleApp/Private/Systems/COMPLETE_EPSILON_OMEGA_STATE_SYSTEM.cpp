#include "COMPLETE_EPSILON_OMEGA_STATE_SYSTEM.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCOMPLETE_EPSILON_OMEGA_STATE_SYSTEM::UCOMPLETE_EPSILON_OMEGA_STATE_SYSTEM()
{
    PrimaryComponentTick.bCanEverTick = false;
    EpsilonOmegaStateLevel = 0;
    MaxEpsilonOmegaStateLevel = 100;
    bIsEpsilonOmegaStateActive = false;
    EpsilonOmegaStatePowerCost = 15.0f;
    EpsilonOmegaStateThreshold = 60.0f;
    
    // Initialize epsilon-omega state properties
    EpsilonPhaseMastery = 0.0f;
    OmegaPhaseDominance = 0.0f;
    StateTransitionControl = 0.0f;
    QuantumStateManipulation = 0.0f;
    UltimateStateAuthority = 0.0f;
}

void UCOMPLETE_EPSILON_OMEGA_STATE_SYSTEM::BeginPlay()
{
    Super::BeginPlay();
    UpdateEpsilonOmegaStateStats();
}

void UCOMPLETE_EPSILON_OMEGA_STATE_SYSTEM::ActivateEpsilonOmegaState()
{
    if (!bIsEpsilonOmegaStateActive && CanActivateEpsilonOmegaState())
    {
        bIsEpsilonOmegaStateActive = true;
        OnEpsilonOmegaStateActivated.Broadcast(EpsilonOmegaStateLevel);
        OnEpsilonOmegaStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Epsilon-Omega State System Activated at Level: %d"), EpsilonOmegaStateLevel);
    }
}

void UCOMPLETE_EPSILON_OMEGA_STATE_SYSTEM::DeactivateEpsilonOmegaState()
{
    if (bIsEpsilonOmegaStateActive)
    {
        bIsEpsilonOmegaStateActive = false;
        OnEpsilonOmegaStateDeactivated.Broadcast(EpsilonOmegaStateLevel);
        OnEpsilonOmegaStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Epsilon-Omega State System Deactivated."));
    }
}

void UCOMPLETE_EPSILON_OMEGA_STATE_SYSTEM::SetEpsilonOmegaStateLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxEpsilonOmegaStateLevel)
    {
        int32 OldLevel = EpsilonOmegaStateLevel;
        EpsilonOmegaStateLevel = NewLevel;
        UpdateEpsilonOmegaStateStats();
        OnEpsilonOmegaStateChanged.Broadcast(OldLevel, EpsilonOmegaStateLevel);
        UE_LOG(LogTemp, Warning, TEXT("Epsilon-Omega State Level set to: %d"), EpsilonOmegaStateLevel);
        
        if (EpsilonOmegaStateLevel >= MaxEpsilonOmegaStateLevel)
        {
            OnEpsilonOmegaStateMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Epsilon-Omega State Max Level Reached!"));
        }
    }
}

void UCOMPLETE_EPSILON_OMEGA_STATE_SYSTEM::UseEpsilonOmegaStatePower()
{
    if (bIsEpsilonOmegaStateActive && EpsilonOmegaStateLevel > 0)
    {
        OnEpsilonOmegaStatePowerUsed.Broadcast(EpsilonOmegaStatePowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Epsilon-Omega State Power Used: %.2f"), EpsilonOmegaStatePowerCost);
    }
    else
    {
        OnEpsilonOmegaStatePowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Epsilon-Omega State Power Use Failed: System not active or insufficient level."));
    }
}

void UCOMPLETE_EPSILON_OMEGA_STATE_SYSTEM::PerformEpsilonOmegaStateAbility()
{
    if (bIsEpsilonOmegaStateActive && EpsilonOmegaStateLevel >= EpsilonOmegaStateThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Epsilon-Omega State Ability at Level %d!"), EpsilonOmegaStateLevel);
        OnEpsilonOmegaStateAbilityPerformed.Broadcast(EpsilonOmegaStateLevel);
        UseEpsilonOmegaStatePower();
        
        // Perform epsilon-omega state ability based on level
        switch (EpsilonOmegaStateLevel / 20)
        {
            case 0:
                MasterEpsilonPhase();
                break;
            case 1:
                DominateOmegaPhase();
                break;
            case 2:
                ControlStateTransitions();
                break;
            case 3:
                ManipulateQuantumStates();
                break;
            case 4:
            case 5:
                ExerciseUltimateStateAuthority();
                break;
            default:
                ExerciseUltimateStateAuthority();
                break;
        }
    }
    else if (EpsilonOmegaStateLevel < EpsilonOmegaStateThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Epsilon-Omega State Level too low to perform ability. Required: %.0f, Current: %d"), EpsilonOmegaStateThreshold, EpsilonOmegaStateLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Epsilon-Omega State is not active, cannot perform ability."));
    }
}

bool UCOMPLETE_EPSILON_OMEGA_STATE_SYSTEM::IsEpsilonOmegaStateActive() const
{
    return bIsEpsilonOmegaStateActive;
}

int32 UCOMPLETE_EPSILON_OMEGA_STATE_SYSTEM::GetEpsilonOmegaStateLevel() const
{
    return EpsilonOmegaStateLevel;
}

float UCOMPLETE_EPSILON_OMEGA_STATE_SYSTEM::GetEpsilonOmegaStatePowerCost() const
{
    return EpsilonOmegaStatePowerCost;
}

void UCOMPLETE_EPSILON_OMEGA_STATE_SYSTEM::MasterEpsilonPhase()
{
    if (bIsEpsilonOmegaStateActive)
    {
        float EpsilonMastery = EpsilonPhaseMastery * (EpsilonOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Mastering Epsilon Phase with power: %.2f"), EpsilonMastery);
        // Apply epsilon phase mastery effects
    }
}

void UCOMPLETE_EPSILON_OMEGA_STATE_SYSTEM::DominateOmegaPhase()
{
    if (bIsEpsilonOmegaStateActive)
    {
        float OmegaDominance = OmegaPhaseDominance * (EpsilonOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Dominating Omega Phase with power: %.2f"), OmegaDominance);
        // Apply omega phase dominance effects
    }
}

void UCOMPLETE_EPSILON_OMEGA_STATE_SYSTEM::ControlStateTransitions()
{
    if (bIsEpsilonOmegaStateActive)
    {
        float TransitionControl = StateTransitionControl * (EpsilonOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Controlling State Transitions with power: %.2f"), TransitionControl);
        // Apply state transition control effects
    }
}

void UCOMPLETE_EPSILON_OMEGA_STATE_SYSTEM::ManipulateQuantumStates()
{
    if (bIsEpsilonOmegaStateActive)
    {
        float QuantumManipulation = QuantumStateManipulation * (EpsilonOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Manipulating Quantum States with power: %.2f"), QuantumManipulation);
        // Apply quantum state manipulation effects
    }
}

void UCOMPLETE_EPSILON_OMEGA_STATE_SYSTEM::ExerciseUltimateStateAuthority()
{
    if (bIsEpsilonOmegaStateActive)
    {
        float StateAuthority = UltimateStateAuthority * (EpsilonOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Exercising Ultimate State Authority with power: %.2f"), StateAuthority);
        // Apply ultimate state authority effects
    }
}

bool UCOMPLETE_EPSILON_OMEGA_STATE_SYSTEM::CanActivateEpsilonOmegaState() const
{
    return EpsilonOmegaStateLevel > 0;
}

void UCOMPLETE_EPSILON_OMEGA_STATE_SYSTEM::UpdateEpsilonOmegaStateStats()
{
    // Update epsilon-omega state properties based on level
    EpsilonPhaseMastery = EpsilonOmegaStateLevel * 3.4f;
    OmegaPhaseDominance = EpsilonOmegaStateLevel * 3.2f;
    StateTransitionControl = EpsilonOmegaStateLevel * 3.1f;
    QuantumStateManipulation = EpsilonOmegaStateLevel * 3.0f;
    UltimateStateAuthority = EpsilonOmegaStateLevel * 3.5f;
}

void UCOMPLETE_EPSILON_OMEGA_STATE_SYSTEM::OnEpsilonOmegaStateChanged()
{
    // Handle state change effects
    if (bIsEpsilonOmegaStateActive)
    {
        // Apply epsilon-omega state activation effects
        UE_LOG(LogTemp, Warning, TEXT("Epsilon-Omega State state changed to ACTIVE"));
    }
    else
    {
        // Remove epsilon-omega state effects
        UE_LOG(LogTemp, Warning, TEXT("Epsilon-Omega State state changed to INACTIVE"));
    }
}
