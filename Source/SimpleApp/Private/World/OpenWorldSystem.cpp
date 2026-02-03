#include "OpenWorldSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DataTable.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundBase.h"
#include "Net/UnrealNetwork.h"

UOpenWorldSystem::UOpenWorldSystem()
{
    PrimaryComponentTick.bCanEverTick = true;
    SetIsReplicatedByDefault(true);
    
    CurrentWeather = EWeatherType::WT_Clear;
    CurrentTimeOfDay = ETimeOfDay::TOD_Morning;
    WorldTime = 6.0f; // Start at 6 AM
    WeatherChangeTimer = 0.0f;
    TimeAdvanceTimer = 0.0f;
    EventUpdateTimer = 0.0f;
}

void UOpenWorldSystem::BeginPlay()
{
    Super::BeginPlay();
    InitializeOpenWorld();
}

void UOpenWorldSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    UpdateWeatherSystem(DeltaTime);
    UpdateTimeSystem(DeltaTime);
    UpdateDynamicEvents(DeltaTime);
    ProcessWorldEvents();
}

void UOpenWorldSystem::InitializeOpenWorld()
{
    UE_LOG(LogTemp, Warning, TEXT("Open World System initialized"));
    
    // Initialize all world systems
    InitializeWorldLocations();
    InitializePointsOfInterest();
    InitializeEnvironmentalStories();
    InitializeWorldEvents();
    
    // Load saved world state
    LoadWorldState();
    
    UE_LOG(LogTemp, Warning, TEXT("Open World System ready"));
}

TArray<FWorldLocation> UOpenWorldSystem::GetWorldLocations() const
{
    return WorldLocations;
}

TArray<FWorldLocation> UOpenWorldSystem::GetDiscoveredLocations() const
{
    TArray<FWorldLocation> DiscoveredLocations;
    
    for (const FWorldLocation& Location : WorldLocations)
    {
        if (Location.bIsDiscovered)
        {
            DiscoveredLocations.Add(Location);
        }
    }
    
    return DiscoveredLocations;
}

FWorldLocation UOpenWorldSystem::GetLocation(const FString& LocationName) const
{
    for (const FWorldLocation& Location : WorldLocations)
    {
        if (Location.LocationName == LocationName)
        {
            return Location;
        }
    }
    
    FWorldLocation EmptyLocation;
    return EmptyLocation;
}

bool UOpenWorldSystem::DiscoverLocation(const FString& LocationName)
{
    if (DiscoveredLocations.Contains(LocationName))
    {
        UE_LOG(LogTemp, Warning, TEXT("Location already discovered: %s"), *LocationName);
        return false;
    }
    
    for (FWorldLocation& Location : WorldLocations)
    {
        if (Location.LocationName == LocationName)
        {
            Location.bIsDiscovered = true;
            DiscoveredLocations.Add(LocationName);
            
            NotifyLocationDiscovered(Location);
            UE_LOG(LogTemp, Warning, TEXT("Location discovered: %s"), *LocationName);
            return true;
        }
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Location not found: %s"), *LocationName);
    return false;
}

bool UOpenWorldSystem::IsLocationDiscovered(const FString& LocationName) const
{
    return DiscoveredLocations.Contains(LocationName);
}

bool UOpenWorldSystem::UnlockFastTravel(const FString& LocationName)
{
    if (!IsLocationDiscovered(LocationName))
    {
        UE_LOG(LogTemp, Warning, TEXT("Cannot unlock fast travel to undiscovered location: %s"), *LocationName);
        return false;
    }
    
    if (UnlockedFastTravel.Contains(LocationName))
    {
        UE_LOG(LogTemp, Warning, TEXT("Fast travel already unlocked: %s"), *LocationName);
        return false;
    }
    
    UnlockedFastTravel.Add(LocationName);
    
    for (FWorldLocation& Location : WorldLocations)
    {
        if (Location.LocationName == LocationName)
        {
            Location.bIsFastTravelUnlocked = true;
            break;
        }
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Fast travel unlocked: %s"), *LocationName);
    return true;
}

bool UOpenWorldSystem::CanFastTravelTo(const FString& LocationName) const
{
    return UnlockedFastTravel.Contains(LocationName);
}

bool UOpenWorldSystem::FastTravelToLocation(const FString& LocationName)
{
    if (!CanFastTravelTo(LocationName))
    {
        UE_LOG(LogTemp, Warning, TEXT("Cannot fast travel to: %s"), *LocationName);
        return false;
    }
    
    FWorldLocation Location = GetLocation(LocationName);
    if (Location.LocationName.IsEmpty())
    {
        UE_LOG(LogTemp, Warning, TEXT("Location not found for fast travel: %s"), *LocationName);
        return false;
    }
    
    AActor* OwnerActor = GetOwner();
    if (OwnerActor)
    {
        OwnerActor->SetActorLocation(Location.WorldPosition);
        OwnerActor->SetActorRotation(Location.WorldRotation);
        
        UE_LOG(LogTemp, Warning, TEXT("Fast traveled to: %s"), *LocationName);
        return true;
    }
    
    return false;
}

TArray<FPointOfInterest> UOpenWorldSystem::GetPointsOfInterest(const FString& LocationName) const
{
    if (LocationPOIs.Contains(LocationName))
    {
        return LocationPOIs[LocationName];
    }
    
    return TArray<FPointOfInterest>();
}

TArray<FPointOfInterest> UOpenWorldSystem::GetDiscoveredPOIs(const FString& LocationName) const
{
    TArray<FPointOfInterest> DiscoveredPOIs;
    
    if (LocationPOIs.Contains(LocationName))
    {
        for (const FPointOfInterest& POI : LocationPOIs[LocationName])
        {
            if (POI.bIsDiscovered)
            {
                DiscoveredPOIs.Add(POI);
            }
        }
    }
    
    return DiscoveredPOIs;
}

bool UOpenWorldSystem::DiscoverPOI(const FString& POIName)
{
    if (DiscoveredPOIs.Contains(POIName))
    {
        UE_LOG(LogTemp, Warning, TEXT("POI already discovered: %s"), *POIName);
        return false;
    }
    
    for (auto& POIPair : LocationPOIs)
    {
        TArray<FPointOfInterest>& POIs = POIPair.Value;
        for (FPointOfInterest& POI : POIs)
        {
            if (POI.POIName == POIName)
            {
                POI.bIsDiscovered = true;
                DiscoveredPOIs.Add(POIName);
                
                NotifyPOIDiscovered(POI);
                UE_LOG(LogTemp, Warning, TEXT("POI discovered: %s"), *POIName);
                return true;
            }
        }
    }
    
    UE_LOG(LogTemp, Warning, TEXT("POI not found: %s"), *POIName);
    return false;
}

FPointOfInterest UOpenWorldSystem::GetPOI(const FString& POIName) const
{
    for (const auto& POIPair : LocationPOIs)
    {
        for (const FPointOfInterest& POI : POIPair.Value)
        {
            if (POI.POIName == POIName)
            {
                return POI;
            }
        }
    }
    
    FPointOfInterest EmptyPOI;
    return EmptyPOI;
}

bool UOpenWorldSystem::IsPOIDiscovered(const FString& POIName) const
{
    return DiscoveredPOIs.Contains(POIName);
}

TArray<FPointOfInterest> UOpenWorldSystem::GetNearbyPOIs(const FVector& PlayerPosition, float Radius) const
{
    TArray<FPointOfInterest> NearbyPOIs;
    
    for (const auto& POIPair : LocationPOIs)
    {
        for (const FPointOfInterest& POI : POIPair.Value)
        {
            float Distance = FVector::Dist(PlayerPosition, POI.Location);
            if (Distance <= Radius)
            {
                NearbyPOIs.Add(POI);
            }
        }
    }
    
    return NearbyPOIs;
}

TArray<FEnvironmentalStory> UOpenWorldSystem::GetEnvironmentalStories(const FString& LocationName) const
{
    TArray<FEnvironmentalStory> LocationStories;
    
    for (const FEnvironmentalStory& Story : EnvironmentalStories)
    {
        if (Story.Location == LocationName)
        {
            LocationStories.Add(Story);
        }
    }
    
    return LocationStories;
}

bool UOpenWorldSystem::DiscoverEnvironmentalStory(const FString& StoryID)
{
    if (DiscoveredStories.Contains(StoryID))
    {
        UE_LOG(LogTemp, Warning, TEXT("Environmental story already discovered: %s"), *StoryID);
        return false;
    }
    
    for (FEnvironmentalStory& Story : EnvironmentalStories)
    {
        if (Story.StoryID == StoryID)
        {
            Story.bIsDiscovered = true;
            DiscoveredStories.Add(StoryID);
            
            NotifyEnvironmentalStoryFound(Story);
            UE_LOG(LogTemp, Warning, TEXT("Environmental story discovered: %s"), *StoryID);
            return true;
        }
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Environmental story not found: %s"), *StoryID);
    return false;
}

FEnvironmentalStory UOpenWorldSystem::GetEnvironmentalStory(const FString& StoryID) const
{
    for (const FEnvironmentalStory& Story : EnvironmentalStories)
    {
        if (Story.StoryID == StoryID)
        {
            return Story;
        }
    }
    
    FEnvironmentalStory EmptyStory;
    return EmptyStory;
}

bool UOpenWorldSystem::HasEnvironmentalStory(const FString& LocationName) const
{
    for (const FEnvironmentalStory& Story : EnvironmentalStories)
    {
        if (Story.Location == LocationName && Story.bIsDiscovered)
        {
            return true;
        }
    }
    
    return false;
}

void UOpenWorldSystem::AddEnvironmentalClue(const FString& LocationName, const FString& Clue)
{
    for (FEnvironmentalStory& Story : EnvironmentalStories)
    {
        if (Story.Location == LocationName && !Story.bIsDiscovered)
        {
            if (!Story.Clues.Contains(Clue))
            {
                Story.Clues.Add(Clue);
                UE_LOG(LogTemp, Warning, TEXT("Environmental clue added: %s to %s"), *Clue, *LocationName);
            }
            break;
        }
    }
}

void UOpenWorldSystem::SetWeather(EWeatherType NewWeather)
{
    if (CurrentWeather == NewWeather)
    {
        return;
    }
    
    CurrentWeather = NewWeather;
    ApplyWeatherEffects(NewWeather);
    NotifyWeatherChanged(NewWeather);
    
    UE_LOG(LogTemp, Warning, TEXT("Weather changed to: %d"), (int32)NewWeather);
}

EWeatherType UOpenWorldSystem::GetCurrentWeather() const
{
    return CurrentWeather;
}

void UOpenWorldSystem::ChangeWeatherRandomly()
{
    TArray<EWeatherType> AvailableWeather;
    
    // Get weather types based on current biome
    for (const FWorldLocation& Location : WorldLocations)
    {
        if (Location.bIsDiscovered)
        {
            TArray<EWeatherType> BiomeWeather = GetAvailableWeatherTypes(Location.Biome);
            for (EWeatherType Weather : BiomeWeather)
            {
                if (!AvailableWeather.Contains(Weather))
                {
                    AvailableWeather.Add(Weather);
                }
            }
        }
    }
    
    if (AvailableWeather.Num() > 0)
    {
        EWeatherType RandomWeather = AvailableWeather[FMath::RandRange(0, AvailableWeather.Num() - 1)];
        SetWeather(RandomWeather);
    }
}

TArray<EWeatherType> UOpenWorldSystem::GetAvailableWeatherTypes(EBiomeType Biome) const
{
    TArray<EWeatherType> AvailableWeather;
    
    switch (Biome)
    {
        case EBiomeType::BT_Forest:
            AvailableWeather.Add(EWeatherType::WT_Clear);
            AvailableWeather.Add(EWeatherType::WT_Cloudy);
            AvailableWeather.Add(EWeatherType::WT_LightRain);
            AvailableWeather.Add(EWeatherType::WT_Fog);
            break;
            
        case EBiomeType::BT_Desert:
            AvailableWeather.Add(EWeatherType::WT_Clear);
            AvailableWeather.Add(EWeatherType::WT_Sandstorm);
            break;
            
        case EBiomeType::BT_Tundra:
            AvailableWeather.Add(EWeatherType::WT_Clear);
            AvailableWeather.Add(EWeatherType::WT_Snow);
            AvailableWeather.Add(EWeatherType::WT_Blizzard);
            break;
            
        case EBiomeType::BT_Volcanic:
            AvailableWeather.Add(EWeatherType::WT_Clear);
            AvailableWeather.Add(EWeatherType::WT_AshFall);
            AvailableWeather.Add(EWeatherType::WT_MagicalStorm);
            break;
            
        default:
            AvailableWeather.Add(EWeatherType::WT_Clear);
            AvailableWeather.Add(EWeatherType::WT_Cloudy);
            AvailableWeather.Add(EWeatherType::WT_LightRain);
            break;
    }
    
    return AvailableWeather;
}

bool UOpenWorldSystem::CanWeatherChange(EBiomeType Biome) const
{
    // Some biomes have restricted weather changes
    return Biome != EBiomeType::BT_Volcanic && Biome != EBiomeType::BT_Abyssal;
}

void UOpenWorldSystem::SetTimeOfDay(ETimeOfDay NewTimeOfDay)
{
    if (CurrentTimeOfDay == NewTimeOfDay)
    {
        return;
    }
    
    CurrentTimeOfDay = NewTimeOfDay;
    ApplyTimeEffects(NewTimeOfDay);
    NotifyTimeOfDayChanged(NewTimeOfDay);
    
    UE_LOG(LogTemp, Warning, TEXT("Time of day changed to: %d"), (int32)NewTimeOfDay);
}

ETimeOfDay UOpenWorldSystem::GetCurrentTimeOfDay() const
{
    return CurrentTimeOfDay;
}

void UOpenWorldSystem::AdvanceTime(float Hours)
{
    WorldTime += Hours;
    
    // Wrap around 24 hours
    while (WorldTime >= 24.0f)
    {
        WorldTime -= 24.0f;
    }
    
    // Update time of day
    if (WorldTime >= 5.0f && WorldTime < 7.0f)
    {
        SetTimeOfDay(ETimeOfDay::TOD_Dawn);
    }
    else if (WorldTime >= 7.0f && WorldTime < 11.0f)
    {
        SetTimeOfDay(ETimeOfDay::TOD_Morning);
    }
    else if (WorldTime >= 11.0f && WorldTime < 13.0f)
    {
        SetTimeOfDay(ETimeOfDay::TOD_Noon);
    }
    else if (WorldTime >= 13.0f && WorldTime < 17.0f)
    {
        SetTimeOfDay(ETimeOfDay::TOD_Afternoon);
    }
    else if (WorldTime >= 17.0f && WorldTime < 19.0f)
    {
        SetTimeOfDay(ETimeOfDay::TOD_Dusk);
    }
    else if (WorldTime >= 19.0f && WorldTime < 21.0f)
    {
        SetTimeOfDay(ETimeOfDay::TOD_Evening);
    }
    else if (WorldTime >= 21.0f && WorldTime < 23.0f)
    {
        SetTimeOfDay(ETimeOfDay::TOD_Night);
    }
    else
    {
        SetTimeOfDay(ETimeOfDay::TOD_Midnight);
    }
}

float UOpenWorldSystem::GetWorldTime() const
{
    return WorldTime;
}

bool UOpenWorldSystem::IsNightTime() const
{
    return CurrentTimeOfDay == ETimeOfDay::TOD_Night || CurrentTimeOfDay == ETimeOfDay::TOD_Midnight;
}

bool UOpenWorldSystem::IsDayTime() const
{
    return !IsNightTime();
}

void UOpenWorldSystem::TriggerWorldEvent(const FString& EventName)
{
    for (const FWorldEvent& Event : WorldEvents)
    {
        if (Event.EventName == EventName && !Event.bIsActive)
        {
            FWorldEvent ActiveEvent = Event;
            ActiveEvent.bIsActive = true;
            ActiveEvents.Add(ActiveEvent);
            
            SpawnWorldEvent(ActiveEvent);
            NotifyWorldEventTriggered(ActiveEvent);
            
            UE_LOG(LogTemp, Warning, TEXT("World event triggered: %s"), *EventName);
            return;
        }
    }
    
    UE_LOG(LogTemp, Warning, TEXT("World event not found or already active: %s"), *EventName);
}

TArray<FWorldEvent> UOpenWorldSystem::GetActiveEvents() const
{
    return ActiveEvents;
}

TArray<FWorldEvent> UOpenWorldSystem::GetAvailableEvents(const FString& LocationName) const
{
    TArray<FWorldEvent> LocationEvents;
    
    for (const FWorldEvent& Event : WorldEvents)
    {
        if (Event.EventLocation.ToString().Contains(LocationName) && !Event.bIsActive)
        {
            LocationEvents.Add(Event);
        }
    }
    
    return LocationEvents;
}

void UOpenWorldSystem::UpdateRandomEvents()
{
    // Check for random event triggers
    for (const FWorldEvent& Event : WorldEvents)
    {
        if (Event.bIsRandomEvent && !Event.bIsActive)
        {
            float RandomChance = FMath::RandRange(0.0f, 1.0f);
            if (RandomChance <= Event.TriggerChance)
            {
                TriggerWorldEvent(Event.EventName);
            }
        }
    }
}

void UOpenWorldSystem::CompleteWorldEvent(const FString& EventName)
{
    for (int32 i = 0; i < ActiveEvents.Num(); i++)
    {
        if (ActiveEvents[i].EventName == EventName)
        {
            DespawnWorldEvent(EventName);
            ActiveEvents.RemoveAt(i);
            
            UE_LOG(LogTemp, Warning, TEXT("World event completed: %s"), *EventName);
            return;
        }
    }
}

float UOpenWorldSystem::GetExplorationProgress() const
{
    int32 DiscoveredCount = GetDiscoveredLocationCount();
    int32 TotalCount = GetTotalLocationCount();
    
    if (TotalCount == 0)
    {
        return 0.0f;
    }
    
    return (float)DiscoveredCount / (float)TotalCount;
}

int32 UOpenWorldSystem::GetDiscoveredLocationCount() const
{
    return DiscoveredLocations.Num();
}

int32 UOpenWorldSystem::GetTotalLocationCount() const
{
    return WorldLocations.Num();
}

TArray<FString> UOpenWorldSystem::GetHiddenLocations() const
{
    TArray<FString> HiddenLocations;
    
    for (const FWorldLocation& Location : WorldLocations)
    {
        if (!Location.bIsDiscovered)
        {
            HiddenLocations.Add(Location.LocationName);
        }
    }
    
    return HiddenLocations;
}

bool UOpenWorldSystem::RevealHiddenLocation(const FString& LocationName)
{
    return DiscoverLocation(LocationName);
}

void UOpenWorldSystem::OnPlayerEnterLocation(const FString& LocationName)
{
    UE_LOG(LogTemp, Warning, TEXT("Player entered location: %s"), *LocationName);
    
    // Trigger location-specific events
    FWorldLocation Location = GetLocation(LocationName);
    if (Location.bHasStoryEvent)
    {
        // Trigger story event
    }
    
    // Update location weather and time
    UpdateLocationWeather(LocationName);
    UpdateLocationTime(LocationName);
}

void UOpenWorldSystem::OnPlayerExitLocation(const FString& LocationName)
{
    UE_LOG(LogTemp, Warning, TEXT("Player exited location: %s"), *LocationName);
}

void UOpenWorldSystem::OnPlayerInteractWithPOI(const FString& POIName)
{
    UE_LOG(LogTemp, Warning, TEXT("Player interacted with POI: %s"), *POIName);
    
    FPointOfInterest POI = GetPOI(POIName);
    if (POI.bHasQuest && !POI.AssociatedQuest.IsEmpty())
    {
        // Trigger quest
    }
    
    if (!POI.EnvironmentalStory.IsEmpty())
    {
        DiscoverEnvironmentalStory(POI.EnvironmentalStory);
    }
}

void UOpenWorldSystem::OnPlayerPickupLoreItem(const FString& LoreItemID)
{
    UE_LOG(LogTemp, Warning, TEXT("Player picked up lore item: %s"), *LoreItemID);
    
    // Update environmental stories with lore item
    for (FEnvironmentalStory& Story : EnvironmentalStories)
    {
        if (Story.LoreItemID == LoreItemID)
        {
            Story.bHasLoreItem = true;
            break;
        }
    }
}

void UOpenWorldSystem::SaveWorldState()
{
    // Save world state
    UE_LOG(LogTemp, Warning, TEXT("World state saved"));
}

void UOpenWorldSystem::LoadWorldState()
{
    // Load world state
    UE_LOG(LogTemp, Warning, TEXT("World state loaded"));
}

void UOpenWorldSystem::ResetWorldState()
{
    DiscoveredLocations.Empty();
    DiscoveredPOIs.Empty();
    DiscoveredStories.Empty();
    UnlockedFastTravel.Empty();
    ActiveEvents.Empty();
    
    for (FWorldLocation& Location : WorldLocations)
    {
        Location.bIsDiscovered = false;
        Location.bIsFastTravelUnlocked = false;
    }
    
    for (auto& POIPair : LocationPOIs)
    {
        for (FPointOfInterest& POI : POIPair.Value)
        {
            POI.bIsDiscovered = false;
        }
    }
    
    for (FEnvironmentalStory& Story : EnvironmentalStories)
    {
        Story.bIsDiscovered = false;
        Story.bHasLoreItem = false;
    }
    
    UE_LOG(LogTemp, Warning, TEXT("World state reset"));
}

void UOpenWorldSystem::InitializeWorldLocations()
{
    WorldLocations.Empty();
    
    // Create major world locations
    WorldLocations.Add(CreateWorldLocation(TEXT("Starting Village"), EBiomeType::BT_Forest, FVector(0, 0, 0)));
    WorldLocations.Add(CreateWorldLocation(TEXT("Royal City"), EBiomeType::BT_Plains, FVector(5000, 3000, 0)));
    WorldLocations.Add(CreateWorldLocation(TEXT("Dragon's Peak"), EBiomeType::BT_Mountain, FVector(-3000, -2000, 1000)));
    WorldLocations.Add(CreateWorldLocation(TEXT("Shadow Swamp"), EBiomeType::BT_Swamp, FVector(2000, -4000, 0)));
    WorldLocations.Add(CreateWorldLocation(TEXT("Burning Desert"), EBiomeType::BT_Desert, FVector(8000, 0, 0)));
    WorldLocations.Add(CreateWorldLocation(TEXT("Frozen Tundra"), EBiomeType::BT_Tundra, FVector(-5000, 5000, 0)));
    WorldLocations.Add(CreateWorldLocation(TEXT("Volcanic Wastes"), EBiomeType::BT_Volcanic, FVector(0, 8000, 500)));
    WorldLocations.Add(CreateWorldLocation(TEXT("Sacred Grove"), EBiomeType::BT_Holy, FVector(-2000, -3000, 0)));
    WorldLocations.Add(CreateWorldLocation(TEXT("Abyssal Depths"), EBiomeType::BT_Abyssal, FVector(10000, 10000, -1000)));
    WorldLocations.Add(CreateWorldLocation(TEXT("Celestial Realm"), EBiomeType::BT_Celestial, FVector(0, 0, 2000)));
    
    // Set starting village as discovered
    WorldLocations[0].bIsDiscovered = true;
    DiscoveredLocations.Add(WorldLocations[0].LocationName);
}

void UOpenWorldSystem::InitializePointsOfInterest()
{
    LocationPOIs.Empty();
    
    // Add POIs to each location
    for (const FWorldLocation& Location : WorldLocations)
    {
        TArray<FPointOfInterest> LocationPOIs;
        
        // Add village POIs
        if (Location.LocationName == TEXT("Starting Village"))
        {
            LocationPOIs.Add(CreatePointOfInterest(TEXT("Village Elder"), EPointOfInterestType::POI_QuestGiver, Location.WorldPosition + FVector(100, 100, 0)));
            LocationPOIs.Add(CreatePointOfInterest(TEXT("Blacksmith"), EPointOfInterestType::POI_Merchant, Location.WorldPosition + FVector(-100, 100, 0)));
            LocationPOIs.Add(CreatePointOfInterest(TEXT("Ancient Ruins"), EPointOfInterestType::POI_Ruin, Location.WorldPosition + FVector(500, 0, 0)));
            LocationPOIs.Add(CreatePointOfInterest(TEXT("Hidden Cave"), EPointOfInterestType::POI_Cave, Location.WorldPosition + FVector(0, -300, 0)));
        }
        
        LocationPOIs.Add(Location.LocationName, LocationPOIs);
    }
}

void UOpenWorldSystem::InitializeEnvironmentalStories()
{
    EnvironmentalStories.Empty();
    
    // Create environmental stories
    EnvironmentalStories.Add(CreateEnvironmentalStory(TEXT("STORY_001"), TEXT("Starting Village"), TEXT("The village elder speaks of ancient times when dragons ruled the skies...")));
    EnvironmentalStories.Add(CreateEnvironmentalStory(TEXT("STORY_002"), TEXT("Ancient Ruins"), TEXT("Crumbled stones tell tales of a fallen civilization that once thrived here...")));
    EnvironmentalStories.Add(CreateEnvironmentalStory(TEXT("STORY_003"), TEXT("Hidden Cave"), TEXT("Strange markings on the walls suggest this was once a place of worship...")));
    EnvironmentalStories.Add(CreateEnvironmentalStory(TEXT("STORY_004"), TEXT("Dragon's Peak"), TEXT("The mountain's peak is scarred with ancient claw marks, evidence of a great battle...")));
    EnvironmentalStories.Add(CreateEnvironmentalStory(TEXT("STORY_005"), TEXT("Shadow Swamp"), TEXT("The swamp's murky waters hide secrets of those who dared to enter...")));
}

void UOpenWorldSystem::InitializeWorldEvents()
{
    WorldEvents.Empty();
    
    // Create world events
    WorldEvents.Add(CreateWorldEvent(TEXT("Bandit Attack"), EBiomeType::BT_Forest, FVector(1000, 1000, 0)));
    WorldEvents.Add(CreateWorldEvent(TEXT("Dragon Sighting"), EBiomeType::BT_Mountain, FVector(-3000, -2000, 1000)));
    WorldEvents.Add(CreateWorldEvent(TEXT("Merchant Caravan"), EBiomeType::BT_Plains, FVector(3000, 2000, 0)));
    WorldEvents.Add(CreateWorldEvent(TEXT("Mysterious Portal"), EBiomeType::BT_Shadow, FVector(-1000, -1000, 0)));
    WorldEvents.Add(CreateWorldEvent(TEXT("Treasure Discovery"), EBiomeType::BT_Custom, FVector(2000, 2000, 0)));
}

void UOpenWorldSystem::UpdateWeatherSystem(float DeltaTime)
{
    WeatherChangeTimer += DeltaTime;
    
    // Change weather every 10-20 minutes
    if (WeatherChangeTimer >= 600.0f) // 10 minutes
    {
        WeatherChangeTimer = 0.0f;
        
        // Random chance to change weather
        if (FMath::RandRange(0.0f, 1.0f) <= 0.3f) // 30% chance
        {
            ChangeWeatherRandomly();
        }
    }
}

void UOpenWorldSystem::UpdateTimeSystem(float DeltaTime)
{
    TimeAdvanceTimer += DeltaTime;
    
    // Advance time every 60 seconds (1 minute real time = 1 hour game time)
    if (TimeAdvanceTimer >= 60.0f)
    {
        TimeAdvanceTimer = 0.0f;
        AdvanceTime(1.0f);
    }
}

void UOpenWorldSystem::UpdateDynamicEvents(float DeltaTime)
{
    EventUpdateTimer += DeltaTime;
    
    // Check for random events every 5 minutes
    if (EventUpdateTimer >= 300.0f)
    {
        EventUpdateTimer = 0.0f;
        UpdateRandomEvents();
    }
}

void UOpenWorldSystem::ProcessWorldEvents()
{
    // Process active events
    for (int32 i = ActiveEvents.Num() - 1; i >= 0; i--)
    {
        FWorldEvent& Event = ActiveEvents[i];
        Event.Duration -= GetWorld()->GetDeltaSeconds();
        
        if (Event.Duration <= 0.0f)
        {
            CompleteWorldEvent(Event.EventName);
        }
    }
}

FWorldLocation UOpenWorldSystem::CreateWorldLocation(const FString& Name, EBiomeType Biome, FVector Position)
{
    FWorldLocation Location;
    Location.LocationName = Name;
    Location.WorldPosition = Position;
    Location.WorldRotation = FRotator::ZeroRotator;
    Location.Biome = Biome;
    Location.CurrentWeather = EWeatherType::WT_Clear;
    Location.TimeOfDay = ETimeOfDay::TOD_Morning;
    Location.bIsDiscovered = false;
    Location.bIsFastTravelUnlocked = false;
    Location.Description = FString::Printf(TEXT("A %s location in the world."), *UEnum::GetValueAsString(Biome));
    Location.ConnectedLocations.Empty();
    Location.RecommendedLevel = 1;
    Location.AvailableQuests.Empty();
    Location.AvailableNPCs.Empty();
    Location.MapIcon = nullptr;
    Location.bHasStoryEvent = false;
    
    return Location;
}

FPointOfInterest UOpenWorldSystem::CreatePointOfInterest(const FString& Name, EPointOfInterestType Type, FVector Location)
{
    FPointOfInterest POI;
    POI.POIName = Name;
    POI.POIType = Type;
    POI.Location = Location;
    POI.Description = FString::Printf(TEXT("A %s of interest."), *UEnum::GetValueAsString(Type));
    POI.bIsDiscovered = false;
    POI.bIsActive = true;
    POI.bHasQuest = false;
    POI.AssociatedQuest = TEXT("");
    POI.Loot.Empty();
    POI.Enemies.Empty();
    POI.EnvironmentalStory = TEXT("");
    POI.Icon = nullptr;
    POI.bIsHidden = false;
    POI.UnlockRequirement = TEXT("");
    
    return POI;
}

FEnvironmentalStory UOpenWorldSystem::CreateEnvironmentalStory(const FString& ID, const FString& Location, const FString& Story)
{
    FEnvironmentalStory EnvironmentalStory;
    EnvironmentalStory.StoryID = ID;
    EnvironmentalStory.Location = Location;
    EnvironmentalStory.StoryText = Story;
    EnvironmentalStory.Clues.Empty();
    EnvironmentalStory.RelatedQuests.Empty();
    EnvironmentalStory.bIsDiscovered = false;
    EnvironmentalStory.bHasLoreItem = false;
    EnvironmentalStory.LoreItemID = TEXT("");
    
    return EnvironmentalStory;
}

FWorldEvent UOpenWorldSystem::CreateWorldEvent(const FString& Name, EBiomeType Biome, FVector Location)
{
    FWorldEvent WorldEvent;
    WorldEvent.EventName = Name;
    WorldEvent.Description = FString::Printf(TEXT("A dynamic event in the %s."), *UEnum::GetValueAsString(Biome));
    WorldEvent.EventLocation = Location;
    WorldEvent.Biome = Biome;
    WorldEvent.bIsActive = false;
    WorldEvent.Duration = 300.0f; // 5 minutes
    WorldEvent.Participants.Empty();
    WorldEvent.Rewards.Empty();
    WorldEvent.EventType = TEXT("Dynamic");
    WorldEvent.bIsRandomEvent = true;
    WorldEvent.TriggerChance = 0.1f; // 10% chance
    
    return WorldEvent;
}

void UOpenWorldSystem::NotifyLocationDiscovered(const FWorldLocation& Location)
{
    OnLocationDiscovered.Broadcast(Location);
}

void UOpenWorldSystem::NotifyPOIDiscovered(const FPointOfInterest& POI)
{
    OnPOIDiscovered.Broadcast(POI);
}

void UOpenWorldSystem::NotifyWeatherChanged(EWeatherType NewWeather)
{
    OnWeatherChanged.Broadcast(NewWeather);
}

void UOpenWorldSystem::NotifyTimeOfDayChanged(ETimeOfDay NewTimeOfDay)
{
    OnTimeOfDayChanged.Broadcast(NewTimeOfDay);
}

void UOpenWorldSystem::NotifyWorldEventTriggered(const FWorldEvent& WorldEvent)
{
    OnWorldEventTriggered.Broadcast(WorldEvent);
}

void UOpenWorldSystem::NotifyEnvironmentalStoryFound(const FEnvironmentalStory& Story)
{
    OnEnvironmentalStoryFound.Broadcast(Story);
}

void UOpenWorldSystem::UpdateLocationWeather(const FString& LocationName)
{
    FWorldLocation Location = GetLocation(LocationName);
    if (!Location.LocationName.IsEmpty())
    {
        Location.CurrentWeather = CurrentWeather;
    }
}

void UOpenWorldSystem::UpdateLocationTime(const FString& LocationName)
{
    FWorldLocation Location = GetLocation(LocationName);
    if (!Location.LocationName.IsEmpty())
    {
        Location.TimeOfDay = CurrentTimeOfDay;
    }
}

bool UOpenWorldSystem::ValidateLocation(const FString& LocationName) const
{
    for (const FWorldLocation& Location : WorldLocations)
    {
        if (Location.LocationName == LocationName)
        {
            return true;
        }
    }
    
    return false;
}

bool UOpenWorldSystem::ValidatePOI(const FString& POIName) const
{
    for (const auto& POIPair : LocationPOIs)
    {
        for (const FPointOfInterest& POI : POIPair.Value)
        {
            if (POI.POIName == POIName)
            {
                return true;
            }
        }
    }
    
    return false;
}

void UOpenWorldSystem::SpawnWorldEvent(const FWorldEvent& WorldEvent)
{
    // Spawn world event in the world
    // This would typically involve spawning NPCs, objects, or triggering effects
    UE_LOG(LogTemp, Warning, TEXT("Spawning world event: %s"), *WorldEvent.EventName);
}

void UOpenWorldSystem::DespawnWorldEvent(const FString& EventName)
{
    // Desawn world event from the world
    UE_LOG(LogTemp, Warning, TEXT("Despawning world event: %s"), *EventName);
}

void UOpenWorldSystem::ApplyWeatherEffects(EWeatherType Weather)
{
    // Apply weather effects to the world
    // This would typically involve changing lighting, particles, and sound
    UE_LOG(LogTemp, Warning, TEXT("Applying weather effects: %d"), (int32)Weather);
}

void UOpenWorldSystem::ApplyTimeEffects(ETimeOfDay TimeOfDay)
{
    // Apply time of day effects to the world
    // This would typically involve changing lighting, sky, and ambient sounds
    UE_LOG(LogTemp, Warning, TEXT("Applying time of day effects: %d"), (int32)TimeOfDay);
}

void UOpenWorldSystem::GenerateRandomWeather()
{
    // Generate random weather based on current biome
    ChangeWeatherRandomly();
}

void UOpenWorldSystem::GenerateRandomEvent()
{
    // Generate random world event
    UpdateRandomEvents();
}

void UOpenWorldSystem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    DOREPLIFETIME(UOpenWorldSystem, WorldLocations);
    DOREPLIFETIME(UOpenWorldSystem, LocationPOIs);
    DOREPLIFETIME(UOpenWorldSystem, EnvironmentalStories);
    DOREPLIFETIME(UOpenWorldSystem, WorldEvents);
    DOREPLIFETIME(UOpenWorldSystem, ActiveEvents);
    DOREPLIFETIME(UOpenWorldSystem, CurrentWeather);
    DOREPLIFETIME(UOpenWorldSystem, CurrentTimeOfDay);
    DOREPLIFETIME(UOpenWorldSystem, WorldTime);
    DOREPLIFETIME(UOpenWorldSystem, DiscoveredLocations);
    DOREPLIFETIME(UOpenWorldSystem, DiscoveredPOIs);
    DOREPLIFETIME(UOpenWorldSystem, DiscoveredStories);
    DOREPLIFETIME(UOpenWorldSystem, UnlockedFastTravel);
}
