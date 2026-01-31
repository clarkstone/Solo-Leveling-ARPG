#include "GuildSystem.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

UGuildSystem::UGuildSystem()
{
    bIsInGuild = false;
    PlayerRank = EGuildRank::GR_Member;
    LastUpdateTime = 0.0f;
    bIsInGuildHall = false;
    CurrentActivity = EGuildActivity::GA_None;
}

void UGuildSystem::BeginPlay()
{
    Super::BeginPlay();
    Initialize();
}

void UGuildSystem::Initialize()
{
    InitializeGuildData();
    LoadGuildData();
    
    UE_LOG(LogTemp, Warning, TEXT("Guild System initialized"));
}

void UGuildSystem::InitializeGuildData()
{
    // Initialize player guild data
    PlayerGuild.GuildName = TEXT("");
    PlayerGuild.GuildDescription = TEXT("");
    PlayerGuild.GuildMaster = TEXT("");
    PlayerGuild.MaxMembers = 50;
    PlayerGuild.CurrentMembers = 0;
    PlayerGuild.GuildLevel = 1.0f;
    PlayerGuild.GuildExperience = 0.0f;
    PlayerGuild.bIsInWar = false;
    PlayerGuild.GuildHall = TEXT("");
    
    UE_LOG(LogTemp, Warning, TEXT("Guild data initialized"));
}

bool UGuildSystem::CreateGuild(FString GuildName, FString GuildDescription)
{
    if (!bIsInGuild && !GuildName.IsEmpty())
    {
        // Create new guild
        PlayerGuild.GuildName = GuildName;
        PlayerGuild.GuildDescription = GuildDescription;
        PlayerGuild.GuildMaster = GetOwner()->GetHumanReadableName();
        PlayerGuild.CurrentMembers = 1;
        
        // Add guild master as first member
        FGuildMember GuildMaster;
        GuildMaster.PlayerName = PlayerGuild.GuildMaster;
        GuildMaster.Rank = EGuildRank::GR_Master;
        GuildMaster.Level = 1;
        GuildMaster.Contribution = 0.0f;
        GuildMaster.bIsOnline = true;
        GuildMaster.LastActive = FDateTime::Now();
        
        PlayerGuild.Members.Add(GuildMaster);
        
        bIsInGuild = true;
        PlayerRank = EGuildRank::GR_Master;
        
        // Add to all guilds database
        AllGuilds.Add(GuildName, PlayerGuild);
        
        OnGuildCreated.Broadcast(PlayerGuild);
        OnGuildJoined.Broadcast(PlayerGuild);
        
        UE_LOG(LogTemp, Warning, TEXT("Guild created: %s"), *GuildName);
        return true;
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Cannot create guild"));
    return false;
}

bool UGuildSystem::JoinGuild(FString GuildName)
{
    if (!bIsInGuild && AllGuilds.Contains(GuildName))
    {
        FGuildData& GuildData = AllGuilds[GuildName];
        
        if (GuildData.CurrentMembers < GuildData.MaxMembers)
        {
            // Add player to guild
            FGuildMember NewMember;
            NewMember.PlayerName = GetOwner()->GetHumanReadableName();
            NewMember.Rank = EGuildRank::GR_Member;
            NewMember.Level = 1;
            NewMember.Contribution = 0.0f;
            NewMember.bIsOnline = true;
            NewMember.LastActive = FDateTime::Now();
            
            GuildData.Members.Add(NewMember);
            GuildData.CurrentMembers++;
            
            // Update player guild data
            PlayerGuild = GuildData;
            bIsInGuild = true;
            PlayerRank = EGuildRank::GR_Member;
            
            OnGuildJoined.Broadcast(PlayerGuild);
            
            UE_LOG(LogTemp, Warning, TEXT("Joined guild: %s"), *GuildName);
            return true;
        }
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Cannot join guild: %s"), *GuildName);
    return false;
}

bool UGuildSystem::LeaveGuild()
{
    if (bIsInGuild)
    {
        FString PlayerName = GetOwner()->GetHumanReadableName();
        
        // Remove player from guild
        for (int32 i = 0; i < PlayerGuild.Members.Num(); i++)
        {
            if (PlayerGuild.Members[i].PlayerName == PlayerName)
            {
                PlayerGuild.Members.RemoveAt(i);
                PlayerGuild.CurrentMembers--;
                break;
            }
        }
        
        // Update guild in database
        if (AllGuilds.Contains(PlayerGuild.GuildName))
        {
            AllGuilds[PlayerGuild.GuildName] = PlayerGuild;
        }
        
        // Reset player guild data
        PlayerGuild = FGuildData();
        bIsInGuild = false;
        PlayerRank = EGuildRank::GR_Member;
        
        OnGuildLeft.Broadcast(PlayerGuild);
        
        UE_LOG(LogTemp, Warning, TEXT("Left guild"));
        return true;
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Cannot leave guild"));
    return false;
}

bool UGuildSystem::InviteToGuild(FString PlayerName)
{
    if (bIsInGuild && PlayerRank >= EGuildRank::GR_Officer)
    {
        // Send guild invitation
        GuildInvitations.Add(PlayerName, PlayerGuild.GuildName);
        
        UE_LOG(LogTemp, Warning, TEXT("Guild invitation sent to: %s"), *PlayerName);
        return true;
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Cannot send guild invitation"));
    return false;
}

bool UGuildSystem::PromoteMember(FString PlayerName, EGuildRank NewRank)
{
    if (bIsInGuild && PlayerRank >= EGuildRank::GR_Captain)
    {
        // Find member in guild
        for (FGuildMember& Member : PlayerGuild.Members)
        {
            if (Member.PlayerName == PlayerName)
            {
                EGuildRank OldRank = Member.Rank;
                Member.Rank = NewRank;
                
                UE_LOG(LogTemp, Warning, TEXT("Member promoted: %s to rank %d"), *PlayerName, (int32)NewRank);
                return true;
            }
        }
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Cannot promote member"));
    return false;
}

void UGuildSystem::StartGuildActivity(EGuildActivity Activity)
{
    CurrentActivity = Activity;
    
    switch (Activity)
    {
        case EGuildActivity::GA_Quest:
            UE_LOG(LogTemp, Warning, TEXT("Guild quest started"));
            break;
        case EGuildActivity::GA_Raid:
            UE_LOG(LogTemp, Warning, TEXT("Guild raid started"));
            break;
        case EGuildActivity::GA_Training:
            UE_LOG(LogTemp, Warning, TEXT("Guild training started"));
            break;
        case EGuildActivity::GA_Meeting:
            UE_LOG(LogTemp, Warning, TEXT("Guild meeting started"));
            break;
        case EGuildActivity::GA_War:
            UE_LOG(LogTemp, Warning, TEXT("Guild war started"));
            break;
        default:
            break;
    }
}

void UGuildSystem::EndGuildActivity()
{
    CurrentActivity = EGuildActivity::GA_None;
    UE_LOG(LogTemp, Warning, TEXT("Guild activity ended"));
}

bool UGuildSystem::DeclareWar(FString EnemyGuildName)
{
    if (bIsInGuild && PlayerRank >= EGuildRank::GR_Captain)
    {
        if (AllGuilds.Contains(EnemyGuildName))
        {
            // Declare war
            PlayerGuild.EnemyGuilds.Add(EnemyGuildName);
            PlayerGuild.bIsInWar = true;
            
            // Update enemy guild
            FGuildData& EnemyGuild = AllGuilds[EnemyGuildName];
            EnemyGuild.EnemyGuilds.Add(PlayerGuild.GuildName);
            EnemyGuild.bIsInWar = true;
            
            OnGuildWarStarted.Broadcast(EnemyGuildName);
            
            UE_LOG(LogTemp, Warning, TEXT("War declared on: %s"), *EnemyGuildName);
            return true;
        }
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Cannot declare war"));
    return false;
}

void UGuildSystem::SendGuildMessage(FString Message)
{
    if (bIsInGuild)
    {
        // Send message to all guild members
        UE_LOG(LogTemp, Warning, TEXT("Guild message: %s"), *Message);
    }
}

void UGuildSystem::OnMemberJoined(FString PlayerName)
{
    if (bIsInGuild)
    {
        UE_LOG(LogTemp, Warning, TEXT("Member joined guild: %s"), *PlayerName);
    }
}

void UGuildSystem::OnMemberLeft(FString PlayerName)
{
    if (bIsInGuild)
    {
        UE_LOG(LogTemp, Warning, TEXT("Member left guild: %s"), *PlayerName);
    }
}

void UGuildSystem::OnGuildLevelUp()
{
    if (bIsInGuild)
    {
        PlayerGuild.GuildLevel += 1.0f;
        OnGuildLevelUp.Broadcast(PlayerGuild);
        
        UE_LOG(LogTemp, Warning, TEXT("Guild leveled up to: %.1f"), PlayerGuild.GuildLevel);
    }
}

void UGuildSystem::UpdateGuildStatus()
{
    if (bIsInGuild)
    {
        // Update member online status
        UpdateMemberStatus();
        
        // Calculate guild experience
        CalculateGuildExperience();
        
        // Process guild wars
        ProcessGuildWars();
    }
}

void UGuildSystem::UpdateMemberStatus()
{
    // Update online status of guild members
    for (FGuildMember& Member : PlayerGuild.Members)
    {
        // This would check actual player connection status
        Member.bIsOnline = true;
        Member.LastActive = FDateTime::Now();
    }
}

void UGuildSystem::CalculateGuildExperience()
{
    // Calculate guild experience based on member activities
    float TotalContribution = 0.0f;
    
    for (const FGuildMember& Member : PlayerGuild.Members)
    {
        if (Member.bIsOnline)
        {
            TotalContribution += Member.Contribution;
        }
    }
    
    PlayerGuild.GuildExperience += TotalContribution * 0.1f;
    
    // Check for level up
    float RequiredExperience = PlayerGuild.GuildLevel * 1000.0f;
    if (PlayerGuild.GuildExperience >= RequiredExperience)
    {
        PlayerGuild.GuildExperience -= RequiredExperience;
        OnGuildLevelUp();
    }
}

void UGuildSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    UpdateGuildStatus();
    UpdateGuildActivity(DeltaTime);
}

void UGuildSystem::UpdateGuildActivity(float DeltaTime)
{
    // Update current guild activity
    if (CurrentActivity != EGuildActivity::GA_None)
    {
        // Process activity logic
    }
}

void UGuildSystem::LoadGuildData()
{
    // Load guild data from database
    UE_LOG(LogTemp, Warning, TEXT("Loading guild data..."));
}
