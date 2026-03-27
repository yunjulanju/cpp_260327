#pragma once
#include "Actor.h"
class APlayer : public AActor
{
public:
	APlayer(int InX = 0, int InY = 0, char InMesh='P');
	virtual ~APlayer();

	void Tick() override;
};

