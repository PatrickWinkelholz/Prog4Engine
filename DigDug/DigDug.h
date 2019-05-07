#pragma once
#include "GoldDiggerGame.h"

class DigDug : public GD::GoldDiggerGame
{
public:
	DigDug();
	~DigDug();

	DigDug(DigDug&) = delete;
	DigDug(DigDug&&) = delete;
	DigDug& operator=(DigDug&) = delete;
	DigDug&& operator=(DigDug&&) = delete;

	void LoadGame() override;
	void LoadResources() override;
};