#include "COMPLETE_NULL_ABSOLUTE_VOID_SYSTEM.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCOMPLETE_NULL_ABSOLUTE_VOID_SYSTEM::UCOMPLETE_NULL_ABSOLUTE_VOID_SYSTEM()
{
    PrimaryComponentTick.bCanEverTick = false;
    NullAbsoluteVoidLevel = 0;
    MaxNullAbsoluteVoidLevel = 100;
    bIsNullAbsoluteVoidActive = false;
    NullAbsoluteVoidPowerCost = 40.0f;
    NullAbsoluteVoidThreshold = 95.0f;
    
    // Initialize null-absolute-void properties
    NullAbsoluteVoidMastery = 0.0f;
    AbsoluteVoidAnnihilation = 0.0f;
    PerfectNullEmptiness = 0.0f;
    ConceptualNullOblivion = 0.0f;
    ExistenceNullNegation = 0.0f;
}

void UCOMPLETE_NULL_ABSOLUTE_VOID_SYSTEM::BeginPlay()
{
    Super::BeginPlay();
    UpdateNullAbsoluteVoidStats();
}

void UCOMPLETE_NULL_ABSOLUTE_VOID_SYSTEM::ActivateNullAbsoluteVoid()
{
    if (!bIsNullAbsoluteVoidActive && CanActivateNullAbsoluteVoid())
    {
        bIsNullAbsoluteVoidActive = true;
        OnNullAbsoluteVoidActivated.Broadcast(NullAbsoluteVoidLevel);
        OnNullAbsoluteVoidStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Null-Absolute-Void System Activated at Level: %d"), NullAbsoluteVoidLevel);
    }
}

void UCOMPLETE_NULL_ABSOLUTE_VOID_SYSTEM::DeactivateNullAbsoluteVoid()
{
    if (bIsNullAbsoluteVoidActive)
    {
        bIsNullAbsoluteVoidActive = false;
        OnNullAbsoluteVoidDeactivated.Broadcast(NullAbsoluteVoidLevel);
        OnNullAbsoluteVoidStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Null-Absolute-Void System Deactivated."));
    }
}

void UCOMPLETE_NULL_ABSOLUTE_VOID_SYSTEM::SetNullAbsoluteVoidLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxNullAbsoluteVoidLevel)
    {
        int32 OldLevel = NullAbsoluteVoidLevel;
        NullAbsoluteVoidLevel = NewLevel;
        UpdateNullAbsoluteVoidStats();
        OnNullAbsoluteVoidLevelChanged.Broadcast(OldLevel, NullAbsoluteVoidLevel);
        UE_LOG(LogTemp, Warning, TEXT("Null-Absolute-Void Level set to: %d"), NullAbsoluteVoidLevel);
        
        if (NullAbsoluteVoidLevel >= MaxNullAbsoluteVoidLevel)
        {
            OnNullAbsoluteVoidMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Null-Absolute-Void Max Level Reached!"));
        }
    }
}

void UCOMPLETE_NULL_ABSOLUTE_VOID_SYSTEM::UseNullAbsoluteVoidPower()
{
    if (bIsNullAbsoluteVoidActive && NullAbsoluteVoidLevel > 0)
    {
        OnNullAbsoluteVoidPowerUsed.Broadcast(NullAbsoluteVoidPowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Null-Absolute-Void Power Used: %.2f"), NullAbsoluteVoidPowerCost);
    }
    else
    {
        OnNullAbsoluteVoidPowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Null-Absolute-Void Power Use Failed: System not active or insufficient level."));
    }
}

void UCOMPLETE_NULL_ABSOLUTE_VOID_SYSTEM::PerformNullAbsoluteVoidAbility()
{
    if (bIsNullAbsoluteVoidActive && NullAbsoluteVoidLevel >= NullAbsoluteVoidThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Null-Absolute-Void Ability at Level %d!"), NullAbsoluteVoidLevel);
        OnNullAbsoluteVoidAbilityPerformed.Broadcast(NullAbsoluteVoidLevel);
        UseNullAbsoluteVoidPower();
        
        // Perform null-absolute-void ability based on level
        switch (NullAbsoluteVoidLevel / 20)
        {
            case 0:
                MasterNullAbsoluteVoid();
                break;
            case 1:
                AnnihilateNullAbsolutely();
                break;
            case 2:
                AchievePerfectNullEmptiness();
                break;
            case 3:
                InduceConceptualNullOblivion();
                break;
            case 4:
            case 5:
                NegateExistenceNull();
                break;
            default:
                NegateExistenceNull();
                break;
        }
    }
    else if (NullAbsoluteVoidLevel < NullAbsoluteVoidThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Null-Absolute-Void Level too low to perform ability. Required: %.0f, Current: %d"), NullAbsoluteVoidThreshold, NullAbsoluteVoidLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Null-Absolute-Void is not active, cannot perform ability."));
    }
}

bool UCOMPLETE_NULL_ABSOLUTE_VOID_SYSTEM::IsNullAbsoluteVoidActive() const
{
    return bIsNullAbsoluteVoidActive;
}

int32 UCOMPLETE_NULL_ABSOLUTE_VOID_SYSTEM::GetNullAbsoluteVoidLevel() const
{
    return NullAbsoluteVoidLevel;
}

float UCOMPLETE_NULL_ABSOLUTE_VOID_SYSTEM::GetNullAbsoluteVoidPowerCost() const
{
    return NullAbsoluteVoidPowerCost;
}

void UCOMPLETE_NULL_ABSOLUTE_VOID_SYSTEM::MasterNullAbsoluteVoid()
{
    if (bIsNullAbsoluteVoidActive)
    {
        float VoidMastery = NullAbsoluteVoidMastery * (NullAbsoluteVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Mastering Null-Absolute-Void with power: %.2f"), VoidMastery);
        // Apply null-absolute-void mastery effects
    }
}

void UCOMPLETE_NULL_ABSOLUTE_VOID_SYSTEM::AnnihilateNullAbsolutely()
{
    if (bIsNullAbsoluteVoidActive)
    {
        float AnnihilationPower = AbsoluteVoidAnnihilation * (NullAbsoluteVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Annihilating Null-Absolutely with power: %.2f"), AnnihilationPower);
        // Apply null-absolute annihilation effects
    }
}

void UCOMPLETE_NULL_ABSOLUTE_VOID_SYSTEM::AchievePerfectNullEmptiness()
{
    if (bIsNullAbsoluteVoidActive)
    {
        float EmptinessPower = PerfectNullEmptiness * (NullAbsoluteVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Perfect Null Emptiness with power: %.2f"), EmptinessPower);
        // Apply perfect null emptiness effects
    }
}

void UCOMPLETE_NULL_ABSOLUTE_VOID_SYSTEM::InduceConceptualNullOblivion()
{
    if (bIsNullAbsoluteVoidActive)
    {
        float OblivionPower = ConceptualNullOblivion * (NullAbsoluteVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Inducing Conceptual Null Oblivion with power: %.2f"), OblivionPower);
        // Apply conceptual null oblivion effects
    }
}

void UCOMPLETE_NULL_ABSOLUTE_VOID_SYSTEM::NegateExistenceNull()
{
    if (bIsNullAbsoluteVoidActive)
    {
        float NegationPower = ExistenceNullNegation * (NullAbsoluteVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Negating Existence Null with power: %.2f"), NegationPower);
        // Apply existence null negation effects
    }
}

bool UCOMPLETE_NULL_ABSOLUTE_VOID_SYSTEM::CanActivateNullAbsoluteVoid() const
{
    return NullAbsoluteVoidLevel > 0;
}

void UCOMPLETE_NULL_ABSOLUTE_VOID_SYSTEM::UpdateNullAbsoluteVoidStats()
{
    // Update null-absolute-void properties based on level
    NullAbsoluteVoidMastery = NullAbsoluteVoidLevel * 13.8f;
    AbsoluteVoidAnnihilation = NullAbsoluteVoidLevel * 13.6f;
    PerfectNullEmptiness = NullAbsoluteVoidLevel * 13.5f;
    ConceptualNullOblivion = NullAbsoluteVoidLevel * 13.4f;
    ExistenceNullNegation = NullAbsoluteVoidLevel * 14.2f;
}

void UCOMPLETE_NULL_ABSOLUTE_VOID_SYSTEM::OnNullAbsoluteVoidStateChanged()
{
    // Handle state change effects
    if (bIsNullAbsoluteVoidActive)
    {
        // Apply null-absolute-void activation effects
        UE_LOG(LogTemp, Warning, TEXT("Null-Absolute-Void state changed to ACTIVE"));
    }
    else
    {
        // Remove null-absolute-void effects
        UE_LOG(LogTemp, Warning, TEXT("Null-Absolute-Void state changed to INACTIVE"));
    }
}
