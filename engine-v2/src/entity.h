#pragma once

#include "universal.h"

struct cTransform {
	Vector2 pos = { 0, 0 };

	std::string ToString();
};

struct Entity {
	std::string name = "Unnamed";
	int64_t id = -1;
	bool is_active = false;

	int32_t transform = -1;
	int32_t grid_transform = -1;
	int32_t renderable = -1;
	int32_t citem = 1;

	Entity() = default;

	Entity(std::string _name, int64_t _id, int32_t _transform, int32_t _grid_transform, int32_t _renderable) {
		name = _name;
		id = _id;
		transform = _transform;
		grid_transform = _grid_transform;
		renderable = _renderable;
	}
};

