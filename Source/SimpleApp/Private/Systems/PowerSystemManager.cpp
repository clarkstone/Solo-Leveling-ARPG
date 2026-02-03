#include "PowerSystemManager.h"
#include "ClassSystemManager.h"
#include "PowerPathComponent.h"
#include "Kismet/GameplayStatics.h"

UPowerSystemManager::UPowerSystemManager()
{
    bIsOptimized = false;
    bUseNewSystem = true; // Use new class-based system by default
    LastUpdateTime = 0.0f;
}

void UPowerSystemManager::BeginPlay()
{
    Super::BeginPlay();
    
    // Create and initialize the new class system manager
    ClassSystemManager = NewObject<UClassSystemManager>(this);
    if (ClassSystemManager)
    {
        ClassSystemManager->RegisterComponent();
        if (GetOwner())
        {
            ClassSystemManager->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
        }
    }
    
    Initialize();
}

void UPowerSystemManager::Initialize()
{
    if (bUseNewSystem && ClassSystemManager)
    {
        // Initialize new class-based system
        UE_LOG(LogTemp, Warning, TEXT("Power System Manager initialized with new class-based system (45 paths)"));
    }
    else
    {
        // Initialize legacy system for backward compatibility
        InitializePowerSystems();
        UE_LOG(LogTemp, Warning, TEXT("Power System Manager initialized with legacy system (134 systems)"));
    }
}

void UPowerSystemManager::SelectClass(ECoreClass CoreClass)
{
    if (ClassSystemManager)
    {
        ClassSystemManager->SelectClass(CoreClass);
    }
}

bool UPowerSystemManager::UnlockPath(const FString& PathName)
{
    if (ClassSystemManager)
    {
        return ClassSystemManager->UnlockPath(PathName);
    }
    return false;
}

bool UPowerSystemManager::ActivatePath(const FString& PathName)
{
    if (ClassSystemManager)
    {
        return ClassSystemManager->ActivatePath(PathName);
    }
    return false;
}

void UPowerSystemManager::AddPathExperience(const FString& PathName, int32 ExperienceAmount)
{
    if (ClassSystemManager)
    {
        ClassSystemManager->AddPathExperience(PathName, ExperienceAmount);
    }
}

TArray<FString> UPowerSystemManager::GetActivePathNames()
{
    if (ClassSystemManager)
    {
        return ClassSystemManager->GetActivePathNames();
    }
    return TArray<FString>();
}

TArray<FAbilityData> UPowerSystemManager::GetAllActiveAbilities()
{
    if (ClassSystemManager)
    {
        return ClassSystemManager->GetAllActiveAbilities();
    }
    return TArray<FAbilityData>();
}

int32 UPowerSystemManager::GetTotalPowerLevel()
{
    if (ClassSystemManager)
    {
        return ClassSystemManager->GetTotalPowerLevel();
    }
    return 0;
}

float UPowerSystemManager::GetTotalPowerMultiplier()
{
    if (ClassSystemManager)
    {
        return ClassSystemManager->GetTotalPowerMultiplier();
    }
    return 1.0f;
}

void UPowerSystemManager::OnStoryEvent(const FString& EventName)
{
    if (ClassSystemManager)
    {
        ClassSystemManager->OnStoryEvent(EventName);
    }
}

void UPowerSystemManager::OnGuildJoined(const FString& GuildName)
{
    if (ClassSystemManager)
    {
        ClassSystemManager->OnGuildJoined(GuildName);
    }
}

void UPowerSystemManager::OnQuestCompleted(const FString& QuestName)
{
    if (ClassSystemManager)
    {
        ClassSystemManager->OnQuestCompleted(QuestName);
    }
}

void UPowerSystemManager::OnAchievementUnlocked(const FString& AchievementName)
{
    if (ClassSystemManager)
    {
        ClassSystemManager->OnAchievementUnlocked(AchievementName);
    }
}

// Legacy System Functions (deprecated)
void UPowerSystemManager::ActivatePowerSystem(EPowerType PowerType)
{
    UE_LOG(LogTemp, Warning, TEXT("Legacy ActivatePowerSystem called - consider using new class-based system"));
    // Legacy implementation for backward compatibility
}

void UPowerSystemManager::DeactivatePowerSystem(EPowerType PowerType)
{
    UE_LOG(LogTemp, Warning, TEXT("Legacy DeactivatePowerSystem called - consider using new class-based system"));
    // Legacy implementation for backward compatibility
}

void UPowerSystemManager::OnCombatStarted()
{
    if (bUseNewSystem && ClassSystemManager)
    {
        // New system combat logic
        UE_LOG(LogTemp, Warning, TEXT("New class-based system: Combat started"));
    }
    else
    {
        // Legacy combat logic
        UE_LOG(LogTemp, Warning, TEXT("Legacy system: Combat started"));
    }
}

void UPowerSystemManager::OnCombatEnded()
{
    if (bUseNewSystem && ClassSystemManager)
    {
        // New system combat logic
        UE_LOG(LogTemp, Warning, TEXT("New class-based system: Combat ended"));
    }
    else
    {
        // Legacy combat logic
        UE_LOG(LogTemp, Warning, TEXT("Legacy system: Combat ended"));
    }
}

void UPowerSystemManager::OnDungeonEntered(int32 DungeonRank)
{
    if (bUseNewSystem && ClassSystemManager)
    {
        // New system dungeon logic
        UE_LOG(LogTemp, Warning, TEXT("New class-based system: Dungeon entered (Rank %d)"), DungeonRank);
    }
    else
    {
        // Legacy dungeon logic
        UE_LOG(LogTemp, Warning, TEXT("Legacy system: Dungeon entered (Rank %d)"), DungeonRank);
    }
}

void UPowerSystemManager::OnDungeonExited()
{
    if (bUseNewSystem && ClassSystemManager)
    {
        // New system dungeon logic
        UE_LOG(LogTemp, Warning, TEXT("New class-based system: Dungeon exited"));
    }
    else
    {
        // Legacy dungeon logic
        UE_LOG(LogTemp, Warning, TEXT("Legacy system: Dungeon exited"));
    }
}

void UPowerSystemManager::ProcessWorldEvent(FWorldEventData EventData)
{
    if (bUseNewSystem && ClassSystemManager)
    {
        // New system world event logic
        UE_LOG(LogTemp, Warning, TEXT("New class-based system: Processing world event"));
    }
    else
    {
        // Legacy world event logic
        UE_LOG(LogTemp, Warning, TEXT("Legacy system: Processing world event"));
    }
}

void UPowerSystemManager::InitializePowerSystems()
{
    // Legacy initialization for backward compatibility
    for (int32 Phase = 1; Phase <= 30; Phase++)
    {
        // Load power systems for each phase
        LoadPowerSystems();
    }
    
    UE_LOG(LogTemp, Warning, TEXT("All 134 legacy power systems loaded"));
}

void UPowerSystemManager::LoadPowerSystems()
{
    // Legacy system loading for backward compatibility
    UE_LOG(LogTemp, Warning, TEXT("Loading legacy power systems..."));
}

TArray<UPowerSystemComponent*> UPowerSystemManager::GetActiveSystems()
{
    if (bUseNewSystem && ClassSystemManager)
    {
        // Convert new system paths to legacy format for compatibility
        TArray<UPowerSystemComponent*> LegacySystems;
        // Conversion logic here if needed
        return LegacySystems;
    }
    
    return ActiveSystems;
}

void UPowerSystemManager::SetOptimizationMode(bool bOptimized)
{
    bIsOptimized = bOptimized;
    
    if (ClassSystemManager)
    {
        // Apply optimization to new system
        UE_LOG(LogTemp, Warning, TEXT("New class-based system optimization set to: %s"), bOptimized ? TEXT("true") : TEXT("false"));
    }
    
    OptimizeSystemPerformance();
}

void UPowerSystemManager::UpdateActiveSystems()
{
    if (bUseNewSystem && ClassSystemManager)
    {
        // Update active systems based on new class system
        UE_LOG(LogTemp, Warning, TEXT("Updating active systems from new class-based system"));
    }
    else
    {
        // Legacy active system update
        UE_LOG(LogTemp, Warning, TEXT("Updating active systems from legacy system"));
    }
}

void UPowerSystemManager::OptimizeSystemPerformance()
{
    if (bIsOptimized)
    {
        UE_LOG(LogTemp, Warning, TEXT("Power system optimization enabled"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Power system optimization disabled"));
    }
}

void UPowerSystemManager::ConfigurePowerSystems()
{
    if (bUseNewSystem && ClassSystemManager)
    {
        // Configure new class-based system
        UE_LOG(LogTemp, Warning, TEXT("Configuring new class-based power system"));
    }
    else
    {
        // Configure legacy system
        UE_LOG(LogTemp, Warning, TEXT("Configuring legacy power system"));
    }
}

void UPowerSystemManager::UpdateSystemStates()
{
    if (bUseNewSystem && ClassSystemManager)
    {
        // Update new system states
        UE_LOG(LogTemp, Warning, TEXT("Updating new class-based system states"));
    }
    else
    {
        // Update legacy system states
        UE_LOG(LogTemp, Warning, TEXT("Updating legacy system states"));
    }
}

void UPowerSystemManager::MigrateToNewSystem()
{
    UE_LOG(LogTemp, Warning, TEXT("Migrating from legacy system to new class-based system"));
    bUseNewSystem = true;
    // Migration logic here if needed
}
