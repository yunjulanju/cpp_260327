#include "Player.h"
#include "Engine.h"

APlayer::APlayer(int InX, int InY, char InMesh)
{
	X = InX;
	Y = InY;
	Mesh = InMesh;
}

APlayer::~APlayer()
{
}

void APlayer::Tick()
{
	if (UEngine::KeyCode == 'w')
	{
		Y--;
		UEngine::KeyCode = 0;
	}
	else if (UEngine::KeyCode == 's')
	{
		Y++;
		UEngine::KeyCode = 0;
	}
	else if (UEngine::KeyCode == 'a')
	{
		X--;
		UEngine::KeyCode = 0;
	}
	else if (UEngine::KeyCode == 'd')
	{
		X++;
		UEngine::KeyCode = 0;
	}
}
