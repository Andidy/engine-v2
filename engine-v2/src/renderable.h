#pragma once

#include "universal.h"

struct cRenderable {
	size_t texture_handle = 0;
	Color tint_color = WHITE;

	cRenderable() = default;

	std::string ToString();
};