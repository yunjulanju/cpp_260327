#pragma once

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
protected:
	void Input();
	void Tick();
	void Render();

	class UWorld* World;

	int bIsRunning : 1;
};

#define GEngine			UEngine::GetInstance()