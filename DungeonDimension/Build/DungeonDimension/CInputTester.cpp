/* Includes *******************************************************************/
#include "CInputTester.hpp"

#include "Engine/Entity.hpp"
#include "Engine/Prop.hpp"

#include <iostream>

/* Using **********************************************************************/
using namespace engine;

/* Namespace ******************************************************************/
namespace game
{

/* CInputTester Definition ****************************************************/

// Constructor/Deconstructor ---------------------------------------------------
CInputTester::CInputTester()
	: engine::Comp("Quitter")
{
}

CInputTester::~CInputTester()
{
}

// Functions -------------------------------------------------------------------
/*void CInputTester::UpdateComp(sf::RenderWindow app)
{
	keyDown = app.GetInput().IsKeyDown(sf::Key::Up);
}*/

void CInputTester::Initialize()
{
	ValueProp<bool> *prop = owner->GetValueProp<bool>("KeyDown", false);

	keyDown = prop->GetValuePointer();
}

void CInputTester::Update(sf::RenderWindow &app)
{
	if (*keyDown) {
		std::cout << "You pressed the key!" << std::endl;
	}
}

} // namespace game