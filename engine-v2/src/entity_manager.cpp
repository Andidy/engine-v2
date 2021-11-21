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

cHealth& EntityManager::Health(Entity& e) {
	return c_health[e.health];
}

// Add Component functions

int EntityManager::AddGridTransform(cGridTransform& gt) {
	int index = (int)c_grid_transforms.size();
	c_grid_transforms.push_back(gt);
	return index;
}

int EntityManager::AddRenderable(cRenderable& r) {
	int index = (int)c_renderables.size();
	c_renderables.push_back(r);
	return index;
}

int EntityManager::AddUnit(cUnit& u) {
	int index = (int)c_units.size();
	c_units.push_back(u);
	return index;
}

int EntityManager::AddHealth(cHealth& h) {
	int index = (int)c_health.size();
	c_health.push_back(h);
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
			pos = GridTransform(e).pos * (float)ec.texture_scale;
		}
		cRenderable r = { pos, ec.texture_handle, ec.tint_color };
		e.renderable = AddRenderable(r);
	}

	if (ec.unit) {
		cUnit u;
		e.unit = AddUnit(u);
	}

	if (ec.health) {
		cHealth h;
		h.max = ec.health_max;
		h.current = h.max;
		e.health = AddHealth(h);
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
	return (int)entities.size() - 1;
}