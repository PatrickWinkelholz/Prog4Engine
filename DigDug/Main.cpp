#include "pch.h"

#include <vld.h>

#include "GoldDigger.h"
#include "GoldDiggerGame.h"
#include "DigDug.h"

int main()
{
	DD::DigDug* digDug{ new DD::DigDug() };
	GD::GoldDigger goldDigger{ digDug };
	goldDigger.Run();

	delete digDug;

	return 0;
}