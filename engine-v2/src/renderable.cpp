#include "renderable.h"

std::string cRenderable::ToString() {
	std::string result = "";
	result += "component renderable = [ ";
	result += std::to_string(texture_handle);
	result += ", ";
	result += std::to_string(tint_color.r);
	result += ", ";
	result += std::to_string(tint_color.g);
	result += ", ";
	result += std::to_string(tint_color.b);
	result += ", ";
	result += std::to_string(tint_color.a);
	result += " ] ;";
	return result;
}