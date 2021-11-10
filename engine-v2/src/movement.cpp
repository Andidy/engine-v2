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
