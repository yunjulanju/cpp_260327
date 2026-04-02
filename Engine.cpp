#include "Engine.h"
#include "World.h"
#include <conio.h>
#include <SDL.h>

UEngine* UEngine::Instance = nullptr;
int UEngine::KeyCode = 0;

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


	bIsRunning = true;
	World = new UWorld();
	InitBuffer();
}

void UEngine::Term()
{
	SDL_DestroyRenderer(MyRenderer);
	SDL_DestroyWindow(MyWindow);
	SDL_Quit();

	delete World;
	TermBuffer();
	World = nullptr;
}

void UEngine::Run()
{
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
}

void UEngine::InitBuffer()
{
	ScreenBufferHandle[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	ScreenBufferHandle[1]=CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	//메모리 어딘가에 화면 저장하는 공간 만들기

	CONSOLE_CURSOR_INFO ConsoleCursorInfo;
	ConsoleCursorInfo.dwSize = 1;
	ConsoleCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(ScreenBufferHandle[0], &ConsoleCursorInfo);
	SetConsoleCursorInfo(ScreenBufferHandle[1], &ConsoleCursorInfo);
}

void UEngine::Clear()
{
	SDL_SetRenderDrawColor(MyRenderer, 255, 255, 255, 255);
	SDL_RenderClear(MyRenderer);

	DWORD DW;
	FillConsoleOutputCharacter(ScreenBufferHandle[ActiveScreenBufferIndex], ' ', 80*25, COORD{0,0}, &DW);
}

void UEngine::Draw(int InX, int InY, char InMesh)
{
	char MeshString[2] = { 0, };
	MeshString[0] = InMesh;
	SetConsoleCursorPosition(ScreenBufferHandle[ActiveScreenBufferIndex], COORD{ (short)InX, (short)InY });
	WriteFile(ScreenBufferHandle[ActiveScreenBufferIndex], MeshString, 1, NULL, NULL);
}

void UEngine::Draw(int InX, int InY, int R, int G, int B, int A)
{
	//SDL_SetRenderDrawColor(MyRenderer, R, G, B, A);
	//SDL_RenderDrawPoint(MyRender, InX, InY);
	SDL_Rect MyRect = { InX * 30,InY * 30 , 30,30};
	SDL_RenderFillRect(MyRenderer, &MyRect);
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
