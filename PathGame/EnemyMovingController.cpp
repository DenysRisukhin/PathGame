#include "EnemyMovingController.h"
#include "Game.h"
#include "Map.h"
#include "Moving.h"

using namespace irr;
using namespace core;

EnemyMovingController::EnemyMovingController(Map* map, Moving* target, Moving* movable) : MovingController(movable)
, _map(map)
, _target(target)
{
}

EnemyMovingController::~EnemyMovingController(void)
{
}

void EnemyMovingController::refresh()
{
	_previousTargetPosition = _target->getPosition();
}

bool EnemyMovingController::OnEvent(const SEvent& event)
{
	if (Game::ToGameEvent(event) == GE_FRAME_ENDED && _moving->isStopped()) {

		u32 destinationCell = _moving->getPosition();

		vector3df destinationPosition = _map->getPosition(destinationCell);

		CH_DIRECTION direction = CH_D_NONE;

		// computes position of our target
		vector3df targetPosition = _map->getPosition(_target->getPosition());

		// computes initial value of metric for finding best position
		f32 minimalDistance = destinationPosition.getDistanceFromSQ(targetPosition);

		if (sqrtf(minimalDistance) > _map->getMinimalDistance())
			minimalDistance = _map->getMaximalDistanceSquared();

		// checks: is better position exists, if exists then uses it
		array<CH_DIRECTION> directions = getAvailableDirections();

		for (u32 i = 0; i < directions.size(); ++i) {

			u32 destinationCell = _map->getDestinationCell(_moving->getPosition(), directions[i]);
			
			vector3df destinationPosition = _map->getPosition(destinationCell);

			f32 distance = destinationPosition.getDistanceFromSQ(targetPosition);

			if (distance < minimalDistance) {
				direction = directions[i];
				minimalDistance = distance;
			}

		}

		// adds current position to the list of used to prevent up-down or left-right jittering when target  is behind the obstacle
		_usedPositions.push_back(_moving->getPosition());

		// moves controlled entity
		_moving->move(direction);

	}
	return false;
}

array<CH_DIRECTION> EnemyMovingController::getAvailableDirections()
{
	u32 targetPosition = _target->getPosition();

	if (_previousTargetPosition != targetPosition) {
		_usedPositions.clear();
		_previousTargetPosition = targetPosition;
	}

	u32 position = _moving->getPosition();


	array<CH_DIRECTION> directions = _map->getAvailableDirections(position);

	for (u32 i = 0; i < directions.size(); ++i)
	{
		u32 destination = _map->getDestinationCell(position, directions[i]);
	
		if (_usedPositions.linear_search(destination) != -1) {
			directions.erase(i--, 1);
		}
	}

	return directions;
}