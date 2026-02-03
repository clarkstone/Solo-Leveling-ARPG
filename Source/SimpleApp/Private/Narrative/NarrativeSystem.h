#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "NarrativeSystem.generated.h"

UENUM(BlueprintType)
enum class EDialogueType : uint8
{
    DT_Simple = 0,        // Basic text dialogue
    DT_Choice,           // Dialogue with player choices
    DT_Branching,        // Complex branching dialogue
    DT_Quest,            // Quest-related dialogue
    DT_Lore,             // Lore and exposition
    DT_Reaction,         // NPC reaction to player actions
    DT_Custom
};

UENUM(BlueprintType)
enum class EQuestStatus : uint8
{
    QS_NotStarted = 0,    // Quest not yet discovered
    QS_Discovered,        // Quest discovered but not accepted
    QS_Active,           // Quest currently in progress
    QS_Completed,        // Quest objectives completed
    QS_TurnedIn,         // Quest rewards claimed
    QS_Failed,           // Quest failed
    QS_Abandoned         // Quest abandoned by player
};

UENUM(BlueprintType)
enum class ELoreType : uint8
{
    LT_Character = 0,      // Character background stories
    LT_Location,          // Location history and secrets
    LT_Item,              // Item lore and legends
    LT_Event,             // Historical events
    LT_Faction,           // Faction information
    LT_World,             // World-building lore
    LT_Custom
};

USTRUCT(BlueprintType)
struct FDialogueOption
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Option")
    FString OptionText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Option")
    int32 OptionID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Option")
    FString NextDialogueID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Option")
    bool bRequiresCondition;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Option")
    FString ConditionScript;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Option")
    TArray<FString> RequiredItems;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Option")
    int32 RequiredLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Option")
    bool bIsHidden;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Option")
    FString ConsequenceScript;
};

USTRUCT(BlueprintType)
struct FDialogueNode
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Node")
    FString NodeID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Node")
    FString SpeakerName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Node")
    FString DialogueText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Node")
    EDialogueType DialogueType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Node")
    TArray<FDialogueOption> Options;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Node")
    FString AudioPath;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Node")
    FString AnimationName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Node")
    float DisplayDuration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Node")
    bool bIsImportant;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Node")
    TArray<FString> TriggeredEvents;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Node")
    FString QuestUpdate;
};

USTRUCT(BlueprintType)
struct FQuestObjective
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Objective")
    FString ObjectiveID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Objective")
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Objective")
    FString ObjectiveType; // "Kill", "Collect", "Explore", "Talk", "Deliver"

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Objective")
    FString TargetID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Objective")
    int32 RequiredCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Objective")
    int32 CurrentCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Objective")
    bool bIsCompleted;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Objective")
    bool bIsOptional;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Objective")
    FString LocationHint;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Objective")
    TArray<FString> RequiredItems;
};

USTRUCT(BlueprintType)
struct FQuestReward
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Reward")
    FString RewardType; // "XP", "Gold", "Item", "Skill", "Reputation"

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Reward")
    FString RewardID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Reward")
    int32 Quantity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Reward")
    int32 Quality;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Reward")
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Reward")
    bool bIsGuaranteed;
};

USTRUCT(BlueprintType)
struct FQuest
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    FString QuestID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    FString QuestName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    EQuestStatus Status;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    TArray<FQuestObjective> Objectives;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    TArray<FQuestReward> Rewards;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    FString QuestGiverID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    int32 RequiredLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    TArray<FString> PrerequisiteQuests;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    bool bIsMainQuest;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    bool bIsRepeatable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    int32 TimeLimit;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    FString StartDialogueID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    FString CompleteDialogueID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    UTexture2D* QuestIcon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    TArray<FString> Tags;
};

USTRUCT(BlueprintType)
struct FLoreEntry
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lore Entry")
    FString LoreID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lore Entry")
    FString Title;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lore Entry")
    FString Content;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lore Entry")
    ELoreType LoreType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lore Entry")
    FString SourceID; // NPC, Item, Location, etc.

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lore Entry")
    bool bIsDiscovered;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lore Entry")
    FString DiscoveryCondition;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lore Entry")
    TArray<FString> RelatedLore;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lore Entry")
    UTexture2D* LoreIcon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lore Entry")
    FString AudioNarration;
};

UCLASS(BlueprintType, Blueprintable)
class SIMPLEAPP_API UNarrativeSystem : public UActorComponent
{
    GENERATED_BODY()

public:
    UNarrativeSystem();

    // Narrative System Events
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogueStarted, const FDialogueNode&, DialogueNode);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogueOptionSelected, const FDialogueOption&, SelectedOption);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogueEnded, const FString&, NodeID);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestStarted, const FQuest&, Quest);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestCompleted, const FQuest&, Quest);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestUpdated, const FQuest&, Quest);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoreDiscovered, const FLoreEntry&, LoreEntry);

    UPROPERTY(BlueprintAssignable, Category = "Narrative Events")
    FOnDialogueStarted OnDialogueStarted;

    UPROPERTY(BlueprintAssignable, Category = "Narrative Events")
    FOnDialogueOptionSelected OnDialogueOptionSelected;

    UPROPERTY(BlueprintAssignable, Category = "Narrative Events")
    FOnDialogueEnded OnDialogueEnded;

    UPROPERTY(BlueprintAssignable, Category = "Narrative Events")
    FOnQuestStarted OnQuestStarted;

    UPROPERTY(BlueprintAssignable, Category = "Narrative Events")
    FOnQuestCompleted OnQuestCompleted;

    UPROPERTY(BlueprintAssignable, Category = "Narrative Events")
    FOnQuestUpdated OnQuestUpdated;

    UPROPERTY(BlueprintAssignable, Category = "Narrative Events")
    FOnLoreDiscovered OnLoreDiscovered;

    // Override UActorComponent functions
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Dialogue System
    UFUNCTION(BlueprintCallable, Category = "Narrative System")
    void InitializeNarrativeSystem();

    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    bool StartDialogue(const FString& DialogueID, const FString& SpeakerID);

    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    bool SelectDialogueOption(int32 OptionID);

    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    void EndDialogue();

    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    FDialogueNode GetCurrentDialogue() const;

    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    bool IsDialogueActive() const;

    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    TArray<FDialogueOption> GetAvailableOptions() const;

    UFUNCTION(BlueprintCallable, Category = "Dialogue")
    bool HasDialogueCondition(const FString& Condition) const;

    // Quest System
    UFUNCTION(BlueprintCallable, Category = "Quest")
    TArray<FQuest> GetAvailableQuests() const;

    UFUNCTION(BlueprintCallable, Category = "Quest")
    TArray<FQuest> GetActiveQuests() const;

    UFUNCTION(BlueprintCallable, Category = "Quest")
    TArray<FQuest> GetCompletedQuests() const;

    UFUNCTION(BlueprintCallable, Category = "Quest")
    bool StartQuest(const FString& QuestID);

    UFUNCTION(BlueprintCallable, Category = "Quest")
    bool CompleteQuest(const FString& QuestID);

    UFUNCTION(BlueprintCallable, Category = "Quest")
    bool UpdateQuestObjective(const FString& QuestID, const FString& ObjectiveID, int32 Progress);

    UFUNCTION(BlueprintCallable, Category = "Quest")
    FQuest GetQuest(const FString& QuestID) const;

    UFUNCTION(BlueprintCallable, Category = "Quest")
    EQuestStatus GetQuestStatus(const FString& QuestID) const;

    UFUNCTION(BlueprintCallable, Category = "Quest")
    bool CanStartQuest(const FString& QuestID) const;

    UFUNCTION(BlueprintCallable, Category = "Quest")
    void AbandonQuest(const FString& QuestID);

    // Lore System
    UFUNCTION(BlueprintCallable, Category = "Lore")
    TArray<FLoreEntry> GetDiscoveredLore() const;

    UFUNCTION(BlueprintCallable, Category = "Lore")
    TArray<FLoreEntry> GetLoreByType(ELoreType LoreType) const;

    UFUNCTION(BlueprintCallable, Category = "Lore")
    bool DiscoverLore(const FString& LoreID);

    UFUNCTION(BlueprintCallable, Category = "Lore")
    FLoreEntry GetLoreEntry(const FString& LoreID) const;

    UFUNCTION(BlueprintCallable, Category = "Lore")
    bool IsLoreDiscovered(const FString& LoreID) const;

    UFUNCTION(BlueprintCallable, Category = "Lore")
    TArray<FString> GetRelatedLore(const FString& LoreID) const;

    // Story Progression
    UFUNCTION(BlueprintCallable, Category = "Story")
    void UpdateStoryProgress(const FString& StoryEvent);

    UFUNCTION(BlueprintCallable, Category = "Story")
    FString GetCurrentStoryChapter() const;

    UFUNCTION(BlueprintCallable, Category = "Story")
    TArray<FString> GetStoryFlags() const;

    UFUNCTION(BlueprintCallable, Category = "Story")
    bool HasStoryFlag(const FString& Flag) const;

    UFUNCTION(BlueprintCallable, Category = "Story")
    void SetStoryFlag(const FString& Flag, bool bValue);

    // NPC Relationships
    UFUNCTION(BlueprintCallable, Category = "NPC")
    void UpdateNPCRelationship(const FString& NPCID, int32 RelationshipChange);

    UFUNCTION(BlueprintCallable, Category = "NPC")
    int32 GetNPCRelationship(const FString& NPCID) const;

    UFUNCTION(BlueprintCallable, Category = "NPC")
    TArray<FString> GetNPCsWithRelationship(int32 MinRelationship) const;

    // Save/Load
    UFUNCTION(BlueprintCallable, Category = "Narrative System")
    void SaveNarrativeState();

    UFUNCTION(BlueprintCallable, Category = "Narrative System")
    void LoadNarrativeState();

    UFUNCTION(BlueprintCallable, Category = "Narrative System")
    void ResetNarrativeState();

protected:
    // Internal Functions
    void InitializeDialogueDatabase();
    void InitializeQuestDatabase();
    void InitializeLoreDatabase();
    void ProcessDialogueChoice(const FDialogueOption& Option);
    void CheckQuestCompletion();
    void UpdateQuestProgress();
    void TriggerStoryEvents();
    void UpdateNPCAttitudes();

private:
    // Internal State
    TArray<FDialogueNode> DialogueDatabase;
    TArray<FQuest> QuestDatabase;
    TArray<FLoreEntry> LoreDatabase;
    
    // Current State
    FDialogueNode CurrentDialogue;
    bool bDialogueActive;
    FString CurrentSpeakerID;
    
    // Quest State
    TMap<FString, FQuest> ActiveQuests;
    TMap<FString, FQuest> CompletedQuests;
    
    // Story State
    TArray<FString> StoryFlags;
    FString CurrentChapter;
    TMap<FString, int32> NPCRelationships;
    
    // Lore State
    TSet<FString> DiscoveredLore;
    
    // Helper Functions
    FDialogueNode CreateDialogueNode(const FString& ID, const FString& Speaker, const FString& Text);
    FQuest CreateQuest(const FString& ID, const FString& Name, const FString& Description);
    FLoreEntry CreateLoreEntry(const FString& ID, const FString& Title, const FString& Content, ELoreType Type);
    void NotifyDialogueStarted(const FDialogueNode& DialogueNode);
    void NotifyDialogueOptionSelected(const FDialogueOption& SelectedOption);
    void NotifyDialogueEnded(const FString& NodeID);
    void NotifyQuestStarted(const FQuest& Quest);
    void NotifyQuestCompleted(const FQuest& Quest);
    void NotifyQuestUpdated(const FQuest& Quest);
    void NotifyLoreDiscovered(const FLoreEntry& LoreEntry);
    bool ValidateDialogueCondition(const FString& Condition) const;
    bool ValidateQuestPrerequisites(const FString& QuestID) const;
    void GrantQuestRewards(const FQuest& Quest);
    void ProcessConsequences(const FString& ConsequenceScript);
    void UpdateWorldState(const FString& Event);
    void SaveDialogueState();
    void SaveQuestState();
    void SaveLoreState();
    void LoadDialogueState();
    void LoadQuestState();
    void LoadLoreState();
};
