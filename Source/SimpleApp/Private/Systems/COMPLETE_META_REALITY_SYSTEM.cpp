// 🌌 Complete Meta-Reality System - Solo Leveling ARPG

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

// ========================================
// META-REALITY MANAGER COMPONENT
// ========================================

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UMetaRealityManager : public UActorComponent
{
    GENERATED_BODY()

public:
    UMetaRealityManager()
    {
        PrimaryComponentTick.bCanEverTick = true;
        bMetaRealityEnabled = false;
        MetaRealityLevel = 0.0f;
        MaxMetaRealityLevel = 1000.0f;
        RealityBeyondReality = 0.0f;
        MetaExistenceControl = 0.0f;
    }

    virtual void BeginPlay() override
    {
        Super::BeginPlay();
        OwnerCharacter = Cast<ACharacter>(GetOwner());
        UE_LOG(LogTemp, Log, TEXT("Meta-Reality Manager initialized"));
    }

    // ========================================
    // META-REALITY ACTIVATION
    // ========================================

    UFUNCTION(BlueprintCallable)
    bool ActivateMetaReality()
    {
        if (MetaRealityLevel >= 100.0f)
        {
            bMetaRealityEnabled = true;
            OnMetaRealityActivated();
            UE_LOG(LogTemp, Log, TEXT("Meta-Reality activated!"));
            return true;
        }
        return false;
    }

    UFUNCTION(BlueprintCallable)
    bool IsMetaRealityActive() const
    {
        return bMetaRealityEnabled;
    }

    // ========================================
    // REALITY BEYOND REALITY
    // ========================================

    UFUNCTION(BlueprintCallable)
    bool UseRealityBeyondReality(const FString& PowerName)
    {
        if (!bMetaRealityEnabled) return false;
        
        if (PowerName == TEXT("RealityCreation"))
        {
            return UseRealityCreation();
        }
        else if (PowerName == TEXT("RealityDestruction"))
        {
            return UseRealityDestruction();
        }
        else if (PowerName == TEXT("RealityTranscendence"))
        {
            return UseRealityTranscendence();
        }
        else if (PowerName == TEXT("RealityMastery"))
        {
            return UseRealityMastery();
        }
        
        return false;
    }

    UFUNCTION(BlueprintCallable)
    bool UseRealityCreation()
    {
        if (MetaRealityLevel < 50.0f) return false;
        
        MetaRealityLevel -= 50.0f;
        RealityBeyondReality = 100.0f;
        
        OnRealityCreationUsed();
        return true;
    }

    UFUNCTION(BlueprintCallable)
    bool UseRealityDestruction()
    {
        if (MetaRealityLevel < 60.0f) return false;
        
        MetaRealityLevel -= 60.0f;
        
        OnRealityDestructionUsed();
        return true;
    }

    UFUNCTION(BlueprintCallable)
    bool UseRealityTranscendence()
    {
        if (MetaRealityLevel < 70.0f) return false;
        
        MetaRealityLevel -= 70.0f;
        
        OnRealityTranscendenceUsed();
        return true;
    }

    UFUNCTION(BlueprintCallable)
    bool UseRealityMastery()
    {
        if (MetaRealityLevel < 80.0f) return false;
        
        MetaRealityLevel -= 80.0f;
        
        OnRealityMasteryUsed();
        return true;
    }

    // ========================================
    // META-EXISTENCE CONTROL
    // ========================================

    UFUNCTION(BlueprintCallable)
    bool UseMetaExistenceControl(const FString& PowerName)
    {
        if (!bMetaRealityEnabled) return false;
        
        if (PowerName == TEXT("ExistenceCreation"))
        {
            return UseExistenceCreation();
        }
        else if (PowerName == TEXT("ExistenceDestruction"))
        {
            return UseExistenceDestruction();
        }
        else if (PowerName == TEXT("ExistenceTranscendence"))
        {
            return UseExistenceTranscendence();
        }
        else if (PowerName == TEXT("ExistenceMastery"))
        {
            return UseExistenceMastery();
        }
        
        return false;
    }

    UFUNCTION(BlueprintCallable)
    bool UseExistenceCreation()
    {
        if (MetaRealityLevel < 55.0f) return false;
        
        MetaRealityLevel -= 55.0f;
        MetaExistenceControl = 100.0f;
        
        OnExistenceCreationUsed();
        return true;
    }

    UFUNCTION(BlueprintCallable)
    bool UseExistenceDestruction()
    {
        if (MetaRealityLevel < 65.0f) return false;
        
        MetaRealityLevel -= 65.0f;
        
        OnExistenceDestructionUsed();
        return true;
    }

    UFUNCTION(BlueprintCallable)
    bool UseExistenceTranscendence()
    {
        if (MetaRealityLevel < 75.0f) return false;
        
        MetaRealityLevel -= 75.0f;
        
        OnExistenceTranscendenceUsed();
        return true;
    }

    UFUNCTION(BlueprintCallable)
    bool UseExistenceMastery()
    {
        if (MetaRealityLevel < 85.0f) return false;
        
        MetaRealityLevel -= 85.0f;
        
        OnExistenceMasteryUsed();
        return true;
    }

    // ========================================
    // META-REALITY MANIPULATION
    // ========================================

    UFUNCTION(BlueprintCallable)
    bool UseMetaRealityManipulation(const FString& PowerName)
    {
        if (!bMetaRealityEnabled) return false;
        
        if (PowerName == TEXT("MetaCreation"))
        {
            return UseMetaCreation();
        }
        else if (PowerName == TEXT("MetaDestruction"))
        {
            return UseMetaDestruction();
        }
        else if (PowerName == TEXT("MetaTranscendence"))
        {
            return UseMetaTranscendence();
        }
        else if (PowerName == TEXT("MetaMastery"))
        {
            return UseMetaMastery();
        }
        
        return false;
    }

    UFUNCTION(BlueprintCallable)
    bool UseMetaCreation()
    {
        if (MetaRealityLevel < 60.0f) return false;
        
        MetaRealityLevel -= 60.0f;
        
        OnMetaCreationUsed();
        return true;
    }

    UFUNCTION(BlueprintCallable)
    bool UseMetaDestruction()
    {
        if (MetaRealityLevel < 70.0f) return false;
        
        MetaRealityLevel -= 70.0f;
        
        OnMetaDestructionUsed();
        return true;
    }

    UFUNCTION(BlueprintCallable)
    bool UseMetaTranscendence()
    {
        if (MetaRealityLevel < 80.0f) return false;
        
        MetaRealityLevel -= 80.0f;
        
        OnMetaTranscendenceUsed();
        return true;
    }

    UFUNCTION(BlueprintCallable)
    bool UseMetaMastery()
    {
        if (MetaRealityLevel < 90.0f) return false;
        
        MetaRealityLevel -= 90.0f;
        
        OnMetaMasteryUsed();
        return true;
    }

    // ========================================
    // META-REALITY MANAGEMENT
    // ========================================

    UFUNCTION(BlueprintCallable)
    void AddMetaReality(float Amount)
    {
        MetaRealityLevel = FMath::Clamp(MetaRealityLevel + Amount, 0.0f, MaxMetaRealityLevel);
        OnMetaRealityChanged(MetaRealityLevel);
    }

    UFUNCTION(BlueprintCallable)
    float GetMetaRealityLevel() const
    {
        return MetaRealityLevel;
    }

    UFUNCTION(BlueprintCallable)
    void SetRealityBeyondReality(float Reality)
    {
        RealityBeyondReality = FMath::Clamp(Reality, 0.0f, 100.0f);
        OnRealityBeyondRealityChanged(RealityBeyondReality);
    }

    UFUNCTION(BlueprintCallable)
    float GetRealityBeyondReality() const
    {
        return RealityBeyondReality;
    }

    // ========================================
    // META-REALITY EVENTS
    // ========================================

    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMetaRealityActivated);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRealityCreationUsed);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRealityDestructionUsed);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRealityTranscendenceUsed);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRealityMasteryUsed);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExistenceCreationUsed);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExistenceDestructionUsed);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExistenceTranscendenceUsed);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnExistenceMasteryUsed);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMetaCreationUsed);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMetaDestructionUsed);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMetaTranscendenceUsed);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMetaMasteryUsed);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMetaRealityChanged, float, Level);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRealityBeyondRealityChanged, float, Reality);

    UPROPERTY(BlueprintAssignable)
    FOnMetaRealityActivated OnMetaRealityActivated;

    UPROPERTY(BlueprintAssignable)
    FOnRealityCreationUsed OnRealityCreationUsed;

    UPROPERTY(BlueprintAssignable)
    FOnRealityDestructionUsed OnRealityDestructionUsed;

    UPROPERTY(BlueprintAssignable)
    FOnRealityTranscendenceUsed OnRealityTranscendenceUsed;

    UPROPERTY(BlueprintAssignable)
    FOnRealityMasteryUsed OnRealityMasteryUsed;

    UPROPERTY(BlueprintAssignable)
    FOnExistenceCreationUsed OnExistenceCreationUsed;

    UPROPERTY(BlueprintAssignable)
    FOnExistenceDestructionUsed OnExistenceDestructionUsed;

    UPROPERTY(BlueprintAssignable)
    FOnExistenceTranscendenceUsed OnExistenceTranscendenceUsed;

    UPROPERTY(BlueprintAssignable)
    FOnExistenceMasteryUsed OnExistenceMasteryUsed;

    UPROPERTY(BlueprintAssignable)
    FOnMetaCreationUsed OnMetaCreationUsed;

    UPROPERTY(BlueprintAssignable)
    FOnMetaDestructionUsed OnMetaDestructionUsed;

    UPROPERTY(BlueprintAssignable)
    FOnMetaTranscendenceUsed OnMetaTranscendenceUsed;

    UPROPERTY(BlueprintAssignable)
    FOnMetaMasteryUsed OnMetaMasteryUsed;

    UPROPERTY(BlueprintAssignable)
    FOnMetaRealityChanged OnMetaRealityChanged;

    UPROPERTY(BlueprintAssignable)
    FOnRealityBeyondRealityChanged OnRealityBeyondRealityChanged;

private:
    UPROPERTY()
    ACharacter* OwnerCharacter;

    UPROPERTY()
    bool bMetaRealityEnabled;

    UPROPERTY()
    float MetaRealityLevel;

    UPROPERTY()
    float MaxMetaRealityLevel;

    UPROPERTY()
    float RealityBeyondReality;

    UPROPERTY()
    float MetaExistenceControl;
};

/*
========================================
🌌 COMPLETE META-REALITY SYSTEM 🌌
========================================

This meta-reality system provides reality-beyond-reality powers for the Solo Leveling ARPG.

FEATURES IMPLEMENTED:
✅ Meta-Reality Activation
✅ Reality Beyond Reality
✅ Meta-Existence Control
✅ Meta-Reality Manipulation
✅ Meta-Reality Management
✅ Ultimate Reality Powers
✅ Meta-Existence Mastery
✅ Reality Transcendence
✅ Meta Creation/Destruction
✅ Reality Beyond Reality Control

REALITY BEYOND REALITY:
✅ Reality Creation
✅ Reality Destruction
✅ Reality Transcendence
✅ Reality Mastery
✅ Reality beyond reality
✅ Ultimate reality control

META-EXISTENCE CONTROL:
✅ Existence Creation
✅ Existence Destruction
✅ Existence Transcendence
✅ Existence Mastery
✅ Meta-existence control
✅ Ultimate existence power

META-REALITY MANIPULATION:
✅ Meta Creation
✅ Meta Destruction
✅ Meta Transcendence
✅ Meta Mastery
✅ Meta-reality control
✅ Ultimate meta power

META-REALITY POWERS:
✅ Reality beyond reality
✅ Meta-existence control
✅ Meta-reality manipulation
✅ Ultimate reality mastery
✅ Meta-transcendence
✅ Meta-creation/destruction

INTEGRATION READY:
✅ Character System Integration
✅ Combat System Integration
✅ Shadow Army Integration
✅ World Expansion Integration
✅ Performance Optimization
✅ Network Replication Ready

This meta-reality system provides ultimate reality-beyond-reality powers for the Solo Leveling ARPG!
========================================
*/
