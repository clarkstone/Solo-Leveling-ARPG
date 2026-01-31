#include "NPC.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/SoloLevelingCharacter.h"

ANPC::ANPC()
{
    // Initialize NPC properties
    NPCType = ENPCType::NT_Villager;
    CurrentState = ENPCState::NS_Idle;
    NPCName = TEXT("NPC");
    NPCDescription = TEXT("A non-player character");
    
    // Initialize behavior properties
    bIsFriendly = true;
    bCanTrade = false;
    bCanTrain = false;
    bCanCraft = false;
    
    // Initialize dialogue properties
    bHasVoiceOver = false;
    
    // Initialize schedule properties
    WakeUpTime = 6.0f;
    SleepTime = 22.0f;
    WorkStartTime = 9.0f;
    WorkEndTime = 17.0f;
    
    // Initialize internal state
    LastUpdateTime = 0.0f;
    bIsInteracting = false;
    bIsWorking = false;
    bIsSleeping = false;
    CurrentPatrolIndex = 0;
    TargetLocation = FVector::ZeroVector;
    
    // Create AI Controller
    NPCController = CreateDefaultSubobject<AAIController>(TEXT("NPCController"));
}

void ANPC::BeginPlay()
{
    Super::BeginPlay();
    
    InitializeNPC();
    InitializeAI();
    SetupAIController();
    
    UE_LOG(LogTemp, Warning, TEXT("NPC initialized: %s"), *NPCName);
}

void ANPC::InitializeNPC()
{
    // Set home location to current position
    HomeLocation = GetActorLocation();
    
    // Initialize patrol points
    PatrolPoints.Add(HomeLocation + FVector(200.0f, 0.0f, 0.0f));
    PatrolPoints.Add(HomeLocation + FVector(0.0f, 200.0f, 0.0f));
    PatrolPoints.Add(HomeLocation + FVector(-200.0f, 0.0f, 0.0f));
    PatrolPoints.Add(HomeLocation + FVector(0.0f, -200.0f, 0.0f));
    
    UE_LOG(LogTemp, Warning, TEXT("NPC %s initialized with %d patrol points"), *NPCName, PatrolPoints.Num());
}

void ANPC::InitializeAI()
{
    // Configure AI based on NPC type
    switch (NPCType)
    {
        case ENPCType::NT_Merchant:
            bCanTrade = true;
            break;
        case ENPCType::NT_Trainer:
            bCanTrain = true;
            break;
        case ENPCType::NT_Blacksmith:
            bCanCraft = true;
            break;
        case ENPCType::NT_Alchemist:
            bCanCraft = true;
            break;
        case ENPCType::NT_Enchanter:
            bCanCraft = true;
            break;
        default:
            break;
    }
    
    UE_LOG(LogTemp, Warning, TEXT("NPC AI initialized for type: %d"), (int32)NPCType);
}

void ANPC::SetupAIController()
{
    if (NPCController)
    {
        // Set up behavior tree
        FString BehaviorTreePath = TEXT("/Game/AI/BehaviorTrees/BT_NPC.BT_NPC");
        UBehaviorTree* BehaviorTree = LoadObject<UBehaviorTree>(nullptr, *BehaviorTreePath);
        
        if (BehaviorTree)
        {
            NPCController->RunBehaviorTree(BehaviorTree);
        }
        
        // Set up blackboard
        UBlackboardComponent* Blackboard = NPCController->FindComponentByClass<UBlackboardComponent>();
        if (Blackboard)
        {
            Blackboard->SetValueAsEnum(TEXT("NPCState"), (uint8)CurrentState);
            Blackboard->SetValueAsVector(TEXT("HomeLocation"), HomeLocation);
            Blackboard->SetValueAsBool(TEXT("IsFriendly"), bIsFriendly);
        }
    }
}

void ANPC::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    
    UpdateAI();
    ProcessSchedule();
}

void ANPC::SetNPCState(ENPCState NewState)
{
    if (CurrentState != NewState)
    {
        ENPCState OldState = CurrentState;
        CurrentState = NewState;
        
        // Update AI controller
        if (NPCController)
        {
            UBlackboardComponent* Blackboard = NPCController->FindComponentByClass<UBlackboardComponent>();
            if (Blackboard)
            {
                Blackboard->SetValueAsEnum(TEXT("NPCState"), (uint8)NewState);
            }
        }
        
        OnNPCStateChanged.Broadcast(this, OldState, NewState);
        
        UE_LOG(LogTemp, Warning, TEXT("NPC %s state changed to: %d"), *NPCName, (int32)NewState);
    }
}

void ANPC::UpdateAI()
{
    // Update AI behavior based on current state
    switch (CurrentState)
    {
        case ENPCState::NS_Idle:
            HandleIdleState();
            break;
        case ENPCState::NS_Patrol:
            HandlePatrolState();
            break;
        case ENPCState::NS_Dialogue:
            HandleDialogueState();
            break;
        case ENPCState::NS_Working:
            HandleWorkingState();
            break;
        case ENPCState::NS_Sleeping:
            HandleSleepingState();
            break;
        case ENPCState::NS_Emergency:
            HandleEmergencyState();
            break;
    }
}

void ANPC::HandleIdleState()
{
    // Random idle behaviors
    if (FMath::FRand() < 0.1f)
    {
        // Start patrolling
        SetNPCState(ENPCState::NS_Patrol);
    }
}

void ANPC::HandlePatrolState()
{
    // Move along patrol path
    if (PatrolPoints.Num() > 0)
    {
        FVector NextPatrolPoint = PatrolPoints[CurrentPatrolIndex];
        
        // Move to patrol point
        MoveToTarget(NextPatrolPoint);
        
        // Check if reached patrol point
        float Distance = FVector::Dist(GetActorLocation(), NextPatrolPoint);
        if (Distance < 100.0f)
        {
            CurrentPatrolIndex = (CurrentPatrolIndex + 1) % PatrolPoints.Num();
        }
    }
}

void ANPC::HandleDialogueState()
{
    // Stay in place during dialogue
    if (NPCController)
    {
        NPCController->StopMovement();
    }
}

void ANPC::HandleWorkingState()
{
    // Work behavior based on NPC type
    switch (NPCType)
    {
        case ENPCType::NT_Merchant:
            // Merchant working behavior
            break;
        case ENPCType::NT_Blacksmith:
            // Blacksmith working behavior
            break;
        default:
            // Generic working behavior
            break;
    }
}

void ANPC::HandleSleepingState()
{
    // Sleep behavior
    if (NPCController)
    {
        NPCController->StopMovement();
    }
}

void ANPC::HandleEmergencyState()
{
    // Emergency response behavior
    UE_LOG(LogTemp, Warning, TEXT("NPC %s in emergency state"), *NPCName);
}

void ANPC::ProcessSchedule()
{
    // Get current time (simplified)
    float CurrentTime = GetWorld()->GetTimeSeconds() / 3600.0f; // Convert to hours
    CurrentTime = FMath::Fmod(CurrentTime, 24.0f);
    
    // Check schedule
    if (CurrentTime >= WakeUpTime && CurrentTime < WorkStartTime)
    {
        if (CurrentState != ENPCState::NS_Dialogue)
        {
            SetNPCState(ENPCState::NS_Idle);
        }
    }
    else if (CurrentTime >= WorkStartTime && CurrentTime < WorkEndTime)
    {
        if (CurrentState != ENPCState::NS_Dialogue)
        {
            SetNPCState(ENPCState::NS_Working);
        }
    }
    else if (CurrentTime >= SleepTime || CurrentTime < WakeUpTime)
    {
        if (CurrentState != ENPCState::NS_Dialogue)
        {
            SetNPCState(ENPCState::NS_Sleeping);
        }
    }
}

void ANPC::InteractWithPlayer(ASoloLevelingCharacter* Player)
{
    if (Player && !bIsInteracting)
    {
        bIsInteracting = true;
        
        // Start dialogue
        StartDialogue(TEXT("Greeting"));
        
        OnNPCInteracted.Broadcast(this, Player);
        
        UE_LOG(LogTemp, Warning, TEXT("NPC %s interacting with player"), *NPCName);
    }
}

void ANPC::StartDialogue(FString DialogueID)
{
    SetNPCState(ENPCState::NS_Dialogue);
    
    // Face the player
    if (ASoloLevelingCharacter* Player = Cast<ASoloLevelingCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn()))
    {
        FVector PlayerLocation = Player->GetActorLocation();
        FRotator LookAtRotation = (PlayerLocation - GetActorLocation()).Rotation();
        SetActorRotation(LookAtRotation);
    }
    
    UE_LOG(LogTemp, Warning, TEXT("NPC %s starting dialogue: %s"), *NPCName, *DialogueID);
}

void ANPC::EndDialogue()
{
    bIsInteracting = false;
    SetNPCState(ENPCState::NS_Idle);
    
    UE_LOG(LogTemp, Warning, TEXT("NPC %s ending dialogue"), *NPCName);
}

void ANPC::OpenShop()
{
    if (bCanTrade)
    {
        UE_LOG(LogTemp, Warning, TEXT("NPC %s opening shop"), *NPCName);
    }
}

void ANPC::OpenTrainingMenu()
{
    if (bCanTrain)
    {
        UE_LOG(LogTemp, Warning, TEXT("NPC %s opening training menu"), *NPCName);
    }
}

void ANPC::OpenCraftingMenu()
{
    if (bCanCraft)
    {
        UE_LOG(LogTemp, Warning, TEXT("NPC %s opening crafting menu"), *NPCName);
    }
}

void ANPC::OpenEnchantmentMenu()
{
    if (bCanCraft)
    {
        UE_LOG(LogTemp, Warning, TEXT("NPC %s opening enchantment menu"), *NPCName);
    }
}

void ANPC::Patrol()
{
    SetNPCState(ENPCState::NS_Patrol);
}

void ANPC::GoToLocation(FVector Location)
{
    TargetLocation = Location;
    MoveToTarget(Location);
}

void ANPC::ReturnHome()
{
    GoToLocation(HomeLocation);
}

void ANPC::MoveToTarget(FVector TargetLocation)
{
    if (NPCController)
    {
        // Use AI controller to move to target
        NPCController->MoveToLocation(TargetLocation);
    }
}

void ANPC::SetBehaviorFriendly()
{
    bIsFriendly = true;
    
    if (NPCController)
    {
        UBlackboardComponent* Blackboard = NPCController->FindComponentByClass<UBlackboardComponent>();
        if (Blackboard)
        {
            Blackboard->SetValueAsBool(TEXT("IsFriendly"), true);
        }
    }
}

void ANPC::SetBehaviorHostile()
{
    bIsFriendly = false;
    
    if (NPCController)
    {
        UBlackboardComponent* Blackboard = NPCController->FindComponentByClass<UBlackboardComponent>();
        if (Blackboard)
        {
            Blackboard->SetValueAsBool(TEXT("IsFriendly"), false);
        }
    }
}

void ANPC::SetBehaviorNeutral()
{
    bIsFriendly = false;
    
    if (NPCController)
    {
        UBlackboardComponent* Blackboard = NPCController->FindComponentByClass<UBlackboardComponent>();
        if (Blackboard)
        {
            Blackboard->SetValueAsBool(TEXT("IsFriendly"), false);
        }
    }
}
