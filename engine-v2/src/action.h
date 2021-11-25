#pragma once

#include "universal.h"

// Action System

enum class ActionType {
	START,
	END
};

struct Action {
	size_t hash; // hashed string of action name
	ActionType type;

	Action(size_t hash, ActionType type);
};

// Key code adjustment constants and functions
const int MOUSE_CODE_OFFSET = 400;
const int CONTROLLER_CODE_OFFSET = 500;

int rl_KeyboardToCode(int keycode);
int rl_MouseToCode(int keycode);
int rl_ControllerToCode(int keycode);
int rl_ControllerAxisToCode(int axis);
int rl_CodeToKeyboard(int code);
int rl_CodeToMouse(int code);
int rl_CodeToController(int code);
int rl_CodeToControllerAxis(int code);