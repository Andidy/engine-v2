#pragma once

#include "universal.h"

// Action System

enum class ActionType {
	START,
	END
};

struct Action {
	std::string action;
	// int action_hash; // this will replace the string version of action to lower the amount of memory being passed around
	ActionType type;

	Action(const std::string& action_name, ActionType type);
	void PrintString();
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