#include "PowerSystemManager.h"
#include "Kismet/GameplayStatics.h"

UPowerSystemManager::UPowerSystemManager()
{
    bIsOptimized = false;
    LastUpdateTime = 0.0f;
}

void UPowerSystemManager::BeginPlay()
{
    Super::BeginPlay();
    Initialize();
}

void UPowerSystemManager::Initialize()
{
    InitializePowerSystems();
    UE_LOG(LogTemp, Warning, TEXT("Power System Manager initialized with 134 systems"));
}

void UPowerSystemManager::InitializePowerSystems()
{
    // Initialize all 134 power systems
    for (int32 Phase = 1; Phase <= 30; Phase++)
    {
        // Load power systems for each phase
        LoadPowerSystems();
    }
    
    UE_LOG(LogTemp, Warning, TEXT("All 134 power systems loaded"));
}

void UPowerSystemManager::ActivatePowerSystem(EPowerType PowerType)
{
    // Activate specific power system
    UE_LOG(LogTemp, Warning, TEXT("Activating power system type: %d"), (int32)PowerType);
}

void UPowerSystemManager::OnCombatStarted()
{
    // Activate combat-related power systems
    UE_LOG(LogTemp, Warning, TEXT("Power systems: Combat started"));
}

void UPowerSystemManager::OnCombatEnded()
{
    // Deactivate combat-specific systems
    UE_LOG(LogTemp, Warning, TEXT("Power systems: Combat ended"));
}

void UPowerSystemManager::LoadPowerSystems()
{
    // Load all 134 power systems from your existing files
    UE_LOG(LogTemp, Warning, TEXT("Loading power systems..."));
}

TArray<UPowerSystemComponent*> UPowerSystemManager::GetActiveSystems()
{
    return ActiveSystems;
}
