#ifndef _INC_ASTRA_FANFLATPROJECTIONGEOMETRY2D
#define _INC_ASTRA_FANFLATPROJECTIONGEOMETRY2D

#include "ProjectionGeometry2D.h"
#include "FanFlatVecProjectionGeometry2D.h"

#include <cmath>

class CFanFlatProjectionGeometry2D : public CProjectionGeometry2D
{
	/**
		* Distance from the origin of the coordinate system to the source.
		*/
	float m_fOriginSourceDistance;

	/**
		* Distance from the origin of the coordinate system to the detector (i.e., the distance between the origin and its orthogonal projection
		* onto the detector array).
		*/
	float m_fOriginDetectorDistance;

public:

	/** Default constructor. Sets all variables to zero. Note that this constructor leaves the object in an unusable state and must
		* be followed by a call to init().
		*/
	CFanFlatProjectionGeometry2D();

	/** Constructor.
		*
		* @param _iProjectionAngleCount Number of projection angles.
		* @param _iDetectorCount Number of detectors, i.e., the number of detector measurements for each projection angle.
		* @param _fDetectorWidth Width of a detector cell, in unit lengths. All detector cells are assumed to have equal width.
		* @param _pfProjectionAngles Pointer to an array of projection angles. The angles will be copied from this array.
		*		  All angles are represented in radians.
		* @param _fOriginSourceDistance Distance from the origin of the coordinate system to the source
		* @param _fOriginDetectorDistance Distance from the origin of the coordinate system to the detector
		*/
	CFanFlatProjectionGeometry2D(int _iProjectionAngleCount,
		int _iDetectorCount,
		float _fDetectorWidth,
		const float* _pfProjectionAngles,
		float _fOriginSourceDistance,
		float _fOriginDetectorDistance);

	/** Copy constructor.
		*/
	CFanFlatProjectionGeometry2D(const CFanFlatProjectionGeometry2D& _projGeom);

	/** Assignment operator.
		*/
	CFanFlatProjectionGeometry2D& operator=(const CFanFlatProjectionGeometry2D& _other);

	/** Destructor.
		*/
	virtual ~CFanFlatProjectionGeometry2D();

	/** Initialization. This function MUST be called after using the default constructor and MAY be called to
		* reset a previously initialized object.
		*
		* @param _iProjectionAngleCount Number of projection angles.
		* @param _iDetectorCount Number of detectors, i.e., the number of detector measurements for each projection angle.
		* @param _fDetectorWidth Width of a detector cell, in unit lengths. All detector cells are assumed to have equal width.
		* @param _pfProjectionAngles Pointer to an array of projection angles. The angles will be copied from this array.
		* @param _fOriginSourceDistance Distance from the origin of the coordinate system to the source
		* @param _fOriginDetectorDistance Distance from the origin of the coordinate system to the detector
		*/
	bool initialize(int _iProjectionAngleCount,
		int _iDetectorCount,
		float _fDetectorWidth,
		const float* _pfProjectionAngles,
		float _fOriginSourceDistance,
		float _fOriginDetectorDistance);

	/** Create a hard copy.
	*/
	virtual CProjectionGeometry2D* clone();

	/** Returns true if the type of geometry defined in this class is the one specified in _sType.
		*
		* @param _sType geometry type to compare to.
		* @return true if _sType == "fanflat".
		*/
	virtual bool isOfType(const std::string& _sType);

	/** Return true if this geometry instance is the same as the one specified.
		*
		* @return true if this geometry instance is the same as the one specified.
		*/
	virtual bool isEqual(CProjectionGeometry2D*) const;

	/** Returns the distance from the origin of the coordinate system to the source.
		*
		* @return Distance from the origin of the coordinate system to the source
		*/
	float getOriginSourceDistance() const;

	/** Returns the distance from the origin of the coordinate system to the detector
		* (i.e., the distance between the origin and its orthogonal projection onto the detector array).
		*
		* @return Distance from the origin of the coordinate system to the detector
		*/
	float getOriginDetectorDistance() const;

	/** Returns the distance from the source to the detector
		* (i.e., the distance between the source and its orthogonal projection onto the detector array).
		*
		* @return Distance from the source to the detector
		*/
	float getSourceDetectorDistance() const;

	/** Get the value for t and theta, based upon the row and column index.
		*
		* @param _iRow		row index
		* @param _iColumn	column index
		* @param _fT		output: value of t
		* @param _fTheta	output: value of theta, always lies within the [0,pi[ interval.
		*/
	virtual void getRayParams(int _iRow, int _iColumn, float& _fT, float& _fTheta) const;

	/**
		* Returns a vector describing the direction of a ray belonging to a certain detector
		*
		* @param _iProjectionIndex index of projection
		* @param _iProjectionIndex index of detector
		*
		* @return a unit vector describing the direction
		*/
	/*virtual CVector3D getProjectionDirection(int _iProjectionIndex, int _iDetectorIndex);*/

	/** Create a vector geom
	*/
	CFanFlatVecProjectionGeometry2D* toVectorGeometry();
};



// Returns the distance from the origin of the coordinate system to the source.
inline float CFanFlatProjectionGeometry2D::getOriginSourceDistance() const
{
	return m_fOriginSourceDistance;
}


// Returns the distance from the origin of the coordinate system to the detector.
inline float CFanFlatProjectionGeometry2D::getOriginDetectorDistance() const
{
	return m_fOriginDetectorDistance;
}


// Returns the distance from the source to the detector.
inline float CFanFlatProjectionGeometry2D::getSourceDetectorDistance() const
{
	return (m_fOriginSourceDistance + m_fOriginDetectorDistance);
}


// Get T and Theta
inline void CFanFlatProjectionGeometry2D::getRayParams(int _iRow, int _iColumn, float& _fT, float& _fTheta) const
{
	assert(m_bInitialized);

	// get the distance between the center of the detector array and the detector.
	float det_offset = indexToDetectorOffset(_iColumn);

	// get the angle between the center ray of the projection and the projection.
	float alpha = atan(det_offset / getSourceDetectorDistance());

	// calculate t and theta
	_fT = m_fOriginSourceDistance * sin(alpha);
	_fTheta = getProjectionAngle(_iRow) + alpha;

	// if theta is larger than pi, flip of the origin
	if (PI <= _fTheta) {
		_fTheta -= PI;
		_fT = -_fT;
	}
	// if theta is below 0, flip
	if (_fTheta < 0) {
		_fTheta += PI;
		_fT = -_fT;
	}
}

#endif /* _INC_ASTRA_FANFLATPROJECTIONGEOMETRY2D */

