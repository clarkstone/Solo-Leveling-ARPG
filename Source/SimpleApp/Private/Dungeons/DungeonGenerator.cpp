#include "DungeonGenerator.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

UDungeonGenerator::UDungeonGenerator()
{
    LastGenerationTime = 0.0f;
    CurrentDungeonID = 0;
    bIsGenerating = false;
}

void UDungeonGenerator::BeginPlay()
{
    Super::BeginPlay();
    Initialize();
}

void UDungeonGenerator::Initialize()
{
    InitializeDungeonTemplates();
    InitializeGenerationAlgorithms();
    LoadDungeonTemplates();
    LoadDungeonContent();
    InitializeBiomeData();
    InitializeRankData();
    
    UE_LOG(LogTemp, Warning, TEXT("Dungeon Generator initialized"));
}

void UDungeonGenerator::InitializeDungeonTemplates()
{
    // Initialize E-Rank dungeon template
    FDungeonConfig ERankTemplate;
    ERankTemplate.DungeonType = EDungeonType::DT_Classic;
    ERankTemplate.DungeonRank = EDungeonRank::DR_E;
    ERankTemplate.Biome = EDungeonBiome::DB_Underground;
    ERankTemplate.MinRooms = 3;
    ERankTemplate.MaxRooms = 5;
    ERankTemplate.MinCorridors = 2;
    ERankTemplate.MaxCorridors = 4;
    ERankTemplate.Difficulty = 1.0f;
    ERankTemplate.bHasBoss = false;
    ERankTemplate.bHasSecretRooms = false;
    ERankTemplate.bHasTreasureRooms = false;
    ERankTemplate.bHasPuzzleRooms = false;
    DungeonTemplates.Add(EDungeonRank::DR_E, ERankTemplate);
    
    // Initialize D-Rank dungeon template
    FDungeonConfig DRankTemplate;
    DRankTemplate.DungeonType = EDungeonType::DT_Cave;
    DRankTemplate.DungeonRank = EDungeonRank::DR_D;
    DRankTemplate.Biome = EDungeonBiome::DB_Cavern;
    DRankTemplate.MinRooms = 5;
    DRankTemplate.MaxRooms = 8;
    DRankTemplate.MinCorridors = 4;
    DRankTemplate.MaxCorridors = 6;
    DRankTemplate.Difficulty = 2.0f;
    DRankTemplate.bHasBoss = false;
    DRankTemplate.bHasSecretRooms = true;
    DRankTemplate.bHasTreasureRooms = true;
    DRankTemplate.bHasPuzzleRooms = false;
    DungeonTemplates.Add(EDungeonRank::DR_D, DRankTemplate);
    
    // Initialize C-Rank dungeon template
    FDungeonConfig CRankTemplate;
    CRankTemplate.DungeonType = EDungeonType::DT_Forest;
    CRankTemplate.DungeonRank = EDungeonRank::DR_C;
    CRankTemplate.Biome = EDungeonBiome::DB_Forest;
    CRankTemplate.MinRooms = 8;
    CRankTemplate.MaxRooms = 12;
    CRankTemplate.MinCorridors = 6;
    CRankTemplate.MaxCorridors = 10;
    CRankTemplate.Difficulty = 3.0f;
    CRankTemplate.bHasBoss = true;
    CRankTemplate.bHasSecretRooms = true;
    CRankTemplate.bHasTreasureRooms = true;
    CRankTemplate.bHasPuzzleRooms = true;
    DungeonTemplates.Add(EDungeonRank::DR_C, CRankTemplate);
    
    // Initialize B-Rank dungeon template
    FDungeonConfig BRankTemplate;
    BRankTemplate.DungeonType = EDungeonType::DT_Desert;
    BRankTemplate.DungeonRank = EDungeonRank::DR_B;
    BRankTemplate.Biome = EDungeonBiome::DB_Desert;
    BRankTemplate.MinRooms = 12;
    BRankTemplate.MaxRooms = 16;
    BRankTemplate.MinCorridors = 10;
    BRankTemplate.MaxCorridors = 14;
    BRankTemplate.Difficulty = 4.0f;
    BRankTemplate.bHasBoss = true;
    BRankTemplate.bHasSecretRooms = true;
    BRankTemplate.bHasTreasureRooms = true;
    BRankTemplate.bHasPuzzleRooms = true;
    DungeonTemplates.Add(EDungeonRank::DR_B, BRankTemplate);
    
    // Initialize A-Rank dungeon template
    FDungeonTemplate ARankTemplate;
    ARankTemplate.DungeonType = EDungeonType::DT_Ice;
    ARankTemplate.DungeonRank = EDungeonRank::DR_A;
    ARankTemplate.Biome = EDungeonBiome::DB_Ice;
    ARankTemplate.MinRooms = 16;
    ARankTemplate.MaxRooms = 20;
    ARankTemplate.MinCorridors = 14;
    ARankTemplate.MaxCorridors = 18;
    ARankTemplate.Difficulty = 5.0f;
    ARankTemplate.bHasBoss = true;
    ARankTemplate.bHasSecretRooms = true;
    ARankTemplate.bHasTreasureRooms = true;
    ARankTemplate.bHasPuzzleRooms = true;
    DungeonTemplates.Add(EDungeonRank::DR_A, ARankTemplate);
    
    // Initialize S-Rank dungeon template
    FDungeonConfig SRankTemplate;
    SRankTemplate.DungeonType = EDungeonType::DT_Fire;
    SRankTemplate.DungeonRank = EDungeonRank::DR_S;
    SRankTemplate.Biome = EDungeonBiome::DB_Volcanic;
    SRankTemplate.MinRooms = 20;
    SRankTemplate.MaxRooms = 25;
    SRankTemplate.MinCorridors = 18;
    SRankTemplate.MaxCorridors = 22;
    SRankTemplate.Difficulty = 6.0f;
    SRankTemplate.bHasBoss = true;
    SRankTemplate.bHasSecretRooms = true;
    SRankTemplate.bHasTreasureRooms = true;
    SRankTemplate.bHasPuzzleRooms = true;
    DungeonTemplates.Add(EDungeonRank::DR_S, SRankTemplate);
    
    UE_LOG(LogTemp, Warning, TEXT("Dungeon templates initialized"));
}

FDungeonLayout UDungeonGenerator::GenerateDungeon(FDungeonConfig Config)
{
    FDungeonLayout Layout;
    
    // Generate unique dungeon ID
    FString DungeonID = FString::Printf(TEXT("Dungeon_%d"), ++CurrentDungeonID);
    
    // Generate dungeon structure
    GenerateDungeonStructure(Config, Layout);
    
    // Generate dungeon content
    GenerateDungeonContent(Config, Layout);
    
    // Add to generated dungeons
    GeneratedDungeons.Add(Layout);
    
    // Notify dungeon generation
    OnDungeonGenerated.Broadcast(DungeonID, Layout);
    
    UE_LOG(LogTemp, Warning, TEXT("Dungeon generated: %s with %d rooms"), *DungeonID, Layout.Rooms.Num());
    
    return Layout;
}

void UDungeonGenerator::GenerateDungeonStructure(FDungeonConfig& Config, FDungeonLayout& Layout)
{
    // Generate room layout
    GenerateRoomLayout(Config, Layout);
    
    // Generate corridor connections
    GenerateCorridorLayout(Config, Layout);
    
    // Optimize room placement
    OptimizeRoomPlacement(Layout);
    
    // Validate dungeon layout
    ValidateDungeonLayout(Layout);
    
    UE_LOG(LogTemp, Warning, TEXT("Dungeon structure generated"));
}

void UDungeonGenerator::GenerateRoomLayout(FDungeonConfig& Config, FDungeonLayout& Layout)
{
    int32 RoomCount = FMath::RandRange(Config.MinRooms, Config.MaxRooms + 1);
    
    // Generate entrance room
    FDungeonRoom EntranceRoom;
    EntranceRoom.RoomID = 0;
    EntranceRoom.RoomLocation = Config.DungeonEntrance;
    EntranceRoom.RoomSize = FVector(1000.0f, 1000.0f, 500.0f);
    EntranceRoom.Biome = Config.Biome;
    EntranceRoom.bIsBossRoom = false;
    EntranceRoom.bIsSecretRoom = false;
    EntranceRoom.bIsTreasureRoom = false;
    EntranceRoom.bIsPuzzleRoom = false;
    Layout.Rooms.Add(EntranceRoom);
    Layout.EntranceRoom = TEXT("Room_0");
    
    // Generate regular rooms
    for (int32 i = 1; i < RoomCount - 1; i++)
    {
        FVector RoomLocation = GenerateRandomLocation(Config.DungeonEntrance, 5000.0f);
        FVector RoomSize = FVector(FMath::RandRange(800.0f, 1200.0f), FMath::RandRange(800.0f, 1200.0f), 500.0f);
        
        FDungeonRoom NewRoom;
        NewRoom.RoomID = i;
        NewRoom.RoomLocation = RoomLocation;
        NewRoom.RoomSize = RoomSize;
        NewRoom.Biome = Config.Biome;
        NewRoom.bIsBossRoom = false;
        NewRoom.bIsSecretRoom = false;
        NewRoom.bIsTreasureRoom = false;
        NewRoom.bIsPuzzleRoom = false;
        
        Layout.Rooms.Add(NewRoom);
        Layout.RoomLocations.Add(FString::Printf(TEXT("Room_%d"), i), RoomLocation);
    }
    
    // Generate boss room if required
    if (Config.bHasBoss)
    {
        FVector BossRoomLocation = GenerateRandomLocation(Config.DungeonEntrance, 6000.0f);
        FVector BossRoomSize = FVector(2000.0f, 2000.0f, 1000.0f);
        
        FDungeonRoom BossRoom;
        BossRoom.RoomID = RoomCount;
        BossRoom.RoomLocation = BossRoomLocation;
        BossRoom.RoomSize = BossRoomSize;
        BossRoom.Biome = Config.Biome;
        BossRoom.bIsBossRoom = true;
        BossRoom.bIsSecretRoom = false;
        BossRoom.bIsTreasureRoom = false;
        BossRoom.bIsPuzzleRoom = false;
        
        Layout.Rooms.Add(BossRoom);
        Layout.RoomLocations.Add(FString::Printf(TEXT("BossRoom")), BossRoomLocation);
        Layout.BossRoom = TEXT("BossRoom");
    }
    
    // Generate special rooms
    if (Config.bHasSecretRooms)
    {
        GenerateSecretRoom(Config, Layout);
    }
    
    if (Config.bHasTreasureRooms)
    {
        GenerateTreasureRoom(Config, Layout);
    }
    
    if (Config.bHasPuzzleRooms)
    {
        GeneratePuzzleRoom(Config, Layout);
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Room layout generated with %d rooms"), Layout.Rooms.Num());
}

void UDungeonGenerator::GenerateCorridorLayout(FDungeonConfig& Config, FDungeonLayout& Layout)
{
    int32 CorridorCount = FMath::RandRange(Config.MinCorridors, Config.MaxCorridors + 1);
    
    // Connect rooms with corridors
    for (int32 i = 0; i < Layout.Rooms.Num() - 1; i++)
    {
        FString Room1ID = FString::Printf(TEXT("Room_%d"), i);
        FString Room2ID = FString::Printf(TEXT("Room_%d"), i + 1);
        
        ConnectRooms(Layout, Room1ID, Room2ID);
    }
    
    // Add extra corridors for connectivity
    for (int32 i = Layout.Rooms.Num(); i < CorridorCount; i++)
    {
        FString Room1 = FString::Printf(TEXT("Room_%d"), FMath::RandRange(0, Layout.Rooms.Num() - 1));
        FString Room2 = FString::Printf(TEXT("Room_%d"), FMath::RandRange(0, Layout.Rooms.Num() - 1));
        
        if (Room1 != Room2)
        {
            ConnectRooms(Layout, Room1, Room2);
        }
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Corridor layout generated with %d corridors"), CorridorCount);
}

void UDungeonGenerator::ConnectRooms(FDungeonLayout& Layout, FString Room1, FString Room2)
{
    FString CorridorID = FString::Printf(TEXT("Corridor_%s_%s"), *Room1, *Room2);
    
    Layout.Corridors.Add(CorridorID);
    
    // Add room connections
    if (Layout.RoomConnections.Contains(Room1))
    {
        Layout.RoomConnections[Room1].Add(Room2);
    }
    else
    {
        TArray<FString> Connections;
        Connections.Add(Room2);
        Layout.RoomConnections.Add(Room1, Connections);
    }
    
    if (Layout.RoomConnections.Contains(Room2))
    {
        Layout.RoomConnections[Room2].Add(Room1);
    }
    else
    {
        TArray<FString> Connections;
        Connections.Add(Room1);
        Layout.RoomConnections.Add(Room2, Connections);
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Connected rooms: %s <-> %s"), *Room1, *Room2);
}

void UDungeonGenerator::GenerateSecretRoom(FDungeonConfig& Config, FDungeonLayout& Layout)
{
    FVector SecretLocation = GenerateRandomLocation(Config.DungeonEntrance, 4000.0f);
    FVector SecretSize = FVector(800.0f, 800.0f, 400.0f);
    
    FDungeonRoom SecretRoom;
    SecretRoom.RoomID = Layout.Rooms.Num();
    SecretRoom.RoomLocation = SecretLocation;
    SecretRoom.RoomSize = SecretSize;
    SecretRoom.Biome = Config.Biome;
    SecretRoom.bIsBossRoom = false;
    SecretRoom.bIsSecretRoom = true;
    SecretRoom.bIsTreasureRoom = true;
    SecretRoom.bIsPuzzleRoom = false;
    
    Layout.Rooms.Add(SecretRoom);
    Layout.RoomLocations.Add(FString::Printf(TEXT("SecretRoom_%d")), SecretLocation);
    
    UE_LOG(LogTemp, Warning, TEXT("Secret room generated"));
}

void UDungeonGenerator::GenerateTreasureRoom(FDungeonConfig& Config, FDungeonLayout& Layout)
{
    FVector TreasureLocation = GenerateRandomLocation(Config.DungeonEntrance, 4500.0f);
    FVector TreasureSize = FVector(1000.0f, 1000.0f, 500.0f);
    
    FDungeonRoom TreasureRoom;
    TreasureRoom.RoomID = Layout.Rooms.Num();
    TreasureRoom.RoomLocation = TreasureLocation;
    TreasureRoom.RoomSize = TreasureSize;
    TreasureRoom.Biome = Config.Biome;
    TreasureRoom.bIsBossRoom = false;
    TreasureRoom.bIsSecretRoom = false;
    TreasureRoom.bIsTreasureRoom = true;
    TreasureRoom.bIsPuzzleRoom = false;
    
    Layout.Rooms.Add(TreasureRoom);
    Layout.RoomLocations.Add(FString::Printf(TEXT("TreasureRoom_%d")), TreasureLocation);
    
    UE_LOG(LogTemp, Warning, TEXT("Treasure room generated"));
}

void UDungeonGenerator::GeneratePuzzleRoom(FDungeonConfig& Config, FDungeonLayout& Layout)
{
    FVector PuzzleLocation = GenerateRandomLocation(Config.DungeonEntrance, 3500.0f);
    FVector PuzzleSize = FVector(800.0f, 800.0f, 400.0f);
    
    FDungeonRoom PuzzleRoom;
    PuzzleRoom.RoomID = Layout.Rooms.Num();
    PuzzleRoom.RoomLocation = PuzzleLocation;
    PuzzleRoom.RoomSize = PuzzleSize;
    PuzzleRoom.Biome = Config.Biome;
    PuzzleRoom.bIsBossRoom = false;
    PuzzleRoom.bIsSecretRoom = false;
    PuzzleRoom.bIsTreasureRoom = false;
    PuzzleRoom.bIsPuzzleRoom = true;
    
    Layout.Rooms.Add(PuzzleRoom);
    Layout.RoomLocations.Add(FString::Printf(TEXT("PuzzleRoom_%d")), PuzzleLocation);
    
    UE_LOG(LogTemp, Warning, TEXT("Puzzle room generated"));
}

void UDungeonGenerator::GenerateDungeonContent(FDungeonConfig& Config, FDungeonLayout& Layout)
{
    // Populate dungeon with enemies, loot, and traps
    PopulateDungeon(Layout);
    
    // Generate dungeon atmosphere
    GenerateDungeonAtmosphere(Config, Layout);
    
    // Generate dungeon difficulty
    GenerateDungeonDifficulty(Config, Layout);
    
    UE_LOG(Temp, Warning, TEXT("Dungeon content generated"));
}

void UDungeonGenerator::PopulateDungeon(FDungeonLayout& Layout)
{
    for (FDungeonRoom& Room : Layout.Rooms)
    {
        SpawnEnemies(Room);
        PlaceLoot(Room);
        PlaceTraps(Room);
    }
}

void UDungeonGenerator::SpawnEnemies(FDungeonRoom& Room)
{
    // Spawn enemies based on dungeon rank and biome
    TArray<FString> AvailableEnemies;
    
    // Get enemies by rank
    if (RankEnemies.Contains(DungeonRank::DR_E))
    {
        AvailableEnemies.Append(RankEnemies[DungeonRank::DR_E]);
    }
    
    // Get enemies by biome
    if (BiomeEnemies.Contains(Room.Biome))
    {
        AvailableEnemies.Append(BiomeEnemies[Room.Biome]);
    }
    
    // Spawn enemies
    int32 EnemyCount = FMath::RandRange(2, 5);
    for (int32 i = 0; i < EnemyCount; i++)
    {
        if (AvailableEnemies.Num() > 0)
        {
            FString EnemyType = AvailableEnemies[FMath::RandRange(0, AvailableEnemies.Num() - 1)];
            Room.Enemies.Add(EnemyType);
        }
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Spawned %d enemies in room %d"), EnemyCount, Room.RoomID);
}

void UDungeonGenerator::PlaceLoot(FDungeonRoom& Room)
{
    // Place loot based on dungeon rank and biome
    TArray<FString> AvailableLoot;
    
    // Get loot by rank
    if (RankLoot.Contains(DungeonRank::DR_E))
    {
        AvailableLoot.Append(RankLoot[DungeonRank::DR_E]);
    }
    
    // Get loot by biome
    if (BiomeLoot.Contains(Room.Biome))
    {
        AvailableLoot.Append(BiomeLoot[Room.Biome]);
    }
    
    // Place loot
    int32 LootCount = FMath::RandRange(1, 3);
    for (int32 i = 0; i < LootCount; i++)
    {
        if (AvailableLoot.Num() > 0)
        {
            FString LootType = AvailableLoot[FMath::RandRange(0, AvailableLoot.Num() - 1)];
            Room.Loot.Add(LootType);
        }
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Placed %d loot items in room %d"), LootCount, Room.RoomID);
}

void UDungeonGenerator::PlaceTraps(FDungeonRoom& Room)
{
    // Place traps based on dungeon difficulty
    int32 TrapCount = FMath::RandRange(0, 2);
    
    for (int32 i = 0; i < TrapCount; i++)
    {
        FString TrapType = TEXT("Trap_") + FString::FromInt(FMath::RandRange(1, 5));
        Room.Enemies.Add(TrapType);
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Placed %d traps in room %d"), TrapCount, Room.RoomID);
}

void UDungeonGenerator::GenerateDungeonAtLocation(FDungeonConfig Config, FVector Location)
{
    Config.DungeonEntrance = Location;
    GenerateDungeon(Config);
}

void UDungeonGenerator::GenerateRandomDungeon(EDungeonRank Rank, FVector Location)
{
    FDungeonConfig Config = DungeonTemplates[Rank];
    Config.DungeonEntrance = Location;
    GenerateDungeon(Config);
}

FVector UDungeonGenerator::GenerateRandomLocation(FVector Center, float Radius)
{
    float Angle = FMath::RandRange(0.0f, 2.0f * PI);
    float Distance = FMath::RandRange(1000.0f, Radius);
    
    FVector RandomLocation;
    RandomLocation.X = Center.X + FMath::Cos(Angle) * Distance;
    RandomLocation.Y = Center.Y + FMath::Sin(Angle) * Distance;
    RandomLocation.Z = Center.Z;
    
    return RandomLocation;
}

void UDungeonGenerator::LoadDungeonTemplates()
{
    // Load dungeon templates from files or database
    UE_LOG(LogTemp, Warning, TEXT("Loading dungeon templates..."));
}

void UDungeonGenerator::LoadDungeonContent()
{
    // Initialize biome enemies
    BiomeEnemies.Add(EDungeonBiome::DB_Underground, TArray<FString>{TEXT("Goblin"), TEXT("Skeleton")});
    BiomeEnemies.Add(EDungeonBiome::DB_Cavern, TArray<FString>{TEXT("Bat"), TEXT("Spider")});
    BiomeEnemies.Add(EDungeonBiome::DB_Forest, TArray<FString>{TEXT("Wolf"), TEXT("Bear")});
    BiomeEnemies.Add(EDungeonBiome::DB_Desert, TArray<FString>{TEXT("Scorpion"), TEXT("Snake")});
    BiomeEnemies.Add(EDungeonBiome::DB_Ice, TArray<FString>{TEXT("IceElemental"), TEXT("FrostGiant")});
    BiomeEnemies.Add(EDungeonBiome::DB_Volcanic, TArray<FString>{TEXT("FireElemental"), TEXT("LavaDemon")});
    
    // Initialize biome loot
    BiomeLoot.Add(EDungeonBiome::DB_Underground, TArray<FString>{TEXT("Gold"), TEXT("Iron")});
    BiomeLoot.Add(EDungeonBiome::DB_Cavern, TArray<FString>{TEXT("Crystal"), TEXT("Gem")});
    BiomeLoot.Add(EDungeonBiome::DB_Forest, TArray<FString>{TEXT("Wood"), TEXT("Herb")});
    BiomeLoot.Add(EDungeonBiome::DB_Desert, TArray<FString>{TEXT("Sand"), TEXT("Oasis")});
    BiomeLoot.Add(EDungeonBiome::DB_Ice, TArray<FString>{TEXT("IceShard"), TEXT("FrostEssence")});
    BiomeLoot.Add(EDungeonBiome::DB_Volcanic, TArray<FString>{TEXT("FireStone"), TEXT("LavaCore")});
    
    // Initialize rank enemies
    RankEnemies.Add(EDungeonRank::DR_E, TArray<FString>{TEXT("Goblin"), TEXT("Skeleton")});
    RankEnemies.Add(EDungeonRank::DR_D, TArray<FString>{TEXT("Orc"), TEXT("Troll")});
    RankEnemies.Add(EDungeonRank::DR_C, TArray<FString>{TEXT("Ogre"), TEXT("Cyclops")});
    RankEnemies.Add(EDungeonRank::DR_B, TArray<FString>{TEXT("Minotaur"), TEXT("Dragon")});
    RankEnemies.Add(EDungeonRank::DR_A, TArray<FString>{TEXT("DemonLord"), TEXT("AncientDragon")});
    RankEnemies.Add(EDungeonRank::DR_S, TArray<FString>{TEXT("DemonKing"), TEXT("DragonLord")});
    
    // Initialize rank loot
    RankLoot.Add(EDungeonRank::DR_E, TArray<FString>{TEXT("BasicPotion"), TEXT("BasicSword")});
    RankLoot.Add(EDungeonRank::DR_D, TArray<FString>{TEXT("AdvancedPotion"), TEXT("AdvancedSword")});
    RankLoot.Add(EDungeonRank::DR_C, TArray<FString>{TEXT("SuperiorPotion"), TEXT("SuperiorSword")});
    RankLoot.Add(EDungeonRank::DR_B, TArray<FString>{TEXT("MasterPotion"), TEXT("MasterSword")});
    RankLoot.Add(EDungeonRank::DR_A, TArray<FString>{TEXT("UltimatePotion"), TEXT("UltimateSword")});
    RankLoot.Add(EDungeonRank::DR_S, TArray<FString>{TEXT("LegendaryPotion"), TEXT("LegendarySword")});
    
    UE_LOG(LogTemp, Warning, TEXT("Dungeon content loaded"));
}

void UDungeonGenerator::InitializeBiomeData()
{
    UE_LOG(LogTemp, Warning, TEXT("Biome data initialized"));
}

void UDungeonGenerator::InitializeRankData()
{
    UE_LOG(LogTemp, Warning, TEXT("Rank data initialized"));
}

void UDungeonGenerator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    UpdateDungeonStates();
}

void UDungeonGenerator::UpdateDungeonStates()
{
    // Update dungeon states and events
    for (FDungeonLayout& Layout : GeneratedDungeons)
    {
        // Check if dungeon is complete
        bool bAllRoomsCleared = true;
        for (const FDungeonRoom& Room : Layout.Rooms)
        {
            if (Room.Enemies.Num() > 0)
            {
                bAllRoomsCleared = false;
                break;
            }
        }
        
        if (bAllRoomsCleared && Layout.BossRoom.IsEmpty())
        {
            OnDungeonCompleted.Broadcast(Layout);
        }
    }
}
