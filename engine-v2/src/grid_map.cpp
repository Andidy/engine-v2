#include "grid_map.h"

Color grass = { 106, 190, 48, 255 };
Color water = { 99, 155, 255, 255 };
Color forest = { 75, 105, 47, 255 };

void GridMap::LoadMap(std::string filename) {
	Image img = LoadImage(filename.c_str());
	Color* colors = LoadImageColors(img);
	int num_colors = img.width * img.height;

	for (int i = 0; i < num_colors; i++) {
		Color c = colors[i];

		int x = i % img.width;
		int y = i / img.width;

		if (c == grass) {
			tiles.insert({ {x, y}, { { x, y }, true, 0 } });
		}
		else if (c == water) {
			tiles.insert({ {x, y}, { { x, y }, false, 1 } });
		}
		else if (c == forest) {
			tiles.insert({ {x, y}, { { x, y }, true, 2 } });
		}
	}


	UnloadImageColors(colors);
}