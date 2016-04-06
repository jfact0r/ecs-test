#include <cstring>
#include <iostream>
#include "CWorld.hpp"
#include "../Engine/Utility.hpp"

/* Namespace ******************************************************************/
namespace engine
{

/*
** Constructs the world, allocating the worldMap.
*/
World::World()
	: head(0)
{
	worldMap = new Entity*[WORLD_SIZE * WORLD_SIZE * WORLD_SIZE];

	for (int i = 0; i < WORLD_SIZE; i++) {
		for (int j = 0; j < WORLD_SIZE; j++) {
			for (int k = 0; k < WORLD_SIZE; k++) {
				worldMap[i + j * WORLD_SIZE + k * WORLD_SIZE * WORLD_SIZE] = 0;
			}
		}
	}
}

/*
** Deconstructs the world, deallocating the worldMap.
*/
World::~World()
{
	delete[] worldMap;
}

/*
** Gets the cell corresponding to the given position in the world.
*/
Entity **World::get(sf::Vector3f *position) const
{
	return &worldMap[util::clamp<int>((int)position->x, 0, WORLD_SIZE) +
	            util::clamp<int>((int)position->y, 0, WORLD_SIZE) * WORLD_SIZE +
			    util::clamp<int>((int)position->z, 0, WORLD_SIZE) * WORLD_SIZE * WORLD_SIZE];
}

/*
** Adds an entity to the world.
*/
void World::add(Entity *e)
{
	// Update the head of the world
	Entity *oldHead = head;
	head = e;

	if (oldHead != 0) {
		e->nextInWorld = oldHead;
		oldHead->prevInWorld = e;
	}

	// Get the cell and the potential neighbour
	Entity **cell = get(e->position);
	Entity *neighbour = *cell;

	// Put the entity in the cell
	*cell = e;

	// Add neighbour to this entity's list if it exists
	if (neighbour != 0) {
		e->nextInCell = neighbour;
		neighbour->prevInCell = e;
	}

	std::cout << "Added entity to (" << e->position->x << ", "
	                                 << e->position->y << ", "
	                                 << e->position->z << ")" << std::endl;
}

/*
** Removes an entity from the world.
*/
void World::remove(Entity *e)
{
	// Handle world list
	if (e->prevInWorld == 0) {
		// We're the head of the world - set the head to the next in the world
		head = e->nextInWorld;

		if (e->nextInWorld != 0) {
			e->nextInWorld->prevInWorld = 0;
		}
	} else {
		// We're not the head of the world - remove ourselves from our neighbours
		e->prevInWorld->nextInWorld = e->nextInWorld;

		if (e->nextInWorld != 0) {
			e->nextInWorld->prevInWorld = e->prevInWorld;
		}
	}

	// Handle cell list
	if (e->prevInCell == 0) {
		// We're the head of the cell - set the head to our next neighbour
		Entity **cell = get(e->position);
		*cell = e->nextInCell;

		if (e->nextInCell != 0) {
			e->nextInCell->prevInCell = 0;
		}
	} else {
		// We're not the head of the cell - remove ourselves from our neighbours
		e->prevInCell->nextInCell = e->nextInCell;

		if (e->nextInCell != 0) {
			e->nextInCell->prevInCell = e->prevInCell;
		}
	}

	std::cout << "Removed entity from (" << e->position->x << ", "
	                                     << e->position->y << ", "
	                                     << e->position->z << ")" << std::endl;
}

} // namespace engine