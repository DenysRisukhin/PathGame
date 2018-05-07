#pragma once

#include "MovingController.h"
#include "Direction.h"

/*!
Controller that forces controlled object to behave very straightforward
walking along a predetermined route.
*/
class WalkingMovableController : MovingController
{
public:
	/*!
	Creates controller.
	@param directions A set of directions defining
	controlled object's behaviour.
	@param movable Controlled object (can be set up later).
	*/
	WalkingMovableController(const irr::core::list<CH_DIRECTION>& directions, Moving* movable = NULL);
	~WalkingMovableController(void);

	/*!
	Implementation of IController.
	*/

	void refresh();

	bool OnEvent(const irr::SEvent& event);

private:
	irr::core::list<CH_DIRECTION> _directions;
	irr::core::list<CH_DIRECTION>::ConstIterator _iterator;
};