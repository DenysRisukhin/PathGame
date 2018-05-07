#include "RandomMovableController.h"
#include "Game.h"
#include "Map.h"
#include "Moving.h"
#include "Random.h"

using namespace irr;
using namespace core;

RandomMovableController::RandomMovableController(Map* board,
	f32 turnProbability, Moving* movable)
	: MovingController(movable)
	, _board(board)
	, _turnProbability(turnProbability)
{
	Random::SetSeed();
}

RandomMovableController::~RandomMovableController(void)
{
}

void RandomMovableController::refresh()
{
}

bool RandomMovableController::OnEvent(const SEvent& event)
{
	if (Game::ToGameEvent(event) == GE_FRAME_ENDED &&
		_movable->isStopped() &&
		Random::GetNumber() < _turnProbability) {

		array<CH_DIRECTION> directions = _board->getAvailableDirections(_movable->getPosition());

		_movable->move(directions[Random::GetNumber(directions.size())]);

	}
	return false;
}