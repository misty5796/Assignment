// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PlayerCharacter.h"
#include "WarriorClass.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API AWarriorClass : public APlayerCharacter
{
	GENERATED_BODY()
	
public:
	AWarriorClass();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Animation")
	class UAnimSequence* NormalAttackAnimation;

	virtual void NormalAttack() override;
	virtual void CastSkill1() override;
	virtual void CastSkill2() override;

};
