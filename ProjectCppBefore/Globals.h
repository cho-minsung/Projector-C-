#ifndef _INC_ASTRA_GLOBALS
#define _INC_ASTRA_GLOBALS

 //----------------------------------------------------------------------------------------

#ifdef _MSC_VER

// disable warning: 'fopen' was declared deprecated
#pragma warning (disable : 4996)
// disable warning: C++ exception handler used, but unwind semantics are not enables
#pragma warning (disable : 4530)
// disable warning: no suitable definition provided for explicit template instantiation request
#pragma warning (disable : 4661)

#endif

//----------------------------------------------------------------------------------------
// standard includes
#include <cassert>
#include <iostream>
#include <fstream>
#include <math.h>

//----------------------------------------------------------------------------------------
// macro's

#define ASTRA_TOOLBOXVERSION_MAJOR 2
#define ASTRA_TOOLBOXVERSION_MINOR 1
#define ASTRA_TOOLBOXVERSION ((ASTRA_TOOLBOXVERSION_MAJOR)*100 + (ASTRA_TOOLBOXVERSION_MINOR))
#define ASTRA_TOOLBOXVERSION_STRING "2.1.1"


#define ASTRA_ASSERT(a) assert(a)

#define ASTRA_CONFIG_CHECK(value, type, msg) if (!(value)) { std::cout << "Configuration Error in " << type << ": " << msg << std::endl; return false; }

#define ASTRA_CONFIG_WARNING(type, msg) { std::cout << "Warning in " << type << ": " << msg << sdt::endl; }


#define ASTRA_DELETE(a) if (a) { delete a; a = NULL; }
#define ASTRA_DELETE_ARRAY(a) if (a) { delete[] a; a = NULL; }

#ifdef _MSC_VER

#else

#define _AstraExport

#endif


//----------------------------------------------------------------------------------------
// typedefs
typedef double float64;
typedef unsigned short int uint16;
typedef signed short int sint16;
typedef unsigned char uchar8;
typedef signed char schar8;

typedef int int32;
typedef short int int16;


//----------------------------------------------------------------------------------------
// variables
const float PI = 3.14159265358979323846264338328f;
const float PI32 = 3.14159265358979323846264338328f;
const float PIdiv2 = PI / 2;
const float PIdiv4 = PI / 4;
const float eps = 1e-6f;

//----------------------------------------------------------------------------------------
// structs
/**
	* Struct for storing pixel weigths
	**/
struct SPixelWeight
{
	int m_iIndex;
	float m_fWeight;
};

/**
	* Struct combining some properties of a detector in 1D detector row
	**/
struct SDetector2D
{
	int m_iIndex;
	int m_iAngleIndex;
	int m_iDetectorIndex;
};

/**
	* Struct combining some properties of a detector in 2D detector array
	**/
struct SDetector3D
{
	int m_iIndex;
	int m_iAngleIndex;
	int m_iDetectorIndex;
	int m_iSliceIndex;
};


//----------------------------------------------------------------------------------------
// portability between MSVC and Linux/gcc

#ifndef _MSC_VER
#define EXPIMP_TEMPLATE

#if !defined(FORCEINLINE) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1))
#define FORCEINLINE inline __attribute__((__always_inline__))
#else
#define FORCEINLINE inline
#endif

#else

#define FORCEINLINE __forceinline

#endif

//----------------------------------------------------------------------------------------
// use pthreads on Linux and OSX
#if defined(__linux__) || defined(__MACH__)
#define USE_PTHREADS
#endif


#endif
