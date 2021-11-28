#include "action.h"

// Action System

Action::Action(const std::string& _action_name, ActionType _type) {
	action = _action_name;
	type = _type;
}

void Action::PrintString() {
	std::cout << "Action: " << action << ", " << (int)type << "\n";
}