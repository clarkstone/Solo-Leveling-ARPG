#include "COMPLETE_ABSOLUTE_VOID_NULL_SYSTEM.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCOMPLETE_ABSOLUTE_VOID_NULL_SYSTEM::UCOMPLETE_ABSOLUTE_VOID_NULL_SYSTEM()
{
    PrimaryComponentTick.bCanEverTick = false;
    AbsoluteVoidNullLevel = 0;
    MaxAbsoluteVoidNullLevel = 100;
    bIsAbsoluteVoidNullActive = false;
    AbsoluteVoidNullPowerCost = 35.0f;
    AbsoluteVoidNullThreshold = 90.0f;
    
    // Initialize absolute-void-null properties
    AbsoluteVoidNullMastery = 0.0f;
    SupremeVoidAnnihilation = 0.0f;
    PerfectNullVoidEmptiness = 0.0f;
    ConceptualVoidNullOblivion = 0.0f;
    ExistenceVoidNullNegation = 0.0f;
}

void UCOMPLETE_ABSOLUTE_VOID_NULL_SYSTEM::BeginPlay()
{
    Super::BeginPlay();
    UpdateAbsoluteVoidNullStats();
}

void UCOMPLETE_ABSOLUTE_VOID_NULL_SYSTEM::ActivateAbsoluteVoidNull()
{
    if (!bIsAbsoluteVoidNullActive && CanActivateAbsoluteVoidNull())
    {
        bIsAbsoluteVoidNullActive = true;
        OnAbsoluteVoidNullActivated.Broadcast(AbsoluteVoidNullLevel);
        OnAbsoluteVoidNullStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Absolute-Void-Null System Activated at Level: %d"), AbsoluteVoidNullLevel);
    }
}

void UCOMPLETE_ABSOLUTE_VOID_NULL_SYSTEM::DeactivateAbsoluteVoidNull()
{
    if (bIsAbsoluteVoidNullActive)
    {
        bIsAbsoluteVoidNullActive = false;
        OnAbsoluteVoidNullDeactivated.Broadcast(AbsoluteVoidNullLevel);
        OnAbsoluteVoidNullStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Absolute-Void-Null System Deactivated."));
    }
}

void UCOMPLETE_ABSOLUTE_VOID_NULL_SYSTEM::SetAbsoluteVoidNullLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxAbsoluteVoidNullLevel)
    {
        int32 OldLevel = AbsoluteVoidNullLevel;
        AbsoluteVoidNullLevel = NewLevel;
        UpdateAbsoluteVoidNullStats();
        OnAbsoluteVoidNullLevelChanged.Broadcast(OldLevel, AbsoluteVoidNullLevel);
        UE_LOG(LogTemp, Warning, TEXT("Absolute-Void-Null Level set to: %d"), AbsoluteVoidNullLevel);
        
        if (AbsoluteVoidNullLevel >= MaxAbsoluteVoidNullLevel)
        {
            OnAbsoluteVoidNullMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Absolute-Void-Null Max Level Reached!"));
        }
    }
}

void UCOMPLETE_ABSOLUTE_VOID_NULL_SYSTEM::UseAbsoluteVoidNullPower()
{
    if (bIsAbsoluteVoidNullActive && AbsoluteVoidNullLevel > 0)
    {
        OnAbsoluteVoidNullPowerUsed.Broadcast(AbsoluteVoidNullPowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Absolute-Void-Null Power Used: %.2f"), AbsoluteVoidNullPowerCost);
    }
    else
    {
        OnAbsoluteVoidNullPowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Absolute-Void-Null Power Use Failed: System not active or insufficient level."));
    }
}

void UCOMPLETE_ABSOLUTE_VOID_NULL_SYSTEM::PerformAbsoluteVoidNullAbility()
{
    if (bIsAbsoluteVoidNullActive && AbsoluteVoidNullLevel >= AbsoluteVoidNullThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Absolute-Void-Null Ability at Level %d!"), AbsoluteVoidNullLevel);
        OnAbsoluteVoidNullAbilityPerformed.Broadcast(AbsoluteVoidNullLevel);
        UseAbsoluteVoidNullPower();
        
        // Perform absolute-void-null ability based on level
        switch (AbsoluteVoidNullLevel / 20)
        {
            case 0:
                MasterAbsoluteVoidNull();
                break;
            case 1:
                AnnihilateVoidNullSupremely();
                break;
            case 2:
                AchievePerfectNullVoidEmptiness();
                break;
            case 3:
                InduceConceptualVoidNullOblivion();
                break;
            case 4:
            case 5:
                NegateExistenceVoidNull();
                break;
            default:
                NegateExistenceVoidNull();
                break;
        }
    }
    else if (AbsoluteVoidNullLevel < AbsoluteVoidNullThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Absolute-Void-Null Level too low to perform ability. Required: %.0f, Current: %d"), AbsoluteVoidNullThreshold, AbsoluteVoidNullLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Absolute-Void-Null is not active, cannot perform ability."));
    }
}

bool UCOMPLETE_ABSOLUTE_VOID_NULL_SYSTEM::IsAbsoluteVoidNullActive() const
{
    return bIsAbsoluteVoidNullActive;
}

int32 UCOMPLETE_ABSOLUTE_VOID_NULL_SYSTEM::GetAbsoluteVoidNullLevel() const
{
    return AbsoluteVoidNullLevel;
}

float UCOMPLETE_ABSOLUTE_VOID_NULL_SYSTEM::GetAbsoluteVoidNullPowerCost() const
{
    return AbsoluteVoidNullPowerCost;
}

void UCOMPLETE_ABSOLUTE_VOID_NULL_SYSTEM::MasterAbsoluteVoidNull()
{
    if (bIsAbsoluteVoidNullActive)
    {
        float VoidMastery = AbsoluteVoidNullMastery * (AbsoluteVoidNullLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Mastering Absolute-Void-Null with power: %.2f"), VoidMastery);
        // Apply absolute-void-null mastery effects
    }
}

void UCOMPLETE_ABSOLUTE_VOID_NULL_SYSTEM::AnnihilateVoidNullSupremely()
{
    if (bIsAbsoluteVoidNullActive)
    {
        float AnnihilationPower = SupremeVoidAnnihilation * (AbsoluteVoidNullLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Annihilating Void-Null Supremely with power: %.2f"), AnnihilationPower);
        // Apply supreme void-null annihilation effects
    }
}

void UCOMPLETE_ABSOLUTE_VOID_NULL_SYSTEM::AchievePerfectNullVoidEmptiness()
{
    if (bIsAbsoluteVoidNullActive)
    {
        float EmptinessPower = PerfectNullVoidEmptiness * (AbsoluteVoidNullLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Perfect Null-Void Emptiness with power: %.2f"), EmptinessPower);
        // Apply perfect null-void emptiness effects
    }
}

void UCOMPLETE_ABSOLUTE_VOID_NULL_SYSTEM::InduceConceptualVoidNullOblivion()
{
    if (bIsAbsoluteVoidNullActive)
    {
        float OblivionPower = ConceptualVoidNullOblivion * (AbsoluteVoidNullLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Inducing Conceptual Void-Null Oblivion with power: %.2f"), OblivionPower);
        // Apply conceptual void-null oblivion effects
    }
}

void UCOMPLETE_ABSOLUTE_VOID_NULL_SYSTEM::NegateExistenceVoidNull()
{
    if (bIsAbsoluteVoidNullActive)
    {
        float NegationPower = ExistenceVoidNullNegation * (AbsoluteVoidNullLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Negating Existence Void-Null with power: %.2f"), NegationPower);
        // Apply existence void-null negation effects
    }
}

bool UCOMPLETE_ABSOLUTE_VOID_NULL_SYSTEM::CanActivateAbsoluteVoidNull() const
{
    return AbsoluteVoidNullLevel > 0;
}

void UCOMPLETE_ABSOLUTE_VOID_NULL_SYSTEM::UpdateAbsoluteVoidNullStats()
{
    // Update absolute-void-null properties based on level
    AbsoluteVoidNullMastery = AbsoluteVoidNullLevel * 10.8f;
    SupremeVoidAnnihilation = AbsoluteVoidNullLevel * 10.6f;
    PerfectNullVoidEmptiness = AbsoluteVoidNullLevel * 10.5f;
    ConceptualVoidNullOblivion = AbsoluteVoidNullLevel * 10.4f;
    ExistenceVoidNullNegation = AbsoluteVoidNullLevel * 11.2f;
}

void UCOMPLETE_ABSOLUTE_VOID_NULL_SYSTEM::OnAbsoluteVoidNullStateChanged()
{
    // Handle state change effects
    if (bIsAbsoluteVoidNullActive)
    {
        // Apply absolute-void-null activation effects
        UE_LOG(LogTemp, Warning, TEXT("Absolute-Void-Null state changed to ACTIVE"));
    }
    else
    {
        // Remove absolute-void-null effects
        UE_LOG(LogTemp, Warning, TEXT("Absolute-Void-Null state changed to INACTIVE"));
    }
}
