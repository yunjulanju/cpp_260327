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
	int TileSize = 30;
	int W = Image->w / 5;
	int H = Image->h / 5;
	//SDL_Rect SourceRect = { W * AnimX ,H * AnimY, W, H };
	SDL_Rect DestinationRect = { X * TileSize, Y * TileSize, TileSize, TileSize };
	SDL_RenderCopy(GEngine->GetRenderer(), Texture, nullptr, &DestinationRect);
}

void AActor::SetActorLocation(int NewX, int NewY)
{
	X = NewX;
	Y = NewY;
}
