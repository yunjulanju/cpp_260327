#include "Actor.h"
#include <iostream>
#include "Engine.h"

AActor::AActor(int InX, int InY, char InMesh)
{
	X = InX;
	Y = InY;
	Mesh = InMesh;

	R = 0;
	G = 0;
	B = 0;
}

AActor::~AActor()
{

}

void AActor::BeginPlay()
{
}

void AActor::Tick()
{
}

void AActor::Render()
{
	/*COORD Coordinate;
	Coordinate.X = X;
	Coordinate.Y = Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Coordinate);

	std::cout << Mesh;*/

	GEngine->Draw(X,Y,Mesh);
	GEngine->Draw(X, Y, R,G,B, 255);
}

void AActor::SetActorLocation(int NewX, int NewY)
{
	X = NewX;
	Y = NewY;
}
