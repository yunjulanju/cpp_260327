#pragma once
#include <Windows.h>
#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#pragma comment(lib, "SDL2")
#pragma comment(lib, "SDL2main")
#pragma comment(lib, "SDL2_mixer")
#pragma comment(lib, "SDL2_ttf")

class AActor;
class UWorld;
class UResourceManager;

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

	HANDLE ScreenBufferHandle[2];
	int ActiveScreenBufferIndex = 0;
	// 0번쓰고 있으면 1번을 쓰고 그다음 쓸댄 0번 쓰고 해야하니가

	void InitBuffer();
	void Clear();
	/*void Draw(int InX, int InY, char InMesh);
	void Draw(int InX, int InY, int R, int G, int B, int A);*/
	void Draw(int InX, int InY, SDL_Texture* InTexture);
	void Flip();
	void TermBuffer();

	inline SDL_Window* GetWindow() const
	{
		return MyWindow;
	}

	inline const SDL_Event& GetEvent()
	{
		return MyEvent;
	}

	inline SDL_Renderer* GetRenderer() const
	{
		return MyRenderer;
	}

	inline float GetDeltaSeconds() const
	{
		return DeltaSeconds;
	}

	inline UResourceManager* GetResourceManager() const
	{
		return ResourceManager;
	}

	inline UWorld* GetWorld() const
	{
		return World;
	}

protected:
	void Input();
	void Tick();
	void Render();

	class UWorld* World;

	int bIsRunning : 1;

	SDL_Window* MyWindow;
	SDL_Renderer* MyRenderer;
	SDL_Event MyEvent;
	float DeltaSeconds;

	UResourceManager* ResourceManager;
};

#define GEngine			UEngine::GetInstance()