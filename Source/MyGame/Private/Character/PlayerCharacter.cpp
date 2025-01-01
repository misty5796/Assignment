// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"
#include "Net/UnrealNetwork.h"
#include "Camera/CameraComponent.h"
#include "Character/Classes/WarriorClass.h"
#include "Character/Classes/MageClass.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set default values
	Health = 100.0f;
	Mana = 100.0f;
	CharacterClass = ECharacterClass::Warrior; // Default to Warrior

	// Enable replication for multiplayer
	bReplicates = true;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
    Camera->SetupAttachment(RootComponent);
    Camera->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
    if (CharacterClass == ECharacterClass::Warrior)
    {
        CurrentClass = NewObject<AWarriorClass>();
    }
    else if (CharacterClass == ECharacterClass::Mage)
    {
        CurrentClass = NewObject<AMageClass>();
    }

    Super::BeginPlay();
}

void APlayerCharacter::NormalAttack()
{
}

void APlayerCharacter::CastSkill1()
{
}

void APlayerCharacter::CastSkill2()
{
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

    // Movement
    PlayerInputComponent->BindAxis("Move Forward / Backward", this, &APlayerCharacter::MoveForwardBackward);
    PlayerInputComponent->BindAxis("Move Left / Right", this, &APlayerCharacter::MoveLeftRight);
    PlayerInputComponent->BindAction("Normal Attack", IE_Pressed, this, &APlayerCharacter::ServerUseAbility_Implementation);

    // View
    PlayerInputComponent->BindAxis("Look Left / Right", this, &APlayerCharacter::LookLeftRight);
    PlayerInputComponent->BindAxis("Look Up / Down", this, &APlayerCharacter::LookUpDown);
}

// Replicate properties for multiplayer
void APlayerCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(APlayerCharacter, Health);
    DOREPLIFETIME(APlayerCharacter, Mana);
}

void APlayerCharacter::ServerUseAbility_Implementation()
{
    isAttacking = true;
    NormalAttack();
}

bool APlayerCharacter::ServerUseAbility_Validate()
{
    return true; // Add any necessary validation logic here
}

void APlayerCharacter::ServerPlayAnimation_Implementation(UAnimSequence* AnimSequence)
{
    if (AnimSequence && !GetMesh()->IsPlaying())
    {
        // Play animation on server
        GetMesh()->PlayAnimation(AnimSequence, false);

        // Multicast to all clients
        MulticastPlayAnimation(AnimSequence);
    }
}

bool APlayerCharacter::ServerPlayAnimation_Validate(UAnimSequence* AnimSequence)
{
    return AnimSequence != nullptr;
}

void APlayerCharacter::MulticastPlayAnimation_Implementation(UAnimSequence* AnimSequence)
{
    if (AnimSequence && !GetMesh()->IsPlaying())
    {
        // Play the animation sequence on the client
        GetMesh()->PlayAnimation(AnimSequence, false);
    }
}

void APlayerCharacter::MoveForwardBackward(float value)
{
    if (!isAttacking)
    {
        FVector ForwardDirection = GetActorForwardVector();
        AddMovementInput(ForwardDirection, value);
    }
}

void APlayerCharacter::MoveLeftRight(float value)
{
    if (!isAttacking)
    {
        FVector RightDirection = GetActorRightVector();
        AddMovementInput(RightDirection, value);
    }
}

void APlayerCharacter::LookLeftRight(float value)
{
    AddControllerYawInput(value);
}

void APlayerCharacter::LookUpDown(float value)
{
    AddControllerPitchInput(value);
}
