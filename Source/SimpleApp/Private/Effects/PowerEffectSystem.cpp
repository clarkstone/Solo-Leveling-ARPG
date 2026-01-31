#include "PowerEffectSystem.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "GameFramework/Character.h"

UPowerEffectSystem::UPowerEffectSystem()
{
    bEnableVisualEffects = true;
    bEnableSoundEffects = true;
    EffectVolume = 1.0f;
    MaxActiveEffectsCount = 50;
    LastUpdateTime = 0.0f;
    bIsOptimized = false;
}

void UPowerEffectSystem::BeginPlay()
{
    Super::BeginPlay();
    Initialize();
}

void UPowerEffectSystem::Initialize()
{
    InitializeEffectLibrary();
    LoadEffectLibrary();
    ConfigureEffectSettings();
    
    UE_LOG(LogTemp, Warning, TEXT("Power Effect System initialized"));
}

void UPowerEffectSystem::InitializeEffectLibrary()
{
    // Initialize basic effects
    FEffectData AttackEffect;
    AttackEffect.EffectType = EEffectType::ET_Attack;
    AttackEffect.EffectDuration = 1.0f;
    AttackEffect.EffectIntensity = 1.0f;
    AttackEffect.EffectColor = FLinearColor::White;
    EffectLibrary.Add(EEffectType::ET_Attack, AttackEffect);
    
    FEffectData ComboEffect;
    ComboEffect.EffectType = EEffectType::ET_Combo;
    ComboEffect.EffectDuration = 2.0f;
    ComboEffect.EffectIntensity = 1.5f;
    ComboEffect.EffectColor = FLinearColor::Yellow;
    EffectLibrary.Add(EEffectType::ET_Combo, ComboEffect);
    
    FEffectData PerfectTimingEffect;
    PerfectTimingEffect.EffectType = EEffectType::ET_PerfectTiming;
    PerfectTimingEffect.EffectDuration = 1.5f;
    PerfectTimingEffect.EffectIntensity = 2.0f;
    PerfectTimingEffect.EffectColor = FLinearColor::Blue;
    EffectLibrary.Add(EEffectType::ET_PerfectTiming, PerfectTimingEffect);
    
    UE_LOG(LogTemp, Warning, TEXT("Effect library initialized"));
}

void UPowerEffectSystem::PlayEffect(EEffectType EffectType, FVector Location, FRotator Rotation)
{
    if (!bEnableVisualEffects && !bEnableSoundEffects)
        return;
    
    if (EffectLibrary.Contains(EffectType))
    {
        FEffectData EffectData = EffectLibrary[EffectType];
        
        // Create visual effects
        if (bEnableVisualEffects)
        {
            if (EffectData.NiagaraEffect)
            {
                CreateNiagaraEffect(EffectData, Location, Rotation);
            }
            
            if (EffectData.ParticleEffect)
            {
                CreateParticleEffect(EffectData, Location, Rotation);
            }
        }
        
        // Create sound effects
        if (bEnableSoundEffects && EffectData.SoundEffect)
        {
            CreateAudioEffect(EffectData, Location);
        }
        
        UE_LOG(LogTemp, Warning, TEXT("Playing effect type: %d"), (int32)EffectType);
    }
}

void UPowerEffectSystem::PlayAttackEffect(FVector ImpactLocation, bool bIsCritical)
{
    EEffectType EffectType = bIsCritical ? EEffectType::ET_PerfectTiming : EEffectType::ET_Attack;
    
    if (bIsCritical)
    {
        // Enhanced effect for critical hits
        PlayEffect(EffectType, ImpactLocation, FRotator::ZeroRotator);
        ShowDamageNumber(ImpactLocation, 0.0f, true);
    }
    else
    {
        PlayEffect(EffectType, ImpactLocation, FRotator::ZeroRotator);
    }
}

void UPowerEffectSystem::PlayComboEffect(FVector Location, TArray<FName> Combo)
{
    // Enhanced effect for combos
    FEffectData ComboEffect;
    ComboEffect.EffectType = EEffectType::ET_Combo;
    ComboEffect.EffectDuration = 2.0f;
    ComboEffect.EffectIntensity = Combo.Num() * 0.5f;
    ComboEffect.EffectColor = FLinearColor::Yellow;
    
    PlayEffect(EEffectType::ET_Combo, Location, FRotator::ZeroRotator);
    
    UE_LOG(LogTemp, Warning, TEXT("Combo effect played with %d moves"), Combo.Num());
}

void UPowerEffectSystem::PlayPerfectTimingEffect(FName ActionName, FVector Location)
{
    // Special effect for perfect timing
    PlayEffect(EEffectType::ET_PerfectTiming, Location, FRotator::ZeroRotator);
    
    UE_LOG(LogTemp, Warning, TEXT("Perfect timing effect for: %s"), *ActionName.ToString());
}

void UPowerEffectSystem::PlayShadowStepEffect(FVector StartLocation, FVector EndLocation)
{
    // Shadow step effect - create trail between locations
    PlayEffect(EEffectType::ET_ShadowSummon, StartLocation, FRotator::ZeroRotator);
    PlayEffect(EEffectType::ET_ShadowSummon, EndLocation, FRotator::ZeroRotator);
    
    UE_LOG(LogTemp, Warning, TEXT("Shadow step effect from %s to %s"), *StartLocation.ToString(), *EndLocation.ToString());
}

void UPowerEffectSystem::PlayUltimateEffect(FVector CenterLocation)
{
    // Ultimate ability effect - large, spectacular
    FEffectData UltimateEffect;
    UltimateEffect.EffectType = EEffectType::ET_Ultimate;
    UltimateEffect.EffectDuration = 5.0f;
    UltimateEffect.EffectIntensity = 3.0f;
    UltimateEffect.EffectColor = FLinearColor::Red;
    
    PlayEffect(EEffectType::ET_Ultimate, CenterLocation, FRotator::ZeroRotator);
    
    UE_LOG(LogTemp, Warning, TEXT("Ultimate effect at center: %s"), *CenterLocation.ToString());
}

UNiagaraComponent* UPowerEffectSystem::CreateNiagaraEffect(FEffectData& EffectData, FVector Location, FRotator Rotation)
{
    if (!EffectData.NiagaraEffect)
        return nullptr;
    
    UNiagaraComponent* NiagaraComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(
        EffectData.NiagaraEffect,
        GetOwner(),
        NAME_None,
        Location,
        Rotation,
        EAttachLocation::KeepWorldPosition,
        true
    );
    
    if (NiagaraComponent)
    {
        NiagaraComponent->SetFloatParameter(TEXT("Intensity"), EffectData.EffectIntensity);
        NiagaraComponent->SetVectorParameter(TEXT("EffectColor"), FVector(EffectData.EffectColor));
        NiagaraComponent->Activate();
        
        ActiveNiagaraEffects.Add(NiagaraComponent);
        
        // Schedule cleanup
        FTimerHandle EffectTimer;
        GetWorld()->GetTimerManager().SetTimer(EffectTimer, [NiagaraComponent]()
        {
            if (NiagaraComponent)
            {
                NiagaraComponent->Deactivate();
                NiagaraComponent->DestroyComponent();
            }
        }, EffectData.EffectDuration, false);
    }
    
    return NiagaraComponent;
}

void UPowerEffectSystem::SetEffectVolume(float Volume)
{
    EffectVolume = FMath::Clamp(Volume, 0.0f, 2.0f);
    
    // Update all active audio components
    for (UAudioComponent* AudioComponent : ActiveAudioComponents)
    {
        if (AudioComponent)
        {
            AudioComponent->SetVolumeMultiplier(EffectVolume);
        }
    }
    
    UE_LOG(LogTemp, Warning, TEXT("Effect volume set to: %.2f"), EffectVolume);
}

void UPowerEffectSystem::OptimizeEffects()
{
    bIsOptimized = true;
    MaxActiveEffectsCount = 20; // Reduce for performance
    
    UE_LOG(LogTemp, Warning, TEXT("Effects optimized for performance"));
}

void UPowerEffectSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    UpdateActiveEffects();
    CleanupExpiredEffects();
}

void UPowerEffectSystem::UpdateActiveEffects()
{
    // Update all active effects
    for (UNiagaraComponent* NiagaraComponent : ActiveNiagaraEffects)
    {
        if (NiagaraComponent && NiagaraComponent->IsActive())
        {
            // Update effect parameters based on game state
        }
    }
}

void UPowerEffectSystem::CleanupExpiredEffects()
{
    // Clean up expired effects
    for (int32 i = ActiveNiagaraEffects.Num() - 1; i >= 0; i--)
    {
        if (UNiagaraComponent* NiagaraComponent = ActiveNiagaraEffects[i])
        {
            if (!NiagaraComponent->IsActive())
            {
                ActiveNiagaraEffects.RemoveAt(i);
                NiagaraComponent->DestroyComponent();
            }
        }
    }
    
    for (int32 i = ActiveParticleEffects.Num() - 1; i >= 0; i--)
    {
        if (UParticleSystemComponent* ParticleComponent = ActiveParticleEffects[i])
        {
            if (!ParticleComponent->IsActive())
            {
                ActiveParticleEffects.RemoveAt(i);
                ParticleComponent->DestroyComponent();
            }
        }
    }
}
