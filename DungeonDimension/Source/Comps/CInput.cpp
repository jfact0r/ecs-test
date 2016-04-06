/* Includes ***************************************************************************************/
#include "CInput.hpp"

#include "../Engine/Entity.hpp"
#include "../Engine/Prop.hpp"

#include <iostream>

/* Namespace **************************************************************************************/
namespace engine
{

/* CInput Definition ******************************************************************************/

// Constructor/Deconstructor ---------------------------------------------------
CInput::CInput()
	: Comp("Input")
{
}

CInput::~CInput()
{
}

// Functions -------------------------------------------------------------------
/*void CInput::UpdateComp(sf::RenderWindow app)
{
	keyDown = app.GetInput().IsKeyDown(sf::Key::Up);
}*/

void CInput::Initialize()
{
	ValueProp<bool> *prop = owner->GetValueProp<bool>("KeyDown", false);

	keyDown = prop->GetValuePointer();
}

void CInput::Update(sf::RenderWindow &app)
{
	*keyDown = sf::Keyboard::IsKeyPressed(sf::Keyboard::A);
}

} // namespace engine