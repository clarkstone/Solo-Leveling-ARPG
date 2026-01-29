#include "P01_VOID_ABSOLUTE.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP01_VOID_ABSOLUTE::UP01_VOID_ABSOLUTE()
{
    PrimaryComponentTick.bCanEverTick = false;
    AbsoluteVoidLevel = 0;
    MaxAbsoluteVoidLevel = 100;
    bIsAbsoluteVoidActive = false;
    AbsoluteVoidPowerCost = 10.0f;
    AbsoluteVoidThreshold = 10.0f;
    
    // Initialize absolute void properties
    VoidMastery = 0.0f;
    AbsoluteAnnihilation = 0.0f;
    PerfectEmptiness = 0.0f;
    ConceptualOblivion = 0.0f;
    ExistenceNegation = 0.0f;
}

void UP01_VOID_ABSOLUTE::BeginPlay()
{
    Super::BeginPlay();
    UpdateAbsoluteVoidStats();
}

void UP01_VOID_ABSOLUTE::ActivateAbsoluteVoid()
{
    if (!bIsAbsoluteVoidActive && CanActivateAbsoluteVoid())
    {
        bIsAbsoluteVoidActive = true;
        OnAbsoluteVoidActivated.Broadcast(AbsoluteVoidLevel);
        OnAbsoluteVoidStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Absolute Void System Activated at Level: %d"), AbsoluteVoidLevel);
    }
}

void UP01_VOID_ABSOLUTE::DeactivateAbsoluteVoid()
{
    if (bIsAbsoluteVoidActive)
    {
        bIsAbsoluteVoidActive = false;
        OnAbsoluteVoidDeactivated.Broadcast(AbsoluteVoidLevel);
        OnAbsoluteVoidStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Absolute Void System Deactivated."));
    }
}

void UP01_VOID_ABSOLUTE::SetAbsoluteVoidLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxAbsoluteVoidLevel)
    {
        int32 OldLevel = AbsoluteVoidLevel;
        AbsoluteVoidLevel = NewLevel;
        UpdateAbsoluteVoidStats();
        OnAbsoluteVoidLevelChanged.Broadcast(OldLevel, AbsoluteVoidLevel);
        UE_LOG(LogTemp, Warning, TEXT("Absolute Void Level set to: %d"), AbsoluteVoidLevel);
        
        if (AbsoluteVoidLevel >= MaxAbsoluteVoidLevel)
        {
            OnAbsoluteVoidMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Absolute Void Max Level Reached!"));
        }
    }
}

void UP01_VOID_ABSOLUTE::UseAbsoluteVoidPower()
{
    if (bIsAbsoluteVoidActive && AbsoluteVoidLevel > 0)
    {
        OnAbsoluteVoidPowerUsed.Broadcast(AbsoluteVoidPowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Absolute Void Power Used: %.2f"), AbsoluteVoidPowerCost);
    }
    else
    {
        OnAbsoluteVoidPowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Absolute Void Power Use Failed: System not active or insufficient level."));
    }
}

void UP01_VOID_ABSOLUTE::PerformAbsoluteVoidAbility()
{
    if (bIsAbsoluteVoidActive && AbsoluteVoidLevel >= AbsoluteVoidThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Absolute Void Ability at Level %d!"), AbsoluteVoidLevel);
        OnAbsoluteVoidAbilityPerformed.Broadcast(AbsoluteVoidLevel);
        UseAbsoluteVoidPower();
        
        // Perform absolute void ability based on level
        switch (AbsoluteVoidLevel / 20)
        {
            case 0:
                MasterAbsoluteVoid();
                break;
            case 1:
                AnnihilateAbsolutely();
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
    }
    else if (AbsoluteVoidLevel < AbsoluteVoidThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Absolute Void Level too low to perform ability. Required: %.0f, Current: %d"), AbsoluteVoidThreshold, AbsoluteVoidLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Absolute Void is not active, cannot perform ability."));
    }
}

bool UP01_VOID_ABSOLUTE::IsAbsoluteVoidActive() const
{
    return bIsAbsoluteVoidActive;
}

int32 UP01_VOID_ABSOLUTE::GetAbsoluteVoidLevel() const
{
    return AbsoluteVoidLevel;
}

float UP01_VOID_ABSOLUTE::GetAbsoluteVoidPowerCost() const
{
    return AbsoluteVoidPowerCost;
}

void UP01_VOID_ABSOLUTE::MasterAbsoluteVoid()
{
    if (bIsAbsoluteVoidActive)
    {
        float VoidMasteryPower = VoidMastery * (AbsoluteVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Mastering Absolute Void with power: %.2f"), VoidMasteryPower);
        // Apply absolute void mastery effects
    }
}

void UP01_VOID_ABSOLUTE::AnnihilateAbsolutely()
{
    if (bIsAbsoluteVoidActive)
    {
        float AnnihilationPower = AbsoluteAnnihilation * (AbsoluteVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Annihilating Absolutely with power: %.2f"), AnnihilationPower);
        // Apply absolute annihilation effects
    }
}

void UP01_VOID_ABSOLUTE::AchievePerfectEmptiness()
{
    if (bIsAbsoluteVoidActive)
    {
        float EmptinessPower = PerfectEmptiness * (AbsoluteVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Perfect Emptiness with power: %.2f"), EmptinessPower);
        // Apply perfect emptiness effects
    }
}

void UP01_VOID_ABSOLUTE::InduceConceptualOblivion()
{
    if (bIsAbsoluteVoidActive)
    {
        float OblivionPower = ConceptualOblivion * (AbsoluteVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Inducing Conceptual Oblivion with power: %.2f"), OblivionPower);
        // Apply conceptual oblivion effects
    }
}

void UP01_VOID_ABSOLUTE::NegateExistence()
{
    if (bIsAbsoluteVoidActive)
    {
        float NegationPower = ExistenceNegation * (AbsoluteVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Negating Existence with power: %.2f"), NegationPower);
        // Apply existence negation effects
    }
}

bool UP01_VOID_ABSOLUTE::CanActivateAbsoluteVoid() const
{
    return AbsoluteVoidLevel > 0;
}

void UP01_VOID_ABSOLUTE::UpdateAbsoluteVoidStats()
{
    // Update absolute void properties based on level
    VoidMastery = AbsoluteVoidLevel * 1.4f;
    AbsoluteAnnihilation = AbsoluteVoidLevel * 1.6f;
    PerfectEmptiness = AbsoluteVoidLevel * 1.5f;
    ConceptualOblivion = AbsoluteVoidLevel * 1.3f;
    ExistenceNegation = AbsoluteVoidLevel * 1.7f;
}

void UP01_VOID_ABSOLUTE::OnAbsoluteVoidStateChanged()
{
    // Handle state change effects
    if (bIsAbsoluteVoidActive)
    {
        // Apply absolute void activation effects
        UE_LOG(LogTemp, Warning, TEXT("Absolute Void state changed to ACTIVE"));
    }
    else
    {
        // Remove absolute void effects
        UE_LOG(LogTemp, Warning, TEXT("Absolute Void state changed to INACTIVE"));
    }
}
