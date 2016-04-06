/* Includes *******************************************************************/
#include "CQuitter.hpp"

#include "../Engine/Entity.hpp"
#include "../Engine/Prop.hpp"

/* Using **********************************************************************/
using namespace engine;

/* Namespace ******************************************************************/
namespace game
{

/* CQuitter Definition ********************************************************/

// Constructor/Deconstructor ---------------------------------------------------
CQuitter::CQuitter()
	: engine::Comp("Quitter")
{
}

CQuitter::~CQuitter()
{
}

// Functions -------------------------------------------------------------------
/*void CQuitter::UpdateComp(sf::RenderWindow app)
{
	keyDown = app.GetInput().IsKeyDown(sf::Key::Up);
}*/

void CQuitter::Initialize()
{
	ValueProp<bool> *prop = owner->GetValueProp<bool>("KeyDown", false);

	keyDown = prop->GetValuePointer();
}

void CQuitter::Update(sf::RenderWindow &app)
{
	if (*keyDown) {
		app.Close();
	}
}

} // namespace game