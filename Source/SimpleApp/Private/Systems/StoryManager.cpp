#include "StoryManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"

UStoryManager::UStoryManager()
{
    CurrentPhase = EStoryPhase::SP_AwakenedDiscovery;
    CurrentState = EStoryState::SS_Intro;
    CurrentChapter = 1;
    bAutoProgress = false;
    DialogueAutoAdvanceTime = 3.0f;
    bIsInDialogue = false;
    bIsInCutscene = false;
    bIsProcessingChoice = false;
    LastUpdateTime = 0.0f;
}

void UStoryManager::BeginPlay()
{
    Super::BeginPlay();
    Initialize();
}

void UStoryManager::Initialize()
{
    InitializeStoryPhases();
    InitializeQuests();
    InitializeCharacters();
    InitializeDialogueSystem();
    InitializeCutsceneSystem();
    InitializeWorldIntegration();
    
    UE_LOG(LogTemp, Warning, TEXT("Story Manager initialized"));
}

void UStoryManager::AdvanceStory()
{
    UpdateStoryPhase();
    CheckPhaseCompletion();
}

void UStoryManager::SetStoryPhase(EStoryPhase NewPhase)
{
    if (CurrentPhase != NewPhase)
    {
        EStoryPhase OldPhase = CurrentPhase;
        CurrentPhase = NewPhase;
        
        TriggerPhaseTransition(NewPhase);
        OnStoryPhaseChanged.Broadcast(OldPhase, NewPhase);
        
        UE_LOG(LogTemp, Warning, TEXT("Story phase changed to: %d"), (int32)NewPhase);
    }
}

void UStoryManager::StartQuest(FString QuestID)
{
    CurrentQuest = QuestID;
    QuestProgress.Add(QuestID, 0);
    
    OnQuestStarted.Broadcast(QuestID);
    UE_LOG(LogTemp, Warning, TEXT("Quest started: %s"), *QuestID);
}

void UStoryManager::CompleteQuest(FString QuestID)
{
    QuestProgress.Add(QuestID, 100);
    
    OnQuestCompleted.Broadcast(QuestID);
    UE_LOG(LogTemp, Warning, TEXT("Quest completed: %s"), *QuestID);
}

void UStoryManager::InteractWithCharacter(FString CharacterName)
{
    OnCharacterInteraction.Broadcast(CharacterName);
    UpdateCharacterRelationship(CharacterName, 0.1f);
    
    UE_LOG(LogTemp, Warning, TEXT("Interacting with character: %s"), *CharacterName);
}

void UStoryManager::StartDialogue(FString CharacterName, FString DialogueID)
{
    CurrentDialogueCharacter = CharacterName;
    CurrentDialogueID = DialogueID;
    bIsInDialogue = true;
    
    OnDialogueStarted.Broadcast(CharacterName, DialogueID);
    UE_LOG(LogTemp, Warning, TEXT("Dialogue started: %s - %s"), *CharacterName, *DialogueID);
}

void UStoryManager::ProcessWorldEvent(FWorldEventData EventData)
{
    // Process world events that affect story
    if (EventData.EventName == TEXT("GateOutbreak"))
    {
        AdvanceStory();
    }
    
    UpdateWorldBasedOnStory();
}

void UStoryManager::InitializeStoryPhases()
{
    // Initialize story nodes for each phase
    FStoryNode AwakenedNode;
    AwakenedNode.NodeID = TEXT("AwakenedDiscovery");
    AwakenedNode.NodeTitle = TEXT("Awakened Hunter");
    AwakenedNode.Phase = EStoryPhase::SP_AwakenedDiscovery;
    AwakenedNode.bIsCritical = true;
    StoryNodes.Add(AwakenedNode);
    
    UE_LOG(LogTemp, Warning, TEXT("Story phases initialized"));
}

void UStoryManager::InitializeQuests()
{
    // Initialize main story quests
    StartQuest(TEXT("MainQuest_Chapter1"));
    
    UE_LOG(LogTemp, Warning, TEXT("Quest system initialized"));
}

void UStoryManager::InitializeCharacters()
{
    // Initialize main characters
    FCharacterRelationship ChaHaeIn;
    ChaHaeIn.CharacterName = TEXT("ChaHaeIn");
    ChaHaeIn.AffinityLevel = 0.0f;
    ChaHaeIn.bIsRomanceOption = true;
    CharacterRelationships.Add(TEXT("ChaHaeIn"), ChaHaeIn);
    
    UE_LOG(LogTemp, Warning, TEXT("Characters initialized"));
}

void UStoryManager::InitializeDialogueSystem()
{
    // Initialize dialogue data
    UE_LOG(LogTemp, Warning, TEXT("Dialogue system initialized"));
}

void UStoryManager::InitializeCutsceneSystem()
{
    // Initialize cutscene data
    UE_LOG(LogTemp, Warning, TEXT("Cutscene system initialized"));
}

void UStoryManager::InitializeWorldIntegration()
{
    // Initialize world-story integration
    UE_LOG(LogTemp, Warning, TEXT("World integration initialized"));
}
