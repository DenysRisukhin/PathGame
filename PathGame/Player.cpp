#include "Player.h"
#include "Game.h"
#include "Level.h"
#include "Map.h"

using namespace irr;
using namespace io;
using namespace scene;

Player::Player(Level* level,
	IAnimatedMeshSceneNode* node, const LevelInfo& config)
	: Moving(level, node, config.MainCharacter.Position,
		config.MainCharacter.Speed, config.SoundFilenames.Hit)
	, _game(level->getGame())
	, _livesCount(config.MainCharacter.LivesCount)
	, _invisibilityTime(config.MainCharacter.InvisibilityTime)
	, _coinsCount(0)
	, _time(level->getGame()->getDevice()->getTimer()->getTime())
{
	_coinSound = new Sound(level->getGame(), config.SoundFilenames.Coin);
	_deathSound = new Sound(level->getGame(), config.SoundFilenames.Death);

	node->setScale({ 30, 30, 30 });
	node->setFrameLoop(1, 13);
	node->setAnimationSpeed(30);
	node->setMaterialTexture(0, level->getGame()->getDevice()->getVideoDriver()->getTexture("Models/nskinbl.jpg"));
}

Player::~Player(void)
{
	delete _coinSound;
	delete _deathSound;
}

bool Player::isVisible() const
{
	return _game->getDevice()->getTimer()->getTime() -
		_time > _invisibilityTime;
}

void Player::injure()
{
	if (isVisible()) {
		--_livesCount;
		_deathSound->play();
		_time = _game->getDevice()->getTimer()->getTime();
		_level->refreshStatistics();
	}
}

u32 Player::getLivesCount() const
{
	return _livesCount;
}

u32 Player::getCoinsCount() const
{
	return _coinsCount;
}

void Player::OnPosition(u32 position)
{
	bool result = _level->getBoard()->collectCoin(position);
	if (result) {
		++_coinsCount;
		_coinSound->play(false);
		_level->refreshStatistics();
	}
}