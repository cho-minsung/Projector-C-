#ifndef _INC_ASTRA_ALGORITHM
#define _INC_ASTRA_ALGORITHM

#include "Globals.h"


/**
	* This class contains the interface for an algorithm implementation.
	*/
class  CAlgorithm {

public:

	/** Default constructor, containing no code.
		*/
	CAlgorithm();

	/** Destructor.
		*/
	virtual ~CAlgorithm();

	/** Perform a number of iterations.
		*
		* @param _iNrIterations amount of iterations to perform.
		*/
	virtual void run(int _iNrIterations = 0) = 0;

	/** Has this class been initialized?
		*
		* @return initialized
		*/
	bool isInitialized() const;

	/** get a description of the class
		*
		* @return description string
		*/
	virtual std::string description() const;

	/** Set the GPU Index to run on.
		* TODO: Move this from CAlgorithm to a Context-like class
		*/
	virtual void setGPUIndex(int /*_iGPUIndex*/) { };

protected:

	//< Has this class been initialized?
	bool m_bIsInitialized;

private:
	/**
		* Private copy constructor to prevent CAlgorithms from being copied.
		*/
	CAlgorithm(const CAlgorithm&);

	/**
		* Private assignment operator to prevent CAlgorithms from being copied.
		*/
	CAlgorithm& operator=(const CAlgorithm&);

};

// inline functions
inline std::string CAlgorithm::description() const { return "Algorithm"; };
inline bool CAlgorithm::isInitialized() const { return m_bIsInitialized; }


#endif
