#pragma once

#include "Entity.hpp"

/* Namespace ******************************************************************/
namespace engine
{

/*
** The game world.
*/
class World
{
public:
	World();
	~World();

	Entity **get(sf::Vector3f *position) const;
	void add(Entity *e);
	void remove(Entity *e);

	static const int WORLD_SIZE = 256;

private:
	Entity *head;
	Entity **worldMap;
};

} // namespace engine