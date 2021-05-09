#pragma once

#ifndef __LOCK_NATIVE_H__
#define __LOCK_NATIVE_H__

#include "Python.h"

class AppletLock
{
public:
	AppletLock() {}
	~AppletLock() {}


	void PyLock() {
		PyEval_RestoreThread(this->m_state);
	}

	void PyUnlock() {
		PyEval_SaveThread();
	}

protected:

	PyThreadState*	m_state;
};


#endif // !__LOCK_NATIVE_H__

