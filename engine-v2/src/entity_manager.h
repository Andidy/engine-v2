#pragma once

#include "universal.h"

#include "components.h"
#include "entity.h"

struct EntityManager {
	int entity_id_counter = 0;
	
	std::vector<Entity> entities;
	std::vector<cGridTransform> c_grid_transforms;
	std::vector<cRenderable> c_renderables;
	std::vector<cUnit> c_units;
	std::vector<cHealth> c_health;
	std::vector<cAttack> c_attack;
	std::vector<cFaction> c_faction;

	// Component Accessors
	cGridTransform& GridTransform(Entity& e);
	cRenderable& Renderable(Entity& e);
	cUnit& Unit(Entity& e);
	cHealth& Health(Entity& e);
	cAttack& Attack(Entity& e);
	cFaction& Faction(Entity& e);

	// Add Component
	int AddGridTransform(cGridTransform& gt);
	int AddRenderable(cRenderable& r);
	int AddUnit(cUnit& u);
	int AddHealth(cHealth& h);
	int AddAttack(cAttack& a);
	int AddFaction(cFaction& f);
	
	// Entity Management
	int CreateEntity(EntityContext& ec);
};
