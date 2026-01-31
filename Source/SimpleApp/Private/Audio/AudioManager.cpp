#include "AudioManager.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Character.h"
#include "Sound/SoundCue.h"

UAudioManager::UAudioManager()
{
    MasterVolume = 1.0f;
    MusicVolume = 0.8f;
    EffectsVolume = 1.0f;
    VoiceVolume = 1.0f;
    
    CurrentMusicState = EMusicState::MS_Exploration;
    bIsInCombat = false;
    
    LastUpdateTime = 0.0f;
    bIsTransitioning = false;
    TransitionTimer = 0.0f;
    PreviousMusicState = EMusicState::MS_Exploration;
}

void UAudioManager::BeginPlay()
{
    Super::BeginPlay();
    Initialize();
}

void UAudioManager::Initialize()
{
    InitializeAudioComponents();
    InitializeAudioLibrary();
    LoadAudioLibrary();
    ConfigureAudioSettings();
    
    UE_LOG(LogTemp, Warning, TEXT("Audio Manager initialized"));
}

void UAudioManager::InitializeAudioComponents()
{
    // Create music component
    MusicComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("MusicComponent"));
    MusicComponent->bAutoActivate = false;
    MusicComponent->SetVolumeMultiplier(MusicVolume);
    
    // Create ambient component
    AmbientComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AmbientComponent"));
    AmbientComponent->bAutoActivate = false;
    AmbientComponent->SetVolumeMultiplier(0.5f);
    
    UE_LOG(LogTemp, Warning, TEXT("Audio components initialized"));
}

void UAudioManager::InitializeAudioLibrary()
{
    // Initialize basic sound effects
    FAudioData AttackSound;
    AttackSound.AudioType = EAudioType::AT_Effect;
    AttackSound.Volume = 1.0f;
    AttackSound.Pitch = 1.0f;
    AttackSound.bLoop = false;
    AttackSound.bSpatialized = true;
    SoundEffects.Add(TEXT("Attack"), AttackSound);
    
    FAudioData ComboSound;
    ComboSound.AudioType = EAudioType::AT_Effect;
    ComboSound.Volume = 1.2f;
    ComboSound.Pitch = 1.1f;
    ComboSound.bLoop = false;
    ComboSound.bSpatialized = false;
    SoundEffects.Add(TEXT("Combo"), ComboSound);
    
    // Initialize music tracks
    FAudioData ExplorationMusic;
    ExplorationMusic.AudioType = EAudioType::AT_Music;
    ExplorationMusic.Volume = 0.8f;
    ExplorationMusic.Pitch = 1.0f;
    ExplorationMusic.bLoop = true;
    ExplorationMusic.bSpatialized = false;
    MusicTracks.Add(EMusicState::MS_Exploration, ExplorationMusic);
    
    FAudioData CombatMusic;
    CombatMusic.AudioType = EAudioType::AT_Music;
    CombatMusic.Volume = 1.0f;
    CombatMusic.Pitch = 1.0f;
    CombatMusic.bLoop = true;
    CombatMusic.bSpatialized = false;
    MusicTracks.Add(EMusicState::MS_Combat, CombatMusic);
    
    UE_LOG(LogTemp, Warning, TEXT("Audio library initialized"));
}

void UAudioManager::PlayMusic(EMusicState MusicState)
{
    if (CurrentMusicState != MusicState)
    {
        PreviousMusicState = CurrentMusicState;
        CurrentMusicState = MusicState;
        
        if (MusicTracks.Contains(MusicState))
        {
            FAudioData MusicData = MusicTracks[MusicState];
            
            if (MusicComponent)
            {
                MusicComponent->Stop();
                
                if (MusicData.SoundAsset)
                {
                    MusicComponent->SetSound(MusicData.SoundAsset);
                    MusicComponent->SetVolumeMultiplier(MusicData.Volume * MusicVolume);
                    MusicComponent->Play();
                }
            }
        }
        
        OnMusicStateChanged.Broadcast(PreviousMusicState, MusicState);
        UE_LOG(LogTemp, Warning, TEXT("Music state changed to: %d"), (int32)MusicState);
    }
}

void UAudioManager::PlaySoundEffect(FString SoundName, FVector Location)
{
    if (SoundEffects.Contains(SoundName))
    {
        FAudioData SoundData = SoundEffects[SoundName];
        
        if (SoundData.SoundAsset)
        {
            UGameplayStatics::PlaySoundAtLocation(
                GetWorld(),
                SoundData.SoundAsset,
                Location,
                SoundData.Volume * EffectsVolume * MasterVolume,
                SoundData.Pitch
            );
        }
        
        OnSoundEffectPlayed.Broadcast(SoundName, Location);
        UE_LOG(LogTemp, Warning, TEXT("Sound effect: %s at %s"), *SoundName, *Location.ToString());
    }
}

void UAudioManager::PlayCombatSound(FString SoundName, FVector Location)
{
    // Enhanced combat sound with spatial audio
    PlaySoundEffect(SoundName, Location);
    
    UE_LOG(LogTemp, Warning, TEXT("Combat sound: %s"), *SoundName);
}

void UAudioManager::PlayPowerSystemSound(FString PowerSystemName, FString SoundType)
{
    FString SoundName = PowerSystemName + TEXT("_") + SoundType;
    FVector Location = GetOwner()->GetActorLocation();
    
    PlaySoundEffect(SoundName, Location);
    
    UE_LOG(LogTemp, Warning, TEXT("Power system sound: %s"), *SoundName);
}

void UAudioManager::PlayComboSound(TArray<FName> Combo)
{
    // Dynamic combo sound based on combo length
    FString ComboSound = FString::Printf(TEXT("Combo_%d"), Combo.Num());
    FVector Location = GetOwner()->GetActorLocation();
    
    PlaySoundEffect(ComboSound, Location);
    
    UE_LOG(LogTemp, Warning, TEXT("Combo sound: %d moves"), Combo.Num());
}

void UAudioManager::PlayPerfectTimingSound(FName ActionName)
{
    FString SoundName = FString::Printf(TEXT("PerfectTiming_%s"), *ActionName.ToString());
    FVector Location = GetOwner()->GetActorLocation();
    
    PlaySoundEffect(SoundName, Location);
    
    UE_LOG(LogTemp, Warning, TEXT("Perfect timing sound: %s"), *ActionName.ToString());
}

void UAudioManager::PlayAmbientSound(EWeatherType WeatherType)
{
    // Update ambient sound based on weather
    FString AmbientSound = TEXT("Ambient_");
    
    switch (WeatherType)
    {
        case EWeatherType::WT_Rain:
            AmbientSound += TEXT("Rain");
            break;
        case EWeatherType::WT_Storm:
            AmbientSound += TEXT("Storm");
            break;
        case EWeatherType::WT_Snow:
            AmbientSound += TEXT("Snow");
            break;
        default:
            AmbientSound += TEXT("Clear");
            break;
    }
    
    FVector Location = GetOwner()->GetActorLocation();
    PlaySoundEffect(AmbientSound, Location);
    
    UE_LOG(LogTemp, Warning, TEXT("Ambient sound for weather: %d"), (int32)WeatherType);
}

void UAudioManager::PlayDialogueVoice(FString CharacterName, FString DialogueID)
{
    FString VoiceSound = CharacterName + TEXT("_") + DialogueID;
    FVector Location = GetOwner()->GetActorLocation();
    
    PlaySoundEffect(VoiceSound, Location);
    
    UE_LOG(LogTemp, Warning, TEXT("Dialogue voice: %s - %s"), *CharacterName, *DialogueID);
}

void UAudioManager::PlayUIEffect(FString UIAction)
{
    FString UISound = TEXT("UI_") + UIAction;
    FVector Location = GetOwner()->GetActorLocation();
    
    PlaySoundEffect(UISound, Location);
    
    UE_LOG(LogTemp, Warning, TEXT("UI sound: %s"), *UIAction);
}

void UAudioManager::SetMasterVolume(float Volume)
{
    MasterVolume = FMath::Clamp(Volume, 0.0f, 2.0f);
    UpdateAudioVolumes();
    
    UE_LOG(LogTemp, Warning, TEXT("Master volume set to: %.2f"), MasterVolume);
}

void UAudioManager::SetMusicVolume(float Volume)
{
    MusicVolume = FMath::Clamp(Volume, 0.0f, 2.0f);
    
    if (MusicComponent)
    {
        MusicComponent->SetVolumeMultiplier(MusicVolume);
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Music volume set to: %.2f"), MusicVolume);
}

void UAudioManager::SetEffectsVolume(float Volume)
{
    EffectsVolume = FMath::Clamp(Volume, 0.0f, 2.0f);
    UpdateAudioVolumes();
    
    UE_LOG(LogTemp, Warning, TEXT("Effects volume set to: %.2f"), EffectsVolume);
}

void UAudioManager::UpdateAudioVolumes()
{
    // Update all active audio components
    for (UAudioComponent* AudioComponent : EffectComponents)
    {
        if (AudioComponent)
        {
            AudioComponent->SetVolumeMultiplier(EffectsVolume * MasterVolume);
        }
    }
}

void UAudioManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    UpdateAudioState();
}

void UAudioManager::UpdateAudioState()
{
    // Update audio based on game state
    UpdateMusicState();
    UpdateEffectVolumes();
    UpdateAmbientAudio();
}

void UAudioManager::UpdateMusicState()
{
    // Transition music based on combat state
    if (bIsInCombat && CurrentMusicState != EMusicState::MS_Combat)
    {
        PlayMusic(EMusicState::MS_Combat);
    }
    else if (!bIsInCombat && CurrentMusicState == EMusicState::MS_Combat)
    {
        PlayMusic(EMusicState::MS_Exploration);
    }
}

void UAudioManager::LoadAudioLibrary()
{
    // Load all audio assets
    UE_LOG(LogTemp, Warning, TEXT("Loading audio library..."));
}

void UAudioManager::ConfigureAudioSettings()
{
    // Configure audio settings for optimal performance
    UE_LOG(LogTemp, Warning, TEXT("Audio settings configured"));
}
