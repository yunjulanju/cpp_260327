#include "World.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Wall.h"
#include "Player.h"
#include "Monster.h"
#include "Goal.h"
#include "Floor.h"

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
	for (auto Actor : Actors)
	{
		Actor->Render();
	}
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
				}
				else if (line[x] == 'P')
				{
					SpawnActor<APlayer>()->SetActorLocation(x, y);
				}
				else if (line[x] == 'M')
				{
					SpawnActor<AMonster>()->SetActorLocation(x, y);
				}
				else if (line[x] == 'G')
				{
					SpawnActor<AGoal>()->SetActorLocation(x, y);
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
	else
	{
		std::cout << "Failed File load";
	}
}
