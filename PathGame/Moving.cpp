#include "Moving.h"
#include "Level.h"
#include "Map.h"

using namespace irr;
using namespace io;
using namespace core;
using namespace scene;

Moving::Moving(Level* level, IAnimatedMeshSceneNode* node,
	u32 position, f32 speed, const path& hitSoundFilename)
	: _level(level)
	, _node(node)
	, _position(position)
	, _speed(speed)
	, _requestedDirection(CH_D_NONE)
	, _animator(0)
	, _hitSoundPlayed(false)
{
	_hitSound = new Sound(level->getGame(), hitSoundFilename);
}

Moving::~Moving(void)
{
	delete _hitSound;
	_node->remove();
}

void Moving::move(CH_DIRECTION direction)
{
	_requestedDirection = direction;
}

void Moving::update()
{
	if (isStopped()) {
		OnPosition(_position);

		Map* board = _level->getBoard();
		if (board->canMove(_position, _requestedDirection)) {
			if (_animator = getAnimator()) {

				_node->removeAnimators();
				_node->addAnimator(_animator);
				_animator->drop();

				_node->setRotation(vector3df(
					0, getAngle(_requestedDirection), 0));

				_position = board->getDestinationCell(
					_position, _requestedDirection);

				_hitSoundPlayed = false;
			}
		}
		else if (!_hitSoundPlayed) {
			_hitSound->play();
			_hitSoundPlayed = true;
		}
	}
}

u32 Moving::getPosition() const
{
	return _position;
}

bool Moving::isStopped() const
{
	return !_animator || _animator->hasFinished();
}

IAnimatedMeshSceneNode* Moving::getNode() const
{
	return _node;
}

ISceneNodeAnimator* Moving::getAnimator()
{
	Map* board = _level->getBoard();
	Game* game = _level->getGame();

	return board->canMove(_position, _requestedDirection)
		? game->getDevice()->getSceneManager()->createFlyStraightAnimator(
			board->getPosition(_position), board->getPosition(
				board->getDestinationCell(_position, _requestedDirection)),
				(u32)(1000 / _speed))
		: NULL;
}

f32 Moving::getAngle(CH_DIRECTION direction)
{
	switch (direction) {

	case CH_D_UP:
		return -90;

	case CH_D_DOWN:
		return 90;

	case CH_D_LEFT:
	default:
		return -180;

	case CH_D_RIGHT:
		return 0;
	}
}