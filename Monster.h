#pragma once
#include "Actor.h"

class AMonster : public AActor
{
public:
	AMonster(int InX = 0, int InY = 0, char InMesh = 'M');
	virtual ~AMonster();

	virtual void Tick() override;

private:
	int AnimX = 0;
	int AnimY = 0;
	float CurrentTime = 0;

};

