#include "COMPLETE_ABSOLUTE_VOID_SYSTEM.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCOMPLETE_ABSOLUTE_VOID_SYSTEM::UCOMPLETE_ABSOLUTE_VOID_SYSTEM()
{
    PrimaryComponentTick.bCanEverTick = false;
    AbsoluteVoidLevel = 0;
    MaxAbsoluteVoidLevel = 100;
    bIsAbsoluteVoidActive = false;
    AbsoluteVoidPowerCost = 20.0f;
    AbsoluteVoidThreshold = 70.0f;
    
    // Initialize absolute-void properties
    AbsoluteVoidMastery = 0.0f;
    UltimateAnnihilation = 0.0f;
    PerfectEmptiness = 0.0f;
    ConceptualOblivion = 0.0f;
    ExistenceNegation = 0.0f;
}

void UCOMPLETE_ABSOLUTE_VOID_SYSTEM::BeginPlay()
{
    Super::BeginPlay();
    UpdateAbsoluteVoidStats();
}

void UCOMPLETE_ABSOLUTE_VOID_SYSTEM::ActivateAbsoluteVoid()
{
    if (!bIsAbsoluteVoidActive && CanActivateAbsoluteVoid())
    {
        bIsAbsoluteVoidActive = true;
        OnAbsoluteVoidActivated.Broadcast(AbsoluteVoidLevel);
        OnAbsoluteVoidStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Absolute-Void System Activated at Level: %d"), AbsoluteVoidLevel);
    }
}

void UCOMPLETE_ABSOLUTE_VOID_SYSTEM::DeactivateAbsoluteVoid()
{
    if (bIsAbsoluteVoidActive)
    {
        bIsAbsoluteVoidActive = false;
        OnAbsoluteVoidDeactivated.Broadcast(AbsoluteVoidLevel);
        OnAbsoluteVoidStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Absolute-Void System Deactivated."));
    }
}

void UCOMPLETE_ABSOLUTE_VOID_SYSTEM::SetAbsoluteVoidLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxAbsoluteVoidLevel)
    {
        int32 OldLevel = AbsoluteVoidLevel;
        AbsoluteVoidLevel = NewLevel;
        UpdateAbsoluteVoidStats();
        OnAbsoluteVoidLevelChanged.Broadcast(OldLevel, AbsoluteVoidLevel);
        UE_LOG(LogTemp, Warning, TEXT("Absolute-Void Level set to: %d"), AbsoluteVoidLevel);
        
        if (AbsoluteVoidLevel >= MaxAbsoluteVoidLevel)
        {
            OnAbsoluteVoidMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Absolute-Void Max Level Reached!"));
        }
    }
}

void UCOMPLETE_ABSOLUTE_VOID_SYSTEM::UseAbsoluteVoidPower()
{
    if (bIsAbsoluteVoidActive && AbsoluteVoidLevel > 0)
    {
        OnAbsoluteVoidPowerUsed.Broadcast(AbsoluteVoidPowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Absolute-Void Power Used: %.2f"), AbsoluteVoidPowerCost);
    }
    else
    {
        OnAbsoluteVoidPowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Absolute-Void Power Use Failed: System not active or insufficient level."));
    }
}

void UCOMPLETE_ABSOLUTE_VOID_SYSTEM::PerformAbsoluteVoidAbility()
{
    if (bIsAbsoluteVoidActive && AbsoluteVoidLevel >= AbsoluteVoidThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Absolute-Void Ability at Level %d!"), AbsoluteVoidLevel);
        OnAbsoluteVoidAbilityPerformed.Broadcast(AbsoluteVoidLevel);
        UseAbsoluteVoidPower();
        
        // Perform absolute-void ability based on level
        switch (AbsoluteVoidLevel / 20)
        {
            case 0:
                MasterAbsoluteVoid();
                break;
            case 1:
                AnnihilateUltimately();
                break;
            case 2:
                AchievePerfectEmptiness();
                break;
            case 3:
                InduceConceptualOblivion();
                break;
            case 4:
            case 5:
                NegateExistence();
                break;
            default:
                NegateExistence();
                break;
        }
    }
    else if (AbsoluteVoidLevel < AbsoluteVoidThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Absolute-Void Level too low to perform ability. Required: %.0f, Current: %d"), AbsoluteVoidThreshold, AbsoluteVoidLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Absolute-Void is not active, cannot perform ability."));
    }
}

bool UCOMPLETE_ABSOLUTE_VOID_SYSTEM::IsAbsoluteVoidActive() const
{
    return bIsAbsoluteVoidActive;
}

int32 UCOMPLETE_ABSOLUTE_VOID_SYSTEM::GetAbsoluteVoidLevel() const
{
    return AbsoluteVoidLevel;
}

float UCOMPLETE_ABSOLUTE_VOID_SYSTEM::GetAbsoluteVoidPowerCost() const
{
    return AbsoluteVoidPowerCost;
}

void UCOMPLETE_ABSOLUTE_VOID_SYSTEM::MasterAbsoluteVoid()
{
    if (bIsAbsoluteVoidActive)
    {
        float VoidMastery = AbsoluteVoidMastery * (AbsoluteVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Mastering Absolute Void with power: %.2f"), VoidMastery);
        // Apply absolute void mastery effects
    }
}

void UCOMPLETE_ABSOLUTE_VOID_SYSTEM::AnnihilateUltimately()
{
    if (bIsAbsoluteVoidActive)
    {
        float AnnihilationPower = UltimateAnnihilation * (AbsoluteVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Annihilating Ultimately with power: %.2f"), AnnihilationPower);
        // Apply ultimate annihilation effects
    }
}

void UCOMPLETE_ABSOLUTE_VOID_SYSTEM::AchievePerfectEmptiness()
{
    if (bIsAbsoluteVoidActive)
    {
        float EmptinessPower = PerfectEmptiness * (AbsoluteVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Perfect Emptiness with power: %.2f"), EmptinessPower);
        // Apply perfect emptiness effects
    }
}

void UCOMPLETE_ABSOLUTE_VOID_SYSTEM::InduceConceptualOblivion()
{
    if (bIsAbsoluteVoidActive)
    {
        float OblivionPower = ConceptualOblivion * (AbsoluteVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Inducing Conceptual Oblivion with power: %.2f"), OblivionPower);
        // Apply conceptual oblivion effects
    }
}

void UCOMPLETE_ABSOLUTE_VOID_SYSTEM::NegateExistence()
{
    if (bIsAbsoluteVoidActive)
    {
        float NegationPower = ExistenceNegation * (AbsoluteVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Negating Existence with power: %.2f"), NegationPower);
        // Apply existence negation effects
    }
}

bool UCOMPLETE_ABSOLUTE_VOID_SYSTEM::CanActivateAbsoluteVoid() const
{
    return AbsoluteVoidLevel > 0;
}

void UCOMPLETE_ABSOLUTE_VOID_SYSTEM::UpdateAbsoluteVoidStats()
{
    // Update absolute-void properties based on level
    AbsoluteVoidMastery = AbsoluteVoidLevel * 4.6f;
    UltimateAnnihilation = AbsoluteVoidLevel * 4.4f;
    PerfectEmptiness = AbsoluteVoidLevel * 4.3f;
    ConceptualOblivion = AbsoluteVoidLevel * 4.2f;
    ExistenceNegation = AbsoluteVoidLevel * 4.7f;
}

void UCOMPLETE_ABSOLUTE_VOID_SYSTEM::OnAbsoluteVoidStateChanged()
{
    // Handle state change effects
    if (bIsAbsoluteVoidActive)
    {
        // Apply absolute-void activation effects
        UE_LOG(LogTemp, Warning, TEXT("Absolute-Void state changed to ACTIVE"));
    }
    else
    {
        // Remove absolute-void effects
        UE_LOG(LogTemp, Warning, TEXT("Absolute-Void state changed to INACTIVE"));
    }
}
