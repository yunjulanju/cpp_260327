#include "Monster.h"
#include "Engine.h"
#include <random>
#include "ResourceManager.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"
#include "World.h"

AMonster::AMonster(int InX, int InY, char InMesh)
{
	X = InX;
	Y = InY;

	SpriteComponent = CreateDefaultSubobject<USpriteComponent>("Sprite");

	Resource TempResource = GEngine->GetResourceManager()->LoadTexture("Data/monster.bmp", true, 255, 255, 255);
	SpriteComponent->Image = TempResource.Image;
	SpriteComponent->Texture = TempResource.Texture;
	SpriteComponent->ZOrder = 10;

	CollisionComponent = CreateDefaultSubobject<UCollisionComponent>("Collision");
	CollisionComponent->bIsGenerateOverlap = true;
	CollisionComponent->bIsGenerateHit = false;
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
		if (Direction == 0 && PredictMove(X, Y - 1))
		{
			Y--;
		}
		if (Direction == 1 && PredictMove(X, Y + 1))
		{
			Y++;

		}
		if (Direction == 2 && PredictMove(X - 1, Y))
		{
			X--;

		}
		if (Direction == 3 && PredictMove(X + 1, Y))
		{
			X++;

		}
		if (Direction == 4)
		{
			
		}
		CurrentTime = 0;
	}

}