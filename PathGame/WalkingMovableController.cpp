#include "WalkingMovableController.h"
#include "Game.h"
#include "Moving.h"

using namespace irr;
using namespace core;

WalkingMovableController::WalkingMovableController(const list<CH_DIRECTION>& directions, Moving* movable)
    : MovingController(movable)
	, _directions(directions)
{
	_iterator = _directions.begin();
}

WalkingMovableController::~WalkingMovableController(void)
{
}


void WalkingMovableController::refresh()
{
}

bool WalkingMovableController::OnEvent(const SEvent& event)
{
	if (Game::ToGameEvent(event) == GE_FRAME_ENDED &&
		_movable->isStopped()) {
		_movable->move(*_iterator);
		if (++_iterator == _directions.end())
			_iterator = _directions.begin();
	}
	return false;
}