#include "Monster.h"
#include "Engine.h"
#include <random>

AMonster::AMonster(int InX, int InY, char InMesh)
{
	X = InX;
	Y = InY;
	Mesh = InMesh;
	ZOrder = 5;

	R = 255;
	G = 0;
	B = 0;

	Load("Data/monster.bmp");
}

AMonster::~AMonster()
{
}

std::random_device RandomDevice;
std::mt19937 RandomGenerator(RandomDevice());
std::mt19937 rng(RandomDevice());

void AMonster::Tick()
{
	std::uniform_int_distribution<int> RandDirection(0, 5);
	
	if (CurrentTime < 0.2)
	{
		CurrentTime += GEngine->GetDeltaSeconds();
	}
	else
	{
		int Direction = RandDirection(RandomGenerator);
		if (Direction == 0)
		{
			Y--;
		}
		if (Direction == 1)
		{
			Y++;

		}
		if (Direction == 2)
		{
			X--;

		}
		if (Direction == 3)
		{
			X++;

		}
		if (Direction == 4)
		{
			
		}
		CurrentTime = 0;
	}

}
