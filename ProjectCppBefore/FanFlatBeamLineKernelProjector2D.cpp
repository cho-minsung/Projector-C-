#include "FanFlatBeamLineKernelProjector2D.h"

#include <cmath>
#include <cstring>
#include <algorithm>

#include "DataProjectorPolicies.h"
#include "FanFlatBeamLineKernelProjector2D.inl"

// type of the projector, needed to register with CProjectorFactory
std::string CFanFlatBeamLineKernelProjector2D::type = "line_fanflat";


//----------------------------------------------------------------------------------------
// default constructor
CFanFlatBeamLineKernelProjector2D::CFanFlatBeamLineKernelProjector2D()
{
	_clear();
}

//----------------------------------------------------------------------------------------
// constructor
CFanFlatBeamLineKernelProjector2D::CFanFlatBeamLineKernelProjector2D(CFanFlatProjectionGeometry2D* _pProjectionGeometry,
	CVolumeGeometry2D* _pReconstructionGeometry)

{
	_clear();
	initialize(_pProjectionGeometry, _pReconstructionGeometry);
}

//----------------------------------------------------------------------------------------
// destructor
CFanFlatBeamLineKernelProjector2D::~CFanFlatBeamLineKernelProjector2D()
{
	clear();
}

//---------------------------------------------------------------------------------------
// Clear - Constructors
void CFanFlatBeamLineKernelProjector2D::_clear()
{
	CProjector2D::_clear();
	m_bIsInitialized = false;
}

//---------------------------------------------------------------------------------------
// Clear - Public
void CFanFlatBeamLineKernelProjector2D::clear()
{
	CProjector2D::clear();
	m_bIsInitialized = false;
}

//---------------------------------------------------------------------------------------
// Check
bool CFanFlatBeamLineKernelProjector2D::_check()
{
	// check base class
	ASTRA_CONFIG_CHECK(CProjector2D::_check(), "FanFlatBeamLineKernelProjector2D", "Error in Projector2D initialization");

	ASTRA_CONFIG_CHECK(dynamic_cast<CFanFlatProjectionGeometry2D*>(m_pProjectionGeometry) || dynamic_cast<CFanFlatVecProjectionGeometry2D*>(m_pProjectionGeometry), "FanFlatBeamLineKernelProjector2D", "Unsupported projection geometry");

	ASTRA_CONFIG_CHECK(abs(m_pVolumeGeometry->getPixelLengthX() / m_pVolumeGeometry->getPixelLengthY()) - 1 < eps, "FanFlatBeamLineKernelProjector2D", "Pixel height must equal pixel width.");

	// success
	return true;
}

//---------------------------------------------------------------------------------------
// Initialize
bool CFanFlatBeamLineKernelProjector2D::initialize(CFanFlatProjectionGeometry2D* _pProjectionGeometry,
	CVolumeGeometry2D* _pVolumeGeometry)
{
	// if already initialized, clear first
	if (m_bIsInitialized) {
		clear();
	}

	// hardcopy geometries
	m_pProjectionGeometry = _pProjectionGeometry->clone();
	m_pVolumeGeometry = _pVolumeGeometry->clone();

	// success
	m_bIsInitialized = _check();
	return m_bIsInitialized;
}

//----------------------------------------------------------------------------------------
// Get maximum amount of weights on a single ray
int CFanFlatBeamLineKernelProjector2D::getProjectionWeightsCount(int _iProjectionIndex)
{
	int maxDim = std::max(m_pVolumeGeometry->getGridRowCount(), m_pVolumeGeometry->getGridColCount());
	return maxDim * 2 + 1;
}

//----------------------------------------------------------------------------------------
// Single Ray Weights
void CFanFlatBeamLineKernelProjector2D::computeSingleRayWeights(int _iProjectionIndex,
	int _iDetectorIndex,
	SPixelWeight* _pWeightedPixels,
	int _iMaxPixelCount,
	int& _iStoredPixelCount)
{
	ASTRA_ASSERT(m_bIsInitialized);
	StorePixelWeightsPolicy p(_pWeightedPixels, _iMaxPixelCount);
	projectSingleRay(_iProjectionIndex, _iDetectorIndex, p);
	_iStoredPixelCount = p.getStoredPixelCount();
}

//----------------------------------------------------------------------------------------
//Result is always in [-PI/2; PI/2]
float CFanFlatBeamLineKernelProjector2D::angleBetweenVectors(float _fAX, float _fAY, float _fBX, float _fBY)
{
	float sinAB = (_fAX * _fBY - _fAY * _fBX) / sqrt((_fAX * _fAX + _fAY * _fAY) * (_fBX * _fBX + _fBY * _fBY));
	return asin(sinAB);
}

//----------------------------------------------------------------------------------------
