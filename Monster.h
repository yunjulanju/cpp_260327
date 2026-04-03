#pragma once
#include "Character.h"

class USpriteComponent;
class UCollisionComponent;

class AMonster : public ACharacter
{
public:
	AMonster(int InX = 0, int InY = 0, char InMesh = 'M');
	virtual ~AMonster();

	virtual void Tick() override;

	USpriteComponent* SpriteComponent;
	UCollisionComponent* CollisionComponent;

protected:
	float ElapsedTime = 0;
	float ExecutionTime = 0.1f;

private:
	float CurrentTime = 0.0f;
};

