#include "game.h"

void GameUpdate(GameState* gs) {
	float dt = GetFrameTime();
	const float base_speed = 50;
	const float speed_multiplier = 10;

	float speed = base_speed;
	if (IsKeyDown(KEY_LEFT_SHIFT)) {
		speed *= speed_multiplier;
	}

	if (IsKeyDown(KEY_LEFT)) {
		gs->camera.target.x -= speed * 2 * dt;
	}
	else if (IsKeyDown(KEY_RIGHT)) {
		gs->camera.target.x += speed * 2 * dt;
	}
	if (IsKeyDown(KEY_UP)) {
		gs->camera.target.y -= speed * 2 * dt;
	}
	else if (IsKeyDown(KEY_DOWN)) {
		gs->camera.target.y += speed * 2 * dt;
	}
	if ((!IsKeyDown(KEY_DOWN) && !IsKeyDown(KEY_UP) && !IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_LEFT)) &&
		(IsKeyReleased(KEY_DOWN) || IsKeyReleased(KEY_UP) || IsKeyReleased(KEY_RIGHT) || IsKeyReleased(KEY_LEFT))) {
		gs->camera.target.x = roundf(gs->camera.target.x);
		gs->camera.target.y = roundf(gs->camera.target.y);
	}

	float mouse_wheel_delta = GetMouseWheelMove();
	if (mouse_wheel_delta > 0 || mouse_wheel_delta < 0) {
		gs->camera.zoom += mouse_wheel_delta / 10;
	}

	if (IsKeyDown(KEY_PAGE_UP)) {
		gs->camera.zoom += speed * 0.1f * dt;
	}
	else if (IsKeyDown(KEY_PAGE_DOWN)) {
		gs->camera.zoom -= speed * 0.1f * dt;
		if (gs->camera.zoom < 0.0f) {
			gs->camera.zoom = 0.0f;
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
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			for (int i = 0; i < gs->em.entities.size(); i++) {
				if (gs->em.entities[i].grid_transform >= 0) {
					if (gs->grid_pos == gs->em.c_grid_transforms[gs->em.entities[i].grid_transform].pos) {
						gs->selected_entity = i;
					}
				}
			}
		}

		Entity& e = gs->em.entities[gs->selected_entity];
		if (e.grid_transform >= 0) {
			if (IsKeyPressed(KEY_A)) {
				gs->em.GridTransform(e).pos.x -= 1;
			}
			if (IsKeyPressed(KEY_D)) {
				gs->em.GridTransform(e).pos.x += 1;
			}
			if (IsKeyPressed(KEY_W)) {
				gs->em.GridTransform(e).pos.y -= 1;
			}
			if (IsKeyPressed(KEY_S)) {
				gs->em.GridTransform(e).pos.y += 1;
			}

			if (e.renderable >= 0) {
				gs->em.Renderable(e).pos = gs->em.GridTransform(e).pos * gs->entity_scale;
			}
		}
	}

	if (IsKeyPressed(KEY_O)) {
		WriteEntityToFile(gs);
	}
	else if (IsKeyPressed(KEY_I)) {
		ReadEntityFromFile(gs, "entity.txt");
		std::cout << "Done\n";
	}
	if (IsKeyPressed(KEY_U)) {
		remove("entity.txt");
	}

	// Debug
	if (IsKeyPressed(KEY_EQUAL)) {
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