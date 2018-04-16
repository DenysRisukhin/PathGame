#pragma once

#include "MovingController.h"

class Map;

/*!
Controller that forces controlled object to behave randomly.
*/
class RandomMovableController : MovingController
{
public:
	/*!
	Constructs controller.
	@param board Board instance.
	@param turnProbability Probability (from 0 to 1 inclusively)
	of change of direction.
	@param movable Controlled object (can be set up later).
	*/
	RandomMovableController(Map* board, irr::f32 turnProbability, Moving* movable = NULL);
	~RandomMovableController(void);

	/*!
	Implementation of IController.
	*/

	void refresh();

	bool OnEvent(const irr::SEvent& event);

private:
	Map* _board;
	irr::f32 _turnProbability;
};