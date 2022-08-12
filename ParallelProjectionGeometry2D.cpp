#include "ParallelProjectionGeometry2D.h"
#include "GeometryUtil2D.h"

#include <cstring>

//----------------------------------------------------------------------------------------
// Default constructor.
CParallelProjectionGeometry2D::CParallelProjectionGeometry2D() :
	CProjectionGeometry2D()
{

}

//----------------------------------------------------------------------------------------
// Constructor.
CParallelProjectionGeometry2D::CParallelProjectionGeometry2D(int _iProjectionAngleCount,
	int _iDetectorCount,
	float _fDetectorWidth,
	const float* _pfProjectionAngles)
{
	_clear();
	initialize(_iProjectionAngleCount,
		_iDetectorCount,
		_fDetectorWidth,
		_pfProjectionAngles);
}

//----------------------------------------------------------------------------------------
CParallelProjectionGeometry2D::CParallelProjectionGeometry2D(const CParallelProjectionGeometry2D& _projGeom)
{
	_clear();
	initialize(_projGeom.m_iProjectionAngleCount,
		_projGeom.m_iDetectorCount,
		_projGeom.m_fDetectorWidth,
		_projGeom.m_pfProjectionAngles);
}

//----------------------------------------------------------------------------------------

CParallelProjectionGeometry2D& CParallelProjectionGeometry2D::operator=(const CParallelProjectionGeometry2D& _other)
{
	if (m_bInitialized)
		delete[] m_pfProjectionAngles;
	m_bInitialized = _other.m_bInitialized;
	if (_other.m_bInitialized) {
		m_iProjectionAngleCount = _other.m_iProjectionAngleCount;
		m_iDetectorCount = _other.m_iDetectorCount;
		m_fDetectorWidth = _other.m_fDetectorWidth;
		m_pfProjectionAngles = new float[m_iProjectionAngleCount];
		memcpy(m_pfProjectionAngles, _other.m_pfProjectionAngles, sizeof(float) * m_iProjectionAngleCount);
	}
	return *this;

}

//----------------------------------------------------------------------------------------
// Destructor.
CParallelProjectionGeometry2D::~CParallelProjectionGeometry2D()
{

}

//----------------------------------------------------------------------------------------
// Initialization.
bool CParallelProjectionGeometry2D::initialize(int _iProjectionAngleCount,
	int _iDetectorCount,
	float _fDetectorWidth,
	const float* _pfProjectionAngles)
{
	_initialize(_iProjectionAngleCount,
		_iDetectorCount,
		_fDetectorWidth,
		_pfProjectionAngles);

	// success
	m_bInitialized = _check();
	return m_bInitialized;
}

//----------------------------------------------------------------------------------------
// Clone
CProjectionGeometry2D* CParallelProjectionGeometry2D::clone()
{
	return new CParallelProjectionGeometry2D(*this);
}

//----------------------------------------------------------------------------------------
// is equal
bool CParallelProjectionGeometry2D::isEqual(CProjectionGeometry2D* _pGeom2) const
{
	if (_pGeom2 == NULL) return false;

	// try to cast argument to CParallelProjectionGeometry2D
	CParallelProjectionGeometry2D* pGeom2 = dynamic_cast<CParallelProjectionGeometry2D*>(_pGeom2);
	if (pGeom2 == NULL) return false;

	// both objects must be initialized
	if (!m_bInitialized || !pGeom2->m_bInitialized) return false;

	// check all values
	if (m_iProjectionAngleCount != pGeom2->m_iProjectionAngleCount) return false;
	if (m_iDetectorCount != pGeom2->m_iDetectorCount) return false;
	if (m_fDetectorWidth != pGeom2->m_fDetectorWidth) return false;

	for (int i = 0; i < m_iProjectionAngleCount; ++i) {
		//	if (m_pfProjectionAngles[i] != pGeom2->m_pfProjectionAngles[i]) return false;
	}

	return true;
}

//----------------------------------------------------------------------------------------
// is of type
bool CParallelProjectionGeometry2D::isOfType(const std::string& _sType)
{
	return (_sType == "parallel");
}

//----------------------------------------------------------------------------------------
CParallelVecProjectionGeometry2D* CParallelProjectionGeometry2D::toVectorGeometry()
{
	SParProjection* vectors = genParProjections(m_iProjectionAngleCount,
		m_iDetectorCount,
		m_fDetectorWidth,
		m_pfProjectionAngles, 0);
	// TODO: ExtraOffsets?
	CParallelVecProjectionGeometry2D* vecGeom = new CParallelVecProjectionGeometry2D();
	vecGeom->initialize(m_iProjectionAngleCount, m_iDetectorCount, vectors);
	delete[] vectors;
	return vecGeom;
}

