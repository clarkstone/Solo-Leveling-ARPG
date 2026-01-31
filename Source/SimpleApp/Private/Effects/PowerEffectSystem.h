#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"
#include "PowerEffectSystem.generated.h"

UENUM(BlueprintType)
enum class EEffectType : uint8
{
    ET_Attack,
    ET_HeavyAttack,
    ET_Combo,
    ET_PerfectTiming,
    ET_PowerActivation,
    ET_ShadowSummon,
    ET_Environmental,
    ET_Ultimate
};

USTRUCT(BlueprintType)
struct FEffectData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    EEffectType EffectType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UNiagaraSystem* NiagaraEffect;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UParticleSystem* ParticleEffect;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class USoundBase* SoundEffect;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float EffectDuration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float EffectIntensity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FLinearColor EffectColor;
};

UCLASS()
class SIMPLEAPP_API UPowerEffectSystem : public UActorComponent
{
    GENERATED_BODY()

public:
    UPowerEffectSystem();

    // Effect Configuration
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
    TMap<EEffectType, FEffectData> EffectLibrary;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
    bool bEnableVisualEffects;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
    bool bEnableSoundEffects;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effects")
    float EffectVolume;

    // Active Effects
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Effects")
    TArray<class UNiagaraComponent*> ActiveNiagaraEffects;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Effects")
    TArray<class UParticleSystemComponent*> ActiveParticleEffects;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Effects")
    TArray<class UAudioComponent*> ActiveAudioComponents;

    // Override UActorComponent functions
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // Initialization
    UFUNCTION(BlueprintCallable, Category = "Effects")
    void Initialize();

    // Effect Management
    UFUNCTION(BlueprintCallable, Category = "Effects")
    void PlayEffect(EEffectType EffectType, FVector Location, FRotator Rotation);

    UFUNCTION(BlueprintCallable, Category = "Effects")
    void PlayEffectOnActor(EEffectType EffectType, AActor* TargetActor);

    UFUNCTION(BlueprintCallable, Category = "Effects")
    void StopEffect(EEffectType EffectType);

    UFUNCTION(BlueprintCallable, Category = "Effects")
    void StopAllEffects();

    // Power System Effects
    UFUNCTION(BlueprintCallable, Category = "Effects")
    void PlayPowerSystemEffect(FString PowerSystemName, FVector Location);

    UFUNCTION(BlueprintCallable, Category = "Effects")
    void PlayPowerComboEffect(TArray<FName> ComboSequence);

    UFUNCTION(BlueprintCallable, Category = "Effects")
    void PlayPerfectTimingEffect(FName ActionName, FVector Location);

    // Environmental Effects
    UFUNCTION(BlueprintCallable, Category = "Effects")
    void PlayWeatherEffect(EWeatherType WeatherType);

    UFUNCTION(BlueprintCallable, Category = "Effects")
    void PlaySeasonalEffect(ESeason Season);

    // Combat Effects
    UFUNCTION(BlueprintCallable, Category = "Effects")
    void PlayAttackEffect(FVector ImpactLocation, bool bIsCritical);

    UFUNCTION(BlueprintCallable, Category = "Effects")
    void PlayComboEffect(FVector Location, TArray<FName> Combo);

    UFUNCTION(BlueprintCallable, Category = "Effects")
    void PlayUltimateEffect(FVector CenterLocation);

    // Shadow Effects
    UFUNCTION(BlueprintCallable, Category = "Effects")
    void PlayShadowSummonEffect(FVector Location);

    UFUNCTION(BlueprintCallable, Category = "Effects")
    void PlayShadowStepEffect(FVector StartLocation, FVector EndLocation);

    // Effect Configuration
    UFUNCTION(BlueprintCallable, Category = "Effects")
    void SetEffectVolume(float Volume);

    UFUNCTION(BlueprintCallable, Category = "Effects")
    void SetEffectIntensity(EEffectType EffectType, float Intensity);

    // Performance
    UFUNCTION(BlueprintCallable, Category = "Effects")
    void OptimizeEffects();

    UFUNCTION(BlueprintCallable, Category = "Effects")
    void SetMaxActiveEffects(int32 MaxEffects);

protected:
    // Internal Effect Systems
    void InitializeEffectLibrary();
    void UpdateActiveEffects();
    void CleanupExpiredEffects();

    // Effect Creation
    UNiagaraComponent* CreateNiagaraEffect(FEffectData& EffectData, FVector Location, FRotator Rotation);
    UParticleSystemComponent* CreateParticleEffect(FEffectData& EffectData, FVector Location, FRotator Rotation);
    UAudioComponent* CreateAudioEffect(FEffectData& EffectData, FVector Location);

private:
    // Internal State
    int32 MaxActiveEffectsCount;
    float LastUpdateTime;
    bool bIsOptimized;

    // Effect Management
    TMap<EEffectType, TArray<class UActorComponent*>> ActiveEffectsByType;
    TMap<FString, FEffectData> PowerSystemEffects;

    // Helper Functions
    void LoadEffectLibrary();
    void ConfigureEffectSettings();
    void UpdateEffectPerformance();
};
