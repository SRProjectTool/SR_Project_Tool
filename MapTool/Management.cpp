#include "stdafx.h"
#include "Management.h"
#include "GameObjectMgr.h"
#include "ComponentMgr.h"
#include "SceneMgr.h"
#include "GraphicDevice.h"

IMPLEMENT_SINGLETON(CManagement)

CManagement::CManagement()
	: m_pDevice_Manager(CGraphicDevice::GetInstance())
	, m_pScene_Manager(CScene_Manager::GetInstance())
	, m_pGameObject_Manager(CGameObject_Manager::GetInstance())
	, m_pComponent_Manager(CComponent_Manager::GetInstance())
{
}

HRESULT CManagement::Ready_Engine(_uint iSceneCount)
{
	if (nullptr == m_pDevice_Manager ||
		nullptr == m_pScene_Manager ||
		nullptr == m_pGameObject_Manager ||
		nullptr == m_pComponent_Manager)
		return E_FAIL;

	if (FAILED(m_pDevice_Manager->Ready_GraphicDevice()))
	{
		MSG_BOX(L"Failed To Ready_Device");
		return E_FAIL;
	}

	m_pRenderer = CRenderer::Create(m_pDevice_Manager->GetDevice());
	if (nullptr == m_pRenderer)
	{
		MSG_BOX(L"Failed To Renderer");
		return E_FAIL;
	}

	if (FAILED(m_pGameObject_Manager->Ready_GameObject_Manager(iSceneCount)))
	{
		MSG_BOX(L"Failed To Ready_GameObject_Manager");
		return E_FAIL;
	}

	if (FAILED(m_pComponent_Manager->Ready_Component_Manager(iSceneCount)))
	{
		MSG_BOX(L"Failed To Ready_Component_Manager");
		return E_FAIL;
	}

	return S_OK;
}

_uint CManagement::Update_Engine()
{
	if (nullptr == m_pScene_Manager ||
		nullptr == m_pGameObject_Manager)
		return 0;

	_uint iEvent = 0;

	if (iEvent = m_pScene_Manager->Update_Scene(0.f))
		return iEvent;

	if (iEvent = m_pGameObject_Manager->Update_GameObject(0.f))
		return iEvent;

	if (iEvent = m_pScene_Manager->LateUpdate_Scene(0.f))
		return iEvent;

	if (iEvent = m_pGameObject_Manager->LateUpdate_GameObject(0.f))
		return iEvent;

	return _uint();
}

HRESULT CManagement::Render_Engine()
{
	if (nullptr == m_pRenderer)
		return E_FAIL;

	return m_pRenderer->Render();
}

HRESULT CManagement::Clear_ForScene(_uint iSceneIndex)
{
	if (nullptr == m_pGameObject_Manager ||
		nullptr == m_pComponent_Manager)
		return E_FAIL;

	if (FAILED(m_pGameObject_Manager->Clear_ForScene(iSceneIndex)))
		return E_FAIL;

	if (FAILED(m_pComponent_Manager->Clear_ForScene(iSceneIndex)))
		return E_FAIL;

	return S_OK;
}

LPDIRECT3DDEVICE9 CManagement::Get_Device() const
{
	if (nullptr == m_pDevice_Manager)
		return nullptr;

	return m_pDevice_Manager->GetDevice();
}

HRESULT CManagement::SetUp_CurrentScene(_int iSceneID, CScene * pNextScene)
{
	if (nullptr == m_pScene_Manager)
		return E_FAIL;

	return m_pScene_Manager->SetUp_CurrentScene(iSceneID, pNextScene);
}

HRESULT CManagement::Add_GameObjectToRenderList(
	ERenderID eRenderID,
	CGameObject * pGameObject)
{
	if (nullptr == m_pRenderer)
		return E_FAIL;

	return m_pRenderer->Add_GameObjectToRenderList(eRenderID, pGameObject);
}

HRESULT CManagement::Add_GameObject_Prototype(
	_uint iSceneIndex,
	const wstring & PrototypeTag,
	CGameObject * pPrototype)
{
	if (nullptr == m_pGameObject_Manager)
		return E_FAIL;

	return m_pGameObject_Manager->Add_GameObject_Prototype(iSceneIndex, PrototypeTag, pPrototype);
}

HRESULT CManagement::Add_GameObject_ToLayer(
	_uint iFromSceneIndex,
	const wstring & PrototypeTag,
	_uint iToSceneIndex,
	const wstring & LayerTag,
	void * pArg)
{
	if (nullptr == m_pGameObject_Manager)
		return E_FAIL;

	return m_pGameObject_Manager->Add_GameObject_ToLayer(iFromSceneIndex, PrototypeTag, iToSceneIndex, LayerTag, pArg);
}

HRESULT CManagement::Add_Component_Prototype(
	_uint iSceneIndex,
	const wstring & PrototypeTag,
	CComponent * pPrototype)
{
	if (nullptr == m_pComponent_Manager)
		return E_FAIL;

	return m_pComponent_Manager->Add_Component_Prototype(iSceneIndex, PrototypeTag, pPrototype);
}

CComponent * CManagement::Clone_Component(_uint iSceneIndex, const wstring & PrototypeTag, void * pArg)
{
	if (nullptr == m_pComponent_Manager)
		return nullptr;

	return m_pComponent_Manager->Clone_Component(iSceneIndex, PrototypeTag, pArg);
}

void CManagement::Free()
{
	if (Safe_Release(m_pRenderer))
	{
		MSG_BOX(L"Failed To Release m_pRenderer");
	}

	if (CComponent_Manager::DestroyInstance())
	{
		MSG_BOX(L"Failed To Destroy_Instance CComponent_Manager");
	}

	if (CGameObject_Manager::DestroyInstance())
	{
		MSG_BOX(L"Failed To Destroy_Instance CGameObject_Manager");
	}

	if (CScene_Manager::DestroyInstance())
	{
		MSG_BOX(L"Failed To Destroy_Instance CScene_Manager");
	}

	if (CGraphicDevice::DestroyInstance())
	{
		MSG_BOX(L"Failed To Destroy_Instance CDevice_Manager");
	}
}