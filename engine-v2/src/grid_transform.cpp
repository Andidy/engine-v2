#include "grid_transform.h"

std::string cGridTransform::ToString() {
	std::string result = "";
	result += "component grid_transform = [ ";
	result += std::to_string(pos.x);
	result += ", ";
	result += std::to_string(pos.y);
	result += " ] ;";
	return result;
}