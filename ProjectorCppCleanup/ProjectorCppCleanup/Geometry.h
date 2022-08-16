#pragma once
#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include <cassert>
#include <cmath>

#include "DataStructure.h"

const float PI = 3.14159265358979323846264338328f;

struct Coordinates {
	float sourceX, sourceY;
	float detectorX0, detectorY0;
	float detectorPixelWidth, detectorPixelHeight;
};

class Geometry {
public:
	Geometry();
	Geometry(
		int _projectionAngleCount,
		int _detectorCount,
		float _detectorWidth,
		const float* _projectionAnglesRad,
		float _sourceDistance,
		float _detectorDistance,
		int _FOVColumnCount,
		int _FOVRowCount
	);
	virtual ~Geometry();

	int getProjectionAngleCount() const;
	int getDetectorCount() const;
	const Coordinates* getProjectionAngles() const { return projectionAngles; };

	int getFOVColumnCount() const;
	int getFOVRowCount() const;
	float getPixelWidth() const;
	float getPixelHeight() const;
	float getWindowMinX() const;
	float getWindowMaxY() const;

protected:
	int projectionAngleCount;
	int detectorCount;
	float detectorWidth;
	Coordinates* projectionAngles;

	int FOVColumnCount;  // x
	int FOVRowCount;     // y
	float pixelWidth;    // x
	float pixelHeight;   // y
	float windowMinX;
	float windowMinY;
	float windowMaxX;
	float windowMaxY;
	float windowWidth;   // x
	float windowHeight;  // y

private:
	float sourceDistance;
	float detectorDistance;
};


inline int Geometry::getProjectionAngleCount() const { return projectionAngleCount; }
inline int Geometry::getDetectorCount() const { return detectorCount; }

inline int Geometry::getFOVColumnCount() const { return FOVColumnCount; }
inline int Geometry::getFOVRowCount() const { return FOVRowCount; }
inline float Geometry::getPixelWidth() const { return pixelWidth; }
inline float Geometry::getPixelHeight() const { return pixelHeight; }
inline float Geometry::getWindowMinX() const { return windowMinX; }
inline float Geometry::getWindowMaxY() const { return windowMaxY; }

#endif
