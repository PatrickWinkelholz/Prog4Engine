#pragma once
#include <Xinput.h>
#include <math.h>
#include <string>

struct SDL_Texture;

namespace GD 
{
	class GameObject;

	struct Vector2 
	{
		float x;
		float y;

		// i got these operators from https://codereview.stackexchange.com/questions/5856/mathematical-vector2-class-implementation
		//ASSINGMENT AND EQUALITY OPERATIONS
		inline Vector2 & operator = (const Vector2 & v) { x = v.x; y = v.y; return *this; }
		inline Vector2 & operator = (const float & f) { x = f; y = f; return *this; }
		inline Vector2 & operator - (void) { x = -x; y = -y; return *this; }
		inline bool operator == (const Vector2 & v) const { return (x == v.x) && (y == v.y); }
		inline bool operator != (const Vector2 & v) const { return (x != v.x) || (y != v.y); }

		//VECTOR2 TO VECTOR2 OPERATIONS
		inline const Vector2 operator + (const Vector2 & v) const { return Vector2{x + v.x, y + v.y}; }
		inline const Vector2 operator - (const Vector2 & v) const { return Vector2{x - v.x, y - v.y}; }
		inline const Vector2 operator * (const Vector2 & v) const { return Vector2{x * v.x, y * v.y}; }
		inline const Vector2 operator / (const Vector2 & v) const { return Vector2{x / v.x, y / v.y}; }

		//VECTOR2 TO THIS OPERATIONS
		inline Vector2 & operator += (const Vector2 & v) { x += v.x; y += v.y; return *this; }
		inline Vector2 & operator -= (const Vector2 & v) { x -= v.x; y -= v.y; return *this; }
		inline Vector2 & operator *= (const Vector2 & v) { x *= v.x; y *= v.y; return *this; }
		inline Vector2 & operator /= (const Vector2 & v) { x /= v.x; y /= v.y; return *this; }

		//SCALER TO VECTOR2 OPERATIONS
		inline const Vector2 operator + (float v) const { return Vector2{x + v, y + v}; }
		inline const Vector2 operator - (float v) const { return Vector2{x - v, y - v}; }
		inline const Vector2 operator * (float v) const { return Vector2{x * v, y * v}; }
		inline const Vector2 operator / (float v) const { return Vector2{x / v, y / v}; }

		//SCALER TO THIS OPERATIONS
		inline Vector2 & operator += (float v) { x += v; y += v; return *this; }
		inline Vector2 & operator -= (float v) { x -= v; y -= v; return *this; }
		inline Vector2 & operator *= (float v) { x *= v; y *= v; return *this; }
		inline Vector2 & operator /= (float v) { x /= v; y /= v; return *this; }

		float Length() const { return float(sqrt(x * x + y * y)); }
		float LengthSquared() const { return x * x + y * y; }

		Vector2& Normalize()
		{
			if (LengthSquared() != 0)
			{
				float length = Length();
				x /= length; 
				y /= length;
			}
			return *this;
		}

		Vector2 Normalized() const
		{
			if (LengthSquared() != 0) 
			{
				float length = Length();
				return { x / length, y / length };
			}
			return { 0, 0 };
		}
	};

	struct Rect 
	{
		Vector2 topLeft;
		Vector2 botRight;
		inline float GetWidth() const { return botRight.x - topLeft.x; };
		inline float GetHeight() const { return botRight.y - topLeft.y; };
	};

	struct Transform
	{
		Vector2 pos;
		Vector2 scale = {1.f, 1.f};
		float zOrder;
	};

	struct Grid 
	{
		Rect bounds;
		int rows;
		int cols;
		Vector2 dimensions = { bounds.botRight.x - bounds.topLeft.x, bounds.botRight.y - bounds.topLeft.y };
		Vector2 tileDimensions = { dimensions.x / float(rows), dimensions.y / float(cols) };
	};

	enum class RenderMode 
	{
		corner,
		center
	};

	struct Texture
	{
		SDL_Texture* SDLTexture;
		RenderMode mode;
		Rect sourceRect;
		bool enabled;
	};

	struct Achievement
	{
		Achievement(int r, std::string&& m)
			: requirement(r), message(m) {};
		int counter = 0;
		bool locked = true;
		int requirement;
		std::string message;
	};

	struct Input
	{
		Vector2 movement{};
		//TODO: move this to digdug
		bool attack = false;
		bool startFloat = false;
	};

	struct Animation
	{
		unsigned int nrFrames = 1;
		float frameTime = 0.2f;
		Rect allFrames = {};
		bool loop = true;
		inline float GetFrameWidth() const { return allFrames.GetWidth() / static_cast<float>(nrFrames); };
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

	enum class ControllerButton
	{
		DPadUp = XINPUT_GAMEPAD_DPAD_UP,
		DPadDown = XINPUT_GAMEPAD_DPAD_DOWN,
		DPadLeft = XINPUT_GAMEPAD_DPAD_LEFT,
		DPadRight = XINPUT_GAMEPAD_DPAD_RIGHT,
		Start = XINPUT_GAMEPAD_START,
		Back = XINPUT_GAMEPAD_BACK,
		LeftStick = XINPUT_GAMEPAD_LEFT_THUMB,
		RightStick = XINPUT_GAMEPAD_RIGHT_THUMB,
		LeftBumper = XINPUT_GAMEPAD_LEFT_SHOULDER,
		RightBumper = XINPUT_GAMEPAD_RIGHT_SHOULDER,
		A = XINPUT_GAMEPAD_A,
		B = XINPUT_GAMEPAD_B,
		X = XINPUT_GAMEPAD_X,
		Y = XINPUT_GAMEPAD_Y
	};

	//tells the inputmanager which SDL_SCANCODE key should be associated with each XBox
	//controller button
	struct KeyboardMap
	{
		WORD DPadUp;
		WORD DPadDown;
		WORD DPadLeft;
		WORD DPadRight;
		WORD Start;
		WORD Back;
		WORD LeftStick;
		WORD RightStick;
		WORD LeftBumper;
		WORD RightBumper;
		WORD A;
		WORD B;
		WORD X;
		WORD Y;
		WORD LeftStickLeft;
		WORD LeftStickRight;
		WORD LeftStickUp;
		WORD LeftStickDown;
		WORD RightStickLeft;
		WORD RightStickRight;
		WORD RightStickUp;
		WORD RightStickDown;
		WORD LeftTrigger;
		WORD RightTrigger;
	};
}