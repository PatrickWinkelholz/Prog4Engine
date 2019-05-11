#include "pch.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <vld.h>

#include "GoldDigger.h"
#include "GoldDiggerGame.h"
#include "DigDug.h"

int main()
{
	DigDug* digDug{ new DigDug() };
	GD::GoldDigger goldDigger{ digDug };
	goldDigger.Run();

	delete digDug;

	return 0;
}