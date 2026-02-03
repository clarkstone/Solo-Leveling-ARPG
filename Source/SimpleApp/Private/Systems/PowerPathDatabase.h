#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PowerSystemCore.h"
#include "PowerPathDatabase.generated.h"

UCLASS()
class SIMPLEAPP_API UPowerPathDatabase : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    // Initialize all 45 power paths
    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static void InitializeAllPaths();

    // Get path definition by name
    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetPathDefinition(const FString& PathName);

    // Get all paths for a specific class
    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static TArray<FPowerPathDefinition> GetPathsForClass(ECoreClass CoreClass);

    // Get all legendary paths
    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static TArray<FPowerPathDefinition> GetLegendaryPaths();

    // Get all available paths
    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static TArray<FPowerPathDefinition> GetAllPaths();

    // Fighter Paths
    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetBeastKingPath();

    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetDragonheartPath();

    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetInfernalWarlordPath();

    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetStormHeraldPath();

    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetBloodKnightPath();

    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetCelestialCrusaderPath();

    // Mage Paths
    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetHighMagePath();

    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetInfernalArcanistPath();

    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetFrostbinderPath();

    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetStormcallerPath();

    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetGravebinderPath();

    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetDemonologistPath();

    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetChronomancerPath();

    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetNightmareWeaverPath();

    // Assassin Paths
    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetShadowMonarchPath();

    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetNightStalkerPath();

    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetVenombladePath();

    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetPhantomPath();

    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetCrimsonEclipsePath();

    // Tank Paths
    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetIronGuardianPath();

    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetStoneheartGuardianPath();

    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetDivineAegisPath();

    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetDuskDreadnoughtPath();

    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetImmortalBastionPath();

    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetSpellshieldWardenPath();

    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetGravityTitanPath();

    // Ranger Paths
    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetWildHuntPath();

    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetDeadeyeSniperPath();

    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetTempestRangerPath();

    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetVenomstrikeArcherPath();

    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetSylvanSentinelPath();

    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetPhantomArcherPath();

    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetDemonbaneMarksmanPath();

    // Healer Paths
    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetLightWeaverPath();

    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetNaturesTouchPath();

    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetBloodMenderPath();

    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetSpiritChannelerPath();

    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetPainAlchemistPath();

    UFUNCTION(BlueprintCallable, Category = "Power Path Database")
    static FPowerPathDefinition GetPsychicHealerPath();

private:
    // Helper functions to create abilities
    static FAbilityData CreateAbility(const FString& Name, const FString& Description, EPowerRank Rank, int32 ManaCost, float Cooldown, float Range, float Damage);
    static void AddAbilityToPath(FPowerPathDefinition& Path, EPowerRank Rank, const FAbilityData& Ability);
    static void SetRankTitle(FPowerPathDefinition& Path, EPowerRank Rank, const FString& Title);
    static void SetRankPowerLevel(FPowerPathDefinition& Path, EPowerRank Rank, int32 PowerLevel);

    // Static database storage
    static TMap<FString, FPowerPathDefinition> PathDatabase;
    static bool bInitialized;
};
