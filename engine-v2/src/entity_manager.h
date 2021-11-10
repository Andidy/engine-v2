#pragma once

#include "universal.h"

#include "components.h"
#include "entity.h"

struct EntityManager {
	int64_t entity_id_counter = 0;
	
	std::vector<Entity> entities;
	std::vector<cGridTransform> c_grid_transforms;
	std::vector<cRenderable> c_renderables;
	std::vector<cUnit> c_units;

	// Component Accessors
	cGridTransform& GridTransform(Entity& e);
	cRenderable& Renderable(Entity& e);
	cUnit& Unit(Entity& e);

	// Add Component
	int32_t AddGridTransform(cGridTransform& gt);
	int32_t AddRenderable(cRenderable& r);
	int32_t AddUnit(cUnit& u);
	
	// Entity Management
	int CreateEntity(EntityContext& ec);
};
