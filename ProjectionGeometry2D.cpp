#include "ProjectionGeometry2D.h"


//----------------------------------------------------------------------------------------
// Default constructor.
CProjectionGeometry2D::CProjectionGeometry2D()
{
	_clear();
}

//----------------------------------------------------------------------------------------
// Constructor.
CProjectionGeometry2D::CProjectionGeometry2D(int _iAngleCount,
	int _iDetectorCount,
	float _fDetectorWidth,
	const float* _pfProjectionAngles)
{
	_clear();
	_initialize(_iAngleCount, _iDetectorCount, _fDetectorWidth, _pfProjectionAngles);
}

//----------------------------------------------------------------------------------------
// Destructor.
CProjectionGeometry2D::~CProjectionGeometry2D()
{
	if (m_bInitialized) {
		clear();
	}
}

//----------------------------------------------------------------------------------------
// Clear all member variables, setting all numeric variables to 0 and all pointers to NULL. 
// Should only be used by constructors.  Otherwise use the clear() function.
void CProjectionGeometry2D::_clear()
{
	m_iProjectionAngleCount = 0;
	m_iDetectorCount = 0;
	m_fDetectorWidth = 0.0f;
	m_pfProjectionAngles = NULL;
	m_bInitialized = false;
}

//----------------------------------------------------------------------------------------
// Clear all member variables, setting all numeric variables to 0 and all pointers to NULL. 
void CProjectionGeometry2D::clear()
{
	m_iProjectionAngleCount = 0;
	m_iDetectorCount = 0;
	m_fDetectorWidth = 0.0f;
	if (m_bInitialized) {
		delete[] m_pfProjectionAngles;
	}
	m_pfProjectionAngles = NULL;
	m_bInitialized = false;
}

//----------------------------------------------------------------------------------------
// Check all variable values.
bool CProjectionGeometry2D::_check()
{
	ASTRA_CONFIG_CHECK(m_iDetectorCount > 0, "ProjectionGeometry2D", "Detector Count should be positive.");
	ASTRA_CONFIG_CHECK(m_fDetectorWidth > 0.0f, "ProjectionGeometry2D", "Detector Width should be positive.");
	ASTRA_CONFIG_CHECK(m_iProjectionAngleCount > 0, "ProjectionGeometry2D", "ProjectionAngleCount should be positive.");
	ASTRA_CONFIG_CHECK(m_pfProjectionAngles != NULL, "ProjectionGeometry2D", "ProjectionAngles not initialized");

	// autofix: angles in [0,2pi[
	for (int i = 0; i < m_iProjectionAngleCount; i++) {
		while (2 * PI <= m_pfProjectionAngles[i]) m_pfProjectionAngles[i] -= 2 * PI;
		while (m_pfProjectionAngles[i] < 0) m_pfProjectionAngles[i] += 2 * PI;
	}

	// success
	return true;
}

//----------------------------------------------------------------------------------------
// Initialization.
bool CProjectionGeometry2D::_initialize(int _iProjectionAngleCount,
	int _iDetectorCount,
	float _fDetectorWidth,
	const float* _pfProjectionAngles)
{
	if (m_bInitialized) {
		clear();
	}

	// copy parameters
	m_iProjectionAngleCount = _iProjectionAngleCount;
	m_iDetectorCount = _iDetectorCount;
	m_fDetectorWidth = _fDetectorWidth;
	m_pfProjectionAngles = new float[m_iProjectionAngleCount];
	for (int i = 0; i < m_iProjectionAngleCount; i++) {
		m_pfProjectionAngles[i] = _pfProjectionAngles[i];
	}

	// Interface class, so don't set m_bInitialized to true
	return true;
}
//---------------------------------------------------------------------------------------
