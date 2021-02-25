#pragma once

#include "Include.h"

class CBase abstract
{
public:
	CBase();
	virtual ~CBase() = default;

public:
	_uint AddRef();
	_uint Release();

protected:
	virtual void Free() PURE;

protected:
	_uint m_iRefCount = 0;
};

