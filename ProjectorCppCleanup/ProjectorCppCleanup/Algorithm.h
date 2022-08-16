#pragma once

#ifndef _ALGORITHM_H_
#define _ALGORITHM_H_

#include "DataStructure.h"
#include "Geometry.h"

class Algorithm {
public:
	Algorithm();
	Algorithm(
		Geometry* _geom,
		DataStructure* _phantom,
		DataStructure* _sino
	);
	virtual ~Algorithm();
	bool initSinoData(int _rayIndex);
	void addWeight(int _rayIndex, int _phantomIndex, float _weight);
	void runProjection();

protected:
	Geometry* geom;
	DataStructure* phantom;
	DataStructure* sino;
};

#endif
