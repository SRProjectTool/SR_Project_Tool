#include "stdafx.h"
#include "Layer.h"
#include "GameObject.h"

CLayer::CLayer()
{
}

HRESULT CLayer::Add_GameObject(CGameObject* pGameObject)
{
	auto iter_find = find(m_GameObjects.begin(), m_GameObjects.end(), pGameObject);
	if (m_GameObjects.end() == iter_find)
	{
		m_GameObjects.push_back(pGameObject);
	}

	return S_OK;
}

_uint CLayer::Update_GameObject()
{
	return _uint();
}

_uint CLayer::LateUpdate_GameObject()
{
	_uint iEvent = 0;

	for (auto& pGameObjeect : m_GameObjects)
	{
		if (iEvent = pGameObjeect->LateUpdate_GameObject())
		{
			return iEvent;
		}
	}

	return _uint();
}

CLayer * CLayer::Create()
{
	return new CLayer;
}

void CLayer::Free()
{
	for (auto& pGameObject : m_GameObjects)
	{
		Safe_Release(pGameObject);
	}

	m_GameObjects.clear();
}