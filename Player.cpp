#include "Player.h"
#include "Engine.h"
#include "ResourceManager.h"

APlayer::APlayer(int InX, int InY, char InMesh)
{
	X = InX;
	Y = InY;
	Mesh = InMesh;
	ZOrder = 10;

	R = 0;
	G = 0;
	B = 255;

	AnimY = 3;

	Resource TempResource = GEngine->GetResourceManager()->LoadTexture("Data/Player.bmp", true, 255,0,255);
	Image = TempResource.Image;
	Texture = TempResource.Texture;
}

APlayer::~APlayer()
{
}

void APlayer::Tick()
{
	__super::Tick();

	SDL_Event Event = GEngine->GetEvent();

	if (Event.type == SDL_KEYDOWN)
	{
		SDL_Keycode KeyCode = Event.key.keysym.sym;
		if (KeyCode == SDLK_w)
		{
			Y--;
			AnimY = 2;
		}
		if (KeyCode == SDLK_s)
		{
			Y++;
			AnimY = 3;
		}
		if (KeyCode == SDLK_a)
		{
			X--;
			AnimY = 0;
		}
		if (KeyCode == SDLK_d)
		{
			X++;
			AnimY = 1;
		}
		if (KeyCode == SDLK_SPACE)
		{
			GEngine->Stop();
		}
	}

	if (CurrentTime < 0.2)
	{
		CurrentTime += GEngine->GetDeltaSeconds();
	}
	else
	{
		AnimX = (AnimX + 1) % 5;
		CurrentTime = 0;
	}
	
}

void APlayer::Render()
{
	int TileSize = 30;
	int W = Image->w/5;
	int H = Image->h/5;
	SDL_Rect SourceRect = { W * AnimX ,H * AnimY, W, H};
	SDL_Rect DestinationRect = { X * TileSize, Y * TileSize, TileSize, TileSize };
	SDL_RenderCopy(GEngine->GetRenderer(), Texture, &SourceRect, &DestinationRect);
}
