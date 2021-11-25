#include "scene.h"
#include "game.h"

// Scene ======================================================================

void Scene::RegisterAction(int input_type, int keycode, std::string action_name) {
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

	size_t hash = str_hash(action_name);
	action_map[keycode] = hash;
	action_name_map[hash] = action_name;
}