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