#include "YouDieActor.h"
#include "TextRenderComponent.h"

AYouDieActor::AYouDieActor()
{
	TextRenderComponent->SetText("You Die.");
	X = 50;
	Y = 50;
	TextRenderComponent->ZOrder = 200;
	TextRenderComponent->bIsVisible = false;
}

AYouDieActor::~AYouDieActor()
{
}
