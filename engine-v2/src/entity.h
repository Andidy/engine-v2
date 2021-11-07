#pragma once

#include "universal.h"

#include "components.h"

struct EntityContext {
	bool is_active = false;
	int32_t id = -1;
	std::string name;

	bool renderable = false;
	int texture_scale = 0;
	size_t texture_handle = 0;
	Color tint_color = WHITE;

	bool grid_transform = false;
	IVector2 gt_pos = { 0, 0 };

	bool unit = false;
};

struct Entity {
	std::string name = "Unnamed";
	int64_t id = -1;
	bool is_active = false;

	int32_t grid_transform = -1;
	int32_t renderable = -1;
	int32_t unit = -1;

	Entity() = default;

	Entity(std::string _name, int64_t _id, int32_t _grid_transform, int32_t _renderable, int32_t _unit) {
		name = _name;
		id = _id;
		grid_transform = _grid_transform;
		renderable = _renderable;
		unit = _unit;
	}
};

