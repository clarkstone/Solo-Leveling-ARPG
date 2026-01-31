#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "StoryManager.generated.h"

UENUM(BlueprintType)
enum class EStoryPhase : uint8
{
    SP_AwakenedDiscovery,
    SP_DoubleAwakening,
    SP_ShadowMonarchJourney,
    SP_WorldThreat,
    SP_FinalConfrontation
};

UENUM(BlueprintType)
enum class EStoryState : uint8
{
    SS_Intro,
    SS_Active,
    SS_Cutscene,
    SS_Dialogue,
    SS_Quest,
    SS_Combat
};

USTRUCT(BlueprintType)
struct FStoryNode
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString NodeID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString NodeTitle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString NodeDescription;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EStoryPhase Phase;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> Choices;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> Consequences;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsCritical;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bHasCutscene;
};

USTRUCT(BlueprintType)
struct FCharacterRelationship
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString CharacterName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AffinityLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> UnlockedDialogues;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsRomanceOption;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsRival;
};

USTRUCT(BlueprintType)
struct FWorldState
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString StateName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString StateDescription;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsPermanent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> AffectedSystems;
};

UCLASS()
class SIMPLEAPP_API UStoryManager : public UActorComponent
{
    GENERATED_BODY()

public:
    UStoryManager();

    // Story State Management
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Story")
    EStoryPhase CurrentPhase;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Story")
    EStoryState CurrentState;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Story")
    int32 CurrentChapter;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Story")
    FString CurrentQuest;

    // Story Progress
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Story")
    TArray<FStoryNode> CompletedNodes;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Story")
    TMap<FString, FWorldState> WorldStates;

    // Character Relationships
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Story")
    TMap<FString, FCharacterRelationship> CharacterRelationships;

    // Story Configuration
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Story")
    bool bAutoProgress;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Story")
    float DialogueAutoAdvanceTime;

    // Override UActorComponent functions
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Initialization
    UFUNCTION(BlueprintCallable, Category = "Story")
    void Initialize();

    // Story Progression
    UFUNCTION(BlueprintCallable, Category = "Story")
    void AdvanceStory();

    UFUNCTION(BlueprintCallable, Category = "Story")
    void SetStoryPhase(EStoryPhase NewPhase);

    UFUNCTION(BlueprintCallable, Category = "Story")
    void CompleteStoryNode(FString NodeID);

    UFUNCTION(BlueprintCallable, Category = "Story")
    bool IsStoryNodeCompleted(FString NodeID);

    // Quest System
    UFUNCTION(BlueprintCallable, Category = "Story")
    void StartQuest(FString QuestID);

    UFUNCTION(BlueprintCallable, Category = "Story")
    void CompleteQuest(FString QuestID);

    UFUNCTION(BlueprintCallable, Category = "Story")
    void UpdateQuestProgress(FString QuestID, float Progress);

    UFUNCTION(BlueprintCallable, Category = "Story")
    bool IsQuestCompleted(FString QuestID);

    // Character Interaction
    UFUNCTION(BlueprintCallable, Category = "Story")
    void InteractWithCharacter(FString CharacterName);

    UFUNCTION(BlueprintCallable, Category = "Story")
    void UpdateCharacterRelationship(FString CharacterName, float AffinityChange);

    UFUNCTION(BlueprintCallable, Category = "Story")
    float GetCharacterAffinity(FString CharacterName);

    UFUNCTION(BlueprintCallable, Category = "Story")
    void UnlockDialogue(FString CharacterName, FString DialogueID);

    // Dialogue System
    UFUNCTION(BlueprintCallable, Category = "Story")
    void StartDialogue(FString CharacterName, FString DialogueID);

    UFUNCTION(BlueprintCallable, Category = "Story")
    void ProcessDialogueChoice(FString ChoiceID);

    UFUNCTION(BlueprintCallable, Category = "Story")
    void EndDialogue();

    // Cutscene System
    UFUNCTION(BlueprintCallable, Category = "Story")
    void PlayCutscene(FString CutsceneID);

    UFUNCTION(BlueprintCallable, Category = "Story")
    void SkipCutscene();

    UFUNCTION(BlueprintCallable, Category = "Story")
    bool IsCutscenePlaying();

    // World Events
    UFUNCTION(BlueprintCallable, Category = "Story")
    void ProcessWorldEvent(FWorldEventData EventData);

    UFUNCTION(BlueprintCallable, Category = "Story")
    void UpdateWorldBasedOnStory();

    // Moral Choice System
    UFUNCTION(BlueprintCallable, Category = "Story")
    void ProcessMoralChoice(FString ChoiceID, FString Consequence);

    UFUNCTION(BlueprintCallable, Category = "Story")
    void UpdateMoralAlignment(FString AlignmentChange);

    // Story Events
    UPROPERTY(BlueprintAssignable, Category = "Story Events")
    FOnStoryPhaseChanged OnStoryPhaseChanged;

    UPROPERTY(BlueprintAssignable, Category = "Story Events")
    FOnStoryNodeCompleted OnStoryNodeCompleted;

    UPROPERTY(BlueprintAssignable, Category = "Story Events")
    FOnQuestStarted OnQuestStarted;

    UPROPERTY(BlueprintAssignable, Category = "Story Events")
    FOnQuestCompleted OnQuestCompleted;

    UPROPERTY(BlueprintAssignable, Category = "Story Events")
    FOnCharacterInteraction OnCharacterInteraction;

    UPROPERTY(BlueprintAssignable, Category = "Story Events")
    FOnDialogueStarted OnDialogueStarted;

    UPROPERTY(BlueprintAssignable, Category = "Story Events")
    FOnDialogueEnded OnDialogueEnded;

    UPROPERTY(BlueprintAssignable, Category = "Story Events")
    FOnCutsceneStarted OnCutsceneStarted;

    UPROPERTY(BlueprintAssignable, Category = "Story Events")
    FOnCutsceneEnded OnCutsceneEnded;

protected:
    // Story Phase Management
    void InitializeStoryPhases();
    void UpdateStoryPhase();
    void CheckPhaseCompletion();

    // Quest Management
    void InitializeQuests();
    void UpdateQuestStatus();
    void CheckQuestCompletion();

    // Character Management
    void InitializeCharacters();
    void UpdateCharacterStates();
    void ProcessCharacterAI();

    // Dialogue Management
    void InitializeDialogueSystem();
    void UpdateDialogueState();
    void ProcessDialogueConsequences();

    // Cutscene Management
    void InitializeCutsceneSystem();
    void UpdateCutsceneState();
    void ProcessCutsceneConsequences();

    // World Integration
    void InitializeWorldIntegration();
    void UpdateWorldStoryElements();
    void ProcessStoryWorldChanges();

private:
    // Internal State
    bool bIsInDialogue;
    bool bIsInCutscene;
    bool bIsProcessingChoice;
    float LastUpdateTime;

    // Story Data
    TArray<FStoryNode> StoryNodes;
    TMap<FString, FStoryNode> CurrentStoryNodes;
    TMap<FString, int32> QuestProgress;

    // Character Data
    TMap<FString, class ACharacter*> StoryCharacters;
    TMap<FString, TArray<FString>> CharacterDialogues;

    // Dialogue Data
    FString CurrentDialogueCharacter;
    FString CurrentDialogueID;
    TArray<FString> CurrentDialogueChoices;

    // Cutscene Data
    FString CurrentCutsceneID;
    bool bCanSkipCutscene;

    // Helper Functions
    void LoadStoryData();
    void SaveStoryData();
    void ProcessStoryConsequences(FStoryNode& Node);
    void UpdateWorldBasedOnPhase();
    void TriggerPhaseTransition(EStoryPhase NewPhase);
};
