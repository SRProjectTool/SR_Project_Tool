#include "stdafx.h"
#include "Renderer.h"
#include "GameObject.h"

CRenderer::CRenderer(LPDIRECT3DDEVICE9 pDevice)
	: m_pDevice(pDevice)
{
	Safe_AddRef(m_pDevice);
}

HRESULT CRenderer::Add_GameObjectToRenderList(ERenderID eRenderID, CGameObject * pGameObject)
{
	if (nullptr == pGameObject)
		return E_FAIL;

	if (ERenderID::Max <= eRenderID)
		return E_FAIL;

	m_RenderList[(_uint)eRenderID].push_back(pGameObject);
	Safe_AddRef(pGameObject);

	return S_OK;
}

HRESULT CRenderer::Render()
{
	if (nullptr == m_pDevice)
		return E_FAIL;

	if (FAILED(m_pDevice->Clear(
		0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,
		D3DCOLOR_ARGB(255, 0, 0, 255), 1.f, 0)))
		return E_FAIL;

	if (FAILED(m_pDevice->BeginScene()))
		return E_FAIL;

	if (FAILED(Render_Priority()))
		return E_FAIL;

	if (FAILED(Render_NonAlpha()))
		return E_FAIL;

	if (FAILED(Render_Alpha()))
		return E_FAIL;

	if (FAILED(m_pDevice->EndScene()))
		return E_FAIL;

	if (FAILED(m_pDevice->Present(nullptr, nullptr, g_hWND, nullptr)))
		return E_FAIL;

	return S_OK;
}

HRESULT CRenderer::Render_Priority()
{
	for (auto& pGameObject : m_RenderList[(_uint)ERenderID::Priority])
	{
		if (FAILED(pGameObject->Render_GameObject()))
			return E_FAIL;

		Safe_Release(pGameObject);
	}

	m_RenderList[(_uint)ERenderID::Priority].clear();

	return S_OK;
}

HRESULT CRenderer::Render_NonAlpha()
{
	for (auto& pGameObject : m_RenderList[(_uint)ERenderID::NonAlpha])
	{
		if (FAILED(pGameObject->Render_GameObject()))
			return E_FAIL;

		Safe_Release(pGameObject);
	}

	m_RenderList[(_uint)ERenderID::NonAlpha].clear();

	return S_OK;
}

HRESULT CRenderer::Render_Alpha()
{
	for (auto& pGameObject : m_RenderList[(_uint)ERenderID::Alpha])
	{
		if (FAILED(pGameObject->Render_GameObject()))
			return E_FAIL;

		Safe_Release(pGameObject);
	}

	m_RenderList[(_uint)ERenderID::Alpha].clear();

	return S_OK;
}

CRenderer * CRenderer::Create(LPDIRECT3DDEVICE9 pDevice)
{
	return new CRenderer(pDevice);
}

void CRenderer::Free()
{
	Safe_Release(m_pDevice);
}
