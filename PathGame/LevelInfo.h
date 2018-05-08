#pragma once

#include <map>
#include "Info.h"
#include "Direction.h"
#include "MovingControllerType.h"

/*!
Represents level settings: level, map, player, skyBox, models, enemies etc.
*/
class LevelInfo : Info
{
public:
	/*!
	Reads config using provided path.
	@param game Game instance.
	@param filename Path to config file.
	*/
	LevelInfo(Game* game, const irr::io::path& filename);

	~LevelInfo(void);

	LevelInfo() {}
	LevelInfo(LevelInfo &&) {}

	irr::EKEY_CODE AbortKey;
	irr::EKEY_CODE PauseKey;

	struct
	{
		irr::f32 Fov;
		irr::f32 Near;
		irr::f32 Far;
	} Camera;

	struct
	{
		irr::video::ITexture* Front;
		irr::video::ITexture* Back;
		irr::video::ITexture* Left;
		irr::video::ITexture* Right;
		irr::video::ITexture* Top;
		irr::video::ITexture* Bottom;
	} SkyBox;

	/*!
	Size of the map in cells.
	*/
	struct
	{
		irr::u32 Width;
		irr::u32 Height;
	} Map;

	struct Model
	{
		irr::scene::IAnimatedMesh* Mesh;
		irr::f32 AnimationSpeed;
		bool AnisotropicFiltering;
	};

	struct
	{
		Model Floor;
		Model Obstacle;
		Model Coin;
		Model Enemy;
		Model Player;
	} Models;

	irr::f32 CoinRotationSpeed;

	/*!
	Indices of the cells with obstacles.
	*/
	irr::core::array<irr::u32> Obstacles;

	/*!
	Indices of the cells with coins.
	*/
	irr::core::array<irr::u32> Coins;

	struct
	{
		irr::io::path Hit;
		irr::io::path Coin;
		irr::io::path Death;
	} SoundFilenames;

	struct
	{
		irr::u32 ControllerId;
		irr::u32 Position;
		irr::u32 LivesCount;
		irr::u32 InvisibilityTime;
		irr::f32 Speed;
	} Player;

	struct Enemy
	{
		irr::u32 ControllerId;
		irr::u32 Position;
		irr::f32 Speed;
	};

	irr::core::array<Enemy> Enemies;

	struct MovableController
	{
		MOVING_CONTROLLER_TYPE Type;
		union
		{
			irr::u32 WaypointsSetId;
			irr::f32 TurnProbability;
		} Parameter;
	};

	irr::core::map<irr::u32, MovableController> MovableControllers;

	std::map<irr::u32, irr::core::list<CH_DIRECTION>> WaypointsSets;

	irr::core::map<irr::EKEY_CODE, CH_DIRECTION> Controls;

private:
	/*!
	Implementation of Config.
	*/
	void OnNode(const irr::core::stringw& name);

	void readCamera(const irr::core::stringw& name);
	void readEnvironment(const irr::core::stringw& name);
	void readMap(const irr::core::stringw& name);
	void readCharacters(const irr::core::stringw& name);
	void readControllers(const irr::core::stringw& name);

	void readModel(Model& model);
};