#include "scene_battle.h"
#include "game.h"

// Battle Scene ===============================================================

void BattleScene::Init() {
	RegisterAction(0, KEY_O, "SAVEGAME");
	RegisterAction(0, KEY_I, "LOADGAME");
	RegisterAction(0, KEY_U, "DELETESAVE");
	RegisterAction(0, KEY_EQUAL, "DEBUG");

	RegisterAction(0, KEY_W, "ENTITY_UP");
	RegisterAction(0, KEY_D, "ENTITY_RIGHT");
	RegisterAction(0, KEY_S, "ENTITY_DOWN");
	RegisterAction(0, KEY_A, "ENTITY_LEFT");
	RegisterAction(0, KEY_R, "RESET_MOVEMENT");

	RegisterAction(0, KEY_LEFT, "CAMERA_LEFT");
	RegisterAction(0, KEY_RIGHT, "CAMERA_RIGHT");
	RegisterAction(0, KEY_UP, "CAMERA_UP");
	RegisterAction(0, KEY_DOWN, "CAMERA_DOWN");
	RegisterAction(0, KEY_LEFT_SHIFT, "CAMERA_BOOST");
	RegisterAction(0, KEY_PAGE_UP, "CAMERA_ZOOM_IN");
	RegisterAction(0, KEY_PAGE_DOWN, "CAMERA_ZOOM_OUT");

	RegisterAction(1, MOUSE_BUTTON_LEFT, "ENTITY_SELECT");
	RegisterAction(1, MOUSE_BUTTON_RIGHT, "ENTITY_ACTION");

	RegisterAction(2, GAMEPAD_BUTTON_RIGHT_FACE_LEFT, "ENTITY_LEFT");
	RegisterAction(2, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT, "ENTITY_RIGHT");
	RegisterAction(2, GAMEPAD_BUTTON_RIGHT_FACE_UP, "ENTITY_UP");
	RegisterAction(2, GAMEPAD_BUTTON_RIGHT_FACE_DOWN, "ENTITY_DOWN");
	RegisterAction(2, GAMEPAD_BUTTON_RIGHT_TRIGGER_2, "RESET_MOVEMENT");

	RegisterAction(2, GAMEPAD_BUTTON_LEFT_FACE_LEFT, "CAMERA_LEFT");
	RegisterAction(2, GAMEPAD_BUTTON_LEFT_FACE_RIGHT, "CAMERA_RIGHT");
	RegisterAction(2, GAMEPAD_BUTTON_LEFT_FACE_UP, "CAMERA_UP");
	RegisterAction(2, GAMEPAD_BUTTON_LEFT_FACE_DOWN, "CAMERA_DOWN");
	RegisterAction(2, GAMEPAD_BUTTON_RIGHT_TRIGGER_1, "CAMERA_BOOST");
	RegisterAction(2, GAMEPAD_BUTTON_LEFT_TRIGGER_1, "CAMERA_ZOOM_IN");
	RegisterAction(2, GAMEPAD_BUTTON_LEFT_TRIGGER_2, "CAMERA_ZOOM_OUT");

	//RegisterAction(3, GAMEPAD_AXIS_RIGHT_X, "CAMERA_LEFT");
	//RegisterAction(3, GAMEPAD_AXIS_RIGHT_X, "CAMERA_RIGHT");
	//RegisterAction(3, GAMEPAD_AXIS_RIGHT_Y, "CAMERA_UP");
	//RegisterAction(3, GAMEPAD_AXIS_RIGHT_Y, "CAMERA_DOWN");


	origin_debug_region = { game_window.x + game_window.width, 0 };
	origin_debug_region2 = { 10, game_window.y + game_window.height };

	// my_layout: controls initialization
	//----------------------------------------------------------------------------------
	anchor01 = origin_debug_region;
	anchor02 = origin_debug_region2;

	label_mouse_pos.bounds = { anchor01.x + 10, anchor01.y + 10, 125, 25 };
	label_mouse_pos.text = {};
	debug_gui_controls.push_back(&label_mouse_pos);

	label_world_pos.bounds = { anchor01.x + 10, anchor01.y + 30, 125, 25 };
	label_world_pos.text = {};
	debug_gui_controls.push_back(&label_world_pos);

	label_grid_pos.bounds = { anchor01.x + 10, anchor01.y + 50, 125, 25 };
	label_grid_pos.text = {};
	debug_gui_controls.push_back(&label_grid_pos);

	label_selected_entity.bounds = { anchor01.x + 10, anchor01.y + 70, 125, 25 };
	label_selected_entity.text = {};
	debug_gui_controls.push_back(&label_selected_entity);

	label_num_entities.bounds = { anchor01.x + 10, anchor01.y + 90, 125, 25 };
	label_num_entities.text = {};
	debug_gui_controls.push_back(&label_num_entities);

	label_unit_movement_points.bounds = { anchor01.x + 10, anchor01.y + 110, 125, 25 };
	label_unit_movement_points.text = {};
	debug_gui_controls.push_back(&label_unit_movement_points);

	// Entity Spawner variables
	//----------------------------------------------------------------------------------
	anchor_EntitySpawner = { anchor01.x + 10, 220 };

	const int entity_spawner_text_size = 128;

	window_entity_spawner.bounds = { anchor_EntitySpawner.x + 0, anchor_EntitySpawner.y + 0, 275, 425 };
	window_entity_spawner.is_active = true;
	window_entity_spawner.text = "Entity Spawner";
	entity_spawner_controls.push_back(&window_entity_spawner);

	checkbox_renderable.bounds = { anchor_EntitySpawner.x + 5, anchor_EntitySpawner.y + 90, 12, 12 };
	checkbox_renderable.checked = false;
	checkbox_renderable.text = "Renderable";
	entity_spawner_controls.push_back(&checkbox_renderable);

	checkbox_grid_transform.bounds = { anchor_EntitySpawner.x + 5, anchor_EntitySpawner.y + 300, 12, 12 };
	checkbox_grid_transform.checked = false;
	checkbox_grid_transform.text = "Grid Transform";
	entity_spawner_controls.push_back(&checkbox_grid_transform);

	checkbox_unit.bounds = { anchor_EntitySpawner.x + 5, anchor_EntitySpawner.y + 360, 12, 12 };
	checkbox_unit.checked = false;
	checkbox_unit.text = "Unit";
	entity_spawner_controls.push_back(&checkbox_unit);

	checkbox_is_active.bounds = { anchor_EntitySpawner.x + 5, anchor_EntitySpawner.y + 30, 12, 12 };
	checkbox_is_active.checked = false;
	checkbox_is_active.text = "is_active";
	entity_spawner_controls.push_back(&checkbox_is_active);

	checkbox_health.bounds = { anchor_EntitySpawner.x + 5 + 275, anchor_EntitySpawner.y + 5, 12, 12 };
	checkbox_health.checked = false;
	checkbox_health.text = "Health";
	entity_spawner_controls.push_back(&checkbox_health);

	vb_health.bounds = { anchor_EntitySpawner.x + 5 + 275 + 105, checkbox_health.bounds.y, 30, 20 };
	vb_health.value = 5;
	vb_health.text = "";
	vb_health.min = 0;
	vb_health.max = 100;
	vb_health.edit_mode = false;
	entity_spawner_controls.push_back(&vb_health);

	checkbox_attack.bounds = { anchor_EntitySpawner.x + 5 + 275, anchor_EntitySpawner.y + 30, 12, 12 };
	checkbox_attack.checked = false;
	checkbox_attack.text = "Attack";
	entity_spawner_controls.push_back(&checkbox_attack);

	vb_atk_dmg.bounds = { anchor_EntitySpawner.x + 5 + 275 + 105, checkbox_attack.bounds.y, 30, 20 };
	vb_atk_dmg.value = 1;
	vb_atk_dmg.text = "Damage";
	vb_atk_dmg.min = 0;
	vb_atk_dmg.max = 100;
	vb_atk_dmg.edit_mode = false;
	entity_spawner_controls.push_back(&vb_atk_dmg);

	vb_atk_rng.bounds = { anchor_EntitySpawner.x + 5 + 275 + 175, checkbox_attack.bounds.y, 30, 20 };
	vb_atk_rng.value = 1;
	vb_atk_rng.text = "Range";
	vb_atk_rng.min = 0;
	vb_atk_rng.max = 100;
	vb_atk_rng.edit_mode = false;
	entity_spawner_controls.push_back(&vb_atk_rng);

	checkbox_faction.bounds = { anchor_EntitySpawner.x + 5 + 275, anchor_EntitySpawner.y + 55, 12, 12 };
	checkbox_faction.checked = false;
	checkbox_faction.text = "Faction";
	entity_spawner_controls.push_back(&checkbox_faction);

	tb_faction_name.bounds = { anchor_EntitySpawner.x + 5 + 275 + 60, checkbox_faction.bounds.y, 125, 25 };
	tb_faction_name.edit_mode = false;
	tb_faction_name.text = (char*)calloc(entity_spawner_text_size, sizeof(char));
	strcpy_s(tb_faction_name.text, entity_spawner_text_size, "Friendly");
	tb_faction_name.text_size = entity_spawner_text_size;
	entity_spawner_controls.push_back(&tb_faction_name);

	line_0.bounds = { anchor_EntitySpawner.x + 0, anchor_EntitySpawner.y + 80, 275, 25 };
	entity_spawner_controls.push_back(&line_0);

	line_1.bounds = { anchor_EntitySpawner.x + 0, anchor_EntitySpawner.y + 290, 275, 20 };
	entity_spawner_controls.push_back(&line_1);

	line_2.bounds = { anchor_EntitySpawner.x + 0, anchor_EntitySpawner.y + 350, 275, 20 };
	entity_spawner_controls.push_back(&line_2);

	line_3.bounds = { anchor_EntitySpawner.x + 0, anchor_EntitySpawner.y + 380, 275, 20 };
	entity_spawner_controls.push_back(&line_3);

	color_picker_entity_spawner.bounds = { anchor_EntitySpawner.x + 15, anchor_EntitySpawner.y + 135, 145, 145 };
	color_picker_entity_spawner.color = WHITE;
	entity_spawner_controls.push_back(&color_picker_entity_spawner);

	textbox_entity_name.bounds = { anchor_EntitySpawner.x + 5, anchor_EntitySpawner.y + 50, 125, 25 };
	textbox_entity_name.edit_mode = false;
	textbox_entity_name.text = (char*)calloc(entity_spawner_text_size, sizeof(char));
	strcpy_s(textbox_entity_name.text, entity_spawner_text_size, "Unnamed");
	textbox_entity_name.text_size = entity_spawner_text_size;
	entity_spawner_controls.push_back(&textbox_entity_name);

	textbox_grid_pos.bounds = { anchor_EntitySpawner.x + 5, anchor_EntitySpawner.y + 320, 125, 25 };
	textbox_grid_pos.edit_mode = false;
	textbox_grid_pos.text = (char*)calloc(entity_spawner_text_size, sizeof(char));
	strcpy_s(textbox_grid_pos.text, entity_spawner_text_size, "x, y");
	textbox_grid_pos.text_size = entity_spawner_text_size;
	entity_spawner_controls.push_back(&textbox_grid_pos);

	spinner_texture_select.bounds = { anchor_EntitySpawner.x + 90, anchor_EntitySpawner.y + 100, 100, 25 };
	spinner_texture_select.edit_mode = false;
	spinner_texture_select.text = "Texture Select";
	spinner_texture_select.value = 0;
	spinner_texture_select.min = 0;
	spinner_texture_select.max = gs->textures.size() - 1;
	entity_spawner_controls.push_back(&spinner_texture_select);

	button_spawn_entity.bounds = { anchor_EntitySpawner.x + 5, anchor_EntitySpawner.y + 390, 125, 25 };
	button_spawn_entity.text = "Spawn Entity";
	entity_spawner_controls.push_back(&button_spawn_entity);

	render_texture = LoadRenderTexture(game_window.width, game_window.height);
}

// Systems ================================================================

void BattleScene::Update() {
	float dt = GetFrameTime();

	// See what actions need to be performed
	while (!action_queue.empty()) {
		auto& action = action_queue.front();

		// Debugging Actions
		if (action.action == "DEBUG") {
			debug = action.type == ActionType::START;
		}

		// IO
		if (action.action == "SAVEGAME") {
			save = action.type == ActionType::END;
		}
		if (action.action == "LOADGAME") {
			load = action.type == ActionType::END;
		}
		if (action.action == "DELETESAVE") {
			clear_save = action.type == ActionType::END;
		}

		// Camera Actions
		if (action.action == "CAMERA_UP") {
			camera_up = action.type == ActionType::START;
		}
		if (action.action == "CAMERA_DOWN") {
			camera_down = action.type == ActionType::START;
		}
		if (action.action == "CAMERA_LEFT") {
			camera_left = action.type == ActionType::START;
		}
		if (action.action == "CAMERA_RIGHT") {
			camera_right = action.type == ActionType::START;
		}
		if (action.action == "CAMERA_BOOST") {
			camera_boost = action.type == ActionType::START;
		}
		if (action.action == "CAMERA_ZOOM_IN") {
			camera_zoom_in = action.type == ActionType::START;
		}
		if (action.action == "CAMERA_ZOOM_OUT") {
			camera_zoom_out = action.type == ActionType::START;
		}

		// Entity Actions
		if (action.action == "ENTITY_UP") {
			entity_up = action.type == ActionType::END;
		}
		if (action.action == "ENTITY_DOWN") {
			entity_down = action.type == ActionType::END;
		}
		if (action.action == "ENTITY_LEFT") {
			entity_left = action.type == ActionType::END;
		}
		if (action.action == "ENTITY_RIGHT") {
			entity_right = action.type == ActionType::END;
		}
		if (action.action == "ENTITY_SELECT") {
			entity_select = action.type == ActionType::END;
		}
		if (action.action == "ENTITY_ACTION") {
			entity_action = action.type == ActionType::END;
		}
		if (action.action == "RESET_MOVEMENT") {
			reset_movement = action.type == ActionType::END;
		}

		action_queue.pop();
	}

	// Update the camera
	const float base_speed = 50;
	const float speed_multiplier = 10;

	float speed = base_speed;
	if (camera_boost) {
		speed *= speed_multiplier;
	}

	if (camera_left) {
		camera.target.x -= speed * 2 * dt;
	}
	else if (camera_right) {
		camera.target.x += speed * 2 * dt;
	}
	if (camera_up) {
		camera.target.y -= speed * 2 * dt;
	}
	else if (camera_down) {
		camera.target.y += speed * 2 * dt;
	}
	if ((camera_was_moving && !camera_up && !camera_down && !camera_left && !camera_right)) {
		camera.target.x = roundf(camera.target.x);
		camera.target.y = roundf(camera.target.y);
	}

	camera_was_moving = camera_up || camera_down || camera_left || camera_right;


	float mouse_wheel_delta = GetMouseWheelMove();
	if (mouse_wheel_delta > 0 || mouse_wheel_delta < 0) {
		camera.zoom += mouse_wheel_delta / 10;
		if (camera.zoom < 0.3f) {
			camera.zoom = 0.3f;
		}
		else if (camera.zoom > 2.0f) {
			camera.zoom = 2.0f;
		}
	}

	if (camera_zoom_in) {
		camera.zoom += speed * 0.1f * dt;
	}
	else if (camera_zoom_out) {
		camera.zoom -= speed * 0.1f * dt;
		if (camera.zoom < 0.3f) {
			camera.zoom = 0.3f;
		}
		else if (camera.zoom > 2.0f) {
			camera.zoom = 2.0f;
		}
	}

	// Update the mouse position
	mouse_pos = GetMousePosition();

	Vector2 test = mouse_pos;
	test -= game_origin;

	// Convert mouse location to a world position
	world_pos = GetScreenToWorld2D(test, camera);

	// Convert world location to a grid position
	grid_pos.x = (int)floorf(world_pos.x / (float)gs->entity_scale);
	grid_pos.y = (int)floorf(world_pos.y / (float)gs->entity_scale);

	if (em.entities.size() >= 1) {
		// Select an entity
		if (entity_select) {
			for (int i = 0; i < em.entities.size(); i++) {
				if (em.entities[i].grid_transform >= 0) {
					if (grid_pos == em.c_grid_transforms[em.entities[i].grid_transform].pos) {
						selected_entity = i;
					}
				}
			}
			entity_select = false;
		}

		Entity& e = em.entities[selected_entity];
		if (e.grid_transform >= 0) {
			if (entity_left) {
				em.GridTransform(e).pos.x -= 1;
				entity_left = false;
			}
			if (entity_right) {
				em.GridTransform(e).pos.x += 1;
				entity_right = false;
			}
			if (entity_up) {
				em.GridTransform(e).pos.y -= 1;
				entity_up = false;
			}
			if (entity_down) {
				em.GridTransform(e).pos.y += 1;
				entity_down = false;
			}

			if (e.unit >= 0) {
				// Reset movement points of the current unit
				if (reset_movement) {
					em.Unit(e).current_movement_points = em.Unit(e).movement_points;
					reset_movement = false;
				}

				// Move the unit
				if (entity_action) {
					Vector2 source = em.GridTransform(e).pos;
					Vector2 dest = grid_pos;
					int movement_points = em.Unit(e).current_movement_points;
					
					AStarContext asc;
					asc.found_path = false;
					asc.start = { (int)source.x, (int)source.y };
					asc.goal = { (int)dest.x, (int)dest.y };
					asc.remaining_movement_points = movement_points;
					asc.gm = &map;
					AStar(asc);
					if (asc.found_path) {
						std::cout << "Found Path\n";
						while (asc.path.size() > 0) {
							int dir = asc.path.front();
							asc.path.pop_front();
							switch (dir) {
								case 1: em.GridTransform(e).pos.y -= 1.0f; std::cout << dir << "\n"; break;
								case 2: em.GridTransform(e).pos.y += 1.0f; std::cout << dir << "\n"; break;
								case 3: em.GridTransform(e).pos.x -= 1.0f; std::cout << dir << "\n"; break;
								case 4: em.GridTransform(e).pos.x += 1.0f; std::cout << dir << "\n"; break;
							}
						}
						em.Unit(e).current_movement_points = asc.remaining_movement_points;
					}
					else {
						std::cout << "Did not find path\n";
					}

					entity_action = false;
				}
			}

			// Setup rendering information
			if (e.renderable >= 0) {
				em.Renderable(e).pos = em.GridTransform(e).pos * gs->entity_scale;
			}
		}
	}

	if (save) {
		WriteEntityToFile();
		save = false;
	}
	else if (load) {
		ReadEntityFromFile("entity.txt");
		map.LoadMap("map.png");
		load = false;
	}
	if (clear_save) {
		remove("entity.txt");
		clear_save = false;
	}

	// Debug
	if (debug) {
		debug = false;
		__debugbreak();
	}
}

void BattleScene::Render() {
	// Rendering Code =====================================================

	BeginTextureMode(render_texture);
	ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
	BeginMode2D(camera);

	for (auto& tile : map.tiles) {
		size_t tex_handle = 0;
		switch (tile.second.terrain_type) {
			case 0: tex_handle = gs->texture_handles["grass"]; break;
			case 1: tex_handle = gs->texture_handles["water"]; break;
			case 2: tex_handle = gs->texture_handles["tree"]; break;
		}

		Vector2 pos = tile.second.pos;
		pos *= gs->entity_scale;
		DrawTextureEx(gs->textures[tex_handle], pos, 0.0f, 1.0f, WHITE);
	}

	DrawGridLines();

	DrawText("This is the game window", 190, 200, 20, LIGHTGRAY);

	for (Entity& e : em.entities) {
		if (e.unit >= 0 && e.renderable >= 0) {
			cUnit& c = em.Unit(e);
			cRenderable& r = em.Renderable(e);

			Color temp_r = WHITE;
			temp_r.a = 128; // set transparency to half

			int movement_color = gs->texture_handles["Movement"];
			int attack_color = gs->texture_handles["Attack"];

			FloodFillContext ffc;
			ffc.remaining_movement_points = c.current_movement_points;
			ffc.start = em.GridTransform(e).pos;
			ffc.gm = &map;
			FloodFill(ffc);

			for (auto node : ffc.visited) {
				Vector2 pos = node;
				pos *= gs->entity_scale;
				DrawTextureEx(gs->textures[movement_color], pos, 0.0f, 1.0f, temp_r);
			}

			for (auto node : ffc.edge_frontier) {
				Vector2 pos = node;
				pos *= gs->entity_scale;
				DrawTextureEx(gs->textures[attack_color], pos, 0.0f, 1.0f, temp_r);
			}

			// Show path to mouse cursor
			if (grid_pos != em.GridTransform(e).pos) {
				Vector2 source = em.GridTransform(e).pos;
				Vector2 dest = grid_pos;
				int movement_points = em.Unit(e).current_movement_points;

				// Build path from unit to cursor
				// BuildPathContext bpc = BuildPath(source, dest, movement_points);
				//if (bpc.found_path) {
				
				AStarContext asc;
				asc.found_path = false;
				asc.start = { (int)source.x, (int)source.y };
				asc.goal = { (int)dest.x, (int)dest.y };
				asc.remaining_movement_points = movement_points;
				asc.gm = &map;
				AStar(asc);
				if (asc.found_path) {
					// Get texture handles for drawing the path
					int arrow_butt = gs->texture_handles["arrow_butt"];
					int arrow_head = gs->texture_handles["arrow_head"];
					int arrow_shaft = gs->texture_handles["arrow_shaft"];
					int arrow_bend = gs->texture_handles["arrow_bend"];
					int cursor_tile = gs->texture_handles["cursor_tile"];

					// Draw the path arrow
					Vector2 ghost = em.GridTransform(e).pos;

					// Parameters for the drawing
					Rectangle src = { 0, 0, 16, 16 };
					Vector2 origin = { src.width, src.height };
					Vector2 pos = ghost * gs->entity_scale;
					Rectangle dest = { pos.x + src.width, pos.y + src.height, src.width * 2.0f, src.height * 2.0f };

					// Draw the arrow butt underneath the unit
					switch (asc.path.front()) {
						case 1:
						{
							DrawTexturePro(gs->textures[arrow_butt], src, dest, origin, 0.0f, WHITE);
							ghost.y -= 1.0f;
						} break;
						case 2:
						{
							DrawTexturePro(gs->textures[arrow_butt], src, dest, origin, 180.0f, WHITE);
							ghost.y += 1.0f;
						} break;
						case 3:
						{
							DrawTexturePro(gs->textures[arrow_butt], src, dest, origin, 270.0f, WHITE);
							ghost.x -= 1.0f;
						} break;
						case 4:
						{
							DrawTexturePro(gs->textures[arrow_butt], src, dest, origin, 90.0f, WHITE);
							ghost.x += 1.0f;
						} break;
					}

					// Draw the first segment that connects to the butt
					for (int i = 1; i < asc.path.size(); i++) {
						pos = ghost * gs->entity_scale;
						dest = { pos.x + src.width, pos.y + src.height, src.width * 2.0f, src.height * 2.0f };

						// continuing in the same direction, use arrow_shaft
						if (asc.path[i] == asc.path[i - 1]) {
							switch (asc.path[i]) {
								case 1:
								{
									DrawTexturePro(gs->textures[arrow_shaft], src, dest, origin, 0.0f, WHITE);
									ghost.y -= 1.0f;
								} break;
								case 2:
								{
									DrawTexturePro(gs->textures[arrow_shaft], src, dest, origin, 180.0f, WHITE);
									ghost.y += 1.0f;
								} break;
								case 3:
								{
									DrawTexturePro(gs->textures[arrow_shaft], src, dest, origin, 270.0f, WHITE);
									ghost.x -= 1.0f;
								} break;
								case 4:
								{
									DrawTexturePro(gs->textures[arrow_shaft], src, dest, origin, 90.0f, WHITE);
									ghost.x += 1.0f;
								} break;
							}
						}
						// changing the direction, use arrow_bend
						if (asc.path[i] != asc.path[i - 1]) {
							switch (asc.path[i]) {
								case 1:
								{
									if (asc.path[i - 1] == 3) {
										DrawTexturePro(gs->textures[arrow_bend], src, dest, origin, 270.0f, WHITE);
										ghost.y -= 1.0f;
									}
									else if (asc.path[i - 1] == 4) {
										DrawTexturePro(gs->textures[arrow_bend], src, dest, origin, 180.0f, WHITE);
										ghost.y -= 1.0f;
									}
								} break;
								case 2:
								{
									if (asc.path[i - 1] == 3) {
										DrawTexturePro(gs->textures[arrow_bend], src, dest, origin, 0.0f, WHITE);
										ghost.y += 1.0f;
									}
									else if (asc.path[i - 1] == 4) {
										DrawTexturePro(gs->textures[arrow_bend], src, dest, origin, 90.0f, WHITE);
										ghost.y += 1.0f;
									}
								} break;
								case 3:
								{
									if (asc.path[i - 1] == 1) {
										DrawTexturePro(gs->textures[arrow_bend], src, dest, origin, 90.0f, WHITE);
										ghost.x -= 1.0f;
									}
									else if (asc.path[i - 1] == 2) {
										DrawTexturePro(gs->textures[arrow_bend], src, dest, origin, 180.0f, WHITE);
										ghost.x -= 1.0f;
									}
								} break;
								case 4:
								{
									if (asc.path[i - 1] == 1) {
										DrawTexturePro(gs->textures[arrow_bend], src, dest, origin, 0.0f, WHITE);
										ghost.x += 1.0f;
									}
									else if (asc.path[i - 1] == 2) {
										DrawTexturePro(gs->textures[arrow_bend], src, dest, origin, 270.0f, WHITE);
										ghost.x += 1.0f;
									}
								} break;
							}
						}
					}

					// Draw the arrow head where the cursor is
					pos = ghost * gs->entity_scale;
					dest = { pos.x + src.width, pos.y + src.height, src.width * 2.0f, src.height * 2.0f };
					switch (asc.path.back()) {
						case 1:
						{
							DrawTexturePro(gs->textures[arrow_head], src, dest, origin, 0.0f, WHITE);
						} break;
						case 2:
						{
							DrawTexturePro(gs->textures[arrow_head], src, dest, origin, 180.0f, WHITE);
						} break;
						case 3:
						{
							DrawTexturePro(gs->textures[arrow_head], src, dest, origin, 270.0f, WHITE);
						} break;
						case 4:
						{
							DrawTexturePro(gs->textures[arrow_head], src, dest, origin, 90.0f, WHITE);
						} break;
					}
				}
			}
		}

		if (e.renderable >= 0) {
			cRenderable& r = em.Renderable(e);
			DrawTextureEx(gs->textures[r.texture_handle], r.pos, 0.0f, 1.0f, r.tint_color);
		}
	}

	EndMode2D();
	EndTextureMode();

	BeginDrawing();
	ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

	// Draw Game Region ===================================================

	DrawRectangleLines(game_window.x - 1, game_window.y - 1, game_window.width + 2, game_window.height + 2, GRAY);
	DrawTexturePro(render_texture.texture, { 0, 0, game_width, -game_height }, game_window, { 0, 0 }, 0.0f, WHITE);

	// Draw Debug Region ==================================================
	DrawText("This is the debug window", anchor01.x + 10, anchor01.y + 200, 20, LIGHTGRAY);

	DrawText("Controls:", anchor02.x, anchor02.y + 10, 20, GRAY);
	DrawText("Press O to save the currently spawned entities", anchor02.x, anchor02.y + 30, 20, GRAY);
	DrawText("Press I to load entities that were saved", anchor02.x, anchor02.y + 50, 20, GRAY);
	DrawText("Press U to clear the save file", anchor02.x, anchor02.y + 70, 20, GRAY);

	DrawText("WASD to move the first blue square", anchor02.x, anchor02.y + 100, 20, GRAY);
	DrawText("Arrow keys to move the camera", anchor02.x, anchor02.y + 120, 20, GRAY);
	DrawText("Holding Shift makes blue square and camera move faster", anchor02.x, anchor02.y + 140, 20, GRAY);

	// raygui: controls drawing
	//----------------------------------------------------------------------------------
	label_mouse_pos.text.clear();
	label_mouse_pos.text += "Mouse Pos: ";
	label_mouse_pos.text += std::to_string(mouse_pos.x);
	label_mouse_pos.text += ", ";
	label_mouse_pos.text += std::to_string(mouse_pos.y);
	label_mouse_pos.text += ", Zoom: ";
	label_mouse_pos.text += std::to_string(camera.zoom);

	label_world_pos.text.clear();
	label_world_pos.text += "World Pos: ";
	label_world_pos.text += std::to_string(world_pos.x);
	label_world_pos.text += ", ";
	label_world_pos.text += std::to_string(world_pos.y);

	label_grid_pos.text.clear();
	label_grid_pos.text += "Grid Pos: ";
	label_grid_pos.text += std::to_string(grid_pos.x);
	label_grid_pos.text += ", ";
	label_grid_pos.text += std::to_string(grid_pos.y);

	label_selected_entity.text.clear();
	label_selected_entity.text += "Selected Entity: ";
	label_selected_entity.text += std::to_string(selected_entity);

	label_num_entities.text.clear();
	label_num_entities.text += "Num Entities: ";
	label_num_entities.text += std::to_string(em.entities.size());

	label_unit_movement_points.text.clear();
	label_unit_movement_points.text += "Current Movement Points: ";
	if (selected_entity >= 0 && em.entities[selected_entity].unit >= 0) {
		label_unit_movement_points.text += std::to_string(em.c_units[selected_entity].current_movement_points);
	}

	for (int i = 0; i < debug_gui_controls.size(); i++) {
		debug_gui_controls[i]->Draw();
	}

	if (checkbox_unit.checked) {
		checkbox_health.checked = true;
		checkbox_attack.checked = true;
		checkbox_faction.checked = true;
	}

	// Entity Spawner
	if (window_entity_spawner.is_active) {
		spinner_texture_select.max = gs->textures.size() - 1;

		for (int i = 0; i < entity_spawner_controls.size(); i++) {
			entity_spawner_controls[i]->Draw();
		}

		if (button_spawn_entity.pressed) {
			IVector2 gt_pos = { 0, 0 };
			{
				std::string text = textbox_grid_pos.text;
				std::string ignore;
				std::stringstream gt_input_converter(text);
				gt_input_converter >> gt_pos.x >> ignore >> gt_pos.y;
			}

			EntityContext ec;
			ec.is_active = checkbox_is_active.checked;
			ec.name = textbox_entity_name.text;
			ec.renderable = checkbox_renderable.checked;
			ec.texture_scale = gs->entity_scale;
			ec.texture_handle = (size_t)spinner_texture_select.value;
			ec.tint_color = color_picker_entity_spawner.color;
			ec.grid_transform = checkbox_grid_transform.checked;
			ec.gt_pos = gt_pos;
			ec.unit = checkbox_unit.checked;
			
			// for now just use some hardcoded values for health, attack, and faction
			ec.attack = checkbox_attack.checked;
			ec.attack_damage = vb_atk_dmg.value;
			ec.attack_range = vb_atk_rng.value;

			ec.health = checkbox_health.checked;
			ec.health_max = vb_health.value;

			ec.faction = checkbox_faction.checked;
			ec.faction_name = tb_faction_name.text;

			selected_entity = em.CreateEntity(ec);
		}

		Vector2 texture_preview_pos = { color_picker_entity_spawner.bounds.x + color_picker_entity_spawner.bounds.width + 40, color_picker_entity_spawner.bounds.y };
		DrawTextureEx(gs->textures[spinner_texture_select.value], texture_preview_pos, 0.0f, 2.0f, color_picker_entity_spawner.color);
	}

	//----------------------------------------------------------------------------------

	EndDrawing();
}

void BattleScene::DrawGridLines() {
	float spacing = gs->entity_scale;

	// Draw the vertical lines
	float min = camera.target.x;
	min = ceilf(min / spacing) * spacing;
	float max = camera.target.x + game_width / camera.zoom;
	max = ceilf(max / spacing) * spacing;

	if (IsKeyPressed(KEY_B)) printf("min: %f, max: %f\n", min, max);

	for (float i = min; i < max; i += spacing) {
		Vector2 begin = { i, camera.target.y };
		Vector2 end = { i, camera.target.y + game_height / camera.zoom };

		DrawLineV(begin, end, LIGHTGRAY);
	}

	// Draw the horizontal lines
	min = camera.target.y;
	min = ceilf(min / spacing) * spacing;
	max = camera.target.y + game_height / camera.zoom;
	max = ceilf(max / spacing) * spacing;

	for (float i = min; i < max; i += spacing) {
		Vector2 begin = { camera.target.x, i };
		Vector2 end = { camera.target.x + game_width / camera.zoom, i };

		DrawLineV(begin, end, LIGHTGRAY);
	}
}

// File I/O ===================================================================

// This function is meant as a testbed for saving Entity data to a file so that
// it can be reloaded later.
void BattleScene::WriteEntityToFile() {
	std::fstream file("entity.txt", std::ios::out);

	file << "selected_entity = " << selected_entity << " ;\n";

	for (Entity& e : em.entities) {
		file << "entity = [\n";
		file << "\tname = " << e.name << " ;\n";
		file << "\tid = " << e.id << " ;\n";
		file << "\tis_active = " << e.is_active << " ;\n";
		if (e.grid_transform != -1) {
			file << "\t" << em.GridTransform(e).ToString() << "\n";
		}
		if (e.renderable != -1) {
			file << "\t" << em.Renderable(e).ToString() << "\n";
		}
		if (e.unit != -1) {
			file << "\t" << em.Unit(e).ToString() << "\n";
		}
		if (e.health != -1) {
			file << "\t" << em.Health(e).ToString() << "\n";
		}
		if (e.attack != -1) {
			file << "\t" << em.Attack(e).ToString() << "\n";
		}
		if (e.faction != -1) {
			file << "\t" << em.Faction(e).ToString() << "\n";
		}
		file << "];\n";
	}

	file.close();
}

// This function is meant as a testbed for loading Entity data from a file to
// populate the GameState.
void BattleScene::ReadEntityFromFile(std::string filename) {
	std::cout << "in read entity from file\n\n";
	std::fstream file(filename, std::ios::in);
	std::string file_contents;
	std::string ignore_string;

	Entity* e;

	while (file.good()) {
		file >> file_contents;

		if (file_contents == "selected_entity") {
			// ignore the "="
			file >> ignore_string;
			file >> selected_entity;
			file >> ignore_string;
		}
		else if (file_contents == "entity") {
			e = new Entity;
			// We want to ignore the "= ["
			file >> ignore_string >> ignore_string;

			while (file.good()) {
				// we hit our first entity variable
				file >> file_contents;
				if (file_contents == "name") {
					// ignore the =
					file >> ignore_string;
					// load the name
					file >> e->name;
					// ignore the ;
					file >> ignore_string;
				}
				else if (file_contents == "id") {
					// ignore the =
					file >> ignore_string;
					// load the id
					file >> e->id;
					// ignore the ;
					file >> ignore_string;
				}
				else if (file_contents == "is_active") {
					// ignore the =
					file >> ignore_string;
					// load the activity state
					file >> e->is_active;
					// ignore the ;
					file >> ignore_string;
				}
				else if (file_contents == "component") {
					// we found a component to load
					file >> file_contents;
					if (file_contents == "grid_transform") {
						// ignore the "= ["
						file >> ignore_string >> ignore_string;

						// need to load the grid_transform component
						cGridTransform t;
						file >> t.pos.x >> ignore_string >> t.pos.y;

						// ignore the "] ;"
						file >> ignore_string >> ignore_string;

						e->grid_transform = em.AddGridTransform(t);
					}
					else if (file_contents == "renderable") {
						// ignore the "= ["
						file >> ignore_string >> ignore_string;

						// need to load the renderable component
						cRenderable r;
						file >> r.pos.x >> ignore_string >> r.pos.y >> ignore_string >> r.texture_handle >> ignore_string >> r.tint_color;

						// ignore the "] ;"
						file >> ignore_string >> ignore_string;

						e->renderable = em.AddRenderable(r);
					}
					else if (file_contents == "unit") {
						// ignore the "= ["
						file >> ignore_string >> ignore_string;

						// need to load the renderable component
						cUnit u;
						//size_t num_waypoints = 0;
						file >> u.current_movement_points >> ignore_string >> u.movement_points >> ignore_string;

						/*
						for (int i = 0; i < num_waypoints; i++) {
							Vector2 v = {};
							file >> v.x >> ignore_string >> v.y >> ignore_string;
							u.waypoint_pos.push_back(v);
						}
						*/
						// ignore the "] ;"
						file >> ignore_string >> ignore_string;

						e->unit = em.AddUnit(u);
					}
					else if (file_contents == "health") {
						// ignore the "= ["
						file >> ignore_string >> ignore_string;
						
						// need to load the health component
						cHealth h;
						file >> h.current >> ignore_string >> h.max;

						// ignore the "] ;"
						file >> ignore_string >> ignore_string;

						e->health = em.AddHealth(h);
					}
					else if (file_contents == "attack") {
						// ignore the "= ["
						file >> ignore_string >> ignore_string;

						// need to load the health component
						cAttack a;
						file >> a.damage >> ignore_string >> a.range;

						// ignore the "] ;"
						file >> ignore_string >> ignore_string;

						e->attack = em.AddAttack(a);
					}
					else if (file_contents == "faction") {
						// ignore the "= ["
						file >> ignore_string >> ignore_string;

						// need to load the health component
						cFaction f;
						file >> f.faction;

						// ignore the "] ;"
						file >> ignore_string >> ignore_string;

						e->faction = em.AddFaction(f);
					}
				}
				else if (file_contents == "];") {
					Entity e_final = *e;
					em.entities.push_back(e_final);
					break;
				}
			}
		}
	}

	std::cout << "\n\n";
}