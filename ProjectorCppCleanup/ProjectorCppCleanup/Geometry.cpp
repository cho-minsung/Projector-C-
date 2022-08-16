#include <iostream>
#include "Geometry.h"

Geometry::Geometry() {
	projectionAngleCount = 0;
	detectorCount = 0;
	detectorWidth = 0.0f;
	projectionAngles = NULL;
	sourceDistance = 0.0f;
	detectorDistance = 0.0f;
}

Geometry::Geometry(
	int _projectionAngleCount,
	int _detectorCount,
	float _detectorWidth,
	const float* _projectionAngles,
	float _sourceDistance,
	float _detectorDistance,
	int _FOVColumnCount,
	int _FOVRowCount
) {
	projectionAngleCount = _projectionAngleCount;
	detectorCount = _detectorCount;
	sourceDistance = _sourceDistance;
	detectorDistance = _detectorDistance;
	detectorWidth = _detectorWidth;
	projectionAngles = new Coordinates[projectionAngleCount];

	float detectorStartX0 = detectorCount * detectorWidth / -2.0f;
	
	for (unsigned int i = 0; i < projectionAngleCount; ++i) {
		float angle = _projectionAngles[i] + PI / 2;

		projectionAngles[i].sourceX = sourceDistance * sin(angle);
		projectionAngles[i].sourceY = -sourceDistance * cos(angle);
		projectionAngles[i].detectorX0 = detectorStartX0 * cos(angle) - detectorDistance * sin(angle);
		projectionAngles[i].detectorY0 = detectorStartX0 * sin(angle) + detectorDistance * cos(angle);
		projectionAngles[i].detectorPixelWidth = detectorWidth * cos(angle);
		projectionAngles[i].detectorPixelHeight = detectorWidth * sin(angle);
	}

	FOVColumnCount = _FOVColumnCount;
	FOVRowCount = _FOVRowCount;
	windowMinX = -FOVColumnCount / 2.0f;
	windowMaxX = FOVColumnCount / 2.0f;
	windowMinY = -FOVRowCount / 2.0f;
	windowMaxY = FOVRowCount / 2.0f;
	windowWidth = windowMaxX - windowMinX;
	windowHeight = windowMaxY - windowMinY;
	pixelWidth = (windowWidth / (float)FOVColumnCount);
	pixelHeight = (windowHeight / (float)FOVRowCount);
}

Geometry::~Geometry() {}

