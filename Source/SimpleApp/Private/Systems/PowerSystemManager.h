#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "PowerSystemCore.h"
#include "PowerSystemManager.generated.h"

UCLASS()
class SIMPLEAPP_API UPowerSystemManager : public UActorComponent
{
    GENERATED_BODY()

public:
    UPowerSystemManager();

    // New Class-Based System
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Power Systems")
    class UClassSystemManager* ClassSystemManager;

    // Legacy Support (deprecated)
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Power Systems")
    TArray<class UPowerSystemComponent*> AllPowerSystems;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Power Systems")
    TArray<class UPowerSystemComponent*> ActiveSystems;

    // Override UActorComponent functions
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Initialization
    UFUNCTION(BlueprintCallable, Category = "Power Systems")
    void Initialize();

    // New Class-Based Functions
    UFUNCTION(BlueprintCallable, Category = "Power Systems")
    void SelectClass(ECoreClass CoreClass);

    UFUNCTION(BlueprintCallable, Category = "Power Systems")
    bool UnlockPath(const FString& PathName);

    UFUNCTION(BlueprintCallable, Category = "Power Systems")
    bool ActivatePath(const FString& PathName);

    UFUNCTION(BlueprintCallable, Category = "Power Systems")
    void AddPathExperience(const FString& PathName, int32 ExperienceAmount);

    UFUNCTION(BlueprintCallable, Category = "Power Systems")
    TArray<FString> GetActivePathNames();

    UFUNCTION(BlueprintCallable, Category = "Power Systems")
    TArray<FAbilityData> GetAllActiveAbilities();

    UFUNCTION(BlueprintCallable, Category = "Power Systems")
    int32 GetTotalPowerLevel();

    UFUNCTION(BlueprintCallable, Category = "Power Systems")
    float GetTotalPowerMultiplier();

    // Legacy System Management (deprecated)
    UFUNCTION(BlueprintCallable, Category = "Power Systems")
    void ActivatePowerSystem(EPowerType PowerType);

    UFUNCTION(BlueprintCallable, Category = "Power Systems")
    void DeactivatePowerSystem(EPowerType PowerType);

    UFUNCTION(BlueprintCallable, Category = "Power Systems")
    TArray<UPowerSystemComponent*> GetActiveSystems();

    // Event Handlers
    UFUNCTION(BlueprintCallable, Category = "Power Systems")
    void OnDungeonEntered(int32 DungeonRank);

    UFUNCTION(BlueprintCallable, Category = "Power Systems")
    void OnDungeonExited();

    UFUNCTION(BlueprintCallable, Category = "Power Systems")
    void OnCombatStarted();

    UFUNCTION(BlueprintCallable, Category = "Power Systems")
    void OnCombatEnded();

    UFUNCTION(BlueprintCallable, Category = "Power Systems")
    void ProcessWorldEvent(FWorldEventData EventData);

    // Story and Quest Integration
    UFUNCTION(BlueprintCallable, Category = "Power Systems")
    void OnStoryEvent(const FString& EventName);

    UFUNCTION(BlueprintCallable, Category = "Power Systems")
    void OnGuildJoined(const FString& GuildName);

    UFUNCTION(BlueprintCallable, Category = "Power Systems")
    void OnQuestCompleted(const FString& QuestName);

    UFUNCTION(BlueprintCallable, Category = "Power Systems")
    void OnAchievementUnlocked(const FString& AchievementName);

    // Performance
    UFUNCTION(BlueprintCallable, Category = "Power Systems")
    void SetOptimizationMode(bool bOptimized);

protected:
    // Internal Systems
    void InitializePowerSystems();
    void UpdateActiveSystems();
    void OptimizeSystemPerformance();

private:
    // Internal State
    bool bIsOptimized;
    bool bUseNewSystem;
    float LastUpdateTime;

    // Helper Functions
    void LoadPowerSystems();
    void ConfigurePowerSystems();
    void UpdateSystemStates();
    void MigrateToNewSystem();
};
