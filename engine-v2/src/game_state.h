#pragma once

#include "universal.h"

#include "components.h"
#include "entity.h"
#include "entity_manager.h"

struct GameState {
	// Assets / Textures
	int entity_scale = 32;
	std::unordered_map<std::string, size_t> texture_handles;
	std::vector<Texture2D> textures;

	// Entities and Components
	std::unordered_map<std::string, cGridTransform> blueprint_grid_transforms;
	std::unordered_map<std::string, cRenderable> blueprint_renderables;
	std::unordered_map<std::string, cUnit> blueprint_units;
	
	EntityManager em;

	int32_t selected_entity = 0;

	// Camera and UI Information ==============================================
	Vector2 mouse_pos = {};
	Vector2 world_pos = {};
	IVector2 grid_pos = {};

	const Vector2 game_origin = { 25, 25 };
	const float game_width = 640;
	const float game_height = 480;
	const Rectangle game_window = { game_origin.x, game_origin.y, game_width, game_height };
	const Vector2 origin_debug_region = { game_origin.x + game_width, 0 };
	const Vector2 origin_debug_region2 = { 10, game_origin.y + game_height };
	Camera2D camera = { { 0.0f, 0.0f }, {0.0f, 0.0f}, 0.0f, 1.0f };

	GameState() = default;
};