#pragma once

#include "universal.h"
#include "grid_map.h"

struct FloodFillContext {
	IVector2 start = {0, 0};
	int remaining_movement_points = 0;
	int attack_range = 0;
	std::unordered_set<IVector2, IVector2Hash> visited;
	std::unordered_set<IVector2, IVector2Hash> visited_atk_final;

	GridMap* gm;
};

void FloodFill(FloodFillContext& ffc);

template<typename T, typename priority_t>
struct PriorityQueue {
	typedef std::pair<priority_t, T> PQElement;
	
	struct Compare {
		bool operator() (PQElement lhs, PQElement rhs) {
			return lhs.first > rhs.first;
		}
	};
	
	std::priority_queue<PQElement, std::vector<PQElement>, Compare> elements;

	inline bool empty() const { return elements.empty(); }
	inline void put(T item, priority_t priority) { elements.emplace(priority, item); }
	T get() {
		T top = elements.top().second;
		elements.pop();
		return top;
	}
};

struct AStarContext {
	bool found_path = false;
	int remaining_movement_points = 0;

	IVector2 start = { 0, 0 };
	IVector2 goal = { 0, 0 };
	PriorityQueue<IVector2, int> frontier;
	std::unordered_map<IVector2, IVector2, IVector2Hash> from;
	std::unordered_map<IVector2, int, IVector2Hash> costs;
	std::deque<int> path;

	GridMap* gm;
};

void AStar(AStarContext& asc);