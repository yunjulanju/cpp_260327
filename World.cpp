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

void UWorld::Tick()
{
	for (auto Actor : Actors)
	{
		Actor->Tick();
	}
}


void UWorld::Render()
{
	//그리기 전 지운다
	GEngine->Clear();
	for (auto Actor : Actors)
	{
		Actor->Render();
	}
	GEngine->Flip();
}

void UWorld::Load(std::string MapName)
{
	string line;
	int y = 0;
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
			}
			y++;
		}
		file.close();
	}
	//Sort()를 알고리즘에 있는 함수로 쓴다면
	sort(Actors.begin(), Actors.end(), [](AActor* First, AActor* Second) -> int {return (First->GetZOrder() < Second->GetZOrder() ? 1 : 0); });
}

void UWorld::Sort()
{
	for (int FirstIndex = 0; FirstIndex < Actors.size(); FirstIndex++)
	{
		for (int SecondIndex = 1; SecondIndex < Actors.size(); SecondIndex++)
		{
			if (Actors[FirstIndex]->GetZOrder() < Actors[SecondIndex]->GetZOrder())
			{
				auto Temp = Actors[FirstIndex];
				Actors[FirstIndex] = Actors[SecondIndex];
				Actors[SecondIndex] = Temp;
			}
		}
	}
}
