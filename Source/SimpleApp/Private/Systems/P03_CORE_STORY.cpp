#include "P03_CORE_STORY.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UP03_CORE_STORY::UP03_CORE_STORY()
{
    PrimaryComponentTick.bCanEverTick = false;
    StoryLevel = 0;
    MaxStoryLevel = 100;
    bIsStoryActive = false;
    StoryPowerCost = 10.0f;
    StoryThreshold = 10.0f;
    
    // Initialize story properties
    StoryProgression = 0.0f;
    NarrativeControl = 0.0f;
    QuestGeneration = 0.0f;
    DialogueSystem = 0.0f;
}

void UP03_CORE_STORY::BeginPlay()
{
    Super::BeginPlay();
    UpdateStoryStats();
}

void UP03_CORE_STORY::ActivateStory()
{
    if (!bIsStoryActive && CanActivateStory())
    {
        bIsStoryActive = true;
        OnStoryActivated.Broadcast(StoryLevel);
        OnStoryStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Story System Activated at Level: %d"), StoryLevel);
    }
}

void UP03_CORE_STORY::DeactivateStory()
{
    if (bIsStoryActive)
    {
        bIsStoryActive = false;
        OnStoryDeactivated.Broadcast(StoryLevel);
        OnStoryStateChanged();
        UE_LOG(LogTemp, Warning, TEXT("Story System Deactivated."));
    }
}

void UP03_CORE_STORY::SetStoryLevel(int32 NewLevel)
{
    if (NewLevel >= 0 && NewLevel <= MaxStoryLevel)
    {
        int32 OldLevel = StoryLevel;
        StoryLevel = NewLevel;
        UpdateStoryStats();
        OnStoryLevelChanged.Broadcast(OldLevel, StoryLevel);
        UE_LOG(LogTemp, Warning, TEXT("Story Level set to: %d"), StoryLevel);
        
        if (StoryLevel >= MaxStoryLevel)
        {
            OnStoryMaxLevelReached.Broadcast();
            UE_LOG(LogTemp, Warning, TEXT("Story Max Level Reached!"));
        }
    }
}

void UP03_CORE_STORY::UseStoryPower()
{
    if (bIsStoryActive && StoryLevel > 0)
    {
        OnStoryPowerUsed.Broadcast(StoryPowerCost);
        UE_LOG(LogTemp, Warning, TEXT("Story Power Used: %.2f"), StoryPowerCost);
    }
    else
    {
        OnStoryPowerFailed.Broadcast();
        UE_LOG(LogTemp, Warning, TEXT("Story Power Use Failed: System not active or insufficient level."));
    }
}

void UP03_CORE_STORY::PerformStoryAbility()
{
    if (bIsStoryActive && StoryLevel >= StoryThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Performing Story Ability at Level %d!"), StoryLevel);
        OnStoryAbilityPerformed.Broadcast(StoryLevel);
        UseStoryPower();
        
        // Perform story ability based on level
        switch (StoryLevel / 20)
        {
            case 0:
                ProgressStory();
                break;
            case 1:
                ControlNarrative();
                break;
            case 2:
                GenerateQuests();
                break;
            case 3:
                AccessDialogueSystem();
                break;
            default:
                AccessDialogueSystem();
                break;
        }
    }
    }
    else if (StoryLevel < StoryThreshold)
    {
        UE_LOG(LogTemp, Warning, TEXT("Story Level too low to perform ability. Required: %.0f, Current: %d"), StoryThreshold, StoryLevel);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Story is not active, cannot perform ability."));
    }
}

bool UP03_CORE_STORY::IsStoryActive() const
{
    return bIsStoryActive;
}

int32 UP03_CORE_STORY::GetStoryLevel() const
{
    return StoryLevel;
}

float UP03_CORE_STORY::GetStoryPowerCost() const
{
    return StoryPowerCost;
}

void UP03_CORE_STORY::ProgressStory()
{
    if (bIsStoryActive)
    {
        float ProgressionPower = StoryProgression * (StoryLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Progressing Story with power: %.2f"), ProgressionPower);
        // Apply story progression effects
    }
}

void UP03_CORE_STORY::ControlNarrative()
{
    if (bIsStoryActive)
    {
        float NarrativePower = NarrativeControl * (StoryLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Controlling Narrative with power: %.2f"), NarrativePower);
        // Apply narrative control effects
    }
}

void UP03_CORE_STORY::GenerateQuests()
{
    if (bIsStoryActive)
    {
        float QuestPower = QuestGeneration * (StoryLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Generating Quests with power: %.2f"), QuestPower);
        // Apply quest generation effects
    }
}

void UP03_CORE_STORY::AccessDialogueSystem()
{
    if (bIsStoryActive)
    {
        float DialoguePower = DialogueSystem * (StoryLevel / 100.0f);
        UE_LOG(LogTemp, Warning, TEXT("Accessing Dialogue System with power: %.2f"), DialoguePower);
        // Apply dialogue system effects
    }
}

bool UP03_CORE_STORY::CanActivateStory() const
{
    return StoryLevel > 0;
}

void UP03_CORE_STORY::UpdateStoryStats()
{
    // Update story properties based on level
    StoryProgression = StoryLevel * 1.2f;
    NarrativeControl = StoryLevel * 1.5f;
    QuestGeneration = StoryLevel * 1.3f;
    DialogueSystem = StoryLevel * 1.1f;
}

void UP03_CORE_STORY::OnStoryStateChanged()
{
    // Handle state change effects
    if (bIsStoryActive)
    {
        // Apply story activation effects
        UE_LOG(LogTemp, Warning, TEXT("Story state changed to ACTIVE"));
    }
    else
    {
        // Remove story effects
        UE_LOG(LogTemp, Warning, TEXT("Story state changed to INACTIVE"));
    }
}
