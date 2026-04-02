#include "Player.h"
#include "Engine.h"

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

	Load("Data/Player.bmp");
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

void APlayer::Load(std::string Filename)
{
	Image = SDL_LoadBMP(Filename.c_str());
	//surface¿¡¼­ Æ¯Á¤ »ö »©¼­ ±×·ÁÁà
	SDL_SetColorKey(Image, SDL_TRUE, SDL_MapRGB(Image->format, 255, 0, 255));

	Texture = SDL_CreateTextureFromSurface(GEngine->GetRenderer(), Image);
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
