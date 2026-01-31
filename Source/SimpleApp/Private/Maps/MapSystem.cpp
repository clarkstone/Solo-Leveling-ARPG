#include "MapSystem.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

UMapSystem::UMapSystem()
{
    LastUpdateTime = 0.0f;
    bIsTraveling = false;
    CurrentDestination = TEXT("");
}

void UMapSystem::BeginPlay()
{
    Super::BeginPlay();
    Initialize();
}

void UMapSystem::Initialize()
{
    InitializeMapDatabase();
    LoadMapDatabase();
    
    UE_LOG(LogTemp, Warning, TEXT("Map System initialized"));
}

void UMapSystem::InitializeMapDatabase()
{
    // Initialize South Korea maps
    TArray<FMapData> SouthKoreaMaps;
    
    FMapData Seoul;
    Seoul.MapName = TEXT("Seoul");
    Seoul.MapDescription = TEXT("Capital city of South Korea and Hunter Association HQ");
    Seoul.MapType = EMapType::MT_City;
    Seoul.Region = EMapRegion::MR_SouthKorea;
    Seoul.MapCenter = FVector(0.0f, 0.0f, 0.0f);
    Seoul.MapSize = FVector(10000.0f, 10000.0f, 1000.0f);
    Seoul.MapScale = 1.0f;
    Seoul.bIsInstanced = true;
    
    // Add locations
    FMapLocation HunterAssociation;
    HunterAssociation.LocationName = TEXT("Hunter Association HQ");
    HunterAssociation.Location = FVector(1000.0f, 1000.0f, 0.0f);
    HunterAssociation.Region = EMapRegion::MR_SouthKorea;
    HunterAssociation.MapType = EMapType::MT_City;
    HunterAssociation.RequiredLevel = 1;
    HunterAssociation.bIsUnlocked = true;
    HunterAssociation.bIsFastTravel = true;
    HunterAssociation.NPCs.Add(TEXT("Guild Master"));
    Seoul.Locations.Add(HunterAssociation);
    
    FMapLocation JinWooHome;
    JinWooHome.LocationName = TEXT("Jin-Woo's Home");
    JinWooHome.Location = FVector(-500.0f, -500.0f, 0.0f);
    JinWooHome.Region = EMapRegion::MR_SouthKorea;
    JinWooHome.MapType = EMapType::MT_Village;
    JinWooHome.RequiredLevel = 1;
    JinWooHome.bIsUnlocked = true;
    JinWooHome.bIsFastTravel = true;
    Seoul.Locations.Add(JinWooHome);
    
    Seoul.Locations.Add(HunterAssociation);
    SouthKoreaMaps.Add(Seoul);
    MapsByRegion.Add(EMapRegion::MR_SouthKorea, SouthKoreaMaps);
    
    // Initialize Japan maps
    TArray<FMapType> JapanMaps;
    
    FMapData Tokyo;
    Tokyo.MapName = TEXT("Tokyo");
    Tokyo.MapDescription = TEXT("Capital city of Japan and regional hunter hub");
    Tokyo.MapType = EMapType::MT_City;
    Tokyo.Region = EMapRegion::MR_Japan;
    Tokyo.MapCenter = FVector(20000.0f, 0.0f, 0.0f);
    Tokyo.MapSize = FVector(8000.0f, 8000f, 1000.0f);
    Tokyo.MapScale = 1.0f;
    Tokyo.bIsInstanced = true;
    Tokyo.bIsUnlocked = false;
    
    JapanMaps.Add(Tokyo);
    MapsByRegion.Add(EMapRegion::MR_Japan, JapanMaps);
    
    // Initialize China maps
    TArray<FMapType> ChinaMaps;
    
    FMapData Beijing;
    Beijing.MapName = TEXT("Beijing");
    Beijing.MapDescription = TEXT("Capital city of China and regional hunter hub");
    Beijing.MapType = EMapType::MT_City;
    Beijing.Region = EMapRegion::MR_China;
    Beijing.MapCenter = FVector(-20000.0f, 0.0f, 0.0f);
    Beijing.MapSize = FVector(8000.0f, 8000.0f, 1000.0f);
    Beijing.MapScale = 1.0f;
    Beijing.bIsInstanced = true;
    Beijing.bIsUnlocked = false;
    
    ChinaMaps.Add(Beijing);
    MapsByRegion.Add(EMapRegion::MR_China, ChinaMaps);
    
    // Initialize Europe maps
    TArray<FMapType> EuropeMaps;
    
    FMapData London;
    London.MapName = TEXT("London");
    London.MapDescription = TEXT("Capital city of Europe and regional hunter hub");
    London.MapType = EMapType::MT_City;
    London.Region = EMapRegion::MR_Europe;
    London.MapCenter = FVector(0.0f, 20000.0f, 0.0f);
    London.MapSize = FVector(6000.0f, 6000.0f, 1000.0f);
    London.MapScale = 1.0f;
    London.bIsInstanced = true;
    London.bIsUnlocked = false;
    
    EuropeMaps.Add(London);
    MapsByRegion.Add(EMapRegion::MR_Europe, EuropeMaps);
    
    // Initialize America maps
    TArray<FMapType> AmericaMaps;
    
    FMapData NewYork;
    NewYork.MapName = TEXT("New York");
    NewYork.MapDescription = TEXT("Capital city of America and regional hunter hub");
    NewYork.MapType = EMapType::MT_City;
    NewYork.Region = EMapRegion::MR_America;
    NewYork.MapCenter = FVector(-10000.0f, -20000.0f, 0.0f);
    NewYork.MapSize = FVector(6000.0f, 6000f, 1000.0f);
    NewYork.MapScale = 1.0f;
    NewYork.bIsInstanced = true;
    NewYork.bIsUnlocked = false;
    
    AmericaMaps.Add(NewYork);
    MapsByRegion.Add(EMapRegion::MR_America, AmericaMaps);
    
    UE_LOG(LogTemp, Warning, TEXT("Map database initialized"));
}

void UMapSystem::RegisterMap(FString MapID, FMapData MapData)
{
    MapDatabase.Add(MapID, MapData);
    
    // Add to region mapping
    MapsByRegion.FindOrAdd(MapData.Region, TArray<FMapData>()).Add(MapData);
    
    UE_LOG(LogTemp, Warning, TEXT("Map registered: %s"), *MapID);
}

void UMapSystem::TravelToLocation(FString MapID, FString LocationID)
{
    if (MapDatabase.Contains(MapID))
    {
        FMapData MapData = MapDatabase[MapID];
        
        // Find location
        for (const FMapLocation& Location : MapData.Locations)
        {
            if (Location.LocationName == LocationID)
            {
                // Check if location is unlocked
                if (Location.bIsUnlocked)
                {
                    // Check if map is unlocked
                    if (MapData.bIsUnlocked || MapData.MapType == EMapType::MT_City)
                    {
                        // Travel to location
                        CurrentDestination = LocationID;
                        bIsTraveling = true;
                        
                        UE_LOG(LogTemp, Warning, TEXT("Traveling to: %s in %s"), *LocationID, *MapID);
                        
                        // This would trigger travel animation and location loading
                        OnLocationDiscovered.Broadcast(LocationID);
                        
                        return;
                    }
                }
            }
        }
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Cannot travel to: %s in %s"), *LocationID, *MapID);
}

void UMapSystem::FastTravel(FString LocationID)
{
    if (CanFastTravel(LocationID))
    {
        // Fast travel logic
        UE_LOG(LogTemp, Warning, TEXT("Fast traveling to: %s"), *LocationID);
    }
}

bool UMapSystem::CanFastTravel(FString LocationID)
{
    return FastTravelUnlocked.Contains(LocationID);
}

TArray<FString> UMapSystem::GetAvailableFastTravelLocations()
{
    TArray<FString> AvailableLocations;
    
    for (const auto& Pair : FastTravelUnlocked)
    {
        if (Pair.Value)
        {
            AvailableLocations.Add(Pair.Key);
        }
    }
    
    return AvailableLocations;
}

void UMapSystem::DiscoverLocation(FString LocationID)
{
    // Mark location as discovered
    for (auto& MapPair : MapDatabase)
    {
        FMapData& MapData = MapPair.Value;
        
        for (FMapLocation& Location : MapData.Locations)
        {
            if (Location.LocationName == LocationID)
            {
                Location.bIsUnlocked = true;
                OnLocationDiscovered.Broadcast(LocationID);
                
                UE_LOG(LogTemp, Warning, TEXT("Location discovered: %s"), *LocationID);
                return;
            }
        }
    }
}

void UMapSystem::DiscoverMap(FString MapID)
{
    if (MapDatabase.Contains(MapID))
    {
        FMapData& MapData = MapDatabase[MapID];
        MapData.bIsUnlocked = true;
        
        OnMapDiscovered.Broadcast(MapID);
        
        UE_LOG(LogTemp, Warning, TEXT("Map discovered: %s"), *MapID);
    }
}

void UMapSystem::UnlockLocation(FString LocationID)
{
    // Unlock location for fast travel
    FastTravelUnlocked.Add(LocationID, true);
    
    OnLocationUnlocked.Broadcast(LocationID);
    
    UE_LOG(LogTemp, Warning, TEXT("Location unlocked: %s"), *LocationID);
}

void UMapSystem::UnlockMap(FString MapID)
{
    if (MapDatabase.Contains(MapID))
    {
        FMapData& MapData = MapDatabase[MapID];
        MapData.bIsUnlocked = true;
        
        OnMapUnlocked.Broadcast(MapID);
        
        UE_LOG(LogTemp, Warning, TEXT("Map unlocked: %s"), *MapID);
    }
}

void UMapSystem::OnWorldEventTriggered(FWorldEventData EventData)
{
    // Update map based on world events
    if (EventData.EventName == TEXT("GateOutbreak"))
    {
        // Add temporary dungeon location to map
        FString DungeonID = TEXT("Dungeon_") + FString::FromInt(FMath::RandRange(1000, 9999));
        
        FMapLocation DungeonLocation;
        DungeonLocation.LocationName = TEXT("Emergency Gate");
        DungeonLocation.Location = EventData.EventLocation;
        DungeonLocation.Region = EMapRegion::MR_SouthKorea;
        DungeonLocation.MapType = EMapType::MT_Dungeon;
        DungeonLocation.RequiredLevel = EventData.EventRadius / 100.0f;
        DungeonLocation.bIsUnlocked = true;
        DungeonLocation.bIsFastTravel = false;
        
        // Add to Seoul map
        if (MapDatabase.Contains(TEXT("Seoul")))
        {
            FMapData& SeoulMap = MapDatabase[TEXT("Seoul")];
            SeoulMap.Locations.Add(DungeonLocation);
        }
        
        UE_LOG(LogTemp, Warning, TEXT("Dungeon location added to map: %s"), *DungeonLocation.LocationName);
    }
}

void UMapSystem::OnPlayerLevelUp(int32 NewLevel)
{
    // Unlock new locations based on level
    if (NewLevel >= 10)
    {
        UnlockLocation(TEXT("Tokyo"));
    }
    
    if (NewLevel >= 20)
    {
        UnlockLocation(TEXT("Beijing"));
    }
    
    if (NewLevel >= 30)
    {
        UnlockLocation(TEXT("London"));
    }
    
    if (NewLevel >= 40)
    {
        UnlockLocation(TEXT("New York"));
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Map updated for player level: %d"), NewLevel);
}

void UMapSystem::OnQuestCompleted(FString QuestID)
{
    // Unlock quest-related locations
    UE_LOG(LogTemp, Warning, TEXT("Map updated for quest completion: %s"), *QuestID);
}

FMapData UMapSystem::GetMapData(FString MapID)
{
    if (MapDatabase.Contains(MapID))
    {
        return MapDatabase[MapID];
    }
    
    return FMapData();
}

TArray<FMapData> UMapSystem::GetMapsByRegion(EMapRegion Region)
{
    if (MapsByRegion.Contains(Region))
    {
        return MapsByRegion[Region];
    }
    
    return TArray<FMapData>();
}

void UMapSystem::LoadMapDatabase()
{
    // Load map data from files or database
    UE_LOG(LogTemp, Warning, TEXT("Loading map database..."));
}

void UMapSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    UpdateMapStates();
    ProcessMapEvents();
}

void UMapSystem::UpdateMapStates()
{
    // Update map states and fast travel system
    UpdateFastTravelSystem();
    UpdateMapRevealSystem();
}

void UMapSystem::UpdateFastTravelSystem()
{
    // Update fast travel costs based on distance and level
    for (auto& Pair : FastTravelCosts)
    {
        FString LocationID = Pair.Key;
        TMap<FString, float>& Costs = Pair.Value;
        
        for (auto& CostPair : Costs)
        {
            FString TargetLocationID = CostPair.Key;
            float& Cost = CostPair.Value;
            
            // Calculate cost based on distance
            if (MapDatabase.Contains(LocationID) && MapDatabase.Contains(TargetLocationID))
            {
                FVector Location1 = MapDatabase[LocationID].MapCenter;
                FVector Location2 = MapDatabase[TargetLocationID].MapCenter;
                float Distance = FVector::Dist(Location1, Location2);
                
                Cost = Distance / 1000.0f; // Cost per 1000 units
            }
        }
    }
}

void UMapSystem::UpdateMapRevealSystem()
{
    // Update map revealed percentage
    for (auto& Pair : MapRevealedPercentage)
    {
        FString MapID = Pair.Key;
        float& RevealedPercentage = Pair.Value;
        
        if (MapDatabase.Contains(MapID))
        {
            FMapData& MapData = MapDatabase[MapID];
            int32 TotalLocations = MapData.Locations.Num();
            int32 UnlockedLocations = 0;
            
            for (const FMapLocation& Location : MapData.Locations)
            {
                if (Location.bIsUnlocked)
                {
                    UnlockedLocations++;
                }
            }
            
            RevealedPercentage = (float)UnlockedLocations / TotalLocations * 100.0f;
        }
    }
}
