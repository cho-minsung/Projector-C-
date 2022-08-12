#ifndef _INC_ASTRA_GEOMETRYUTIL2D
#define _INC_ASTRA_GEOMETRYUTIL2D


struct SParProjection {
	// the ray direction
	float fRayX, fRayY;

	// the start of the (linear) detector
	float fDetSX, fDetSY;

	// the length of a single detector pixel
	float fDetUX, fDetUY;


	void translate(double dx, double dy) {
		fDetSX += dx;
		fDetSY += dy;
	}
	void scale(double factor) {
		fRayX *= factor;
		fRayY *= factor;
		fDetSX *= factor;
		fDetSY *= factor;
		fDetUX *= factor;
		fDetUY *= factor;
	}
};


struct SFanProjection {
	// the source
	float fSrcX, fSrcY;

	// the start of the (linear) detector
	float fDetSX, fDetSY;

	// the length of a single detector pixel
	float fDetUX, fDetUY;

	void translate(double dx, double dy) {
		fSrcX += dx;
		fSrcY += dy;
		fDetSX += dx;
		fDetSY += dy;
	}
	void scale(double factor) {
		fSrcX *= factor;
		fSrcY *= factor;
		fDetSX *= factor;
		fDetSY *= factor;
		fDetUX *= factor;
		fDetUY *= factor;
	}
};



SParProjection* genParProjections(unsigned int iProjAngles,
	unsigned int iProjDets,
	double fDetSize,
	const float* pfAngles,
	const float* pfExtraOffsets);

SFanProjection* genFanProjections(unsigned int iProjAngles,
	unsigned int iProjDets,
	double fOriginSource, double fOriginDetector,
	double fDetSize,
	const float* pfAngles);

bool getParParameters(const SParProjection& proj, unsigned int iProjDets, float& fAngle, float& fDetSize, float& fOffset);

bool getFanParameters(const SFanProjection& proj, unsigned int iProjDets, float& fAngle, float& fOriginSource, float& fOriginDetector, float& fDetSize, float& fOffset);



#endif
