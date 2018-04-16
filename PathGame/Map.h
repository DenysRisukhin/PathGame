#pragma once

#include <irrlicht.h>
#include "LevelInfo.h"

class Game;
class Level;

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;

class Map
{
public:

	Map(Level* level, const LevelInfo& config);
	~Map(void);

	irr::scene::ISceneNode* getRootNode() const;

	bool canMove(irr::u32 position, CH_DIRECTION direction) const;

	irr::u32 getDestinationCell(irr::u32 position, CH_DIRECTION direction) const;

	irr::core::vector3df getPosition(irr::u32 cell);

	bool collectCoin(irr::u32 cell);

	irr::u32 getCoinsCount() const;

	irr::f32 getWidth() const;

	irr::f32 getHeight() const;

	irr::f32 getMinimalDistance() const;

	irr::f32 getMaximalDistanceSquared() const;

	irr::core::array<CH_DIRECTION> getAvailableDirections(irr::u32 position) const;

private:
	Game* _game;

	irr::u32 _width;
	irr::u32 _height;

	irr::f32 _minimalDistance;
	irr::f32 _maximalDistanceSquared;

	irr::scene::ISceneNode* _rootNode;
	irr::core::array<irr::core::rectf> _cells;
	irr::core::array<irr::u32> _obstacles;
	irr::core::array<irr::u32> _coins;
	irr::core::array<irr::scene::ISceneNode*> _coinNodes;

	/*!
	Helper for adding cell's content.
	*/
	irr::scene::IAnimatedMeshSceneNode* addCellContent(irr::u32 cell,
		irr::scene::IAnimatedMesh* mesh, irr::f32 yOffset = 0);
};

