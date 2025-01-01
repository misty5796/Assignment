// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	Warrior UMETA(DisplayName = "Warrior"),
	Mage UMETA(DisplayName = "Mage")
};

UCLASS(Blueprintable)
class MYGAME_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NormalAttack();
	virtual void CastSkill1();
	virtual void CastSkill2();

	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

	APlayerCharacter* CurrentClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	

	// Character's class (Warrior or Mage)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Information")
	ECharacterClass CharacterClass;

	// Health and Mana properties
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Player Information")
	float Health;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "Player Information")
	float Mana;

	// Function to replicate values over the network
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerUseAbility();
	void ServerUseAbility_Implementation();
	bool ServerUseAbility_Validate();

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerPlayAnimation(UAnimSequence* AnimSequence);
	void ServerPlayAnimation_Implementation(UAnimSequence* AnimSequence);
	bool ServerPlayAnimation_Validate(UAnimSequence* AnimSequence);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastPlayAnimation(UAnimSequence* AnimSequence);
	void MulticastPlayAnimation_Implementation(UAnimSequence* AnimSequence);

	UPROPERTY(BlueprintReadWrite)
	bool isAttacking;

private:
	// Movement
	void MoveForwardBackward(float value);
	void MoveLeftRight(float value);

	// View
	void LookLeftRight(float value);
	void LookUpDown(float value);
};
