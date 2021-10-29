#pragma once

#include "universal.h"
#include <deque>

/*
	the unit component is the primary marker of the gameplay definition of a unit
	which is some living thing in the game world that can be controlled and
	interacted with by the player and AI's. Some examples of units are: an army,
	a trading caravan, a fleet of ships, and a herd of animals.
*/
struct cUnit {
	bool waypoint_active = false; // is the movement waypoint active
	std::deque<Vector2> waypoint_pos; // where the movement waypoint is
	// Constructors and Assignment Operators ==================================

	cUnit() = default;

	// copy constructor
	cUnit(const cUnit& source) {
		waypoint_active = source.waypoint_active;
		for (int i = 0; i < source.waypoint_pos.size(); i++) {
			waypoint_pos.push_back(source.waypoint_pos[i]);
		}
	}

	// copy assignment
	cUnit& operator= (const cUnit& source) {
		assert(this != &source);

		waypoint_active = source.waypoint_active;
		for (int i = 0; i < source.waypoint_pos.size(); i++) {
			waypoint_pos.push_back(source.waypoint_pos[i]);
		}

		return *this;
	}

	// move constructor
	cUnit(cUnit&& source) {
		waypoint_active = source.waypoint_active;
		for (int i = 0; i < source.waypoint_pos.size(); i++) {
			waypoint_pos.push_back(source.waypoint_pos[i]);
		}

		source.waypoint_active = false;
		source.waypoint_pos.clear();
	}

	// move assignment
	cUnit& operator= (cUnit&& source) {
		assert(this != &source);

		waypoint_active = source.waypoint_active;
		for (int i = 0; i < source.waypoint_pos.size(); i++) {
			waypoint_pos.push_back(source.waypoint_pos[i]);
		}

		source.waypoint_active = false;
		source.waypoint_pos.clear();

		return *this;
	}
};
