#include "movement.h"

void FloodFill(FloodFillContext& ffc) {
	ffc.frontier.push(ffc.start);
	ffc.cost[ffc.start] = 0;

	while (!ffc.frontier.empty()) {
		auto curr_tile = ffc.frontier.front();
		ffc.frontier.pop();

		if (ffc.visited.find(curr_tile) == ffc.visited.end()) {
			ffc.visited.insert(curr_tile);
			auto cost = ffc.cost[curr_tile];

			const int num_directions = 4;
			IVector2 directions[num_directions] = {
				{curr_tile.x, curr_tile.y - 1}, // north
				{curr_tile.x, curr_tile.y + 1}, // south
				{curr_tile.x - 1, curr_tile.y}, // west
				{curr_tile.x + 1, curr_tile.y}  // east
			};

			if (cost < ffc.remaining_movement_points) {
				ffc.finalCost[curr_tile] = cost;
				
				for (int i = 0; i < num_directions; i++) {
					IVector2 dir = directions[i];
					if (ffc.gm->tiles.find(dir) != ffc.gm->tiles.end()) {
						if (ffc.gm->tiles[dir].is_land) {
							if (ffc.visited.find(dir) == ffc.visited.end()) {
								int pathCost = cost + terrain_costs[ffc.gm->tiles[dir].terrain_type];

								int cost_so_far = INT_MAX;
								if (ffc.cost.find(dir) != ffc.cost.end()) {
									cost_so_far = ffc.cost[dir];
								}

								if (pathCost < cost_so_far) {
									ffc.cost[dir] = pathCost;
								}

								ffc.frontier.push(dir);
							}
						}
					}
				}
			}
			else { // store final boundary?
				for (int i = 0; i < num_directions; i++) {
					IVector2 dir = directions[i];
					if (ffc.gm->tiles.find(dir) != ffc.gm->tiles.end()) {
						if (ffc.gm->tiles[dir].is_land) {
							if (ffc.visited.find(dir) == ffc.visited.end()) {
								int pathCost = cost + 1;

								int cost_so_far = INT_MAX;
								if (ffc.cost.find(dir) != ffc.cost.end()) {
									cost_so_far = ffc.cost[dir];
								}

								if (pathCost < cost_so_far) {
									ffc.cost[dir] = pathCost;
								}

								ffc.edge_frontier.insert(dir);
							}
						}
					}
				}
			}
		}
	}

	for (auto& node : ffc.visited) {
		ffc.edge_frontier.extract(node);
	}
}

int AStarHeuristic(IVector2 start, IVector2 end) {
	return abs(start.x - end.x) + abs(start.y - end.y);
}

const int UP = 1;
const int DOWN = 2;
const int LEFT = 3;
const int RIGHT = 4;

void AStar(AStarContext& asc) {
	asc.frontier.put(asc.start, 0);
	asc.from[asc.start] = asc.start;
	asc.costs[asc.start] = 0;

	while (!asc.frontier.empty()) {
		IVector2 curr_tile = asc.frontier.get();

		if (curr_tile == asc.goal) {
			asc.found_path = true;
			break;
		}

		if (asc.costs[curr_tile] >= asc.remaining_movement_points) {
			continue;
		}

		const int num_directions = 4;
		IVector2 directions[num_directions] = {
			{curr_tile.x, curr_tile.y - 1}, // north
			{curr_tile.x, curr_tile.y + 1}, // south
			{curr_tile.x - 1, curr_tile.y}, // west
			{curr_tile.x + 1, curr_tile.y}  // east
		};

		for (int i = 0; i < num_directions; i++) {
			Tile t = asc.gm->tiles[directions[i]];
			if (t.is_land) {
				int new_cost = asc.costs[curr_tile] + terrain_costs[t.terrain_type];

				if (asc.costs.find(directions[i]) == asc.costs.end() || new_cost < asc.costs[directions[i]]) {
					asc.costs[directions[i]] = new_cost;
					int priority = new_cost + AStarHeuristic(directions[i], asc.goal);
					asc.frontier.put(directions[i], priority);
					asc.from[directions[i]] = curr_tile;
				}
			}
		}
	}

	if (!asc.found_path) {
		return;
	}
	else {
		IVector2 ghost = asc.goal;
		
		while (ghost != asc.start) {
			IVector2 prev = asc.from[ghost];
			IVector2 delta = ghost - prev;

			if (delta.x == 1) {
				// RIGHT
				asc.path.push_front(RIGHT);
			}
			else if (delta.x == -1) {
				// LEFT
				asc.path.push_front(LEFT);
			}
			else if (delta.y == 1) {
				// DOWN
				asc.path.push_front(DOWN);
			}
			else if (delta.y == -1) {
				// UP
				asc.path.push_front(UP);
			}

			ghost = prev;
		}

		asc.remaining_movement_points -= asc.costs[asc.goal];
	}
}