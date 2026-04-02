#pragma once
#include "Actor.h"
class APlayer : public AActor
{
public:
	APlayer(int InX = 0, int InY = 0, char InMesh='P');
	virtual ~APlayer();

	virtual void Tick() override;
	virtual void Load(std::string Filename) override;
	virtual void Render() override;

private:
	int AnimX = 0;
	int AnimY = 0;
	float CurrentTime = 0;
};

