#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "DungeonGenerator.generated.h"

UENUM(BlueprintType)
enum class EDungeonType : uint8
{
    DT_Classic,
    DT_Cave,
    DT_Forest,
    DT_Desert,
    DT_Ice,
    DT_Fire,
    DT_Shadow,
    DT_Cosmic,
    DT_Abyssal,
    DT_Dimensional
};

UENUM(BlueprintType)
enum class EDungeonRank : uint8
{
    DR_E,
    DR_D,
    DR_C,
    DR_B,
    DR_A,
    DR_S
};

UENUM(BlueprintType)
enum class EDungeonBiome : uint8
{
    DB_Underground,
    DB_Cavern,
    DB_Ruins,
    DB_Forest,
    DB_Desert,
    DB_Ice,
    DB_Volcanic,
    DB_Swamp,
    DB_Celestial,
    DB_Abyssal
};

USTRUCT(BlueprintType)
struct FDungeonRoom
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 RoomID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector RoomLocation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector RoomSize;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EDungeonBiome Biome;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> RequiredKeys;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> Enemies;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> Loot;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsBossRoom;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsSecretRoom;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsTreasureRoom;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsPuzzleRoom;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> ConnectedRooms;
};

USTRUCT(BlueprintType)
struct FDungeonConfig
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EDungeonType DungeonType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EDungeonRank DungeonRank;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EDungeonBiome Biome;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MinRooms;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxRooms;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MinCorridors;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxCorridors;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Difficulty;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bHasBoss;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bHasSecretRooms;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bHasTreasureRooms;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bHasPuzzleRooms;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> RequiredPowerSystems;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector DungeonEntrance;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector DungeonExit;
};

USTRUCT(BlueprintType)
struct FDungeonLayout
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FDungeonRoom> Rooms;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> Corridors;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString EntranceRoom;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString BossRoom;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ExitRoom;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FString, FVector> RoomLocations;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TMap<FString, TArray<FString>> RoomConnections;
};

UCLASS()
class SIMPLEAPP_API UDungeonGenerator : public UActorComponent
{
    GENERATED_BODY()

public:
    UDungeonGenerator();

    // Dungeon Configuration
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon")
    TMap<EDungeonRank, FDungeonConfig> DungeonTemplates;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dungeon")
    TArray<FDungeonLayout> GeneratedDungeons;

    // Override UActorComponent functions
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Initialization
    UFUNCTION(BlueprintCallable, Category = "Dungeon")
    void Initialize();

    // Dungeon Generation
    UFUNCTION(BlueprintCallable, Category = "Dungeon")
    FDungeonLayout GenerateDungeon(FDungeonConfig Config);

    UFUNCTION(BlueprintCallable, Category = "Dungeon")
    void GenerateDungeonAtLocation(FDungeonConfig Config, FVector Location);

    UFUNCTION(BlueprintCallable, Category = "Dungeon")
    void GenerateRandomDungeon(EDungeonRank Rank, FVector Location);

    // Room Generation
    UFUNCTION(BlueprintCallable, Category = "Dungeon")
    FDungeonRoom GenerateRoom(FVector Location, FVector Size, EDungeonBiome Biome);

    UFUNCTION(BlueprintCallable, Category = "Dungeon")
    FDungeonRoom GenerateBossRoom(FVector Location, FVector Size, EDungeonBiome Biome);

    UFUNCTION(BlueprintCallable, Category = "Dungeon")
    FDungeonRoom GenerateSecretRoom(FVector Location, FVector Size, EDungeonBiome Biome);

    UFUNCTION(BlueprintCallable, Category = "Dungeon")
    FDungeonRoom GenerateTreasureRoom(FVector Location, FVector Size, EDungeonBiome Biome);

    UFUNCTION(BlueprintCallable, Category = "Dungeon")
    FDungeonRoom GeneratePuzzleRoom(FVector Location, FVector Size, EDungeonBiome Biome);

    // Corridor Generation
    UFUNCTION(BlueprintCallable, Category = "Dungeon")
    void GenerateCorridors(FDungeonLayout& Layout);

    UFUNCTION(BlueprintCallable, Category = "Dungeon")
    void ConnectRooms(FDungeonLayout& Layout, FString Room1, FString Room2);

    // Dungeon Population
    UFUNCTION(BlueprintCallable, Category = "Dungeon")
    void PopulateDungeon(FDungeonLayout& Layout);

    UFUNCTION(BlueprintCallable, Category = "Dungeon")
    void SpawnEnemies(FDungeonRoom& Room);

    UFUNCTION(BlueprintCallable, Category = "Dungeon")
    void PlaceLoot(FDungeonRoom& Room);

    UFUNCTION(BlueprintCallable, Category = "Dungeon")
    void PlaceTraps(FDungeonRoom& Room);

    // Dungeon Management
    UFUNCTION(BlueprintCallable, Category = "Dungeon")
    void SpawnDungeon(FDungeonLayout Layout);

    UFUNCTION(BlueprintCallable, Category = "Dungeon")
    void DespawnDungeon(FString DungeonID);

    UFUNCTION(BlueprintCallable, Category = "Dungeon")
    void ResetDungeon(FString DungeonID);

    // Dungeon Information
    UFUNCTION(BlueprintCallable, Category = "Dungeon")
    FDungeonLayout GetDungeonLayout(FString DungeonID);

    UFUNCTION(BlueprintCallable, Category = "Dungeon")
    TArray<FDungeonRoom> GetDungeonRooms(FString DungeonID);

    UFUNCTION(BlueprintCallable, Category = "Dungeon")
    bool IsDungeonComplete(FString DungeonID);

    // Dungeon Events
    UFUNCTION(BlueprintCallable, Category = "Dungeon")
    void OnRoomEntered(FString DungeonID, FString RoomID);

    UFUNCTION(BlueprintCallable, Category = "Dungeon")
    void OnRoomCleared(FString DungeonID, FString RoomID);

    UFUNCTION(BlueprintCallable, Category = "Dungeon")
    void OnBossDefeated(FString DungeonID);

    // Dungeon Events
    UPROPERTY(BlueprintAssignable, Category = "Dungeon Events")
    FOnDungeonGenerated OnDungeonGenerated;

    UPROPERTY(BlueprintAssignable, Category = "Dungeon Events")
    FOnDungeonCompleted OnDungeonCompleted;

    UPROPERTY(BlueprintAssignable, Category = "Dungeon Events")
    FOnRoomEntered OnRoomEntered;

    UPROPERTY(BlueprintAssignable, Category = "Dungeon Events")
    FOnRoomCleared OnRoomCleared;

protected:
    // Internal Generation Systems
    void InitializeDungeonTemplates();
    void InitializeGenerationAlgorithms();
    void UpdateDungeonStates();

    // Generation Algorithms
    void GenerateRoomLayout(FDungeonConfig& Config, FDungeonLayout& Layout);
    void GenerateCorridorLayout(FDungeonConfig& Config, FDungeonLayout& Layout);
    void GenerateDungeonStructure(FDungeonConfig& Config, FDungeonLayout& Layout);

    // Room Placement
    void PlaceRooms(FDungeonConfig& Config, FDungeonLayout& Layout);
    void OptimizeRoomPlacement(FDungeonLayout& Layout);
    void ValidateDungeonLayout(FDungeonLayout& Layout);

    // Content Generation
    void GenerateDungeonContent(FDungeonConfig& Config, FDungeonLayout& Layout);
    void GenerateDungeonAtmosphere(FDungeonConfig& Config, FDungeonLayout& Layout);
    void GenerateDungeonDifficulty(FDungeonConfig& Config, FDungeonLayout& Layout);

private:
    // Internal State
    float LastGenerationTime;
    int32 CurrentDungeonID;
    bool bIsGenerating;

    // Generation Data
    TMap<EDungeonBiome, TArray<FString>> BiomeEnemies;
    TMap<EDungeonBiome, TArray<FString>> BiomeLoot;
    TMap<EDungeonRank, TArray<FString>> RankEnemies;
    TMap<EDungeonRank, TArray<FString>> RankLoot;

    // Helper Functions
    void LoadDungeonTemplates();
    void LoadDungeonContent();
    void InitializeBiomeData();
    void InitializeRankData();
    FVector GenerateRandomLocation(FVector Center, float Radius);
};
