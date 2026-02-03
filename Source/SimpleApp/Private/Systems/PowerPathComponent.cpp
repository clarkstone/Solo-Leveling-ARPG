#include "PowerPathComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

UPowerPathComponent::UPowerPathComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    SetIsReplicatedByDefault(true);

    CurrentRank = EPowerRank::F;
    CurrentExperience = 0;
    bIsActive = false;
    bIsUnlocked = false;
    CachedPowerLevel = 0;
    CachedPowerMultiplier = 1.0f;
}

void UPowerPathComponent::BeginPlay()
{
    Super::BeginPlay();
    UpdateCachedData();
}

void UPowerPathComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UPowerPathComponent::InitializePath(const FPowerPathDefinition& InPathDefinition)
{
    PathDefinition = InPathDefinition;
    CurrentRank = EPowerRank::F;
    CurrentExperience = 0;
    bIsUnlocked = false;
    bIsActive = false;
    
    UpdateCachedData();
    UE_LOG(LogTemp, Warning, TEXT("Power Path initialized: %s"), *PathDefinition.PathData.PathName);
}

void UPowerPathComponent::UnlockPath()
{
    if (bIsUnlocked)
    {
        UE_LOG(LogTemp, Warning, TEXT("Path %s is already unlocked"), *PathDefinition.PathData.PathName);
        return;
    }

    bIsUnlocked = true;
    UE_LOG(LogTemp, Warning, TEXT("Power Path unlocked: %s"), *PathDefinition.PathData.PathName);
}

void UPowerPathComponent::ActivatePath()
{
    if (!bIsUnlocked)
    {
        UE_LOG(LogTemp, Warning, TEXT("Cannot activate locked path: %s"), *PathDefinition.PathData.PathName);
        return;
    }

    if (bIsActive)
    {
        UE_LOG(LogTemp, Warning, TEXT("Path %s is already active"), *PathDefinition.PathData.PathName);
        return;
    }

    bIsActive = true;
    OnPathActivated.Broadcast(PathDefinition.PathData.PathName);
    UE_LOG(LogTemp, Warning, TEXT("Power Path activated: %s at rank %d"), *PathDefinition.PathData.PathName, (int32)CurrentRank);
}

void UPowerPathComponent::DeactivatePath()
{
    if (!bIsActive)
    {
        return;
    }

    bIsActive = false;
    UE_LOG(LogTemp, Warning, TEXT("Power Path deactivated: %s"), *PathDefinition.PathData.PathName);
}

bool UPowerPathComponent::CanActivate() const
{
    return bIsUnlocked && !bIsActive;
}

void UPowerPathComponent::AddExperience(int32 ExperienceAmount)
{
    if (!bIsUnlocked)
    {
        UE_LOG(LogTemp, Warning, TEXT("Cannot add experience to locked path: %s"), *PathDefinition.PathData.PathName);
        return;
    }

    CurrentExperience += ExperienceAmount;
    UE_LOG(LogTemp, Warning, TEXT("Added %d experience to path %s (Total: %d)"), ExperienceAmount, *PathDefinition.PathData.PathName, CurrentExperience);

    // Check for rank up
    while (CanRankUp())
    {
        RankUp();
    }
}

bool UPowerPathComponent::CanRankUp() const
{
    if (CurrentRank >= EPowerRank::TrueMonarch)
    {
        return false;
    }

    EPowerRank NextRank = GetNextRank();
    int32 RequiredExperience = GetRequiredExperienceForRank(NextRank);
    return CurrentExperience >= RequiredExperience;
}

void UPowerPathComponent::RankUp()
{
    if (!CanRankUp())
    {
        return;
    }

    EPowerRank OldRank = CurrentRank;
    CurrentRank = GetNextRank();
    
    // Unlock new abilities for this rank
    UpdateAbilities();
    OnRankUpInternal();
    
    // Broadcast rank up event
    OnRankUp.Broadcast(OldRank, CurrentRank);
    
    UE_LOG(LogTemp, Warning, TEXT("Path %s ranked up to %s"), *PathDefinition.PathData.PathName, *GetCurrentRankTitle());
}

EPowerRank UPowerPathComponent::GetNextRank() const
{
    if (CurrentRank >= EPowerRank::TrueMonarch)
    {
        return EPowerRank::TrueMonarch;
    }
    
    return (EPowerRank)((int32)CurrentRank + 1);
}

int32 UPowerPathComponent::GetExperienceToNextRank() const
{
    if (CurrentRank >= EPowerRank::TrueMonarch)
    {
        return 0;
    }

    EPowerRank NextRank = GetNextRank();
    int32 RequiredExperience = GetRequiredExperienceForRank(NextRank);
    return RequiredExperience - CurrentExperience;
}

TArray<FAbilityData> UPowerPathComponent::GetCurrentAbilities() const
{
    return GetAbilitiesForRank(CurrentRank);
}

TArray<FAbilityData> UPowerPathComponent::GetAbilitiesForRank(EPowerRank Rank) const
{
    if (PathDefinition.RankAbilities.Contains(Rank))
    {
        return PathDefinition.RankAbilities[Rank];
    }
    
    return TArray<FAbilityData>();
}

bool UPowerPathComponent::HasAbility(const FString& AbilityName) const
{
    TArray<FAbilityData> CurrentAbilities = GetCurrentAbilities();
    for (const FAbilityData& Ability : CurrentAbilities)
    {
        if (Ability.AbilityName == AbilityName)
        {
            return true;
        }
    }
    return false;
}

FAbilityData UPowerPathComponent::GetAbility(const FString& AbilityName) const
{
    TArray<FAbilityData> CurrentAbilities = GetCurrentAbilities();
    for (const FAbilityData& Ability : CurrentAbilities)
    {
        if (Ability.AbilityName == AbilityName)
        {
            return Ability;
        }
    }
    
    return FAbilityData();
}

int32 UPowerPathComponent::GetPowerLevel() const
{
    return CachedPowerLevel;
}

float UPowerPathComponent::GetPowerMultiplier() const
{
    return CachedPowerMultiplier;
}

FString UPowerPathComponent::GetCurrentRankTitle() const
{
    if (PathDefinition.RankTitles.Contains(CurrentRank))
    {
        return PathDefinition.RankTitles[CurrentRank];
    }
    
    return FString::Printf(TEXT("Rank %d"), (int32)CurrentRank);
}

bool UPowerPathComponent::IsLegendaryPath() const
{
    return PathDefinition.PathData.bIsLegendary;
}

ECoreClass UPowerPathComponent::GetCoreClass() const
{
    return PathDefinition.PathData.CoreClass;
}

FString UPowerPathComponent::GetPathName() const
{
    return PathDefinition.PathData.PathName;
}

void UPowerPathComponent::UpdateAbilities()
{
    TArray<FAbilityData> NewAbilities = GetAbilitiesForRank(CurrentRank);
    for (const FAbilityData& Ability : NewAbilities)
    {
        if (!HasAbility(Ability.AbilityName))
        {
            NotifyAbilityUnlocked(Ability);
        }
    }
}

void UPowerPathComponent::OnRankUpInternal()
{
    UpdateCachedData();
    UpdateAbilities();
}

void UPowerPathComponent::CalculatePowerLevel()
{
    // Base power level from rank
    int32 BasePower = (int32)CurrentRank * 10;
    
    // Add path-specific power level
    if (PathDefinition.RankPowerLevels.Contains(CurrentRank))
    {
        BasePower += PathDefinition.RankPowerLevels[CurrentRank];
    }
    
    // Legendary bonus
    if (IsLegendaryPath())
    {
        BasePower = (int32)(BasePower * 1.5f);
    }
    
    CachedPowerLevel = BasePower;
    
    // Calculate power multiplier
    CachedPowerMultiplier = 1.0f + ((int32)CurrentRank * 0.1f);
    if (IsLegendaryPath())
    {
        CachedPowerMultiplier *= 1.25f;
    }
}

void UPowerPathComponent::NotifyAbilityUnlocked(const FAbilityData& Ability)
{
    OnAbilityUnlocked.Broadcast(Ability);
    UE_LOG(LogTemp, Warning, TEXT("Ability unlocked: %s for path %s"), *Ability.AbilityName, *PathDefinition.PathData.PathName);
}

int32 UPowerPathComponent::GetRequiredExperienceForRank(EPowerRank Rank) const
{
    // Experience requirements scale exponentially
    switch (Rank)
    {
        case EPowerRank::E: return 100;
        case EPowerRank::D: return 250;
        case EPowerRank::C: return 500;
        case EPowerRank::B: return 1000;
        case EPowerRank::A: return 2000;
        case EPowerRank::S: return 4000;
        case EPowerRank::SS: return 8000;
        case EPowerRank::SSS: return 16000;
        case EPowerRank::National: return 32000;
        case EPowerRank::TrueMonarch: return 64000;
        default: return 0;
    }
}

void UPowerPathComponent::UpdateCachedData()
{
    CalculatePowerLevel();
    CachedAbilities.Empty();
    
    // Cache abilities for all ranks up to current
    for (int32 i = 0; i <= (int32)CurrentRank; i++)
    {
        EPowerRank Rank = (EPowerRank)i;
        if (PathDefinition.RankAbilities.Contains(Rank))
        {
            CachedAbilities.Add(Rank, PathDefinition.RankAbilities[Rank]);
        }
    }
}

void UPowerPathComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    DOREPLIFETIME(UPowerPathComponent, CurrentRank);
    DOREPLIFETIME(UPowerPathComponent, CurrentExperience);
    DOREPLIFETIME(UPowerPathComponent, bIsActive);
    DOREPLIFETIME(UPowerPathComponent, bIsUnlocked);
}
