#pragma once

#include "Base.h"

class CRenderer : public CBase
{
private:
	explicit CRenderer(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CRenderer() = default;

public:
	HRESULT Add_GameObjectToRenderList(ERenderID eRenderID, class CGameObject* pGameObject);
	HRESULT Render();

private:
	HRESULT Render_Priority();
	HRESULT Render_NonAlpha();
	HRESULT Render_Alpha();

public:
	static CRenderer* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual void Free() override;

private:
	LPDIRECT3DDEVICE9 m_pDevice = nullptr;

	typedef std::list<class CGameObject*> GAMEOBJECTS;
	GAMEOBJECTS m_RenderList[(_uint)ERenderID::Max];
};

