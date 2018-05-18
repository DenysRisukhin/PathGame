#include "Enemy.h"
#include "Level.h"
#include "Map.h"
#include "Player.h"

using namespace irr;
using namespace core;
using namespace scene;

Enemy::Enemy(Level* level, IAnimatedMeshSceneNode* node, const LevelInfo& config, u32 index)
	  : Moving(level, node, config.Enemies[index].Position, config.Enemies[index].Speed, config.SoundFilenames.Hit)
{
	node->setScale({ 30, 30, 30 });
	node->setFrameLoop(1, 13);
	node->setAnimationSpeed(20);
	node->setMaterialTexture(0, level->getGame()->getDevice()->getVideoDriver()->getTexture("Models/nskinrd.jpg"));
}

Enemy::~Enemy(void)
{
}

void Enemy::update()
{
	Player* player = _level->getPlayer();
	Map* map = _level->getMap();

	vector3df playerPosition = map->getPosition(player->getPosition());
	vector3df enemyPosition = map->getPosition(getPosition());

	if (playerPosition.getDistanceFrom(enemyPosition) < map->getMinimalDistance())
		player->injure();

	Moving::update();
}

void Enemy::OnPosition(u32 position)
{
}