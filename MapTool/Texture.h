#pragma once

#include "Component.h"

class CTexture : public CComponent
{
public:
	explicit CTexture(LPDIRECT3DDEVICE9 pDevice, ETextureType eType, const TCHAR* pFilePath, _size iCount);
	explicit CTexture(const CTexture& other);
	virtual ~CTexture() = default;

public:
	virtual HRESULT Ready_Component_Prototype() override;
	virtual HRESULT Ready_Component(void * pArg = nullptr) override;

public:
	HRESULT Set_Texture(_size iIndex);

public:
	static CTexture* Create(LPDIRECT3DDEVICE9 pDevice, ETextureType eType, const TCHAR* pFilePath, _size iCount);
	virtual CComponent * Clone(void * pArg = nullptr) override;
	virtual void Free() override;

private:
	typedef vector<IDirect3DBaseTexture9*> TEXTURES;
	TEXTURES m_Textures;

	const TCHAR* m_pFilePath = L"";
	_size m_iCount = 0;
	ETextureType m_eType = ETextureType::Default;
};

