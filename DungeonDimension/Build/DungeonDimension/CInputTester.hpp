#pragma once

/* Includes *******************************************************************/
#include "Engine/Comp.hpp"

/* Namespace ******************************************************************/
namespace game
{

/* CInputTester Declaration ***************************************************/
class CInputTester : public engine::Comp
{
public:
	// Constructor/Deconstructor
	CInputTester();
	~CInputTester();

	// Functions
	virtual void Initialize();

	virtual void UpdateComp(sf::RenderWindow &app) {};
	virtual void Update(sf::RenderWindow &app);

private:
	// Members
	bool *keyDown;
};

} // namespace game