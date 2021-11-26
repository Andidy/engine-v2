#pragma once

#include "universal.h"

#include "components.h"

struct EntityContext {
	bool is_active = false;
	int id = -1;
	std::string name;

	bool renderable = false;
	int texture_scale = 0;
	size_t texture_handle = 0;
	Color tint_color = WHITE;

	bool grid_transform = false;
	IVector2 gt_pos = { 0, 0 };

	bool unit = false;

	bool health = false;
	int health_max = 0;

	bool attack = false;
	int attack_damage = 0;
	int attack_range = 0;
};

struct Entity {
	std::string name = "Unnamed";
	int id = -1;
	bool is_active = false;

	int grid_transform = -1;
	int renderable = -1;
	int unit = -1;
	int health = -1;
	int attack = -1;

	Entity() = default;

	Entity(std::string _name, int _id, int _grid_transform, int _renderable, int _unit) {
		name = _name;
		id = _id;
		grid_transform = _grid_transform;
		renderable = _renderable;
		unit = _unit;
	}
};

