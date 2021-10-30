#include "universal.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "game_state.h"
#include "game.h"

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

int main(void) {
	InitWindow(1200, 900, "raylib [core] example - basic window");

	bool test = false;

	GameState gs;

	std::string entity_name = "Box";
	cTransform t = { 0, 0 };
	cGridTransform gt = { 0,0 };
	
	gs.blueprint_transforms.insert({"Box", t});
	gs.blueprint_grid_transforms.insert({ "Box", gt });
	
	GuiLoadStyle("assets/gui_style/bluish.rgs");

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
			DrawRectangle(gs.c_transforms[e.transform].pos.x, gs.c_transforms[e.transform].pos.y, gs.entity_scale, gs.entity_scale, BLUE);
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

	cTransform t = { (float)(gt.pos.x * gs->entity_scale), (float)(gt.pos.y * gs->entity_scale) };
	size_t i_t = gs->c_transforms.size();
	gs->c_transforms.push_back(t);
	size_t i_g_t = gs->c_grid_transforms.size();
	gs->c_grid_transforms.push_back(gt);

	Entity e = {};
	e.id = gs->entity_id_counter++;
	e.is_active = true;
	e.name = "Box";
	e.transform = i_t;
	e.grid_transform = i_g_t;

	gs->entities.push_back(e);
}