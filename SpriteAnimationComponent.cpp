#include "SpriteAnimationComponent.h"
#include "Engine.h"
#include "Actor.h"

USpriteAnimationComponent::USpriteAnimationComponent()
{
}

USpriteAnimationComponent::~USpriteAnimationComponent()
{
}

void USpriteAnimationComponent::Render()
{
	int TileSize = 30;
	int SpriteSizeX = Image->w / 5;
	int SpriteSizeY = Image->h / 5;

	SDL_Rect SourceRect = { SpriteIndexX * SpriteSizeX, SpriteIndexY * SpriteSizeY, SpriteSizeX, SpriteSizeY };
	SDL_Rect DestinationRect = { Owner->GetX() * TileSize, Owner->GetY() * TileSize, TileSize, TileSize };
	SDL_RenderCopy(GEngine->GetRenderer(), Texture, &SourceRect, &DestinationRect);

}

void USpriteAnimationComponent::Tick()
{
	__super::Tick();
	if (CurrentTime < 0.2)
	{
		CurrentTime += GEngine->GetDeltaSeconds();
	}
	else
	{
		SpriteIndexX = (SpriteIndexX + 1) % 5;
		CurrentTime = 0;
	}
}
