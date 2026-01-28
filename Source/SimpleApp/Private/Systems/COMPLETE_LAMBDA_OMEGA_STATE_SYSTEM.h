#include "COMPLETE_LAMBDA_OMEGA_STATE_SYSTEM.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCOMPLETE_LAMBDA_OMEGA_STATE_SYSTEM::UCOMPLETE_LAMBDA_OMEGA_STATE_SYSTEM()
{
    PrimaryComponentTick.bCanEverTick = false;
    LambdaOmegaStateLevel = 0;
    MaxLambdaOmegaStateLevel = 100;
    bIsLambdaOmegaStateActive = false;
    LambdaOmegaStatePowerCost = 50.0f;
    LambdaOmegaStateThreshold = 100.0f;
    
    // Initialize lambda-omega state properties
    LambdaPhaseUltimateAbsoluteSupremeUltimacy = 0.0f;
    OmegaPhaseFinalUltimateAbsoluteFinality = 0.0f;
    UltimateAbsoluteStateTransition = 0.0f;
    PlanckQuantumStateSupremacy = 0.0f;
    FinalStateUltimateAbsoluteUltimacy = 0.0f;
}

void UCOMPLETE_LAMBDA_OMEGA_STATE_SYSTEM::BeginPlay()
{
    Super::BeginPlay();
    UpdateLambdaOmegaStateStats();
}

void UCOMPLETE_LAMBDA_OMEGA_STATE_SYSTEM::ActivateLambdaOmegaState()
{
    if (!bIsLambdaOmegaStateActive && CanActivateLambdaOmegaState())
    {
        bIsLambdaOmegaStateActive = true;
        OnLambdaOmegaStateActivated.Broadcast(LambdaOmegaStateLevel);
        OnLambdaOmegaStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Lambda-Omega State System Activated at Level: %d"), LambdaOmegaStateLevel);
    }
}

void UCOMPLETE_LAMBDA_OMEGA_STATE_SYSTEM::DeactivateLambdaOmegaState()
{
    if (bIsLambdaOmegaStateActive)
    {
        bIsLambdaOmegaStateActive = false;
        OnLambdaOmegaStateDeactivated.Broadcast(LambdaOmegaStateLevel);
        OnLambdaOmegaStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Lambda-Omega State System Deactivated."));
    }
}

void UCOMPLETE_LAMBDA_OMEGA_STATE_SYSTEM::SetLambdaOmegaStateLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxLambdaOmegaStateLevel)
    {
        int32 OldLevel = LambdaOmegaStateLevel;
        LambdaOmegaStateLevel = NewLevel;
        UpdateLambdaOmegaStateStats();
        OnLambdaOmegaStateChanged.Broadcast(OldLevel, LambdaOmegaStateLevel);
        UE_LOG(LogTemp, Warning, TEXT("Lambda-Omega State Level set to: %d"), LambdaOmegaStateLevel);
        
        if (LambdaOmegaStateLevel >= MaxLambdaOmegaStateLevel)
        {
            OnLambdaOmegaStateMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Lambda-Omega State Max Level Reached!"));
        }
    }
}

void UCOMPLETE_LAMBDA_OMEGA_STATE_SYSTEM::UseLambdaOmegaStatePower()
{
    if (bIsLambdaOmegaStateActive && LambdaOmegaStateLevel > 0)
    {
        OnLambdaOmegaStatePowerUsed.Broadcast(LambdaOmegaStatePowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Lambda-Omega State Power Used: %.2f"), LambdaOmegaStatePowerCost);
    }
    else
    {
        OnLambdaOmegaStatePowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Lambda-Omega State Power Use Failed: System not active or insufficient level."));
    }
}

void UCOMPLETE_LAMBDA_OMEGA_STATE_SYSTEM::PerformLambdaOmegaStateAbility()
{
    if (bIsLambdaOmegaStateActive && LambdaOmegaStateLevel >= LambdaOmegaStateThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Lambda-Omega State Ability at Level %d!"), LambdaOmegaStateLevel);
        OnLambdaOmegaStateAbilityPerformed.Broadcast(LambdaOmegaStateLevel);
        UseLambdaOmegaStatePower();
        
        // Perform lambda-omega state ability based on level
        switch (LambdaOmegaStateLevel / 20)
        {
            case 0:
                ExerciseLambdaPhaseUltimateAbsoluteSupremeUltimacy();
                break;
            case 1:
                AchieveOmegaPhaseFinalUltimateAbsoluteFinality();
                break;
            case 2:
                ControlUltimateAbsoluteStateTransitions();
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
    else if (LambdaOmegaStateLevel < LambdaOmegaStateThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Lambda-Omega State Level too low to perform ability. Required: %.0f, Current: %d"), LambdaOmegaStateThreshold, LambdaOmegaStateLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Lambda-Omega State is not active, cannot perform ability."));
    }
}

bool UCOMPLETE_LAMBDA_OMEGA_STATE_SYSTEM::IsLambdaOmegaStateActive() const
{
    return bIsLambdaOmegaStateActive;
}

int32 UCOMPLETE_LAMBDA_OMEGA_STATE_SYSTEM::GetLambdaOmegaStateLevel() const
{
    return LambdaOmegaStateLevel;
}

float UCOMPLETE_LAMBDA_OMEGA_STATE_SYSTEM::GetLambdaOmegaStatePowerCost() const
{
    return LambdaOmegaStatePowerCost;
}

void UCOMPLETE_LAMBDA_OMEGA_STATE_SYSTEM::ExerciseLambdaPhaseUltimateAbsoluteSupremeUltimacy()
{
    if (bIsLambdaOmegaStateActive)
    {
        float UltimacyPower = LambdaPhaseUltimateAbsoluteSupremeUltimacy * (LambdaOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Exercising Lambda Phase Ultimate Absolute Supreme Ultimacy with power: %.2f"), UltimacyPower);
        // Apply lambda phase ultimate absolute supreme ultimacy effects
    }
}

void UCOMPLETE_LAMBDA_OMEGA_STATE_SYSTEM::AchieveOmegaPhaseFinalUltimateAbsoluteFinality()
{
    if (bIsLambdaOmegaStateActive)
    {
        float FinalityPower = OmegaPhaseFinalUltimateAbsoluteFinality * (LambdaOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Omega Phase Final Ultimate Absolute Finality with power: %.2f"), FinalityPower);
        // Apply omega phase final ultimate absolute finality effects
    }
}

void UCOMPLETE_LAMBDA_OMEGA_STATE_SYSTEM::ControlUltimateAbsoluteStateTransitions()
{
    if (bIsLambdaOmegaStateActive)
    {
        float TransitionPower = UltimateAbsoluteStateTransition * (LambdaOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Controlling Ultimate-Absolute State Transitions with power: %.2f"), TransitionPower);
        // Apply ultimate-absolute state transition control effects
    }
}

void UCOMPLETE_LAMBDA_OMEGA_STATE_SYSTEM::DominatePlanckQuantumStates()
{
    if (bIsLambdaOmegaStateActive)
    {
        float PlanckPower = PlanckQuantumStateSupremacy * (LambdaOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Dominating Planck-Quantum States with power: %.2f"), PlanckPower);
        // Apply planck-quantum state domination effects
    }
}

void UCOMPLETE_LAMBDA_OMEGA_STATE_SYSTEM::WieldFinalStateUltimateAbsoluteUltimacy()
{
    if (bIsLambdaOmegaStateActive)
    {
        float FinalStatePower = FinalStateUltimateAbsoluteUltimacy * (LambdaOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Wielding Final State Ultimate Absolute Ultimacy with power: %.2f"), FinalStatePower);
        // Apply final state ultimate absolute ultimacy effects
    }
}

bool UCOMPLETE_LAMBDA_OMEGA_STATE_SYSTEM::CanActivateLambdaOmegaState() const
{
    return LambdaOmegaStateLevel > 0;
}

void UCOMPLETE_LAMBDA_OMEGA_STATE_SYSTEM::UpdateLambdaOmegaStateStats()
{
    // Update lambda-omega state properties based on level
    LambdaPhaseUltimateAbsoluteSupremeUltimacy = LambdaOmegaStateLevel * 18.5f;
    OmegaPhaseFinalUltimateAbsoluteFinality = LambdaOmegaStateLevel * 18.3f;
    UltimateAbsoluteStateTransition = LambdaOmegaStateLevel * 18.2f;
    PlanckQuantumStateSupremacy = LambdaOmegaStateLevel * 18.1f;
    FinalStateUltimateAbsoluteUltimacy = LambdaOmegaStateLevel * 19.0f;
}

void UCOMPLETE_LAMBDA_OMEGA_STATE_SYSTEM::OnLambdaOmegaStateChanged()
{
    // Handle state change effects
    if (bIsLambdaOmegaStateActive)
    {
        // Apply lambda-omega state activation effects
        UE_LOG(LogTemp, Warning, TEXT("Lambda-Omega State state changed to ACTIVE"));
    }
    else
    {
        // Remove lambda-omega state effects
        UE_LOG(LogTemp, Warning, TEXT("Lambda-Omega State state changed to INACTIVE"));
    }
}
