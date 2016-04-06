#pragma once

/// CInput
///
/// Component that listens to the keyboard.

/* Includes *******************************************************************/
#include "../Comp.hpp"

/* Namespace ******************************************************************/
namespace engine
{

/* CInput Declaration *********************************************************/
class CInput : public Comp
{
public:
	// Constructor/Deconstructor
	CInput();
	~CInput();

	// Functions
	virtual void Initialize();

	virtual void UpdateComp(sf::RenderWindow &app) {};
	virtual void Update(sf::RenderWindow &app);

private:
	// Members
	bool *keyDown;
};

} // namespace engine