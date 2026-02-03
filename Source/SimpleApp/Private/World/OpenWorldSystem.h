#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "OpenWorldSystem.generated.h"

UENUM(BlueprintType)
enum class EBiomeType : uint8
{
    BT_Forest = 0,
    BT_Mountain,
    BT_Desert,
    BT_Swamp,
    BT_Tundra,
    BT_Volcanic,
    BT_Ocean,
    BT_Island,
    BT_Plains,
    BT_Jungle,
    BT_Cursed,
    BT_Holy,
    BT_Abyssal,
    BT_Celestial,
    BT_Shadow,
    BT_Custom
};

UENUM(BlueprintType)
enum class EWeatherType : uint8
{
    WT_Clear = 0,
    WT_Cloudy,
    WT_LightRain,
    WT_HeavyRain,
    WT_Thunderstorm,
    WT_Snow,
    WT_Blizzard,
    WT_Fog,
    TS_Mist,
    WT_Sandstorm,
    WT_AshFall,
    WT_MagicalStorm,
    WT_Custom
};

UENUM(BlueprintType)
enum class ETimeOfDay : uint8
{
    TOD_Dawn = 0,
    TOD_Morning,
    TOD_Noon,
    TOD_Afternoon,
    TOD_Dusk,
    TOD_Evening,
    TOD_Night,
    TOD_Midnight
};

UENUM(BlueprintType)
enum class EPointOfInterestType : uint8
{
    POI_Village = 0,
    POI_City,
    POI_Dungeon,
    POI_Ruin,
    POI_Cave,
    POI_Fortress,
    POI_Temple,
    POI_Shrine,
    POI_Camp,
    POI_Merchant,
    POI_QuestGiver,
    POI_BossArena,
    POI_HiddenArea,
    POI_Landmark,
    POI_Resource,
    POI_Custom
};

USTRUCT(BlueprintType)
struct FWorldLocation
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Location")
    FString LocationName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Location")
    FVector WorldPosition;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Location")
    FRotator WorldRotation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Location")
    EBiomeType Biome;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Location")
    EWeatherType CurrentWeather;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Location")
    ETimeOfDay TimeOfDay;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Location")
    bool bIsDiscovered;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Location")
    bool bIsFastTravelUnlocked;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Location")
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Location")
    TArray<FString> ConnectedLocations;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Location")
    int32 RecommendedLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Location")
    TArray<FString> AvailableQuests;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Location")
    TArray<FString> AvailableNPCs;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Location")
    UTexture2D* MapIcon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Location")
    bool bHasStoryEvent;
};

USTRUCT(BlueprintType)
struct FPointOfInterest
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point of Interest")
    FString POIName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point of Interest")
    EPointOfInterestType POIType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point of Interest")
    FVector Location;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point of Interest")
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point of Interest")
    bool bIsDiscovered;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point of Interest")
    bool bIsActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point of Interest")
    bool bHasQuest;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point of Interest")
    FString AssociatedQuest;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point of Interest")
    TArray<FString> Loot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point of Interest")
    TArray<FString> Enemies;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point of Interest")
    FString EnvironmentalStory;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point of Interest")
    UTexture2D* Icon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point of Interest")
    bool bIsHidden;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point of Interest")
    FString UnlockRequirement;
};

USTRUCT(BlueprintType)
struct FEnvironmentalStory
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environmental Story")
    FString StoryID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environmental Story")
    FString Location;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environmental Story")
    FString StoryText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environmental Story")
    TArray<FString> Clues;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environmental Story")
    TArray<FString> RelatedQuests;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environmental Story")
    bool bIsDiscovered;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environmental Story")
    bool bHasLoreItem;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Environmental Story")
    FString LoreItemID;
};

USTRUCT(BlueprintType)
struct FWorldEvent
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Event")
    FString EventName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Event")
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Event")
    FVector EventLocation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Event")
    EBiomeType Biome;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Event")
    bool bIsActive;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Event")
    float Duration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Event")
    TArray<FString> Participants;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Event")
    TArray<FString> Rewards;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Event")
    FString EventType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Event")
    bool bIsRandomEvent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Event")
    float TriggerChance;
};

UCLASS(BlueprintType, Blueprintable)
class SIMPLEAPP_API UOpenWorldSystem : public UActorComponent
{
    GENERATED_BODY()

public:
    UOpenWorldSystem();

    // World Events
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLocationDiscovered, const FWorldLocation&, Location);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPOIDiscovered, const FPointOfInterest&, POI);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeatherChanged, EWeatherType, NewWeather);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimeOfDayChanged, ETimeOfDay, NewTimeOfDay);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWorldEventTriggered, const FWorldEvent&, WorldEvent);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnvironmentalStoryFound, const FEnvironmentalStory&, Story);

    UPROPERTY(BlueprintAssignable, Category = "Open World Events")
    FOnLocationDiscovered OnLocationDiscovered;

    UPROPERTY(BlueprintAssignable, Category = "Open World Events")
    FOnPOIDiscovered OnPOIDiscovered;

    UPROPERTY(BlueprintAssignable, Category = "Open World Events")
    FOnWeatherChanged OnWeatherChanged;

    UPROPERTY(BlueprintAssignable, Category = "Open World Events")
    FOnTimeOfDayChanged OnTimeOfDayChanged;

    UPROPERTY(BlueprintAssignable, Category = "Open World Events")
    FOnWorldEventTriggered OnWorldEventTriggered;

    UPROPERTY(BlueprintAssignable, Category = "Open World Events")
    FOnEnvironmentalStoryFound OnEnvironmentalStoryFound;

    // Override UActorComponent functions
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // World Management
    UFUNCTION(BlueprintCallable, Category = "Open World")
    void InitializeOpenWorld();

    UFUNCTION(BlueprintCallable, Category = "Open World")
    TArray<FWorldLocation> GetWorldLocations() const;

    UFUNCTION(BlueprintCallable, Category = "Open World")
    TArray<FWorldLocation> GetDiscoveredLocations() const;

    UFUNCTION(BlueprintCallable, Category = "Open World")
    FWorldLocation GetLocation(const FString& LocationName) const;

    UFUNCTION(BlueprintCallable, Category = "Open World")
    bool DiscoverLocation(const FString& LocationName);

    UFUNCTION(BlueprintCallable, Category = "Open World")
    bool IsLocationDiscovered(const FString& LocationName) const;

    UFUNCTION(BlueprintCallable, Category = "Open World")
    bool UnlockFastTravel(const FString& LocationName);

    UFUNCTION(BlueprintCallable, Category = "Open World")
    bool CanFastTravelTo(const FString& LocationName) const;

    UFUNCTION(BlueprintCallable, Category = "Open World")
    bool FastTravelToLocation(const FString& LocationName);

    // Points of Interest
    UFUNCTION(BlueprintCallable, Category = "Open World")
    TArray<FPointOfInterest> GetPointsOfInterest(const FString& LocationName) const;

    UFUNCTION(BlueprintCallable, Category = "Open World")
    TArray<FPointOfInterest> GetDiscoveredPOIs(const FString& LocationName) const;

    UFUNCTION(BlueprintCallable, Category = "Open World")
    bool DiscoverPOI(const FString& POIName);

    UFUNCTION(BlueprintCallable, Category = "Open World")
    FPointOfInterest GetPOI(const FString& POIName) const;

    UFUNCTION(BlueprintCallable, Category = "Open World")
    bool IsPOIDiscovered(const FString& POIName) const;

    UFUNCTION(BlueprintCallable, Category = "Open World")
    TArray<FPointOfInterest> GetNearbyPOIs(const FVector& PlayerPosition, float Radius) const;

    // Environmental Storytelling
    UFUNCTION(BlueprintCallable, Category = "Open World")
    TArray<FEnvironmentalStory> GetEnvironmentalStories(const FString& LocationName) const;

    UFUNCTION(BlueprintCallable, Category = "Open World")
    bool DiscoverEnvironmentalStory(const FString& StoryID);

    UFUNCTION(BlueprintCallable, Category = "Open World")
    FEnvironmentalStory GetEnvironmentalStory(const FString& StoryID) const;

    UFUNCTION(BlueprintCallable, Category = "Open World")
    bool HasEnvironmentalStory(const FString& LocationName) const;

    UFUNCTION(BlueprintCallable, Category = "Open World")
    void AddEnvironmentalClue(const FString& LocationName, const FString& Clue);

    // Weather System
    UFUNCTION(BlueprintCallable, Category = "Open World")
    void SetWeather(EWeatherType NewWeather);

    UFUNCTION(BlueprintCallable, Category = "Open World")
    EWeatherType GetCurrentWeather() const;

    UFUNCTION(BlueprintCallable, Category = "Open World")
    void ChangeWeatherRandomly();

    UFUNCTION(BlueprintCallable, Category = "Open World")
    TArray<EWeatherType> GetAvailableWeatherTypes(EBiomeType Biome) const;

    UFUNCTION(BlueprintCallable, Category = "Open World")
    bool CanWeatherChange(EBiomeType Biome) const;

    // Time System
    UFUNCTION(BlueprintCallable, Category = "Open World")
    void SetTimeOfDay(ETimeOfDay NewTimeOfDay);

    UFUNCTION(BlueprintCallable, Category = "Open World")
    ETimeOfDay GetCurrentTimeOfDay() const;

    UFUNCTION(BlueprintCallable, Category = "Open World")
    void AdvanceTime(float Hours);

    UFUNCTION(BlueprintCallable, Category = "Open World")
    float GetWorldTime() const;

    UFUNCTION(BlueprintCallable, Category = "Open World")
    bool IsNightTime() const;

    UFUNCTION(BlueprintCallable, Category = "Open World")
    bool IsDayTime() const;

    // Dynamic Events
    UFUNCTION(BlueprintCallable, Category = "Open World")
    void TriggerWorldEvent(const FString& EventName);

    UFUNCTION(BlueprintCallable, Category = "Open World")
    TArray<FWorldEvent> GetActiveEvents() const;

    UFUNCTION(BlueprintCallable, Category = "Open World")
    TArray<FWorldEvent> GetAvailableEvents(const FString& LocationName) const;

    UFUNCTION(BlueprintCallable, Category = "Open World")
    void UpdateRandomEvents();

    UFUNCTION(BlueprintCallable, Category = "Open World")
    void CompleteWorldEvent(const FString& EventName);

    // Exploration
    UFUNCTION(BlueprintCallable, Category = "Open World")
    float GetExplorationProgress() const;

    UFUNCTION(BlueprintCallable, Category = "Open World")
    int32 GetDiscoveredLocationCount() const;

    UFUNCTION(BlueprintCallable, Category = "Open World")
    int32 GetTotalLocationCount() const;

    UFUNCTION(BlueprintCallable, Category = "Open World")
    TArray<FString> GetHiddenLocations() const;

    UFUNCTION(BlueprintCallable, Category = "Open World")
    bool RevealHiddenLocation(const FString& LocationName);

    // World Interaction
    UFUNCTION(BlueprintCallable, Category = "Open World")
    void OnPlayerEnterLocation(const FString& LocationName);

    UFUNCTION(BlueprintCallable, Category = "Open World")
    void OnPlayerExitLocation(const FString& LocationName);

    UFUNCTION(BlueprintCallable, Category = "Open World")
    void OnPlayerInteractWithPOI(const FString& POIName);

    UFUNCTION(BlueprintCallable, Category = "Open World")
    void OnPlayerPickupLoreItem(const FString& LoreItemID);

    // Save/Load
    UFUNCTION(BlueprintCallable, Category = "Open World")
    void SaveWorldState();

    UFUNCTION(BlueprintCallable, Category = "Open World")
    void LoadWorldState();

    UFUNCTION(BlueprintCallable, Category = "Open World")
    void ResetWorldState();

protected:
    // Internal Functions
    void InitializeWorldLocations();
    void InitializePointsOfInterest();
    void InitializeEnvironmentalStories();
    void InitializeWorldEvents();
    void UpdateWeatherSystem(float DeltaTime);
    void UpdateTimeSystem(float DeltaTime);
    void UpdateDynamicEvents(float DeltaTime);
    void ProcessWorldEvents();

private:
    // Internal State
    TArray<FWorldLocation> WorldLocations;
    TMap<FString, TArray<FPointOfInterest>> LocationPOIs;
    TArray<FEnvironmentalStory> EnvironmentalStories;
    TArray<FWorldEvent> WorldEvents;
    TArray<FWorldEvent> ActiveEvents;

    // World State
    EWeatherType CurrentWeather;
    ETimeOfDay CurrentTimeOfDay;
    float WorldTime;
    float WeatherChangeTimer;
    float TimeAdvanceTimer;
    float EventUpdateTimer;

    // Exploration Data
    TSet<FString> DiscoveredLocations;
    TSet<FString> DiscoveredPOIs;
    TSet<FString> DiscoveredStories;
    TSet<FString> UnlockedFastTravel;

    // Helper Functions
    FWorldLocation CreateWorldLocation(const FString& Name, EBiomeType Biome, FVector Position);
    FPointOfInterest CreatePointOfInterest(const FString& Name, EPointOfInterestType Type, FVector Location);
    FEnvironmentalStory CreateEnvironmentalStory(const FString& ID, const FString& Location, const FString& Story);
    FWorldEvent CreateWorldEvent(const FString& Name, EBiomeType Biome, FVector Location);
    void NotifyLocationDiscovered(const FWorldLocation& Location);
    void NotifyPOIDiscovered(const FPointOfInterest& POI);
    void NotifyWeatherChanged(EWeatherType NewWeather);
    void NotifyTimeOfDayChanged(ETimeOfDay NewTimeOfDay);
    void NotifyWorldEventTriggered(const FWorldEvent& WorldEvent);
    void NotifyEnvironmentalStoryFound(const FEnvironmentalStory& Story);
    void UpdateLocationWeather(const FString& LocationName);
    void UpdateLocationTime(const FString& LocationName);
    bool ValidateLocation(const FString& LocationName) const;
    bool ValidatePOI(const FString& POIName) const;
    void SpawnWorldEvent(const FWorldEvent& WorldEvent);
    void DespawnWorldEvent(const FString& EventName);
    void ApplyWeatherEffects(EWeatherType Weather);
    void ApplyTimeEffects(ETimeOfDay TimeOfDay);
    void GenerateRandomWeather();
    void GenerateRandomEvent();
};
