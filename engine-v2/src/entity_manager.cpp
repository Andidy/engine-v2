#include "entity_manager.h"

// Component Accessor functions

cGridTransform& EntityManager::GridTransform(Entity& e) {
	return c_grid_transforms[e.grid_transform];
}

cRenderable& EntityManager::Renderable(Entity& e) {
	return c_renderables[e.renderable];
}

cUnit& EntityManager::Unit(Entity& e) {
	return c_units[e.unit];
}

// Add Component functions

int32_t EntityManager::AddGridTransform(cGridTransform& gt) {
	int32_t index = c_grid_transforms.size();
	c_grid_transforms.push_back(gt);
	return index;
}

int32_t EntityManager::AddRenderable(cRenderable& r) {
	int32_t index = c_renderables.size();
	c_renderables.push_back(r);
	return index;
}

int32_t EntityManager::AddUnit(cUnit& u) {
	int32_t index = c_units.size();
	c_units.push_back(u);
	return index;
}

// Entity Management functions

int EntityManager::CreateEntity(EntityContext& ec) {
	Entity e = {};

	if (ec.grid_transform) {
		cGridTransform gt;
		gt.pos = ec.gt_pos;
		e.grid_transform = AddGridTransform(gt);
	}

	if (ec.renderable) {
		Vector2 pos = { 0, 0 };
		if (e.grid_transform >= 0) {
			pos = GridTransform(e).pos * ec.texture_scale;
		}
		cRenderable r = { pos, ec.texture_handle, ec.tint_color };
		e.renderable = AddRenderable(r);
	}

	if (ec.unit) {
		cUnit u;
		e.unit = AddUnit(u);
	}

	// If the id is known and in the context use it
	// Otherwise, we want to generate a new id.
	if (ec.id >= 0) {
		e.id = ec.id;
	}
	else {
		e.id = entity_id_counter++;
	}

	e.is_active = ec.is_active;
	e.name = std::string(ec.name);

	entities.push_back(e);
	return entities.size() - 1;
}