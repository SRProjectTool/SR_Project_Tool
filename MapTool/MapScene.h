#pragma once

#include "Scene.h"

class CMapScene : public CScene
{
private:
	explicit CMapScene(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CMapScene() = default;

public:
	virtual HRESULT Ready_Scene() override;
	virtual _uint Update_Scene(_float fDeltaTime) override;
	virtual _uint LateUpdate_Scene(_float fDeltaTime) override;

private:
	HRESULT Add_Cube_Layer(const wstring& LayerTag);

public:
	static CMapScene* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual void Free() override;
};

