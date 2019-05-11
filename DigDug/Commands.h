#pragma once
#include "Command.h"
#include "GameObject.h"

class MoveHorizontal : public GD::Command
{
public:
	void Execute(GD::GameObject& gameObject) override;
	~MoveHorizontal() = default;
};

class MoveVertical : public GD::Command 
{
public:
	void Execute(GD::GameObject& gameObject) override;
	~MoveVertical() = default;
};