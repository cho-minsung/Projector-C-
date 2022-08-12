#ifndef _INC_ASTRA_FLOAT32DATA
#define _INC_ASTRA_FLOAT32DATA

#include "Globals.h"


/**
	* This is a virtual base class for floating point data classes.
	*/
class CFloat32Data {

protected:

	// Protected Member Variables
	bool m_bInitialized;	///< has the object been initialized? 
	int m_iDimensions;		///< the number of dimensions

public:

	/**
		* Default constructor.
		*/
	CFloat32Data();

	/**
		* Destructor. Free allocated memory
		*/
	virtual ~CFloat32Data();

	/**
		* Get the initialization state of the object.
		*
		* @return true iff the object has been initialized
		*/
	bool isInitialized() const;

	/**
		* Get the number of dimensions of this object.
		*
		* @return number of dimensions
		*/
	virtual int getDimensionCount() const = 0;

};

//----------------------------------------------------------------------------------------
// Inline member functions
//----------------------------------------------------------------------------------------

// Get the initialization state of the object.
inline bool CFloat32Data::isInitialized() const
{
	return m_bInitialized;
}
//----------------------------------------------------------------------------------------


#endif
