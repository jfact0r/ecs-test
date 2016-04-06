#pragma once

/* Includes *******************************************************************/
#include "Engine/Comp.hpp"

/* Namespace ******************************************************************/
namespace game
{

/* CQuitter Declaration *******************************************************/
class CQuitter : public engine::Comp
{
public:
	// Constructor/Deconstructor
	CQuitter();
	~CQuitter();

	// Functions
	virtual void Initialize();

	virtual void UpdateComp(sf::RenderWindow &app) {};
	virtual void Update(sf::RenderWindow &app);

private:
	// Members
	bool *keyDown;
};

} // namespace game