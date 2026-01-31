#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "NPCSystem.generated.h"

UENUM(BlueprintType)
enum class ENPCType : uint8
{
    NT_QuestGiver,
    NT_Merchant,
    NT_Trainer,
    NT_Blacksmith,
    NT_Alchemist,
    NT_Enchanter,
    NT_StoryCharacter,
    NT_GuildMaster,
    NT_Guard,
    NT_Villager
};

UENUM(BlueprintType)
enum class ENPCState : uint8
{
    NS_Idle,
    NS_Patrol,
    NS_Dialogue,
    NS_Training,
    NS_Working,
    NS_Sleeping,
    NS_Emergency
};

USTRUCT(BlueprintType)
struct FNPCDialogue
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString DialogueID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString SpeakerName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString DialogueText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> PlayerChoices;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> ChoiceConsequences;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bHasVoiceOver;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString VoiceOverPath;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DialogueDuration;
};

USTRUCT(BlueprintType)
struct FNPCSchedule
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StartTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float EndTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ENPCState ScheduledState;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector ScheduledLocation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ScheduledActivity;
};

USTRUCT(BlueprintType)
struct FNPCRelationship
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString NPCName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AffinityLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> UnlockedDialogues;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsRomanceOption;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsRival;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsFriend;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 InteractionCount;
};

UCLASS()
class SIMPLEAPP_API UNPCSystem : public UActorComponent
{
    GENERATED_BODY()

public:
    UNPCSystem();

    // NPC Configuration
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC")
    TMap<FString, class ANPC*> AllNPCs;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NPC")
    TMap<FString, FNPCRelationship> PlayerRelationships;

    // Override UActorComponent functions
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Initialization
    UFUNCTION(BlueprintCallable, Category = "NPC")
    void Initialize();

    // NPC Management
    UFUNCTION(BlueprintCallable, Category = "NPC")
    void RegisterNPC(FString NPCID, class ANPC* NPC);

    UFUNCTION(BlueprintCallable, Category = "NPC")
    void UnregisterNPC(FString NPCID);

    UFUNCTION(BlueprintCallable, Category = "NPC")
    class ANPC* GetNPC(FString NPCID);

    UFUNCTION(BlueprintCallable, Category = "NPC")
    TArray<class ANPC*> GetNPCsByType(ENPCType NPCType);

    // Dialogue System
    UFUNCTION(BlueprintCallable, Category = "NPC")
    void StartDialogue(FString NPCID, FString DialogueID);

    UFUNCTION(BlueprintCallable, Category = "NPC")
    void ProcessDialogueChoice(FString NPCID, int32 ChoiceIndex);

    UFUNCTION(BlueprintCallable, Category = "NPC")
    void EndDialogue(FString NPCID);

    UFUNCTION(BlueprintCallable, Category = "NPC")
    TArray<FNPCDialogue> GetAvailableDialogues(FString NPCID);

    // Relationship System
    UFUNCTION(BlueprintCallable, Category = "NPC")
    void UpdateRelationship(FString NPCID, float AffinityChange);

    UFUNCTION(BlueprintCallable, Category = "NPC")
    float GetRelationshipLevel(FString NPCID);

    UFUNCTION(BlueprintCallable, Category = "NPC")
    void UnlockDialogue(FString NPCID, FString DialogueID);

    UFUNCTION(BlueprintCallable, Category = "NPC")
    bool IsDialogueUnlocked(FString NPCID, FString DialogueID);

    // NPC AI
    UFUNCTION(BlueprintCallable, Category = "NPC")
    void UpdateNPCAI();

    UFUNCTION(BlueprintCallable, Category = "NPC")
    void UpdateNPCSchedules();

    UFUNCTION(BlueprintCallable, Category = "NPC")
    void UpdateNPCBehaviors();

    // NPC Events
    UFUNCTION(BlueprintCallable, Category = "NPC")
    void OnWorldEventTriggered(FWorldEventData EventData);

    UFUNCTION(BlueprintCallable, Category = "NPC")
    void OnPlayerLevelUp(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "NPC")
    void OnQuestCompleted(FString QuestID);

    UFUNCTION(BlueprintCallable, Category = "NPC")
    void OnGuildJoined(FString GuildName);

    // NPC Services
    UFUNCTION(BlueprintCallable, Category = "NPC")
    void StartMerchantTransaction(FString NPCID);

    UFUNCTION(BlueprintCallable, Category = "NPC")
    void StartTrainingSession(FString NPCID);

    UFUNCTION(BlueprintCallable, Category = "NPC")
    void StartCrafting(FString NPCID);

    UFUNCTION(BlueprintCallable, Category = "NPC")
    void StartEnchantment(FString NPCID);

    // NPC States
    UFUNCTION(BlueprintCallable, Category = "NPC")
    void SetNPCState(FString NPCID, ENPCState NewState);

    UFUNCTION(BlueprintCallable, Category = "NPC")
    ENPCState GetNPCState(FString NPCID);

    // NPC Events
    UPROPERTY(BlueprintAssignable, Category = "NPC Events")
    FOnNPCInteraction OnNPCInteraction;

    UPROPERTY(BlueprintAssignable, Category = "NPC Events")
    FOnDialogueStarted OnDialogueStarted;

    UPROPERTY(BlueprintAssignable, Category = "NPC Events")
    FOnDialogueEnded OnDialogueEnded;

    UPROPERTY(BlueprintAssignable, Category = "NPC Events")
    FOnRelationshipChanged OnRelationshipChanged;

protected:
    // Internal NPC Systems
    void InitializeNPCDatabase();
    void UpdateNPCStates();
    void ProcessNPCEvents();

    // Dialogue Management
    void LoadDialogueDatabase();
    void UpdateDialogueAvailability();
    void ProcessDialogueConsequences(FString NPCID, FString ChoiceID);

    // Relationship Management
    void InitializeRelationships();
    void UpdateRelationshipStates();
    void ProcessRelationshipEvents();

private:
    // Internal State
    float LastUpdateTime;
    bool bIsInDialogue;
    FString CurrentDialogueNPC;

    // NPC Data
    TMap<FString, TArray<FNPCDialogue>> NPCDialogues;
    TMap<FString, TArray<FNPCSchedule>> NPCSchedules;
    TMap<ENPCType, TArray<FString>> NPCsByType;

    // Helper Functions
    void LoadNPCData();
    void UpdateNPCAI();
    void ProcessNPCEvent(FString EventType, TArray<FString> Parameters);
};
