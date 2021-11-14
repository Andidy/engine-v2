#include "game.h"

void GameState::Update() {
	current_scene->Update();
}