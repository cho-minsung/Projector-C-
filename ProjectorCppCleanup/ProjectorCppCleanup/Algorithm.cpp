#include <iostream>

#include "Algorithm.h"

Algorithm::Algorithm() {
	geom = NULL;
	sino = NULL;
	phantom = NULL;
};

Algorithm::Algorithm(
	Geometry* _geom,
	DataStructure* _phantom,
	DataStructure* _sino
) {
	geom = _geom;
	phantom = _phantom;
	sino = _sino;
}

Algorithm::~Algorithm() {};

bool Algorithm::initSinoData(int _rayIndex) {
	sino->getData()[_rayIndex] = 0.0f;
	return true;
}

void Algorithm::addWeight(int _rayIndex, int _phantomIndex, float _weight) {
	sino->getData()[_rayIndex] += phantom->getData()[_phantomIndex] * _weight;
};

void Algorithm::runProjection() {
	sino->setData(0.0f);

	// precomputations
	const float pixelWidth = geom->getPixelWidth();
	const float pixelHeight = geom->getPixelHeight();
	const float pixelWidth_inv = 1.0f / pixelWidth;
	const float pixelHeight_inv = 1.0f / pixelHeight;
	const int FOVColumnCount = geom->getFOVColumnCount();
	const int FOVRowCount = geom->getFOVRowCount();
	const int detectorCount = geom->getDetectorCount();
	const float adjustX = geom->getWindowMinX() + pixelWidth * 0.5f;
	const float adjustY = geom->getWindowMaxY() - pixelHeight * 0.5f;

	// loop angles
	for (int angleIndex = 0; angleIndex < geom->getProjectionAngleCount(); ++angleIndex) {

		// variables
		float Dx, Dy, Rx, Ry, S, T, weight, c, r, deltac, deltar, offset, RxOverRy, RyOverRx;
		float lengthPerRow, lengthPerCol, invTminSTimesLengthPerRow, invTminSTimesLengthPerCol;
		int phantomIndex, rayIndex, row, col, detectorIndex;

		const Coordinates* proj = &geom->getProjectionAngles()[angleIndex];  // changed to coordinates

		// loop detectors
		for (detectorIndex = 0; detectorIndex < geom->getDetectorCount(); ++detectorIndex) {
			rayIndex = angleIndex * detectorCount + detectorIndex;

			//if (!initSinoData(rayIndex)) continue;

			Dx = proj->detectorX0 + (detectorIndex + 0.5f) * proj->detectorPixelWidth;
			Dy = proj->detectorY0 + (detectorIndex + 0.5f) * proj->detectorPixelHeight;

			Rx = proj->sourceX - Dx;
			Ry = proj->sourceY - Dy;

			bool vertical = fabs(Rx) < fabs(Ry);
			bool isin = false;

			// vertically
			if (vertical) {
				RxOverRy = Rx / Ry;
				lengthPerRow = pixelWidth * sqrt(Rx * Rx + Ry * Ry) / abs(Ry);
				deltac = -pixelHeight * RxOverRy * pixelWidth_inv;
				S = 0.5f - 0.5f * fabs(RxOverRy);
				T = 0.5f + 0.5f * fabs(RxOverRy);
				invTminSTimesLengthPerRow = lengthPerRow / (T - S);

				// calculate c for row 0
				c = (Dx + (adjustY - Dy) * RxOverRy - adjustX) * pixelWidth_inv;

				// for each row
				for (row = 0; row < FOVRowCount; ++row, c += deltac) {

					col = int(floor(c + 0.5f));
					if (col < -1 || col > FOVColumnCount) { if (!isin) continue; else break; }
					offset = c - float(col);

					// left
					if (offset < -S) {
						weight = (offset + T) * invTminSTimesLengthPerRow;

						phantomIndex = row * FOVColumnCount + col - 1;
						if (col > 0) {
							addWeight(rayIndex, phantomIndex, lengthPerRow - weight);
						}

						phantomIndex++;
						if (col >= 0 && col < FOVColumnCount) {
							addWeight(rayIndex, phantomIndex, weight);
						}
					}

					// right
					else if (S < offset) {
						weight = (offset - S) * invTminSTimesLengthPerRow;

						phantomIndex = row * FOVColumnCount + col;
						if (col >= 0 && col < FOVColumnCount) {
							addWeight(rayIndex, phantomIndex, lengthPerRow - weight);
						}

						phantomIndex++;
						if (col + 1 < FOVColumnCount) {
							addWeight(rayIndex, phantomIndex, weight);
						}
					}

					// centre
					else if (col >= 0 && col < FOVColumnCount) {
						phantomIndex = row * FOVColumnCount + col;
						addWeight(rayIndex, phantomIndex, lengthPerRow);
					}
					isin = true;
				}
			}

			// horizontally
			else {
				RyOverRx = Ry / Rx;
				lengthPerCol = pixelHeight * sqrt(Rx * Rx + Ry * Ry) / abs(Rx);
				deltar = -pixelWidth * RyOverRx * pixelHeight_inv;
				S = 0.5f - 0.5f * fabs(RyOverRx);
				T = 0.5f + 0.5f * fabs(RyOverRx);
				invTminSTimesLengthPerCol = lengthPerCol / (T - S);

				// calculate r for col 0
				r = -(Dy + (adjustX - Dx) * RyOverRx - adjustY) * pixelHeight_inv;

				// for each col
				for (col = 0; col < FOVColumnCount; ++col, r += deltar) {

					row = int(floor(r + 0.5f));
					if (row < -1 || row > FOVRowCount) { if (!isin) continue; else break; }
					offset = r - float(row);

					// up
					if (offset < -S) {
						weight = (offset + T) * invTminSTimesLengthPerCol;

						phantomIndex = (row - 1) * FOVColumnCount + col;
						if (row > 0) {
							addWeight(rayIndex, phantomIndex, lengthPerCol - weight);
						}

						phantomIndex += FOVColumnCount;
						if (row >= 0 && row < FOVRowCount) {
							addWeight(rayIndex, phantomIndex, weight);
						}
					}

					// down
					else if (S < offset) {
						weight = (offset - S) * invTminSTimesLengthPerCol;

						phantomIndex = row * FOVColumnCount + col;
						if (row >= 0 && row < FOVRowCount) {
							addWeight(rayIndex, phantomIndex, lengthPerCol - weight);
						}

						phantomIndex += FOVColumnCount;
						if (row + 1 < FOVRowCount) {
							addWeight(rayIndex, phantomIndex, weight);
						}
					}

					// centre
					else if (row >= 0 && row < FOVRowCount) {
						phantomIndex = row * FOVColumnCount + col;
						addWeight(rayIndex, phantomIndex, lengthPerCol);
					}
					isin = true;
				}
			}
		} // end loop detector
	} // end loop angles
}
