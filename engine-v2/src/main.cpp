#include "universal.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "raygui_helpers.h"

#include "game_state.h"
#include "game.h"

#include <filesystem>
static std::filesystem::path path_to_textures = "assets/gfx";
static std::filesystem::path path_to_gui_layouts = "assets/gui/layout";
static std::filesystem::path path_to_gui_styles = "assets/gui/style";
static std::string bluish = "bluish";
static std::string gui_layout_extension = ".rgl";
static std::string gui_style_extension = ".rgs";
static std::string texture_extension = ".png";

void DrawGridLines(GameState& gs) {
	float spacing = gs.entity_scale;

	// Draw the vertical lines
	float min = gs.camera.target.x;
	min = ceilf(min / spacing) * spacing;

	float max = gs.camera.target.x + gs.game_width;
	max = ceilf(max / spacing) * spacing;

	if(IsKeyPressed(KEY_B)) printf("min: %f, max: %f\n", min, max);

	for (float i = min; i < max; i += spacing)
	{
		Vector2 begin = { i, gs.camera.target.y };
		Vector2 end = { i, gs.camera.target.y + gs.game_height };
		
		DrawLineV(begin, end, LIGHTGRAY);
	}

	// Draw the horizontal lines
	min = gs.camera.target.y;
	min = ceilf(min / spacing) * spacing;
	max = gs.camera.target.y + gs.game_height;
	max = ceilf(max / spacing) * spacing;

	for (float i = min; i < max; i += spacing)
	{
		Vector2 begin = { gs.camera.target.x, i };
		Vector2 end = { gs.camera.target.x + gs.game_width, i };

		DrawLineV(begin, end, LIGHTGRAY);
	}
}

void LoadTextureFromFile(GameState& gs, std::string filename) {
	std::filesystem::path full_path = path_to_textures / std::filesystem::path(filename + texture_extension);
	size_t index = gs.textures.size();
	gs.texture_handles.insert({ full_path.filename().stem().string().c_str(), index });
	gs.textures.push_back(LoadTexture(full_path.string().c_str()));
}

int main(void) {
	InitWindow(1200, 900, "raylib [core] example - basic window");

	bool test = false;

	GameState gs;
	
	std::filesystem::path gui_style_path = path_to_gui_styles / std::filesystem::path(bluish + gui_style_extension);
	GuiLoadStyle(gui_style_path.string().c_str());

	// my_layout: controls initialization
	//----------------------------------------------------------------------------------
	Vector2 anchor01 = gs.origin_debug_region;
	Vector2 anchor02 = gs.origin_debug_region2;

	gui::LabelContext label_mouse_pos = {};
	label_mouse_pos.bounds = { anchor01.x + 10, anchor01.y + 10, 125, 25 };
	label_mouse_pos.text = {};

	gui::LabelContext label_world_pos = {};
	label_world_pos.bounds = { anchor01.x + 10, anchor01.y + 30, 125, 25 };
	label_world_pos.text = {};

	gui::LabelContext label_grid_pos = {};
	label_grid_pos.bounds = { anchor01.x + 10, anchor01.y + 50, 125, 25 };
	label_grid_pos.text = {};

	gui::LabelContext label_selected_entity = {};
	label_selected_entity.bounds = { anchor01.x + 10, anchor01.y + 70, 125, 25 };
	label_selected_entity.text = {};

	gui::LabelContext label_num_entities = {};
	label_num_entities.bounds = { anchor01.x + 10, anchor01.y + 90, 125, 25 };
	label_num_entities.text = {};

	// Entity Spawner variables
	//----------------------------------------------------------------------------------
	Vector2 anchor_EntitySpawner = { anchor01.x + 10, 220 };
	
	const int entity_spawner_text_size = 128;

	gui::WindowBoxContext window_entity_spawner = {};
	window_entity_spawner.bounds = { anchor_EntitySpawner.x + 0, anchor_EntitySpawner.y + 0, 275, 425 };
	window_entity_spawner.is_active = true;
	window_entity_spawner.text = "Entity Spawner";

	gui::CheckBoxContext checkbox_renderable = {};
	checkbox_renderable.bounds = { anchor_EntitySpawner.x + 5, anchor_EntitySpawner.y + 90, 12, 12 };
	checkbox_renderable.checked = false;
	checkbox_renderable.text = "Renderable";

	gui::CheckBoxContext checkbox_grid_transform = {};
	checkbox_grid_transform.bounds = { anchor_EntitySpawner.x + 5, anchor_EntitySpawner.y + 300, 12, 12 };
	checkbox_grid_transform.checked = false;
	checkbox_grid_transform.text = "Grid Transform";

	gui::CheckBoxContext checkbox_unit = {};
	checkbox_unit.bounds = { anchor_EntitySpawner.x + 5, anchor_EntitySpawner.y + 360, 12, 12 };
	checkbox_unit.checked = false;
	checkbox_unit.text = "Unit";

	gui::CheckBoxContext checkbox_is_active = {};
	checkbox_is_active.bounds = { anchor_EntitySpawner.x + 5, anchor_EntitySpawner.y + 30, 12, 12 };
	checkbox_is_active.checked = false;
	checkbox_is_active.text = "is_active";

	gui::LineContext line_0 = {};
	line_0.bounds = { anchor_EntitySpawner.x + 0, anchor_EntitySpawner.y + 80, 275, 25 };

	gui::LineContext line_1 = {};
	line_1.bounds = { anchor_EntitySpawner.x + 0, anchor_EntitySpawner.y + 290, 275, 20 };

	gui::LineContext line_2 = {};
	line_2.bounds = { anchor_EntitySpawner.x + 0, anchor_EntitySpawner.y + 350, 275, 20 };

	gui::LineContext line_3 = {};
	line_3.bounds = { anchor_EntitySpawner.x + 0, anchor_EntitySpawner.y + 380, 275, 20 };

	gui::ColorPickerContext color_picker_entity_spawner = {};
	color_picker_entity_spawner.bounds = { anchor_EntitySpawner.x + 15, anchor_EntitySpawner.y + 135, 145, 145 };
	color_picker_entity_spawner.color = WHITE;

	gui::TextBoxContext textbox_entity_name = {};
	textbox_entity_name.bounds = { anchor_EntitySpawner.x + 5, anchor_EntitySpawner.y + 50, 125, 25 };
	textbox_entity_name.edit_mode = false;
	textbox_entity_name.text = (char*)calloc(entity_spawner_text_size, sizeof(char));
	strcpy_s(textbox_entity_name.text, entity_spawner_text_size, "Unnamed");
	textbox_entity_name.text_size = entity_spawner_text_size;

	gui::TextBoxContext textbox_grid_pos = {};
	textbox_grid_pos.bounds = { anchor_EntitySpawner.x + 5, anchor_EntitySpawner.y + 320, 125, 25 };
	textbox_grid_pos.edit_mode = false;
	textbox_grid_pos.text = (char*)calloc(entity_spawner_text_size, sizeof(char));
	strcpy_s(textbox_grid_pos.text, entity_spawner_text_size, "x, y");
	textbox_grid_pos.text_size = entity_spawner_text_size;

	gui::SpinnerContext spinner_texture_select = {};
	spinner_texture_select.bounds = { anchor_EntitySpawner.x + 90, anchor_EntitySpawner.y + 100, 100, 25 };
	spinner_texture_select.edit_mode = false;
	spinner_texture_select.text = "Texture Select";
	spinner_texture_select.value = 0;
	spinner_texture_select.min = 0;
	spinner_texture_select.max = gs.textures.size() - 1;

	gui::ButtonContext button_spawn_entity = {};
	button_spawn_entity.bounds = { anchor_EntitySpawner.x + 5, anchor_EntitySpawner.y + 390, 125, 25 };
	button_spawn_entity.text = "Spawn Entity";

	//----------------------------------------------------------------------------------

	RenderTexture2D render_texture = LoadRenderTexture(gs.game_width, gs.game_height);

	// Load Texture Assets
	//----------------------------------------------------------------------------------

	// Load a pure magenta texture to act as the debug texture in slot 0.
	gs.texture_handles.insert({ "Debug", 0 });
	gs.textures.push_back(LoadTextureFromImage(GenImageColor(gs.entity_scale, gs.entity_scale, MAGENTA)));
	
	// std::string tex_name = "Tex0.png";
	// This will load "assets/gfx/Tex0.png"
	// LoadTextureFromFile(gs, tex_name);
	std::string tex0 = "grass";
	std::string tex1 = "tree";
	std::string tex2 = "water";
	LoadTextureFromFile(gs, tex0);
	LoadTextureFromFile(gs, tex1);
	LoadTextureFromFile(gs, tex2);

	//----------------------------------------------------------------------------------

	while (!WindowShouldClose()) {
		GameUpdate(&gs);

		// Rendering Code =====================================================
		
		BeginTextureMode(render_texture);
		ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
		BeginMode2D(gs.camera);

		DrawGridLines(gs);

		DrawText("This is the game window", 190, 200, 20, LIGHTGRAY);

		for (Entity& e : gs.em.entities) {
			if (e.renderable >= 0) {
				cRenderable& r = gs.em.Renderable(e);
				DrawTextureEx(gs.textures[r.texture_handle], r.pos, 0.0f, 1.0f, r.tint_color);
			}
		}

		EndMode2D();
		EndTextureMode();

		BeginDrawing();
		ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
		
		// Draw Game Region ===================================================
		
		DrawRectangleLines(gs.game_window.x-1, gs.game_window.y-1, gs.game_window.width+2, gs.game_window.height+2, GRAY);
		DrawTexturePro(render_texture.texture, { 0, 0, gs.game_width, -gs.game_height }, gs.game_window, {0, 0}, 0.0f, WHITE);
		
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
		label_mouse_pos.text += std::to_string(gs.mouse_pos.x);
		label_mouse_pos.text += ", ";
		label_mouse_pos.text += std::to_string(gs.mouse_pos.y);
		gui::Label(label_mouse_pos);
		
		label_world_pos.text.clear();
		label_world_pos.text += "World Pos: ";
		label_world_pos.text += std::to_string(gs.world_pos.x);
		label_world_pos.text += ", ";
		label_world_pos.text += std::to_string(gs.world_pos.y);
		gui::Label(label_world_pos);

		label_grid_pos.text.clear();
		label_grid_pos.text += "Grid Pos: ";
		label_grid_pos.text += std::to_string(gs.grid_pos.x);
		label_grid_pos.text += ", ";
		label_grid_pos.text += std::to_string(gs.grid_pos.y);
		gui::Label(label_grid_pos);

		label_selected_entity.text.clear();
		label_selected_entity.text += "Selected Entity: ";
		label_selected_entity.text += std::to_string(gs.selected_entity);
		gui::Label(label_selected_entity);

		label_num_entities.text.clear();
		label_num_entities.text += "Num Entities: ";
		label_num_entities.text += std::to_string(gs.em.entities.size());
		gui::Label(label_num_entities);

		// Entity Spawner
		if (window_entity_spawner.is_active) {
			gui::WindowBox(window_entity_spawner);
			gui::CheckBox(checkbox_is_active);
			gui::CheckBox(checkbox_renderable);
			gui::CheckBox(checkbox_grid_transform);
			gui::CheckBox(checkbox_unit);
			gui::Line(line_0);
			gui::Line(line_1);
			gui::Line(line_2);
			gui::Line(line_3);
			gui::ColorPicker(color_picker_entity_spawner);
			gui::TextBox(textbox_entity_name);
			gui::TextBox(textbox_grid_pos);
			gui::Spinner(spinner_texture_select, gs.textures.size() - 1);
			
			if (gui::Button(button_spawn_entity)) {
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
				ec.texture_scale = gs.entity_scale;
				ec.texture_handle = (size_t)spinner_texture_select.value;
				ec.tint_color = color_picker_entity_spawner.color;
				ec.grid_transform = checkbox_grid_transform.checked;
				ec.gt_pos = gt_pos;
				ec.unit = checkbox_unit.checked;

				gs.em.CreateEntity(ec);
			}

			Vector2 texture_preview_pos = { color_picker_entity_spawner.bounds.x + color_picker_entity_spawner.bounds.width + 40, color_picker_entity_spawner.bounds.y };
			DrawTextureEx(gs.textures[spinner_texture_select.value], texture_preview_pos, 0.0f, 2.0f, color_picker_entity_spawner.color);
		}

		//----------------------------------------------------------------------------------

		EndDrawing();
	}

	CloseWindow();

	return 0;
}