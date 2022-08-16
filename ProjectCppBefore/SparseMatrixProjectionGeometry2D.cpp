#include "SparseMatrixProjectionGeometry2D.h"
#include "AstraObjectManager.h"


//----------------------------------------------------------------------------------------
// Default constructor.
CSparseMatrixProjectionGeometry2D::CSparseMatrixProjectionGeometry2D() :
	CProjectionGeometry2D()
{
	m_pMatrix = 0;
}

//----------------------------------------------------------------------------------------
// Constructor.
CSparseMatrixProjectionGeometry2D::CSparseMatrixProjectionGeometry2D(int _iProjectionAngleCount,
	int _iDetectorCount,
	const CSparseMatrix* _pMatrix)
{
	_clear();
	initialize(_iProjectionAngleCount,
		_iDetectorCount,
		_pMatrix);
}

//----------------------------------------------------------------------------------------
CSparseMatrixProjectionGeometry2D::CSparseMatrixProjectionGeometry2D(const CSparseMatrixProjectionGeometry2D& _projGeom)
{
	_clear();
	initialize(_projGeom.m_iProjectionAngleCount,
		_projGeom.m_iDetectorCount,
		_projGeom.m_pMatrix);
}

//----------------------------------------------------------------------------------------

CSparseMatrixProjectionGeometry2D& CSparseMatrixProjectionGeometry2D::operator=(const CSparseMatrixProjectionGeometry2D& _other)
{
	m_bInitialized = _other.m_bInitialized;
	if (_other.m_bInitialized) {
		m_pMatrix = _other.m_pMatrix;
		m_iDetectorCount = _other.m_iDetectorCount;
		m_fDetectorWidth = _other.m_fDetectorWidth;
	}
	return *this;

}

//----------------------------------------------------------------------------------------
// Destructor.
CSparseMatrixProjectionGeometry2D::~CSparseMatrixProjectionGeometry2D()
{
	m_pMatrix = 0;
}

//----------------------------------------------------------------------------------------
// Initialization.
bool CSparseMatrixProjectionGeometry2D::initialize(int _iProjectionAngleCount,
	int _iDetectorCount,
	const CSparseMatrix* _pMatrix)
{
	if (m_bInitialized) {
		clear();
	}

	m_iProjectionAngleCount = _iProjectionAngleCount;
	m_iDetectorCount = _iDetectorCount;

	// FIXME: We should probably require these for consistency?
	m_fDetectorWidth = 1.0f;
	m_pfProjectionAngles = new float[m_iProjectionAngleCount];
	for (int i = 0; i < m_iProjectionAngleCount; ++i)
		m_pfProjectionAngles[i] = 0.0f;

	m_pMatrix = _pMatrix;

	// success
	m_bInitialized = _check();
	return m_bInitialized;
}

//----------------------------------------------------------------------------------------
// Check.
bool CSparseMatrixProjectionGeometry2D::_check()
{
	// check base class
	ASTRA_CONFIG_CHECK(CProjectionGeometry2D::_check(), "SparseMatrixProjectionGeometry2D", "Error in ProjectionGeometry2D initialization");

	ASTRA_CONFIG_CHECK(m_pMatrix, "SparseMatrixProjectionGeometry2D", "No matrix specified");

	ASTRA_CONFIG_CHECK(m_pMatrix->m_iHeight == (unsigned int)(m_iProjectionAngleCount * m_iDetectorCount), "SparseMatrixProjectionGeometry2D", "Matrix height doesn't match projection geometry");

	return true;
}


//----------------------------------------------------------------------------------------
// Clone
CProjectionGeometry2D* CSparseMatrixProjectionGeometry2D::clone()
{
	return new CSparseMatrixProjectionGeometry2D(*this);
}

//----------------------------------------------------------------------------------------
// is equal
bool CSparseMatrixProjectionGeometry2D::isEqual(CProjectionGeometry2D* _pGeom2) const
{
	if (_pGeom2 == NULL) return false;

	// try to cast argument to CSparseMatrixProjectionGeometry2D
	CSparseMatrixProjectionGeometry2D* pGeom2 = dynamic_cast<CSparseMatrixProjectionGeometry2D*>(_pGeom2);
	if (pGeom2 == NULL) return false;

	// both objects must be initialized
	if (!m_bInitialized || !pGeom2->m_bInitialized) return false;

	// check all values
	if (m_iProjectionAngleCount != pGeom2->m_iProjectionAngleCount) return false;
	if (m_iDetectorCount != pGeom2->m_iDetectorCount) return false;
	if (m_fDetectorWidth != pGeom2->m_fDetectorWidth) return false;

	// Maybe check equality of matrices by element?
	if (m_pMatrix != pGeom2->m_pMatrix) return false;

	return true;
}

//----------------------------------------------------------------------------------------
// is of type
bool CSparseMatrixProjectionGeometry2D::isOfType(const std::string& _sType)
{
	return (_sType == "sparse_matrix");
}

