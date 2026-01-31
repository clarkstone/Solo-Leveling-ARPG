#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "SoloLevelingCharacter.generated.h"

UENUM(BlueprintType)
enum class EWeatherType : uint8
{
    WT_Clear,
    WT_Cloudy,
    WT_Rain,
    WT_Storm,
    WT_Snow,
    WT_Fog,
    WT_MagicalStorm
};

UENUM(BlueprintType)
enum class ESeason : uint8
{
    ES_Spring,
    ES_Summer,
    ES_Autumn,
    ES_Winter
};

USTRUCT(BlueprintType)
struct FWorldEventData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString EventName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString EventDescription;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector EventLocation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float EventRadius;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float EventDuration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsGlobalEvent;
};

USTRUCT(BlueprintType)
struct FDungeonConfig
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 DungeonRank;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString DungeonTheme;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MinRooms;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxRooms;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bHasBoss;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> RequiredPowerSystems;
};

USTRUCT(BlueprintType)
struct FBiomeData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString BiomeName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EWeatherType DefaultWeather;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    ESeason DefaultSeason;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> NativeMonsters;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> Resources;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Temperature;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Humidity;
};

UCLASS()
class SIMPLEAPP_API UWorldEventManager : public UActorComponent
{
    GENERATED_BODY()

public:
    UWorldEventManager();

    // World State Management
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "World")
    EWeatherType CurrentWeather;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "World")
    ESeason CurrentSeason;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "World")
    float WorldTimeScale;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "World")
    float CurrentWorldTime;

    // Dungeon System
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dungeon")
    bool bIsInDungeon;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dungeon")
    int32 CurrentDungeonRank;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dungeon")
    FString CurrentDungeonTheme;

    // World Events
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Events")
    TArray<FWorldEventData> ActiveEvents;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Events")
    TArray<FWorldEventData> RecentEvents;

    // Monster Territories
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Monsters")
    TMap<FString, FVector> MonsterTerritories;

    // Dynamic World Properties
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World")
    float DayLength;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World")
    float NightLength;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World")
    bool bHasDynamicWeather;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World")
    float WeatherChangeFrequency;

    // Override UActorComponent functions
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Initialization
    UFUNCTION(BlueprintCallable, Category = "World")
    void Initialize();

    // World Time Management
    UFUNCTION(BlueprintCallable, Category = "World")
    void UpdateWorldTime(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "World")
    void SetTimeScale(float NewScale);

    UFUNCTION(BlueprintCallable, Category = "World")
    bool IsDaytime();

    UFUNCTION(BlueprintCallable, Category = "World")
    bool IsNighttime();

    // Weather System
    UFUNCTION(BlueprintCallable, Category = "World")
    void ChangeWeather(EWeatherType NewWeather);

    UFUNCTION(BlueprintCallable, Category = "World")
    void UpdateWeatherSystem(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "World")
    void TriggerWeatherEvent(EWeatherType EventType);

    // Season System
    UFUNCTION(BlueprintCallable, Category = "World")
    void ChangeSeason(ESeason NewSeason);

    UFUNCTION(BlueprintCallable, Category = "World")
    void UpdateSeasonSystem(float DeltaTime);

    // Dungeon System
    UFUNCTION(BlueprintCallable, Category = "Dungeon")
    void EnterDungeon(FDungeonConfig DungeonConfig);

    UFUNCTION(BlueprintCallable, Category = "Dungeon")
    void ExitDungeon();

    UFUNCTION(BlueprintCallable, Category = "Dungeon")
    void GenerateDungeon(FDungeonConfig Config);

    UFUNCTION(BlueprintCallable, Category = "Dungeon")
    void UpdateDungeonState(float DeltaTime);

    // World Events
    UFUNCTION(BlueprintCallable, Category = "Events")
    void TriggerWorldEvent(FWorldEventData EventData);

    UFUNCTION(BlueprintCallable, Category = "Events")
    void UpdateWorldEvents(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "Events")
    void ProcessEventConsequences(FWorldEventData EventData);

    // Monster Territory System
    UFUNCTION(BlueprintCallable, Category = "Monsters")
    void UpdateMonsterTerritories();

    UFUNCTION(BlueprintCallable, Category = "Monsters")
    void SpawnMonsterInTerritory(FString TerritoryName, FString MonsterType);

    UFUNCTION(BlueprintCallable, Category = "Monsters")
    void ClearMonsterTerritory(FString TerritoryName);

    // Environmental Effects
    UFUNCTION(BlueprintCallable, Category = "Environment")
    void ApplyWeatherEffects();

    UFUNCTION(BlueprintCallable, Category = "Environment")
    void ApplySeasonalEffects();

    UFUNCTION(BlueprintCallable, Category = "Environment")
    void UpdateEnvironmentalEffects(float DeltaTime);

    // World Generation
    UFUNCTION(BlueprintCallable, Category = "Generation")
    void GenerateBiome(FBiomeData& Biome, FVector2D Coordinates);

    UFUNCTION(BlueprintCallable, Category = "Generation")
    void PlaceDungeonGates(TArray<FVector>& GateLocations);

    UFUNCTION(BlueprintCallable, Category = "Generation")
    void GenerateMonsterTerritories(TArray<FMonsterTerritory>& Territories);

    // Events
    UPROPERTY(BlueprintAssignable, Category = "World Events")
    FOnDungeonEntered OnDungeonEntered;

    UPROPERTY(BlueprintAssignable, Category = "World Events")
    FOnDungeonExited OnDungeonExited;

    UPROPERTY(BlueprintAssignable, Category = "World Events")
    FOnWorldEventTriggered OnWorldEventTriggered;

    UPROPERTY(BlueprintAssignable, Category = "World Events")
    FOnWeatherChanged OnWeatherChanged;

    UPROPERTY(BlueprintAssignable, Category = "World Events")
    FOnSeasonChanged OnSeasonChanged;

protected:
    // Internal Systems
    void InitializeWeatherSystem();
    void InitializeSeasonSystem();
    void InitializeDungeonSystem();
    void InitializeEventSystem();

    // Weather Effects
    void ApplyRainEffects();
    void ApplyStormEffects();
    void ApplySnowEffects();
    void ApplyFogEffects();
    void ApplyMagicalStormEffects();

    // Seasonal Effects
    void ApplySpringEffects();
    void ApplySummerEffects();
    void ApplyAutumnEffects();
    void ApplyWinterEffects();

    // Event Management
    void ScheduleRandomEvent();
    void ProcessGlobalEvent(FWorldEventData& Event);
    void ProcessLocalEvent(FWorldEventData& Event);

private:
    // Internal State
    float LastWeatherChangeTime;
    float LastSeasonChangeTime;
    float LastEventTime;
    float WeatherChangeTimer;
    float SeasonChangeTimer;
    float EventTimer;

    // Time Management
    float CurrentDayTime;
    int32 CurrentDay;
    int32 CurrentMonth;
    int32 CurrentYear;

    // Weather System
    TArray<EWeatherType> WeatherPatterns;
    int32 CurrentWeatherPattern;

    // Event System
    TArray<FWorldEventData> ScheduledEvents;
    TArray<FWorldEventData> AvailableEvents;

    // Helper Functions
    void CalculateTimeOfDay();
    void UpdateDayNightCycle();
    void DetermineWeatherPattern();
    void DetermineSeasonalChanges();
    void UpdateMonsterBehavior();
};
