#include "BOSS_CLASSIFICATION_SYSTEM.h"
#include "Engine/DataTable.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UBOSS_CLASSIFICATION_SYSTEM::UBOSS_CLASSIFICATION_SYSTEM()
{
    PrimaryComponentTick.bCanEverTick = false;
    BossDatabase = nullptr;
}

void UBOSS_CLASSIFICATION_SYSTEM::BeginPlay()
{
    Super::BeginPlay();
    LoadBossDatabase();
    UE_LOG(LogTemp, Warning, TEXT("Boss Classification System Initialized"));
}

void UBOSS_CLASSIFICATION_SYSTEM::LoadBossDatabase()
{
    if (!BossDatabase)
    {
        UE_LOG(LogTemp, Warning, TEXT("Boss Database not assigned!"));
        return;
    }

    // Load all boss data from the data table
    TArray<FName> RowNames;
    BossDatabase->GetRowNames(RowNames);

    for (const FName& RowName : RowNames)
    {
        const FBossData* BossRow = BossDatabase->FindRow<FBossData>(RowName, TEXT("Looking for boss data"));
        if (BossRow)
        {
            ActiveBosses.Add(RowName, *BossRow);
            
            // Track defeated unique bosses
            if (BossRow->HasBeenDefeated && BossRow->BossType == EBossType::BT_UniqueBoss)
            {
                DefeatedUniqueBosses.Add(RowName);
            }
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("Loaded %d bosses from database"), ActiveBosses.Num());
}

bool UBOSS_CLASSIFICATION_SYSTEM::SpawnBoss(FName BossID, FVector SpawnLocation, FRotator SpawnRotation)
{
    FBossData* BossData = FindBossData(BossID);
    if (!BossData)
    {
        UE_LOG(LogTemp, Warning, TEXT("Boss %s not found in database"), *BossID.ToString());
        return false;
    }

    // Check if boss can be spawned
    if (BossData->HasBeenDefeated && !BossData->RespawnEnabled)
    {
        UE_LOG(LogTemp, Warning, TEXT("Boss %s has been defeated and does not respawn"), *BossID.ToString());
        return false;
    }

    if (BossData->HasBeenDefeated && BossData->BossType == EBossType::BT_UniqueBoss)
    {
        UE_LOG(LogTemp, Warning, TEXT("Unique Boss %s cannot respawn"), *BossID.ToString());
        return false;
    }

    // Update spawn location
    BossData->SpawnLocation = SpawnLocation;
    BossData->SpawnRotation = SpawnRotation;

    // Spawn the boss actor (this would be implemented with actual boss spawning logic)
    UE_LOG(LogTemp, Warning, TEXT("Spawning boss %s at location: %s"), *BossID.ToString(), *SpawnLocation.ToString());

    // Trigger boss encountered event
    OnBossEncountered.Broadcast(*BossData);

    return true;
}

bool UBOSS_CLASSIFICATION_SYSTEM::CheckSpawnConditions(FName BossID, AActor* TriggeringActor)
{
    FBossData* BossData = FindBossData(BossID);
    if (!BossData)
    {
        return false;
    }

    switch (BossData->SpawnCondition)
    {
        case ESpawnCondition::SC_Static:
            return CheckStaticSpawn(BossID);
            
        case ESpawnCondition::SC_Triggered:
            return CheckTriggeredSpawn(BossID, TriggeringActor);
            
        case ESpawnCondition::SC_Hidden:
            return CheckHiddenSpawn(BossID, TriggeringActor);
            
        case ESpawnCondition::SC_UniqueScenario:
            return CheckUniqueScenario(BossID, TriggeringActor);
            
        case ESpawnCondition::SC_Random:
            return CheckRandomSpawn(BossID);
            
        case ESpawnCondition::SC_Temporal:
            return CheckTemporalSpawn(BossID);
            
        default:
            return false;
    }
}

void UBOSS_CLASSIFICATION_SYSTEM::StartBossEncounter(FName BossID)
{
    FBossData* BossData = FindBossData(BossID);
    if (!BossData)
    {
        UE_LOG(LogTemp, Warning, TEXT("Cannot start encounter with boss %s - not found"), *BossID.ToString());
        return;
    }

    // Initialize boss phase
    CurrentBossPhases.Add(BossID, EBossPhase::BP_Phase1);
    
    // Scale difficulty based on player count and level
    ScaleBossDifficulty(BossID, 1, 50); // Default to 1 player, level 50
    
    // Trigger phase change event
    OnBossPhaseChanged.Broadcast(EBossPhase::BP_Phase1);
    
    UE_LOG(LogTemp, Warning, TEXT("Starting boss encounter with %s"), *BossData->BossName);
}

void UBOSS_CLASSIFICATION_SYSTEM::AdvanceBossPhase()
{
    // Find the current active boss (simplified - in practice would track specific boss)
    for (auto& BossPhasePair : CurrentBossPhases)
    {
        EBossPhase CurrentPhase = BossPhasePair.Value;
        EBossPhase NextPhase = static_cast<EBossPhase>(static_cast<int32>(CurrentPhase) + 1);
        
        if (NextPhase <= EBossPhase::BP_FinalPhase)
        {
            BossPhasePair.Value = NextPhase;
            OnBossPhaseChanged.Broadcast(NextPhase);
            
            UE_LOG(LogTemp, Warning, TEXT("Boss advancing to phase %d"), static_cast<int32>(NextPhase));
            break;
        }
    }
}

void UBOSS_CLASSIFICATION_SYSTEM::HandleBossDefeated(const FString& DefeatMethod)
{
    // Find the current active boss
    FName DefeatedBossID;
    FBossData* DefeatedBossData = nullptr;
    
    for (auto& BossPair : ActiveBosses)
    {
        if (CurrentBossPhases.Contains(BossPair.Key))
        {
            DefeatedBossID = BossPair.Key;
            DefeatedBossData = &BossPair.Value;
            break;
        }
    }
    
    if (!DefeatedBossData)
    {
        UE_LOG(LogTemp, Warning, TEXT("No active boss found to mark as defeated"));
        return;
    }

    // Validate defeat method
    if (!ValidateBossDefeatMethod(DefeatMethod, *DefeatedBossData))
    {
        UE_LOG(LogTemp, Warning, TEXT("Invalid defeat method for boss %s: %s"), *DefeatedBossID.ToString(), *DefeatMethod);
        // Still mark as defeated but with reduced rewards
    }

    // Mark boss as defeated
    DefeatedBossData->HasBeenDefeated = true;
    CurrentBossPhases.Remove(DefeatedBossID);
    
    // Calculate and distribute loot
    FBossLootRewards LootRewards = CalculateLoot(DefeatedBossID, DefeatMethod);
    
    // Trigger events
    OnBossDefeated.Broadcast(*DefeatedBossData);
    OnBossLootDropped.Broadcast(LootRewards, DefeatMethod);
    
    // Apply world changes for unique bosses
    if (DefeatedBossData->IsWorldChanging)
    {
        ApplyWorldChanges(*DefeatedBossData);
    }
    
    // Handle unique boss defeat
    if (DefeatedBossData->BossType == EBossType::BT_UniqueBoss)
    {
        ProcessUniqueBossDefeat(DefeatedBossID);
        DefeatedUniqueBosses.Add(DefeatedBossID);
    }
    
    // Save boss state
    SaveBossState();
    
    UE_LOG(LogTemp, Warning, TEXT("Boss %s defeated with method: %s"), *DefeatedBossData->BossName, *DefeatMethod);
}

void UBOSS_CLASSIFICATION_SYSTEM::ScaleBossDifficulty(FName BossID, int32 PlayerCount, int32 AveragePlayerLevel)
{
    FBossData* BossData = FindBossData(BossID);
    if (!BossData)
    {
        return;
    }

    const FBossDifficultyScaling& Scaling = BossData->DifficultyScaling;
    
    // Apply level cap
    int32 EffectivePlayerLevel = FMath::Min(AveragePlayerLevel, static_cast<int32>(Scaling.LevelCap));
    
    // Scale HP and attack power
    float HPMultiplier = FMath::Pow(Scaling.PlayerLevelScaling, (EffectivePlayerLevel - 50.0f) / 10.0f);
    float AttackMultiplier = FMath::Pow(Scaling.PlayerLevelScaling, (EffectivePlayerLevel - 50.0f) / 10.0f);
    
    // Apply party size scaling
    if (PlayerCount > 1)
    {
        HPMultiplier *= FMath::Pow(Scaling.PartySizeMultiplier, PlayerCount - 1);
        AttackMultiplier *= FMath::Pow(Scaling.PartySizeMultiplier, PlayerCount - 1);
    }
    
    float ScaledHP = Scaling.BaseHP * HPMultiplier;
    float ScaledAttack = Scaling.BaseAttackPower * AttackMultiplier;
    
    UE_LOG(LogTemp, Warning, TEXT("Scaling boss %s: HP=%.0f, Attack=%.0f (Players: %d, Avg Level: %d)"), 
           *BossID.ToString(), ScaledHP, ScaledAttack, PlayerCount, EffectivePlayerLevel);
}

FBossData UBOSS_CLASSIFICATION_SYSTEM::GetBossData(FName BossID)
{
    FBossData* BossData = FindBossData(BossID);
    if (BossData)
    {
        return *BossData;
    }
    
    return FBossData(); // Return empty struct if not found
}

bool UBOSS_CLASSIFICATION_SYSTEM::IsBossDefeated(FName BossID)
{
    FBossData* BossData = FindBossData(BossID);
    return BossData ? BossData->HasBeenDefeated : false;
}

TArray<FBossData> UBOSS_CLASSIFICATION_SYSTEM::GetAvailableBosses()
{
    TArray<FBossData> AvailableBosses;
    
    for (const auto& BossPair : ActiveBosses)
    {
        if (!BossPair.Value.HasBeenDefeated || BossPair.Value.RespawnEnabled)
        {
            AvailableBosses.Add(BossPair.Value);
        }
    }
    
    return AvailableBosses;
}

TArray<FBossData> UBOSS_CLASSIFICATION_SYSTEM::GetUniqueBosses()
{
    TArray<FBossData> UniqueBosses;
    
    for (const auto& BossPair : ActiveBosses)
    {
        if (BossPair.Value.BossType == EBossType::BT_UniqueBoss)
        {
            UniqueBosses.Add(BossPair.Value);
        }
    }
    
    return UniqueBosses;
}

bool UBOSS_CLASSIFICATION_SYSTEM::CanRespawnBoss(FName BossID)
{
    FBossData* BossData = FindBossData(BossID);
    if (!BossData)
    {
        return false;
    }
    
    // Unique bosses never respawn
    if (BossData->BossType == EBossType::BT_UniqueBoss)
    {
        return false;
    }
    
    // Check if respawn is enabled and time has passed
    if (BossData->RespawnEnabled && BossData->HasBeenDefeated)
    {
        // In practice, would check actual respawn timer
        return true;
    }
    
    return false;
}

// Boss Classification Functions
bool UBOSS_CLASSIFICATION_SYSTEM::IsSubBoss(FName BossID)
{
    FBossData* BossData = FindBossData(BossID);
    return BossData ? BossData->BossType == EBossType::BT_SubBoss : false;
}

bool UBOSS_CLASSIFICATION_SYSTEM::IsAreaBoss(FName BossID)
{
    FBossData* BossData = FindBossData(BossID);
    return BossData ? BossData->BossType == EBossType::BT_AreaBoss : false;
}

bool UBOSS_CLASSIFICATION_SYSTEM::IsUniqueBoss(FName BossID)
{
    FBossData* BossData = FindBossData(BossID);
    return BossData ? BossData->BossType == EBossType::BT_UniqueBoss : false;
}

// Spawn Condition Functions
bool UBOSS_CLASSIFICATION_SYSTEM::CheckStaticSpawn(FName BossID)
{
    FBossData* BossData = FindBossData(BossID);
    if (!BossData)
    {
        return false;
    }
    
    // Static spawns are always available if not defeated
    return !BossData->HasBeenDefeated;
}

bool UBOSS_CLASSIFICATION_SYSTEM::CheckTriggeredSpawn(FName BossID, AActor* TriggeringActor)
{
    FBossData* BossData = FindBossData(BossID);
    if (!BossData || !TriggeringActor)
    {
        return false;
    }
    
    // Check if player has required quest progress or items
    // This would be implemented with actual quest system integration
    UE_LOG(LogTemp, Warning, TEXT("Checking triggered spawn conditions for %s"), *BossID.ToString());
    return true; // Placeholder
}

bool UBOSS_CLASSIFICATION_SYSTEM::CheckHiddenSpawn(FName BossID, AActor* DiscoveringActor)
{
    FBossData* BossData = FindBossData(BossID);
    if (!BossData || !DiscoveringActor)
    {
        return false;
    }
    
    // Check if player has discovered the hidden area
    UE_LOG(LogTemp, Warning, TEXT("Checking hidden spawn conditions for %s"), *BossID.ToString());
    return true; // Placeholder
}

bool UBOSS_CLASSIFICATION_SYSTEM::CheckUniqueScenario(FName BossID, AActor* TriggeringActor)
{
    FBossData* BossData = FindBossData(BossID);
    if (!BossData || !TriggeringActor)
    {
        return false;
    }
    
    // Check complex unknown conditions
    UE_LOG(LogTemp, Warning, TEXT("Checking unique scenario conditions for %s"), *BossID.ToString());
    return FMath::RandRange(0, 100) < 5; // Placeholder: 5% chance
}

bool UBOSS_CLASSIFICATION_SYSTEM::CheckRandomSpawn(FName BossID)
{
    FBossData* BossData = FindBossData(BossID);
    if (!BossData)
    {
        return false;
    }
    
    // Random chance for Colossi to appear anywhere, anytime
    if (BossData->BossType == EBossType::BT_UniqueBoss)
    {
        return FMath::RandRange(0, 1000) < 1; // 0.1% chance per check
    }
    
    return false;
}

bool UBOSS_CLASSIFICATION_SYSTEM::CheckTemporalSpawn(FName BossID)
{
    FBossData* BossData = FindBossData(BossID);
    if (!BossData)
    {
        return false;
    }
    
    // Check time of day or environmental conditions
    // This would integrate with game's time/weather system
    UE_LOG(LogTemp, Warning, TEXT("Checking temporal spawn conditions for %s"), *BossID.ToString());
    return true; // Placeholder
}

// Loot Distribution Functions
FBossLootRewards UBOSS_CLASSIFICATION_SYSTEM::CalculateLoot(FName BossID, const FString& DefeatMethod)
{
    FBossData* BossData = FindBossData(BossID);
    if (!BossData)
    {
        return FBossLootRewards();
    }
    
    FBossLootRewards CalculatedLoot = BossData->LootRewards;
    
    // Adjust loot based on defeat method
    if (!IsLootMethodValid(DefeatMethod, BossID))
    {
        // Reduce rewards for invalid defeat methods
        CalculatedLoot.LegendaryItems.Empty();
        CalculatedLoot.GrantsNewSkill = false;
        CalculatedLoot.GrantedSkill = NAME_None;
    }
    
    return CalculatedLoot;
}

void UBOSS_CLASSIFICATION_SYSTEM::DistributeLoot(const FBossLootRewards& LootRewards, AActor* DefeatingActor)
{
    if (!DefeatingActor)
    {
        return;
    }
    
    // Grant experience and gold
    // This would integrate with the player's progression system
    UE_LOG(LogTemp, Warning, TEXT("Distributing loot: %d EXP, %d Gold"), LootRewards.ExperienceReward, LootRewards.GoldReward);
    
    // Grant items
    for (const FName& Item : LootRewards.UniqueItems)
    {
        UE_LOG(LogTemp, Warning, TEXT("Granting unique item: %s"), *Item.ToString());
    }
    
    for (const FName& Item : LootRewards.RareMaterials)
    {
        UE_LOG(LogTemp, Warning, TEXT("Granting rare material: %s"), *Item.ToString());
    }
    
    for (const FName& Item : LootRewards.LegendaryItems)
    {
        UE_LOG(LogTemp, Warning, TEXT("Granting legendary item: %s"), *Item.ToString());
    }
    
    // Grant special key item
    if (!LootRewards.SpecialKeyItem.IsNone())
    {
        UE_LOG(LogTemp, Warning, TEXT("Granting special key item: %s"), *LootRewards.SpecialKeyItem.ToString());
    }
    
    // Grant new skill
    if (LootRewards.GrantsNewSkill && !LootRewards.GrantedSkill.IsNone())
    {
        UE_LOG(LogTemp, Warning, TEXT("Granting new skill: %s"), *LootRewards.GrantedSkill.ToString()));
    }
}

bool UBOSS_CLASSIFICATION_SYSTEM::IsLootMethodValid(const FString& DefeatMethod, const FBossData& BossData)
{
    // Check if defeat method meets requirements for full rewards
    // Example: Wezaemon requires specific method for Tome of Truth
    if (BossData.BossID == FName("Wezaemon"))
    {
        return DefeatMethod == "HonorVictory"; // Example condition
    }
    
    return true; // Default to valid
}

// World State Functions
void UBOSS_CLASSIFICATION_SYSTEM::ApplyWorldChanges(const FBossData& BossData)
{
    if (!BossData.IsWorldChanging)
    {
        return;
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Applying world changes for defeated boss: %s"), *BossData.BossName);
    
    // Unlock new areas
    UnlockNewAreas(BossData);
    
    // Trigger story progression
    TriggerStoryProgression(BossData);
    
    // Notify other systems of world state changes
    // This would integrate with world management systems
}

void UBOSS_CLASSIFICATION_SYSTEM::UnlockNewAreas(const FBossData& BossData)
{
    UE_LOG(LogTemp, Warning, TEXT("Unlocking new areas after defeating %s"), *BossData.BossName));
    // This would integrate with the world/area management system
}

void UBOSS_CLASSIFICATION_SYSTEM::TriggerStoryProgression(const FBossData& BossData)
{
    UE_LOG(LogTemp, Warning, TEXT("Triggering story progression after defeating %s"), *BossData.BossName);
    // This would integrate with the quest/story system
}

void UBOSS_CLASSIFICATION_SYSTEM::ProcessUniqueBossDefeat(FName BossID)
{
    UE_LOG(LogTemp, Warning, TEXT("Processing unique boss defeat: %s"), *BossID.ToString());
    
    // Handle special Colossus defeat logic
    HandleColossusDefeat(BossID);
    
    // Notify server/world of the defeat
    // This would integrate with multiplayer/network systems
}

void UBOSS_CLASSIFICATION_SYSTEM::HandleColossusDefeat(FName BossID)
{
    UE_LOG(LogTemp, Warning, TEXT("Colossus %s has been defeated! This is a world-changing event."), *BossID.ToString());
    
    // Create server-wide notification
    // Grant server-wide bonuses
    // Update world state permanently
}

void UBOSS_CLASSIFICATION_SYSTEM::SaveBossState()
{
    UE_LOG(LogTemp, Warning, TEXT("Saving boss state to persistent storage"));
    // This would integrate with save game system
}

FBossData* UBOSS_CLASSIFICATION_SYSTEM::FindBossData(FName BossID)
{
    return ActiveBosses.Find(BossID);
}

bool UBOSS_CLASSIFICATION_SYSTEM::ValidateBossDefeatMethod(const FString& Method, const FBossData& BossData)
{
    // Additional validation logic for specific boss defeat methods
    return IsLootMethodValid(Method, BossData);
}
