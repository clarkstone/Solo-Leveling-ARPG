#include "COMPLETE_META_INFINITE_TRANSCENDENCE_SYSTEM.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCOMPLETE_META_INFINITE_TRANSCENDENCE_SYSTEM::UCOMPLETE_META_INFINITE_TRANSCENDENCE_SYSTEM()
{
    PrimaryComponentTick.bCanEverTick = false;
    MetaInfiniteTranscendenceLevel = 0;
    MaxMetaInfiniteTranscendenceLevel = 100;
    bIsMetaInfiniteTranscendenceActive = false;
    MetaInfiniteTranscendencePowerCost = 20.0f;
    MetaInfiniteTranscendenceThreshold = 70.0f;
    
    // Initialize meta-infinite-transcendence properties
    MetaRealitySovereignty = 0.0f;
    TranscendenceBeyondTranscendence = 0.0f;
    InfiniteMetaAwareness = 0.0f;
    ConceptualMetamorphosis = 0.0f;
    AbsoluteMetaAuthority = 0.0f;
}

void UCOMPLETE_META_INFINITE_TRANSCENDENCE_SYSTEM::BeginPlay()
{
    Super::BeginPlay();
    UpdateMetaInfiniteTranscendenceStats();
}

void UCOMPLETE_META_INFINITE_TRANSCENDENCE_SYSTEM::ActivateMetaInfiniteTranscendence()
{
    if (!bIsMetaInfiniteTranscendenceActive && CanActivateMetaInfiniteTranscendence())
    {
        bIsMetaInfiniteTranscendenceActive = true;
        OnMetaInfiniteTranscendenceActivated.Broadcast(MetaInfiniteTranscendenceLevel);
        OnMetaInfiniteTranscendenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Meta-Infinite-Transcendence System Activated at Level: %d"), MetaInfiniteTranscendenceLevel);
    }
}

void UCOMPLETE_META_INFINITE_TRANSCENDENCE_SYSTEM::DeactivateMetaInfiniteTranscendence()
{
    if (bIsMetaInfiniteTranscendenceActive)
    {
        bIsMetaInfiniteTranscendenceActive = false;
        OnMetaInfiniteTranscendenceDeactivated.Broadcast(MetaInfiniteTranscendenceLevel);
        OnMetaInfiniteTranscendenceStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Meta-Infinite-Transcendence System Deactivated."));
    }
}

void UCOMPLETE_META_INFINITE_TRANSCENDENCE_SYSTEM::SetMetaInfiniteTranscendenceLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxMetaInfiniteTranscendenceLevel)
    {
        int32 OldLevel = MetaInfiniteTranscendenceLevel;
        MetaInfiniteTranscendenceLevel = NewLevel;
        UpdateMetaInfiniteTranscendenceStats();
        OnMetaInfiniteTranscendenceLevelChanged.Broadcast(OldLevel, MetaInfiniteTranscendenceLevel);
        UE_LOG(LogTemp, Warning, TEXT("Meta-Infinite-Transcendence Level set to: %d"), MetaInfiniteTranscendenceLevel);
        
        if (MetaInfiniteTranscendenceLevel >= MaxMetaInfiniteTranscendenceLevel)
        {
            OnMetaInfiniteTranscendenceMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Meta-Infinite-Transcendence Max Level Reached!"));
        }
    }
}

void UCOMPLETE_META_INFINITE_TRANSCENDENCE_SYSTEM::UseMetaInfiniteTranscendencePower()
{
    if (bIsMetaInfiniteTranscendenceActive && MetaInfiniteTranscendenceLevel > 0)
    {
        OnMetaInfiniteTranscendencePowerUsed.Broadcast(MetaInfiniteTranscendencePowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Meta-Infinite-Transcendence Power Used: %.2f"), MetaInfiniteTranscendencePowerCost);
    }
    else
    {
        OnMetaInfiniteTranscendencePowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Meta-Infinite-Transcendence Power Use Failed: System not active or insufficient level."));
    }
}

void UCOMPLETE_META_INFINITE_TRANSCENDENCE_SYSTEM::PerformMetaInfiniteTranscendenceAbility()
{
    if (bIsMetaInfiniteTranscendenceActive && MetaInfiniteTranscendenceLevel >= MetaInfiniteTranscendenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Meta-Infinite-Transcendence Ability at Level %d!"), MetaInfiniteTranscendenceLevel);
        OnMetaInfiniteTranscendenceAbilityPerformed.Broadcast(MetaInfiniteTranscendenceLevel);
        UseMetaInfiniteTranscendencePower();
        
        // Perform meta-infinite-transcendence ability based on level
        switch (MetaInfiniteTranscendenceLevel / 20)
        {
            case 0:
                ExerciseMetaRealitySovereignty();
                break;
            case 1:
                TranscendBeyondTranscendence();
                break;
            case 2:
                AccessInfiniteMetaAwareness();
                break;
            case 3:
                UndergoConceptualMetamorphosis();
                break;
            case 4:
            case 5:
                WieldAbsoluteMetaAuthority();
                break;
            default:
                WieldAbsoluteMetaAuthority();
                break;
        }
    }
    else if (MetaInfiniteTranscendenceLevel < MetaInfiniteTranscendenceThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Meta-Infinite-Transcendence Level too low to perform ability. Required: %.0f, Current: %d"), MetaInfiniteTranscendenceThreshold, MetaInfiniteTranscendenceLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Meta-Infinite-Transcendence is not active, cannot perform ability."));
    }
}

bool UCOMPLETE_META_INFINITE_TRANSCENDENCE_SYSTEM::IsMetaInfiniteTranscendenceActive() const
{
    return bIsMetaInfiniteTranscendenceActive;
}

int32 UCOMPLETE_META_INFINITE_TRANSCENDENCE_SYSTEM::GetMetaInfiniteTranscendenceLevel() const
{
    return MetaInfiniteTranscendenceLevel;
}

float UCOMPLETE_META_INFINITE_TRANSCENDENCE_SYSTEM::GetMetaInfiniteTranscendencePowerCost() const
{
    return MetaInfiniteTranscendencePowerCost;
}

void UCOMPLETE_META_INFINITE_TRANSCENDENCE_SYSTEM::ExerciseMetaRealitySovereignty()
{
    if (bIsMetaInfiniteTranscendenceActive)
    {
        float SovereigntyPower = MetaRealitySovereignty * (MetaInfiniteTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Exercising Meta-Reality Sovereignty with power: %.2f"), SovereigntyPower);
        // Apply meta-reality sovereignty effects
    }
}

void UCOMPLETE_META_INFINITE_TRANSCENDENCE_SYSTEM::TranscendBeyondTranscendence()
{
    if (bIsMetaInfiniteTranscendenceActive)
    {
        float TranscendencePower = TranscendenceBeyondTranscendence * (MetaInfiniteTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Transcending Beyond Transcendence with power: %.2f"), TranscendencePower);
        // Apply transcendence beyond transcendence effects
    }
}

void UCOMPLETE_META_INFINITE_TRANSCENDENCE_SYSTEM::AccessInfiniteMetaAwareness()
{
    if (bIsMetaInfiniteTranscendenceActive)
    {
        float AwarenessPower = InfiniteMetaAwareness * (MetaInfiniteTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Accessing Infinite Meta-Awareness with power: %.2f"), AwarenessPower);
        // Apply infinite meta-awareness effects
    }
}

void UCOMPLETE_META_INFINITE_TRANSCENDENCE_SYSTEM::UndergoConceptualMetamorphosis()
{
    if (bIsMetaInfiniteTranscendenceActive)
    {
        float MetamorphosisPower = ConceptualMetamorphosis * (MetaInfiniteTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Undergoing Conceptual Metamorphosis with power: %.2f"), MetamorphosisPower);
        // Apply conceptual metamorphosis effects
    }
}

void UCOMPLETE_META_INFINITE_TRANSCENDENCE_SYSTEM::WieldAbsoluteMetaAuthority()
{
    if (bIsMetaInfiniteTranscendenceActive)
    {
        float AuthorityPower = AbsoluteMetaAuthority * (MetaInfiniteTranscendenceLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Wielding Absolute Meta-Authority with power: %.2f"), AuthorityPower);
        // Apply absolute meta-authority effects
    }
}

bool UCOMPLETE_META_INFINITE_TRANSCENDENCE_SYSTEM::CanActivateMetaInfiniteTranscendence() const
{
    return MetaInfiniteTranscendenceLevel > 0;
}

void UCOMPLETE_META_INFINITE_TRANSCENDENCE_SYSTEM::UpdateMetaInfiniteTranscendenceStats()
{
    // Update meta-infinite-transcendence properties based on level
    MetaRealitySovereignty = MetaInfiniteTranscendenceLevel * 4.0f;
    TranscendenceBeyondTranscendence = MetaInfiniteTranscendenceLevel * 3.8f;
    InfiniteMetaAwareness = MetaInfiniteTranscendenceLevel * 3.6f;
    ConceptualMetamorphosis = MetaInfiniteTranscendenceLevel * 3.7f;
    AbsoluteMetaAuthority = MetaInfiniteTranscendenceLevel * 4.2f;
}

void UCOMPLETE_META_INFINITE_TRANSCENDENCE_SYSTEM::OnMetaInfiniteTranscendenceStateChanged()
{
    // Handle state change effects
    if (bIsMetaInfiniteTranscendenceActive)
    {
        // Apply meta-infinite-transcendence activation effects
        UE_LOG(LogTemp, Warning, TEXT("Meta-Infinite-Transcendence state changed to ACTIVE"));
    }
    else
    {
        // Remove meta-infinite-transcendence effects
        UE_LOG(LogTemp, Warning, TEXT("Meta-Infinite-Transcendence state changed to INACTIVE"));
    }
}
