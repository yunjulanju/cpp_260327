#include <iostream>
#include "Engine.h"
#include "World.h"
#include "MyGM.h"

using namespace std;

int SDL_main(int argc, char* argv[])
{

	GEngine->GetWorld()->SetGameMode(new AMyGM());
	GEngine->GetWorld()->Load("Map.txt");
	GEngine->Run();

	return 0;
}