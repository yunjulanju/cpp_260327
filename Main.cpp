#include <iostream>
#include "Engine.h"
#include "World.h"
#include <random>

#include "SDL.h"

using namespace std;


int SDL_main(int argc, char* argv[])
{
	
	GEngine->GetInstance();
	GEngine->GetWorld()->Load("Map.txt");
	GEngine->Run();

	return 0;
}

//int main()
//{
//	
//
//
//	return 0;
//}