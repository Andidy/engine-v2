#pragma once

#include "scene.h"

struct BattleScene : Scene {
	// Game ===============================================
	int selected_entity = -1;

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

	// Rendering and Gui ==================================
	Vector2 origin_debug_region;
	Vector2 origin_debug_region2;

	Vector2 anchor01;
	Vector2 anchor02;
	Vector2 anchor_EntitySpawner;

	// Debug Region
	gui::Label label_mouse_pos;
	gui::Label label_world_pos;
	gui::Label label_grid_pos;
	gui::Label label_selected_entity;
	gui::Label label_num_entities;
	gui::Label label_unit_movement_points;

	// Entity Spawner
	gui::WindowBox window_entity_spawner;
	gui::CheckBox checkbox_renderable;
	gui::CheckBox checkbox_grid_transform;
	gui::CheckBox checkbox_unit;
	gui::CheckBox checkbox_is_active;
	gui::CheckBox checkbox_health;
	gui::ValueBox vb_health;
	gui::CheckBox checkbox_attack;
	gui::ValueBox vb_atk_dmg;
	gui::ValueBox vb_atk_rng;
	gui::CheckBox checkbox_faction;
	gui::TextBox tb_faction_name;
	gui::Line line_0;
	gui::Line line_1;
	gui::Line line_2;
	gui::Line line_3;
	gui::ColorPicker color_picker_entity_spawner;
	gui::TextBox textbox_entity_name;
	gui::TextBox textbox_grid_pos;
	gui::Spinner spinner_texture_select;
	gui::Button button_spawn_entity;

	std::vector<gui::Element*> debug_gui_controls;
	std::vector<gui::Element*> entity_spawner_controls;

	// Camera and UI Information ==============================================
	Vector2 mouse_pos = {};
	Vector2 world_pos = {};
	IVector2 grid_pos = {};

	const Vector2 game_origin = { 25, 25 };
	const float game_width = 640;
	const float game_height = 480;
	const Rectangle game_window = { game_origin.x, game_origin.y, game_width, game_height };
	Camera2D camera = { { 0.0f, 0.0f }, {0.0f, 0.0f}, 0.0f, 1.0f };

	RenderTexture2D render_texture;

	void Init();
	void Update();
	void Render();
	void DrawGridLines();
	void WriteEntityToFile();
	void ReadEntityFromFile(std::string filename);
};