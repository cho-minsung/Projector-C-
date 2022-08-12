#ifndef _INC_ASTRA_PROJECTIONGEOMETRY2D
#define _INC_ASTRA_PROJECTIONGEOMETRY2D

#include "Globals.h"

#include <string>
#include <cmath>
#include <vector>

/**
	* This abstract base class defines the projection geometry.
	* It has a number of data fields, such as width of detector
	* pixels, projection angles, number of detector pixels and object offsets
	* for every projection angle.
	*/
class CProjectionGeometry2D
{

protected:

	bool m_bInitialized;	///< Has the object been intialized?

	/** Number of projection angles
		*/
	int m_iProjectionAngleCount;

	/** Number of detectors, i.e., the number of detector measurements for each projection angle.
		*/
	int m_iDetectorCount;

	/** Width of a detector pixel, i.e., the distance between projected rays (or width of projected strips).
		*/
	float m_fDetectorWidth;

	/** Dynamically allocated array of projection angles. All angles are represented in radians and lie in
		* the [0,2pi[ interval.
		*/
	float* m_pfProjectionAngles;

	/** Default constructor. Sets all numeric member variables to 0 and all pointer member variables to NULL.
		*
		* If an object is constructed using this default constructor, it must always be followed by a call
		* to one of the init() methods before the object can be used. Any use before calling init() is not
		* allowed, except calling the member function isInitialized().
		*
		*/
	CProjectionGeometry2D();

	/** Constructor. Create an instance of the CProjectionGeometry2D class.
		*
		*  @param _iProjectionAngleCount Number of projection angles.
		*  @param _iDetectorCount Number of detectors, i.e., the number of detector measurements for each projection angle.
		*  @param _fDetectorWidth Width of a detector cell, in unit lengths. All detector cells are assumed to have equal width.
		*  @param _pfProjectionAngles Pointer to an array of projection angles. The angles will be copied from this array.
		*  All angles are represented in radians.
		*/
	CProjectionGeometry2D(int _iProjectionAngleCount,
		int _iDetectorCount,
		float _fDetectorWidth,
		const float* _pfProjectionAngles);

	/** Copy constructor.
		*/
	CProjectionGeometry2D(const CProjectionGeometry2D& _projGeom);

	/** Check variable values.
		*/
	bool _check();

	/** Clear all member variables, setting all numeric variables to 0 and all pointers to NULL.
		* Should only be used by constructors.  Otherwise use the clear() function.
		*/
	void _clear();

	/** Initialization. Initializes an instance of the CProjectionGeometry2D class. If the object has been
		* initialized before, the object is reinitialized and memory is freed and reallocated if necessary.
		*
		*  @param _iProjectionAngleCount Number of projection angles.
		*  @param _iDetectorCount Number of detectors, i.e., the number of detector measurements for each projection angle.
		*  @param _fDetectorWidth Width of a detector cell, in unit lengths. All detector cells are assumed to have equal width.
		*  @param _pfProjectionAngles Pointer to an array of projection angles. The angles will be copied from this array.
		*/
	bool _initialize(int _iProjectionAngleCount,
		int _iDetectorCount,
		float _fDetectorWidth,
		const float* _pfProjectionAngles);

public:

	/** Destructor
		*/
	virtual ~CProjectionGeometry2D();

	/** Clear all member variables, setting all numeric variables to 0 and all pointers to NULL.
		*/
	virtual void clear();

	/** Create a hard copy.
	*/
	virtual CProjectionGeometry2D* clone() = 0;

	/** Get the initialization state of the object.
		*
		* @return true iff the object has been initialized
		*/
	bool isInitialized() const;

	/** Return true if this geometry instance is the same as the one specified.
		*
		* @return true if this geometry instance is the same as the one specified.
		*/
	virtual bool isEqual(CProjectionGeometry2D*) const = 0;

	/** Get the number of projection angles.
		*
		* @return Number of projection angles
		*/
	int getProjectionAngleCount() const;

	/** Get the number of detectors.
		*
		* @return Number of detectors, i.e., the number of detector measurements for each projection angle.
		*/
	int getDetectorCount() const;

	/** Get the width of a detector.
		*
		* @return Width of a detector, in unit lengths
		*/
	float getDetectorWidth() const;

	/** Get a projection angle, given by its index. The angle is represented in Radians.
		*
		* @return Projection angle with index _iProjectionIndex
		*/
	float getProjectionAngle(int _iProjectionIndex) const;

	/** Returns a buffer containing all projection angles. The element count of the buffer is equal
		*  to the number given by getProjectionAngleCount.
		*
		*  The angles are in radians.
		*
		* @return Pointer to buffer containing the angles.
		*/
	const float* getProjectionAngles() const;

	/** Get a projection angle, given by its index. The angle is represented in degrees.
		*
		* @return Projection angle with index _iProjectionIndex
		*/
	float getProjectionAngleDegrees(int _iProjectionIndex) const;

	/** Get the index coordinate of a point on a detector array.
		*
		* @param _fOffset	distance between the center of the detector array and a certain point
		* @return			the location of the point in index coordinates (still float, not rounded)
		*/
	virtual float detectorOffsetToIndexFloat(float _fOffset) const;

	/** Get the index coordinate of a point on a detector array.
		*
		* @param _fOffset	distance between the center of the detector array and a certain point
		* @return			the index of the detector that is hit, -1 if detector array isn't hit.
		*/
	virtual int detectorOffsetToIndex(float _fOffset) const;

	/** Get the offset of a detector based on its index coordinate.
		*
		* @param _iIndex	the index of the detector.
		* @return			the offset from the center of the detector array.
		*/
	virtual float indexToDetectorOffset(int _iIndex) const;

	/** Get the angle and detector index of a sinogram pixel
		*
		* @param _iIndex	the index of the detector pixel in the sinogram.
		* @param _iAngleIndex	output: index of angle
		* @param _iDetectorIndex output: index of detector
		*/
	virtual void indexToAngleDetectorIndex(int _iIndex, int& _iAngleIndex, int& _iDetectorIndex) const;

	/** Get the value for t and theta, based upon the row and column index.
		*
		* @param _iRow		row index
		* @param _iColumn	column index
		* @param _fT		output: value of t
		* @param _fTheta	output: value of theta, always lies within the [0,pi[ interval.
		*/
	virtual void getRayParams(int _iRow, int _iColumn, float& _fT, float& _fTheta) const;

	/** Returns true if the type of geometry defined in this class is the one specified in _sType.
		*
		* @param _sType geometry type to compare to.
		* @return true if the type of geometry defined in this class is the one specified in _sType.
		*/
	virtual bool isOfType(const std::string& _sType) = 0;
};



//----------------------------------------------------------------------------------------
// Inline member functions
//----------------------------------------------------------------------------------------


// Get the initialization state.
inline bool CProjectionGeometry2D::isInitialized() const
{
	return m_bInitialized;
}


// Get the number of detectors.
inline int CProjectionGeometry2D::getDetectorCount() const
{
	ASTRA_ASSERT(m_bInitialized);
	return m_iDetectorCount;
}

// Get the width of a single detector (in unit lengths).
inline float CProjectionGeometry2D::getDetectorWidth() const
{
	ASTRA_ASSERT(m_bInitialized);
	return m_fDetectorWidth;
}

// Get the number of projection angles.
inline int CProjectionGeometry2D::getProjectionAngleCount() const
{
	ASTRA_ASSERT(m_bInitialized);
	return m_iProjectionAngleCount;
}

// Get pointer to buffer used to store projection angles.
inline const float* CProjectionGeometry2D::getProjectionAngles() const
{
	ASTRA_ASSERT(m_bInitialized);
	return m_pfProjectionAngles;
}

// Get a projection angle, represented in Radians.
inline float CProjectionGeometry2D::getProjectionAngle(int _iProjectionIndex) const
{
	// basic checks
	ASTRA_ASSERT(m_bInitialized);
	ASTRA_ASSERT(_iProjectionIndex >= 0);
	ASTRA_ASSERT(_iProjectionIndex < m_iProjectionAngleCount);

	return m_pfProjectionAngles[_iProjectionIndex];
}

// Get a projection angle, represented in degrees.
inline float CProjectionGeometry2D::getProjectionAngleDegrees(int _iProjectionIndex) const
{
	// basic checks
	ASTRA_ASSERT(m_bInitialized);
	ASTRA_ASSERT(_iProjectionIndex >= 0);
	ASTRA_ASSERT(_iProjectionIndex < m_iProjectionAngleCount);

	return (m_pfProjectionAngles[_iProjectionIndex] * 180.0f / PI32);
}

// Get T and Theta
inline void CProjectionGeometry2D::getRayParams(int _iRow, int _iColumn, float& _fT, float& _fTheta) const
{
	ASTRA_ASSERT(m_bInitialized);
	_fT = indexToDetectorOffset(_iColumn);
	_fTheta = getProjectionAngle(_iRow);
	if (PI <= _fTheta) {
		_fTheta -= PI;
		_fT = -_fT;
	}
}

// detector offset -> detector index
inline int CProjectionGeometry2D::detectorOffsetToIndex(float _fOffset) const
{
	int res = (int)(detectorOffsetToIndexFloat(_fOffset) + 0.5f);
	return (res > 0 && res <= m_iDetectorCount) ? res : -1;
}

// detector offset -> detector index (float)
inline float CProjectionGeometry2D::detectorOffsetToIndexFloat(float _fOffset) const
{
	return (_fOffset / m_fDetectorWidth) + ((m_iDetectorCount - 1.0f) * 0.5f);
}

// detector index -> detector offset
inline float CProjectionGeometry2D::indexToDetectorOffset(int _iIndex) const
{
	return (_iIndex - (m_iDetectorCount - 1.0f) * 0.5f) * m_fDetectorWidth;
}

// sinogram index -> angle and detecor index
inline void CProjectionGeometry2D::indexToAngleDetectorIndex(int _iIndex, int& _iAngleIndex, int& _iDetectorIndex) const
{
	_iAngleIndex = _iIndex / m_iDetectorCount;
	_iDetectorIndex = _iIndex % m_iDetectorCount;
}


#endif /* _INC_ASTRA_PROJECTIONGEOMETRY2D */
