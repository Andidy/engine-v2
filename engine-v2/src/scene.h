#pragma once

#include "universal.h"

#include "action.h"
#include "entity_manager.h"

struct Scene {
	GameState* gs = nullptr;
	bool paused = false;
	
	// Actions
	std::unordered_map<size_t, std::string> action_name_map;
	std::unordered_map<int, size_t> action_map;
	std::queue<Action> action_queue;
	void RegisterAction(int input_type, int keycode, std::string action_name);

	// Entities
	EntityManager em;

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};