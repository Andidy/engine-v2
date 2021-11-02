#include "entity.h"

std::string cTransform::ToString() {
	std::string result = "";
	result += "component transform = [ ";
	result += std::to_string(pos.x);
	result += ", ";
	result += std::to_string(pos.y);
	result += " ] ;";
	return result;
}