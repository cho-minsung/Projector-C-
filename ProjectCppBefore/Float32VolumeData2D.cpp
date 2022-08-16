#include "Float32VolumeData2D.h"
#include <iostream>

//----------------------------------------------------------------------------------------
// Default constructor
CFloat32VolumeData2D::CFloat32VolumeData2D() :
	CFloat32Data2D()
{
	m_pGeometry = NULL;
	m_bInitialized = false;
}

//----------------------------------------------------------------------------------------
// Create an instance of the CFloat32VolumeData2D class, allocating (but not initializing) the data block.
CFloat32VolumeData2D::CFloat32VolumeData2D(CVolumeGeometry2D* _pGeometry)
{
	m_bInitialized = false;
	m_bInitialized = initialize(_pGeometry);
}

//----------------------------------------------------------------------------------------
// Create an instance of the CFloat32VolumeData2D class with initialization of the data.
CFloat32VolumeData2D::CFloat32VolumeData2D(CVolumeGeometry2D* _pGeometry, float* _pfData)
{
	std::cout << "initialized with pointer" << std::endl;
	m_bInitialized = false;
	m_bInitialized = initialize(_pGeometry, _pfData);
}

//----------------------------------------------------------------------------------------
// Create an instance of the CFloat32VolumeData2D class with initialization of the data.
CFloat32VolumeData2D::CFloat32VolumeData2D(CVolumeGeometry2D* _pGeometry, float _fScalar)
{
	std::cout << "initialized with scalar" << std::endl;
	m_bInitialized = false;
	m_bInitialized = initialize(_pGeometry, _fScalar);
}

//----------------------------------------------------------------------------------------
// Copy constructor
CFloat32VolumeData2D::CFloat32VolumeData2D(const CFloat32VolumeData2D& _other) : CFloat32Data2D(_other)
{
	m_pGeometry = _other.m_pGeometry->clone();
	m_bInitialized = true;
}

//----------------------------------------------------------------------------------------
// Create an instance of the CFloat32VolumeData2D class with pre-allocated data
CFloat32VolumeData2D::CFloat32VolumeData2D(CVolumeGeometry2D* _pGeometry, CFloat32CustomMemory* _pCustomMemory)
{
	m_bInitialized = false;
	m_bInitialized = initialize(_pGeometry, _pCustomMemory);
}


// Assignment operator

CFloat32VolumeData2D& CFloat32VolumeData2D::operator=(const CFloat32VolumeData2D& _other)
{
	ASTRA_ASSERT(_other.m_bInitialized);

	if (m_bInitialized)
		delete m_pGeometry;
	*((CFloat32Data2D*)this) = _other;
	m_pGeometry = _other.m_pGeometry->clone();
	m_bInitialized = true;

	return *this;
}

//----------------------------------------------------------------------------------------
// Destructor
CFloat32VolumeData2D::~CFloat32VolumeData2D()
{
	if (m_bInitialized)
		delete m_pGeometry;
	m_pGeometry = 0;
}

//----------------------------------------------------------------------------------------
// Initialization
bool CFloat32VolumeData2D::initialize(CVolumeGeometry2D* _pGeometry)
{
	m_pGeometry = _pGeometry->clone();
	m_bInitialized = _initialize(m_pGeometry->getGridColCount(), m_pGeometry->getGridRowCount());
	return m_bInitialized;
}

//----------------------------------------------------------------------------------------
// Initialization
bool CFloat32VolumeData2D::initialize(CVolumeGeometry2D* _pGeometry, const float* _pfData)
{
	m_pGeometry = _pGeometry->clone();
	m_bInitialized = _initialize(m_pGeometry->getGridColCount(), m_pGeometry->getGridRowCount(), _pfData);
	return m_bInitialized;
}

//----------------------------------------------------------------------------------------
// Initialization
bool CFloat32VolumeData2D::initialize(CVolumeGeometry2D* _pGeometry, float _fScalar)
{
	m_pGeometry = _pGeometry->clone();
	m_bInitialized = _initialize(m_pGeometry->getGridColCount(), m_pGeometry->getGridRowCount(), _fScalar);
	return m_bInitialized;
}

//----------------------------------------------------------------------------------------
// Initialization
bool CFloat32VolumeData2D::initialize(CVolumeGeometry2D* _pGeometry, CFloat32CustomMemory* _pCustomMemory)
{
	m_pGeometry = _pGeometry->clone();
	m_bInitialized = _initialize(m_pGeometry->getGridColCount(), m_pGeometry->getGridRowCount(), _pCustomMemory);
	return m_bInitialized;
}


//----------------------------------------------------------------------------------------
void CFloat32VolumeData2D::changeGeometry(CVolumeGeometry2D* _pGeometry)
{
	if (!m_bInitialized) return;

	delete m_pGeometry;
	m_pGeometry = _pGeometry->clone();
}
