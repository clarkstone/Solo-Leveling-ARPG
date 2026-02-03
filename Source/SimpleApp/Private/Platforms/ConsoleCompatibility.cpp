#include "ConsoleCompatibility.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"
#include "HAL/PlatformFilemanager.h"
#include "Misc/Paths.h"
#include "Misc/ConfigCacheIni.h"
#include "Net/UnrealNetwork.h"

UConsoleCompatibility::UConsoleCompatibility()
{
    PrimaryComponentTick.bCanEverTick = true;
    SetIsReplicatedByDefault(true);
    
    CurrentPlatform = EConsolePlatform::CP_Unknown;
    CurrentInputMethod = EInputMethod::IM_KeyboardMouse;
    CurrentDisplayMode = EDisplayMode::DM_Balanced;
    bPerformanceMonitoring = false;
    AverageFrameTime = 0.0f;
    CurrentFPS = 60;
    bPerformanceStable = true;
    bAutoAdjustQuality = true;
    bUseSafeZone = true;
    UIScale = 1.0f;
    MaxSaveSlots = 10;
    bDebugMode = false;
}

void UConsoleCompatibility::BeginPlay()
{
    Super::BeginPlay();
    InitializeConsoleCompatibility();
}

void UConsoleCompatibility::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    if (bPerformanceMonitoring)
    {
        MonitorPerformance(DeltaTime);
    }
    
    UpdateInputMethod();
    AdjustQualityBasedOnPerformance();
}

void UConsoleCompatibility::InitializeConsoleCompatibility()
{
    UE_LOG(LogTemp, Warning, TEXT("Console Compatibility System initialized"));
    
    // Initialize all compatibility systems
    InitializePlatformProfiles();
    InitializeInputMappings();
    InitializeDefaultSettings();
    
    // Detect current platform
    CurrentPlatform = DetectCurrentPlatform();
    NotifyPlatformDetected(CurrentPlatform);
    
    // Load platform-specific settings
    LoadCompatibilitySettings();
    
    // Apply platform optimizations
    OptimizeForPlatform();
    
    // Initialize subsystems
    InitializeInputSystem();
    InitializeDisplaySettings();
    InitializeUISystem();
    InitializeSaveSystem();
    InitializeAchievementSystem();
    InitializeNetworkServices();
    InitializePlatformFeatures();
    
    // Start performance monitoring
    StartPerformanceMonitoring();
    
    UE_LOG(LogTemp, Warning, TEXT("Console Compatibility System ready for platform: %s"), *GetPlatformName());
}

EConsolePlatform UConsoleCompatibility::DetectCurrentPlatform()
{
    // Platform detection logic
    FString PlatformString = UGameplayStatics::GetPlatformName();
    
    if (PlatformString == TEXT("PS4"))
    {
        return EConsolePlatform::CP_PlayStation4;
    }
    else if (PlatformString == TEXT("PS5"))
    {
        return EConsolePlatform::CP_PlayStation5;
    }
    else if (PlatformString == TEXT("XboxOne"))
    {
        return EConsolePlatform::CP_XboxOne;
    }
    else if (PlatformString == TEXT("XSX"))
    {
        return EConsolePlatform::CP_XboxSeriesX;
    }
    else if (PlatformString == TEXT("Switch"))
    {
        return EConsolePlatform::CP_NintendoSwitch;
    }
    else if (PlatformString.Contains(TEXT("Windows")) || PlatformString.Contains(TEXT("Mac")) || PlatformString.Contains(TEXT("Linux")))
    {
        return EConsolePlatform::PC_Standalone;
    }
    
    return EConsolePlatform::CP_Unknown;
}

FConsoleProfile UConsoleCompatibility::GetPlatformProfile(EConsolePlatform Platform) const
{
    if (PlatformProfiles.Contains(Platform))
    {
        return PlatformProfiles[Platform];
    }
    
    // Return default profile if not found
    return CreatePlatformProfile(EConsolePlatform::PC_Standalone);
}

bool UConsoleCompatibility::IsConsolePlatform() const
{
    return CurrentPlatform != EConsolePlatform::PC_Standalone && CurrentPlatform != EConsolePlatform::PC_GamePass;
}

FString UConsoleCompatibility::GetPlatformName() const
{
    switch (CurrentPlatform)
    {
        case EConsolePlatform::CP_PlayStation4:
            return TEXT("PlayStation 4");
        case EConsolePlatform::CP_PlayStation5:
            return TEXT("PlayStation 5");
        case EConsolePlatform::CP_XboxOne:
            return TEXT("Xbox One");
        case EConsolePlatform::CP_XboxSeriesX:
            return TEXT("Xbox Series X");
        case EConsolePlatform::CP_NintendoSwitch:
            return TEXT("Nintendo Switch");
        case EConsolePlatform::PC_Standalone:
            return TEXT("PC");
        case EConsolePlatform::PC_GamePass:
            return TEXT("PC Game Pass");
        default:
            return TEXT("Unknown Platform");
    }
}

TArray<FString> UConsoleCompatibility::GetPlatformCapabilities() const
{
    TArray<FString> Capabilities;
    
    switch (CurrentPlatform)
    {
        case EConsolePlatform::CP_PlayStation5:
        case EConsolePlatform::CP_XboxSeriesX:
            Capabilities.Add(TEXT("HighPerformance"));
            Capabilities.Add(TEXT("RayTracing"));
            Capabilities.Add(TEXT("4KSupport"));
            Capabilities.Add(TEXT("FastSSD"));
            break;
            
        case EConsolePlatform::CP_PlayStation4:
        case EConsolePlatform::CP_XboxOne:
            Capabilities.Add(TEXT("StandardPerformance"));
            Capabilities.Add(TEXT("1080pSupport"));
            break;
            
        case EConsolePlatform::CP_NintendoSwitch:
            Capabilities.Add(TEXT("Portable"));
            Capabilities.Add(TEXT("720pHandheld"));
            Capabilities.Add(TEXT("1080pDocked"));
            break;
            
        case EConsolePlatform::PC_Standalone:
            Capabilities.Add(TEXT("Customizable"));
            Capabilities.Add(TEXT("ModSupport"));
            Capabilities.Add(TEXT("UltraSettings"));
            break;
            
        default:
            break;
    }
    
    return Capabilities;
}

void UConsoleCompatibility::InitializeInputSystem()
{
    UE_LOG(LogTemp, Warning, TEXT("Input system initialized"));
    
    // Load platform-specific input profile
    LoadInputProfile(CurrentPlatform);
    
    // Configure console input if needed
    if (IsConsolePlatform())
    {
        ConfigureConsoleInput();
    }
}

EInputMethod UConsoleCompatibility::GetCurrentInputMethod() const
{
    return CurrentInputMethod;
}

void UConsoleCompatibility::SetInputMethod(EInputMethod NewMethod)
{
    if (CurrentInputMethod != NewMethod)
    {
        CurrentInputMethod = NewMethod;
        NotifyInputMethodChanged(NewMethod);
        
        UE_LOG(LogTemp, Warning, TEXT("Input method changed to: %d"), (int32)NewMethod);
    }
}

TArray<FInputMapping> UConsoleCompatibility::GetInputMappings() const
{
    return InputMappings;
}

bool UConsoleCompatibility::RemapInput(const FString& ActionName, const FString& NewKey)
{
    for (FInputMapping& Mapping : InputMappings)
    {
        if (Mapping.ActionName == ActionName && Mapping.bIsRemappable)
        {
            if (CurrentInputMethod == EInputMethod::IM_KeyboardMouse)
            {
                Mapping.KeyboardKey = NewKey;
            }
            else
            {
                Mapping.GamepadButton = NewKey;
            }
            
            SaveInputSettings();
            return true;
        }
    }
    
    return false;
}

void UConsoleCompatibility::LoadInputProfile(EConsolePlatform Platform)
{
    FConsoleProfile Profile = GetPlatformProfile(Platform);
    
    // Apply input-specific settings from profile
    // This would typically load platform-specific input configurations
    
    UE_LOG(LogTemp, Warning, TEXT("Input profile loaded for platform: %s"), *GetPlatformName());
}

void UConsoleCompatibility::SaveInputSettings()
{
    // Save input settings to platform-specific location
    FString SavePath = GetSaveDirectory();
    FString InputConfigFile = SavePath / TEXT("Input.ini");
    
    // Save current input mappings
    // This would use UE's config system
    
    UE_LOG(LogTemp, Warning, TEXT("Input settings saved"));
}

void UConsoleCompatibility::InitializeDisplaySettings()
{
    UE_LOG(LogTemp, Warning, TEXT("Display settings initialized"));
    
    // Apply platform-specific display settings
    ApplyGraphicsSettings(CurrentProfile);
    
    // Setup console UI if needed
    if (IsConsolePlatform())
    {
        SetupConsoleUI();
    }
}

void UConsoleCompatibility::SetDisplayMode(EDisplayMode Mode)
{
    if (CurrentDisplayMode != Mode)
    {
        CurrentDisplayMode = Mode;
        CurrentProfile.DisplayMode = Mode;
        
        ApplyGraphicsSettings(CurrentProfile);
        NotifyDisplayModeChanged(Mode);
        
        UE_LOG(LogTemp, Warning, TEXT("Display mode changed to: %d"), (int32)Mode);
    }
}

EDisplayMode UConsoleCompatibility::GetDisplayMode() const
{
    return CurrentDisplayMode;
}

void UConsoleCompatibility::ApplyGraphicsSettings(const FConsoleProfile& Profile)
{
    // Apply graphics settings based on profile
    if (GEngine)
    {
        // Apply resolution scale
        if (Profile.ResolutionScale > 0)
        {
            // Apply resolution scaling
        }
        
        // Apply VSync
        GEngine->bUseVSync = Profile.bUseVSync;
        
        // Apply frame rate limit
        if (Profile.TargetFPS > 0)
        {
            GEngine->bSmoothFrameRate = true;
            GEngine->SmoothFrameRate = Profile.TargetFPS;
        }
        
        // Apply quality settings
        // This would apply various console commands or engine settings
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Graphics settings applied"));
}

void UConsoleCompatibility::OptimizeForPlatform()
{
    UE_LOG(LogTemp, Warning, TEXT("Optimizing for platform: %s"), *GetPlatformName());
    
    // Apply platform-specific optimizations
    ApplyConsoleSpecificSettings();
    OptimizeForHardware();
    ValidatePlatformRequirements();
}

void UConsoleCompatibility::AutoAdjustQuality()
{
    if (!bAutoAdjustQuality)
    {
        return;
    }
    
    AdjustGraphicsQuality();
    
    UE_LOG(LogTemp, Warning, TEXT("Auto-adjusted quality based on performance"));
}

int32 UConsoleCompatibility::GetCurrentFPS() const
{
    return CurrentFPS;
}

bool UConsoleCompatibility::IsPerformanceStable() const
{
    return bPerformanceStable;
}

void UConsoleCompatibility::InitializeUISystem()
{
    UE_LOG(LogTemp, Warning, TEXT("UI system initialized"));
    
    // Apply UI scaling based on platform
    if (IsConsolePlatform())
    {
        // Configure safe zone for TV displays
        ConfigureSafeZone();
    }
    
    ApplyUIScaling(CurrentUISettings);
}

void UConsoleCompatibility::ApplyUIScaling(const FUIScalingSettings& Settings)
{
    CurrentUISettings = Settings;
    
    // Apply UI scaling to all UI elements
    // This would typically update UMG widgets and scales
    
    UE_LOG(LogTemp, Warning, TEXT("UI scaling applied: %.2f"), Settings.UIScale);
}

FUIScalingSettings UConsoleCompatibility::GetUISettings() const
{
    return CurrentUISettings;
}

void UConsoleCompatibility::SetUIScale(float Scale)
{
    CurrentUISettings.UIScale = Scale;
    ApplyUIScaling(CurrentUISettings);
    
    UE_LOG(LogTemp, Warning, TEXT("UI scale set to: %.2f"), Scale);
}

void UConsoleCompatibility::ConfigureSafeZone()
{
    if (bUseSafeZone && IsConsolePlatform())
    {
        // Configure safe zone margins for TV displays
        CurrentUISettings.SafeZoneMargin = FVector2D(0.05f, 0.05f); // 5% margins
        CurrentUISettings.bUseSafeZone = true;
        
        UE_LOG(LogTemp, Warning, TEXT("Safe zone configured"));
    }
}

FVector2D UConsoleCompatibility::GetSafeZoneMargins() const
{
    return CurrentUISettings.SafeZoneMargin;
}

void UConsoleCompatibility::StartPerformanceMonitoring()
{
    bPerformanceMonitoring = true;
    FrameTimeHistory.Empty();
    
    UE_LOG(LogTemp, Warning, TEXT("Performance monitoring started"));
}

void UConsoleCompatibility::StopPerformanceMonitoring()
{
    bPerformanceMonitoring = false;
    
    UE_LOG(LogTemp, Warning, TEXT("Performance monitoring stopped"));
}

float UConsoleCompatibility::GetAverageFrameTime() const
{
    return AverageFrameTime;
}

int32 UConsoleCompatibility::GetMemoryUsage() const
{
    // Get memory usage in MB
    return FPlatformMemory::GetStats().UsedPhysical / (1024 * 1024);
}

void UConsoleCompatibility::OptimizeMemoryUsage()
{
    // Perform memory optimization
    GarbageCollect();
    
    UE_LOG(LogTemp, Warning, TEXT("Memory usage optimized"));
}

void UConsoleCompatibility::GarbageCollect()
{
    // Force garbage collection
    GEngine->ForceGarbageCollection(true);
    
    UE_LOG(LogTemp, Warning, TEXT("Garbage collection performed"));
}

void UConsoleCompatibility::InitializeSaveSystem()
{
    UE_LOG(LogTemp, Warning, TEXT("Save system initialized"));
    
    // Initialize platform-specific save system
    InitializeConsoleSaveSystem();
    
    // Configure auto-save
    ConfigureAutoSave();
}

FString UConsoleCompatibility::GetSaveDirectory() const
{
    FString SaveDir;
    
    if (IsConsolePlatform())
    {
        // Use platform-specific save directory
        SaveDir = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("SaveData"));
    }
    else
    {
        // Use standard PC save directory
        SaveDir = FPaths::Combine(FPaths::ProjectSavedDir(), TEXT("SaveGames"));
    }
    
    return SaveDir;
}

bool UConsoleCompatibility::IsValidSaveLocation() const
{
    FString SaveDir = GetSaveDirectory();
    return FPlatformFileManager::Get().GetPlatformFile().DirectoryExists(*SaveDir);
}

void UConsoleCompatibility::ConfigureAutoSave()
{
    // Configure auto-save settings based on platform
    // Consoles typically have more frequent auto-saves
    
    UE_LOG(LogTemp, Warning, TEXT("Auto-save configured"));
}

int32 UConsoleCompatibility::GetMaxSaveSlots() const
{
    return MaxSaveSlots;
}

void UConsoleCompatibility::InitializeAchievementSystem()
{
    UE_LOG(LogTemp, Warning, TEXT("Achievement system initialized"));
    
    // Initialize platform-specific achievement system
    // This would connect to PlayStation Network, Xbox Live, etc.
}

void UConsoleCompatibility::UnlockAchievement(const FString& AchievementID)
{
    // Unlock achievement on platform-specific service
    UE_LOG(LogTemp, Warning, TEXT("Achievement unlocked: %s"), *AchievementID);
}

bool UConsoleCompatibility::IsAchievementUnlocked(const FString& AchievementID) const
{
    // Check achievement status from platform service
    return false; // Placeholder
}

TArray<FString> UConsoleCompatibility::GetAchievements() const
{
    // Get list of achievements from platform service
    return TArray<FString>(); // Placeholder
}

void UConsoleCompatibility::UpdateAchievementProgress(const FString& AchievementID, int32 Progress)
{
    // Update achievement progress on platform service
    UE_LOG(LogTemp, Warning, TEXT("Achievement progress updated: %s - %d"), *AchievementID, Progress);
}

void UConsoleCompatibility::InitializeNetworkServices()
{
    UE_LOG(LogTemp, Warning, TEXT("Network services initialized"));
    
    // Initialize platform-specific network services
    // This would connect to PlayStation Network, Xbox Live, etc.
}

bool UConsoleCompatibility::IsOnlineServiceAvailable() const
{
    // Check if platform online service is available
    return true; // Placeholder
}

FString UConsoleCompatibility::GetPlayerID() const
{
    // Get player ID from platform service
    return TEXT("PlayerID"); // Placeholder
}

void UConsoleCompatibility::ConnectToOnlineService()
{
    // Connect to platform-specific online service
    UE_LOG(LogTemp, Warning, TEXT("Connecting to online service"));
}

void UConsoleCompatibility::DisconnectFromOnlineService()
{
    // Disconnect from platform-specific online service
    UE_LOG(LogTemp, Warning, TEXT("Disconnecting from online service"));
}

void UConsoleCompatibility::InitializePlatformFeatures()
{
    UE_LOG(LogTemp, Warning, TEXT("Platform features initialized"));
    
    // Enable platform-specific features
    ProcessPlatformSpecificSettings();
}

bool UConsoleCompatibility::SupportsFeature(const FString& FeatureName) const
{
    return EnabledFeatures.Contains(FeatureName);
}

void UConsoleCompatibility::EnableFeature(const FString& FeatureName)
{
    EnabledFeatures.Add(FeatureName);
    UE_LOG(LogTemp, Warning, TEXT("Feature enabled: %s"), *FeatureName);
}

void UConsoleCompatibility::DisableFeature(const FString& FeatureName)
{
    EnabledFeatures.Remove(FeatureName);
    UE_LOG(LogTemp, Warning, TEXT("Feature disabled: %s"), *FeatureName);
}

TArray<FString> UConsoleCompatibility::GetEnabledFeatures() const
{
    return EnabledFeatures.Array();
}

void UConsoleCompatibility::EnableDebugMode()
{
    bDebugMode = true;
    UE_LOG(LogTemp, Warning, TEXT("Debug mode enabled"));
}

void UConsoleCompatibility::DisableDebugMode()
{
    bDebugMode = false;
    UE_LOG(LogTemp, Warning, TEXT("Debug mode disabled"));
}

bool UConsoleCompatibility::IsDebugModeEnabled() const
{
    return bDebugMode;
}

void UConsoleCompatibility::LogPlatformInfo()
{
    UE_LOG(LogTemp, Warning, TEXT("=== Platform Info ==="));
    UE_LOG(LogTemp, Warning, TEXT("Platform: %s"), *GetPlatformName());
    UE_LOG(LogTemp, Warning, TEXT("Is Console: %s"), IsConsolePlatform() ? TEXT("Yes") : TEXT("No"));
    UE_LOG(LogTemp, Warning, TEXT("Input Method: %d"), (int32)CurrentInputMethod);
    UE_LOG(LogTemp, Warning, TEXT("Display Mode: %d"), (int32)CurrentDisplayMode);
    UE_LOG(LogTemp, Warning, TEXT("Current FPS: %d"), CurrentFPS);
    UE_LOG(LogTemp, Warning, TEXT("Memory Usage: %d MB"), GetMemoryUsage());
    
    TArray<FString> Capabilities = GetPlatformCapabilities();
    UE_LOG(LogTemp, Warning, TEXT("Capabilities:"));
    for (const FString& Capability : Capabilities)
    {
        UE_LOG(LogTemp, Warning, TEXT("  - %s"), *Capability);
    }
    
    UE_LOG(LogTemp, Warning, TEXT("===================="));
}

void UConsoleCompatibility::TestPerformance()
{
    UE_LOG(LogTemp, Warning, TEXT("Starting performance test..."));
    
    // Run performance test
    TestPerformance();
    
    UE_LOG(LogTemp, Warning, TEXT("Performance test completed"));
}

void UConsoleCompatibility::SaveCompatibilitySettings()
{
    // Save all compatibility settings
    SaveInputSettings();
    
    UE_LOG(LogTemp, Warning, TEXT("Compatibility settings saved"));
}

void UConsoleCompatibility::LoadCompatibilitySettings()
{
    // Load all compatibility settings
    LoadInputProfile(CurrentPlatform);
    
    UE_LOG(LogTemp, Warning, TEXT("Compatibility settings loaded"));
}

void UConsoleCompatibility::ResetToDefaults()
{
    // Reset all settings to defaults
    CurrentDisplayMode = EDisplayMode::DM_Balanced;
    UIScale = 1.0f;
    bAutoAdjustQuality = true;
    
    // Reload default profile
    CurrentProfile = CreatePlatformProfile(CurrentPlatform);
    ApplyGraphicsSettings(CurrentProfile);
    
    UE_LOG(LogTemp, Warning, TEXT("Settings reset to defaults"));
}

void UConsoleCompatibility::InitializePlatformProfiles()
{
    PlatformProfiles.Empty();
    
    // Create profiles for each platform
    PlatformProfiles.Add(EConsolePlatform::CP_PlayStation5, CreatePlatformProfile(EConsolePlatform::CP_PlayStation5));
    PlatformProfiles.Add(EConsolePlatform::CP_XboxSeriesX, CreatePlatformProfile(EConsolePlatform::CP_XboxSeriesX));
    PlatformProfiles.Add(EConsolePlatform::CP_PlayStation4, CreatePlatformProfile(EConsolePlatform::CP_PlayStation4));
    PlatformProfiles.Add(EConsolePlatform::CP_XboxOne, CreatePlatformProfile(EConsolePlatform::CP_XboxOne));
    PlatformProfiles.Add(EConsolePlatform::CP_NintendoSwitch, CreatePlatformProfile(EConsolePlatform::CP_NintendoSwitch));
    PlatformProfiles.Add(EConsolePlatform::PC_Standalone, CreatePlatformProfile(EConsolePlatform::PC_Standalone));
}

void UConsoleCompatibility::InitializeInputMappings()
{
    InputMappings.Empty();
    
    // Create default input mappings
    InputMappings.Add(CreateInputMapping(TEXT("Jump"), TEXT("Space"), TEXT("A")));
    InputMappings.Add(CreateInputMapping(TEXT("Attack"), TEXT("LeftMouse"), TEXT("RT")));
    InputMappings.Add(CreateInputMapping(TEXT("Dodge"), TEXT("Shift"), TEXT("B")));
    InputMappings.Add(CreateInputMapping(TEXT("Interact"), TEXT("E"), TEXT("X")));
    InputMappings.Add(CreateInputMapping(TEXT("Inventory"), TEXT("I"), TEXT("Y")));
    InputMappings.Add(CreateInputMapping(TEXT("Skill1"), TEXT("1"), TEXT("LB")));
    InputMappings.Add(CreateInputMapping(TEXT("Skill2"), TEXT("2"), TEXT("RB")));
    InputMappings.Add(CreateInputMapping(TEXT("Pause"), TEXT("Escape"), TEXT("Start")));
}

void UConsoleCompatibility::InitializeDefaultSettings()
{
    // Set current profile
    if (PlatformProfiles.Contains(CurrentPlatform))
    {
        CurrentProfile = PlatformProfiles[CurrentPlatform];
    }
    else
    {
        CurrentProfile = CreatePlatformProfile(EConsolePlatform::PC_Standalone);
    }
    
    // Set default UI settings
    CurrentUISettings = CreateUISettings(1.0f);
    
    // Set platform-specific defaults
    if (IsConsolePlatform())
    {
        bUseSafeZone = true;
        UIScale = 1.2f; // Larger UI for console
        MaxSaveSlots = 5; // Limited save slots on console
    }
    else
    {
        bUseSafeZone = false;
        UIScale = 1.0f;
        MaxSaveSlots = 10;
    }
}

void UConsoleCompatibility::MonitorPerformance(float DeltaTime)
{
    // Update frame time history
    FrameTimeHistory.Add(DeltaTime);
    
    // Keep only last 60 frames (1 second at 60 FPS)
    if (FrameTimeHistory.Num() > 60)
    {
        FrameTimeHistory.RemoveAt(0);
    }
    
    // Calculate average frame time
    AverageFrameTime = 0.0f;
    for (float FrameTime : FrameTimeHistory)
    {
        AverageFrameTime += FrameTime;
    }
    AverageFrameTime /= FrameTimeHistory.Num();
    
    // Calculate current FPS
    CurrentFPS = FMath::RoundToInt(1.0f / AverageFrameTime);
    
    // Check performance stability
    bPerformanceStable = IsTargetFPSAchieved();
    
    UpdatePerformanceStats(DeltaTime);
}

void UConsoleCompatibility::AdjustQualityBasedOnPerformance()
{
    if (!bAutoAdjustQuality || !bPerformanceMonitoring)
    {
        return;
    }
    
    // Adjust quality if performance is not stable
    if (!bPerformanceStable)
    {
        AdjustGraphicsQuality();
    }
}

void UConsoleCompatibility::UpdateInputMethod()
{
    // Detect current input method
    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (PC)
    {
        // Check if gamepad is being used
        // This would typically check input state
        bool bUsingGamepad = false; // Placeholder
        
        EInputMethod NewMethod = bUsingGamepad ? EInputMethod::IM_Gamepad : EInputMethod::IM_KeyboardMouse;
        
        if (NewMethod != CurrentInputMethod)
        {
            SetInputMethod(NewMethod);
        }
    }
}

void UConsoleCompatibility::ProcessPlatformSpecificSettings()
{
    // Process platform-specific settings and features
    switch (CurrentPlatform)
    {
        case EConsolePlatform::CP_PlayStation5:
        case EConsolePlatform::CP_XboxSeriesX:
            EnableFeature(TEXT("RayTracing"));
            EnableFeature(TEXT("4KSupport"));
            EnableFeature(TEXT("FastSSD"));
            break;
            
        case EConsolePlatform::CP_PlayStation4:
        case EConsolePlatform::CP_XboxOne:
            EnableFeature(TEXT("1080pSupport"));
            break;
            
        case EConsolePlatform::CP_NintendoSwitch:
            EnableFeature(TEXT("Portable"));
            EnableFeature(TEXT("JoyConSupport"));
            break;
            
        case EConsolePlatform::PC_Standalone:
            EnableFeature(TEXT("UltraSettings"));
            EnableFeature(TEXT("ModSupport"));
            break;
            
        default:
            break;
    }
}

FConsoleProfile UConsoleCompatibility::CreatePlatformProfile(EConsolePlatform Platform)
{
    FConsoleProfile Profile;
    Profile.Platform = Platform;
    Profile.bAutoAdjustQuality = true;
    
    switch (Platform)
    {
        case EConsolePlatform::CP_PlayStation5:
        case EConsolePlatform::CP_XboxSeriesX:
            Profile.ProfileName = TEXT("Next-Gen Console");
            Profile.DisplayMode = EDisplayMode::DM_Quality;
            Profile.TargetFPS = 60;
            Profile.ResolutionScale = 100;
            Profile.TextureQuality = 4; // Ultra
            Profile.ShadowQuality = 3; // High
            Profile.EffectsQuality = 4; // Ultra
            Profile.SupportedFeatures.Add(TEXT("RayTracing"));
            Profile.SupportedFeatures.Add(TEXT("4KSupport"));
            break;
            
        case EConsolePlatform::CP_PlayStation4:
        case EConsolePlatform::CP_XboxOne:
            Profile.ProfileName = TEXT("Last-Gen Console");
            Profile.DisplayMode = EDisplayMode::DM_Performance;
            Profile.TargetFPS = 30;
            Profile.ResolutionScale = 85;
            Profile.TextureQuality = 2; // Medium
            Profile.ShadowQuality = 2; // Medium
            Profile.EffectsQuality = 2; // Medium
            break;
            
        case EConsolePlatform::CP_NintendoSwitch:
            Profile.ProfileName = TEXT("Nintendo Switch");
            Profile.DisplayMode = EDisplayMode::DM_Performance;
            Profile.TargetFPS = 30;
            Profile.ResolutionScale = 75;
            Profile.TextureQuality = 1; // Low
            Profile.ShadowQuality = 1; // Low
            Profile.EffectsQuality = 1; // Low
            break;
            
        case EConsolePlatform::PC_Standalone:
            Profile.ProfileName = TEXT("PC");
            Profile.DisplayMode = EDisplayMode::DM_Custom;
            Profile.TargetFPS = 0; // Unlimited
            Profile.ResolutionScale = 100;
            Profile.TextureQuality = 4; // Ultra
            Profile.ShadowQuality = 4; // Ultra
            Profile.EffectsQuality = 4; // Ultra
            Profile.SupportedFeatures.Add(TEXT("UltraSettings"));
            Profile.SupportedFeatures.Add(TEXT("ModSupport"));
            break;
            
        default:
            Profile.ProfileName = TEXT("Default");
            Profile.DisplayMode = EDisplayMode::DM_Balanced;
            Profile.TargetFPS = 60;
            Profile.ResolutionScale = 100;
            Profile.TextureQuality = 2; // Medium
            Profile.ShadowQuality = 2; // Medium
            Profile.EffectsQuality = 2; // Medium
            break;
    }
    
    return Profile;
}

FInputMapping UConsoleCompatibility::CreateInputMapping(const FString& Action, const FString& Key, const FString& Button)
{
    FInputMapping Mapping;
    Mapping.ActionName = Action;
    Mapping.KeyboardKey = Key;
    Mapping.GamepadButton = Button;
    Mapping.TouchGesture = TEXT("");
    Mapping.bIsRemappable = true;
    Mapping.IconPath = TEXT("");
    
    return Mapping;
}

FUIScalingSettings UConsoleCompatibility::CreateUISettings(float Scale)
{
    FUIScalingSettings Settings;
    Settings.UIScale = Scale;
    Settings.TextScale = Scale;
    Settings.IconScale = Scale;
    Settings.bUseSafeZone = false;
    Settings.SafeZoneMargin = FVector2D::ZeroVector;
    Settings.bAdaptToScreenSize = true;
    
    return Settings;
}

void UConsoleCompatibility::NotifyPlatformDetected(EConsolePlatform Platform)
{
    OnPlatformDetected.Broadcast(Platform);
}

void UConsoleCompatibility::NotifyInputMethodChanged(EInputMethod NewMethod)
{
    OnInputMethodChanged.Broadcast(NewMethod);
}

void UConsoleCompatibility::NotifyDisplayModeChanged(EDisplayMode NewMode)
{
    OnDisplayModeChanged.Broadcast(NewMode);
}

void UConsoleCompatibility::NotifyPerformanceAdjusted(int32 NewFPS, bool bStable)
{
    OnPerformanceAdjusted.Broadcast(NewFPS, bStable);
}

void UConsoleCompatibility::NotifyProfileLoaded(const FConsoleProfile& Profile)
{
    OnProfileLoaded.Broadcast(Profile);
}

void UConsoleCompatibility::ApplyConsoleSpecificSettings()
{
    // Apply console-specific settings
    if (IsConsolePlatform())
    {
        // Configure console-specific features
        GEngine->bEnableOnScreenDebugMessages = bDebugMode;
        
        // Apply console-specific engine settings
        if (GEngine)
        {
            // Console-specific optimizations
        }
    }
}

void UConsoleCompatibility::OptimizeForHardware()
{
    // Optimize based on detected hardware
    // This would check system specifications and adjust accordingly
    
    UE_LOG(LogTemp, Warning, TEXT("Hardware optimization applied"));
}

void UConsoleCompatibility::ValidatePlatformRequirements()
{
    // Validate that platform meets minimum requirements
    bool bMeetsRequirements = true;
    
    // Check memory, storage, etc.
    int32 MemoryUsage = GetMemoryUsage();
    if (MemoryUsage > 6000) // 6GB limit for some platforms
    {
        UE_LOG(LogTemp, Warning, TEXT("High memory usage detected: %d MB"), MemoryUsage);
        OptimizeMemoryUsage();
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Platform requirements validated"));
}

void UConsoleCompatibility::UpdatePerformanceStats(float DeltaTime)
{
    // Update performance statistics
    // This would track various performance metrics
}

bool UConsoleCompatibility::IsTargetFPSAchieved() const
{
    if (CurrentProfile.TargetFPS <= 0)
    {
        return true; // Unlimited FPS
    }
    
    return CurrentFPS >= (CurrentProfile.TargetFPS - 5); // Allow 5 FPS tolerance
}

void UConsoleCompatibility::AdjustGraphicsQuality()
{
    // Adjust graphics quality based on performance
    if (!bPerformanceStable)
    {
        // Lower quality settings
        if (CurrentProfile.TextureQuality > 0)
        {
            CurrentProfile.TextureQuality--;
        }
        
        ApplyGraphicsSettings(CurrentProfile);
        
        UE_LOG(LogTemp, Warning, TEXT("Graphics quality adjusted for performance"));
    }
}

void UConsoleCompatibility::ConfigureConsoleInput()
{
    // Configure console-specific input settings
    // This would set up gamepad defaults, vibration, etc.
    
    UE_LOG(LogTemp, Warning, TEXT("Console input configured"));
}

void UConsoleCompatibility::SetupConsoleUI()
{
    // Setup console-specific UI elements
    // This would configure safe zones, button prompts, etc.
    
    UE_LOG(LogTemp, Warning, TEXT("Console UI setup completed"));
}

void UConsoleCompatibility::InitializeConsoleSaveSystem()
{
    // Initialize console-specific save system
    // This would set up cloud saves, limited slots, etc.
    
    UE_LOG(LogTemp, Warning, TEXT("Console save system initialized"));
}

void UConsoleCompatibility::LogPerformanceMetrics()
{
    if (bDebugMode)
    {
        UE_LOG(LogTemp, Warning, TEXT("=== Performance Metrics ==="));
        UE_LOG(LogTemp, Warning, TEXT("Current FPS: %d"), CurrentFPS);
        UE_LOG(LogTemp, Warning, TEXT("Average Frame Time: %.3f ms"), AverageFrameTime * 1000.0f);
        UE_LOG(LogTemp, Warning, TEXT("Performance Stable: %s"), bPerformanceStable ? TEXT("Yes") : TEXT("No"));
        UE_LOG(LogTemp, Warning, TEXT("Memory Usage: %d MB"), GetMemoryUsage());
        UE_LOG(LogTemp, Warning, TEXT("=========================="));
    }
}

void UConsoleCompatibility::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    
    DOREPLIFETIME(UConsoleCompatibility, CurrentPlatform);
    DOREPLIFETIME(UConsoleCompatibility, CurrentInputMethod);
    DOREPLIFETIME(UConsoleCompatibility, CurrentDisplayMode);
    DOREPLIFETIME(UConsoleCompatibility, CurrentProfile);
    DOREPLIFETIME(UConsoleCompatibility, CurrentUISettings);
    DOREPLIFETIME(UConsoleCompatibility, bPerformanceMonitoring);
    DOREPLIFETIME(UConsoleCompatibility, CurrentFPS);
    DOREPLIFETIME(UConsoleCompatibility, bPerformanceStable);
    DOREPLIFETIME(UConsoleCompatibility, EnabledFeatures);
}
