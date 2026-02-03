#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "NarrativeSystem.h"
#include "EvolvingDialogueSystem.generated.h"

UENUM(BlueprintType)
enum class EDialogueTrigger : uint8
{
    DT_LevelUp = 0,           // Player leveled up
    DT_QuestComplete,        // Quest completed
    DT_SkillLearned,         // New skill acquired
    DT_ItemAcquired,         // Important item obtained
    DT_LocationDiscovered,   // New area discovered
    DT_RelationshipChange,   // NPC relationship changed
    DT_TimePassed,           // Time progression
    DT_WorldEvent,           // Dynamic world event
    DT_PlayerAction,         // Specific player action
    DT_Custom
};

UENUM(BlueprintType)
enum class EDialogueContext : uint8
{
    DC_General = 0,          // General conversation
    DC_QuestRelated,        // Quest-specific dialogue
    DC_SkillRelated,         // Skill-related discussion
    DC_ItemRelated,          // Item-related conversation
    DC_LocationRelated,      // Location-specific dialogue
    DC_RelationshipRelated,  // Relationship-based dialogue
    DC_WorldEventRelated,    // Event-specific dialogue
    DC_PlayerStatusRelated,  // Player status-based dialogue
    DC_Custom
};

UENUM(BlueprintType)
enum class EDialoguePriority : uint8
{
    DP_Low = 0,              // Low priority dialogue
    DP_Normal,               // Normal priority
    DP_High,                 // High priority
    DP_Critical,             // Critical/must-show dialogue
    DP_Story                 // Story-critical dialogue
};

USTRUCT(BlueprintType)
struct FDialogueCondition
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Condition")
    EDialogueTrigger TriggerType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Condition")
    FString Parameter; // Level, quest ID, skill ID, etc.

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Condition")
    FString Operator; // ">", "<", "==", "!=", "contains", etc.

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Condition")
    FString Value; // Required value

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Condition")
    bool bIsMet;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Condition")
    FString Description;
};

USTRUCT(BlueprintType)
struct FDialogueVariant
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Variant")
    FString VariantID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Variant")
    FString DialogueText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Variant")
    TArray<FDialogueCondition> Conditions;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Variant")
    EDialoguePriority Priority;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Variant")
    bool bIsAvailable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Variant")
    FString AudioPath;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Variant")
    FString AnimationName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Variant")
    TArray<FString> Consequences;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue Variant")
    float Weight; // For random selection among valid variants
};

USTRUCT(BlueprintType)
struct FEvolvingDialogueNode
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Evolving Dialogue Node")
    FString NodeID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Evolving Dialogue Node")
    FString SpeakerID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Evolving Dialogue Node")
    EDialogueContext Context;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Evolving Dialogue Node")
    TArray<FDialogueVariant> Variants;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Evolving Dialogue Node")
    TArray<FDialogueOption> Options;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Evolving Dialogue Node")
    bool bIsRepeatable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Evolving Dialogue Node")
    int32 MaxUses;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Evolving Dialogue Node")
    int32 CurrentUses;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Evolving Dialogue Node")
    float CooldownTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Evolving Dialogue Node")
    float LastUsedTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Evolving Dialogue Node")
    bool bIsImportant;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Evolving Dialogue Node")
    TArray<FString> Tags;
};

USTRUCT(BlueprintType)
struct FPlayerDialogueState
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Dialogue State")
    int32 PlayerLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Dialogue State")
    FString PlayerRank;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Dialogue State")
    TArray<FString> CompletedQuests;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Dialogue State")
    TArray<FString> KnownSkills;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Dialogue State")
    TArray<FString> ImportantItems;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Dialogue State")
    TArray<FString> DiscoveredLocations;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Dialogue State")
    TMap<FString, int32> NPCRelationships;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Dialogue State")
    TArray<FString> WorldEvents;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Dialogue State")
    float PlayTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Dialogue State")
    int32 EnemiesDefeated;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Dialogue State")
    TMap<FString, FString> PlayerChoices;
};

UCLASS(BlueprintType, Blueprintable)
class SIMPLEAPP_API UEvolvingDialogueSystem : public UActorComponent
{
    GENERATED_BODY()

public:
    UEvolvingDialogueSystem();

    // Evolving Dialogue Events
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEvolvingDialogueTriggered, const FEvolvingDialogueNode&, DialogueNode);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDialogueVariantSelected, const FString&, NodeID, const FDialogueVariant&, Variant);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogueConditionMet, const FDialogueCondition&, Condition);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerStateChanged, const FPlayerDialogueState&, NewState);

    UPROPERTY(BlueprintAssignable, Category = "Evolving Dialogue Events")
    FOnEvolvingDialogueTriggered OnEvolvingDialogueTriggered;

    UPROPERTY(BlueprintAssignable, Category = "Evolving Dialogue Events")
    FOnDialogueVariantSelected OnDialogueVariantSelected;

    UPROPERTY(BlueprintAssignable, Category = "Evolving Dialogue Events")
    FOnDialogueConditionMet OnDialogueConditionMet;

    UPROPERTY(BlueprintAssignable, Category = "Evolving Dialogue Events")
    FOnPlayerStateChanged OnPlayerStateChanged;

    // Override UActorComponent functions
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // System Initialization
    UFUNCTION(BlueprintCallable, Category = "Evolving Dialogue System")
    void InitializeEvolvingDialogue();

    UFUNCTION(BlueprintCallable, Category = "Evolving Dialogue System")
    void UpdatePlayerState();

    // Dialogue Management
    UFUNCTION(BlueprintCallable, Category = "Evolving Dialogue")
    bool StartEvolvingDialogue(const FString& NodeID, const FString& SpeakerID);

    UFUNCTION(BlueprintCallable, Category = "Evolving Dialogue")
    FDialogueVariant GetBestDialogueVariant(const FString& NodeID);

    UFUNCTION(BlueprintCallable, Category = "Evolving Dialogue")
    TArray<FDialogueVariant> GetAvailableVariants(const FString& NodeID);

    UFUNCTION(BlueprintCallable, Category = "Evolving Dialogue")
    bool SelectDialogueVariant(const FString& NodeID, const FString& VariantID);

    UFUNCTION(BlueprintCallable, Category = "Evolving Dialogue")
    FEvolvingDialogueNode GetDialogueNode(const FString& NodeID) const;

    UFUNCTION(BlueprintCallable, Category = "Evolving Dialogue")
    TArray<FEvolvingDialogueNode> GetDialogueNodes(const FString& SpeakerID) const;

    // Condition System
    UFUNCTION(BlueprintCallable, Category = "Evolving Dialogue")
    bool CheckDialogueConditions(const TArray<FDialogueCondition>& Conditions);

    UFUNCTION(BlueprintCallable, Category = "Evolving Dialogue")
    bool IsConditionMet(const FDialogueCondition& Condition);

    UFUNCTION(BlueprintCallable, Category = "Evolving Dialogue")
    void AddDialogueCondition(const FString& NodeID, const FString& VariantID, const FDialogueCondition& Condition);

    UFUNCTION(BlueprintCallable, Category = "Evolving Dialogue")
    void RemoveDialogueCondition(const FString& NodeID, const FString& VariantID, const FString& ConditionID);

    // Player State Tracking
    UFUNCTION(BlueprintCallable, Category = "Player State")
    FPlayerDialogueState GetPlayerState() const;

    UFUNCTION(BlueprintCallable, Category = "Player State")
    void SetPlayerLevel(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Player State")
    void SetPlayerRank(const FString& NewRank);

    UFUNCTION(BlueprintCallable, Category = "Player State")
    void AddCompletedQuest(const FString& QuestID);

    UFUNCTION(BlueprintCallable, Category = "Player State")
    void AddKnownSkill(const FString& SkillID);

    UFUNCTION(BlueprintCallable, Category = "Player State")
    void AddImportantItem(const FString& ItemID);

    UFUNCTION(BlueprintCallable, Category = "Player State")
    void AddDiscoveredLocation(const FString& LocationID);

    UFUNCTION(BlueprintCallable, Category = "Player State")
    void UpdateNPCRelationship(const FString& NPCID, int32 RelationshipValue);

    UFUNCTION(BlueprintCallable, Category = "Player State")
    void AddWorldEvent(const FString& EventID);

    UFUNCTION(BlueprintCallable, Category = "Player State")
    void SetPlayerChoice(const FString& ChoiceID, const FString& ChoiceValue);

    // Trigger System
    UFUNCTION(BlueprintCallable, Category = "Evolving Dialogue")
    void TriggerDialogueEvent(EDialogueTrigger TriggerType, const FString& Parameter = TEXT(""));

    UFUNCTION(BlueprintCallable, Category = "Evolving Dialogue")
    void OnPlayerLevelUp(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Evolving Dialogue")
    void OnQuestCompleted(const FString& QuestID);

    UFUNCTION(BlueprintCallable, Category = "Evolving Dialogue")
    void OnSkillLearned(const FString& SkillID);

    UFUNCTION(BlueprintCallable, Category = "Evolving Dialogue")
    void OnItemAcquired(const FString& ItemID);

    UFUNCTION(BlueprintCallable, Category = "Evolving Dialogue")
    void OnLocationDiscovered(const FString& LocationID);

    UFUNCTION(BlueprintCallable, Category = "Evolving Dialogue")
    void OnWorldEventTriggered(const FString& EventID);

    // Context-Aware Dialogue
    UFUNCTION(BlueprintCallable, Category = "Evolving Dialogue")
    TArray<FEvolvingDialogueNode> GetContextualDialogue(EDialogueContext Context) const;

    UFUNCTION(BlueprintCallable, Category = "Evolving Dialogue")
    TArray<FEvolvingDialogueNode> GetPriorityDialogue() const;

    UFUNCTION(BlueprintCallable, Category = "Evolving Dialogue")
    TArray<FEvolvingDialogueNode> GetAvailableDialogue() const;

    UFUNCTION(BlueprintCallable, Category = "Evolving Dialogue")
    void UpdateDialogueContext();

    // Dialogue History
    UFUNCTION(BlueprintCallable, Category = "Evolving Dialogue")
    TArray<FString> GetDialogueHistory() const;

    UFUNCTION(BlueprintCallable, Category = "Evolving Dialogue")
    void AddToHistory(const FString& DialogueEntry);

    UFUNCTION(BlueprintCallable, Category = "Evolving Dialogue")
    void ClearDialogueHistory();

    UFUNCTION(BlueprintCallable, Category = "Evolving Dialogue")
    bool HasDialogueBeenSaid(const FString& NodeID, const FString& VariantID) const;

    // Save/Load
    UFUNCTION(BlueprintCallable, Category = "Evolving Dialogue System")
    void SaveEvolvingDialogueState();

    UFUNCTION(BlueprintCallable, Category = "Evolving Dialogue System")
    void LoadEvolvingDialogueState();

    UFUNCTION(BlueprintCallable, Category = "Evolving Dialogue System")
    void ResetEvolvingDialogueState();

protected:
    // Internal Functions
    void InitializeDialogueDatabase();
    void InitializePlayerState();
    void ProcessDialogueTriggers();
    void UpdateDialogueAvailability();
    void CheckForNewDialogue();
    void RefreshAllDialogue();

private:
    // Internal State
    TArray<FEvolvingDialogueNode> DialogueDatabase;
    FPlayerDialogueState CurrentPlayerState;
    TArray<FString> DialogueHistory;
    
    // Dialogue State
    TMap<FString, float> DialogueCooldowns;
    TMap<FString, int32> DialogueUsageCounts;
    TSet<FString> SaidDialogueVariants;
    
    // Trigger Queue
    TArray<TPair<EDialogueTrigger, FString>> PendingTriggers;
    
    // Helper Functions
    FEvolvingDialogueNode CreateDialogueNode(const FString& ID, const FString& SpeakerID, EDialogueContext Context);
    FDialogueVariant CreateDialogueVariant(const FString& ID, const FString& Text, EDialoguePriority Priority);
    FDialogueCondition CreateDialogueCondition(EDialogueTrigger Trigger, const FString& Param, const FString& Op, const FString& Val);
    FPlayerDialogueState CreateInitialPlayerState();
    void NotifyEvolvingDialogueTriggered(const FEvolvingDialogueNode& DialogueNode);
    void NotifyDialogueVariantSelected(const FString& NodeID, const FDialogueVariant& Variant);
    void NotifyDialogueConditionMet(const FDialogueCondition& Condition);
    void NotifyPlayerStateChanged(const FPlayerDialogueState& NewState);
    bool EvaluateCondition(const FDialogueCondition& Condition);
    float CalculateVariantWeight(const FDialogueVariant& Variant);
    FDialogueVariant SelectWeightedVariant(const TArray<FDialogueVariant>& ValidVariants);
    void ProcessDialogueConsequences(const TArray<FString>& Consequences);
    void UpdateDialogueCooldown(const FString& NodeID);
    bool IsDialogueOnCooldown(const FString& NodeID);
    bool CanUseDialogueVariant(const FString& NodeID, const FDialogueVariant& Variant);
    void MarkDialogueAsSaid(const FString& NodeID, const FString& VariantID);
    void SortDialogueByPriority(TArray<FEvolvingDialogueNode>& DialogueNodes);
    void FilterDialogueByContext(TArray<FEvolvingDialogueNode>& DialogueNodes, EDialogueContext Context);
    void LogDialogueState();
    void ValidateDialogueDatabase();
};
