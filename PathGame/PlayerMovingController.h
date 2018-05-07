#pragma once

#include "MovingController.h"
#include "Direction.h"

class Moving;

/*!
Controls movable treating keyboard events
as changes of direction for controlled object.
*/
class PlayerMovingController : MovingController
{
public:
	/*!
	Constructs controller using provided keymap.
	@param controls Keymap.
	@param movable Controlled object (can be set up later).
	*/
	PlayerMovingController(irr::core::map<irr::EKEY_CODE, CH_DIRECTION>& controls, Moving* movable = NULL);
	~PlayerMovingController(void);

	/*!
	Implementation of IController.
	*/

	void refresh();

	bool OnEvent(const irr::SEvent& event);

private:
	irr::core::map<irr::EKEY_CODE, CH_DIRECTION> _controls;
};