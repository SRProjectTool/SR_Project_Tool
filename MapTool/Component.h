#pragma once

#include "Base.h"

class CComponent abstract : public CBase
{
protected:
	explicit CComponent(LPDIRECT3DDEVICE9 pDevice);
	explicit CComponent(const CComponent& other);
	virtual ~CComponent() = default;

public:
	virtual HRESULT Ready_Component_Prototype() = 0;
	virtual HRESULT Ready_Component(void* pArg = nullptr) = 0;

public:
	virtual CComponent* Clone(void* pArg = nullptr) = 0;
	virtual void Free() override;

protected:
	LPDIRECT3DDEVICE9	m_pDevice = nullptr;
	_bool				m_IsClone = false;
};