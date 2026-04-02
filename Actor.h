#pragma once
#include <string>

struct SDL_Surface;
struct SDL_Texture;
struct FPosition
{
	int X;
	int Y;
};
class AActor
{
public:
	AActor(int InX = 0, int InY=0, char InMesh = ' ');
	virtual ~AActor();

	virtual void BeginPlay();
	virtual void Tick();
	virtual void Render();

	void SetActorLocation(int NewX, int NewY);
	const int GetZOrder() { return ZOrder; };
	inline FPosition GetPosition() const
	{
		return { X, Y };
	}
protected:
	int X;
	int Y;
	
	int R;
	int G;
	int B;

	int ZOrder = 0;
	char Mesh;

	SDL_Surface* Image = 0;
	SDL_Texture* Texture = 0;

	int AnimX = 0;
	int AnimY = 0;
};

