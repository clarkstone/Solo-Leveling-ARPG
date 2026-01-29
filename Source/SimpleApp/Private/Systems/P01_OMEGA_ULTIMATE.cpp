#include "P01_OMEGA_ULTIMATE.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP01_OMEGA_ULTIMATE::UP01_OMEGA_ULTIMATE()
{
    PrimaryComponentTick.bCanEverTick = false;
    UltimateOmegaStateLevel = 0;
    MaxUltimateOmegaStateLevel = 100;
    bIsUltimateOmegaStateActive = false;
    UltimateOmegaStatePowerCost = 10.0f;
    UltimateOmegaStateThreshold = 10.0f;
    
    // Initialize ultimate omega state properties
    OmegaPhaseUltimacy = 0.0f;
    FinalStateAuthority = 0.0f;
    StateTransitions = 0.0f;
    UltimateConsciousness = 0.0f;
    FinalUltimacy = 0.0f;
}

void UP01_OMEGA_ULTIMATE::BeginPlay()
{
    Super::BeginPlay();
    UpdateUltimateOmegaStateStats();
}

void UP01_OMEGA_ULTIMATE::ActivateUltimateOmegaState()
{
    if (!bIsUltimateOmegaStateActive && CanActivateUltimateOmegaState())
    {
        bIsUltimateOmegaStateActive = true;
        OnUltimateOmegaStateActivated.Broadcast(UltimateOmegaStateLevel);
        OnUltimateOmegaStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Ultimate Omega State System Activated at Level: %d"), UltimateOmegaStateLevel);
    }
}

void UP01_OMEGA_ULTIMATE::DeactivateUltimateOmegaState()
{
    if (bIsUltimateOmegaStateActive)
    {
        bIsUltimateOmegaStateActive = false;
        OnUltimateOmegaStateDeactivated.Broadcast(UltimateOmegaStateLevel);
        OnUltimateOmegaStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Ultimate Omega State System Deactivated."));
    }
}

void UP01_OMEGA_ULTIMATE::SetUltimateOmegaStateLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxUltimateOmegaStateLevel)
    {
        int32 OldLevel = UltimateOmegaStateLevel;
        UltimateOmegaStateLevel = NewLevel;
        UpdateUltimateOmegaStateStats();
        OnUltimateOmegaStateChanged.Broadcast(OldLevel, UltimateOmegaStateLevel);
        UE_LOG(LogTemp, Warning, TEXT("Ultimate Omega State Level set to: %d"), UltimateOmegaStateLevel);
        
        if (UltimateOmegaStateLevel >= MaxUltimateOmegaStateLevel)
        {
            OnUltimateOmegaStateMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Ultimate Omega State Max Level Reached!"));
        }
    }
}

void UP01_OMEGA_ULTIMATE::UseUltimateOmegaStatePower()
{
    if (bIsUltimateOmegaStateActive && UltimateOmegaStateLevel > 0)
    {
        OnUltimateOmegaStatePowerUsed.Broadcast(UltimateOmegaStatePowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Ultimate Omega State Power Used: %.2f"), UltimateOmegaStatePowerCost);
    }
    else
    {
        OnUltimateOmegaStatePowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Ultimate Omega State Power Use Failed: System not active or insufficient level."));
    }
}

void UP01_OMEGA_ULTIMATE::PerformUltimateOmegaStateAbility()
{
    if (bIsUltimateOmegaStateActive && UltimateOmegaStateLevel >= UltimateOmegaStateThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Ultimate Omega State Ability at Level %d!"), UltimateOmegaStateLevel);
        OnUltimateOmegaStateAbilityPerformed.Broadcast(UltimateOmegaStateLevel);
        UseUltimateOmegaStatePower();
        
        // Perform ultimate omega state ability based on level
        switch (UltimateOmegaStateLevel / 20)
        {
            case 0:
                AchieveOmegaPhaseUltimacy();
                break;
            case 1:
                WieldFinalStateAuthority();
                break;
            case 2:
                ControlStateTransitions();
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
    else if (UltimateOmegaStateLevel < UltimateOmegaStateThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Ultimate Omega State Level too low to perform ability. Required: %.0f, Current: %d"), UltimateOmegaStateThreshold, UltimateOmegaStateLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Ultimate Omega State is not active, cannot perform ability."));
    }
}

bool UP01_OMEGA_ULTIMATE::IsUltimateOmegaStateActive() const
{
    return bIsUltimateOmegaStateActive;
}

int32 UP01_OMEGA_ULTIMATE::GetUltimateOmegaStateLevel() const
{
    return UltimateOmegaStateLevel;
}

float UP01_OMEGA_ULTIMATE::GetUltimateOmegaStatePowerCost() const
{
    return UltimateOmegaStatePowerCost;
}

void UP01_OMEGA_ULTIMATE::AchieveOmegaPhaseUltimacy()
{
    if (bIsUltimateOmegaStateActive)
    {
        float UltimacyPower = OmegaPhaseUltimacy * (UltimateOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Omega Phase Ultimacy with power: %.2f"), UltimacyPower);
        // Apply omega phase ultimacy effects
    }
}

void UP01_OMEGA_ULTIMATE::WieldFinalStateAuthority()
{
    if (bIsUltimateOmegaStateActive)
    {
        float AuthorityPower = FinalStateAuthority * (UltimateOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Wielding Final State Authority with power: %.2f"), AuthorityPower);
        // Apply final state authority effects
    }
}

void UP01_OMEGA_ULTIMATE::ControlStateTransitions()
{
    if (bIsUltimateOmegaStateActive)
    {
        float TransitionPower = StateTransitions * (UltimateOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, TEXT("Controlling State Transitions with power: %.2f"), TransitionPower);
        // Apply state transition control effects
    }
}

void UP01_OMEGA_ULTIMATE::AccessUltimateConsciousness()
{
    if (bIsUltimateOmegaStateActive)
    {
        float ConsciousnessPower = UltimateConsciousness * (UltimateOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Accessing Ultimate Consciousness with power: %.2f"), ConsciousnessPower);
        // Apply ultimate consciousness effects
    }
}

void UP01_OMEGA_ULTIMATE::WieldFinalUltimacy()
{
    if (bIsUltimateOmegaStateActive)
    {
        float UltimacyPower = FinalUltimacy * (UltimateOmegaStateLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Wielding Final Ultimacy with power: %.2f"), UltimacyPower);
        // Apply final ultimacy effects
    }
}

bool UP01_OMEGA_ULTIMATE::CanActivateUltimateOmegaState() const
{
    return UltimateOmegaStateLevel > 0;
}

void UP01_OMEGA_ULTIMATE::UpdateUltimateOmegaStateStats()
{
    // Update ultimate omega state properties based on level
    OmegaPhaseUltimacy = UltimateOmegaStateLevel * 2.0f;
    FinalStateAuthority = UltimateOmegaStateLevel * 2.2f;
    StateTransitions = UltimateOmegaStateLevel * 1.8f;
    UltimateConsciousness = UltimateOmegaStateLevel * 1.9f;
    FinalUltimacy = UltimateOmegaStateLevel * 2.1f;
}

void UP01_OMEGA_ULTIMATE::OnUltimateOmegaStateChanged()
{
    // Handle state change effects
    if (bIsUltimateOmegaStateActive)
    {
        // Apply ultimate omega state activation effects
        UE_LOG(LogTemp, Warning, TEXT("Ultimate Omega State state changed to ACTIVE"));
    }
    else
    {
        // Remove ultimate omega state effects
        UE_LOG(LogTemp, Warning, TEXT("Ultimate Omega State state changed to INACTIVE"));
    }
}
