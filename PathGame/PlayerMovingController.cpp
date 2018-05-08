#include "PlayerMovingController.h"
#include "Player.h"

using namespace irr;
using namespace core;
using namespace io;

PlayerMovingController::PlayerMovingController(map<EKEY_CODE, CH_DIRECTION>& controls, Moving* movable) : MovingController(movable)
{
	// Irrlicht map's copy constructor is not available, 
	// so copy operation is performed manually
	map<EKEY_CODE, CH_DIRECTION>::Iterator it = controls.getIterator();
	while (!it.atEnd()) {
		_controls.set(it->getKey(), it->getValue());
		it++;
	}
}

PlayerMovingController::~PlayerMovingController(void)
{
}

void PlayerMovingController::refresh()
{
}

bool PlayerMovingController::OnEvent(const SEvent& event)
{
	if (event.EventType == EET_KEY_INPUT_EVENT && event.KeyInput.PressedDown && _controls.find(event.KeyInput.Key))
	{
		_movable->move(_controls[event.KeyInput.Key]);
		return true;
	}
	return false;
}