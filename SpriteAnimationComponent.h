#pragma once
#include "SpriteComponent.h"

class USpriteAnimationComponent : public USpriteComponent
{
public:
	USpriteAnimationComponent();
	virtual ~USpriteAnimationComponent();

	virtual void Render() override;
	virtual void Tick() override;

	int SpriteIndexX = 0;
	int SpriteIndexY = 0;

	float CurrentTime = 0;
};

