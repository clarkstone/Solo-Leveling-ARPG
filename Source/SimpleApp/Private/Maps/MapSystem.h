#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "MapSystem.generated.h"

UENUM(BlueprintType)
enum class EMapType : uint8
{
    MT_Overworld,
    MT_Dungeon,
    MT_City,
    MT_Village,
    MT_Special
};

UENUM(BlueprintType)
enum class EMapRegion : uint8
{
    MR_SouthKorea,
    MR_Japan,
    MR_China,
    MR_Europe,
    MR_America,
    MR_MiddleEast,
    MR_SouthAmerica,
    MR_Africa,
    MR_Oceania,
    MT_Antarctica,
    MT_Dimension
};

USTRUCT(BlueprintType)
struct FMapLocation
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString LocationName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector Location;

    UPROPERTY(EditAnywhere, BlueprintType)
    EMapRegion Region;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EMapType MapType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 RequiredLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsUnlocked;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsFastTravel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> ConnectedLocations;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> AvailableQuests;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> NPCs;
};

USTRUCT(BlueprintType)
struct FMapData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString MapName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString MapDescription;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EMapType MapType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EMapRegion Region;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector MapCenter;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector MapSize;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float MapScale;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsInstanced;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FMapLocation> Locations;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> Dungeons;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> NPCs;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> Events;
};

UCLASS()
class SIMPLEAPP_API UMapSystem : public UActorComponent
{
    GENERATED_BODY()

public:
    UMapSystem();

    // Map Configuration
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Map")
    TMap<FString, FMapData> MapDatabase;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Map")
    TMap<EMapRegion, TArray<FMapData>> MapsByRegion;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Map")
    FString CurrentMap;

    // Override UActorComponent functions
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Initialization
    UFUNCTION(BlueprintCallable, Category = "Map")
    void Initialize();

    // Map Management
    UFUNCTION(BlueprintCallable, Category = "Map")
    void RegisterMap(FString MapID, FMapData MapData);

    UFUNCTION(BlueprintCallable, Category = "Map")
    void UnregisterMap(FString MapID);

    UFUNCTION(BlueprintCallable, Category = "Map")
    FMapData GetMapData(FString MapID);

    UFUNCTION(BlueprintCallable, Category = "Map")
    TArray<FMapData> GetMapsByRegion(EMapRegion Region);

    // Map Navigation
    UFUNCTION(BlueprintCallable, Category = "Map")
    void TravelToLocation(FString MapID, FString LocationID);

    USTRING(BlueprintCallable, Category = "Map")
    void FastTravel(FString LocationID);

    UFUNCTION(BlueprintCallable, Category = "Map")
    bool CanFastTravel(FString LocationID);

    UFUNCTION(BlueprintCallable, Category = "Map")
    TArray<FString> GetAvailableFastTravelLocations();

    // Map Information
    UFUNCTION(BlueprintCallable, Category = "Map")
    bool IsLocationUnlocked(FString LocationID);

    UFUNCTION(BlueprintCallable, Category = "Map")
    bool IsMapUnlocked(FString MapID);

    UFUNCTION(BlueprintCallable, Category = "Map")
    void UnlockLocation(FString LocationID);

    UFUNCTION(BlueprintType = Category = "Map")
    void UnlockMap(FString MapID);

    // Map Discovery
    UFUNCTION(BlueprintCallable, Category = "Map")
    void DiscoverLocation(FString LocationID);

    UFUNCTION(BlueprintCallable, Category = "Map")
    void DiscoverMap(FString MapID);

    UFUNCTION(BlueprintType = Category = "Map")
    void UpdateMapRevealedPercentage(FString MapID);

    // Map Events
    UFUNCTION(BlueprintCallable, Category = "Map")
    void OnWorldEventTriggered(FWorldEventData EventData);

    UFUNCTION(BlueprintCallable, Category = "Map")
    OnPlayerLevelUp(int32 NewLevel);

    UFUNCTION(BlueprintCallable, Category = "Map")
    OnQuestCompleted(FString QuestID);

    // Map Events
    UPROPERTY(BlueprintAssignable, Category = "Map Events")
    FOnLocationDiscovered OnLocationDiscovered;

    UPROPERTY(BlueprintAssignable, Category = "Map Events")
    FOnMapDiscovered OnMapDiscovered;

    UPROPERTY(BlueprintAssignable, Category = "Map Events")
    FOnLocationUnlocked OnLocationUnlocked;

    UPROPERTY(BlueprintAssignable, Category = "Map Events")
    FOnMapUnlocked OnMapUnlocked;

protected:
    // Internal Map Systems
    void InitializeMapDatabase();
    void UpdateMapStates();
    void ProcessMapEvents();

    // Map Generation
    void GenerateMap(FMapData& MapData);
    void GenerateMapLocations(FMapData& MapData);
    void GenerateMapConnections(FMapData& MapData);

    // Map Navigation
    void UpdateFastTravelSystem();
    void UpdateMapRevealSystem();

private:
    // Internal State
    float LastUpdateTime;
    bool bIsTraveling;
    FString CurrentDestination;

    // Map Data
    TMap<FString, float> MapRevealedPercentage;
    TMap<FString, bool> FastTravelUnlocked;
    TMap<FString, TMap<FString, float>> FastTravelCosts;

    // Helper Functions
    void LoadMapDatabase();
    void SaveMapData();
    void ProcessMapEvent(FString EventType, TArray<FString> Parameters);
};
