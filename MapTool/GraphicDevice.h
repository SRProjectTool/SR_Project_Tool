#pragma once

#include "Base.h"

class CGraphicDevice final : public CBase
{
	DECLARE_SINGLETON(CGraphicDevice)

private:
	CGraphicDevice();
	virtual ~CGraphicDevice() = default;

public:
	HRESULT Ready_GraphicDevice();
	LPDIRECT3DDEVICE9 GetDevice() const;
	virtual void Free() override;

private:
	LPDIRECT3D9 m_pSDK;
	LPDIRECT3DDEVICE9 m_pDevice;
};
