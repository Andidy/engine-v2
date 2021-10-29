#pragma once

#include "universal.h"
#include "entity.h"
#include <deque>

/*
	The item component is the primary marker of a class of gameplay elements
	which can be acquired and used by units and stored in a location like a
	building or structure.
*/
struct cItem {
	enum class Type {
		None = 0,
		Valuable = 1,
		Food = 2,
		Weapon = 3,
		Tool = 4,
		Wood = 5,
		Stone = 6
	};
	Type type;
	int32_t value;

	// Constructors and Assignment Operators ==================================

	cItem() = default;

	cItem(int _type, int _value) {
		type = (Type)_type;
		value = _value;
	}

	// Copy Ctor
	cItem(const cItem& source) {
		type = source.type;
		value = source.value;
	}

	// Copy op=
	cItem& operator= (const cItem& source) {
		assert(this != &source);

		type = source.type;
		value = source.value;

		return *this;
	}

	// Move Ctor
	cItem(cItem&& source) {
		type = source.type;
		source.type = cItem::Type::None;
		value = source.value;
		source.value = INT_MIN;
	}

	// Move op=
	cItem& operator= (cItem&& source) {
		assert(this != &source);

		type = source.type;
		source.type = cItem::Type::None;
		value = source.value;
		source.value = INT_MIN;

		return *this;
	}
};

/*
	The food component allows a unit entity to consume this entity to continue
	to live.
*/
struct cFood {
	int32_t nourishment; // how much nourishment the food provides
	// Constructors and Assignment Operators ==================================

	cFood() = default;

	cFood(int nourishment)
		: nourishment(nourishment) {}

	// Copy Ctor
	cFood(const cFood& source) {
		nourishment = source.nourishment;
	}

	// Copy op=
	cFood& operator= (const cFood& source) {
		assert(this != &source);

		nourishment = source.nourishment;

		return *this;
	}

	// Move Ctor
	cFood(cFood&& source) {
		nourishment = source.nourishment;
		source.nourishment = INT_MIN;
	}

	// Move op=
	cFood& operator= (cFood&& source) {
		assert(this != &source);

		nourishment = source.nourishment;
		source.nourishment = INT_MIN;

		return *this;
	}
};

/*
	ItemPile is a helper structure to allow the inventory component to store
	items and the quantity of those items together, because the quantity isn't
	an intrinsic value of an item.
	TODO: Perhaps the entity shouldn't be a full entity and instead just an index
	into the array of entities in GameState?
*/
struct ItemPile {
	Entity e;
	int32_t quantity;
};

/*
	The inventory component allows an entity to store references to other entities
	and the quantity of those entities. Ex: 10 Carrots, 1 Sword, and 128 coins.
*/
struct cInventory {
	std::vector<ItemPile> items;

	// Constructors and Assignment Operators ==================================

	cInventory() = default;

	// copy constructor
	cInventory(const cInventory& source) {
		for (int i = 0; i < source.items.size(); i++) {
			items.push_back(source.items[i]);
		}
	}

	// copy assignment
	cInventory& operator= (const cInventory& source) {
		assert(this != &source);

		for (int i = 0; i < source.items.size(); i++) {
			items.push_back(source.items[i]);
		}

		return *this;
	}

	// move constructor
	cInventory(cInventory&& source) {
		for (int i = 0; i < source.items.size(); i++) {
			items.push_back(source.items[i]);
		}
		source.items.clear();
	}

	// move assignment
	cInventory& operator= (cInventory&& source) {
		assert(this != &source);

		for (int i = 0; i < source.items.size(); i++) {
			items.push_back(source.items[i]);
		}
		source.items.clear();

		return *this;
	}
}; ragma once
