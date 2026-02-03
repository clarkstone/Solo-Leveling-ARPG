#include "ClassSystemManager.h"
#include "PowerPathComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DataTable.h"
#include "Net/UnrealNetwork.h"

UClassSystemManager::UClassSystemManager()
{
    PrimaryComponentTick.bCanEverTick = true;
    SetIsReplicatedByDefault(true);
}

void UClassSystemManager::BeginPlay()
{
    Super::BeginPlay();
    InitializePowerPaths();
    LoadPathDefinitions();
    UE_LOG(LogTemp, Warning, TEXT("Class System Manager initialized"));
}

void UClassSystemManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UClassSystemManager::SelectClass(ECoreClass CoreClass)
{
    if (PlayerProgression.SelectedClass != ECoreClass::None)
    {
        UE_LOG(LogTemp, Warning, TEXT("Class already selected: %d"), (int32)PlayerProgression.SelectedClass);
        return;
    }

    PlayerProgression.SelectedClass = CoreClass;
    OnClassSelected.Broadcast(CoreClass);
    
    // Check for auto-unlocks based on class selection
    CheckForAutoUnlocks();
    
    UE_LOG(LogTemp, Warning, TEXT("Class selected: %d"), (int32)CoreClass);
}

ECoreClass UClassSystemManager::GetSelectedClass() const
{
    return PlayerProgression.SelectedClass;
}

bool UClassSystemManager::HasSelectedClass() const
{
    return PlayerProgression.SelectedClass != ECoreClass::None;
}

bool UClassSystemManager::UnlockPath(const FString& PathName)
{
    if (!HasSelectedClass())
    {
        UE_LOG(LogTemp, Warning, TEXT("Cannot unlock path %s: No class selected"), *PathName);
        return false;
    }

    UPowerPathComponent* PathComponent = GetPath(PathName);
    if (!PathComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("Path %s not found"), *PathName);
        return false;
    }

    if (!ValidatePathForClass(PathName, PlayerProgression.SelectedClass))
    {
        UE_LOG(LogTemp, Warning, TEXT("Path %s not valid for class %d"), *PathName, (int32)PlayerProgression.SelectedClass);
        return false;
    }

    if (PathComponent->bIsUnlocked)
    {
        UE_LOG(LogTemp, Warning, TEXT("Path %s already unlocked"), *PathName);
        return true;
    }

    // Check acquisition requirements
    if (!CheckAcquisitionRequirements(PathComponent->PathDefinition.PathData))
    {
        UE_LOG(LogTemp, Warning, TEXT("Requirements not met for path %s"), *PathName);
        return false;
    }

    PathComponent->UnlockPath();
    PlayerProgression.UnlockedPaths.Add(PathName);
    PlayerProgression.PathRanks.Add(PathName, EPowerRank::F);
    PlayerProgression.PathExperience.Add(PathName, 0);
    
    if (!UnlockedPaths.Contains(PathComponent))
    {
        UnlockedPaths.Add(PathComponent);
    }
    
    OnPathUnlocked.Broadcast(PathName, PathComponent->GetCoreClass());
    UpdatePlayerProgression();
    
    UE_LOG(LogTemp, Warning, TEXT("Path unlocked: %s"), *PathName);
    return true;
}

bool UClassSystemManager::ActivatePath(const FString& PathName)
{
    UPowerPathComponent* PathComponent = GetPath(PathName);
    if (!PathComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("Path %s not found"), *PathName);
        return false;
    }

    if (!PathComponent->CanActivate())
    {
        UE_LOG(LogTemp, Warning, TEXT("Cannot activate path %s"), *PathName);
        return false;
    }

    PathComponent->ActivatePath();
    
    if (!ActivePaths.Contains(PathComponent))
    {
        ActivePaths.Add(PathComponent);
    }
    
    if (!PlayerProgression.ActivePaths.Contains(PathName))
    {
        PlayerProgression.ActivePaths.Add(PathName);
    }
    
    OnPathActivated.Broadcast(PathName, true);
    UpdateActivePaths();
    
    UE_LOG(LogTemp, Warning, TEXT("Path activated: %s"), *PathName);
    return true;
}

bool UClassSystemManager::DeactivatePath(const FString& PathName)
{
    UPowerPathComponent* PathComponent = GetPath(PathName);
    if (!PathComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("Path %s not found"), *PathName);
        return false;
    }

    PathComponent->DeactivatePath();
    ActivePaths.Remove(PathComponent);
    PlayerProgression.ActivePaths.Remove(PathName);
    
    OnPathActivated.Broadcast(PathName, false);
    UpdateActivePaths();
    
    UE_LOG(LogTemp, Warning, TEXT("Path deactivated: %s"), *PathName);
    return true;
}

bool UClassSystemManager::IsPathUnlocked(const FString& PathName) const
{
    UPowerPathComponent* PathComponent = GetPath(PathName);
    return PathComponent ? PathComponent->bIsUnlocked : false;
}

bool UClassSystemManager::IsPathActive(const FString& PathName) const
{
    UPowerPathComponent* PathComponent = GetPath(PathName);
    return PathComponent ? PathComponent->bIsActive : false;
}

UPowerPathComponent* UClassSystemManager::GetPath(const FString& PathName) const
{
    if (PathComponents.Contains(PathName))
    {
        return PathComponents[PathName];
    }
    return nullptr;
}

TArray<UPowerPathComponent*> UClassSystemManager::GetPathsForClass(ECoreClass CoreClass) const
{
    TArray<UPowerPathComponent*> ClassPaths;
    for (const auto& PathPair : PathComponents)
    {
        UPowerPathComponent* PathComponent = PathPair.Value;
        if (PathComponent && PathComponent->GetCoreClass() == CoreClass)
        {
            ClassPaths.Add(PathComponent);
        }
    }
    return ClassPaths;
}

TArray<UPowerPathComponent*> UClassSystemManager::GetAvailablePaths() const
{
    if (!HasSelectedClass())
    {
        return TArray<UPowerPathComponent*>();
    }
    
    return GetPathsForClass(PlayerProgression.SelectedClass);
}

void UClassSystemManager::AddPathExperience(const FString& PathName, int32 ExperienceAmount)
{
    UPowerPathComponent* PathComponent = GetPath(PathName);
    if (!PathComponent)
    {
        UE_LOG(LogTemp, Warning, TEXT("Path %s not found"), *PathName);
        return;
    }

    EPowerRank OldRank = PathComponent->CurrentRank;
    PathComponent->AddExperience(ExperienceAmount);
    
    // Update progression data
    if (PlayerProgression.PathExperience.Contains(PathName))
    {
        PlayerProgression.PathExperience[PathName] = PathComponent->CurrentExperience;
    }
    else
    {
        PlayerProgression.PathExperience.Add(PathName, PathComponent->CurrentExperience);
    }
    
    if (PlayerProgression.PathRanks.Contains(PathName))
    {
        PlayerProgression.PathRanks[PathName] = PathComponent->CurrentRank;
    }
    else
    {
        PlayerProgression.PathRanks.Add(PathName, PathComponent->CurrentRank);
    }
    
    UpdatePlayerProgression();
}

EPowerRank UClassSystemManager::GetPathRank(const FString& PathName) const
{
    UPowerPathComponent* PathComponent = GetPath(PathName);
    return PathComponent ? PathComponent->CurrentRank : EPowerRank::F;
}

int32 UClassSystemManager::GetTotalPowerLevel() const
{
    int32 TotalPower = 0;
    for (UPowerPathComponent* PathComponent : ActivePaths)
    {
        if (PathComponent)
        {
            TotalPower += PathComponent->GetPowerLevel();
        }
    }
    return TotalPower;
}

float UClassSystemManager::GetTotalPowerMultiplier() const
{
    float TotalMultiplier = 1.0f;
    for (UPowerPathComponent* PathComponent : ActivePaths)
    {
        if (PathComponent)
        {
            TotalMultiplier *= PathComponent->GetPowerMultiplier();
        }
    }
    return TotalMultiplier;
}

bool UClassSystemManager::CanUnlockMultiPath() const
{
    // Multi-path access requires at least one path at rank A or higher
    for (const auto& RankPair : PlayerProgression.PathRanks)
    {
        if (RankPair.Value >= EPowerRank::A)
        {
            return true;
        }
    }
    return false;
}

void UClassSystemManager::UnlockMultiPathAccess()
{
    if (!PlayerProgression.bHasMultiPathAccess)
    {
        PlayerProgression.bHasMultiPathAccess = true;
        CheckForAutoUnlocks();
        UE_LOG(LogTemp, Warning, TEXT("Multi-path access unlocked"));
    }
}

bool UClassSystemManager::HasMultiPathAccess() const
{
    return PlayerProgression.bHasMultiPathAccess;
}

TArray<FString> UClassSystemManager::GetHybridAbilities() const
{
    TArray<FString> HybridAbilities;
    
    // Combine abilities from multiple active paths
    TSet<FString> AllAbilityNames;
    for (UPowerPathComponent* PathComponent : ActivePaths)
    {
        if (PathComponent)
        {
            TArray<FAbilityData> Abilities = PathComponent->GetCurrentAbilities();
            for (const FAbilityData& Ability : Abilities)
            {
                AllAbilityNames.Add(Ability.AbilityName);
            }
        }
    }
    
    for (const FString& AbilityName : AllAbilityNames)
    {
        HybridAbilities.Add(AbilityName);
    }
    
    return HybridAbilities;
}

bool UClassSystemManager::CheckAcquisitionRequirements(const FPowerPathData& PathData) const
{
    switch (PathData.AcquisitionMethod)
    {
        case EAcquisitionMethod::Default:
            return true;
            
        case EAcquisitionMethod::StoryEvent:
            for (const FString& RequiredEvent : PathData.RequiredQuests)
            {
                if (!TriggeredStoryEvents.Contains(RequiredEvent))
                {
                    return false;
                }
            }
            return true;
            
        case EAcquisitionMethod::GuildUnlock:
            for (const FString& RequiredGuild : PathData.RequiredGuilds)
            {
                if (!JoinedGuilds.Contains(RequiredGuild))
                {
                    return false;
                }
            }
            return true;
            
        case EAcquisitionMethod::QuestReward:
            for (const FString& RequiredQuest : PathData.RequiredQuests)
            {
                if (!CompletedQuests.Contains(RequiredQuest))
                {
                    return false;
                }
            }
            return true;
            
        case EAcquisitionMethod::Achievement:
            for (const FString& RequiredAchievement : PathData.RequiredQuests)
            {
                if (!UnlockedAchievements.Contains(RequiredAchievement))
                {
                    return false;
                }
            }
            return true;
            
        default:
            return true;
    }
}

void UClassSystemManager::OnStoryEvent(const FString& EventName)
{
    if (!TriggeredStoryEvents.Contains(EventName))
    {
        TriggeredStoryEvents.Add(EventName);
        CheckForAutoUnlocks();
        UE_LOG(LogTemp, Warning, TEXT("Story event triggered: %s"), *EventName);
    }
}

void UClassSystemManager::OnGuildJoined(const FString& GuildName)
{
    if (!JoinedGuilds.Contains(GuildName))
    {
        JoinedGuilds.Add(GuildName);
        CheckForAutoUnlocks();
        UE_LOG(LogTemp, Warning, TEXT("Guild joined: %s"), *GuildName);
    }
}

void UClassSystemManager::OnQuestCompleted(const FString& QuestName)
{
    if (!CompletedQuests.Contains(QuestName))
    {
        CompletedQuests.Add(QuestName);
        CheckForAutoUnlocks();
        UE_LOG(LogTemp, Warning, TEXT("Quest completed: %s"), *QuestName);
    }
}

void UClassSystemManager::OnAchievementUnlocked(const FString& AchievementName)
{
    if (!UnlockedAchievements.Contains(AchievementName))
    {
        UnlockedAchievements.Add(AchievementName);
        CheckForAutoUnlocks();
        UE_LOG(LogTemp, Warning, TEXT("Achievement unlocked: %s"), *AchievementName);
    }
}

TArray<FString> UClassSystemManager::GetAllPathNames() const
{
    TArray<FString> PathNames;
    for (const auto& PathPair : PathComponents)
    {
        PathNames.Add(PathPair.Key);
    }
    return PathNames;
}

TArray<FString> UClassSystemManager::GetActivePathNames() const
{
    TArray<FString> ActivePathNames;
    for (UPowerPathComponent* PathComponent : ActivePaths)
    {
        if (PathComponent)
        {
            ActivePathNames.Add(PathComponent->GetPathName());
        }
    }
    return ActivePathNames;
}

TArray<FAbilityData> UClassSystemManager::GetAllActiveAbilities() const
{
    TArray<FAbilityData> AllAbilities;
    for (UPowerPathComponent* PathComponent : ActivePaths)
    {
        if (PathComponent)
        {
            TArray<FAbilityData> PathAbilities = PathComponent->GetCurrentAbilities();
            AllAbilities.Append(PathAbilities);
        }
    }
    return AllAbilities;
}

bool UClassSystemManager::HasAbility(const FString& AbilityName) const
{
    for (UPowerPathComponent* PathComponent : ActivePaths)
    {
        if (PathComponent && PathComponent->HasAbility(AbilityName))
        {
            return true;
        }
    }
    return false;
}

void UClassSystemManager::InitializePowerPaths()
{
    // This will be populated with all 45 paths
    // For now, we'll create empty components
    UE_LOG(LogTemp, Warning, TEXT("Initializing power paths..."));
}

void UClassSystemManager::LoadPathDefinitions()
{
    // Load path definitions from data tables or create them programmatically
    // This will contain all 45 path definitions
    UE_LOG(LogTemp, Warning, TEXT("Loading path definitions..."));
}

void UClassSystemManager::UpdateActivePaths()
{
    ActivePaths.Empty();
    for (UPowerPathComponent* PathComponent : UnlockedPaths)
    {
        if (PathComponent && PathComponent->bIsActive)
        {
            ActivePaths.Add(PathComponent);
        }
    }
}

void UClassSystemManager::CheckForAutoUnlocks()
{
    // Check for paths that can be automatically unlocked
    for (const auto& PathPair : PathComponents)
    {
        const FString& PathName = PathPair.Key;
        UPowerPathComponent* PathComponent = PathPair.Value;
        
        if (PathComponent && !PathComponent->bIsUnlocked)
        {
            // Check if path can be unlocked for selected class or with multi-path access
            bool CanUnlock = false;
            
            if (HasSelectedClass() && ValidatePathForClass(PathName, PlayerProgression.SelectedClass))
            {
                CanUnlock = CheckAcquisitionRequirements(PathComponent->PathDefinition.PathData);
            }
            else if (HasMultiPathAccess())
            {
                CanUnlock = CheckAcquisitionRequirements(PathComponent->PathDefinition.PathData);
            }
            
            if (CanUnlock)
            {
                UnlockPath(PathName);
            }
        }
    }
}

UPowerPathComponent* UClassSystemManager::CreatePathComponent(const FString& PathName)
{
    UPowerPathComponent* PathComponent = NewObject<UPowerPathComponent>(this);
    if (PathComponent)
    {
        RegisterPathComponent(PathComponent);
    }
    return PathComponent;
}

void UClassSystemManager::RegisterPathComponent(UPowerPathComponent* PathComponent)
{
    if (PathComponent)
    {
        FString PathName = PathComponent->GetPathName();
        PathComponents.Add(PathName, PathComponent);
        AllPowerPaths.Add(PathComponent);
    }
}

void UClassSystemManager::UnregisterPathComponent(UPowerPathComponent* PathComponent)
{
    if (PathComponent)
    {
        FString PathName = PathComponent->GetPathName();
        PathComponents.Remove(PathName);
        AllPowerPaths.Remove(PathComponent);
        UnlockedPaths.Remove(PathComponent);
        ActivePaths.Remove(PathComponent);
    }
}

bool UClassSystemManager::ValidatePathForClass(const FString& PathName, ECoreClass CoreClass) const
{
    UPowerPathComponent* PathComponent = GetPath(PathName);
    return PathComponent ? PathComponent->GetCoreClass() == CoreClass : false;
}

void UClassSystemManager::UpdatePlayerProgression()
{
    PlayerProgression.UnlockedPaths = GetActivePathNames();
    // Update other progression data as needed
}

void UClassSystemManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    DOREPLIFETIME(UClassSystemManager, PlayerProgression);
    DOREPLIFETIME(UClassSystemManager, CompletedQuests);
    DOREPLIFETIME(UClassSystemManager, JoinedGuilds);
    DOREPLIFETIME(UClassSystemManager, UnlockedAchievements);
    DOREPLIFETIME(UClassSystemManager, TriggeredStoryEvents);
}
