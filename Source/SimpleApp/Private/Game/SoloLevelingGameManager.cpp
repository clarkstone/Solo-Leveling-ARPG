#include "SoloLevelingGameManager.h"
#include "Systems/PowerSystemManager.h"
#include "Systems/WorldEventManager.h"
#include "Systems/CombatManager.h"
#include "Systems/StoryManager.h"
#include "Systems/AIManager.h"
#include "Kismet/GameplayStatics.h"

ASoloLevelingGameManager::ASoloLevelingGameManager()
{
    PrimaryActorTick.bCanEverTick = true;
    
    // Initialize system pointers
    PowerSystemManager = nullptr;
    WorldEventManager = nullptr;
    CombatManager = nullptr;
    StoryManager = nullptr;
    AIManager = nullptr;
    
    // Initialize game state
    bIsInCombat = false;
    bIsInDungeon = false;
    CurrentDungeonRank = 0;
    
    // Initialize world configuration
    WorldTimeScale = 1.0f;
    CurrentWeather = EWeatherType::Clear;
    CurrentSeason = ESeason::Spring;
    
    // Performance tracking
    LastUpdateTime = 0.0f;
    ActiveEnemyCount = 0;
}

void ASoloLevelingGameManager::BeginPlay()
{
    Super::BeginPlay();
    
    // Initialize all core systems
    InitializeCoreSystems();
    InitializeWorldSystems();
    InitializeCombatSystems();
    InitializeStorySystems();
    InitializeAISystems();
    
    UE_LOG(LogTemp, Warning, TEXT("Solo Leveling Game Manager initialized with all systems"));
}

void ASoloLevelingGameManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    // Update all systems in coordinated manner
    UpdateWorldState(DeltaTime);
    UpdateCombatState(DeltaTime);
    UpdateStoryState(DeltaTime);
    UpdateAIState(DeltaTime);
    
    // Coordinate system interactions
    CoordinateSystemInteractions();
    
    // Balance system performance
    BalanceSystemPerformance();
    
    LastUpdateTime += DeltaTime;
}

void ASoloLevelingGameManager::InitializeCoreSystems()
{
    // Create and initialize Power System Manager
    PowerSystemManager = NewObject<UPowerSystemManager>(this);
    if (PowerSystemManager)
    {
        PowerSystemManager->Initialize();
        UE_LOG(LogTemp, Warning, TEXT("Power System Manager initialized with 134 systems"));
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Core systems initialization complete"));
}

void ASoloLevelingGameManager::InitializeWorldSystems()
{
    // Create and initialize World Event Manager
    WorldEventManager = NewObject<UWorldEventManager>(this);
    if (WorldEventManager)
    {
        WorldEventManager->Initialize();
        WorldEventManager->OnDungeonEntered.AddDynamic(this, &ASoloLevelingGameManager::OnDungeonEntered);
        WorldEventManager->OnDungeonExited.AddDynamic(this, &ASoloLevelingGameManager::OnDungeonExited);
        WorldEventManager->OnWorldEventTriggered.AddDynamic(this, &ASoloLevelingGameManager::OnWorldEventTriggered);
        UE_LOG(LogTemp, Warning, TEXT("World Event Manager initialized"));
    }
    
    UE_LOG(LogTemp, Warning, TEXT("World systems initialization complete"));
}

void ASoloLevelingGameManager::InitializeCombatSystems()
{
    // Create and initialize Combat Manager
    CombatManager = NewObject<UCombatManager>(this);
    if (CombatManager)
    {
        CombatManager->Initialize();
        CombatManager->OnCombatStarted.AddDynamic(this, &ASoloLevelingGameManager::OnCombatStarted);
        CombatManager->OnCombatEnded.AddDynamic(this, &ASoloLevelingGameManager::OnCombatEnded);
        UE_LOG(LogTemp, Warning, TEXT("Combat Manager initialized"));
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Combat systems initialization complete"));
}

void ASoloLevelingGameManager::InitializeStorySystems()
{
    // Create and initialize Story Manager
    StoryManager = NewObject<UStoryManager>(this);
    if (StoryManager)
    {
        StoryManager->Initialize();
        UE_LOG(LogTemp, Warning, TEXT("Story Manager initialized"));
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Story systems initialization complete"));
}

void ASoloLevelingGameManager::InitializeAISystems()
{
    // Create and initialize AI Manager
    AIManager = NewObject<UAIManager>(this);
    if (AIManager)
    {
        AIManager->Initialize();
        UE_LOG(LogTemp, Warning, TEXT("AI Manager initialized"));
    }
    
    UE_LOG(LogTemp, Warning, TEXT("AI systems initialization complete"));
}

void ASoloLevelingGameManager::UpdateWorldState(float DeltaTime)
{
    if (WorldEventManager)
    {
        WorldEventManager->UpdateWorldState(DeltaTime);
    }
}

void ASoloLevelingGameManager::UpdateCombatState(float DeltaTime)
{
    if (CombatManager)
    {
        CombatManager->UpdateCombatState(DeltaTime);
        ActiveEnemyCount = CombatManager->GetActiveEnemyCount();
    }
}

void ASoloLevelingGameManager::UpdateStoryState(float DeltaTime)
{
    if (StoryManager)
    {
        StoryManager->UpdateStoryState(DeltaTime);
    }
}

void ASoloLevelingGameManager::UpdateAIState(float DeltaTime)
{
    if (AIManager)
    {
        AIManager->UpdateAIState(DeltaTime);
    }
}

void ASoloLevelingGameManager::CoordinateSystemInteractions()
{
    // Coordinate power systems with combat
    if (PowerSystemManager && CombatManager)
    {
        // Sync power system states with combat state
        CombatManager->UpdatePowerSystemStates(PowerSystemManager->GetActiveSystems());
    }
    
    // Coordinate world events with story progression
    if (WorldEventManager && StoryManager)
    {
        // Update story based on world events
        StoryManager->ProcessWorldEvents(WorldEventManager->GetRecentEvents());
    }
    
    // Coordinate AI with combat and world state
    if (AIManager && CombatManager)
    {
        // Update AI behavior based on combat situation
        AIManager->UpdateCombatAwareness(CombatManager->GetCombatSituation());
    }
}

void ASoloLevelingGameManager::BalanceSystemPerformance()
{
    // Monitor performance and adjust system priorities
    float CurrentFrameTime = GetWorld()->GetDeltaSeconds();
    
    if (CurrentFrameTime > 0.033f) // Below 30 FPS
    {
        // Reduce AI update frequency
        if (AIManager)
        {
            AIManager->SetUpdateFrequency(0.1f);
        }
        
        // Optimize power system updates
        if (PowerSystemManager)
        {
            PowerSystemManager->SetOptimizationMode(true);
        }
    }
    else if (CurrentFrameTime < 0.016f) // Above 60 FPS
    {
        // Restore full update frequency
        if (AIManager)
        {
            AIManager->SetUpdateFrequency(0.016f);
        }
        
        // Disable optimization mode
        if (PowerSystemManager)
        {
            PowerSystemManager->SetOptimizationMode(false);
        }
    }
}

void ASoloLevelingGameManager::OnDungeonEntered(int32 DungeonRank)
{
    bIsInDungeon = true;
    CurrentDungeonRank = DungeonRank;
    
    UE_LOG(LogTemp, Warning, TEXT("Entered Rank %d Dungeon"), DungeonRank);
    
    // Notify all systems of dungeon entry
    if (PowerSystemManager)
    {
        PowerSystemManager->OnDungeonEntered(DungeonRank);
    }
    
    if (StoryManager)
    {
        StoryManager->OnDungeonEntered(DungeonRank);
    }
    
    if (AIManager)
    {
        AIManager->OnDungeonEntered(DungeonRank);
    }
}

void ASoloLevelingGameManager::OnDungeonExited()
{
    bIsInDungeon = false;
    CurrentDungeonRank = 0;
    
    UE_LOG(LogTemp, Warning, TEXT("Exited Dungeon"));
    
    // Notify all systems of dungeon exit
    if (PowerSystemManager)
    {
        PowerSystemManager->OnDungeonExited();
    }
    
    if (StoryManager)
    {
        StoryManager->OnDungeonExited();
    }
    
    if (AIManager)
    {
        AIManager->OnDungeonExited();
    }
}

void ASoloLevelingGameManager::OnCombatStarted()
{
    bIsInCombat = true;
    
    UE_LOG(LogTemp, Warning, TEXT("Combat Started"));
    
    // Notify all systems of combat start
    if (PowerSystemManager)
    {
        PowerSystemManager->OnCombatStarted();
    }
    
    if (WorldEventManager)
    {
        WorldEventManager->OnCombatStarted();
    }
    
    if (StoryManager)
    {
        StoryManager->OnCombatStarted();
    }
    
    if (AIManager)
    {
        AIManager->OnCombatStarted();
    }
}

void ASoloLevelingGameManager::OnCombatEnded()
{
    bIsInCombat = false;
    
    UE_LOG(LogTemp, Warning, TEXT("Combat Ended"));
    
    // Notify all systems of combat end
    if (PowerSystemManager)
    {
        PowerSystemManager->OnCombatEnded();
    }
    
    if (WorldEventManager)
    {
        WorldEventManager->OnCombatEnded();
    }
    
    if (StoryManager)
    {
        StoryManager->OnCombatEnded();
    }
    
    if (AIManager)
    {
        AIManager->OnCombatEnded();
    }
}

void ASoloLevelingGameManager::OnWorldEventTriggered(FWorldEventData EventData)
{
    UE_LOG(LogTemp, Warning, TEXT("World Event Triggered: %s"), *EventData.EventName);
    
    // Process world event through all systems
    if (StoryManager)
    {
        StoryManager->ProcessWorldEvent(EventData);
    }
    
    if (AIManager)
    {
        AIManager->ProcessWorldEvent(EventData);
    }
    
    if (PowerSystemManager)
    {
        PowerSystemManager->ProcessWorldEvent(EventData);
    }
}
