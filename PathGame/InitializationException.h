#pragma once

#include <irrlicht.h>

using namespace irr;
using namespace core;

class InitializationException
{
public:
	InitializationException(const stringw& message);
	~InitializationException(void);

	const stringw& getMessage() const;

private:
	const stringw& _message;
};