#include "P06_TRNS_PHASE6.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP06_TRNS_PHASE6::UP06_TRNS_PHASE6()
{
    PrimaryComponentTick.bCanEverTick = false;
    MetaPhase6Level = 0;
    MaxMetaPhase6Level = 100;
    bIsMetaPhase6Active = false;
    MetaPhase6PowerCost = 35.0f;
    MetaPhase6Threshold = 35.0f;
    
    // Initialize meta phase6 properties
    MetaPhase6Dominion = 0.0f;
    Phase6UltimateRecursion = 0.0f;
    MetaPhase6InfiniteConsciousness = 0.0f;
    ConceptualPhase6Evolution = 0.0f;
    Phase6UltimateAuthority = 0.0f;
}

void UP06_TRNS_PHASE6::BeginPlay()
{
    Super::BeginPlay();
    UpdateMetaPhase6Stats();
}

void UP06_TRNS_PHASE6::ActivateMetaPhase6()
{
    if (!bIsMetaPhase6Active && CanActivateMetaPhase6())
    {
        bIsMetaPhase6Active = true;
        OnMetaPhase6Activated.Broadcast(MetaPhase6Level);
        OnMetaPhase6StateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Meta Phase6 System Activated at Level: %d"), MetaPhase6Level);
    }
}

void UP06_TRNS_PHASE6::DeactivateMetaPhase6()
{
    if (bIsMetaPhase6Active)
    {
        bIsMetaPhase6Active = false;
        OnMetaPhase6Deactivated.Broadcast(MetaPhase6Level);
        OnMetaPhase6StateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Meta Phase6 System Deactivated."));
    }
}

void UP06_TRNS_PHASE6::SetMetaPhase6Level(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxMetaPhase6Level)
    {
        int32 OldLevel = MetaPhase6Level;
        MetaPhase6Level = NewLevel;
        UpdateMetaPhase6Stats();
        OnMetaPhase6LevelChanged.Broadcast(OldLevel, MetaPhase6Level);
        UE_LOG(LogTemp, Warning, TEXT("Meta Phase6 Level set to: %d"), MetaPhase6Level);
        
        if (MetaPhase6Level >= MaxMetaPhase6Level)
        {
            OnMetaPhase6MaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Meta Phase6 Max Level Reached!"));
        }
    }
}

void UP06_TRNS_PHASE6::UseMetaPhase6Power()
{
    if (bIsMetaPhase6Active && MetaPhase6Level > 0)
    {
        OnMetaPhase6PowerUsed.Broadcast(MetaPhase6PowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Meta Phase6 Power Used: %.2f"), MetaPhase6PowerCost);
    }
    else
    {
        OnMetaPhase6PowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Meta Phase6 Power Use Failed: System not active or insufficient level."));
    }
}

void UP06_TRNS_PHASE6::PerformMetaPhase6Ability()
{
    if (bIsMetaPhase6Active && MetaPhase6Level >= MetaPhase6Threshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Meta Phase6 Ability at Level %d!"), MetaPhase6Level);
        OnMetaPhase6AbilityPerformed.Broadcast(MetaPhase6Level);
        UseMetaPhase6Power();
        
        // Perform meta phase6 ability based on level
        switch (MetaPhase6Level / 20)
        {
            case 0:
                ExerciseMetaPhase6Dominion();
                break;
            case 1:
                TranscendPhase6UltimateRecursion();
                break;
            case 2:
                AccessMetaPhase6InfiniteConsciousness();
                break;
            case 3:
                EvolveConceptuallyPhase6();
                break;
            case 4:
            case 5:
                WieldPhase6UltimateAuthority();
                break;
            default:
                WieldPhase6UltimateAuthority();
                break;
        }
    }
    }
    else if (MetaPhase6Level < MetaPhase6Threshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Meta Phase6 Level too low to perform ability. Required: %.0f, Current: %d"), MetaPhase6Threshold, MetaPhase6Level);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Meta Phase6 is not active, cannot perform ability."));
    }
}

bool UP06_TRNS_PHASE6::IsMetaPhase6Active() const
{
    return bIsMetaPhase6Active;
}

int32 UP06_TRNS_PHASE6::GetMetaPhase6Level() const
{
    return MetaPhase6Level;
}

float UP06_TRNS_PHASE6::GetMetaPhase6PowerCost() const
{
    return MetaPhase6PowerCost;
}

void UP06_TRNS_PHASE6::ExerciseMetaPhase6Dominion()
{
    if (bIsMetaPhase6Active)
    {
        float DominionPower = MetaPhase6Dominion * (MetaPhase6Level / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Exercising Meta Phase6 Dominion with power: %.2f"), DominionPower);
        // Apply meta phase6 dominion effects
    }
}

void UP06_TRNS_PHASE6::TranscendPhase6UltimateRecursion()
{
    if (bIsMetaPhase6Active)
    {
        float RecursionPower = Phase6UltimateRecursion * (MetaPhase6Level / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Transcending Phase6 Ultimate Recursion with power: %.2f"), RecursionPower);
        // Apply meta phase6 ultimate recursion effects
    }
}

void UP06_TRNS_PHASE6::AccessMetaPhase6InfiniteConsciousness()
{
    if (bIsMetaPhase6Active)
    {
        float ConsciousnessPower = MetaPhase6InfiniteConsciousness * (MetaPhase6Level / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Accessing Meta Phase6 Infinite Consciousness with power: %.2f"), ConsciousnessPower);
        // Apply meta phase6 infinite consciousness effects
    }
}

void UP06_TRNS_PHASE6::EvolveConceptuallyPhase6()
{
    if (bIsMetaPhase6Active)
    {
        float EvolutionPower = ConceptualPhase6Evolution * (MetaPhase6Level / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Evolving Conceptually Phase6 with power: %.2f"), EvolutionPower);
        // Apply conceptual phase6 evolution effects
    }
}

void UP06_TRNS_PHASE6::WieldPhase6UltimateAuthority()
{
    if (bIsMetaPhase6Active)
    {
        float AuthorityPower = Phase6UltimateAuthority * (MetaPhase6Level / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Wielding Phase6 Ultimate Authority with power: %.2f"), AuthorityPower);
        // Apply phase6 ultimate authority effects
    }
}

bool UP06_TRNS_PHASE6::CanActivateMetaPhase6() const
{
    return MetaPhase6Level > 0;
}

void UP06_TRNS_PHASE6::UpdateMetaPhase6Stats()
{
    // Update meta phase6 properties based on level
    MetaPhase6Dominion = MetaPhase6Level * 4.5f;
    Phase6UltimateRecursion = MetaPhase6Level * 4.3f;
    MetaPhase6InfiniteConsciousness = MetaPhase6Level * 4.1f;
    ConceptualPhase6Evolution = MetaPhase6Level * 4.2f;
    Phase6UltimateAuthority = MetaPhase6Level * 4.7f;
}

void UP06_TRNS_PHASE6::OnMetaPhase6StateChanged()
{
    // Handle state change effects
    if (bIsMetaPhase6Active)
    {
        // Apply meta phase6 activation effects
        UE_LOG(LogTemp, Warning, TEXT("Meta Phase6 state changed to ACTIVE"));
    }
    else
    {
        // Remove meta phase6 effects
        UE_LOG(LogTemp, Warning, TEXT("Meta Phase6 state changed to INACTIVE"));
    }
}
