#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PowerSystemCore.generated.h"

// Core Classes Enum
UENUM(BlueprintType)
enum class ECoreClass : uint8
{
    None = 0,
    Fighter,
    Mage,
    Assassin,
    Tank,
    Ranger,
    Healer
};

// Rank Progression Enum
UENUM(BlueprintType)
enum class EPowerRank : uint8
{
    F = 0,
    E,
    D,
    C,
    B,
    A,
    S,
    SS,
    SSS,
    National,
    TrueMonarch
};

// Path Acquisition Method
UENUM(BlueprintType)
enum class EAcquisitionMethod : uint8
{
    Default = 0,
    StoryEvent,
    GuildUnlock,
    QuestReward,
    WorldExploration,
    Achievement,
    SpecialEvent
};

// Power Path Data Structure
USTRUCT(BlueprintType)
struct FPowerPathData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power Path")
    FString PathName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power Path")
    ECoreClass CoreClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power Path")
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power Path")
    EAcquisitionMethod AcquisitionMethod;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power Path")
    EPowerRank MinimumRank;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power Path")
    bool bIsLegendary;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power Path")
    TArray<FString> RequiredQuests;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power Path")
    TArray<FString> RequiredGuilds;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power Path")
    int32 PowerCost;
};

// Player Power Progression
USTRUCT(BlueprintType)
struct FPlayerPowerProgression
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power Progression")
    ECoreClass SelectedClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power Progression")
    TArray<FString> UnlockedPaths;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power Progression")
    TMap<FString, EPowerRank> PathRanks;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power Progression")
    TMap<FString, int32> PathExperience;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power Progression")
    bool bHasMultiPathAccess;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power Progression")
    TArray<FString> ActivePaths;
};

// Ability Data Structure
USTRUCT(BlueprintType)
struct FAbilityData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
    FString AbilityName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
    EPowerRank RequiredRank;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
    int32 ManaCost;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
    float Cooldown;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
    float Range;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
    float Damage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
    TArray<FString> StatusEffects;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
    UTexture2D* Icon;
};

// Power Path Full Definition
USTRUCT(BlueprintType)
struct FPowerPathDefinition
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power Path")
    FPowerPathData PathData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power Path")
    TMap<EPowerRank, FString> RankTitles;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power Path")
    TMap<EPowerRank, TArray<FAbilityData>> RankAbilities;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power Path")
    TMap<EPowerRank, int32> RankPowerLevels;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power Path")
    FString UltimateAbility;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power Path")
    EPowerRank UltimateRank;
};

// Data Table Row for Power Paths
USTRUCT(BlueprintType)
struct FPowerPathTableRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Power Path")
    FPowerPathDefinition PowerPathDefinition;
};
