#include "components.h"

// cGridTransform =============================================================

std::string cGridTransform::ToString() {
	std::string result = "";
	result += "component grid_transform = [ ";
	result += std::to_string(pos.x);
	result += ", ";
	result += std::to_string(pos.y);
	result += " ] ;";
	return result;
}

// cRenderable ================================================================

std::string cRenderable::ToString() {
	std::string result = "";
	result += "component renderable = [ ";
	result += std::to_string(pos.x);
	result += ", ";
	result += std::to_string(pos.y);
	result += ", ";
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

// cUnit ======================================================================

std::string cUnit::ToString() {
	std::string result = "";
	result += "component unit = [ ";
	result += std::to_string(waypoint_active);
	result += ", ";
	result += std::to_string(waypoint_pos.size());
	result += ", ";
	for (int i = 0; i < waypoint_pos.size(); i++) {
		result += std::to_string(waypoint_pos[i].x);
		result += ", ";
		result += std::to_string(waypoint_pos[i].y);
		result += ", ";
	}
	result += " ] ;";
	return result;
}