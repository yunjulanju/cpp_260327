#include "Player.h"
#include "Engine.h"

APlayer::APlayer(int InX, int InY, char InMesh)
{
	X = InX;
	Y = InY;
	Mesh = InMesh;
	ZOrder = 10;
}

APlayer::~APlayer()
{
}

void APlayer::Tick()
{
	if (UEngine::KeyCode == 'w')
	{
		Y--;
	}
	if (UEngine::KeyCode == 's')
	{
		Y++;
	}
	if (UEngine::KeyCode == 'a')
	{
		X--;
	}
	if (UEngine::KeyCode == 'd')
	{
		X++;
	}
	UEngine::KeyCode = 0;
}
