#ifndef _INC_ASTRA_FLOAT32DATA2D
#define _INC_ASTRA_FLOAT32DATA2D

#include "Globals.h"
#include "Float32Data.h"



class CFloat32CustomMemory {
public:
	virtual ~CFloat32CustomMemory() = 0;
	float* m_fPtr;
};

/**
	* This class represents a 2-dimensional block of 32-bit floating point data.
	* It contains member functions for accessing this data and for performing
	* elementary computations on the data.
	* The data block is "owned" by the class, meaning that the class is
	* responsible for deallocation of the memory involved.
	*/
class CFloat32Data2D : public CFloat32Data {

protected:

	int m_iWidth;			///< width of the data (x)
	int m_iHeight;			///< height of the data (y)
	int m_iSize;			///< total size of the data

	/** Pointer to the data block, represented as a 1-dimensional array.
		* Note that the data memory is "owned" by this class, meaning that the
		* class is responsible for deallocation of the memory involved.
		* To access element (ix, iy) internally, use
		* m_pData[iy * m_iWidth + ix]
		*/
	float* m_pfData;

	/** Array of float pointers, each pointing to a single horizontal
		* line in the m_pfData memory block.
		* To access element (ix, iy) internally, use m_ppfData2D[iy][ix]
		*/
	float** m_ppfData2D;

	float m_fGlobalMin;	///< minimum value of the data
	float m_fGlobalMax;	///< maximum value of the data
	float m_fGlobalMean;  ///< mean value of the data

	/** Allocate memory for m_pfData and m_ppfData2D arrays.
		*
		* The allocated block consists of m_iSize floats. The block is
		* not cleared after allocation and its contents is undefined.
		* This function may NOT be called if memory has already been allocated.
		*/
	void _allocateData();

	/** Free memory for m_pfData and m_ppfData2D arrays.
		*
		* This function may ONLY be called if the memory for both blocks has been
		* allocated before.
		*/
	void _freeData();

	/** Clear all member variables, setting all numeric variables to 0 and all pointers to NULL.
		*/
	void _clear();

	/** Un-initialize the object, bringing it back in the uninitialized state.
		*/
	void _unInit();

	/** Find the minimum and maximum data value and store them in
		* m_fGlobalMin and m_fGlobalMax
		*/
	void _computeGlobalMinMax();

	/** Initialization. Initializes an instance of the CFloat32Data2D class, without filling the data block.
		* Can only be called by derived classes.
		*
		* Initializes an instance of the CFloat32Data2D class. Memory is allocated for the
		* data block. The allocated memory is not cleared and its contents after
		* construction is undefined. Initialization may be followed by a call to
		* copyData() to fill the memory block. If the object has been initialized before, the
		* object is reinitialized and memory is freed and reallocated if necessary.
		* This function does not set m_bInitialized to true if everything is ok.
		*
		* @param _iWidth width of the 2D data (x-axis), must be > 0
		* @param _iHeight height of the 2D data (y-axis), must be > 0
		* @return initialization of the base class successfull
		*/
	bool _initialize(int _iWidth, int _iHeight);

	/** Initialization. Initializes an instance of the CFloat32Data2D class with initialization of the data block.
		* Can only be called by derived classes.
		*
		* Initializes an instance of the CFloat32Data2D class. Memory
		* is allocated for the data block and the contents of the memory pointed to by
		* _pfData is copied into the allocated memory. If the object has been initialized before, the
		* object is reinitialized and memory is freed and reallocated if necessary.
		* This function does not set m_bInitialized to true if everything is ok.
		*
		* @param _iWidth width of the 2D data (x-axis), must be > 0
		* @param _iHeight height of the 2D data (y-axis), must be > 0
		* @param _pfData pointer to a one-dimensional float data block
		*/
	bool _initialize(int _iWidth, int _iHeight, const float* _pfData);

	/** Initialization. Initializes an instance of the CFloat32Data2D class with initialization of the data
		* block with a scalar value. Can only be called by derived classes.
		*
		* Initializes an instance of the CFloat32Data2D class. Memory
		* is allocated for the data block and the contents of the memory pointed to by
		* _pfData is copied into the allocated memory. If the object has been initialized before, the
		* object is reinitialized and memory is freed and reallocated if necessary.
		* This function does not set m_bInitialized to true if everything is ok.
		*
		* @param _iWidth width of the 2D data (x-axis), must be > 0
		* @param _iHeight height of the 2D data (y-axis), must be > 0
		* @param _fScalar scalar value to put at each index
		*/
	bool _initialize(int _iWidth, int _iHeight, float _fScalar);

	/** Initialization. Initializes an instance of the CFloat32Data2D class with pre-allocated memory.
		* Can only be called by derived classes.
		*
		* Initializes an instance of the CFloat32Data2D class. Memory
		* is pre-allocated and passed via the abstract CFloat32CustomMemory handle
		* class. The handle will be deleted when the memory can be freed.
		* You should override the destructor to provide custom behaviour on free.
		* If the object has been initialized before, the
		* object is reinitialized and memory is freed and reallocated if necessary.
		* This function does not set m_bInitialized to true if everything is ok.
		*
		* @param _iWidth width of the 2D data (x-axis), must be > 0
		* @param _iHeight height of the 2D data (y-axis), must be > 0
		* @param _pfData pointer to a one-dimensional float data block
		*/
	bool _initialize(int _iWidth, int _iHeight, CFloat32CustomMemory* _pCustomMemory);

	/** Constructor. Create an instance of the CFloat32Data2D class without initializing the data block.
		* Can only be called by derived classes.
		*
		* Creates an instance of the CFloat32Data2D class. Memory is allocated for the
		* data block. The allocated memory is not cleared and its contents after
		* construction is undefined. Construction may be followed by a call to
		* copyData() to fill the memory block.
		*
		* @param _iWidth width of the 2D data (x-axis), must be > 0
		* @param _iHeight height of the 2D data (y-axis), must be > 0
		*/
	CFloat32Data2D(int _iWidth, int _iHeight);

	/** Constructor. Create an instance of the CFloat32Data2D class with initialization of the data block.
		* Can only be called by derived classes.
		*
		* Creates an instance of the CFloat32Data2D class. Memory
		* is allocated for the data block and the contents of the memory pointed to by
		* _pfData is copied into the allocated memory.
		*
		* @param _iWidth width of the 2D data (x-axis), must be > 0
		* @param _iHeight height of the 2D data (y-axis), must be > 0
		* @param _pfData pointer to a one-dimensional float data block
		*/
	CFloat32Data2D(int _iWidth, int _iHeight, const float* _pfData);

	/** Constructor. Create an instance of the CFloat32Data2D class with initialization of the data block
		* with a scalar value. Can only be called by derived classes.
		*
		* Creates an instance of the CFloat32Data2D class. Memory
		* is allocated for the data block and the contents of the memory pointed to by
		* _pfData is copied into the allocated memory.
		*
		* @param _iWidth width of the 2D data (x-axis), must be > 0
		* @param _iHeight height of the 2D data (y-axis), must be > 0
		* @param _fScalar scalar value to put at each index
		*/
	CFloat32Data2D(int _iWidth, int _iHeight, float _fScalar);

	/** Constructor. Create an instance of the CFloat32Data2D class with pre-allocated memory.

		* Can only be called by derived classes.
		*
		* Creates an instance of the CFloat32Data2D class. Memory
		* is pre-allocated and passed via the abstract CFloat32CustomMemory handle
		* class. The handle will be deleted when the memory can be freed.
		* You should override the destructor to provide custom behaviour on free.
		*
		* @param _iWidth width of the 2D data (x-axis), must be > 0
		* @param _iHeight height of the 2D data (y-axis), must be > 0
		* @param _pfData pointer to a one-dimensional float data block
		*/
	CFloat32Data2D(int _iWidth, int _iHeight, CFloat32CustomMemory* _pCustomMemory);

	/** Copy constructor.
		*/
	CFloat32Data2D(const CFloat32Data2D&);

public:

	/** Typedef with available datatypes: BASE, PROJECTION, VOLUME.
	*/
	typedef enum {
		BASE,
		PROJECTION,
		VOLUME
	} EDataType;

	/** Default constructor. Sets all numeric member variables to 0 and all pointer member variables to NULL.
		*
		* If an object is constructed using this default constructor, it must always be followed by a call
		* to one of the initialize() methods before the object can be used. Any use before calling init() is not allowed,
		* except calling the member function isInitialized().
		*
		*/
	CFloat32Data2D();

	/** Destructor. Free allocated memory
		*/
	virtual ~CFloat32Data2D();

	/** Copy the data block pointed to by _pfData to the data block pointed to by m_pfData.
		* The pointer _pfData must point to a block of m_iSize floats.
		*
		* @param _pfData source data block
		*/
	void copyData(const float* _pfData);

	/** scale the grey value of the data from 0-255.
		*
		*/
	void scale();

	/** Set each element of the data to a specified scalar value.
		*
		* @param _fScalar scalar value
		*/
	void setData(float _fScalar);

	/** Set all data to zero
		*/
	void clearData();

	/** Get a pointer to the data block, represented as a 1-dimensional
		* array of float values. The data memory is still "owned" by the
		* CFloat32Data2D instance; this memory may NEVER be freed by the
		* caller of this function. If changes are made to this data, the
		* function updateStatistics() should be called after completion of
		* all changes.
		*
		* @return pointer to the 1-dimensional 32-bit floating point data block
		*/
	float* getData();

	/** Get a const pointer to the data block, represented as a 1-dimensional
		* array of float values. The data memory is still "owned" by the
		* CFloat32Data2D instance; this memory may NEVER be freed by the
		* caller of this function. If changes are made to this data, the
		* function updateStatistics() should be called after completion of
		* all changes.
		*
		* @return pointer to the 1-dimensional 32-bit floating point data block
		*/
	const float* getDataConst() const;

	/** Get a float** to the data block, represented as a 2-dimensional array of float values.
		*
		* After the call p = getData2D(), use p[iy][ix] to access element (ix, iy).
		* The data memory and pointer array are still "owned" by the CFloat32Data2D
		* instance; this memory may NEVER be freed by the caller of this function.
		* If changes are made to this data, the function updateStatistics()
		* should be called after completion of all changes.
		*
		* @return pointer to the 2-dimensional 32-bit floating point data block
		*/
	float** getData2D();

	/** Get a const float** to the data block, represented as a 2-dimensional array of float values.
		*
		* After the call p = getData2D(), use p[iy][ix] to access element (ix, iy).
		* The data memory and pointer array are still "owned" by the CFloat32Data2D
		* instance; this memory may NEVER be freed by the caller of this function.
		* If changes are made to this data, the function updateStatistics()
		* should be called after completion of all changes.
		*
		* @return pointer to the 2-dimensional 32-bit floating point data block
		*/
	const float** getData2DConst() const;

	/** Update data statistics, such as minimum and maximum value, after the data has been modified.
		*/
	virtual void updateStatistics();

	/** Get the minimum value in the data block.
		* If the data has been changed after construction, the function
		* updateStatistics() must be called at least once before
		* a query can be made on this value.
		*
		* @return minimum value in the data block
		*/
	virtual float getGlobalMin() const;

	/** Get the maximum value in the data block
		* If the data has been changed after construction, the function
		* updateStatistics() must be called at least once before
		* a query can be made on this value.
		*
		* @return maximum value in the data block
		*/
	virtual float getGlobalMax() const;

	/** Get the mean value in the data block
		* If the data has been changed after construction, the function
		* updateStatistics() must be called at least once before
		* a query can be made on this value.
		*
		* @return maximum value in the data block
		*/
	virtual float getGlobalMean() const;


	/** Get the width of the data block.
		*
		* @return width of the data block
		*/
	int getWidth() const;

	/** Get the height of the data block.
		*
		* @return height of the data block
		*/
	int getHeight() const;

	/** Get the total size (width*height) of the data block.
		*
		* @return size of the data block
		*/
	int getSize() const;

	/** which type is this class?
		*
		* @return DataType: ASTRA_DATATYPE_FLOAT32_PROJECTION or
		*					 ASTRA_DATATYPE_FLOAT32_VOLUME
		*/
	virtual EDataType getType() const;

	/** get a description of the class
		*
		* @return description string
		*/
	virtual std::string description() const;

	/** Get the number of dimensions of this object.
		*
		* @return number of dimensions
		*/
	int getDimensionCount() const;

	/**
		* Clamp data to minimum value
		*
		* @param _fMin minimum value
		* @return l-value
		*/
	CFloat32Data2D& clampMin(float& _fMin);

	/**
		* Clamp data to maximum value
		*
		* @param _fMax maximum value
		* @return l-value
		*/
	CFloat32Data2D& clampMax(float& _fMax);

	/**
		* Overloaded Operator: data += data (pointwise)
		*
		* @param _data r-value
		* @return l-value
		*/
	CFloat32Data2D& operator+=(const CFloat32Data2D& _data);

	/**
		* Overloaded Operator: data -= data (pointwise)
		*
		* @param _data r-value
		* @return l-value
		*/
	CFloat32Data2D& operator-=(const CFloat32Data2D& _data);

	/**
		* Overloaded Operator: data *= data (pointwise)
		*
		* @param _data r-value
		* @return l-value
		*/
	CFloat32Data2D& operator*=(const CFloat32Data2D& _data);

	/**
		* Overloaded Operator: data *= scalar (pointwise)
		*
		* @param _fScalar r-value
		* @return l-value
		*/
	CFloat32Data2D& operator*=(const float& _fScalar);

	/**
		* Overloaded Operator: data /= scalar (pointwise)
		*
		* @param _fScalar r-value
		* @return l-value
		*/
	CFloat32Data2D& operator/=(const float& _fScalar);

	/**
		* Overloaded Operator: data += scalar (pointwise)
		*
		* @param _fScalar r-value
		* @return l-value
		*/
	CFloat32Data2D& operator+=(const float& _fScalar);

	/**
		* Overloaded Operator: data -= scalar (pointwise)
		*
		* @param _fScalar r-value
		* @return l-value
		*/
	CFloat32Data2D& operator-=(const float& _fScalar);

	CFloat32Data2D& operator=(const CFloat32Data2D& _dataIn);

	float& getData(int _index);


private:
	CFloat32CustomMemory* m_pCustomMemory;
};


//----------------------------------------------------------------------------------------
// Inline member functions
//----------------------------------------------------------------------------------------

// Get the number of dimensions of this object.
inline int CFloat32Data2D::getDimensionCount() const
{
	return 2;
}

//----------------------------------------------------------------------------------------
// Get the type of this object.
inline CFloat32Data2D::EDataType CFloat32Data2D::getType() const
{
	return BASE;
}

//----------------------------------------------------------------------------------------
// Get the width of the data block.
inline int CFloat32Data2D::getWidth() const
{
	ASTRA_ASSERT(m_bInitialized);
	return m_iWidth;
}

//----------------------------------------------------------------------------------------
// Get the height of the data block.
inline int CFloat32Data2D::getHeight() const
{
	ASTRA_ASSERT(m_bInitialized);
	return m_iHeight;
}

//----------------------------------------------------------------------------------------
// Get the total size (width*height*depth) of the data block.
inline int CFloat32Data2D::getSize() const
{
	ASTRA_ASSERT(m_bInitialized);
	return m_iSize;
}

//----------------------------------------------------------------------------------------
// Get a pointer to the data block, represented as a 1-dimensional array of float values.
inline float* CFloat32Data2D::getData()
{
	//ASTRA_ASSERT(m_bInitialized);
	return m_pfData;
}

//----------------------------------------------------------------------------------------
// Get a pointer to the data block, represented as a 1-dimensional array of float values.
inline float& CFloat32Data2D::getData(int _index)
{
	//ASTRA_ASSERT(m_bInitialized);
	return m_pfData[_index];
}

//----------------------------------------------------------------------------------------
// Get a const pointer to the data block, represented as a 1-dimensional array of float values.
inline const float* CFloat32Data2D::getDataConst() const
{
	ASTRA_ASSERT(m_bInitialized);
	return (const float*)m_pfData;
}

//----------------------------------------------------------------------------------------
// Get a float** to the data block, represented as a 2-dimensional array of float values.
inline float** CFloat32Data2D::getData2D()
{
	ASTRA_ASSERT(m_bInitialized);
	return m_ppfData2D;
}

//----------------------------------------------------------------------------------------
// Get a const float** to the data block, represented as a 2-dimensional array of float values.
inline const float** CFloat32Data2D::getData2DConst() const
{
	ASTRA_ASSERT(m_bInitialized);
	return (const float**)m_ppfData2D;
}

//----------------------------------------------------------------------------------------
// Get the minimum value in the data block.
inline float CFloat32Data2D::getGlobalMin() const
{
	ASTRA_ASSERT(m_bInitialized);
	return m_fGlobalMin;
}

//----------------------------------------------------------------------------------------
// Get the maximum value in the data block
inline float CFloat32Data2D::getGlobalMax() const
{
	ASTRA_ASSERT(m_bInitialized);
	return m_fGlobalMax;
}

//----------------------------------------------------------------------------------------
// Get the mean value in the data block
inline float CFloat32Data2D::getGlobalMean() const
{
	ASTRA_ASSERT(m_bInitialized);
	return m_fGlobalMean;
}



#endif // _INC_ASTRA_FLOAT32DATA2D
