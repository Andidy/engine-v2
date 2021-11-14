#include "game.h"

void GameState::RegisterAction(int input_type, int keycode, std::string action_name) {
	switch (input_type) {
		case 0: // keyboard
		{
			keycode = rl_KeyboardToCode(keycode);
		} break;
		case 1: // mouse
		{
			keycode = rl_MouseToCode(keycode);
		} break;
		case 2: // controller
		{
			keycode = rl_ControllerToCode(keycode);
		} break;
		case 3: // controller axis
		{
			keycode = rl_CodeToControllerAxis(keycode);
		} break;
		default: __debugbreak(); // lol crashing 
	}
	action_map[keycode] = action_name;
}

void GameUpdate(GameState* gs) {
	float dt = GetFrameTime();
	const float base_speed = 50;
	const float speed_multiplier = 10;

	// scene
	{
		while (!gs->action_queue.empty()) {
			auto & action = gs->action_queue.front();
			
			// Debugging Actions
			if (action.action == "DEBUG") {
				gs->debug = action.type == ActionType::START;
			}

			// IO
			if (action.action == "SAVEGAME") {
				gs->save = action.type == ActionType::END;
			}
			if (action.action == "LOADGAME") {
				gs->load = action.type == ActionType::END;
			}
			if (action.action == "DELETESAVE") {
				gs->clear_save = action.type == ActionType::END;
			}

			// Camera Actions
			if (action.action == "CAMERA_UP") {
				gs->camera_up = action.type == ActionType::START;
			}
			if (action.action == "CAMERA_DOWN") {
				gs->camera_down = action.type == ActionType::START;
			}
			if (action.action == "CAMERA_LEFT") {
				gs->camera_left = action.type == ActionType::START;
			}
			if (action.action == "CAMERA_RIGHT") {
				gs->camera_right = action.type == ActionType::START;
			}
			if (action.action == "CAMERA_BOOST") {
				gs->camera_boost = action.type == ActionType::START;
			}
			if (action.action == "CAMERA_ZOOM_IN") {
				gs->camera_zoom_in = action.type == ActionType::START;
			}
			if (action.action == "CAMERA_ZOOM_OUT") {
				gs->camera_zoom_out = action.type == ActionType::START;
			}

			// Entity Actions
			if (action.action == "ENTITY_UP") {
				gs->entity_up = action.type == ActionType::END;
			}
			if (action.action == "ENTITY_DOWN") {
				gs->entity_down = action.type == ActionType::END;
			}
			if (action.action == "ENTITY_LEFT") {
				gs->entity_left = action.type == ActionType::END;
			}
			if (action.action == "ENTITY_RIGHT") {
				gs->entity_right = action.type == ActionType::END;
			}
			if (action.action == "ENTITY_SELECT") {
				gs->entity_select = action.type == ActionType::END;
			}
			if (action.action == "ENTITY_ACTION") {
				gs->entity_action = action.type == ActionType::END;
			}
			if (action.action == "RESET_MOVEMENT") {
				gs->reset_movement = action.type == ActionType::END;
			}

			gs->action_queue.pop();
		}
	}

	float speed = base_speed;
	if (gs->camera_boost) {
		speed *= speed_multiplier;
	}

	if (gs->camera_left) {
		gs->camera.target.x -= speed * 2 * dt;
	}
	else if (gs->camera_right) {
		gs->camera.target.x += speed * 2 * dt;
	}
	if (gs->camera_up) {
		gs->camera.target.y -= speed * 2 * dt;
	}
	else if (gs->camera_down) {
		gs->camera.target.y += speed * 2 * dt;
	}
	if ((gs->camera_was_moving && !gs->camera_up && !gs->camera_down && !gs->camera_left && !gs->camera_right)) {
		gs->camera.target.x = roundf(gs->camera.target.x);
		gs->camera.target.y = roundf(gs->camera.target.y);
	}
	
	gs->camera_was_moving = gs->camera_up || gs->camera_down || gs->camera_left || gs->camera_right;


	float mouse_wheel_delta = GetMouseWheelMove();
	if (mouse_wheel_delta > 0 || mouse_wheel_delta < 0) {
		gs->camera.zoom += mouse_wheel_delta / 10;
		if (gs->camera.zoom < 0.3f) {
			gs->camera.zoom = 0.3f;
		}
		else if (gs->camera.zoom > 2.0f) {
			gs->camera.zoom = 2.0f;
		}
	}

	if (gs->camera_zoom_in) {
		gs->camera.zoom += speed * 0.1f * dt;
	}
	else if (gs->camera_zoom_out) {
		gs->camera.zoom -= speed * 0.1f * dt;
		if (gs->camera.zoom < 0.3f) {
			gs->camera.zoom = 0.3f;
		}
		else if (gs->camera.zoom > 2.0f) {
			gs->camera.zoom = 2.0f;
		}
	}

	// Update the mouse position
	gs->mouse_pos = GetMousePosition();
	
	Vector2 test = gs->mouse_pos;
	test -= gs->game_origin;
	
	// Convert mouse location to a world position
	gs->world_pos = GetScreenToWorld2D(test, gs->camera);

	// Convert world location to a grid position
	gs->grid_pos.x = (int)floorf(gs->world_pos.x / (float)gs->entity_scale);
	gs->grid_pos.y = (int)floorf(gs->world_pos.y / (float)gs->entity_scale);
	
	if (gs->em.entities.size() >= 1) {
		if (gs->entity_select) {
			for (int i = 0; i < gs->em.entities.size(); i++) {
				if (gs->em.entities[i].grid_transform >= 0) {
					if (gs->grid_pos == gs->em.c_grid_transforms[gs->em.entities[i].grid_transform].pos) {
						gs->selected_entity = i;
					}
				}
			}
			gs->entity_select = false;
		}

		Entity& e = gs->em.entities[gs->selected_entity];
		if (e.grid_transform >= 0) {
			if (gs->entity_left) {
				gs->em.GridTransform(e).pos.x -= 1;
				gs->entity_left = false;
			}
			if (gs->entity_right) {
				gs->em.GridTransform(e).pos.x += 1;
				gs->entity_right = false;
			}
			if (gs->entity_up) {
				gs->em.GridTransform(e).pos.y -= 1;
				gs->entity_up = false;
			}
			if (gs->entity_down) {
				gs->em.GridTransform(e).pos.y += 1;
				gs->entity_down = false;
			}

			if (e.unit >= 0) {
				if (gs->reset_movement) {
					gs->em.Unit(e).current_movement_points = gs->em.Unit(e).movement_points;
					gs->reset_movement = false;
				}

				if (gs->entity_action) {
					Vector2 source = gs->em.GridTransform(e).pos;
					Vector2 dest = gs->grid_pos;
					int movement_points = gs->em.Unit(e).current_movement_points;
					BuildPathContext bpc = BuildPath(source, dest, movement_points);
					if (bpc.found_path) {
						std::cout << "Found Path\n";
						while (bpc.orders.size() > 0) {
							int dir = bpc.orders.front();
							bpc.orders.pop_front();
							switch (dir) {
								case 1: gs->em.GridTransform(e).pos.y -= 1.0f; std::cout << dir << "\n"; break;
								case 2: gs->em.GridTransform(e).pos.y += 1.0f; std::cout << dir << "\n"; break;
								case 3: gs->em.GridTransform(e).pos.x -= 1.0f; std::cout << dir << "\n"; break;
								case 4: gs->em.GridTransform(e).pos.x += 1.0f; std::cout << dir << "\n"; break;
							}
						}
						gs->em.Unit(e).current_movement_points = bpc.remaining_movement_points;
					}
					else {
						std::cout << "Did not find path\n";
					}

					gs->entity_action = false;
				}
			}

			if (e.renderable >= 0) {
				gs->em.Renderable(e).pos = gs->em.GridTransform(e).pos * gs->entity_scale;
			}
		}
	}

	if (gs->save) {
		WriteEntityToFile(gs);
		gs->save = false;
	}
	else if (gs->load) {
		ReadEntityFromFile(gs, "entity.txt");
		gs->load = false;
	}
	if (gs->clear_save) {
		remove("entity.txt");
		gs->clear_save = false;
	}

	// Debug
	if (gs->debug) {
		gs->debug = false;
		__debugbreak();
	}
}

// This function is meant as a testbed for saving Entity data to a file so that
// it can be reloaded later.
void WriteEntityToFile(GameState* gs) {
	std::fstream file("entity.txt", std::ios::out);
	
	for (Entity& e : gs->em.entities) {
		file << "entity = [\n";
		file << "\tname = " << e.name << " ;\n";
		file << "\tid = " << e.id << " ;\n";
		file << "\tis_active = " << e.is_active << " ;\n";
		if (e.grid_transform != -1) {
			file << "\t" << gs->em.GridTransform(e).ToString() << "\n";
		}
		if (e.renderable != -1) {
			file << "\t" << gs->em.Renderable(e).ToString() << "\n";
		}
		if (e.unit != -1) {
			file << "\t" << gs->em.Unit(e).ToString() << "\n";
		}
		file << "];\n";
	}

	file.close();
}

// This function is meant as a testbed for loading Entity data from a file to
// populate the GameState.
void ReadEntityFromFile(GameState* gs, std::string filename) {
	std::cout << "in read entity from file\n\n";
	std::fstream file(filename, std::ios::in);
	std::string file_contents;
	std::string ignore_string;

	Entity* e;

	while (file.good()) {
		file >> file_contents;

		if (file_contents == "entity") {
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

						e->grid_transform = gs->em.AddGridTransform(t);
					}
					else if (file_contents == "renderable") {
						// ignore the "= ["
						file >> ignore_string >> ignore_string;
						
						// need to load the renderable component
						cRenderable r;
						file >> r.pos.x >> ignore_string >> r.pos.y >> ignore_string >> r.texture_handle >> ignore_string >> r.tint_color;
						
						// ignore the "] ;"
						file >> ignore_string >> ignore_string;

						e->renderable = gs->em.AddRenderable(r);
					}
					else if (file_contents == "unit") {
						// ignore the "= ["
						file >> ignore_string >> ignore_string;
						
						// need to load the renderable component
						cUnit u;
						size_t num_waypoints = 0;
						file >> u.waypoint_active >> ignore_string >> num_waypoints >> ignore_string;

						for (int i = 0; i < num_waypoints; i++) {
							Vector2 v = {};
							file >> v.x >> ignore_string >> v.y >> ignore_string;
							u.waypoint_pos.push_back(v);
						}
					    
						// ignore the "] ;"
						file >> ignore_string >> ignore_string;
						
						e->unit = gs->em.AddUnit(u);
					}
				}
				else if (file_contents == "];") {
					Entity e_final = *e;
					gs->em.entities.push_back(e_final);
					break;
				}
			}
		}
	}

	std::cout << "\n\n";
}