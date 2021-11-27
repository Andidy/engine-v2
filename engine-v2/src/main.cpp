#include "universal.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "game.h"

#include <filesystem>
static std::filesystem::path path_to_textures = "assets/gfx";
static std::filesystem::path path_to_gui_layouts = "assets/gui/layout";
static std::filesystem::path path_to_gui_styles = "assets/gui/style";
static std::string bluish = "bluish";
static std::string gui_layout_extension = ".rgl";
static std::string gui_style_extension = ".rgs";
static std::string texture_extension = ".png";

void LoadTextureFromFile(GameState& gs, std::string filename) {
	std::filesystem::path full_path = path_to_textures / std::filesystem::path(filename + texture_extension);
	size_t index = gs.textures.size();
	gs.texture_handles.insert({ full_path.filename().stem().string().c_str(), index });
	gs.textures.push_back(LoadTexture(full_path.string().c_str()));
}

int main(void) {
	InitWindow(1200, 900, "raylib [core] example - basic window");

	GameState gs;
	
	std::filesystem::path gui_style_path = path_to_gui_styles / std::filesystem::path(bluish + gui_style_extension);
	GuiLoadStyle(gui_style_path.string().c_str());

	//-------------------------------------------------------------------------

	// Load Texture Assets
	//-------------------------------------------------------------------------

	// Load a pure magenta texture to act as the debug texture in slot 0.
	gs.texture_handles.insert({ "Debug", 0 });
	gs.textures.push_back(LoadTextureFromImage(GenImageColor(gs.entity_scale, gs.entity_scale, MAGENTA)));
	
	// std::string tex_name = "Tex0.png";
	// This will load "assets/gfx/Tex0.png"
	// LoadTextureFromFile(gs, tex_name);
	std::string tex0 = "grass";
	std::string tex1 = "tree";
	std::string tex2 = "water";
	std::string tex3 = "sword";
	LoadTextureFromFile(gs, tex0);
	LoadTextureFromFile(gs, tex1);
	LoadTextureFromFile(gs, tex2);
	LoadTextureFromFile(gs, tex3);

	std::string tex4 = "bitkenney/arrow_shaft";
	std::string tex5 = "bitkenney/arrow_head";
	std::string tex6 = "bitkenney/arrow_butt";
	std::string tex7 = "bitkenney/arrow_bend";
	std::string tex8 = "bitkenney/cursor_tile";
	LoadTextureFromFile(gs, tex4);
	LoadTextureFromFile(gs, tex5);
	LoadTextureFromFile(gs, tex6);
	LoadTextureFromFile(gs, tex7);
	LoadTextureFromFile(gs, tex8);

	// Load a blue texture to act as the movement range indicator.
	{
		size_t index = gs.textures.size();
		gs.texture_handles.insert({ "Movement", index });
		gs.textures.push_back(LoadTextureFromImage(GenImageColor(gs.entity_scale, gs.entity_scale, SKYBLUE)));
	}

	// Load a red texture to act as the attack range indicator.
	{
		size_t index = gs.textures.size();
		gs.texture_handles.insert({ "Attack", index });
		gs.textures.push_back(LoadTextureFromImage(GenImageColor(gs.entity_scale, gs.entity_scale, RED)));
	}

	//-------------------------------------------------------------------------

	BattleScene bs;
	MenuScene ms;
	bs.gs = &gs;
	ms.gs = &gs;
	bs.Init();
	ms.Init();

	gs.scenes["BattleScene"] = &bs;
	gs.scenes["MenuScene"] = &ms;
	gs.current_scene = gs.scenes["BattleScene"];
	
	Scene& scene = *gs.current_scene;

	//-------------------------------------------------------------------------
	
	while (!WindowShouldClose()) {
		// Get Input From User ================================================
		for(int key = 0; key < MAX_KEYBOARD_KEYS; key++) {
			if (IsKeyPressed(key) || IsKeyReleased(key)) {
				if (scene.action_map.find(key) == scene.action_map.end()) {
					// Didn't find the keycode in the mapping
					continue;
				}

				ActionType at = IsKeyPressed(key) ? ActionType::START : ActionType::END;
				Action action = Action(scene.action_map.at(key), at);
				scene.action_queue.push(action);
			}
		}

		for (int mouse_button = 0; mouse_button < MAX_MOUSE_BUTTONS; mouse_button++) {
			if (IsMouseButtonPressed(mouse_button) || IsMouseButtonReleased(mouse_button)) {
				if (scene.action_map.find(rl_MouseToCode(mouse_button)) == scene.action_map.end()) {
					// Didn't find the keycode in the mapping
					continue;
				}

				ActionType at = IsMouseButtonPressed(mouse_button) ? ActionType::START : ActionType::END;
				Action action = Action(scene.action_map.at(rl_MouseToCode(mouse_button)), at);
				scene.action_queue.push(action);
			}
		}
		
		for (int gamepad = 0; gamepad < MAX_GAMEPADS; gamepad++) {
			// If the controller isn't availible skip it
			if (!IsGamepadAvailable(gamepad)) continue;
			
			for (int gamepad_button = 0; gamepad_button < MAX_GAMEPAD_BUTTONS; gamepad_button++) {
				if (IsGamepadButtonPressed(gamepad, gamepad_button) || IsGamepadButtonReleased(gamepad, gamepad_button)) {
					if (scene.action_map.find(rl_ControllerToCode(gamepad_button)) == scene.action_map.end()) {
						// Didn't find the keycode in the mapping
						continue;
					}

					ActionType at = IsGamepadButtonPressed(gamepad, gamepad_button) ? ActionType::START : ActionType::END;
					Action action = Action(scene.action_map.at(rl_ControllerToCode(gamepad_button)), at);
					scene.action_queue.push(action);
				}
			}

			for (int gamepad_axis = 0; gamepad_axis < NUM_CONTROLLER_AXIS; gamepad_axis++) {
				if (scene.action_map.find(rl_ControllerAxisToCode(gamepad_axis)) == scene.action_map.end()) {
					// Didn't find the keycode in the mapping
					continue;
				}
				
				// there are 2 axis per joystick, right left and up down, they go from -1.0 to 1.0
				// on the ps4 controller, up and left are negative.
				float movement = GetGamepadAxisMovement(gamepad, gamepad_axis);
					
				// here is how to test a threshold on the joystick movement
				if (fabsf(movement) > 0.25f) {
					//switch (gamepad_axis) {
					//	case GAMEPAD_AXIS_RIGHT_X:
					//	{
					//		if (movement > 0) {
					//			Action(gs.action_map.at(rl_ControllerAxisToCode(gamepad_axis)), at);
					//		}
					//		else if (movement < 0) {
					//		}
					//	}
					//}
				}
			}
		}

		// Game Update ========================================================

		gs.current_scene->Update();

		// Rendering ==========================================================

		gs.current_scene->Render();
	}

	CloseWindow();

	return 0;
}