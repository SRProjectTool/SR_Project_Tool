#pragma once

#include "VIBuffer.h"

class CVIBuffer_CubeTexture : public CVIBuffer
{
protected:
	explicit CVIBuffer_CubeTexture(LPDIRECT3DDEVICE9 pDevice);
	explicit CVIBuffer_CubeTexture(const CVIBuffer_CubeTexture& other);
	virtual ~CVIBuffer_CubeTexture() = default;

public:
	virtual HRESULT Ready_Component_Prototype() override;
	virtual HRESULT Ready_Component(void * pArg = nullptr) override;
	virtual HRESULT Render_Buffer() override;

public:
	static CVIBuffer_CubeTexture* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual CComponent * Clone(void * pArg = nullptr) override;
	virtual void Free() override;
};

