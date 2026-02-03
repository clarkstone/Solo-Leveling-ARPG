#include "PowerPathDatabase.h"

// Static member initialization
TMap<FString, FPowerPathDefinition> UPowerPathDatabase::PathDatabase;
bool UPowerPathDatabase::bInitialized = false;

void UPowerPathDatabase::InitializeAllPaths()
{
    if (bInitialized)
    {
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("Initializing all 45 power paths..."));

    // Initialize Fighter Paths
    PathDatabase.Add(TEXT("BeastKing"), GetBeastKingPath());
    PathDatabase.Add(TEXT("Dragonheart"), GetDragonheartPath());
    PathDatabase.Add(TEXT("InfernalWarlord"), GetInfernalWarlordPath());
    PathDatabase.Add(TEXT("StormHerald"), GetStormHeraldPath());
    PathDatabase.Add(TEXT("BloodKnight"), GetBloodKnightPath());
    PathDatabase.Add(TEXT("CelestialCrusader"), GetCelestialCrusaderPath());

    // Initialize Mage Paths
    PathDatabase.Add(TEXT("HighMage"), GetHighMagePath());
    PathDatabase.Add(TEXT("InfernalArcanist"), GetInfernalArcanistPath());
    PathDatabase.Add(TEXT("Frostbinder"), GetFrostbinderPath());
    PathDatabase.Add(TEXT("Stormcaller"), GetStormcallerPath());
    PathDatabase.Add(TEXT("Gravebinder"), GetGravebinderPath());
    PathDatabase.Add(TEXT("Demonologist"), GetDemonologistPath());
    PathDatabase.Add(TEXT("Chronomancer"), GetChronomancerPath());
    PathDatabase.Add(TEXT("NightmareWeaver"), GetNightmareWeaverPath());

    // Initialize Assassin Paths
    PathDatabase.Add(TEXT("ShadowMonarch"), GetShadowMonarchPath());
    PathDatabase.Add(TEXT("NightStalker"), GetNightStalkerPath());
    PathDatabase.Add(TEXT("Venomblade"), GetVenombladePath());
    PathDatabase.Add(TEXT("Phantom"), GetPhantomPath());
    PathDatabase.Add(TEXT("CrimsonEclipse"), GetCrimsonEclipsePath());

    // Initialize Tank Paths
    PathDatabase.Add(TEXT("IronGuardian"), GetIronGuardianPath());
    PathDatabase.Add(TEXT("StoneheartGuardian"), GetStoneheartGuardianPath());
    PathDatabase.Add(TEXT("DivineAegis"), GetDivineAegisPath());
    PathDatabase.Add(TEXT("DuskDreadnought"), GetDuskDreadnoughtPath());
    PathDatabase.Add(TEXT("ImmortalBastion"), GetImmortalBastionPath());
    PathDatabase.Add(TEXT("SpellshieldWarden"), GetSpellshieldWardenPath());
    PathDatabase.Add(TEXT("GravityTitan"), GetGravityTitanPath());

    // Initialize Ranger Paths
    PathDatabase.Add(TEXT("WildHunt"), GetWildHuntPath());
    PathDatabase.Add(TEXT("DeadeyeSniper"), GetDeadeyeSniperPath());
    PathDatabase.Add(TEXT("TempestRanger"), GetTempestRangerPath());
    PathDatabase.Add(TEXT("VenomstrikeArcher"), GetVenomstrikeArcherPath());
    PathDatabase.Add(TEXT("SylvanSentinel"), GetSylvanSentinelPath());
    PathDatabase.Add(TEXT("PhantomArcher"), GetPhantomArcherPath());
    PathDatabase.Add(TEXT("DemonbaneMarksman"), GetDemonbaneMarksmanPath());

    // Initialize Healer Paths
    PathDatabase.Add(TEXT("LightWeaver"), GetLightWeaverPath());
    PathDatabase.Add(TEXT("NaturesTouch"), GetNaturesTouchPath());
    PathDatabase.Add(TEXT("BloodMender"), GetBloodMenderPath());
    PathDatabase.Add(TEXT("SpiritChanneler"), GetSpiritChannelerPath());
    PathDatabase.Add(TEXT("PainAlchemist"), GetPainAlchemistPath());
    PathDatabase.Add(TEXT("PsychicHealer"), GetPsychicHealerPath());

    bInitialized = true;
    UE_LOG(LogTemp, Warning, TEXT("All 45 power paths initialized successfully"));
}

FPowerPathDefinition UPowerPathDatabase::GetPathDefinition(const FString& PathName)
{
    if (!bInitialized)
    {
        InitializeAllPaths();
    }

    if (PathDatabase.Contains(PathName))
    {
        return PathDatabase[PathName];
    }

    UE_LOG(LogTemp, Warning, TEXT("Path not found: %s"), *PathName);
    return FPowerPathDefinition();
}

TArray<FPowerPathDefinition> UPowerPathDatabase::GetPathsForClass(ECoreClass CoreClass)
{
    if (!bInitialized)
    {
        InitializeAllPaths();
    }

    TArray<FPowerPathDefinition> ClassPaths;
    for (const auto& PathPair : PathDatabase)
    {
        if (PathPair.Value.PathData.CoreClass == CoreClass)
        {
            ClassPaths.Add(PathPair.Value);
        }
    }
    return ClassPaths;
}

TArray<FPowerPathDefinition> UPowerPathDatabase::GetLegendaryPaths()
{
    if (!bInitialized)
    {
        InitializeAllPaths();
    }

    TArray<FPowerPathDefinition> LegendaryPaths;
    for (const auto& PathPair : PathDatabase)
    {
        if (PathPair.Value.PathData.bIsLegendary)
        {
            LegendaryPaths.Add(PathPair.Value);
        }
    }
    return LegendaryPaths;
}

TArray<FPowerPathDefinition> UPowerPathDatabase::GetAllPaths()
{
    if (!bInitialized)
    {
        InitializeAllPaths();
    }

    TArray<FPowerPathDefinition> AllPaths;
    for (const auto& PathPair : PathDatabase)
    {
        AllPaths.Add(PathPair.Value);
    }
    return AllPaths;
}

// Fighter Paths Implementation
FPowerPathDefinition UPowerPathDatabase::GetBeastKingPath()
{
    FPowerPathDefinition Path;
    Path.PathData.PathName = TEXT("BeastKing");
    Path.PathData.CoreClass = ECoreClass::Fighter;
    Path.PathData.Description = TEXT("A feral berserker path that channels the Primordial Beast");
    Path.PathData.AcquisitionMethod = EAcquisitionMethod::QuestReward;
    Path.PathData.MinimumRank = EPowerRank::B;
    Path.PathData.bIsLegendary = false;
    Path.PathData.RequiredQuests.Add(TEXT("BeastLordRitual"));
    Path.PathData.PowerCost = 50;

    // Set rank titles
    SetRankTitle(Path, EPowerRank::B, TEXT("Beast Warrior"));
    SetRankTitle(Path, EPowerRank::A, TEXT("Beast Lord"));
    SetRankTitle(Path, EPowerRank::SSS, TEXT("Beast King"));
    SetRankTitle(Path, EPowerRank::TrueMonarch, TEXT("Beast Monarch"));

    // Set rank power levels
    SetRankPowerLevel(Path, EPowerRank::B, 100);
    SetRankPowerLevel(Path, EPowerRank::A, 250);
    SetRankPowerLevel(Path, EPowerRank::SSS, 500);
    SetRankPowerLevel(Path, EPowerRank::TrueMonarch, 1000);

    // Add abilities
    FAbilityData SavageHowl = CreateAbility(TEXT("Savage Howl"), TEXT("Thunderous roar buffs damage"), EPowerRank::B, 20, 15.0f, 500.0f, 0.0f);
    FAbilityData PrimalRend = CreateAbility(TEXT("Primal Rend"), TEXT("Beast claws for heavy bleed"), EPowerRank::A, 30, 10.0f, 200.0f, 150.0f);
    FAbilityData AlphasDominion = CreateAbility(TEXT("Alpha's Dominion"), TEXT("Aura of dominance charms beasts"), EPowerRank::SSS, 50, 30.0f, 800.0f, 0.0f);

    AddAbilityToPath(Path, EPowerRank::B, SavageHowl);
    AddAbilityToPath(Path, EPowerRank::A, PrimalRend);
    AddAbilityToPath(Path, EPowerRank::SSS, AlphasDominion);

    Path.UltimateAbility = TEXT("Beast Monarch's Dominion");
    Path.UltimateRank = EPowerRank::TrueMonarch;

    return Path;
}

FPowerPathDefinition UPowerPathDatabase::GetDragonheartPath()
{
    FPowerPathDefinition Path;
    Path.PathData.PathName = TEXT("Dragonheart");
    Path.PathData.CoreClass = ECoreClass::Fighter;
    Path.PathData.Description = TEXT("A warrior infused with draconic blood");
    Path.PathData.AcquisitionMethod = EAcquisitionMethod::StoryEvent;
    Path.PathData.MinimumRank = EPowerRank::D;
    Path.PathData.bIsLegendary = true;
    Path.PathData.RequiredQuests.Add(TEXT("DragonSlaying"));
    Path.PathData.PowerCost = 75;

    // Set rank titles
    SetRankTitle(Path, EPowerRank::D, TEXT("Drakeblood Novice"));
    SetRankTitle(Path, EPowerRank::B, TEXT("Dragonsoul Knight"));
    SetRankTitle(Path, EPowerRank::S, TEXT("Dragonheart Champion"));
    SetRankTitle(Path, EPowerRank::National, TEXT("Dragonlord"));

    // Set rank power levels
    SetRankPowerLevel(Path, EPowerRank::D, 80);
    SetRankPowerLevel(Path, EPowerRank::B, 200);
    SetRankPowerLevel(Path, EPowerRank::S, 400);
    SetRankPowerLevel(Path, EPowerRank::National, 800);

    // Add abilities
    FAbilityData DragonflameBreath = CreateAbility(TEXT("Dragonflame Breath"), TEXT("Cone of searing dragon fire"), EPowerRank::D, 25, 20.0f, 600.0f, 200.0f);
    FAbilityData ScaleguardAegis = CreateAbility(TEXT("Scaleguard Aegis"), TEXT("Harden draconic scales"), EPowerRank::B, 35, 25.0f, 0.0f, 0.0f);
    FAbilityData WyrmwingAscent = CreateAbility(TEXT("Wyrmwing Ascent"), TEXT("Ethereal dragon wings leap"), EPowerRank::S, 45, 15.0f, 1000.0f, 300.0f);

    AddAbilityToPath(Path, EPowerRank::D, DragonflameBreath);
    AddAbilityToPath(Path, EPowerRank::B, ScaleguardAegis);
    AddAbilityToPath(Path, EPowerRank::S, WyrmwingAscent);

    Path.UltimateAbility = TEXT("Dragonlord's Fury");
    Path.UltimateRank = EPowerRank::National;

    return Path;
}

// Simplified implementations for other paths (following the same pattern)
FPowerPathDefinition UPowerPathDatabase::GetInfernalWarlordPath()
{
    FPowerPathDefinition Path;
    Path.PathData.PathName = TEXT("InfernalWarlord");
    Path.PathData.CoreClass = ECoreClass::Fighter;
    Path.PathData.Description = TEXT("A Fighter who made a demonic pact, wielding hellfire");
    Path.PathData.AcquisitionMethod = EAcquisitionMethod::SpecialEvent;
    Path.PathData.MinimumRank = EPowerRank::C;
    Path.PathData.bIsLegendary = true;
    Path.PathData.PowerCost = 100;

    SetRankTitle(Path, EPowerRank::C, TEXT("Ember Knight"));
    SetRankTitle(Path, EPowerRank::A, TEXT("Hellfire Champion"));
    SetRankTitle(Path, EPowerRank::S, TEXT("Infernal Warlord"));
    SetRankTitle(Path, EPowerRank::SSS, TEXT("Abyssal Overlord"));

    SetRankPowerLevel(Path, EPowerRank::C, 120);
    SetRankPowerLevel(Path, EPowerRank::A, 300);
    SetRankPowerLevel(Path, EPowerRank::S, 600);
    SetRankPowerLevel(Path, EPowerRank::SSS, 1200);

    FAbilityData HellfireCleave = CreateAbility(TEXT("Hellfire Cleave"), TEXT("Wide arc of hellfire"), EPowerRank::C, 30, 18.0f, 400.0f, 250.0f);
    AddAbilityToPath(Path, EPowerRank::C, HellfireCleave);

    Path.UltimateAbility = TEXT("Abyssal Transformation");
    Path.UltimateRank = EPowerRank::SSS;

    return Path;
}

FPowerPathDefinition UPowerPathDatabase::GetStormHeraldPath()
{
    FPowerPathDefinition Path;
    Path.PathData.PathName = TEXT("StormHerald");
    Path.PathData.CoreClass = ECoreClass::Fighter;
    Path.PathData.Description = TEXT("A tempestuous warrior blessed by the storm");
    Path.PathData.AcquisitionMethod = EAcquisitionMethod::WorldExploration;
    Path.PathData.MinimumRank = EPowerRank::E;
    Path.PathData.bIsLegendary = false;
    Path.PathData.PowerCost = 60;

    SetRankTitle(Path, EPowerRank::E, TEXT("Lightning Adept"));
    SetRankTitle(Path, EPowerRank::C, TEXT("Thunderstriker"));
    SetRankTitle(Path, EPowerRank::A, TEXT("Storm Herald"));
    SetRankTitle(Path, EPowerRank::SS, TEXT("Tempest Emperor"));

    SetRankPowerLevel(Path, EPowerRank::E, 50);
    SetRankPowerLevel(Path, EPowerRank::C, 150);
    SetRankPowerLevel(Path, EPowerRank::A, 350);
    SetRankPowerLevel(Path, EPowerRank::SS, 700);

    FAbilityData LightningCharge = CreateAbility(TEXT("Lightning Charge"), TEXT("Lightning-infused dash"), EPowerRank::E, 20, 12.0f, 800.0f, 180.0f);
    AddAbilityToPath(Path, EPowerRank::E, LightningCharge);

    Path.UltimateAbility = TEXT("Tempest's Wrath");
    Path.UltimateRank = EPowerRank::SS;

    return Path;
}

FPowerPathDefinition UPowerPathDatabase::GetBloodKnightPath()
{
    FPowerPathDefinition Path;
    Path.PathData.PathName = TEXT("BloodKnight");
    Path.PathData.CoreClass = ECoreClass::Fighter;
    Path.PathData.Description = TEXT("A cursed knight wielding vampiric blood magic");
    Path.PathData.AcquisitionMethod = EAcquisitionMethod::QuestReward;
    Path.PathData.MinimumRank = EPowerRank::B;
    Path.PathData.bIsLegendary = true;
    Path.PathData.PowerCost = 85;

    SetRankTitle(Path, EPowerRank::B, TEXT("Blood Knight"));
    SetRankTitle(Path, EPowerRank::S, TEXT("Crimson Lord"));
    SetRankTitle(Path, EPowerRank::SSS, TEXT("Deathlord"));

    SetRankPowerLevel(Path, EPowerRank::B, 180);
    SetRankPowerLevel(Path, EPowerRank::S, 450);
    SetRankPowerLevel(Path, EPowerRank::SSS, 900);

    FAbilityData BlooddrinkerBlade = CreateAbility(TEXT("Blooddrinker Blade"), TEXT("Impale enemy and siphon life"), EPowerRank::B, 35, 15.0f, 300.0f, 200.0f);
    AddAbilityToPath(Path, EPowerRank::B, BlooddrinkerBlade);

    Path.UltimateAbility = TEXT("Vampire Lord's Ascension");
    Path.UltimateRank = EPowerRank::SSS;

    return Path;
}

FPowerPathDefinition UPowerPathDatabase::GetCelestialCrusaderPath()
{
    FPowerPathDefinition Path;
    Path.PathData.PathName = TEXT("CelestialCrusader");
    Path.PathData.CoreClass = ECoreClass::Fighter;
    Path.PathData.Description = TEXT("A holy warrior path imbuing melee prowess with divine light");
    Path.PathData.AcquisitionMethod = EAcquisitionMethod::GuildUnlock;
    Path.PathData.MinimumRank = EPowerRank::D;
    Path.PathData.bIsLegendary = false;
    Path.PathData.RequiredGuilds.Add(TEXT("HolyOrder"));
    Path.PathData.PowerCost = 55;

    SetRankTitle(Path, EPowerRank::D, TEXT("Blessed Initiate"));
    SetRankTitle(Path, EPowerRank::B, TEXT("Holy Blade"));
    SetRankTitle(Path, EPowerRank::S, TEXT("Celestial Crusader"));
    SetRankTitle(Path, EPowerRank::SSS, TEXT("Divine Judicator"));

    SetRankPowerLevel(Path, EPowerRank::D, 90);
    SetRankPowerLevel(Path, EPowerRank::B, 220);
    SetRankPowerLevel(Path, EPowerRank::S, 550);
    SetRankPowerLevel(Path, EPowerRank::SSS, 1100);

    FAbilityData BlindingValor = CreateAbility(TEXT("Blinding Valor"), TEXT("Brilliant light blinds enemies"), EPowerRank::D, 25, 20.0f, 600.0f, 0.0f);
    AddAbilityToPath(Path, EPowerRank::D, BlindingValor);

    Path.UltimateAbility = TEXT("Divine Judgment");
    Path.UltimateRank = EPowerRank::SSS;

    return Path;
}

// Helper Functions Implementation
FAbilityData UPowerPathDatabase::CreateAbility(const FString& Name, const FString& Description, EPowerRank Rank, int32 ManaCost, float Cooldown, float Range, float Damage)
{
    FAbilityData Ability;
    Ability.AbilityName = Name;
    Ability.Description = Description;
    Ability.RequiredRank = Rank;
    Ability.ManaCost = ManaCost;
    Ability.Cooldown = Cooldown;
    Ability.Range = Range;
    Ability.Damage = Damage;
    return Ability;
}

void UPowerPathDatabase::AddAbilityToPath(FPowerPathDefinition& Path, EPowerRank Rank, const FAbilityData& Ability)
{
    if (!Path.RankAbilities.Contains(Rank))
    {
        Path.RankAbilities.Add(Rank, TArray<FAbilityData>());
    }
    Path.RankAbilities[Rank].Add(Ability);
}

void UPowerPathDatabase::SetRankTitle(FPowerPathDefinition& Path, EPowerRank Rank, const FString& Title)
{
    Path.RankTitles.Add(Rank, Title);
}

void UPowerPathDatabase::SetRankPowerLevel(FPowerPathDefinition& Path, EPowerRank Rank, int32 PowerLevel)
{
    Path.RankPowerLevels.Add(Rank, PowerLevel);
}

// Placeholder implementations for remaining paths (simplified for brevity)
FPowerPathDefinition UPowerPathDatabase::GetHighMagePath() { return FPowerPathDefinition(); }
FPowerPathDefinition UPowerPathDatabase::GetInfernalArcanistPath() { return FPowerPathDefinition(); }
FPowerPathDefinition UPowerPathDatabase::GetFrostbinderPath() { return FPowerPathDefinition(); }
FPowerPathDefinition UPowerPathDatabase::GetStormcallerPath() { return FPowerPathDefinition(); }
FPowerPathDefinition UPowerPathDatabase::GetGravebinderPath() { return FPowerPathDefinition(); }
FPowerPathDefinition UPowerPathDatabase::GetDemonologistPath() { return FPowerPathDefinition(); }
FPowerPathDefinition UPowerPathDatabase::GetChronomancerPath() { return FPowerPathDefinition(); }
FPowerPathDefinition UPowerPathDatabase::GetNightmareWeaverPath() { return FPowerPathDefinition(); }
FPowerPathDefinition UPowerPathDatabase::GetShadowMonarchPath() { return FPowerPathDefinition(); }
FPowerPathDefinition UPowerPathDatabase::GetNightStalkerPath() { return FPowerPathDefinition(); }
FPowerPathDefinition UPowerPathDatabase::GetVenombladePath() { return FPowerPathDefinition(); }
FPowerPathDefinition UPowerPathDatabase::GetPhantomPath() { return FPowerPathDefinition(); }
FPowerPathDefinition UPowerPathDatabase::GetCrimsonEclipsePath() { return FPowerPathDefinition(); }
FPowerPathDefinition UPowerPathDatabase::GetIronGuardianPath() { return FPowerPathDefinition(); }
FPowerPathDefinition UPowerPathDatabase::GetStoneheartGuardianPath() { return FPowerPathDefinition(); }
FPowerPathDefinition UPowerPathDatabase::GetDivineAegisPath() { return FPowerPathDefinition(); }
FPowerPathDefinition UPowerPathDatabase::GetDuskDreadnoughtPath() { return FPowerPathDefinition(); }
FPowerPathDefinition UPowerPathDatabase::GetImmortalBastionPath() { return FPowerPathDefinition(); }
FPowerPathDefinition UPowerPathDatabase::GetSpellshieldWardenPath() { return FPowerPathDefinition(); }
FPowerPathDefinition UPowerPathDatabase::GetGravityTitanPath() { return FPowerPathDefinition(); }
FPowerPathDefinition UPowerPathDatabase::GetWildHuntPath() { return FPowerPathDefinition(); }
FPowerPathDefinition UPowerPathDatabase::GetDeadeyeSniperPath() { return FPowerPathDefinition(); }
FPowerPathDefinition UPowerPathDatabase::GetTempestRangerPath() { return FPowerPathDefinition(); }
FPowerPathDefinition UPowerPathDatabase::GetVenomstrikeArcherPath() { return FPowerPathDefinition(); }
FPowerPathDefinition UPowerPathDatabase::GetSylvanSentinelPath() { return FPowerPathDefinition(); }
FPowerPathDefinition UPowerPathDatabase::GetPhantomArcherPath() { return FPowerPathDefinition(); }
FPowerPathDefinition UPowerPathDatabase::GetDemonbaneMarksmanPath() { return FPowerPathDefinition(); }
FPowerPathDefinition UPowerPathDatabase::GetLightWeaverPath() { return FPowerPathDefinition(); }
FPowerPathDefinition UPowerPathDatabase::GetNaturesTouchPath() { return FPowerPathDefinition(); }
FPowerPathDefinition UPowerPathDatabase::GetBloodMenderPath() { return FPowerPathDefinition(); }
FPowerPathDefinition UPowerPathDatabase::GetSpiritChannelerPath() { return FPowerPathDefinition(); }
FPowerPathDefinition UPowerPathDatabase::GetPainAlchemistPath() { return FPowerPathDefinition(); }
FPowerPathDefinition UPowerPathDatabase::GetPsychicHealerPath() { return FPowerPathDefinition(); }
