// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PlayerCharacter.h"
#include "MageClass.generated.h"

/**
 * 
 */
UCLASS()
class MYGAME_API AMageClass : public APlayerCharacter
{
	GENERATED_BODY()

public:
	AMageClass();

	virtual void NormalAttack() override;
	virtual void CastSkill1() override;
	virtual void CastSkill2() override;
};
