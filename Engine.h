#pragma once
#include <Windows.h>
#include "SDL.h"
#pragma comment(lib, "SDL2")
#pragma comment(lib, "SDL2main")

class AActor;
class UWorld;

struct SDL_Window;
struct SDL_Renderer;

class UEngine
{
private:
	UEngine();

	static UEngine* Instance;
public:
	virtual ~UEngine();

	static UEngine* GetInstance()
	{
		if (Instance == nullptr)
		{
			Instance = new UEngine();
		}

		return Instance;
	}

	void Init();
	void Term();
	
	void Run();
	void Stop();


	inline UWorld* GetWorld()
	{
		return World;
	}
	static int KeyCode;
	HANDLE ScreenBufferHandle[2];
	int ActiveScreenBufferIndex = 0;
	// 0번쓰고 있으면 1번을 쓰고 그다음 쓸댄 0번 쓰고 해야하니가

	void InitBuffer();
	void Clear();
	void Draw(int InX, int InY, char InMesh);
	void Draw(int InX, int InY, int R, int G, int B, int A);
	void Flip();
	void TermBuffer();

	inline const SDL_Event& GetEvent()
	{
		return MyEvent;
	}

protected:
	void Input();
	void Tick();
	void Render();

	class UWorld* World;

	int bIsRunning : 1;

	SDL_Window* MyWindow;
	SDL_Renderer* MyRender;
	SDL_Event MyEvent;
};

#define GEngine			UEngine::GetInstance()