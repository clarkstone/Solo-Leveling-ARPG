#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SoloLevelingGameManager.generated.h"

class UPowerSystemManager;
class UWorldEventManager;
class UCombatManager;
class UStoryManager;
class UAIManager;

UCLASS()
class SIMPLEAPP_API ASoloLevelingGameManager : public AGameModeBase
{
    GENERATED_BODY()

public:
    ASoloLevelingGameManager();

    // Core Systems - Integrates all gameplay systems
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Systems")
    UPowerSystemManager* PowerSystemManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Systems")
    UWorldEventManager* WorldEventManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Systems")
    UCombatManager* CombatManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Systems")
    UStoryManager* StoryManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Systems")
    UAIManager* AIManager;

    // Game State Management
    UPROPERTY(BlueprintReadOnly, Category = "Game State")
    bool bIsInCombat;

    UPROPERTY(BlueprintReadOnly, Category = "Game State")
    bool bIsInDungeon;

    UPROPERTY(BlueprintReadOnly, Category = "Game State")
    int32 CurrentDungeonRank;

    // World Configuration
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Config")
    float WorldTimeScale;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Config")
    EWeatherType CurrentWeather;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "World Config")
    ESeason CurrentSeason;

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    // System Initialization
    void InitializeCoreSystems();
    void InitializeWorldSystems();
    void InitializeCombatSystems();
    void InitializeStorySystems();
    void InitializeAISystems();

    // Game Loop Management
    void UpdateWorldState(float DeltaTime);
    void UpdateCombatState(float DeltaTime);
    void UpdateStoryState(float DeltaTime);
    void UpdateAIState(float DeltaTime);

    // Event Handlers
    UFUNCTION()
    void OnDungeonEntered(int32 DungeonRank);

    UFUNCTION()
    void OnDungeonExited();

    UFUNCTION()
    void OnCombatStarted();

    UFUNCTION()
    void OnCombatEnded();

    UFUNCTION()
    void OnWorldEventTriggered(FWorldEventData EventData);

private:
    // Performance tracking
    UPROPERTY()
    float LastUpdateTime;

    UPROPERTY()
    int32 ActiveEnemyCount;

    // System coordination
    void CoordinateSystemInteractions();
    void BalanceSystemPerformance();
};
