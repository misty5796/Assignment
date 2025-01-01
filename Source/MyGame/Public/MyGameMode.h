// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MyGame/Public/Character/PlayerCharacter.h"
#include "MyGameMode.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MYGAME_API AMyGameMode : public AGameMode
{
	GENERATED_BODY()
	
protected:
	void SpawnPlayerWithClass(APlayerController* PlayerController, ECharacterClass SelectedClass);
};
