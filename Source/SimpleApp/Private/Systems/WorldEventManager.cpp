#include "WorldEventManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "GameFramework/Character.h"
#include "Components/DirectionalLightComponent.h"
#include "Components/SkyLightComponent.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Particles/ParticleSystemComponent.h"

UWorldEventManager::UWorldEventManager()
{
    // Initialize world state
    CurrentWeather = EWeatherType::WT_Clear;
    CurrentSeason = ESeason::ES_Spring;
    WorldTimeScale = 1.0f;
    CurrentWorldTime = 6.0f; // Start at 6 AM
    
    // Initialize dungeon state
    bIsInDungeon = false;
    CurrentDungeonRank = 0;
    CurrentDungeonTheme = TEXT("Default");
    
    // Initialize dynamic world properties
    DayLength = 24.0f; // 24 minutes = 24 hours
    NightLength = 24.0f;
    bHasDynamicWeather = true;
    WeatherChangeFrequency = 300.0f; // 5 minutes
    
    // Initialize internal state
    LastWeatherChangeTime = 0.0f;
    LastSeasonChangeTime = 0.0f;
    LastEventTime = 0.0f;
    WeatherChangeTimer = 0.0f;
    SeasonChangeTimer = 0.0f;
    EventTimer = 0.0f;
    
    // Initialize time management
    CurrentDayTime = 6.0f;
    CurrentDay = 1;
    CurrentMonth = 1;
    CurrentYear = 2026;
    
    // Initialize weather system
    CurrentWeatherPattern = 0;
}

void UWorldEventManager::BeginPlay()
{
    Super::BeginPlay();
    
    Initialize();
    UE_LOG(LogTemp, Warning, TEXT("World Event Manager initialized"));
}

void UWorldEventManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    UpdateWorldTime(DeltaTime);
    UpdateWeatherSystem(DeltaTime);
    UpdateSeasonSystem(DeltaTime);
    UpdateDungeonState(DeltaTime);
    UpdateWorldEvents(DeltaTime);
    UpdateEnvironmentalEffects(DeltaTime);
}

void UWorldEventManager::Initialize()
{
    InitializeWeatherSystem();
    InitializeSeasonSystem();
    InitializeDungeonSystem();
    InitializeEventSystem();
    
    // Set initial weather patterns
    WeatherPatterns.Add(EWeatherType::WT_Clear);
    WeatherPatterns.Add(EWeatherType::WT_Cloudy);
    WeatherPatterns.Add(EWeatherType::WT_Rain);
    WeatherPatterns.Add(EWeatherType::WT_Storm);
    
    // Schedule initial events
    ScheduleRandomEvent();
}

void UWorldEventManager::InitializeWeatherSystem()
{
    // Find and configure lighting components
    TArray<ULightComponent*> LightComponents;
    GetOwner()->GetComponents<ULightComponent>(LightComponents);
    
    for (ULightComponent* Light : LightComponents)
    {
        if (UDirectionalLightComponent* DirLight = Cast<UDirectionalLightComponent>(Light))
        {
            // Configure directional light for weather effects
            DirLight->SetIntensity(10.0f);
        }
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Weather system initialized"));
}

void UWorldEventManager::InitializeSeasonSystem()
{
    // Initialize seasonal effects
    ApplySeasonalEffects();
    
    UE_LOG(LogTemp, Warning, TEXT("Season system initialized"));
}

void UWorldEventManager::InitializeDungeonSystem()
{
    // Initialize dungeon generation parameters
    UE_LOG(LogTemp, Warning, TEXT("Dungeon system initialized"));
}

void UWorldEventManager::InitializeEventSystem()
{
    // Initialize available world events
    FWorldEventData GateOutbreak;
    GateOutbreak.EventName = TEXT("GateOutbreak");
    GateOutbreak.EventDescription = TEXT("A massive gate has appeared, threatening the nearby area!");
    GateOutbreak.EventRadius = 2000.0f;
    GateOutbreak.EventDuration = 600.0f;
    GateOutbreak.bIsGlobalEvent = false;
    AvailableEvents.Add(GateOutbreak);
    
    FWorldEventData MonsterInvasion;
    MonsterInvasion.EventName = TEXT("MonsterInvasion");
    MonsterInvasion.EventDescription = TEXT("Monsters are invading the city! All hunters must respond!");
    MonsterInvasion.EventRadius = 5000.0f;
    MonsterInvasion.EventDuration = 900.0f;
    MonsterInvasion.bIsGlobalEvent = true;
    AvailableEvents.Add(MonsterInvasion);
    
    UE_LOG(LogTemp, Warning, TEXT("Event system initialized with %d available events"), AvailableEvents.Num());
}

void UWorldEventManager::UpdateWorldTime(float DeltaTime)
{
    // Update world time
    CurrentWorldTime += DeltaTime * WorldTimeScale;
    
    // Handle day/night cycle
    if (CurrentWorldTime >= 24.0f)
    {
        CurrentWorldTime -= 24.0f;
        CurrentDay++;
        
        if (CurrentDay > 30)
        {
            CurrentDay = 1;
            CurrentMonth++;
            
            if (CurrentMonth > 12)
            {
                CurrentMonth = 1;
                CurrentYear++;
            }
        }
    }
    
    UpdateDayNightCycle();
}

void UWorldEventManager::UpdateDayNightCycle()
{
    bool bWasDaytime = IsDaytime();
    CurrentDayTime = CurrentWorldTime;
    
    // Update lighting based on time of day
    TArray<ULightComponent*> LightComponents;
    GetOwner()->GetComponents<ULightComponent>(LightComponents);
    
    for (ULightComponent* Light : LightComponents)
    {
        if (UDirectionalLightComponent* DirLight = Cast<UDirectionalLightComponent>(Light))
        {
            float LightIntensity = 1.0f;
            
            if (CurrentWorldTime >= 6.0f && CurrentWorldTime <= 18.0f)
            {
                // Daytime
                LightIntensity = 1.0f;
            }
            else if (CurrentWorldTime > 18.0f && CurrentWorldTime <= 20.0f)
            {
                // Sunset
                LightIntensity = FMath::Lerp(1.0f, 0.2f, (CurrentWorldTime - 18.0f) / 2.0f);
            }
            else if (CurrentWorldTime > 20.0f && CurrentWorldTime <= 22.0f)
            {
                // Night
                LightIntensity = 0.2f;
            }
            else
            {
                // Dawn
                LightIntensity = FMath::Lerp(0.2f, 1.0f, (CurrentWorldTime + 2.0f) / 4.0f);
            }
            
            DirLight->SetIntensity(LightIntensity * 10.0f);
        }
    }
    
    // Check for day/night transition
    bool bIsDaytimeNow = IsDaytime();
    if (bWasDaytime != bIsDaytimeNow)
    {
        UE_LOG(LogTemp, Warning, TEXT("Time changed from %s to %s"), bWasDaytime ? TEXT("day") : TEXT("night"), bIsDaytimeNow ? TEXT("day") : TEXT("night"));
        
        // Trigger day/night events
        if (bIsDaytimeNow)
        {
            // Daytime events
            UpdateMonsterBehavior();
        }
        else
        {
            // Nighttime events
            UpdateMonsterBehavior();
        }
    }
}

void UWorldEventManager::SetTimeScale(float NewScale)
{
    WorldTimeScale = FMath::Clamp(NewScale, 0.1f, 10.0f);
    UE_LOG(LogTemp, Warning, TEXT("World time scale set to: %.2f"), WorldTimeScale);
}

bool UWorldEventManager::IsDaytime()
{
    return CurrentWorldTime >= 6.0f && CurrentWorldTime <= 18.0f;
}

bool UWorldEventManager::IsNighttime()
{
    return !IsDaytime();
}

void UWorldEventManager::ChangeWeather(EWeatherType NewWeather)
{
    if (CurrentWeather != NewWeather)
    {
        EWeatherType OldWeather = CurrentWeather;
        CurrentWeather = NewWeather;
        
        UE_LOG(LogTemp, Warning, TEXT("Weather changed from %d to %d"), (int32)OldWeather, (int32)NewWeather);
        
        ApplyWeatherEffects();
        OnWeatherChanged.Broadcast(OldWeather, NewWeather);
        
        LastWeatherChangeTime = GetWorld()->GetTimeSeconds();
    }
}

void UWorldEventManager::UpdateWeatherSystem(float DeltaTime)
{
    if (!bHasDynamicWeather)
        return;
    
    WeatherChangeTimer += DeltaTime;
    
    // Check if it's time to change weather
    if (WeatherChangeTimer >= WeatherChangeFrequency)
    {
        WeatherChangeTimer = 0.0f;
        
        // Determine new weather pattern
        DetermineWeatherPattern();
        
        // Change weather based on pattern
        if (CurrentWeatherPattern < WeatherPatterns.Num())
        {
            ChangeWeather(WeatherPatterns[CurrentWeatherPattern]);
        }
    }
}

void UWorldEventManager::DetermineWeatherPattern()
{
    // Simple weather pattern determination
    CurrentWeatherPattern = (CurrentWeatherPattern + 1) % WeatherPatterns.Num();
    
    // Add some randomness
    if (FMath::FRand() < 0.3f)
    {
        CurrentWeatherPattern = FMath::RandRange(0, WeatherPatterns.Num() - 1);
    }
}

void UWorldEventManager::ApplyWeatherEffects()
{
    switch (CurrentWeather)
    {
        case EWeatherType::WT_Rain:
            ApplyRainEffects();
            break;
        case EWeatherType::WT_Storm:
            ApplyStormEffects();
            break;
        case EWeatherType::WT_Snow:
            ApplySnowEffects();
            break;
        case EWeatherType::WT_Fog:
            ApplyFogEffects();
            break;
        case EWeatherType::WT_MagicalStorm:
            ApplyMagicalStormEffects();
            break;
        default:
            // Clear weather - no special effects
            break;
    }
}

void UWorldEventManager::ApplyRainEffects()
{
    // Spawn rain particles
    // Reduce visibility
    // Make surfaces wet
    // Affect monster behavior (some monsters more aggressive in rain)
    
    UE_LOG(LogTemp, Warning, TEXT("Applying rain effects"));
    
    // Update fog for rain effect
    TArray<UActor*> FogActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FogActors);
    
    for (AActor* Actor : FogActors)
    {
        if (UExponentialHeightFogComponent* Fog = Actor->FindComponentByClass<UExponentialHeightFogComponent>())
        {
            Fog->SetFogDensity(FMath::Lerp(Fog->GetFogDensity(), 0.05f, 0.1f));
        }
    }
}

void UWorldEventManager::ApplyStormEffects()
{
    // Apply rain effects plus additional storm effects
    ApplyRainEffects();
    
    // Lightning effects
    // Thunder sound
    // Stronger wind
    // More aggressive monster behavior
    
    UE_LOG(LogTemp, Warning, TEXT("Applying storm effects"));
    
    // Reduce visibility further
    TArray<UActor*> FogActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FogActors);
    
    for (AActor* Actor : FogActors)
    {
        if (UExponentialHeightFogComponent* Fog = Actor->FindComponentByClass<UExponentialHeightFogComponent>())
        {
            Fog->SetFogDensity(FMath::Lerp(Fog->GetFogDensity(), 0.1f, 0.1f));
        }
    }
}

void UWorldEventManager::ApplySnowEffects()
{
    // Spawn snow particles
    // Reduce temperature
    // Add snow accumulation
    // Affect monster types (ice monsters appear more)
    
    UE_LOG(LogTemp, Warning, TEXT("Applying snow effects"));
    
    // Create fog effect for snow
    TArray<UActor*> FogActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FogActors);
    
    for (AActor* Actor : FogActors)
    {
        if (UExponentialHeightFogComponent* Fog = Actor->FindComponentByClass<UExponentialHeightFogComponent>())
        {
            Fog->SetFogDensity(FMath::Lerp(Fog->GetFogDensity(), 0.03f, 0.1f));
        }
    }
}

void UWorldEventManager::ApplyFogEffects()
{
    // Heavy fog reduces visibility significantly
    // Affects movement speed
    // Creates ambush opportunities
    
    UE_LOG(LogTemp, Warning, TEXT("Applying fog effects"));
    
    // Increase fog density
    TArray<UActor*> FogActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FogActors);
    
    for (AActor* Actor : FogActors)
    {
        if (UExponentialHeightFogComponent* Fog = Actor->FindComponentByClass<UExponentialHeightFogComponent>())
        {
            Fog->SetFogDensity(FMath::Lerp(Fog->GetFogDensity(), 0.15f, 0.1f));
        }
    }
}

void UWorldEventManager::ApplyMagicalStormEffects()
{
    // Apply storm effects plus magical effects
    ApplyStormEffects();
    
    // Magical particles
    // Reality distortion effects
    // Power system interference
    // Special monster appearances
    
    UE_LOG(LogTemp, Warning, TEXT("Applying magical storm effects"));
    
    // Create magical fog effect
    TArray<UActor*> FogActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FogActors);
    
    for (AActor* Actor : FogActors)
    {
        if (UExponentialHeightFogComponent* Fog = Actor->FindComponentByClass<UExponentialHeightFogComponent>())
        {
            Fog->SetFogDensity(FMath::Lerp(Fog->GetFogDensity(), 0.2f, 0.1f));
        }
    }
}

void UWorldEventManager::ChangeSeason(ESeason NewSeason)
{
    if (CurrentSeason != NewSeason)
    {
        ESeason OldSeason = CurrentSeason;
        CurrentSeason = NewSeason;
        
        UE_LOG(LogTemp, Warning, TEXT("Season changed from %d to %d"), (int32)OldSeason, (int32)NewSeason);
        
        ApplySeasonalEffects();
        OnSeasonChanged.Broadcast(OldSeason, NewSeason);
        
        LastSeasonChangeTime = GetWorld()->GetTimeSeconds();
    }
}

void UWorldEventManager::UpdateSeasonSystem(float DeltaTime)
{
    // Check for seasonal changes (every 30 in-game days)
    static int32 LastSeasonChangeDay = 0;
    
    if (CurrentDay != LastSeasonChangeDay && CurrentDay == 1)
    {
        LastSeasonChangeDay = CurrentDay;
        
        // Change season
        int32 NewSeasonIndex = ((int32)CurrentSeason + 1) % 4;
        ChangeSeason((ESeason)NewSeasonIndex);
    }
}

void UWorldEventManager::ApplySeasonalEffects()
{
    switch (CurrentSeason)
    {
        case ESeason::ES_Spring:
            ApplySpringEffects();
            break;
        case ESeason::ES_Summer:
            ApplySummerEffects();
            break;
        case ESeason::ES_Autumn:
            ApplyAutumnEffects();
            break;
        case ESeason::ES_Winter:
            ApplyWinterEffects();
            break;
    }
}

void UWorldEventManager::ApplySpringEffects()
{
    // New monster migrations
    // Increased spawn rates
    // Blooming vegetation
    // Mild weather patterns
    
    UE_LOG(LogTemp, Warning, TEXT("Applying spring effects"));
}

void UWorldEventManager::ApplySummerEffects()
{
    // Increased monster activity
    // Longer days
    // Hot weather
    // More outdoor events
    
    UE_LOG(LogTemp, Warning, TEXT("Applying summer effects"));
}

void UWorldEventManager::ApplyAutumnEffects()
{
    // Monster preparation for winter
    // Falling leaves
    // Harvest events
    // Mild weather
    
    UE_LOG(LogTemp, Warning, TEXT("Applying autumn effects"));
}

void UWorldEventManager::ApplyWinterEffects()
{
    // Reduced monster activity
    // Ice monsters appear more
    // Snow effects
    // Shorter days
    
    UE_LOG(LogTemp, Warning, TEXT("Applying winter effects"));
    
    // Ensure snow weather in winter
    if (CurrentWeather == EWeatherType::WT_Clear || CurrentWeather == EWeatherType::WT_Cloudy)
    {
        if (FMath::FRand() < 0.3f)
        {
            ChangeWeather(EWeatherType::WT_Snow);
        }
    }
}

void UWorldEventManager::EnterDungeon(FDungeonConfig DungeonConfig)
{
    bIsInDungeon = true;
    CurrentDungeonRank = DungeonConfig.DungeonRank;
    CurrentDungeonTheme = DungeonConfig.DungeonTheme;
    
    UE_LOG(LogTemp, Warning, TEXT("Entering Rank %d dungeon: %s"), CurrentDungeonRank, *CurrentDungeonTheme);
    
    OnDungeonEntered.Broadcast(CurrentDungeonRank);
    
    // Apply dungeon-specific effects
    // Disable weather effects inside dungeon
    bHasDynamicWeather = false;
    
    // Set dungeon lighting
    TArray<ULightComponent*> LightComponents;
    GetOwner()->GetComponents<ULightComponent>(LightComponents);
    
    for (ULightComponent* Light : LightComponents)
    {
        if (UDirectionalLightComponent* DirLight = Cast<UDirectionalLightComponent>(Light))
        {
            DirLight->SetIntensity(2.0f); // Dimmer lighting in dungeon
        }
    }
}

void UWorldEventManager::ExitDungeon()
{
    bIsInDungeon = false;
    CurrentDungeonRank = 0;
    CurrentDungeonTheme = TEXT("Default");
    
    UE_LOG(LogTemp, Warning, TEXT("Exiting dungeon"));
    
    OnDungeonExited.Broadcast();
    
    // Restore weather effects
    bHasDynamicWeather = true;
    
    // Restore normal lighting
    TArray<ULightComponent*> LightComponents;
    GetOwner()->GetComponents<ULightComponent>(LightComponents);
    
    for (ULightComponent* Light : LightComponents)
    {
        if (UDirectionalLightComponent* DirLight = Cast<UDirectionalLightComponent>(Light))
        {
            DirLight->SetIntensity(10.0f);
        }
    }
}

void UWorldEventManager::UpdateDungeonState(float DeltaTime)
{
    if (bIsInDungeon)
    {
        // Update dungeon-specific effects
        // Ambient sounds
        // Particle effects
        // Dynamic lighting changes
    }
}

void UWorldEventManager::TriggerWorldEvent(FWorldEventData EventData)
{
    ActiveEvents.Add(EventData);
    RecentEvents.Add(EventData);
    
    // Limit recent events history
    if (RecentEvents.Num() > 50)
    {
        RecentEvents.RemoveAt(0);
    }
    
    UE_LOG(LogTemp, Warning, TEXT("World event triggered: %s"), *EventData.EventName);
    
    OnWorldEventTriggered.Broadcast(EventData);
    
    // Process event consequences
    ProcessEventConsequences(EventData);
}

void UWorldEventManager::UpdateWorldEvents(float DeltaTime)
{
    // Update active events
    for (int32 i = ActiveEvents.Num() - 1; i >= 0; i--)
    {
        FWorldEventData& Event = ActiveEvents[i];
        Event.EventDuration -= DeltaTime;
        
        if (Event.EventDuration <= 0.0f)
        {
            // Event ended
            UE_LOG(LogTemp, Warning, TEXT("World event ended: %s"), *Event.EventName);
            ActiveEvents.RemoveAt(i);
        }
    }
    
    // Check for random events
    EventTimer += DeltaTime;
    if (EventTimer >= 600.0f) // Check every 10 minutes
    {
        EventTimer = 0.0f;
        ScheduleRandomEvent();
    }
}

void UWorldEventManager::ProcessEventConsequences(FWorldEventData EventData)
{
    if (EventData.bIsGlobalEvent)
    {
        ProcessGlobalEvent(EventData);
    }
    else
    {
        ProcessLocalEvent(EventData);
    }
}

void UWorldEventManager::ProcessGlobalEvent(FWorldEventData& Event)
{
    // Global events affect the entire world
    if (Event.EventName == TEXT("MonsterInvasion"))
    {
        // Spawn monsters in multiple locations
        // Alert all players
        // Trigger emergency response
        UE_LOG(LogTemp, Warning, TEXT("Processing global monster invasion event"));
    }
}

void UWorldEventManager::ProcessLocalEvent(FWorldEventData& Event)
{
    // Local events affect specific areas
    if (Event.EventName == TEXT("GateOutbreak"))
    {
        // Create dungeon gate at event location
        // Spawn monsters around gate
        // Alert nearby players
        UE_LOG(LogTemp, Warning, TEXT("Processing local gate outbreak event at location: %s"), *Event.EventLocation.ToString());
    }
}

void UWorldEventManager::ScheduleRandomEvent()
{
    if (AvailableEvents.Num() > 0 && FMath::FRand() < 0.3f) // 30% chance
    {
        int32 RandomIndex = FMath::RandRange(0, AvailableEvents.Num() - 1);
        FWorldEventData RandomEvent = AvailableEvents[RandomIndex];
        
        // Set random location for local events
        if (!RandomEvent.bIsGlobalEvent)
        {
            // Generate random location within world bounds
            RandomEvent.EventLocation = FVector(FMath::RandRange(-2000.0f, 2000.0f), 0.0f, FMath::RandRange(-2000.0f, 2000.0f));
        }
        
        TriggerWorldEvent(RandomEvent);
    }
}

void UWorldEventManager::UpdateMonsterTerritories()
{
    // Update monster territory boundaries
    // Handle territory conflicts
    // Spawn new monsters in empty territories
}

void UWorldEventManager::UpdateEnvironmentalEffects(float DeltaTime)
{
    // Update particle effects
    // Update sound effects
    // Update visual effects
    // Update physics effects
}

void UWorldEventManager::UpdateMonsterBehavior()
{
    // Update monster behavior based on time of day
    // Some monsters are more active at night
    // Some monsters only appear during certain weather
    
    TArray<AActor*> EnemyActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacter::StaticClass(), EnemyActors);
    
    for (AActor* Actor : EnemyActors)
    {
        // This would interface with the AI system
        // to update monster behavior based on current conditions
    }
}
