#include "Engine.h"
#include "World.h"
#include <conio.h>
#include <SDL.h>
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "ResourceManager.h"
#include "AudioComponent.h"

UEngine* UEngine::Instance = nullptr;

UEngine::UEngine()
{
	Init();
}

UEngine::~UEngine()
{
	Term();
}

void UEngine::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);

	MyWindow = SDL_CreateWindow("Hello", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	MyRenderer = SDL_CreateRenderer(MyWindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

	int frequency = 44100;
	Uint16 format = MIX_DEFAULT_FORMAT;
	int channels = 2;

	//int open = Mix_OpenAudioDevice(44100, MIX_DEFAULT_FORMAT, 2, 2048, NULL, 0);
	int quer = Mix_QuerySpec(&frequency, &format, &channels);
	int succes = Mix_OpenAudio(frequency, format, channels, 2048); //mix 초기화

	TTF_Init(); //ttf 초기화
	Font = TTF_OpenFont("./Data/font.ttf", 32);

	ResourceManager = new UResourceManager();
	bIsRunning = true;
	World = new UWorld();
	InitBuffer();
}

void UEngine::Term()
{
	Mix_CloseAudio();

	//font도 resource니 resourcemanager로 옮겨야 함.
	if (Font)
	{
		TTF_CloseFont(Font);
	}
	TTF_Quit(); //ttf 끄기

	SDL_DestroyRenderer(MyRenderer);
	SDL_DestroyWindow(MyWindow);
	SDL_Quit();

	delete World;
	TermBuffer();
	World = nullptr;

	delete ResourceManager;
}

void UEngine::Run()
{
	World->BeginPlay();

	Uint64 LastTime;
	while (bIsRunning)
	{
		LastTime = SDL_GetTicks64();
		SDL_PollEvent(&MyEvent);

		Input();
		Tick();
		Render();

		DeltaSeconds = (float)(SDL_GetTicks64() - LastTime)/1000.0f;
	}
}

void UEngine::Stop()
{
	bIsRunning = false;
}

void UEngine::InitBuffer()
{
	//ScreenBufferHandle[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	//ScreenBufferHandle[1]=CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	////메모리 어딘가에 화면 저장하는 공간 만들기

	//CONSOLE_CURSOR_INFO ConsoleCursorInfo;
	//ConsoleCursorInfo.dwSize = 1;
	//ConsoleCursorInfo.bVisible = FALSE;
	//SetConsoleCursorInfo(ScreenBufferHandle[0], &ConsoleCursorInfo);
	//SetConsoleCursorInfo(ScreenBufferHandle[1], &ConsoleCursorInfo);
}

void UEngine::Clear()
{
	SDL_SetRenderDrawColor(MyRenderer, 255, 255, 255, 255);
	SDL_RenderClear(MyRenderer);

	/*DWORD DW;
	FillConsoleOutputCharacter(ScreenBufferHandle[ActiveScreenBufferIndex], ' ', 80*25, COORD{0,0}, &DW);*/
}

void UEngine::Draw(int InX, int InY, SDL_Texture* InTexture)
{
	int TileSize = 30;

	SDL_Rect MyRect = { InX * TileSize, InY * TileSize, TileSize,TileSize };
	SDL_RenderCopy(MyRenderer, InTexture, nullptr, &MyRect);
}

void UEngine::Flip()
{
	/*SetConsoleActiveScreenBuffer(ScreenBufferHandle[ActiveScreenBufferIndex]);
	ActiveScreenBufferIndex = 1 - ActiveScreenBufferIndex;*/
}

void UEngine::TermBuffer()
{
	/*CloseHandle(ScreenBufferHandle[0]);
	CloseHandle(ScreenBufferHandle[1]);*/
}

void UEngine::Input()
{
	/*if (_kbhit())
	{
		KeyCode = _getch();
	}*/
}

void UEngine::Tick()
{
	if (MyEvent.type == SDL_QUIT)
	{
		bIsRunning = false;
	}

	World->Tick();
}

void UEngine::Render()
{
	World->Render();

	SDL_RenderPresent(MyRenderer);
}
