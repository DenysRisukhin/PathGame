#pragma once

#include "MovingController.h"
#include "Direction.h"

class Map;
class Moving;

/*!
Represents controller that forces controlled(контролирует войска или силы) to pursue(преследовать) the target.
*/
class EnemyMovingController : MovingController
{
public:
	/*!
	Creates controller.
	@param _map Map instance.
	@param target Target movable.
	@param movable Controlled movable (can be set up later).
	*/
	EnemyMovingController(Map* board, Moving* target, Moving* movable = NULL);
	~EnemyMovingController(void);

	/*!
	Implementation of IController.
	*/

	void refresh();

	bool OnEvent(const irr::SEvent& event);

private:
	Map* _map;
	Moving* _target;

	irr::u32 _previousTargetPosition;

	irr::core::array<irr::u32> _usedPositions;

	irr::core::array<CH_DIRECTION> getAvailableDirections();
};