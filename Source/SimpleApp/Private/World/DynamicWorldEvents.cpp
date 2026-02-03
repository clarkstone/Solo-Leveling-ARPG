#include "DynamicWorldEvents.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DataTable.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundBase.h"
#include "Net/UnrealNetwork.h"

UDynamicWorldEvents::UDynamicWorldEvents()
{
    PrimaryComponentTick.bCanEverTick = true;
    SetIsReplicatedByDefault(true);
    
    EventUpdateTimer = 0.0f;
    RandomEventTimer = 0.0f;
    ScheduledEventTimer = 0.0f;
}

void UDynamicWorldEvents::BeginPlay()
{
    Super::BeginPlay();
    InitializeDynamicEvents();
}

void UDynamicWorldEvents::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    UpdateActiveEvents(DeltaTime);
    UpdateEventTimers(DeltaTime);
    UpdateEventAI(DeltaTime);
    ProcessScheduledEvents();
    CheckForRandomEvents();
}

void UDynamicWorldEvents::InitializeDynamicEvents()
{
    UE_LOG(LogTemp, Warning, TEXT("Dynamic World Events System initialized"));
    
    InitializeEventTemplates();
    InitializeEventChains();
    LoadEventState();
    
    UE_LOG(LogTemp, Warning, TEXT("Dynamic World Events System ready"));
}

TArray<FDynamicWorldEvent> UDynamicWorldEvents::GetAvailableEvents() const
{
    return AvailableEvents;
}

TArray<FDynamicWorldEvent> UDynamicWorldEvents::GetActiveEvents() const
{
    return ActiveEvents;
}

FDynamicWorldEvent UDynamicWorldEvents::GetEvent(const FString& EventID) const
{
    for (const FDynamicWorldEvent& Event : AvailableEvents)
    {
        if (Event.EventID == EventID)
        {
            return Event;
        }
    }
    
    for (const FDynamicWorldEvent& Event : ActiveEvents)
    {
        if (Event.EventID == EventID)
        {
            return Event;
        }
    }
    
    FDynamicWorldEvent EmptyEvent;
    return EmptyEvent;
}

bool UDynamicWorldEvents::TriggerEvent(const FString& EventID)
{
    if (!CanTriggerEvent(EventID))
    {
        UE_LOG(LogTemp, Warning, TEXT("Cannot trigger event: %s"), *EventID);
        return false;
    }
    
    for (const FDynamicWorldEvent& EventTemplate : AvailableEvents)
    {
        if (EventTemplate.EventID == EventID)
        {
            FDynamicWorldEvent NewEvent = EventTemplate;
            NewEvent.bIsActive = true;
            NewEvent.LastTriggeredTime = GetWorld()->GetTimeSeconds();
            
            ActiveEvents.Add(NewEvent);
            SpawnEventParticipants(EventID);
            ApplyEventEffects(EventID);
            
            NotifyEventStarted(NewEvent);
            UpdateEventStatistics(EventID, false);
            
            UE_LOG(LogTemp, Warning, TEXT("Event triggered: %s"), *EventID);
            return true;
        }
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Event template not found: %s"), *EventID);
    return false;
}

void UDynamicWorldEvents::InitializeEventTemplates()
{
    AvailableEvents.Empty();
    EventTemplates.Empty();
    
    // Create battle events
    FDynamicWorldEvent BanditAttack = CreateEventTemplate(TEXT("BANDIT_ATTACK"), EEventType::ET_Battle, EEventFrequency::EF_Common);
    BanditAttack.Description = TEXT("Bandits are attacking the area!");
    BanditAttack.Duration = 300.0f;
    BanditAttack.MaxParticipants = 5;
    BanditAttack.MinimumLevel = 1;
    BanditAttack.RecommendedLevel = 3;
    BanditAttack.TriggerChance = 0.15f;
    BanditAttack.CooldownTime = 600.0f;
    
    AvailableEvents.Add(BanditAttack);
    EventTemplates.Add(BanditAttack.EventID, BanditAttack);
}

void UDynamicWorldEvents::InitializeEventChains()
{
    EventChains.Empty();
    
    TArray<FString> BanditChainEvents;
    BanditChainEvents.Add(TEXT("BANDIT_ATTACK"));
    
    FEventChain BanditChain = CreateEventChain(TEXT("BANDIT_CHAIN"), TEXT("Bandit Menace"), BanditChainEvents);
    EventChains.Add(BanditChain);
}

FDynamicWorldEvent UDynamicWorldEvents::CreateEventTemplate(const FString& ID, EEventType Type, EEventFrequency Frequency)
{
    FDynamicWorldEvent Event;
    Event.EventID = ID;
    Event.EventName = ID;
    Event.EventType = Type;
    Event.Frequency = Frequency;
    Event.Duration = 300.0f;
    Event.bIsActive = false;
    Event.bIsRepeatable = true;
    Event.MaxParticipants = 5;
    Event.TriggerChance = 0.1f;
    Event.CooldownTime = 600.0f;
    
    return Event;
}

FEventParticipant UDynamicWorldEvents::CreateParticipant(const FString& ID, const FString& Name, const FString& Type)
{
    FEventParticipant Participant;
    Participant.ParticipantID = ID;
    Participant.ParticipantName = Name;
    Participant.ParticipantType = Type;
    Participant.bIsHostile = Type == TEXT("Enemy");
    Participant.Level = 1;
    
    return Participant;
}

FEventChain UDynamicWorldEvents::CreateEventChain(const FString& ID, const FString& Name, const TArray<FString>& Events)
{
    FEventChain Chain;
    Chain.ChainID = ID;
    Chain.ChainName = Name;
    Chain.EventSequence = Events;
    Chain.CurrentEventIndex = 0;
    Chain.bIsActive = false;
    Chain.bIsCompleted = false;
    
    return Chain;
}

void UDynamicWorldEvents::NotifyEventStarted(const FDynamicWorldEvent& WorldEvent)
{
    OnEventStarted.Broadcast(WorldEvent);
}

void UDynamicWorldEvents::UpdateActiveEvents(float DeltaTime)
{
    for (int32 i = ActiveEvents.Num() - 1; i >= 0; i--)
    {
        FDynamicWorldEvent& Event = ActiveEvents[i];
        Event.Duration -= DeltaTime;
        
        if (Event.bHasTimeLimit && Event.Duration <= 0.0f)
        {
            FailEvent(Event.EventID);
        }
        else if (CheckEventSuccess(Event.EventID))
        {
            CompleteEvent(Event.EventID);
        }
        else if (CheckEventFailure(Event.EventID))
        {
            FailEvent(Event.EventID);
        }
    }
}

bool UDynamicWorldEvents::CheckEventSuccess(const FString& EventID) const
{
    FDynamicWorldEvent Event = GetEvent(EventID);
    if (Event.EventID.IsEmpty())
    {
        return false;
    }
    
    if (Event.EventType == EEventType::ET_Battle)
    {
        for (const FEventParticipant& Participant : Event.Participants)
        {
            if (Participant.bIsHostile)
            {
                return false; // Still hostile participants
            }
        }
        return true;
    }
    
    return false;
}

bool UDynamicWorldEvents::CheckEventFailure(const FString& EventID) const
{
    FDynamicWorldEvent Event = GetEvent(EventID);
    if (Event.EventID.IsEmpty())
    {
        return false;
    }
    
    if (Event.bHasTimeLimit)
    {
        return GetEventTimeRemaining(EventID) <= 0.0f;
    }
    
    return false;
}

float UDynamicWorldEvents::GetEventTimeRemaining(const FString& EventID) const
{
    for (const FDynamicWorldEvent& Event : ActiveEvents)
    {
        if (Event.EventID == EventID)
        {
            return Event.Duration;
        }
    }
    
    return 0.0f;
}

void UDynamicWorldEvents::SpawnEventParticipants(const FString& EventID)
{
    FDynamicWorldEvent Event = GetEvent(EventID);
    if (Event.EventID.IsEmpty())
    {
        return;
    }
    
    for (const FEventParticipant& Participant : Event.Participants)
    {
        SpawnParticipant(Participant);
    }
}

void UDynamicWorldEvents::DespawnEventParticipants(const FString& EventID)
{
    FDynamicWorldEvent Event = GetEvent(EventID);
    if (Event.EventID.IsEmpty())
    {
        return;
    }
    
    for (const FEventParticipant& Participant : Event.Participants)
    {
        DespawnParticipant(Participant);
    }
}

void UDynamicWorldEvents::ApplyEventEffects(const FString& EventID)
{
    UE_LOG(LogTemp, Warning, TEXT("Applying event effects: %s"), *EventID);
}

void UDynamicWorldEvents::RemoveEventEffects(const FString& EventID)
{
    UE_LOG(LogTemp, Warning, TEXT("Removing event effects: %s"), *EventID);
}

void UDynamicWorldEvents::SpawnParticipant(const FEventParticipant& Participant)
{
    UE_LOG(LogTemp, Warning, TEXT("Spawning participant: %s"), *Participant.ParticipantID);
}

void UDynamicWorldEvents::DespawnParticipant(const FEventParticipant& Participant)
{
    UE_LOG(LogTemp, Warning, TEXT("Despawning participant: %s"), *Participant.ParticipantID);
}

void UDynamicWorldEvents::UpdateEventAI(const FString& EventID)
{
    // Update AI for event
}

void UDynamicWorldEvents::ProcessEventAI(const FString& EventID, float DeltaTime)
{
    // Process AI logic
}

void UDynamicWorldEvents::UpdateEventTimers(float DeltaTime)
{
    // Update scheduled events
    for (auto& EventPair : ScheduledEvents)
    {
        EventPair.Value -= DeltaTime;
        
        if (EventPair.Value <= 0.0f)
        {
            TriggerEvent(EventPair.Key);
            ScheduledEvents.Remove(EventPair.Key);
            break;
        }
    }
}

void UDynamicWorldEvents::ProcessScheduledEvents()
{
    // Process scheduled events
}

void UDynamicWorldEvents::CheckForRandomEvents()
{
    RandomEventTimer += GetWorld()->GetDeltaSeconds();
    
    if (RandomEventTimer >= 300.0f)
    {
        RandomEventTimer = 0.0f;
        GenerateRandomEvent();
    }
}

void UDynamicWorldEvents::GenerateRandomEvent()
{
    TArray<EEventType> EventTypes = {EEventType::ET_Battle, EEventType::ET_Merchant, EEventType::ET_Quest};
    EEventType RandomType = EventTypes[FMath::RandRange(0, EventTypes.Num() - 1)];
    
    TArray<EBiomeType> Biomes = {EBiomeType::BT_Forest, EBiomeType::BT_Plains, EBiomeType::BT_Mountain};
    EBiomeType RandomBiome = Biomes[FMath::RandRange(0, Biomes.Num() - 1)];
    
    FVector RandomLocation = FVector(FMath::RandRange(-5000, 5000), FMath::RandRange(-5000, 5000), 0);
    
    CreateRandomEvent(RandomType, RandomBiome, RandomLocation);
}

void UDynamicWorldEvents::CreateRandomEvent(EEventType EventType, EBiomeType Biome, FVector Location)
{
    TArray<FDynamicWorldEvent> MatchingEvents;
    
    for (const FDynamicWorldEvent& Event : AvailableEvents)
    {
        if (Event.EventType == EventType && Event.Biome == Biome)
        {
            MatchingEvents.Add(Event);
        }
    }
    
    if (MatchingEvents.Num() > 0)
    {
        FDynamicWorldEvent SelectedEvent = MatchingEvents[FMath::RandRange(0, MatchingEvents.Num() - 1)];
        SelectedEvent.EventLocation = Location;
        
        TriggerEvent(SelectedEvent.EventID);
    }
}

void UDynamicWorldEvents::SaveEventState()
{
    UE_LOG(LogTemp, Warning, TEXT("Dynamic events state saved"));
}

void UDynamicWorldEvents::LoadEventState()
{
    UE_LOG(LogTemp, Warning, TEXT("Dynamic events state loaded"));
}

void UDynamicWorldEvents::UpdateEventStatistics(const FString& EventID, bool bSuccess)
{
    if (!EventTriggerCount.Contains(EventID))
    {
        EventTriggerCount.Add(EventID, 0);
        EventSuccessRate.Add(EventID, 0.0f);
    }
    
    EventTriggerCount[EventID]++;
    
    int32 TotalTriggers = EventTriggerCount[EventID];
    float CurrentSuccessRate = EventSuccessRate[EventID];
    
    EventSuccessRate[EventID] = (CurrentSuccessRate * (TotalTriggers - 1) + (bSuccess ? 1.0f : 0.0f)) / TotalTriggers;
}

void UDynamicWorldEvents::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    DOREPLIFETIME(UDynamicWorldEvents, AvailableEvents);
    DOREPLIFETIME(UDynamicWorldEvents, ActiveEvents);
    DOREPLIFETIME(UDynamicWorldEvents, EventChains);
    DOREPLIFETIME(UDynamicWorldEvents, ScheduledEvents);
    DOREPLIFETIME(UDynamicWorldEvents, EventProgress);
}
