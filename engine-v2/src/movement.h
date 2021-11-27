#pragma once

#include "universal.h"

int ManhattanDistance(Vector2 start, Vector2 end);

struct BuildPathContext {
	bool found_path = false;
	int remaining_movement_points = 0;
	std::deque<int> orders;
};

BuildPathContext BuildPath(Vector2 start, Vector2 end, int movement_points);

struct FloodFillContext {
	IVector2 start = {0, 0};
	int remaining_movement_points = 0;
	std::unordered_set<IVector2, IVector2Hash> visited;
	std::vector<IVector2> visited_vec;
	std::vector<IVector2> edge_frontier;
	std::unordered_map<IVector2, int, IVector2Hash> cost;
	std::unordered_map<IVector2, int, IVector2Hash> finalCost;
	std::queue<IVector2> frontier;
};

void FloodFill(FloodFillContext& ffc);