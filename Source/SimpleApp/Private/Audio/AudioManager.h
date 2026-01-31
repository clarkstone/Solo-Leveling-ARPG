#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"
#include "AudioManager.generated.h"

UENUM(BlueprintType)
enum class EAudioType : uint8
{
    AT_Music,
    AT_Ambient,
    AT_Effect,
    AT_Voice,
    AT_UI,
    AT_Story
};

UENUM(BlueprintType)
enum class EMusicState : uint8
{
    MS_Menu,
    MS_Exploration,
    MS_Combat,
    MS_Dungeon,
    MS_Boss,
    MS_Victory,
    MS_Defeat,
    MS_Cutscene
};

USTRUCT(BlueprintType)
struct FAudioData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class USoundBase* SoundAsset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EAudioType AudioType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Volume;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Pitch;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bLoop;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bSpatialized;
};

UCLASS()
class SIMPLEAPP_API UAudioManager : public UActorComponent
{
    GENERATED_BODY()

public:
    UAudioManager();

    // Audio Configuration
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    TMap<EAudioType, FAudioData> AudioLibrary;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    float MasterVolume;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    float MusicVolume;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    float EffectsVolume;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
    float VoiceVolume;

    // Audio Components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio")
    class UAudioComponent* MusicComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio")
    class UAudioComponent* AmbientComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio")
    TArray<class UAudioComponent*> EffectComponents;

    // Audio State
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio")
    EMusicState CurrentMusicState;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio")
    bool bIsInCombat;

    // Override UActorComponent functions
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Initialization
    UFUNCTION(BlueprintCallable, Category = "Audio")
    void Initialize();

    // Music Management
    UFUNCTION(BlueprintCallable, Category = "Audio")
    void PlayMusic(EMusicState MusicState);

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void StopMusic();

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void TransitionMusic(EMusicState NewState, float FadeDuration);

    // Sound Effects
    UFUNCTION(BlueprintCallable, Category = "Audio")
    void PlaySoundEffect(FString SoundName, FVector Location);

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void PlaySoundEffectAttached(FString SoundName, AActor* Actor);

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void PlayCombatSound(FString SoundName, FVector Location);

    // Power System Audio
    UFUNCTION(BlueprintCallable, Category = "Audio")
    void PlayPowerSystemSound(FString PowerSystemName, FString SoundType);

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void PlayComboSound(TArray<FName> Combo);

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void PlayPerfectTimingSound(FName ActionName);

    // Environmental Audio
    UFUNCTION(BlueprintCallable, Category = "Audio")
    void PlayAmbientSound(EWeatherType WeatherType);

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void PlayDungeonAmbient(int32 DungeonRank);

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void UpdateEnvironmentalAudio();

    // Voice Audio
    UFUNCTION(BlueprintCallable, Category = "Audio")
    void PlayDialogueVoice(FString CharacterName, FString DialogueID);

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void PlayCharacterVoice(FString CharacterName, FString VoiceType);

    // UI Audio
    UFUNCTION(BlueprintCallable, Category = "Audio")
    void PlayUIEffect(FString UIAction);

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void PlayNotificationSound();

    // Audio Configuration
    UFUNCTION(BlueprintCallable, Category = "Audio")
    void SetMasterVolume(float Volume);

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void SetMusicVolume(float Volume);

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void SetEffectsVolume(float Volume);

    UFUNCTION(BlueprintCallable, Category = "Audio")
    void SetVoiceVolume(float Volume);

    // Audio Events
    UPROPERTY(BlueprintAssignable, Category = "Audio Events")
    FOnMusicStateChanged OnMusicStateChanged;

    UPROPERTY(BlueprintAssignable, Category = "Audio Events")
    FOnSoundEffectPlayed OnSoundEffectPlayed;

protected:
    // Internal Audio Systems
    void InitializeAudioComponents();
    void InitializeAudioLibrary();
    void UpdateAudioState();

    // Audio Management
    void UpdateMusicState();
    void UpdateEffectVolumes();
    void UpdateAmbientAudio();

private:
    // Internal State
    float LastUpdateTime;
    bool bIsTransitioning;
    float TransitionTimer;
    EMusicState PreviousMusicState;

    // Audio Data
    TMap<FString, FAudioData> SoundEffects;
    TMap<EMusicState, FAudioData> MusicTracks;
    TMap<EWeatherType, FAudioData> AmbientSounds;

    // Helper Functions
    void LoadAudioLibrary();
    void ConfigureAudioSettings();
    void UpdateAudioVolumes();
};
