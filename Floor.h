#pragma once
#include "Actor.h"

class USpriteComponent;

class AFloor : public AActor
{
public:
	AFloor(int InX = 0, int InY = 0, char InMesh = ' ');
	virtual ~AFloor();

	USpriteComponent* SpriteComponent;
};

