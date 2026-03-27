#pragma once
#include <Windows.h>

class AActor;
class UWorld;
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
	void Flip();
	void TermBuffer();

protected:
	void Input();
	void Tick();
	void Render();

	class UWorld* World;

	int bIsRunning : 1;
};

#define GEngine			UEngine::GetInstance()