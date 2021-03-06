#pragma once

#include "Moving.h"
#include "LevelInfo.h"

/*!
Represents enemy entity.
*/
class Enemy : public Moving
{
public:
	/*!
	Constructs new enemy within level.
	@param level Level instance.
	@param node Enemy's scene node.
	@param config Level's config.
	@param index Enemy index (from 0 to count - 1).
	*/
	Enemy(Level* level, irr::scene::IAnimatedMeshSceneNode* node, const LevelInfo& config, irr::u32 index);

	~Enemy(void);

	/*!
	Implementation of Movable.
	*/
	void update();

protected:
	/*!
	Implementation of Movable.
	*/
	void OnPosition(irr::u32 position);
};