#pragma once

#include <assert.h>
#include <stdint.h>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <tuple>
#include <fstream>
#include <sstream>
#include <iostream>

#include "config.h"
// this is here because raylib's config defaults to 8
// which is 2 higher than neccesary for standard controllers
// and 2 of those are for the analog behavior of the triggers
// that some controllers use. I don't feel that the analog
// triggers is useful for engine-v2 so use this instead
// of MAX_GAMEPAD_AXIS
const int NUM_CONTROLLER_AXIS = 4;
#include "raylib.h"

#include "raygui.h"
#include "raygui_helpers.h"

#include "IVector2.h"

#include "raylib_cpp_helpers.h"

// This forward declaration allows the Scenes to have a pointer to the
// GameState to access the assets.
struct GameState;