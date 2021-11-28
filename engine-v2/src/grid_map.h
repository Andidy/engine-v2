#pragma once

#include "universal.h"

static int terrain_costs[] = {
	1, // grass
	1, // water
	2  // trees
};

struct Tile {
	IVector2 pos;
	int is_land;
	int terrain_type;
};

struct GridMap {
	std::unordered_map<IVector2, Tile, IVector2Hash> tiles;

	void LoadMap(std::string name);
};