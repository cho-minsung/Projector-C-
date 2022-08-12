#ifndef _INC_ASTRA_SPARSEMATRIX
#define _INC_ASTRA_SPARSEMATRIX


/** This class implements a sparse matrix. It is stored as three arrays.
	*  The values are stored row-by-row.
	*  m_pfValues     contains the values
	*  m_piColIndices contains the col indices of the values
	*  m_plRowStarts  contains the start offsets of the rows
	*/


class CSparseMatrix {
public:
	CSparseMatrix();

	// TODO: are ints large enough for width/height?
	CSparseMatrix(unsigned int _iHeight, unsigned int _iWidth,
		unsigned long _lSize);

	/** Initialize the matrix structure.
		*  It does not initialize any values.
		*
		* @param _iHeight number of rows
		* @param _iWidth number of columns
		* @param _lSize maximum number of non-zero entries
		* @return initialization successful?
		*/

	bool initialize(unsigned int _iHeight, unsigned int _iWidth,
		unsigned long _lSize);

	/** Destructor.
		*/
	~CSparseMatrix();

	/** Has the matrix structure been initialized?
		*
		* @return initialized successfully
		*/
	bool isInitialized() const { return m_bInitialized; }

	/** get a description of the class
		*
		* @return description string
		*/
	std::string description() const;

	/** get the data for a single row. Entries are stored from left to right.
		*
		* @param _iRow the row
		* @param _iSize the returned number of elements in the row
		* @param _pfValues the values of the non-zero entries in the row
		* @param _piColIndices the column indices of the non-zero entries
		*/
	void getRowData(unsigned int _iRow, unsigned int& _iSize,
		const float*& _pfValues, const unsigned int*& _piColIndices) const
	{
		assert(_iRow < m_iHeight);
		unsigned long lStart = m_plRowStarts[_iRow];
		_iSize = m_plRowStarts[_iRow + 1] - lStart;
		_pfValues = &m_pfValues[lStart];
		_piColIndices = &m_piColIndices[lStart];
	}

	/** get the number of elements in a row
		*
		* @param _iRow the row
		* @return number of stored entries in the row
		*/
	unsigned int getRowSize(unsigned int _iRow) const
	{
		assert(_iRow < m_iHeight);
		return m_plRowStarts[_iRow + 1] - m_plRowStarts[_iRow];
	}


	/** Matrix width
		*/
	unsigned int m_iHeight;

	/** Matrix height
		*/
	unsigned int m_iWidth;

	/** Maximum number of non-zero entries
		*/
	unsigned long m_lSize;

	/** Contains the numeric values of all non-zero elements
		*/
	float* m_pfValues;

	/** Contains the colon index of all non-zero elements
		*/
	unsigned int* m_piColIndices;

	/** The indices in this array point to the first element of each row in the m_pfValues array
		*/
	unsigned long* m_plRowStarts;

protected:

	/** Is the class initialized?
		*/
	bool m_bInitialized;
};


#endif
