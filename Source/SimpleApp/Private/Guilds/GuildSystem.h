#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "GuildSystem.generated.h"

UENUM(BlueprintType)
enum class EGuildRank : uint8
{
    GR_Member,
    GR_Officer,
    GR_Captain,
    GR_Master
};

UENUM(BlueprintType)
enum class EGuildActivity : uint8
{
    GA_None,
    GA_Quest,
    GA_Raid,
    GA_Training,
    GA_Meeting,
    GA_War
};

USTRUCT(BlueprintType)
struct FGuildMember
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString PlayerName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EGuildRank Rank;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 Level;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Contribution;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsOnline;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FDateTime LastActive;
};

USTRUCT(BlueprintType)
struct FGuildData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString GuildName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString GuildDescription;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString GuildMaster;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 MaxMembers;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 CurrentMembers;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float GuildLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float GuildExperience;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FGuildMember> Members;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> AlliedGuilds;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> EnemyGuilds;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsInWar;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString GuildHall;
};

UCLASS()
class SIMPLEAPP_API UGuildSystem : public UActorComponent
{
    GENERATED_BODY()

public:
    UGuildSystem();

    // Guild Configuration
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Guild")
    FGuildData PlayerGuild;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Guild")
    bool bIsInGuild;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Guild")
    EGuildRank PlayerRank;

    // Override UActorComponent functions
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Initialization
    UFUNCTION(BlueprintCallable, Category = "Guild")
    void Initialize();

    // Guild Management
    UFUNCTION(BlueprintCallable, Category = "Guild")
    bool CreateGuild(FString GuildName, FString GuildDescription);

    UFUNCTION(BlueprintCallable, Category = "Guild")
    bool JoinGuild(FString GuildName);

    UFUNCTION(BlueprintCallable, Category = "Guild")
    bool LeaveGuild();

    UFUNCTION(BlueprintCallable, Category = "Guild")
    bool InviteToGuild(FString PlayerName);

    UFUNCTION(BlueprintCallable, Category = "Guild")
    bool KickFromGuild(FString PlayerName);

    UFUNCTION(BlueprintCallable, Category = "Guild")
    bool PromoteMember(FString PlayerName, EGuildRank NewRank);

    UFUNCTION(BlueprintCallable, Category = "Guild")
    bool DemoteMember(FString PlayerName, EGuildRank NewRank);

    // Guild Information
    UFUNCTION(BlueprintCallable, Category = "Guild")
    FGuildData GetGuildData(FString GuildName);

    UFUNCTION(BlueprintCallable, Category = "Guild")
    TArray<FGuildMember> GetGuildMembers();

    UFUNCTION(BlueprintCallable, Category = "Guild")
    TArray<FGuildMember> GetOnlineMembers();

    UFUNCTION(BlueprintCallable, Category = "Guild")
    bool IsMember(FString PlayerName);

    UFUNCTION(BlueprintCallable, Category = "Guild")
    EGuildRank GetMemberRank(FString PlayerName);

    // Guild Activities
    UFUNCTION(BlueprintCallable, Category = "Guild")
    void StartGuildActivity(EGuildActivity Activity);

    UFUNCTION(BlueprintCallable, Category = "Guild")
    void EndGuildActivity();

    UFUNCTION(BlueprintCallable, Category = "Guild")
    void UpdateGuildActivity(float DeltaTime);

    // Guild Wars
    UFUNCTION(BlueprintCallable, Category = "Guild")
    bool DeclareWar(FString EnemyGuildName);

    UFUNCTION(BlueprintCallable, Category = "Guild")
    bool MakePeace(FString EnemyGuildName);

    UFUNCTION(BlueprintCallable, Category = "Guild")
    bool FormAlliance(FString GuildName);

    UFUNCTION(BlueprintCallable, Category = "Guild")
    bool BreakAlliance(FString GuildName);

    // Guild Hall
    UFUNCTION(BlueprintCallable, Category = "Guild")
    void UpgradeGuildHall();

    UFUNCTION(BlueprintCallable, Category = "Guild")
    void EnterGuildHall();

    UFUNCTION(BlueprintCallable, Category = "Guild")
    void LeaveGuildHall();

    // Guild Communication
    UFUNCTION(BlueprintCallable, Category = "Guild")
    void SendGuildMessage(FString Message);

    UFUNCTION(BlueprintCallable, Category = "Guild")
    void SendOfficerMessage(FString Message);

    UFUNCTION(BlueprintCallable, Category = "Guild")
    void SendGuildAnnouncement(FString Announcement);

    // Guild Events
    UFUNCTION(BlueprintCallable, Category = "Guild")
    void OnMemberJoined(FString PlayerName);

    UFUNCTION(BlueprintCallable, Category = "Guild")
    void OnMemberLeft(FString PlayerName);

    UFUNCTION(BlueprintCallable, Category = "Guild")
    void OnGuildLevelUp();

    UFUNCTION(BlueprintCallable, Category = "Guild")
    void OnWarDeclared(FString EnemyGuild);

    UFUNCTION(BlueprintCallable, Category = "Guild")
    void OnWarEnded(FString EnemyGuild);

    // Guild Events
    UPROPERTY(BlueprintAssignable, Category = "Guild Events")
    FOnGuildCreated OnGuildCreated;

    UPROPERTY(BlueprintAssignable, Category = "Guild Events")
    FOnGuildJoined OnGuildJoined;

    UPROPERTY(BlueprintAssignable, Category = "Guild Events")
    FOnGuildLeft OnGuildLeft;

    UPROPERTY(BlueprintAssignable, Category = "Guild Events")
    FOnGuildLevelUp OnGuildLevelUp;

    UPROPERTY(BlueprintAssignable, Category = "Guild Events")
    FOnGuildWarStarted OnGuildWarStarted;

    UPROPERTY(BlueprintAssignable, Category = "Guild Events")
    FOnGuildWarEnded OnGuildWarEnded;

protected:
    // Internal Guild Systems
    void InitializeGuildData();
    void UpdateGuildStatus();
    void ProcessGuildActivities();

    // Guild Management
    void UpdateMemberStatus();
    void CalculateGuildExperience();
    void ProcessGuildWars();

private:
    // Internal State
    float LastUpdateTime;
    bool bIsInGuildHall;
    EGuildActivity CurrentActivity;

    // Guild Data
    TMap<FString, FGuildData> AllGuilds;
    TMap<FString, TArray<FString>> GuildInvitations;

    // Helper Functions
    void LoadGuildData();
    void SaveGuildData();
    void ProcessGuildEvent(FString EventType, TArray<FString> Parameters);
};
