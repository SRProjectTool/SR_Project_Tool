#pragma once

#include "GameObject.h"

class CCube : public CGameObject
{
private:
	explicit CCube(LPDIRECT3DDEVICE9 pDevice);
	explicit CCube(const CCube& other);
	virtual ~CCube() = default;

public:
	virtual HRESULT Ready_GameObject_Prototype() override;
	virtual HRESULT Ready_GameObject(void * pArg = nullptr) override;
	virtual _uint Update_GameObject() override;
	virtual _uint LateUpdate_GameObject() override;
	virtual HRESULT Render_GameObject() override;

public:
	static CCube* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual CGameObject * Clone(void * pArg = nullptr) override;
	virtual void Free() override;

private:
	class CVIBuffer* m_pVIBufferCom = nullptr;
	class CTransform* m_pTransformCom = nullptr;
	class CTexture* m_pTextureCom = nullptr;
};

