#pragma once

#include <irrlicht.h>
#include <irrKlang.h>
#include "StageConfig.h"
#include "GameEvent.h"

using namespace irrklang;
using namespace irr;
using namespace core;
using namespace io;
using namespace video;
using namespace gui;
using namespace scene;

class GameInfo;
class Hud;

class Game : IEventReceiver {
public:

	Game(const char* configFilename);

	~Game(void);

	virtual bool OnEvent(const SEvent& event);

	void createDevice(const GameInfo& config);

	IrrlichtDevice* getDevice() const;

	ISoundEngine* getSoundEngine() const;

	void addMedia(const io::path& filename);

	void broadcastEvent(GAME_EVENT event);

	bool update();

	static GAME_EVENT ToGameEvent(const SEvent& event);

	void enableAdditionalRender(bool enable);

	void enableSound(bool enable);

private:

	Hud* _hud;

	IrrlichtDevice* _device;
	ISoundEngine* _soundEngine;

	array<irr::IEventReceiver*> _stages;

	u32 _sleepValue;
	bool _additionalRender;

	bool _soundEnabled;
	bool _soundAllowed;

	IEventReceiver* createStage(const StageConfig& stage);

};

