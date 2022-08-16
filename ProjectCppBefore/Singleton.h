#ifndef _INC_ASTRA_SINGLETON
#define _INC_ASTRA_SINGLETON

#include <cassert>

#ifndef _MSC_VER
#include <stdint.h>
#endif

/**
	* This singleton interface class ensures that any of its children can be instatiated only once. This is used by the ObjectFactories.
	**/
template<typename T>
class Singleton {

public:

	// constructor
	Singleton() { }

	// destructor
	virtual ~Singleton() {
		assert(m_singleton);
		m_singleton = 0;
	}

	static void construct();

	// get singleton
	static T& getSingleton() {
		if (!m_singleton)
			construct();
		return *m_singleton;
	}
	static T* getSingletonPtr() {
		if (!m_singleton)
			construct();
		return m_singleton;
	}

private:

	// the singleton
	static T* m_singleton;

};

// We specifically avoid defining construct() in the header.
// That way, the call to new is always executed by code inside libastra.
// This avoids the situation where a singleton gets created by a copy
// of the constructor linked into an object file outside of libastra, such
// as a .mex file, which would then also cause the vtable to be outside of
// libastra. This situation would cause issues when .mex files are unloaded.

#define DEFINE_SINGLETON(T) \
template<> T* Singleton<T >::m_singleton = 0; \
template<> void Singleton<T >::construct() { assert(!m_singleton); m_singleton = new T(); }


// This is a hack to support statements like
// DEFINE_SINGLETON2(CTemplatedClass<C1, C2>);
#define DEFINE_SINGLETON2(A,B) \
template<> A,B* Singleton<A,B >::m_singleton = 0; \
template<> void Singleton<A,B >::construct() { assert(!m_singleton); m_singleton = new A,B(); }


#endif
