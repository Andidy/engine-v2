#pragma once

#include "universal.h"

// Grid Transform is used to position an entity within the game world's grid
// system.
struct cGridTransform {
	IVector2 pos = { 0,0 };

	std::string ToString();
};

// Renderable is used to provide the renderer (raylib in this case) with the
// information needed to render an entity.
struct cRenderable {
	Vector2 pos = { 0.0f, 0.0f };
	size_t texture_handle = 0;
	Color tint_color = WHITE;

	std::string ToString();
};

/*
	Unit is the primary marker of the gameplay definition of a unit
	which is some living thing in the game world that can be controlled and
	interacted with by the player and AI's. Some examples of units are: an army,
	a trading caravan, a fleet of ships, and a herd of animals.
*/
struct cUnit {
	int movement_points = 3;
	int current_movement_points = movement_points;
	bool waypoint_active = false; // is the movement waypoint active
	std::deque<Vector2> waypoint_pos; // where the movement waypoint is
	
	std::string ToString();
};

/*
	Health allows an entity to take damage and die / be destroyed.
*/
struct cHealth {
	int max;
	int current;

	std::string ToString();
};

/*
	Attack allows an entity to deal damage to things.
*/
struct cAttack {
	int damage;
	int range;

	std::string ToString();
};

/*
	Faction allows entities to be on the same or different teams, friends,
	allies, enemies, neutral relationships can be handled using faction checks.
*/
struct cFaction {
	std::string faction;

	std::string ToString();
};