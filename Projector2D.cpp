#include "Projector2D.h"

#include "ParallelVecProjectionGeometry2D.h"
#include "FanFlatProjectionGeometry2D.h"
#include "FanFlatVecProjectionGeometry2D.h"
#include "SparseMatrixProjectionGeometry2D.h"
#include "SparseMatrix.h"


//----------------------------------------------------------------------------------------
// constructor
CProjector2D::CProjector2D()
{

	m_bIsInitialized = false;
}

//----------------------------------------------------------------------------------------
// constructor
CProjector2D::CProjector2D(CProjectionGeometry2D* _pProjectionGeometry, CVolumeGeometry2D* _pVolumeGeometry)
{
	m_pProjectionGeometry = _pProjectionGeometry->clone();
	m_pVolumeGeometry = _pVolumeGeometry->clone();
	m_bIsInitialized = true;
}

//----------------------------------------------------------------------------------------
// destructor
CProjector2D::~CProjector2D()
{
	clear();
}

//---------------------------------------------------------------------------------------
// Clear - Constructors
void CProjector2D::_clear()
{
	m_pProjectionGeometry = NULL;
	m_pVolumeGeometry = NULL;
	m_bIsInitialized = false;
}

//---------------------------------------------------------------------------------------
// Clear - Public
void CProjector2D::clear()
{
	if (m_pProjectionGeometry) {
		delete m_pProjectionGeometry;
		m_pProjectionGeometry = NULL;
	}
	if (m_pVolumeGeometry) {
		delete m_pVolumeGeometry;
		m_pVolumeGeometry = NULL;
	}
	m_bIsInitialized = false;
}

//---------------------------------------------------------------------------------------
// Check
bool CProjector2D::_check()
{
	// check pointers
	ASTRA_CONFIG_CHECK(m_pProjectionGeometry, "Projector2D", "Invalid Projection Geometry Object.");
	ASTRA_CONFIG_CHECK(m_pVolumeGeometry, "Projector2D", "Invalid Volume Geometry Object.");

	// check initializations
	ASTRA_CONFIG_CHECK(m_pProjectionGeometry->isInitialized(), "Projector2D", "Projection Geometry Object Not Initialized.");
	ASTRA_CONFIG_CHECK(m_pVolumeGeometry->isInitialized(), "Projector2D", "Volume Geometry Object Not Initialized.");

	// success
	return true;
}

//----------------------------------------------------------------------------------------
// weights of each detector in a projection angle
void CProjector2D::computeProjectionRayWeights(int _iProjection, SPixelWeight* _pfWeightedPixels, int* _piRayStoredPixelCount)
{
	int iPixelBufferSize = getProjectionWeightsCount(_iProjection);

	int iDetector;
	for (iDetector = m_pProjectionGeometry->getDetectorCount() - 1; iDetector >= 0; --iDetector) {
		computeSingleRayWeights(_iProjection,									// projector index
			iDetector,										// detector index
			&_pfWeightedPixels[iDetector * iPixelBufferSize],	// pixel buffer
			iPixelBufferSize,								// pixel buffer size
			_piRayStoredPixelCount[iDetector]);				// stored pixel count
	}

}

//----------------------------------------------------------------------------------------
// explicit projection matrix
CSparseMatrix* CProjector2D::getMatrix()
{
	unsigned int iProjectionCount = m_pProjectionGeometry->getProjectionAngleCount();
	unsigned int iDetectorCount = m_pProjectionGeometry->getDetectorCount();
	unsigned int iRayCount = iProjectionCount * iDetectorCount;
	unsigned int iVolumeSize = m_pVolumeGeometry->getGridTotCount();
	unsigned long lSize = 0;
	unsigned int iMaxRayLength = 0;
	for (unsigned int i = 0; i < iProjectionCount; ++i) {
		unsigned int iRayLength = getProjectionWeightsCount(i);
		lSize += iDetectorCount * iRayLength;
		if (iRayLength > iMaxRayLength)
			iMaxRayLength = iRayLength;
	}
	CSparseMatrix* pMatrix = new CSparseMatrix(iRayCount, iVolumeSize, lSize);

	if (!pMatrix || !pMatrix->isInitialized()) {
		delete pMatrix;
		return 0;
	}

	SPixelWeight* pEntries = new SPixelWeight[iMaxRayLength];
	unsigned long lMatrixIndex = 0;
	for (unsigned int iRay = 0; iRay < iRayCount; ++iRay) {
		pMatrix->m_plRowStarts[iRay] = lMatrixIndex;
		int iPixelCount;
		int iProjIndex, iDetIndex;
		m_pProjectionGeometry->indexToAngleDetectorIndex(iRay, iProjIndex, iDetIndex);
		computeSingleRayWeights(iProjIndex, iDetIndex, pEntries, iMaxRayLength, iPixelCount);

		for (int i = 0; i < iPixelCount; ++i) {
			pMatrix->m_piColIndices[lMatrixIndex] = pEntries[i].m_iIndex;
			pMatrix->m_pfValues[lMatrixIndex] = pEntries[i].m_fWeight;
			++lMatrixIndex;
		}

	}
	pMatrix->m_plRowStarts[iRayCount] = lMatrixIndex;

	delete[] pEntries;
	return pMatrix;
}

