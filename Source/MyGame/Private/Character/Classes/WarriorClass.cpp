// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Classes/WarriorClass.h"

AWarriorClass::AWarriorClass()
{
    CharacterClass = ECharacterClass::Warrior;
    Health = 200.0f;
    Mana = 50.0f;
}

void AWarriorClass::NormalAttack()
{
    if (!GetMesh()->IsPlaying())
    {
        ServerPlayAnimation(NormalAttackAnimation);
    }
}

void AWarriorClass::CastSkill1()
{

}

void AWarriorClass::CastSkill2()
{

}
