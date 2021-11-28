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