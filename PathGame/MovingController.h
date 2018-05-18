#pragma once

#include "IController.h"

class Moving;

/*!
Represents base class for controller with moving
as controlled object.
*/
class MovingController : public IController
{
public:
	/*!
	Constructs controller for given object.
	@param movable Controlled object (can be set up later).
	*/
	MovingController(Moving* movable = NULL);
	~MovingController(void);

	/*!
	Sets controlled object.
	*/
	void setMovable(Moving* movable);

protected:
	Moving* _moving;
};