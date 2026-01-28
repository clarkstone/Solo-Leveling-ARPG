#include "COMPLETE_VOID_NULL_SYSTEM.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCOMPLETE_VOID_NULL_SYSTEM::UCOMPLETE_VOID_NULL_SYSTEM()
{
    PrimaryComponentTick.bCanEverTick = false;
    VoidNullLevel = 0;
    MaxVoidNullLevel = 100;
    bIsVoidNullActive = false;
    VoidNullPowerCost = 30.0f;
    VoidNullThreshold = 85.0f;
    
    // Initialize void-null properties
    VoidNullMastery = 0.0f;
    UltimateVoidAnnihilation = 0.0f;
    PerfectNullEmptiness = 0.0f;
    ConceptualVoidOblivion = 0.0f;
    ExistenceVoidNegation = 0.0f;
}

void UCOMPLETE_VOID_NULL_SYSTEM::BeginPlay()
{
    Super::BeginPlay();
    UpdateVoidNullStats();
}

void UCOMPLETE_VOID_NULL_SYSTEM::ActivateVoidNull()
{
    if (!bIsVoidNullActive && CanActivateVoidNull())
    {
        bIsVoidNullActive = true;
        OnVoidNullActivated.Broadcast(VoidNullLevel);
        OnVoidNullStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Void-Null System Activated at Level: %d"), VoidNullLevel);
    }
}

void UCOMPLETE_VOID_NULL_SYSTEM::DeactivateVoidNull()
{
    if (bIsVoidNullActive)
    {
        bIsVoidNullActive = false;
        OnVoidNullDeactivated.Broadcast(VoidNullLevel);
        OnVoidNullStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Void-Null System Deactivated."));
    }
}

void UCOMPLETE_VOID_NULL_SYSTEM::SetVoidNullLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxVoidNullLevel)
    {
        int32 OldLevel = VoidNullLevel;
        VoidNullLevel = NewLevel;
        UpdateVoidNullStats();
        OnVoidNullLevelChanged.Broadcast(OldLevel, VoidNullLevel);
        UE_LOG(LogTemp, Warning, TEXT("Void-Null Level set to: %d"), VoidNullLevel);
        
        if (VoidNullLevel >= MaxVoidNullLevel)
        {
            OnVoidNullMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Void-Null Max Level Reached!"));
        }
    }
}

void UCOMPLETE_VOID_NULL_SYSTEM::UseVoidNullPower()
{
    if (bIsVoidNullActive && VoidNullLevel > 0)
    {
        OnVoidNullPowerUsed.Broadcast(VoidNullPowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Void-Null Power Used: %.2f"), VoidNullPowerCost);
    }
    else
    {
        OnVoidNullPowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Void-Null Power Use Failed: System not active or insufficient level."));
    }
}

void UCOMPLETE_VOID_NULL_SYSTEM::PerformVoidNullAbility()
{
    if (bIsVoidNullActive && VoidNullLevel >= VoidNullThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Void-Null Ability at Level %d!"), VoidNullLevel);
        OnVoidNullAbilityPerformed.Broadcast(VoidNullLevel);
        UseVoidNullPower();
        
        // Perform void-null ability based on level
        switch (VoidNullLevel / 20)
        {
            case 0:
                MasterVoidNull();
                break;
            case 1:
                AnnihilateVoidUltimately();
                break;
            case 2:
                AchievePerfectNullEmptiness();
                break;
            case 3:
                InduceConceptualVoidOblivion();
                break;
            case 4:
            case 5:
                NegateExistenceVoid();
                break;
            default:
                NegateExistenceVoid();
                break;
        }
    }
    else if (VoidNullLevel < VoidNullThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Void-Null Level too low to perform ability. Required: %.0f, Current: %d"), VoidNullThreshold, VoidNullLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Void-Null is not active, cannot perform ability."));
    }
}

bool UCOMPLETE_VOID_NULL_SYSTEM::IsVoidNullActive() const
{
    return bIsVoidNullActive;
}

int32 UCOMPLETE_VOID_NULL_SYSTEM::GetVoidNullLevel() const
{
    return VoidNullLevel;
}

float UCOMPLETE_VOID_NULL_SYSTEM::GetVoidNullPowerCost() const
{
    return VoidNullPowerCost;
}

void UCOMPLETE_VOID_NULL_SYSTEM::MasterVoidNull()
{
    if (bIsVoidNullActive)
    {
        float VoidMastery = VoidNullMastery * (VoidNullLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Mastering Void-Null with power: %.2f"), VoidMastery);
        // Apply void-null mastery effects
    }
}

void UCOMPLETE_VOID_NULL_SYSTEM::AnnihilateVoidUltimately()
{
    if (bIsVoidNullActive)
    {
        float AnnihilationPower = UltimateVoidAnnihilation * (VoidNullLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Annihilating Void Ultimately with power: %.2f"), AnnihilationPower);
        // Apply ultimate void annihilation effects
    }
}

void UCOMPLETE_VOID_NULL_SYSTEM::AchievePerfectNullEmptiness()
{
    if (bIsVoidNullActive)
    {
        float EmptinessPower = PerfectNullEmptiness * (VoidNullLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Perfect Null Emptiness with power: %.2f"), EmptinessPower);
        // Apply perfect null emptiness effects
    }
}

void UCOMPLETE_VOID_NULL_SYSTEM::InduceConceptualVoidOblivion()
{
    if (bIsVoidNullActive)
    {
        float OblivionPower = ConceptualVoidOblivion * (VoidNullLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Inducing Conceptual Void Oblivion with power: %.2f"), OblivionPower);
        // Apply conceptual void oblivion effects
    }
}

void UCOMPLETE_VOID_NULL_SYSTEM::NegateExistenceVoid()
{
    if (bIsVoidNullActive)
    {
        float NegationPower = ExistenceVoidNegation * (VoidNullLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Negating Existence Void with power: %.2f"), NegationPower);
        // Apply existence void negation effects
    }
}

bool UCOMPLETE_VOID_NULL_SYSTEM::CanActivateVoidNull() const
{
    return VoidNullLevel > 0;
}

void UCOMPLETE_VOID_NULL_SYSTEM::UpdateVoidNullStats()
{
    // Update void-null properties based on level
    VoidNullMastery = VoidNullLevel * 8.0f;
    UltimateVoidAnnihilation = VoidNullLevel * 7.8f;
    PerfectNullEmptiness = VoidNullLevel * 7.7f;
    ConceptualVoidOblivion = VoidNullLevel * 7.6f;
    ExistenceVoidNegation = VoidNullLevel * 8.4f;
}

void UCOMPLETE_VOID_NULL_SYSTEM::OnVoidNullStateChanged()
{
    // Handle state change effects
    if (bIsVoidNullActive)
    {
        // Apply void-null activation effects
        UE_LOG(LogTemp, Warning, TEXT("Void-Null state changed to ACTIVE"));
    }
    else
    {
        // Remove void-null effects
        UE_LOG(LogTemp, Warning, TEXT("Void-Null state changed to INACTIVE"));
    }
}
