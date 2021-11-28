#include "scene.h"
#include "game.h"

// Scene ======================================================================

void Scene::RegisterAction(int input_type, int keycode, std::string action_name) {
	switch (input_type) {
		case 0: // keyboard
		{
			keycode = rlh::MapKeycode(keycode);
		} break;
		case 1: // mouse
		{
			keycode = rlh::MapMousecode(keycode);
		} break;
		case 2: // controller
		{
			keycode = rlh::MapControllercode(keycode);
		} break;
		case 3: // controller axis
		{
			keycode = rlh::MapControllerAxis(keycode);
		} break;
		default: __debugbreak(); // lol crashing 
	}
	action_map[keycode] = action_name;
}