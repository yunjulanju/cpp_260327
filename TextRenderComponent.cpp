#include "TextRenderComponent.h"
#include "SDL_ttf.h"
#include "Engine.h"
#include "Actor.h"

UTextRenderComponent::UTextRenderComponent()
{
	
}

UTextRenderComponent::~UTextRenderComponent()
{
	if (Surface)
	{
		SDL_FreeSurface(Surface);
	}
	if (Texture)
	{
		SDL_DestroyTexture(Texture);
	}
}

void UTextRenderComponent::BeginPlay()
{
}

void UTextRenderComponent::Tick()
{
}

void UTextRenderComponent::Render()
{
	SDL_Rect DestinationRect{ Owner->GetX(), Owner->GetY(), Surface->w,Surface->h };
	SDL_RenderCopy(GEngine->GetRenderer(), Texture, nullptr, &DestinationRect);
}

void UTextRenderComponent::SetText(std::string InText)
{
	Text = InText;

	//ttf->메모리(bmp파일 만들어)->surface
	//Text글자대로 Font를 사용해 surface를 만들어 주는 것.
	Surface = TTF_RenderText_Solid(GEngine->Font, Text.c_str(), SDL_Color{255,255,0,0});
	//메모리에 있으니 그래픽카드로 넘기는 과정
	Texture= SDL_CreateTextureFromSurface(GEngine->GetRenderer(), Surface);
}
