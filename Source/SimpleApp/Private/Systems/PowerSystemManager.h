#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "PowerSystemManager.generated.h"

UCLASS()
class SIMPLEAPP_API UPowerSystemManager : public UActorComponent
{
    GENERATED_BODY()

public:
    UPowerSystemManager();

    // Power System Collection
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

    // System Management
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
    float LastUpdateTime;

    // Helper Functions
    void LoadPowerSystems();
    void ConfigurePowerSystems();
    void UpdateSystemStates();
};
