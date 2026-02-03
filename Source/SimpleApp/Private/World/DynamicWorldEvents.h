#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "OpenWorldSystem.h"
#include "DynamicWorldEvents.generated.h"

UENUM(BlueprintType)
enum class EEventType : uint8
{
    ET_Battle = 0,
    ET_Merchant,
    ET_Quest,
    ET_Exploration,
    ET_Story,
    ET_Weather,
    ET_Monster,
    ET_Natural,
    ET_Magical,
    ET_Social,
    ET_Custom
};

UENUM(BlueprintType)
enum class EEventFrequency : uint8
{
    EF_Common = 0,
    EF_Uncommon,
    EF_Rare,
    EP_Epic,
    EF_Legendary,
    EF_Unique
};

UENUM(BlueprintType)
enum class EEventTrigger : uint8
{
    ET_Time = 0,
    ET_Location,
    ET_PlayerAction,
    ET_Weather,
    ET_QuestCompletion,
    ET_Random,
    ET_Scripted,
    ET_Custom
};

USTRUCT(BlueprintType)
struct FEventParticipant
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event Participant")
    FString ParticipantID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event Participant")
    FString ParticipantName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event Participant")
    FString ParticipantType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event Participant")
    FVector SpawnLocation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event Participant")
    bool bIsHostile;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event Participant")
    int32 Level;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event Participant")
    TArray<FString> Equipment;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event Participant")
    TArray<FString> Abilities;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event Participant")
    FString DialogueTree;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event Participant")
    bool bIsEssential;
};

USTRUCT(BlueprintType)
struct FEventReward
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event Reward")
    FString RewardType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event Reward")
    FString RewardID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event Reward")
    int32 Quantity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event Reward")
    int32 Quality;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event Reward")
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event Reward")
    bool bIsGuaranteed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event Reward")
    float DropChance;
};

USTRUCT(BlueprintType)
struct FDynamicWorldEvent
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic World Event")
    FString EventID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic World Event")
    FString EventName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic World Event")
    EEventType EventType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic World Event")
    EEventFrequency Frequency;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic World Event")
    EEventTrigger TriggerType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic World Event")
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic World Event")
    FVector EventLocation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic World Event")
    EBiomeType Biome;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic World Event")
    float Duration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic World Event")
    bool bIsActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic World Event")
    bool bIsRepeatable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic World Event")
    int32 MaxParticipants;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic World Event")
    TArray<FEventParticipant> Participants;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic World Event")
    TArray<FEventReward> Rewards;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic World Event")
    TArray<FString> RequiredItems;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic World Event")
    TArray<FString> RequiredSkills;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic World Event")
    int32 MinimumLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic World Event")
    int32 RecommendedLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic World Event")
    FString SuccessCondition;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic World Event")
    FString FailureCondition;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic World Event")
    TArray<FString> DialogueOptions;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic World Event")
    FString NextEventID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic World Event")
    bool bIsChainEvent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic World Event")
    float TriggerChance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic World Event")
    float CooldownTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic World Event")
    float LastTriggeredTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic World Event")
    UTexture2D* EventIcon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic World Event")
    bool bHasTimeLimit;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dynamic World Event")
    float TimeLimit;
};

USTRUCT(BlueprintType)
struct FEventChain
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event Chain")
    FString ChainID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event Chain")
    FString ChainName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event Chain")
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event Chain")
    TArray<FString> EventSequence;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event Chain")
    int32 CurrentEventIndex;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event Chain")
    bool bIsActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event Chain")
    bool bIsCompleted;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event Chain")
    TArray<FEventReward> ChainRewards;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Event Chain")
    FString UnlockRequirement;
};

UCLASS(BlueprintType, Blueprintable)
class SIMPLEAPP_API UDynamicWorldEvents : public UActorComponent
{
    GENERATED_BODY()

public:
    UDynamicWorldEvents();

    // Dynamic World Events
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEventStarted, const FDynamicWorldEvent&, WorldEvent);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEventCompleted, const FDynamicWorldEvent&, WorldEvent);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEventFailed, const FDynamicWorldEvent&, WorldEvent);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEventParticipantJoined, const FString&, EventID, const FEventParticipant&, Participant);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEventParticipantLeft, const FString&, EventID, const FEventParticipant&, Participant);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEventChainStarted, const FEventChain&, EventChain);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEventChainCompleted, const FEventChain&, EventChain);

    UPROPERTY(BlueprintAssignable, Category = "Dynamic World Events")
    FOnEventStarted OnEventStarted;

    UPROPERTY(BlueprintAssignable, Category = "Dynamic World Events")
    FOnEventCompleted OnEventCompleted;

    UPROPERTY(BlueprintAssignable, Category = "Dynamic World Events")
    FOnEventFailed OnEventFailed;

    UPROPERTY(BlueprintAssignable, Category = "Dynamic World Events")
    FOnEventParticipantJoined OnEventParticipantJoined;

    UPROPERTY(BlueprintAssignable, Category = "Dynamic World Events")
    FOnEventParticipantLeft OnEventParticipantLeft;

    UPROPERTY(BlueprintAssignable, Category = "Dynamic World Events")
    FOnEventChainStarted OnEventChainStarted;

    UPROPERTY(BlueprintAssignable, Category = "Dynamic World Events")
    FOnEventChainCompleted OnEventChainCompleted;

    // Override UActorComponent functions
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Event Management
    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    void InitializeDynamicEvents();

    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    TArray<FDynamicWorldEvent> GetAvailableEvents() const;

    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    TArray<FDynamicWorldEvent> GetActiveEvents() const;

    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    FDynamicWorldEvent GetEvent(const FString& EventID) const;

    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    bool TriggerEvent(const FString& EventID);

    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    bool CompleteEvent(const FString& EventID);

    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    bool FailEvent(const FString& EventID);

    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    void CancelEvent(const FString& EventID);

    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    bool IsEventActive(const FString& EventID) const;

    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    bool CanTriggerEvent(const FString& EventID) const;

    // Event Creation
    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    bool CreateDynamicEvent(const FDynamicWorldEvent& EventTemplate);

    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    void CreateRandomEvent(EEventType EventType, EBiomeType Biome, FVector Location);

    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    void CreateScheduledEvent(const FString& EventID, float TriggerTime);

    // Event Participants
    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    bool AddParticipantToEvent(const FString& EventID, const FEventParticipant& Participant);

    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    bool RemoveParticipantFromEvent(const FString& EventID, const FString& ParticipantID);

    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    TArray<FEventParticipant> GetEventParticipants(const FString& EventID) const;

    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    FEventParticipant GetEventParticipant(const FString& EventID, const FString& ParticipantID) const;

    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    bool IsParticipantInEvent(const FString& EventID, const FString& ParticipantID) const;

    // Event Chains
    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    TArray<FEventChain> GetAvailableEventChains() const;

    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    bool StartEventChain(const FString& ChainID);

    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    bool CompleteEventChain(const FString& ChainID);

    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    FEventChain GetEventChain(const FString& ChainID) const;

    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    bool IsEventChainActive(const FString& ChainID) const;

    // Event Conditions
    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    bool CheckEventConditions(const FString& EventID) const;

    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    bool CheckEventSuccess(const FString& EventID) const;

    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    bool CheckEventFailure(const FString& EventID) const;

    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    void UpdateEventProgress(const FString& EventID, const FString& ProgressKey, float ProgressValue);

    // Event Rewards
    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    void GrantEventRewards(const FString& EventID);

    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    TArray<FEventReward> GetEventRewards(const FString& EventID) const;

    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    bool HasEventRewards(const FString& EventID) const;

    // Event Timing
    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    void SetEventTimer(const FString& EventID, float Duration);

    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    float GetEventTimeRemaining(const FString& EventID) const;

    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    bool IsEventTimeExpired(const FString& EventID) const;

    // Event Location
    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    TArray<FDynamicWorldEvent> GetEventsInLocation(const FVector& Location, float Radius) const;

    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    TArray<FDynamicWorldEvent> GetEventsInBiome(EBiomeType Biome) const;

    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    void MoveEvent(const FString& EventID, FVector NewLocation);

    // Event AI
    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    void UpdateEventAI(const FString& EventID);

    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    void ProcessEventAI(const FString& EventID, float DeltaTime);

    // Save/Load
    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    void SaveEventState();

    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    void LoadEventState();

    UFUNCTION(BlueprintCallable, Category = "Dynamic World Events")
    void ResetEventState();

protected:
    // Internal Functions
    void InitializeEventTemplates();
    void InitializeEventChains();
    void UpdateActiveEvents(float DeltaTime);
    void UpdateEventTimers(float DeltaTime);
    void UpdateEventAI(float DeltaTime);
    void ProcessScheduledEvents();
    void CheckForRandomEvents();
    void SpawnEventParticipants(const FString& EventID);
    void DespawnEventParticipants(const FString& EventID);
    void ProcessEventDialogue(const FString& EventID);
    void UpdateEventProgression(const FString& EventID);

private:
    // Internal State
    TArray<FDynamicWorldEvent> AvailableEvents;
    TArray<FDynamicWorldEvent> ActiveEvents;
    TArray<FEventChain> EventChains;
    TMap<FString, FDynamicWorldEvent> EventTemplates;
    TMap<FString, float> ScheduledEvents;
    TMap<FString, TMap<FString, float>> EventProgress;

    // Event Timing
    float EventUpdateTimer;
    float RandomEventTimer;
    float ScheduledEventTimer;

    // Event Statistics
    TMap<FString, int32> EventTriggerCount;
    TMap<FString, float> EventSuccessRate;
    TMap<FString, float> EventParticipationRate;

    // Helper Functions
    FDynamicWorldEvent CreateEventTemplate(const FString& ID, EEventType Type, EEventFrequency Frequency);
    FEventParticipant CreateParticipant(const FString& ID, const FString& Name, const FString& Type);
    FEventReward CreateReward(const FString& Type, const FString& ID, int32 Quantity, int32 Quality);
    FEventChain CreateEventChain(const FString& ID, const FString& Name, const TArray<FString>& Events);
    void NotifyEventStarted(const FDynamicWorldEvent& WorldEvent);
    void NotifyEventCompleted(const FDynamicWorldEvent& WorldEvent);
    void NotifyEventFailed(const FDynamicWorldEvent& WorldEvent);
    void NotifyEventParticipantJoined(const FString& EventID, const FEventParticipant& Participant);
    void NotifyEventParticipantLeft(const FString& EventID, const FEventParticipant& Participant);
    void NotifyEventChainStarted(const FEventChain& EventChain);
    void NotifyEventChainCompleted(const FEventChain& EventChain);
    bool ValidateEvent(const FDynamicWorldEvent& Event) const;
    bool ValidateParticipant(const FEventParticipant& Participant) const;
    void CalculateEventDifficulty(FDynamicWorldEvent& Event);
    void BalanceEventRewards(FDynamicWorldEvent& Event);
    void UpdateEventStatistics(const FString& EventID, bool bSuccess);
    void GenerateRandomEvent();
    void ProcessEventChain(const FString& ChainID);
    void AdvanceEventChain(const FString& ChainID);
    bool CanSpawnParticipant(const FEventParticipant& Participant) const;
    void SpawnParticipant(const FEventParticipant& Participant);
    void DespawnParticipant(const FEventParticipant& Participant);
    void UpdateParticipantAI(const FEventParticipant& Participant, float DeltaTime);
    void ProcessParticipantDialogue(const FEventParticipant& Participant);
    void HandleParticipantDeath(const FEventParticipant& Participant);
    void HandleParticipantVictory(const FEventParticipant& Participant);
    void UpdateEventLocation(const FString& EventID);
    void UpdateEventEnvironment(const FString& EventID);
    void ApplyEventEffects(const FString& EventID);
    void RemoveEventEffects(const FString& EventID);
};
