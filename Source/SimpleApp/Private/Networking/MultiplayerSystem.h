#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/PlayerState.h"
#include "MultiplayerSystem.generated.h"

UENUM(BlueprintType)
enum class ENetworkMode : uint8
{
    NM_Offline = 0,        // Single player only
    NM_LAN,               // Local area network
    NM_Online,            // Internet multiplayer
    NM_ListenServer,      // Player-hosted server
    NM_DedicatedServer    // Dedicated server
};

UENUM(BlueprintType)
enum class ESessionType : uint8
{
    ST_Cooperative = 0,    // Co-op gameplay
    ST_Competitive,       // PvP gameplay
    ST_Mixed,             // Both co-op and PvP
    ST_Social,            // Social hub
    ST_Custom
};

UENUM(BlueprintType)
enum class EPlayerRole : uint8
{
    PR_Host = 0,           // Session host
    PR_Client,             // Regular client
    PR_Spectator,          // Spectator only
    PR_Moderator,          // Session moderator
    PR_Admin              // Session administrator
};

USTRUCT(BlueprintType)
struct FPlayerConnectionData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Connection")
    FString PlayerID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Connection")
    FString PlayerName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Connection")
    EPlayerRole Role;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Connection")
    bool bIsReady;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Connection")
    float Ping;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Connection")
    int32 ConnectionQuality;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Connection")
    FString IPAddress;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Connection")
    int32 Port;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Connection")
    bool bIsLocalPlayer;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Connection")
    FDateTime JoinTime;
};

USTRUCT(BlueprintType)
struct FSessionInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Session Info")
    FString SessionID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Session Info")
    FString SessionName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Session Info")
    ESessionType SessionType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Session Info")
    FString MapName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Session Info")
    int32 MaxPlayers;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Session Info")
    int32 CurrentPlayers;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Session Info")
    bool bIsPrivate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Session Info")
    FString Password;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Session Info")
    FString HostName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Session Info")
    FString GameMode;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Session Info")
    TArray<FString> GameOptions;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Session Info")
    float AveragePing;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Session Info")
    bool bHasVoiceChat;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Session Info")
    FDateTime CreationTime;
};

USTRUCT(BlueprintType)
struct FNetworkSettings
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network Settings")
    ENetworkMode NetworkMode;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network Settings")
    int32 MaxConnections;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network Settings")
    int32 ServerPort;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network Settings")
    bool bUseLAN;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network Settings")
    bool bUseNatPunchthrough;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network Settings")
    float Timeout;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network Settings")
    int32 HeartbeatInterval;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network Settings")
    bool bEnableVoiceChat;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network Settings")
    bool bEnableTextChat;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network Settings")
    bool bEnableP2P;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network Settings")
    FString ServerName;
};

UCLASS(BlueprintType, Blueprintable)
class SIMPLEAPP_API UMultiplayerSystem : public UActorComponent
{
    GENERATED_BODY()

public:
    UMultiplayerSystem();

    // Multiplayer System Events
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSessionCreated, const FSessionInfo&, SessionInfo);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSessionJoined, const FSessionInfo&, SessionInfo);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSessionLeft, const FString&, SessionID);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerConnected, const FString&, PlayerID, const FPlayerConnectionData&, PlayerData);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerDisconnected, const FString&, PlayerID, const FPlayerConnectionData&, PlayerData);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNetworkError, const FString&, ErrorMessage);
    DECLARE_DYNAMIC_MULTICAST_DELEGate_OneParam(FOnConnectionQualityChanged, int32, Quality);

    UPROPERTY(BlueprintAssignable, Category = "Multiplayer Events")
    FOnSessionCreated OnSessionCreated;

    UPROPERTY(BlueprintAssignable, Category = "Multiplayer Events")
    FOnSessionJoined OnSessionJoined;

    UPROPERTY(BlueprintAssignable, Category = "Multiplayer Events")
    FOnSessionLeft OnSessionLeft;

    UPROPERTY(BlueprintAssignable, Category = "Multiplayer Events")
    FOnPlayerConnected OnPlayerConnected;

    UPROPERTY(BlueprintAssignable, Category = "Multiplayer Events")
    FOnPlayerDisconnected OnPlayerDisconnected;

    UPROPERTY(BlueprintAssignable, Category = "Multiplayer Events")
    FOnNetworkError OnNetworkError;

    UPROPERTY(BlueprintAssignable, Category = "Multiplayer Events")
    FOnConnectionQualityChanged OnConnectionQualityChanged;

    // Override UActorComponent functions
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Session Management
    UFUNCTION(BlueprintCallable, Category = "Multiplayer System")
    void InitializeMultiplayerSystem();

    UFUNCTION(BlueprintCallable, Category = "Session")
    bool CreateSession(const FString& SessionName, ESessionType SessionType, const FNetworkSettings& Settings);

    UFUNCTION(BlueprintCallable, Category = "Session")
    bool JoinSession(const FString& SessionID, const FString& Password = TEXT(""));

    UFUNCTION(BlueprintCallable, Category = "Session")
    bool LeaveSession();

    UFUNCTION(BlueprintCallable, Category = "Session")
    bool FindSessions();

    UFUNCTION(BlueprintCallable, Category = "Session")
    TArray<FSessionInfo> GetAvailableSessions() const;

    UFUNCTION(BlueprintCallable, Category = "Session")
    FSessionInfo GetCurrentSession() const;

    UFUNCTION(BlueprintCallable, Category = "Session")
    bool IsInSession() const;

    UFUNCTION(BlueprintCallable, Category = "Session")
    bool IsSessionHost() const;

    UFUNCTION(BlueprintCallable, Category = "Session")
    void UpdateSessionInfo(const FSessionInfo& NewInfo);

    // Player Management
    UFUNCTION(BlueprintCallable, Category = "Player")
    TArray<FPlayerConnectionData> GetConnectedPlayers() const;

    UFUNCTION(BlueprintCallable, Category = "Player")
    FPlayerConnectionData GetPlayerData(const FString& PlayerID) const;

    UFUNCTION(BlueprintCallable, Category = "Player")
    FString GetLocalPlayerID() const;

    UFUNCTION(BlueprintCallable, Category = "Player")
    bool IsPlayerConnected(const FString& PlayerID) const;

    UFUNCTION(BlueprintCallable, Category = "Player")
    bool KickPlayer(const FString& PlayerID, const FString& Reason = TEXT(""));

    UFUNCTION(BlueprintCallable, Category = "Player")
    bool BanPlayer(const FString& PlayerID, const FString& Reason = TEXT(""));

    UFUNCTION(BlueprintCallable, Category = "Player")
    void SetPlayerRole(const FString& PlayerID, EPlayerRole NewRole);

    UFUNCTION(BlueprintCallable, Category = "Player")
    EPlayerRole GetPlayerRole(const FString& PlayerID) const;

    // Network Configuration
    UFUNCTION(BlueprintCallable, Category = "Network")
    void ConfigureNetwork(const FNetworkSettings& Settings);

    UFUNCTION(BlueprintCallable, Category = "Network")
    FNetworkSettings GetNetworkSettings() const;

    UFUNCTION(BlueprintCallable, Category = "Network")
    ENetworkMode GetNetworkMode() const;

    UFUNCTION(BlueprintCallable, Category = "Network")
    bool TestConnection();

    UFUNCTION(BlueprintCallable, Category = "Network")
    float GetAveragePing() const;

    UFUNCTION(BlueprintCallable, Category = "Network")
    int32 GetConnectionQuality() const;

    UFUNCTION(BlueprintCallable, Category = "Network")
    void OptimizeConnection();

    // Voice Chat
    UFUNCTION(BlueprintCallable, Category = "Voice Chat")
    void InitializeVoiceChat();

    UFUNCTION(BlueprintCallable, Category = "Voice Chat")
    bool StartVoiceChat();

    UFUNCTION(BlueprintCallable, Category = "Voice Chat")
    void StopVoiceChat();

    UFUNCTION(BlueprintCallable, Category = "Voice Chat")
    bool IsVoiceChatActive() const;

    UFUNCTION(BlueprintCallable, Category = "Voice Chat")
    void MutePlayer(const FString& PlayerID);

    UFUNCTION(BlueprintCallable, Category = "Voice Chat")
    void UnmutePlayer(const FString& PlayerID);

    UFUNCTION(BlueprintCallable, Category = "Voice Chat")
    bool IsPlayerMuted(const FString& PlayerID) const;

    // Text Chat
    UFUNCTION(BlueprintCallable, Category = "Text Chat")
    void InitializeTextChat();

    UFUNCTION(BlueprintCallable, Category = "Text Chat")
    void SendChatMessage(const FString& Message, const FString& TargetPlayerID = TEXT(""));

    UFUNCTION(BlueprintCallable, Category = "Text Chat")
    void SendPrivateMessage(const FString& PlayerID, const FString& Message);

    UFUNCTION(BlueprintCallable, Category = "Text Chat")
    void ReceiveChatMessage(const FString& SenderID, const FString& Message);

    UFUNCTION(BlueprintCallable, Category = "Text Chat")
    TArray<FString> GetChatHistory() const;

    UFUNCTION(BlueprintCallable, Category = "Text Chat")
    void ClearChatHistory();

    // Synchronization
    UFUNCTION(BlueprintCallable, Category = "Synchronization")
    void InitializeSynchronization();

    UFUNCTION(BlueprintCallable, Category = "Synchronization")
    void SyncPlayerData(const FString& PlayerID);

    UFUNCTION(BlueprintCallable, Category = "Synchronization")
    void SyncWorldState();

    UFUNCTION(BlueprintCallable, Category = "Synchronization")
    void RequestGameState();

    UFUNCTION(BlueprintCallable, Category = "Synchronization")
    void BroadcastGameState();

    UFUNCTION(BlueprintCallable, Category = "Synchronization")
    bool ValidateGameState();

    // Matchmaking
    UFUNCTION(BlueprintCallable, Category = "Matchmaking")
    void InitializeMatchmaking();

    UFUNCTION(BlueprintCallable, Category = "Matchmaking")
    bool StartMatchmaking(const FString& GameMode, const TArray<FString>& Preferences);

    UFUNCTION(BlueprintCallable, Category = "Matchmaking")
    void CancelMatchmaking();

    UFUNCTION(BlueprintCallable, Category = "Matchmaking")
    bool IsMatchmakingActive() const;

    UFUNCTION(BlueprintCallable, Category = "Matchmaking")
    void SetMatchmakingPreferences(const TArray<FString>& Preferences);

    // Debug and Testing
    UFUNCTION(BlueprintCallable, Category = "Debug")
    void EnableNetworkDebug();

    UFUNCTION(BlueprintCallable, Category = "Debug")
    void DisableNetworkDebug();

    UFUNCTION(BlueprintCallable, Category = "Debug")
    bool IsNetworkDebugEnabled() const;

    UFUNCTION(BlueprintCallable, Category = "Debug")
    void LogNetworkStats();

    UFUNCTION(BlueprintCallable, Category = "Debug")
    void SimulateNetworkConditions(float PacketLoss, float Latency);

    // Save/Load
    UFUNCTION(BlueprintCallable, Category = "Multiplayer System")
    void SaveNetworkSettings();

    UFUNCTION(BlueprintCallable, Category = "Multiplayer System")
    void LoadNetworkSettings();

    UFUNCTION(BlueprintCallable, Category = "Multiplayer System")
    void ResetNetworkSettings();

protected:
    // Internal Functions
    void InitializeNetworkServices();
    void SetupEventHandlers();
    void StartHeartbeat();
    void StopHeartbeat();
    void UpdateConnectionQuality();
    void ProcessNetworkEvents();
    void HandleNetworkError(const FString& Error);

private:
    // Internal State
    FSessionInfo CurrentSession;
    FNetworkSettings NetworkSettings;
    TArray<FPlayerConnectionData> ConnectedPlayers;
    TArray<FSessionInfo> AvailableSessions;
    
    // Network State
    bool bIsInSession;
    bool bIsHost;
    bool bVoiceChatActive;
    bool bTextChatActive;
    bool bMatchmakingActive;
    bool bNetworkDebug;
    
    // Connection Data
    FString LocalPlayerID;
    int32 ConnectionQuality;
    float AveragePing;
    TArray<float> PingHistory;
    
    // Chat System
    TArray<FString> ChatHistory;
    TSet<FString> MutedPlayers;
    
    // Matchmaking
    TArray<FString> MatchmakingPreferences;
    
    // Timers
    float HeartbeatTimer;
    float QualityUpdateTimer;
    
    // Helper Functions
    FSessionInfo CreateSessionInfo(const FString& Name, ESessionType Type);
    FPlayerConnectionData CreatePlayerData(const FString& PlayerID, const FString& PlayerName);
    FNetworkSettings CreateDefaultNetworkSettings();
    void NotifySessionCreated(const FSessionInfo& SessionInfo);
    void NotifySessionJoined(const FSessionInfo& SessionInfo);
    void NotifySessionLeft(const FString& SessionID);
    void NotifyPlayerConnected(const FString& PlayerID, const FPlayerConnectionData& PlayerData);
    void NotifyPlayerDisconnected(const FString& PlayerID, const FPlayerConnectionData& PlayerData);
    void NotifyNetworkError(const FString& ErrorMessage);
    void NotifyConnectionQualityChanged(int32 Quality);
    void ProcessHeartbeat();
    void UpdatePlayerPing(const FString& PlayerID, float Ping);
    void CalculateConnectionQuality();
    void ValidateNetworkConfiguration();
    void SetupVoiceChat();
    void SetupTextChat();
    void InitializeMatchmakingService();
    void ConnectToMatchmakingService();
    void DisconnectFromMatchmakingService();
    void StartNetworkSimulation();
    void StopNetworkSimulation();
};
