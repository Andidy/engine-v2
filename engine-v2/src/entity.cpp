#include "entity.h"

std::string cTransform::ToString() {
	std::string result = "";
	result.append("component transform = [ ");
	result.append(std::to_string(pos.x));
	result.append(", ");
	result.append(std::to_string(pos.y));
	result.append(" ] ;");
	return result;
}