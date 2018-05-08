#include "LevelInfo.h"

using namespace irr;
using namespace core;
using namespace io;
using namespace video;
using namespace scene;
using namespace gui;

LevelInfo::LevelInfo(Game* game, const path& filename)
	: Info(game, filename)
{
	while (next());

	Coins.sort();
	Obstacles.sort();
}

LevelInfo::~LevelInfo(void)
{
}

void LevelInfo::OnNode(const stringw& name)
{
	readCamera(name);
	readEnvironment(name);
	readMap(name);
	readCharacters(name);
	readControllers(name);
}

void LevelInfo::readCamera(const stringw& name)
{
	if (name == "camera") {

		Camera.Fov = read<f32>("fov");

		Camera.Near = read<f32>("near");
		Camera.Far = read<f32>("far");

	}
}

void LevelInfo::readEnvironment(const stringw& name)
{
	if (name == "environment") {

		SkyBox.Back = read<ITexture*>("back");
		SkyBox.Bottom = read<ITexture*>("bottom");
		SkyBox.Front = read<ITexture*>("front");
		SkyBox.Left = read<ITexture*>("left");
		SkyBox.Right = read<ITexture*>("right");
		SkyBox.Top = read<ITexture*>("top");

	}
	else if (name == "sound") {

		stringw type = read<stringw>("type");
		path filename = read<path>("filename");

		if (type == "hit")
			SoundFilenames.Hit = filename;
		if (type == "coin")
			SoundFilenames.Coin = filename;
		if (type == "death")
			SoundFilenames.Death = filename;

	}
	else if (name == "key") {

		stringw type = read<stringw>("type");
		EKEY_CODE code = (EKEY_CODE)read<u32>("code");

		if (type == "pause")
			PauseKey = code;
		else if (type == "abort")
			AbortKey = code;

	}
}

void LevelInfo::readMap(const stringw& name)
{
	if (name == "board") {

		Map.Width = read<u32>("width");
		Map.Height = read<u32>("height");

		readModel(Models.Floor);

	}
	else if (name == "coins") {

		readModel(Models.Coin);

		CoinRotationSpeed = read<f32>("rotationSpeed");

	}
	else if (name == "coin") {

		Coins.push_back(read<u32>("position"));

	}
	else if (name == "obstacles") {

		readModel(Models.Obstacle);

	}
	else if (name == "obstacle") {

		Obstacles.push_back(read<u32>("position"));

	}
}

void LevelInfo::readCharacters(const stringw& name)
{
	if (name == "mainCharacter") {

		Player.ControllerId = read<u32>("controllerId");

		readModel(Models.Player);

		Player.Position = read<u32>("position");
		Player.LivesCount = read<u32>("livesCount");
		Player.InvisibilityTime = read<u32>("invisibilityTime");
		Player.Speed = read<f32>("speed");

	}
	else if (name == "enemies") {

		readModel(Models.Enemy);

	}
	else if (name == "enemy") {

		LevelInfo::Enemy enemy;

		enemy.ControllerId = read<u32>("controllerId");
		enemy.Position = read<u32>("position");
		enemy.Speed = read<f32>("speed");

		Enemies.push_back(enemy);

	}
}

void LevelInfo::readControllers(const stringw& name)
{
	if (name == "playerMovableController") {

		MovableController controller;
		controller.Type = EMCT_PLAYER;
		MovableControllers.set(read<u32>("id"), controller);

	}
	/*else if (name == "randomMovableController") {

		MovableController controller;
		controller.Type = EMCT_RANDOM;
		controller.Parameter.TurnProbability = read<f32>("turnProbability");
		MovableControllers.set(read<u32>("id"), controller);

	}
	else if (name == "walkingMovableController") {

		MovableController controller;
		controller.Type = EMCT_WALKING;
		controller.Parameter.WaypointsSetId = read<u32>("waypointsSetId");
		MovableControllers.set(read<u32>("id"), controller);

	}*/
	else if (name == "enemyMovableController") {

		MovableController controller;
		controller.Type = EMCT_ENEMY;
		MovableControllers.set(read<u32>("id"), controller);

	}
	else if (name == "waypoint") {

		u32 setId = read<u32>("setId");
		if (WaypointsSets.find(setId) == WaypointsSets.end())
			WaypointsSets[setId] = list<CH_DIRECTION>();
		WaypointsSets[setId].push_back((CH_DIRECTION)read<u32>("direction"));
	}
	else if (name == "control") {

		Controls.set(
			(EKEY_CODE)read<u32>("key"),
			(CH_DIRECTION)read<u32>("direction"));
	}
}

void LevelInfo::readModel(LevelInfo::Model& model)
{
	model.Mesh = read<IAnimatedMesh*>("model");
	model.AnimationSpeed = read<f32>("animationSpeed");
	model.AnisotropicFiltering = read<bool>("anisotropicFiltering");

	if (model.AnisotropicFiltering)
		model.Mesh->setMaterialFlag(EMF_ANISOTROPIC_FILTER, true);
}