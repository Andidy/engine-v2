#pragma once

#include "game_state.h"

void GameUpdate(GameState* gs);

void WriteEntityToFile(GameState* gs);
void ReadEntityFromFile(GameState* gs, std::string filename);