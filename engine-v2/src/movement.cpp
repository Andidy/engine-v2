#include "movement.h"

int ManhattanDistance(Vector2 start, Vector2 end) {
	return fabsf(end.x - start.x) + fabsf(end.y - start.y);
}


#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
BuildPathContext BuildPath(Vector2 start, Vector2 end, int movement_points) {
	BuildPathContext bpc;
	
	int distance = ManhattanDistance(start, end);
	if (distance > movement_points) {
		bpc.found_path = false;
		bpc.remaining_movement_points = movement_points;
		return bpc;
	}

	Vector2 ghost = start;
	while (ghost != end) {
		Vector2 delta = end - ghost;
		if (fabsf(delta.x) >= fabsf(delta.y)) {
			if (delta.x >= 0) {
				bpc.orders.push_back(RIGHT);
				ghost.x += 1.0f;
			}
			else {
				bpc.orders.push_back(LEFT);
				ghost.x -= 1.0f;
			}
		}
		else {
			if (delta.y >= 0) {
				bpc.orders.push_back(DOWN);
				ghost.y += 1.0f;
			}
			else {
				bpc.orders.push_back(UP);
				ghost.y -= 1.0f;
			}
		}
	}

	bpc.found_path = true;
	bpc.remaining_movement_points = movement_points - distance;
	return bpc;
}
#undef UP
#undef DOWN
#undef LEFT
#undef RIGHT

void FloodFill(FloodFillContext& ffc) {
	ffc.frontier.push(ffc.start);
	ffc.cost[ffc.start] = 0.0f;

	while (!ffc.frontier.empty()) {
		auto curr_tile = ffc.frontier.front();
		ffc.frontier.pop();

		if (ffc.visited.find(curr_tile) == ffc.visited.end()) {
			ffc.visited.insert(curr_tile);
			ffc.visited_vec.push_back(curr_tile);
			auto cost = ffc.cost[curr_tile];

			if (cost < ffc.remaining_movement_points) {
				ffc.finalCost[curr_tile] = cost;
				
				// Check North
				IVector2 north = { curr_tile.x, curr_tile.y - 1 };
				if (ffc.visited.find(north) == ffc.visited.end()) {
					int pathCost = cost + 1;
					
					int cost_so_far = INT_MAX;
					if (ffc.cost.find(north) != ffc.cost.end()) {
						cost_so_far = ffc.cost[north];
					}

					if (pathCost < cost_so_far) {
						ffc.cost[north] = pathCost;
					}

					ffc.frontier.push(north);
				}

				// Check South
				IVector2 south = { curr_tile.x, curr_tile.y + 1 };
				if (ffc.visited.find(south) == ffc.visited.end()) {
					int pathCost = cost + 1;

					int cost_so_far = INT_MAX;
					if (ffc.cost.find(south) != ffc.cost.end()) {
						cost_so_far = ffc.cost[south];
					}

					if (pathCost < cost_so_far) {
						ffc.cost[south] = pathCost;
					}

					ffc.frontier.push(south);
				}

				// Check West
				IVector2 west = { curr_tile.x - 1, curr_tile.y };
				if (ffc.visited.find(west) == ffc.visited.end()) {
					int pathCost = cost + 1;

					int cost_so_far = INT_MAX;
					if (ffc.cost.find(west) != ffc.cost.end()) {
						cost_so_far = ffc.cost[west];
					}

					if (pathCost < cost_so_far) {
						ffc.cost[west] = pathCost;
					}

					ffc.frontier.push(west);
				}

				// Check East
				IVector2 east = { curr_tile.x + 1, curr_tile.y };
				if (ffc.visited.find(east) == ffc.visited.end()) {
					int pathCost = cost + 1;

					int cost_so_far = INT_MAX;
					if (ffc.cost.find(east) != ffc.cost.end()) {
						cost_so_far = ffc.cost[east];
					}

					if (pathCost < cost_so_far) {
						ffc.cost[east] = pathCost;
					}

					ffc.frontier.push(east);
				}
			}
			else { // store final boundary?
				ffc.finalCost[curr_tile] = cost;

				// Check North
				IVector2 north = { curr_tile.x, curr_tile.y - 1 };
				if (ffc.visited.find(north) == ffc.visited.end()) {
					int pathCost = cost + 1;

					int cost_so_far = INT_MAX;
					if (ffc.cost.find(north) != ffc.cost.end()) {
						cost_so_far = ffc.cost[north];
					}

					if (pathCost < cost_so_far) {
						ffc.cost[north] = pathCost;
					}

					ffc.edge_frontier.push_back(north);
				}

				// Check South
				IVector2 south = { curr_tile.x, curr_tile.y + 1 };
				if (ffc.visited.find(south) == ffc.visited.end()) {
					int pathCost = cost + 1;

					int cost_so_far = INT_MAX;
					if (ffc.cost.find(south) != ffc.cost.end()) {
						cost_so_far = ffc.cost[south];
					}

					if (pathCost < cost_so_far) {
						ffc.cost[south] = pathCost;
					}

					ffc.edge_frontier.push_back(south);
				}

				// Check West
				IVector2 west = { curr_tile.x - 1, curr_tile.y };
				if (ffc.visited.find(west) == ffc.visited.end()) {
					int pathCost = cost + 1;

					int cost_so_far = INT_MAX;
					if (ffc.cost.find(west) != ffc.cost.end()) {
						cost_so_far = ffc.cost[west];
					}

					if (pathCost < cost_so_far) {
						ffc.cost[west] = pathCost;
					}

					ffc.edge_frontier.push_back(west);
				}

				// Check East
				IVector2 east = { curr_tile.x + 1, curr_tile.y };
				if (ffc.visited.find(east) == ffc.visited.end()) {
					int pathCost = cost + 1;

					int cost_so_far = INT_MAX;
					if (ffc.cost.find(east) != ffc.cost.end()) {
						cost_so_far = ffc.cost[east];
					}

					if (pathCost < cost_so_far) {
						ffc.cost[east] = pathCost;
					}

					ffc.edge_frontier.push_back(east);
				}
			}
		}
	}
}