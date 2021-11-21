#pragma once

#include "scene.h"

struct MenuScene : Scene {
	int test = -1;

	void Init();
	void Update();
	void Render();
};