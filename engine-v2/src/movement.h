#pragma once

#include "universal.h"

int ManhattanDistance(Vector2 start, Vector2 end);

struct BuildPathContext {
	bool found_path = false;
	int remaining_movement_points = 0;
	std::deque<int> orders;
};

BuildPathContext BuildPath(Vector2 start, Vector2 end, int movement_points);