#include "Player.h"
#include "Engine.h"
#include "ResourceManager.h"
#include "SpriteAnimationComponent.h"
#include "CollisionComponent.h"
#include "World.h"
#include "Goal.h"
#include "MyGM.h"
#include "Monster.h"
#include "GameplayStatics.h"

APlayer::APlayer(int InX, int InY, char InMesh)
{
	X = InX;
	Y = InY;

	SpriteAnimationComponent = CreateDefaultSubobject<USpriteAnimationComponent>("Sprite");

	Resource TempResource = GEngine->GetResourceManager()->LoadTexture("Data/player.bmp", true, 255, 0, 255);
	SpriteAnimationComponent->Image = TempResource.Image;
	SpriteAnimationComponent->Texture = TempResource.Texture;
	SpriteAnimationComponent->ZOrder = 50;

	CollisionComponent = CreateDefaultSubobject<UCollisionComponent>("Collision");
	CollisionComponent->bIsGenerateOverlap = true;
	CollisionComponent->bIsGenerateHit = true;
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	__super::BeginPlay();
	OnActorBeginOverlap = [&](AActor* Other) -> void {
		AGoal* Goal = dynamic_cast<AGoal*>(Other);
		if (Goal)
		{
			AMyGM* GM = dynamic_cast<AMyGM*>(UGameplayStatics::GetGameMode());
			if (GM)
			{
				GM->GameComplete();
			}
		}

		AMonster* Monster = dynamic_cast<AMonster*>(Other);
		if (Monster)
		{
			AMyGM* GM = dynamic_cast<AMyGM*>(UGameplayStatics::GetGameMode());
			if (GM)
			{
				GM->GameOver();
			}
		}
		};
}

void APlayer::Tick()
{
	__super::Tick();

	SDL_Event Event = GEngine->GetEvent();

	if (Event.type == SDL_KEYDOWN)
	{
		SDL_Keycode KeyCode = Event.key.keysym.sym;
		if (KeyCode == SDLK_w && PredictMove(X,Y-1))
		{
			Y--;
			SpriteAnimationComponent->SpriteIndexY = 2;
			SpriteAnimationComponent->SpriteIndexX = 0;
		}
		if (KeyCode == SDLK_s && PredictMove(X, Y+1))
		{
			Y++;
			SpriteAnimationComponent->SpriteIndexY = 3;
			SpriteAnimationComponent->SpriteIndexX = 0;
		}
		if (KeyCode == SDLK_a && PredictMove(X-1, Y))
		{
			X--;
			SpriteAnimationComponent->SpriteIndexY = 0;
			SpriteAnimationComponent->SpriteIndexX = 0;
		}
		if (KeyCode == SDLK_d && PredictMove(X+1, Y))
		{
			X++;
			SpriteAnimationComponent->SpriteIndexY = 1;
			SpriteAnimationComponent->SpriteIndexX = 0;
		}
		if (KeyCode == SDLK_SPACE)
		{
			GEngine->Stop();
		}
	}	
}

void APlayer::ReceiveHit(AActor* Other)
{

}

void APlayer::ProcessBeginOverlap(AActor* OtherActor)
{

}