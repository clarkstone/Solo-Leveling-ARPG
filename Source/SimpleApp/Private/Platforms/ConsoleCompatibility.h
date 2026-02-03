#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "ConsoleCompatibility.generated.h"

UENUM(BlueprintType)
enum class EConsolePlatform : uint8
{
    CP_Unknown = 0,
    CP_PlayStation4,
    CP_PlayStation5,
    CP_XboxOne,
    CP_XboxSeriesX,
    CP_NintendoSwitch,
    PC_Standalone,
    PC_GamePass
};

UENUM(BlueprintType)
enum class EInputMethod : uint8
{
    IM_KeyboardMouse = 0,
    IM_Gamepad,
    IM_Touch,
    IM_MotionControls,
    IM_Voice,
    IM_Adaptive
};

UENUM(BlueprintType)
enum class EDisplayMode : uint8
{
    DM_Performance = 0,    // Prioritize framerate
    DM_Quality,           // Prioritize visual quality
    DM_Balanced,          // Balanced mode
    DM_Custom             // User settings
};

USTRUCT(BlueprintType)
struct FConsoleProfile
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Console Profile")
    EConsolePlatform Platform;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Console Profile")
    FString ProfileName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Console Profile")
    EDisplayMode DisplayMode;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Console Profile")
    int32 TargetFPS;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Console Profile")
    int32 ResolutionScale;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Console Profile")
    bool bUseVSync;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Console Profile")
    bool bUseMotionBlur;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Console Profile")
    float FieldOfView;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Console Profile")
    int32 TextureQuality;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Console Profile")
    int32 ShadowQuality;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Console Profile")
    int32 EffectsQuality;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Console Profile")
    bool bAutoAdjustQuality;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Console Profile")
    TArray<FString> SupportedFeatures;
};

USTRUCT(BlueprintType)
struct FInputMapping
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Mapping")
    FString ActionName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Mapping")
    FString KeyboardKey;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Mapping")
    FString GamepadButton;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Mapping")
    FString TouchGesture;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Mapping")
    bool bIsRemappable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input Mapping")
    FString IconPath;
};

USTRUCT(BlueprintType)
struct FUIScalingSettings
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Scaling")
    float UIScale;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Scaling")
    float TextScale;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Scaling")
    float IconScale;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Scaling")
    bool bUseSafeZone;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Scaling")
    FVector2D SafeZoneMargin;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Scaling")
    bool bAdaptToScreenSize;
};

UCLASS(BlueprintType, Blueprintable)
class SIMPLEAPP_API UConsoleCompatibility : public UActorComponent
{
    GENERATED_BODY()

public:
    UConsoleCompatibility();

    // Console Compatibility Events
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlatformDetected, EConsolePlatform, Platform);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInputMethodChanged, EInputMethod, NewMethod);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDisplayModeChanged, EDisplayMode, NewMode);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPerformanceAdjusted, int32, NewFPS, bool, bStable);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnProfileLoaded, const FConsoleProfile&, Profile);

    UPROPERTY(BlueprintAssignable, Category = "Console Events")
    FOnPlatformDetected OnPlatformDetected;

    UPROPERTY(BlueprintAssignable, Category = "Console Events")
    FOnInputMethodChanged OnInputMethodChanged;

    UPROPERTY(BlueprintAssignable, Category = "Console Events")
    FOnDisplayModeChanged OnDisplayModeChanged;

    UPROPERTY(BlueprintAssignable, Category = "Console Events")
    FOnPerformanceAdjusted OnPerformanceAdjusted;

    UPROPERTY(BlueprintAssignable, Category = "Console Events")
    FOnProfileLoaded OnProfileLoaded;

    // Override UActorComponent functions
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Platform Detection
    UFUNCTION(BlueprintCallable, Category = "Console Compatibility")
    void InitializeConsoleCompatibility();

    UFUNCTION(BlueprintCallable, Category = "Platform")
    EConsolePlatform DetectCurrentPlatform();

    UFUNCTION(BlueprintCallable, Category = "Platform")
    FConsoleProfile GetPlatformProfile(EConsolePlatform Platform) const;

    UFUNCTION(BlueprintCallable, Category = "Platform")
    bool IsConsolePlatform() const;

    UFUNCTION(BlueprintCallable, Category = "Platform")
    FString GetPlatformName() const;

    UFUNCTION(BlueprintCallable, Category = "Platform")
    TArray<FString> GetPlatformCapabilities() const;

    // Input Management
    UFUNCTION(BlueprintCallable, Category = "Input")
    void InitializeInputSystem();

    UFUNCTION(BlueprintCallable, Category = "Input")
    EInputMethod GetCurrentInputMethod() const;

    UFUNCTION(BlueprintCallable, Category = "Input")
    void SetInputMethod(EInputMethod NewMethod);

    UFUNCTION(BlueprintCallable, Category = "Input")
    TArray<FInputMapping> GetInputMappings() const;

    UFUNCTION(BlueprintCallable, Category = "Input")
    bool RemapInput(const FString& ActionName, const FString& NewKey);

    UFUNCTION(BlueprintCallable, Category = "Input")
    void LoadInputProfile(EConsolePlatform Platform);

    UFUNCTION(BlueprintCallable, Category = "Input")
    void SaveInputSettings();

    // Display Management
    UFUNCTION(BlueprintCallable, Category = "Display")
    void InitializeDisplaySettings();

    UFUNCTION(BlueprintCallable, Category = "Display")
    void SetDisplayMode(EDisplayMode Mode);

    UFUNCTION(BlueprintCallable, Category = "Display")
    EDisplayMode GetDisplayMode() const;

    UFUNCTION(BlueprintCallable, Category = "Display")
    void ApplyGraphicsSettings(const FConsoleProfile& Profile);

    UFUNCTION(BlueprintCallable, Category = "Display")
    void OptimizeForPlatform();

    UFUNCTION(BlueprintCallable, Category = "Display")
    void AutoAdjustQuality();

    UFUNCTION(BlueprintCallable, Category = "Display")
    int32 GetCurrentFPS() const;

    UFUNCTION(BlueprintCallable, Category = "Display")
    bool IsPerformanceStable() const;

    // UI Scaling
    UFUNCTION(BlueprintCallable, Category = "UI")
    void InitializeUISystem();

    UFUNCTION(BlueprintCallable, Category = "UI")
    void ApplyUIScaling(const FUIScalingSettings& Settings);

    UFUNCTION(BlueprintCallable, Category = "UI")
    FUIScalingSettings GetUISettings() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    void SetUIScale(float Scale);

    UFUNCTION(BlueprintCallable, Category = "UI")
    void ConfigureSafeZone();

    UFUNCTION(BlueprintCallable, Category = "UI")
    FVector2D GetSafeZoneMargins() const;

    // Performance Monitoring
    UFUNCTION(BlueprintCallable, Category = "Performance")
    void StartPerformanceMonitoring();

    UFUNCTION(BlueprintCallable, Category = "Performance")
    void StopPerformanceMonitoring();

    UFUNCTION(BlueprintCallable, Category = "Performance")
    float GetAverageFrameTime() const;

    UFUNCTION(BlueprintCallable, Category = "Performance")
    int32 GetMemoryUsage() const;

    UFUNCTION(BlueprintCallable, Category = "Performance")
    void OptimizeMemoryUsage();

    UFUNCTION(BlueprintCallable, Category = "Performance")
    void GarbageCollect();

    // Save System
    UFUNCTION(BlueprintCallable, Category = "Console Compatibility")
    void InitializeSaveSystem();

    UFUNCTION(BlueprintCallable, Category = "Save System")
    FString GetSaveDirectory() const;

    UFUNCTION(BlueprintCallable, Category = "Save System")
    bool IsValidSaveLocation() const;

    UFUNCTION(BlueprintCallable, Category = "Save System")
    void ConfigureAutoSave();

    UFUNCTION(BlueprintCallable, Category = "Save System")
    int32 GetMaxSaveSlots() const;

    // Achievement System
    UFUNCTION(BlueprintCallable, Category = "Achievements")
    void InitializeAchievementSystem();

    UFUNCTION(BlueprintCallable, Category = "Achievements")
    void UnlockAchievement(const FString& AchievementID);

    UFUNCTION(BlueprintCallable, Category = "Achievements")
    bool IsAchievementUnlocked(const FString& AchievementID) const;

    UFUNCTION(BlueprintCallable, Category = "Achievements")
    TArray<FString> GetAchievements() const;

    UFUNCTION(BlueprintCallable, Category = "Achievements")
    void UpdateAchievementProgress(const FString& AchievementID, int32 Progress);

    // Network Services
    UFUNCTION(BlueprintCallable, Category = "Network")
    void InitializeNetworkServices();

    UFUNCTION(BlueprintCallable, Category = "Network")
    bool IsOnlineServiceAvailable() const;

    UFUNCTION(BlueprintCallable, Category = "Network")
    FString GetPlayerID() const;

    UFUNCTION(BlueprintCallable, Category = "Network")
    void ConnectToOnlineService();

    UFUNCTION(BlueprintCallable, Category = "Network")
    void DisconnectFromOnlineService();

    // Platform-Specific Features
    UFUNCTION(BlueprintCallable, Category = "Platform Features")
    void InitializePlatformFeatures();

    UFUNCTION(BlueprintCallable, Category = "Platform Features")
    bool SupportsFeature(const FString& FeatureName) const;

    UFUNCTION(BlueprintCallable, Category = "Platform Features")
    void EnableFeature(const FString& FeatureName);

    UFUNCTION(BlueprintCallable, Category = "Platform Features")
    void DisableFeature(const FString& FeatureName);

    UFUNCTION(BlueprintCallable, Category = "Platform Features")
    TArray<FString> GetEnabledFeatures() const;

    // Debug and Testing
    UFUNCTION(BlueprintCallable, Category = "Debug")
    void EnableDebugMode();

    UFUNCTION(BlueprintCallable, Category = "Debug")
    void DisableDebugMode();

    UFUNCTION(BlueprintCallable, Category = "Debug")
    bool IsDebugModeEnabled() const;

    UFUNCTION(BlueprintCallable, Category = "Debug")
    void LogPlatformInfo();

    UFUNCTION(BlueprintCallable, Category = "Debug")
    void TestPerformance();

    // Save/Load Settings
    UFUNCTION(BlueprintCallable, Category = "Console Compatibility")
    void SaveCompatibilitySettings();

    UFUNCTION(BlueprintCallable, Category = "Console Compatibility")
    void LoadCompatibilitySettings();

    UFUNCTION(BlueprintCallable, Category = "Console Compatibility")
    void ResetToDefaults();

protected:
    // Internal Functions
    void InitializePlatformProfiles();
    void InitializeInputMappings();
    void InitializeDefaultSettings();
    void MonitorPerformance(float DeltaTime);
    void AdjustQualityBasedOnPerformance();
    void UpdateInputMethod();
    void ProcessPlatformSpecificSettings();

private:
    // Internal State
    EConsolePlatform CurrentPlatform;
    EInputMethod CurrentInputMethod;
    EDisplayMode CurrentDisplayMode;
    FConsoleProfile CurrentProfile;
    FUIScalingSettings CurrentUISettings;
    
    // Performance Monitoring
    bool bPerformanceMonitoring;
    float AverageFrameTime;
    int32 CurrentFPS;
    bool bPerformanceStable;
    TArray<float> FrameTimeHistory;
    
    // Platform Data
    TMap<EConsolePlatform, FConsoleProfile> PlatformProfiles;
    TArray<FInputMapping> InputMappings;
    TSet<FString> EnabledFeatures;
    
    // Settings
    bool bAutoAdjustQuality;
    bool bUseSafeZone;
    float UIScale;
    int32 MaxSaveSlots;
    
    // Debug
    bool bDebugMode;
    
    // Helper Functions
    FConsoleProfile CreatePlatformProfile(EConsolePlatform Platform);
    FInputMapping CreateInputMapping(const FString& Action, const FString& Key, const FString& Button);
    FUIScalingSettings CreateUISettings(float Scale);
    void NotifyPlatformDetected(EConsolePlatform Platform);
    void NotifyInputMethodChanged(EInputMethod NewMethod);
    void NotifyDisplayModeChanged(EDisplayMode NewMode);
    void NotifyPerformanceAdjusted(int32 NewFPS, bool bStable);
    void NotifyProfileLoaded(const FConsoleProfile& Profile);
    void ApplyConsoleSpecificSettings();
    void OptimizeForHardware();
    void UpdatePerformanceStats(float DeltaTime);
    bool IsTargetFPSAchieved() const;
    void AdjustGraphicsQuality();
    void ConfigureConsoleInput();
    void SetupConsoleUI();
    void InitializeConsoleSaveSystem();
    void ValidatePlatformRequirements();
    void LogPerformanceMetrics();
};
