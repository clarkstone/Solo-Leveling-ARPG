#include "COMPLETE_ETERNAL_COSMIC_VOID_SYSTEM.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCOMPLETE_ETERNAL_COSMIC_VOID_SYSTEM::UCOMPLETE_ETERNAL_COSMIC_VOID_SYSTEM()
{
    PrimaryComponentTick.bCanEverTick = false;
    EternalCosmicVoidLevel = 0;
    MaxEternalCosmicVoidLevel = 100;
    bIsEternalCosmicVoidActive = false;
    EternalCosmicVoidPowerCost = 55.0f;
    EternalCosmicVoidThreshold = 100.0f;
    
    // Initialize eternal-cosmic-void properties
    EternalCosmicVoidMastery = 0.0f;
    FinalAbsoluteVoidAnnihilation = 0.0f;
    PerfectEternalCosmicNullEmptiness = 0.0f;
    ConceptualEternalCosmicOblivion = 0.0f;
    ExistenceEternalCosmicNegation = 0.0f;
}

void UCOMPLETE_ETERNAL_COSMIC_VOID_SYSTEM::BeginPlay()
{
    Super::BeginPlay();
    UpdateEternalCosmicVoidStats();
}

void UCOMPLETE_ETERNAL_COSMIC_VOID_SYSTEM::ActivateEternalCosmicVoid()
{
    if (!bIsEternalCosmicVoidActive && CanActivateEternalCosmicVoid())
    {
        bIsEternalCosmicVoidActive = true;
        OnEternalCosmicVoidActivated.Broadcast(EternalCosmicVoidLevel);
        OnEternalCosmicVoidStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Eternal-Cosmic-Void System Activated at Level: %d"), EternalCosmicVoidLevel);
    }
}

void UCOMPLETE_ETERNAL_COSMIC_VOID_SYSTEM::DeactivateEternalCosmicVoid()
{
    if (bIsEternalCosmicVoidActive)
    {
        bIsEternalCosmicVoidActive = false;
        OnEternalCosmicVoidDeactivated.Broadcast(EternalCosmicVoidLevel);
        OnEternalCosmicVoidStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Eternal-Cosmic-Void System Deactivated."));
    }
}

void UCOMPLETE_ETERNAL_COSMIC_VOID_SYSTEM::SetEternalCosmicVoidLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxEternalCosmicVoidLevel)
    {
        int32 OldLevel = EternalCosmicVoidLevel;
        EternalCosmicVoidLevel = NewLevel;
        UpdateEternalCosmicVoidStats();
        OnEternalCosmicVoidLevelChanged.Broadcast(OldLevel, EternalCosmicVoidLevel);
        UE_LOG(LogTemp, Warning, TEXT("Eternal-Cosmic-Void Level set to: %d"), EternalCosmicVoidLevel);
        
        if (EternalCosmicVoidLevel >= MaxEternalCosmicVoidLevel)
        {
            OnEternalCosmicVoidMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Eternal-Cosmic-Void Max Level Reached!"));
        }
    }
}

void UCOMPLETE_ETERNAL_COSMIC_VOID_SYSTEM::UseEternalCosmicVoidPower()
{
    if (bIsEternalCosmicVoidActive && EternalCosmicVoidLevel > 0)
    {
        OnEternalCosmicVoidPowerUsed.Broadcast(EternalCosmicVoidPowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Eternal-Cosmic-Void Power Used: %.2f"), EternalCosmicVoidPowerCost);
    }
    else
    {
        OnEternalCosmicVoidPowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Eternal-Cosmic-Void Power Use Failed: System not active or insufficient level."));
    }
}

void UCOMPLETE_ETERNAL_COSMIC_VOID_SYSTEM::PerformEternalCosmicVoidAbility()
{
    if (bIsEternalCosmicVoidActive && EternalCosmicVoidLevel >= EternalCosmicVoidThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Eternal-Cosmic-Void Ability at Level %d!"), EternalCosmicVoidLevel);
        OnEternalCosmicVoidAbilityPerformed.Broadcast(EternalCosmicVoidLevel);
        UseEternalCosmicVoidPower();
        
        // Perform eternal-cosmic-void ability based on level
        switch (EternalCosmicVoidLevel / 20)
        {
            case 0:
                MasterEternalCosmicVoid();
                break;
            case 1:
                AnnihilateEternalCosmicUltimately();
                break;
            case 2:
                AchievePerfectEternalCosmicNullEmptiness();
                break;
            case 3:
                InduceConceptualEternalCosmicOblivion();
                break;
            case 4:
            case 5:
                NegateExistenceEternalCosmic();
                break;
            default:
                NegateExistenceEternalCosmic();
                break;
        }
    }
    }
    else if (EternalCosmicVoidLevel < EternalCosmicVoidThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Eternal-Cosmic-Void Level too low to perform ability. Required: %.0f, Current: %d"), EternalCosmicVoidThreshold, EternalCosmicVoidLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Eternal-Cosmic-Void is not active, cannot perform ability."));
    }
}

bool UCOMPLETE_ETERNAL_COSMIC_VOID_SYSTEM::IsEternalCosmicVoidActive() const
{
    return bIsEternalCosmicVoidActive;
}

int32 UCOMPLETE_ETERNAL_COSMIC_VOID_SYSTEM::GetEternalCosmicVoidLevel() const
{
    return EternalCosmicVoidLevel;
}

float UCOMPLETE_ETERNAL_COSMIC_VOID_SYSTEM::GetEternalCosmicVoidPowerCost() const
{
    return EternalCosmicVoidPowerCost;
}

void UCOMPLETE_ETERNAL_COSMIC_VOID_SYSTEM::MasterEternalCosmicVoid()
{
    if (bIsEternalCosmicVoidActive)
    {
        float VoidMastery = EternalCosmicVoidMastery * (EternalCosmicVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Mastering Eternal-Cosmic-Void with power: %.2f"), VoidMastery);
        // Apply eternal-cosmic-void mastery effects
    }
}

void UCOMPLETE_ETERNAL_COSMIC_VOID_SYSTEM::AnnihilateEternalCosmicUltimately()
{
    if (bIsEternalCosmicVoidActive)
    {
        float AnnihilationPower = FinalAbsoluteVoidAnnihilation * (EternalCosmicVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Annihilating Eternal-Cosmic Ultimately with power: %.2f"), AnnihilationPower);
        // Apply eternal-cosmic ultimate annihilation effects
    }
}

void UCOMPLETE_ETERNAL_COSMIC_VOID_SYSTEM::AchievePerfectEternalCosmicNullEmptiness()
{
    if (bIsEternalCosmicVoidActive)
    {
        float EmptinessPower = PerfectEternalCosmicNullEmptiness * (EternalCosmicVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Achieving Perfect Eternal-Cosmic Null Emptiness with power: %.2f"), EmptinessPower);
        // Apply perfect eternal-cosmic null emptiness effects
    }
}

void UCOMPLETE_ETERNAL_COSMIC_VOID_SYSTEM::InduceConceptualEternalCosmicOblivion()
{
    if (bIsEternalCosmicVoidActive)
    {
        float OblivionPower = ConceptualEternalCosmicOblivion * (EternalCosmicVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Inducing Conceptual Eternal-Cosmic Oblivion with power: %.2f"), OblivionPower);
        // Apply conceptual eternal-cosmic oblivion effects
    }
}

void UCOMPLETE_ETERNAL_COSMIC_VOID_SYSTEM::NegateExistenceEternalCosmic()
{
    if (bIsEternalCosmicVoidActive)
    {
        float NegationPower = ExistenceEternalCosmicNegation * (EternalCosmicVoidLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Negating Existence Eternal-Cosmic with power: %.2f"), NegationPower);
        // Apply existence eternal-cosmic negation effects
    }
}

bool UCOMPLETE_ETERNAL_COSMIC_VOID_SYSTEM::CanActivateEternalCosmicVoid() const
{
    return EternalCosmicVoidLevel > 0;
}

void UCOMPLETE_ETERNAL_COSMIC_VOID_SYSTEM::UpdateEternalCosmicVoidStats()
{
    // Update eternal-cosmic-void properties based on level
    EternalCosmicVoidMastery = EternalCosmicVoidLevel * 21.8f;
    FinalAbsoluteVoidAnnihilation = EternalCosmicVoidLevel * 21.6f;
    PerfectEternalCosmicNullEmptiness = EternalCosmicVoidLevel * 21.5f;
    ConceptualEternalCosmicOblivion = EternalCosmicVoidLevel * 21.4f;
    ExistenceEternalCosmicNegation = EternalCosmicVoidLevel * 22.2f;
}

void UCOMPLETE_ETERNAL_COSMIC_VOID_SYSTEM::OnEternalCosmicVoidStateChanged()
{
    // Handle state change effects
    if (bIsEternalCosmicVoidActive)
    {
        // Apply eternal-cosmic-void activation effects
        UE_LOG(LogTemp, Warning, TEXT("Eternal-Cosmic-Void state changed to ACTIVE"));
    }
    else
    {
        // Remove eternal-cosmic-void effects
        UE_LOG(LogTemp, Warning, TEXT("Eternal-Cosmic-Void state changed to INACTIVE"));
    }
}
