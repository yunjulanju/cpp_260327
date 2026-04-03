#pragma once
#include "Actor.h"
class ACharacter : public AActor
{
public:
	ACharacter();
	virtual ~ACharacter();

protected:
	bool PredictMove(int InX, int InY); //MovementComponent ¸¸µé±â
};

