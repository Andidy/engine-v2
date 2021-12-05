#pragma once

#include "universal.h"

#include "action.h"

#include "components.h"
#include "entity.h"
#include "entity_manager.h"

#include "scene.h"
#include "scene_battle.h"
#include "scene_mainmenu.h"

struct GameState {
	// Assets / Textures ======================================================
	int entity_scale = 32;
	std::unordered_map<std::string, size_t> texture_handles;
	std::vector<Texture2D> textures;

	// Scenes =================================================================
	Scene* current_scene = nullptr;
	std::unordered_map<std::string, Scene*> scenes;

	GameState() = default;
};