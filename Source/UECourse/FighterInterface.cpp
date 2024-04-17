// Fill out your copyright notice in the Description page of Project Settings.


#include "FighterInterface.h"

// Add default functionality here for any IFighterInterface functions that are not pure virtual.

int IFighterInterface::DealDamage()
{
	return FMath::FRandRange(10, 20);
}