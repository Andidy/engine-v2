#pragma once

#include "universal.h"

// Grid Transform is used to position an entity within the game world's grid
// system.
struct cGridTransform {
	IVector2 pos = { 0,0 };

	std::string ToString();
};