#include "grid_transform.h"

std::string cGridTransform::ToString() {
	std::string result = "";
	result.append("component grid_transform = [ ");
	result.append(std::to_string(pos.x));
	result.append(", ");
	result.append(std::to_string(pos.y));
	result.append(" ] ;");
	return result;
}