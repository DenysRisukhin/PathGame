#include "MovingController.h"

MovingController::MovingController(Moving* movable)
	: _moving(movable)
{
}

MovingController::~MovingController(void)
{
}

void MovingController::setMovable(Moving* movable)
{
	_moving = movable;
}