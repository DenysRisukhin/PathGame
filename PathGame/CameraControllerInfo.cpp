#include "CameraControllerInfo.h"

using namespace irr;
using namespace core;
using namespace io;

CameraControllerInfo::CameraControllerInfo(Game* game, const path& filename): Info(game, filename)
{
	while (next());
}

CameraControllerInfo::~CameraControllerInfo(void)
{
}

void CameraControllerInfo::OnNode(const stringw& name)
{	
	if (name == "cameraAngles") {

		CameraAngles.X = read<f32>("fi");
		CameraAngles.Y = read<f32>("theta");

	}
	else if (name == "cameraRadius") {

		CameraRadius = read<f32>("value");
		MinCameraRadius = read<f32>("min");
		MaxCameraRadius = read<f32>("max");
	}
}