#include "Level.h"
#include "Hud.h"
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "CameraControllerInfo.h"
#include "PlayerMovingController.h"
#include "EnemyMovingController.h"

using namespace irr;
using namespace core;
using namespace io;
using namespace video;
using namespace gui;
using namespace scene;

Level::Level(Game* game, const StageConfig& stage)
	: Stage(game, stage, "level")
	, _config(LevelInfo(game, stage.ConfigFilename))// попытка ссылки на удаленную функцию
	, _paused(false)
{
	// camera
	createCamera();

	// skybox
	_game->getDevice()->getSceneManager()->addSkyBoxSceneNode(
		_config.SkyBox.Top, _config.SkyBox.Bottom,
		_config.SkyBox.Left, _config.SkyBox.Right,
		_config.SkyBox.Front, _config.SkyBox.Back, _rootNode);

	// entities
	createMap();
	createPlayer();
	createEnemies();

	// hud
	_hud = new Hud(this, stage.ConfigFilename);
}

Level::~Level(void)
{
	//delete _hud;

	/*removeControllers();
	removeCamera();
	removeMap();
	removePlayer();
	removeEnemies();*/
}

bool Level::OnEvent(const SEvent& event)
{
	if (_state == ES_ACTIVE && event.EventType == EET_KEY_INPUT_EVENT && event.KeyInput.PressedDown)
	{
		if (event.KeyInput.Key == _config.AbortKey) {
			deactivate(GE_LEVEL_ABORTED);
			return true;
		}
		else if (event.KeyInput.Key == _config.PauseKey) {
			togglePaused();
			return true;
		}

	}


	if (Game::ToGameEvent(event) == GE_LEVEL_REQUESTED) {
		removeCamera();
		removeMap();
		removePlayer();
		removeEnemies();

		removeControllers();

		createCamera();
		createMap();
		createPlayer();
		createEnemies();

		_paused = false;
	}

	if (_state == ES_FADING_IN) {
		for (u32 i = 0; i < _controllers.size(); ++i)
			_controllers[i]->refresh();
		_hud->activate();
		refreshStatistics();
	}

	if (_state == ES_FADING_OUT)
		_hud->deactivate();

	if (_state == ES_ACTIVE) {

		if (_hud->OnEvent(event))
			return true;

		for (u32 i = 0; i < _controllers.size(); ++i)
			if (_controllers[i]->OnEvent(event))
				return true;
	}

	return Stage::OnEvent(event);
}

void Level::refreshStatistics()
{
	if (!_map->getCoinsCount()) {
		//	_hud->showPressAnyKeyIndicator(true);
		deactivate(GE_LEVEL_SUCCEEDED);
	}

	u32 lives = _player->getLivesCount();
	if (!lives) {
		//	_hud->showPressAnyKeyIndicator(true);
		deactivate(GE_LEVEL_FAILED);
	}

	_hud->setLivesCount(lives);
	_hud->setCoinsCount(_player->getCoinsCount());
}

void Level::togglePaused()
{
	_hud->showPauseIndicator(_paused = !_paused);
}

void Level::update()
{
	if (_paused)
		return;

	_player->update();

	for (u32 i = 0; i < _enemies.size(); ++i)
		_enemies[i]->update();
}

IAnimatedMeshSceneNode* Level::createNode(const LevelInfo::Model& model, u32 position)
{
	IAnimatedMeshSceneNode* node = _game->getDevice()->getSceneManager()->addAnimatedMeshSceneNode(model.Mesh, _rootNode, -1, _map->getPosition(position));
	node->setAnimationSpeed(model.AnimationSpeed);
	return node;
}

void Level::createCamera()
{
	_camera = _game->getDevice()->getSceneManager()->addCameraSceneNode(_rootNode, vector3df(1), vector3df(), -1, false);

	_camera->setFOV(_config.Camera.Fov);

	_camera->setNearValue(_config.Camera.Near);
	_camera->setFarValue(_config.Camera.Far);

	//_controllers.push_back((IController*) new CameraController(_game, _camera, _stageInfo.ConfigFilename));

	CameraControllerInfo cameraConfig(_game, _stageInfo.ConfigFilename);

	auto _cameraRadius = cameraConfig.CameraRadius;
	auto _cameraAngles = cameraConfig.CameraAngles;

	_camera->setPosition(vector3df(
		_cameraRadius*sinf(_cameraAngles.Y)*cosf(_cameraAngles.X),
		_cameraRadius*cosf(_cameraAngles.Y),
		_cameraRadius*sinf(_cameraAngles.Y)*sinf(_cameraAngles.X)
	));
}

void Level::createMap()
{
	_map = new Map(this, _config);
	_map->getRootNode()->setParent(_rootNode);
}

void Level::createPlayer()
{
	_player = new Player(this, createNode(_config.Models.Player, _config.Player.Position), _config);

	MovingController* controller = createController(_config.MovableControllers[_config.Player.ControllerId]);
	controller->setMovable(_player);

	_controllers.push_back(controller);
}

void Level::createEnemies()
{
	for (u32 i = 0; i < _config.Enemies.size(); ++i) {
		LevelInfo::Enemy& enemy = _config.Enemies[i];

		Enemy* enemyEntity = new Enemy(this, createNode(_config.Models.Enemy, enemy.Position), _config, i);

		_enemies.push_back(enemyEntity);

		MovingController* controller = createController(_config.MovableControllers[enemy.ControllerId]);
		controller->setMovable(enemyEntity);

		_controllers.push_back(controller);
	}
}

MovingController* Level::createController(const LevelInfo::MovableController& config)
{
	switch (config.Type) {

	case EMCT_PLAYER:
		return (MovingController*) new PlayerMovingController(_config.Controls);

	case EMCT_ENEMY:
		return (MovingController*) new EnemyMovingController(_map, _player);

		/*case EMCT_RANDOM:
		return (MovableController*) new RandomMovableController(
		_map, config.Parameter.TurnProbability);

		case EMCT_WALKING:
		return (MovableController*) new WalkingMovableController(
		_config.WaypointsSets[config.Parameter.WaypointsSetId]);*/

		//default:
		//throw NotImplementedException();

	}
}

Hud* Level::getHud() {
	return _hud;
}

Game* Level::getGame() const
{
	return _game;
}

Map* Level::getMap() const
{
	return _map;
}

Player* Level::getPlayer() const
{
	return _player;
}

void Level::removeControllers()
{
	for (u32 i = 0; i < _controllers.size(); ++i)
		delete _controllers[i];
	_controllers.clear();
}

void Level::removeCamera()
{
	_camera->remove();
}

void Level::removeMap()
{
	delete _map;
}

void Level::removePlayer()
{
	delete _player;
}

void Level::removeEnemies()
{
	for (u32 i = 0; i < _enemies.size(); ++i)
		delete _enemies[i];
	_enemies.clear();
}

