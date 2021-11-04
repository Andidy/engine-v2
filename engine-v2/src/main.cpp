#include "universal.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

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

static void Button000(GameState* gs);

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

	const char* Button000Text = "Spawn Entity";
	const char* ValueBox001Text = "";
	char label002text[64] = {};
	char label003text[64] = {};
	char label004text[64] = {};
	char label005text[64] = {};

	int ValueBox001Value = 0;

	Rectangle layoutRecs[6] = {
		{ anchor01.x + 10, anchor01.y + 10, 125, 30 },
		{ anchor01.x + 10, anchor01.y + 45, 125, 25 },
		{ anchor01.x + 10, anchor01.y + 75, 125, 25 },
		{ anchor01.x + 10, anchor01.y + 95, 125, 25 },
		{ anchor01.x + 10, anchor01.y + 115, 125, 25 },
		{ anchor01.x + 10, anchor01.y + 135, 125, 25 }
	};
	//----------------------------------------------------------------------------------

	RenderTexture2D render_texture = LoadRenderTexture(800, 600);

	// Load Texture Assets
	//----------------------------------------------------------------------------------

	// Load a pure magenta texture to act as the debug texture in slot 0.
	gs.texture_handles.insert({ "Debug", 0 });
	gs.textures.push_back(LoadTextureFromImage(GenImageColor(10, 10, MAGENTA)));
	
	// std::string tex_name = "Tex0.png";
	// This will load "assets/gfx/Tex0.png"
	// LoadTextureFromFile(gs, tex_name);

	//----------------------------------------------------------------------------------

	while (!WindowShouldClose()) {
		GameUpdate(&gs);

		ValueBox001Value = gs.entities.size();
		// Rendering Code =====================================================
		
		BeginTextureMode(render_texture);
		ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
		BeginMode2D(gs.camera);

		DrawGridLines(gs);

		DrawText("This is the game window", 190, 200, 20, LIGHTGRAY);

		for (Entity& e : gs.entities) {
			cRenderable& r = gs.c_renderables[e.renderable];
			DrawTextureEx(gs.textures[r.texture_handle], r.pos, 0.0f, 1.0f, r.tint_color);
		}

		EndMode2D();
		EndTextureMode();

		BeginDrawing();
		ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));
		
		// Draw Game Region ===================================================
		
		DrawRectangleLines(gs.game_window.x-1, gs.game_window.y-1, gs.game_window.width+2, gs.game_window.height+2, GRAY);
		DrawTexturePro(render_texture.texture, { 0, 0, 800, -600 }, gs.game_window, {0, 0}, 0.0f, WHITE);
		
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
		if (GuiButton(layoutRecs[0], Button000Text)) Button000(&gs);
		
		GuiValueBox(layoutRecs[1], ValueBox001Text, &ValueBox001Value, 0, 100, false);
		
		snprintf(label002text, 64, "Mouse Pos: %f, %f", gs.mouse_pos.x, gs.mouse_pos.y);
		GuiLabel(layoutRecs[2], label002text);
		
		snprintf(label003text, 64, "World Pos: %f, %f", gs.world_pos.x, gs.world_pos.y);
		GuiLabel(layoutRecs[3], label003text);

		snprintf(label004text, 64, "Grid Pos: %d, %d", gs.grid_pos.x, gs.grid_pos.y);
		GuiLabel(layoutRecs[4], label004text);

		snprintf(label005text, 64, "Selected Entity: %d", gs.selected_entity);
		GuiLabel(layoutRecs[5], label005text);

		//----------------------------------------------------------------------------------

		// Here is an example of hardcoded use of loaded textures.
		// DrawTexture(gs.textures[0], anchor01.x + 10, anchor01.y + 500, WHITE);
		// Here is an example of hardcoded use but that is closer to ideal use.
		// DrawTexture(gs.textures[gs.texture_handles["Tex0"]], anchor01.x + 50, anchor01.y + 500, WHITE);
		//
		// Here is an example of ideal usage. Where a reference to an entity 'e' exists.
		// And 'texture_handle' is a field in struct Entity that doesn't exist in the current code.
		// DrawTexture(gs.textures[e.texture_handle],
		//             gs.c_transforms[e.transform].pos.x, gs.c_transforms[e.transform].pos.y,
		//             gs.entity_scale, gs.entity_scale, BLUE);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}

static void Button000(GameState* gs) {
	// Spawn entity at random position
	cGridTransform gt = gs->blueprint_grid_transforms["Box"];

	Vector2 min = gs->game_origin;
	min.x -= gs->game_origin.x;
	min.y -= gs->game_origin.y;
	min = GetScreenToWorld2D(min, gs->camera);
	
	Vector2 max = gs->game_origin;
	max.x += gs->game_width;
	max.y += gs->game_height;
	max.x -= gs->game_origin.x;
	max.y -= gs->game_origin.y;
	max = GetScreenToWorld2D(max, gs->camera);
	
	max.x /= gs->entity_scale;
	max.y /= gs->entity_scale;
	min.x /= gs->entity_scale;
	min.y /= gs->entity_scale;

	gt.pos.x = (rand() % (int)(max.x - min.x)) + min.x;
	gt.pos.y = (rand() % (int)(max.y - min.y)) + min.y;

	size_t i_g_t = gs->c_grid_transforms.size();
	gs->c_grid_transforms.push_back(gt);

	cRenderable r = { { (float)(gt.pos.x * gs->entity_scale), (float)(gt.pos.y * gs->entity_scale) }, 0, WHITE };
	size_t i_r = gs->c_renderables.size();
	gs->c_renderables.push_back(r);

	cUnit u;
	u.waypoint_active = false;
	u.waypoint_pos.push_back({ 0,0 });
	u.waypoint_pos.push_back({ 1,1 });
	u.waypoint_pos.push_back({ 2,2 });
	size_t i_u = gs->c_units.size();
	gs->c_units.push_back(u);

	Entity e = {};
	e.id = gs->entity_id_counter++;
	e.is_active = true;
	e.name = "Box";
	e.grid_transform = i_g_t;
	e.renderable = i_r;
	e.unit = i_u;

	gs->entities.push_back(e);
}