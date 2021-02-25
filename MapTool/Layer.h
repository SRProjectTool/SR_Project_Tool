#pragma once

#include "Base.h"

class CLayer : public CBase
{
public:
	CLayer();
	virtual ~CLayer() = default;

public:
	HRESULT Add_GameObject(class CGameObject* pGameObject);
	_uint Update_GameObject();
	_uint LateUpdate_GameObject();

public:
	static CLayer* Create();
	virtual void Free() override;

private:
	typedef std::list<class CGameObject*>	GAMEOBJECTS;
	GAMEOBJECTS	m_GameObjects;	// 오브젝트들의 복제본들을 보관.
};

