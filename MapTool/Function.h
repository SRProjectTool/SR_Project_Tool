#pragma once

template <typename T>
_uint Safe_AddRef(T& ptr)
{
	_uint iRefCount = 0;

	if (ptr)
	{
		iRefCount = ptr->AddRef();
	}

	return iRefCount;
}

template <typename T>
_uint Safe_Release(T& ptr)
{
	_uint iRefCount = 0;

	if (ptr)
	{
		iRefCount = ptr->Release();
		ptr = nullptr;
	}

	return iRefCount;
}

template <typename T>
void Safe_Delete_Array(T& ptr)
{
	if (ptr)
	{
		delete[] ptr;
		ptr = nullptr;
	}
}