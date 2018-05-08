#pragma once

#include "Stage.h"
#include "LevelInfo.h"
#include "IController.h"
#include "MovingController.h"

class Hud;
class Map;
class Player;
class Enemy;
class MovingController;

/*!
Represents game level: map, obstacels, coins, player, enemies, environment etc.
*/
class Level : Stage 
{
public:
	/*!
	Initializes level using provided info.
	@param game Game instance.
	@param stage Contains path to config file.
	*/
	Level(Game* game, const StageConfig& stage);
	~Level(void);

	Game* getGame() const;

	Map* getMap() const;
	Player* getPlayer() const;

	Hud* getHud();

	/*!
	Refreshes HUD and checks win and loss conditions.
	*/
	void refreshStatistics();

	/*!
	Implementation of IEventReceiver.
	*/
	virtual bool OnEvent(const irr::SEvent& event);

private:
	LevelInfo _config;

	Hud* _hud;
	Map* _map;
	Player* _player;
	irr::core::array<Enemy*> _enemies;

	irr::core::array<IController*> _controllers;

	bool _paused;

	/*!
	Pauses or resumes level.
	*/
	void togglePaused();

	/*!
	Implementation of Stage.
	*/
	void update();

	/*!
	Helper for creating scene nodes for characters.
	*/
	irr::scene::IAnimatedMeshSceneNode* createNode(const LevelInfo::Model& model, irr::u32 position);

	/*!
	Helper for creating controllers for characters.
	*/
	MovingController* createController(const LevelInfo::MovableController& config);

	void createCamera();
	void createMap();
	void createPlayer();
	void createEnemies();

	void removeControllers();

	void removeCamera();
	void removeMap();
	void removePlayer();
	void removeEnemies();
};