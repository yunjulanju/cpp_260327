#pragma once
#include "Component.h"
#include <string>

struct Mix_Music;

class UAudioComponent : public UComponent
{
public:
	UAudioComponent();
	virtual ~UAudioComponent();

	virtual void BeginPlay() override;
	virtual void Tick() override;

	void Play();
	void Stop();

	void Load(std::string InFilename);

private:
	std::string Filename;
	Mix_Music* Music;
};

