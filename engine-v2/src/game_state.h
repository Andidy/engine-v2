#pragma once

#include "universal.h"

#include "action.h"

#include "components.h"
#include "entity.h"
#include "entity_manager.h"

#include "movement.h"

struct GameState {
	// Actions
	std::unordered_map<int, std::string> action_map;
	std::queue<Action> action_queue;
	void RegisterAction(int input_type, int keycode, std::string action_name);

	// Assets / Textures
	int entity_scale = 32;
	std::unordered_map<std::string, size_t> texture_handles;
	std::vector<Texture2D> textures;

	// Entities and Components
	std::unordered_map<std::string, cGridTransform> blueprint_grid_transforms;
	std::unordered_map<std::string, cRenderable> blueprint_renderables;
	std::unordered_map<std::string, cUnit> blueprint_units;
	
	EntityManager em;

	int32_t selected_entity = -1;

	// Camera and UI Information ==============================================
	Vector2 mouse_pos = {};
	Vector2 world_pos = {};
	IVector2 grid_pos = {};

	bool entity_up = false;
	bool entity_down = false;
	bool entity_left = false;
	bool entity_right = false;
	bool entity_select = false;
	bool entity_action = false;
	bool reset_movement = false;

	bool camera_up = false;
	bool camera_down = false;
	bool camera_left = false;
	bool camera_right = false;
	bool camera_zoom_in = false;
	bool camera_zoom_out = false;
	bool camera_boost = false;
	bool camera_was_moving = false;

	bool save = false;
	bool load = false;
	bool clear_save = false;
	bool debug = false;

	const Vector2 game_origin = { 25, 25 };
	const float game_width = 640;
	const float game_height = 480;
	const Rectangle game_window = { game_origin.x, game_origin.y, game_width, game_height };
	const Vector2 origin_debug_region = { game_origin.x + game_width, 0 };
	const Vector2 origin_debug_region2 = { 10, game_origin.y + game_height };
	Camera2D camera = { { 0.0f, 0.0f }, {0.0f, 0.0f}, 0.0f, 1.0f };

	GameState() = default;
};