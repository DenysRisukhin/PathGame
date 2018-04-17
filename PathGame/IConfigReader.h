#pragma once

#include <irrlicht.h>

class IConfigReader
{
public:

	virtual bool next() = 0;

	virtual irr::core::stringw getNodeName() = 0;
	
};