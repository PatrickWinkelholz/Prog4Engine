#include "GoldDiggerPCH.h"
#pragma comment(lib,"xinput.lib")

// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#include "SDL.h"
#include "GoldDigger.h"

#pragma warning( push )  
#pragma warning( disable : 4100 )  
int main(int argc, char* argv[]) {
#pragma warning( pop )

	engine::GoldDigger engine;
	engine.Run();
    return 0;
}

