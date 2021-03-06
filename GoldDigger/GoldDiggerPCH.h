#pragma once

#include "targetver.h"

#include <iostream>
#include <sstream>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX //needed for std::max

#include <windows.h>
#include <SDL.h>
#include <xinput.h>

#include "Log.h" // Various logging functions