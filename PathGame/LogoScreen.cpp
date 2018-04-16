#include "LogoScreen.h"
#include "GameEvent.h"

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;

LogoScreen::LogoScreen(Game* game, const StageConfig& stage)
	: Stage(game, stage, "logoScreen")
	, _config(game, stage.ConfigFilename)
{
	//deactivate();
	createOrthoCamera();
	createBackground();

	IrrlichtDevice* device = _game->getDevice();
	ISceneManager* scene = device->getSceneManager();

	// creating logo plane

	const IGeometryCreator* geometry = scene->getGeometryCreator();

	SMaterial material;
	material.MaterialType = EMT_TRANSPARENT_ALPHA_CHANNEL;

	dimension2d<u32> textureSize = _config.LogoTexture->getSize();

	material.setTexture(0, _config.LogoTexture);
	_node = scene->addMeshSceneNode(geometry->createPlaneMesh(dimension2d<f32>((f32)textureSize.Width,(f32)textureSize.Height),dimension2d<u32>(1, 1), &material, dimension2d<f32>(1, 1)), 
		_rootNode);
	_node->setPosition(vector3df(0, 1, 0));

	//_node->setScale({0.5, 0.5, 0.5});

//#define WHITE_COLOR		{255, 255, 255, 255}
//#define WINDOW_WIDTH	1024
//#define WINDOW_HEIGHT	1500
//
//#define SCORE_HEALTH_WIDTH		60
//#define SCORE_HEALTH_HEIGHT		10
//#define TEXT_MARGIN				10
//
//	IGUIStaticText *result = _game->getDevice()->getGUIEnvironment()->addStaticText(L"Press Any Key",
//	{
//		WINDOW_WIDTH / 2 - SCORE_HEALTH_WIDTH / 2,
//		WINDOW_HEIGHT / 2 - SCORE_HEALTH_HEIGHT / 2 - TEXT_MARGIN - SCORE_HEALTH_HEIGHT,
//		WINDOW_WIDTH / 2 + SCORE_HEALTH_WIDTH / 2,
//		WINDOW_HEIGHT / 2 - SCORE_HEALTH_HEIGHT / 2 - TEXT_MARGIN
//	});
//	result->setOverrideColor(WHITE_COLOR);
//	result->enableOverrideColor(true);
	//result->setMinSize({25, 25, 25, 25})
}

LogoScreen::~LogoScreen(void)
{
}

bool LogoScreen::OnEvent(const SEvent& event)
{
	if (!_config.Duration && _state == ES_ACTIVE)
		switch (event.EventType) {

		case EET_KEY_INPUT_EVENT:
			if (event.KeyInput.PressedDown) {
				deactivate();
				return true;
			}
			break;

		case EET_MOUSE_INPUT_EVENT:
			if (event.MouseInput.ButtonStates &
				(EMIE_LMOUSE_PRESSED_DOWN | EMIE_MMOUSE_PRESSED_DOWN |
					EMIE_RMOUSE_PRESSED_DOWN)) {
				deactivate();
				return true;
			}
			break;

		}

	if (_state == ES_FADING_IN) {
		if (_config.ScaleTime)
			_node->setScale(vector3df());
		_time = _game->getDevice()->getTimer()->getTime();
	}


	
	return Stage::OnEvent(event);

	//_state = ES_FADING_IN;
	//return Stage::OnEvent(event);
}

void LogoScreen::update()
{
	u32 delta =  _game->getDevice()->getTimer()->getTime() -_time;

	if (_config.ScaleTime) {
		f32 factor = delta / (f32)_config.ScaleTime;
		if (factor > 1)
			factor = 1;
		_node->setScale(vector3df(factor));
	}

	if (delta > _config.Duration &&	_config.Duration)
		deactivate();
}