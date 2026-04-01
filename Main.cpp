#include <iostream>
#include "Engine.h"
#include "World.h"
#include <random>

#include "SDL.h"

#pragma comment(lib, "SDL2")
#pragma comment(lib,"SDL2main")

using namespace std;

void RandomRect(SDL_Renderer* InRender)
{
	
}

int SDL_main(int argc, char* argv[])
{
	std::random_device RandomDevice;
	std::mt19937 RandomGenerator(RandomDevice());

	
	
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* MyWindow = SDL_CreateWindow("Hello", 100, 100, 640, 480, SDL_WINDOW_SHOWN);

	// GPU 붓
	SDL_Renderer* MyRender = SDL_CreateRenderer(MyWindow, -1, 0);
		
	while (true)
	{
		SDL_Event MyEvent; //계속 물어보는 걸 Polling한다 고 함.
		SDL_PollEvent(&MyEvent);

		if (MyEvent.type == SDL_QUIT) {
			break;
		}
		//GPU 한테 보낼 명령어 모음
		SDL_SetRenderDrawColor(MyRender, 255, 255, 255, 255);
		SDL_RenderClear(MyRender);
		/////////////////////
		
		//그리는 곳 : 어떻게 그릴지 명령어를 GPU에 넣을 곳
		std::uniform_int_distribution<int>  randomX(0, 640);
		std::uniform_int_distribution<int>  randomY(0, 480);
		std::uniform_int_distribution<int>  randomWidth(0, 640);
		std::uniform_int_distribution<int>  randomHeight(0, 480);

		std::uniform_int_distribution<int>  randomR(0, 256);
		std::uniform_int_distribution<int>  randomG(0, 256);
		std::uniform_int_distribution<int>  randomB(0, 256);
		std::uniform_int_distribution<int>  randomA(0, 256);

		SDL_Rect MyRect = { randomX(RandomGenerator),randomY(RandomGenerator),randomWidth(RandomGenerator),randomHeight(RandomGenerator) };
		SDL_SetRenderDrawColor(MyRender, randomR(RandomGenerator), randomG(RandomGenerator), randomB(RandomGenerator), randomA(RandomGenerator));
		SDL_RenderFillRect(MyRender, &MyRect); //C언어 컴파일러가 실행되서 포인터로 받는 것.


		/////////////////////
		SDL_RenderPresent(MyRender);
	}

	SDL_DestroyRenderer(MyRender);
	SDL_DestroyWindow(MyWindow);
	SDL_Quit();


	return 0;
}

//int main()
//{
//	GEngine->GetInstance();
//	GEngine->GetWorld()->Load("Map.txt");
//	GEngine->Run();
//
//
//	return 0;
//}