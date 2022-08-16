#include "ParallelVecProjectionGeometry2D.h"

#include <cstring>
#include <sstream>

//----------------------------------------------------------------------------------------
// Default constructor. Sets all variables to zero. 
CParallelVecProjectionGeometry2D::CParallelVecProjectionGeometry2D()
{
	_clear();
	m_pProjectionAngles = 0;
}

//----------------------------------------------------------------------------------------
// Constructor.
CParallelVecProjectionGeometry2D::CParallelVecProjectionGeometry2D(int _iProjectionAngleCount,
	int _iDetectorCount,
	const SParProjection* _pProjectionAngles)
{
	this->initialize(_iProjectionAngleCount,
		_iDetectorCount,
		_pProjectionAngles);
}

//----------------------------------------------------------------------------------------
// Copy Constructor
CParallelVecProjectionGeometry2D::CParallelVecProjectionGeometry2D(const CParallelVecProjectionGeometry2D& _projGeom)
{
	_clear();
	this->initialize(_projGeom.m_iProjectionAngleCount,
		_projGeom.m_iDetectorCount,
		_projGeom.m_pProjectionAngles);
}

//----------------------------------------------------------------------------------------
// Destructor.
CParallelVecProjectionGeometry2D::~CParallelVecProjectionGeometry2D()
{
	// TODO
	delete[] m_pProjectionAngles;
}


//----------------------------------------------------------------------------------------
// Initialization.
bool CParallelVecProjectionGeometry2D::initialize(int _iProjectionAngleCount,
	int _iDetectorCount,
	const SParProjection* _pProjectionAngles)
{
	m_iProjectionAngleCount = _iProjectionAngleCount;
	m_iDetectorCount = _iDetectorCount;
	m_pProjectionAngles = new SParProjection[m_iProjectionAngleCount];
	for (int i = 0; i < m_iProjectionAngleCount; ++i)
		m_pProjectionAngles[i] = _pProjectionAngles[i];

	// TODO: check?

	// success
	m_bInitialized = _check();
	return m_bInitialized;
}

//----------------------------------------------------------------------------------------
// Clone
CProjectionGeometry2D* CParallelVecProjectionGeometry2D::clone()
{
	return new CParallelVecProjectionGeometry2D(*this);
}

//----------------------------------------------------------------------------------------
// is equal
bool CParallelVecProjectionGeometry2D::isEqual(CProjectionGeometry2D* _pGeom2) const
{
	if (_pGeom2 == NULL) return false;

	// try to cast argument to CParallelVecProjectionGeometry2D
	CParallelVecProjectionGeometry2D* pGeom2 = dynamic_cast<CParallelVecProjectionGeometry2D*>(_pGeom2);
	if (pGeom2 == NULL) return false;

	// both objects must be initialized
	if (!m_bInitialized || !pGeom2->m_bInitialized) return false;

	// check all values
	if (m_iProjectionAngleCount != pGeom2->m_iProjectionAngleCount) return false;
	if (m_iDetectorCount != pGeom2->m_iDetectorCount) return false;

	for (int i = 0; i < m_iProjectionAngleCount; ++i) {
		if (memcmp(&m_pProjectionAngles[i], &pGeom2->m_pProjectionAngles[i], sizeof(m_pProjectionAngles[i])) != 0) return false;
	}

	return true;
}

//----------------------------------------------------------------------------------------
// Is of type
bool CParallelVecProjectionGeometry2D::isOfType(const std::string& _sType)
{
	return (_sType == "parallel_vec");
}

//----------------------------------------------------------------------------------------

void CParallelVecProjectionGeometry2D::getRayParams(int _iRow, int _iColumn, float& _fT, float& _fTheta) const
{
	// not implemented
	ASTRA_ASSERT(false);
}

//----------------------------------------------------------------------------------------

bool CParallelVecProjectionGeometry2D::_check()
{
	// TODO
	return true;
}
