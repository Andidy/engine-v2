#include "action.h"

// Action System

Action::Action(size_t _hash, ActionType _type) {
	hash = _hash;
	type = _type;
}

// Functions to shift raylib key codes into safe regions

int rl_KeyboardToCode(int keycode) {
	return keycode;
}

int rl_MouseToCode(int keycode) {
	return MOUSE_CODE_OFFSET + keycode;
}

int rl_ControllerToCode(int keycode) {
	return CONTROLLER_CODE_OFFSET + keycode;
}

int rl_ControllerAxisToCode(int axis) {
	return CONTROLLER_CODE_OFFSET + MAX_GAMEPAD_BUTTONS + axis;
}

int rl_CodeToKeyboard(int code) {
	return code;
}

int rl_CodeToMouse(int code) {
	return code - MOUSE_CODE_OFFSET;
}

int rl_CodeToController(int code) {
	return code - CONTROLLER_CODE_OFFSET;
}

int rl_CodeToControllerAxis(int code) {
	return code - CONTROLLER_CODE_OFFSET - MAX_GAMEPAD_BUTTONS;
}