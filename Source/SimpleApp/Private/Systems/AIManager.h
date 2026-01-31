#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "AIManager.generated.h"

UCLASS()
class SIMPLEAPP_API UAIManager : public UActorComponent
{
    GENERATED_BODY()

public:
    UAIManager();

    // AI State Management
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    int32 ActiveEnemyCount;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
    bool bIsInCombat;

    // AI Configuration
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float UpdateFrequency;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float PerceptionRange;

    // Override UActorComponent functions
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Initialization
    UFUNCTION(BlueprintCallable, Category = "AI")
    void Initialize();

    // AI Management
    UFUNCTION(BlueprintCallable, Category = "AI")
    void UpdateAIState(float DeltaTime);

    UFUNCTION(BlueprintCallable, Category = "AI")
    void UpdateCombatAwareness(FCombatSituation CombatData);

    // Event Handlers
    UFUNCTION(BlueprintCallable, Category = "AI")
    void OnDungeonEntered(int32 DungeonRank);

    UFUNCTION(BlueprintCallable, Category = "AI")
    void OnCombatStarted();

    UFUNCTION(BlueprintCallable, Category = "AI")
    void OnCombatEnded();

    UFUNCTION(BlueprintCallable, Category = "AI")
    void ProcessWorldEvent(FWorldEventData EventData);

protected:
    // Internal AI Systems
    void UpdateEnemyBehaviors();
    void UpdateAIPerformance();
    void OptimizeAIUpdates();

private:
    // Internal State
    float LastUpdateTime;
    float UpdateTimer;
    bool bIsOptimized;

    // Helper Functions
    void InitializeAI();
    void UpdateEnemyAI();
    void OptimizePerformance();
};
