#pragma once
namespace GD 
{
	struct Vector2 
	{
		float x;
		float y;
	};

	struct Transform
	{
		Vector2 pos;
		Vector2 scale = {1.f, 1.f};
		float zOrder;
	};

	enum RenderMode 
	{
		corner,
		center
	};

	enum class ControllerAxis
	{
		LeftStickY,
		LeftStickX,
		RightStickY,
		RightStickX,
		LeftTrigger,
		RightTrigger
	};

	enum class ControllerIndex
	{
		Keyboard = 0,
		One = 1,
		Two = 2,
		Three = 3,
		Four = 4,
		Any = 5
	};

	enum class ButtonState 
	{
		Pressed,
		Down,
		Released
	};
}