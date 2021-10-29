#pragma once

#include "universal.h"

#include "grid_transform.h"
#include "entity.h"

struct GameState {
	// std::unordered_map<std::string, Entity> blueprint_entities;
	std::unordered_map<std::string, cTransform> blueprint_transforms;
	std::unordered_map<std::string, cGridTransform> blueprint_grid_transforms;
	
	int64_t entity_id_counter = 0;
	std::vector<Entity> entities;
	std::vector<cTransform> c_transforms;
	std::vector<cGridTransform> c_grid_transforms;

	int32_t selected_entity = 0;

	int entity_scale = 10;

	// Camera and UI Information ==============================================
	Vector2 mouse_pos = {};
	Vector2 world_pos = {};
	IVector2 grid_pos = {};

	const Vector2 game_origin = { 25, 25 };
	const float game_width = 800;
	const float game_height = 600;
	const Rectangle game_window = { game_origin.x, game_origin.y, game_width, game_height };
	const Vector2 origin_debug_region = { game_origin.x + game_width, 0 };
	const Vector2 origin_debug_region2 = { 10, game_origin.y + game_height };
	Camera2D camera = { { 0.0f, 0.0f }, {0.0f, 0.0f}, 0.0f, 1.0f };

	GameState() = default;
};