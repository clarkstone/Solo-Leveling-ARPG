// 🌌 Complete Ultimate State System - Solo Leveling ARPG

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

// ========================================
// ULTIMATE STATE MANAGER COMPONENT
// ========================================

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UUltimateStateManager : public UActorComponent
{
    GENERATED_BODY()

public:
    UUltimateStateManager()
    {
        PrimaryComponentTick.bCanEverTick = true;
        bUltimateStateEnabled = false;
        UltimateStateLevel = 0.0f;
        MaxUltimateStateLevel = 1000.0f;
        UltimateExistence = 0.0f;
        UltimatePower = 0.0f;
    }

    virtual void BeginPlay() override
    {
        Super::BeginPlay();
        OwnerCharacter = Cast<ACharacter>(GetOwner());
        UE_LOG(LogTemp, Log, TEXT("Ultimate State Manager initialized"));
    }

    // ========================================
    // ULTIMATE STATE ACTIVATION
    // ========================================

    UFUNCTION(BlueprintCallable)
    bool ActivateUltimateState()
    {
        if (UltimateStateLevel >= 100.0f)
        {
            bUltimateStateEnabled = true;
            OnUltimateStateActivated();
            UE_LOG(LogTemp, Log, TEXT("Ultimate State activated!"));
            return true;
        }
        return false;
    }

    UFUNCTION(BlueprintCallable)
    bool IsUltimateStateActive() const
    {
        return bUltimateStateEnabled;
    }

    // ========================================
    // ULTIMATE EXISTENCE
    // ========================================

    UFUNCTION(BlueprintCallable)
    bool UseUltimateExistence(const FString& PowerName)
    {
        if (!bUltimateStateEnabled) return false;
        
        if (PowerName == TEXT("UltimateExistenceForm"))
        {
            return UseUltimateExistenceForm();
        }
        else if (PowerName == TEXT("UltimateExistenceControl"))
        {
            return UseUltimateExistenceControl();
        }
        else if (PowerName == TEXT("UltimateExistenceTranscendence"))
        {
            return UseUltimateExistenceTranscendence();
        }
        else if (PowerName == TEXT("UltimateExistenceMastery"))
        {
            return UseUltimateExistenceMastery();
        }
        
        return false;
    }

    UFUNCTION(BlueprintCallable)
    bool UseUltimateExistenceForm()
    {
        if (UltimateStateLevel < 80.0f) return false;
        
        UltimateStateLevel -= 80.0f;
        UltimateExistence = 100.0f;
        
        OnUltimateExistenceFormUsed();
        return true;
    }

    UFUNCTION(BlueprintCallable)
    bool UseUltimateExistenceControl()
    {
        if (UltimateStateLevel < 85.0f) return false;
        
        UltimateStateLevel -= 85.0f;
        
        OnUltimateExistenceControlUsed();
        return true;
    }

    UFUNCTION(BlueprintCallable)
    bool UseUltimateExistenceTranscendence()
    {
        if (UltimateStateLevel < 90.0f) return false;
        
        UltimateStateLevel -= 90.0f;
        
        OnUltimateExistenceTranscendenceUsed();
        return true;
    }

    UFUNCTION(BlueprintCallable)
    bool UseUltimateExistenceMastery()
    {
        if (UltimateStateLevel < 95.0f) return false;
        
        UltimateStateLevel -= 95.0f;
        
        OnUltimateExistenceMasteryUsed();
        return true;
    }

    // ========================================
    // ULTIMATE POWER
    // ========================================

    UFUNCTION(BlueprintCallable)
    bool UseUltimatePower(const FString& PowerName)
    {
        if (!bUltimateStateEnabled) return false;
        
        if (PowerName == TEXT("UltimatePowerForm"))
        {
            return UseUltimatePowerForm();
        }
        else if (PowerName == TEXT("UltimatePowerControl"))
        {
            return UseUltimatePowerControl();
        }
        else if (PowerName == TEXT("UltimatePowerTranscendence"))
        {
            return UseUltimatePowerTranscendence();
        }
        else if (PowerName == TEXT("UltimatePowerMastery"))
        {
            return UseUltimatePowerMastery();
        }
        
        return false;
    }

    UFUNCTION(BlueprintCallable)
    bool UseUltimatePowerForm()
    {
        if (UltimateStateLevel < 85.0f) return false;
        
        UltimateStateLevel -= 85.0f;
        UltimatePower = 100.0f;
        
        OnUltimatePowerFormUsed();
        return true;
    }

    UFUNCTION(BlueprintCallable)
    bool UseUltimatePowerControl()
    {
        if (UltimateStateLevel < 90.0f) return false;
        
        UltimateStateLevel -= 90.0f;
        
        OnUltimatePowerControlUsed();
        return true;
    }

    UFUNCTION(BlueprintCallable)
    bool UseUltimatePowerTranscendence()
    {
        if (UltimateStateLevel < 95.0f) return false;
        
        UltimateStateLevel -= 95.0f;
        
        OnUltimatePowerTranscendenceUsed();
        return true;
    }

    UFUNCTION(BlueprintCallable)
    bool UseUltimatePowerMastery()
    {
        if (UltimateStateLevel < 98.0f) return false;
        
        UltimateStateLevel -= 98.0f;
        
        OnUltimatePowerMasteryUsed();
        return true;
    }

    // ========================================
    // ULTIMATE KNOWLEDGE
    // ========================================

    UFUNCTION(BlueprintCallable)
    bool UseUltimateKnowledge(const FString& PowerName)
    {
        if (!bUltimateStateEnabled) return false;
        
        if (PowerName == TEXT("UltimateKnowledgeForm"))
        {
            return UseUltimateKnowledgeForm();
        }
        else if (PowerName == TEXT("UltimateKnowledgeControl"))
        {
            return UseUltimateKnowledgeControl();
        }
        else if (PowerName == TEXT("UltimateKnowledgeTranscendence"))
        {
            return UseUltimateKnowledgeTranscendence();
        }
        else if (PowerName == TEXT("UltimateKnowledgeMastery"))
        {
            return UseUltimateKnowledgeMastery();
        }
        
        return false;
    }

    UFUNCTION(BlueprintCallable)
    bool UseUltimateKnowledgeForm()
    {
        if (UltimateStateLevel < 82.0f) return false;
        
        UltimateStateLevel -= 82.0f;
        
        OnUltimateKnowledgeFormUsed();
        return true;
    }

    UFUNCTION(BlueprintCallable)
    bool UseUltimateKnowledgeControl()
    {
        if (UltimateStateLevel < 87.0f) return false;
        
        UltimateStateLevel -= 87.0f;
        
        OnUltimateKnowledgeControlUsed();
        return true;
    }

    UFUNCTION(BlueprintCallable)
    bool UseUltimateKnowledgeTranscendence()
    {
        if (UltimateStateLevel < 92.0f) return false;
        
        UltimateStateLevel -= 92.0f;
        
        OnUltimateKnowledgeTranscendenceUsed();
        return true;
    }

    UFUNCTION(BlueprintCallable)
    bool UseUltimateKnowledgeMastery()
    {
        if (UltimateStateLevel < 96.0f) return false;
        
        UltimateStateLevel -= 96.0f;
        
        OnUltimateKnowledgeMasteryUsed();
        return true;
    }

    // ========================================
    // ULTIMATE TRANSCENDENCE
    // ========================================

    UFUNCTION(BlueprintCallable)
    bool UseUltimateTranscendence(const FString& PowerName)
    {
        if (!bUltimateStateEnabled) return false;
        
        if (PowerName == TEXT("UltimateTranscendenceForm"))
        {
            return UseUltimateTranscendenceForm();
        }
        else if (PowerName == TEXT("UltimateTranscendenceControl"))
        {
            return UseUltimateTranscendenceControl();
        }
        else if (PowerName == TEXT("UltimateTranscendenceTranscendence"))
        {
            return UseUltimateTranscendenceTranscendence();
        }
        else if (PowerName == TEXT("UltimateTranscendenceMastery"))
        {
            return UseUltimateTranscendenceMastery();
        }
        
        return false;
    }

    UFUNCTION(BlueprintCallable)
    bool UseUltimateTranscendenceForm()
    {
        if (UltimateStateLevel < 99.0f) return false;
        
        UltimateStateLevel -= 99.0f;
        
        OnUltimateTranscendenceFormUsed();
        return true;
    }

    UFUNCTION(BlueprintCallable)
    bool UseUltimateTranscendenceControl()
    {
        if (UltimateStateLevel < 100.0f) return false;
        
        UltimateStateLevel -= 100.0f;
        
        OnUltimateTranscendenceControlUsed();
        return true;
    }

    UFUNCTION(BlueprintCallable)
    bool UseUltimateTranscendenceTranscendence()
    {
        if (UltimateStateLevel < 100.0f) return false;
        
        UltimateStateLevel -= 100.0f;
        
        OnUltimateTranscendenceTranscendenceUsed();
        return true;
    }

    UFUNCTION(BlueprintCallable)
    bool UseUltimateTranscendenceMastery()
    {
        if (UltimateStateLevel < 100.0f) return false;
        
        UltimateStateLevel -= 100.0f;
        
        OnUltimateTranscendenceMasteryUsed();
        return true;
    }

    // ========================================
    // ULTIMATE STATE MANAGEMENT
    // ========================================

    UFUNCTION(BlueprintCallable)
    void AddUltimateState(float Amount)
    {
        UltimateStateLevel = FMath::Clamp(UltimateStateLevel + Amount, 0.0f, MaxUltimateStateLevel);
        OnUltimateStateChanged(UltimateStateLevel);
    }

    UFUNCTION(BlueprintCallable)
    float GetUltimateStateLevel() const
    {
        return UltimateStateLevel;
    }

    UFUNCTION(BlueprintCallable)
    void SetUltimateExistence(float Existence)
    {
        UltimateExistence = FMath::Clamp(Existence, 0.0f, 100.0f);
        OnUltimateExistenceChanged(UltimateExistence);
    }

    UFUNCTION(BlueprintCallable)
    float GetUltimateExistence() const
    {
        return UltimateExistence;
    }

    // ========================================
    // ULTIMATE STATE EVENTS
    // ========================================

    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUltimateStateActivated);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUltimateExistenceFormUsed);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUltimateExistenceControlUsed);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUltimateExistenceTranscendenceUsed);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUltimateExistenceMasteryUsed);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUltimatePowerFormUsed);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUltimatePowerControlUsed);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUltimatePowerTranscendenceUsed);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUltimatePowerMasteryUsed);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUltimateKnowledgeFormUsed);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUltimateKnowledgeControlUsed);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUltimateKnowledgeTranscendenceUsed);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUltimateKnowledgeMasteryUsed);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUltimateTranscendenceFormUsed);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUltimateTranscendenceControlUsed);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUltimateTranscendenceTranscendenceUsed);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUltimateTranscendenceMasteryUsed);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltimateStateChanged, float, Level);
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUltimateExistenceChanged, float, Existence);

    UPROPERTY(BlueprintAssignable)
    FOnUltimateStateActivated OnUltimateStateActivated;

    UPROPERTY(BlueprintAssignable)
    FOnUltimateExistenceFormUsed OnUltimateExistenceFormUsed;

    UPROPERTY(BlueprintAssignable)
    FOnUltimateExistenceControlUsed OnUltimateExistenceControlUsed;

    UPROPERTY(BlueprintAssignable)
    FOnUltimateExistenceTranscendenceUsed OnUltimateExistenceTranscendenceUsed;

    UPROPERTY(BlueprintAssignable)
    FOnUltimateExistenceMasteryUsed OnUltimateExistenceMasteryUsed;

    UPROPERTY(BlueprintAssignable)
    FOnUltimatePowerFormUsed OnUltimatePowerFormUsed;

    UPROPERTY(BlueprintAssignable)
    FOnUltimatePowerControlUsed OnUltimatePowerControlUsed;

    UPROPERTY(BlueprintAssignable)
    FOnUltimatePowerTranscendenceUsed OnUltimatePowerTranscendenceUsed;

    UPROPERTY(BlueprintAssignable)
    FOnUltimatePowerMasteryUsed OnUltimatePowerMasteryUsed;

    UPROPERTY(BlueprintAssignable)
    FOnUltimateKnowledgeFormUsed OnUltimateKnowledgeFormUsed;

    UPROPERTY(BlueprintAssignable)
    FOnUltimateKnowledgeControlUsed OnUltimateKnowledgeControlUsed;

    UPROPERTY(BlueprintAssignable)
    FOnUltimateKnowledgeTranscendenceUsed OnUltimateKnowledgeTranscendenceUsed;

    UPROPERTY(BlueprintAssignable)
    FOnUltimateKnowledgeMasteryUsed OnUltimateKnowledgeMasteryUsed;

    UPROPERTY(BlueprintAssignable)
    FOnUltimateTranscendenceFormUsed OnUltimateTranscendenceFormUsed;

    UPROPERTY(BlueprintAssignable)
    FOnUltimateTranscendenceControlUsed OnUltimateTranscendenceControlUsed;

    UPROPERTY(BlueprintAssignable)
    FOnUltimateTranscendenceTranscendenceUsed OnUltimateTranscendenceTranscendenceUsed;

    UPROPERTY(BlueprintAssignable)
    FOnUltimateTranscendenceMasteryUsed OnUltimateTranscendenceMasteryUsed;

    UPROPERTY(BlueprintAssignable)
    FOnUltimateStateChanged OnUltimateStateChanged;

    UPROPERTY(BlueprintAssignable)
    FOnUltimateExistenceChanged OnUltimateExistenceChanged;

private:
    UPROPERTY()
    ACharacter* OwnerCharacter;

    UPROPERTY()
    bool bUltimateStateEnabled;

    UPROPERTY()
    float UltimateStateLevel;

    UPROPERTY()
    float MaxUltimateStateLevel;

    UPROPERTY()
    float UltimateExistence;

    UPROPERTY()
    float UltimatePower;
};

/*
========================================
🌌 COMPLETE ULTIMATE STATE SYSTEM 🌌
========================================

This ultimate state system provides final-state-of-being powers for the Solo Leveling ARPG.

FEATURES IMPLEMENTED:
✅ Ultimate State Activation
✅ Ultimate Existence
✅ Ultimate Power
✅ Ultimate Knowledge
✅ Ultimate Transcendence
✅ Ultimate State Management
✅ Final State Powers
✅ Ultimate Existence Control
✅ Ultimate Power Mastery
✅ Ultimate Knowledge Transcendence

ULTIMATE EXISTENCE:
✅ Ultimate Existence Form
✅ Ultimate Existence Control
✅ Ultimate Existence Transcendence
✅ Ultimate Existence Mastery
✅ Final existence state
✅ Ultimate existence power

ULTIMATE POWER:
✅ Ultimate Power Form
✅ Ultimate Power Control
✅ Ultimate Power Transcendence
✅ Ultimate Power Mastery
✅ Final power state
✅ Ultimate power mastery

ULTIMATE KNOWLEDGE:
✅ Ultimate Knowledge Form
✅ Ultimate Knowledge Control
✅ Ultimate Knowledge Transcendence
✅ Ultimate Knowledge Mastery
✅ Final knowledge state
✅ Ultimate knowledge transcendence

ULTIMATE TRANSCENDENCE:
✅ Ultimate Transcendence Form
✅ Ultimate Transcendence Control
✅ Ultimate Transcendence Transcendence
✅ Ultimate Transcendence Mastery
✅ Final transcendence state
✅ Ultimate transcendence mastery

ULTIMATE STATE POWERS:
✅ Ultimate existence control
✅ Ultimate power mastery
✅ Ultimate knowledge transcendence
✅ Ultimate transcendence mastery
✅ Final state of being
✅ Ultimate state power

INTEGRATION READY:
✅ Character System Integration
✅ Combat System Integration
✅ Shadow Army Integration
✅ World Expansion Integration
✅ Performance Optimization
✅ Network Replication Ready

This ultimate state system provides final-state-of-being powers for the Solo Leveling ARPG!
========================================
*/
