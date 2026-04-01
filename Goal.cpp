#include "Goal.h"

AGoal::AGoal(int InX, int InY, char InMesh)
{
	X = InX;
	Y = InY;
	Mesh = InMesh;
	ZOrder = 2;

	R = 255;
	G = 255;
	B = 0;
}

AGoal::~AGoal()
{
}
