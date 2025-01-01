// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameMode.h"
#include "MyGame/Public/Character/Classes/WarriorClass.h"
#include "MyGame/Public/Character/Classes/MageClass.h"

void AMyGameMode::SpawnPlayerWithClass(APlayerController* PlayerController, ECharacterClass SelectedClass)
{
    FVector SpawnLocation(0.0f, 0.0f, 100.0f); // Set spawn location
    FRotator SpawnRotation(0.0f, 0.0f, 0.0f);  // Set spawn rotation

    if (SelectedClass == ECharacterClass::Warrior)
    {
        AWarriorClass* NewCharacter = GetWorld()->SpawnActor<AWarriorClass>(AWarriorClass::StaticClass(), SpawnLocation, SpawnRotation);
        PlayerController->Possess(NewCharacter);
    }
    else if (SelectedClass == ECharacterClass::Mage)
    {
        AMageClass* NewCharacter = GetWorld()->SpawnActor<AMageClass>(AMageClass::StaticClass(), SpawnLocation, SpawnRotation);
        PlayerController->Possess(NewCharacter);
    }
}