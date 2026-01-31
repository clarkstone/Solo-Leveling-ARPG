#include "AIManager.h"
#include "Kismet/GameplayStatics.h"

UAIManager::UAIManager()
{
    ActiveEnemyCount = 0;
    bIsInCombat = false;
    UpdateFrequency = 0.016f; // 60 FPS
    PerceptionRange = 1000.0f;
    
    LastUpdateTime = 0.0f;
    UpdateTimer = 0.0f;
    bIsOptimized = false;
}

void UAIManager::BeginPlay()
{
    Super::BeginPlay();
    Initialize();
}

void UAIManager::Initialize()
{
    InitializeAI();
    UE_LOG(LogTemp, Warning, TEXT("AI Manager initialized"));
}

void UAIManager::UpdateAIState(float DeltaTime)
{
    UpdateTimer += DeltaTime;
    
    if (UpdateTimer >= UpdateFrequency)
    {
        UpdateTimer = 0.0f;
        UpdateEnemyBehaviors();
    }
}

void UAIManager::OnCombatStarted()
{
    bIsInCombat = true;
    UE_LOG(LogTemp, Warning, TEXT("AI Manager: Combat started"));
}

void UAIManager::OnCombatEnded()
{
    bIsInCombat = false;
    UE_LOG(LogTemp, Warning, TEXT("AI Manager: Combat ended"));
}

void UAIManager::InitializeAI()
{
    UE_LOG(LogTemp, Warning, TEXT("AI systems initialized"));
}

void UAIManager::UpdateEnemyBehaviors()
{
    // Update all enemy AI behaviors
    TArray<AActor*> EnemyActors;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACharacter::StaticClass(), EnemyActors);
    
    ActiveEnemyCount = EnemyActors.Num();
    
    for (AActor* Actor : EnemyActors)
    {
        // Update individual enemy AI
    }
}

void UAIManager::SetUpdateFrequency(float Frequency)
{
    UpdateFrequency = FMath::Clamp(Frequency, 0.033f, 0.1f);
    UE_LOG(LogTemp, Warning, TEXT("AI update frequency set to: %.3f"), UpdateFrequency);
}
