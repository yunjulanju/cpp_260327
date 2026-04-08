#include "World.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Wall.h"
#include "Player.h"
#include "Monster.h"
#include "Goal.h"
#include "Floor.h"
#include "Actor.h"
#include <algorithm>
#include "Engine.h"
#include "SpriteComponent.h"
#include "GameMode.h"
#include "YouDieActor.h"
#include "BGActor.h"

using namespace std;

UWorld::UWorld()
{
}

UWorld::~UWorld()
{
	for (auto Actor : Actors)
	{
		delete Actor;
	}
	Actors.clear();
}

void UWorld::SetGameMode(AGameMode* NewGameMode)
{
	Actors.push_back(NewGameMode);
}

void UWorld::BeginPlay()
{
	for (auto Actor : Actors)
	{
		Actor->BeginPlay();
	}
}

void UWorld::Tick()
{
	for (auto Actor : Actors)
	{
		Actor->Tick();
	}
}

void UWorld::Render()
{
	GEngine->Clear();

	//모든 액터중에서 Render가능한 컴포넌트가 있으면 렌더 하세요.
	for (auto Actor : Actors)
	{
		for (auto Component : Actor->Components)
		{
			IRenderableComponent* RenderComponent = dynamic_cast<IRenderableComponent*>(Component);
			if (RenderComponent && RenderComponent->bIsVisible)
			{
				RenderComponent->Render();
			}
		}
	}

	GEngine->Flip();
}

void UWorld::Load(std::string MapName)
{
	Actors.push_back(new AGameMode());

	string line;
	int y = 0;

	int MaxX = -1;
	int MaxY = -1;

	ifstream file(MapName); // example.txt 파일을 연다. 없으면 생성. 
	if (file.is_open()) {
		while (getline(file, line)) {
			for (int x = 0; x < line.size(); x++)
			{
				if (line[x] == '*')
				{
					SpawnActor<AWall>()->SetActorLocation(x,y);
					SpawnActor<AFloor>()->SetActorLocation(x, y);
				}
				else if (line[x] == 'P')
				{
					SpawnActor<APlayer>()->SetActorLocation(x, y);
					SpawnActor<AFloor>()->SetActorLocation(x, y);
				}
				else if (line[x] == 'M')
				{
					SpawnActor<AMonster>()->SetActorLocation(x, y);
					SpawnActor<AFloor>()->SetActorLocation(x, y);
				}
				else if (line[x] == 'G')
				{
					SpawnActor<AGoal>()->SetActorLocation(x, y);
					SpawnActor<AFloor>()->SetActorLocation(x, y);
				}
				else if (line[x] == ' ')
				{
					SpawnActor<AFloor>()->SetActorLocation(x, y);
				}
				if (x > MaxX)
				{
					MaxX = x;
				}
			}
			y++;
		}
		file.close();
	}

	MaxY = y;

	SDL_SetWindowSize(GEngine->GetWindow(), (MaxX+1) * 30, MaxY * 30);
	
	//map에서 추가해야 함.
	SpawnActor<AYouDieActor>();
	SpawnActor<ABGActor>();

	//Sort()를 알고리즘에 있는 함수로 쓴다면
	std::sort(Actors.begin(), Actors.end(),
		[](AActor* First, AActor* Second) -> int {

			IRenderableComponent* FirstRenderComponet = nullptr;
			for (auto Component : First->Components)
			{
				FirstRenderComponet = dynamic_cast<IRenderableComponent*>(Component);
				if (FirstRenderComponet)
				{
					break;
				}
			}

			IRenderableComponent* SecondRenderComponet = nullptr;
			for (auto Component : Second->Components)
			{
				SecondRenderComponet = dynamic_cast<IRenderableComponent*>(Component);
				if (SecondRenderComponet)
				{
					break;
				}
			}
			if (!FirstRenderComponet || !SecondRenderComponet)
			{
				return false;
			}

			return (FirstRenderComponet->ZOrder < SecondRenderComponet->ZOrder ? 1 : 0);
		}
	);
}

void UWorld::Sort()
{
	//for (int FirstIndex = 0; FirstIndex < Actors.size(); FirstIndex++)
	//{
	//	for (int SecondIndex = 1; SecondIndex < Actors.size(); SecondIndex++)
	//	{
	//		if (Actors[FirstIndex]->GetZOrder() < Actors[SecondIndex]->GetZOrder())
	//		{
	//			auto Temp = Actors[FirstIndex];
	//			Actors[FirstIndex] = Actors[SecondIndex];
	//			Actors[SecondIndex] = Temp;
	//		}
	//	}
	//}
}
