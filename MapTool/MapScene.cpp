#include "stdafx.h"
#include "MapScene.h"
#include "Management.h"
#include "Transform.h"

CMapScene::CMapScene(LPDIRECT3DDEVICE9 pDevice)
	: CScene(pDevice)
{
}

HRESULT CMapScene::Ready_Scene()
{
	if (FAILED(CScene::Ready_Scene()))
		return E_FAIL;

	if (FAILED(Add_Cube_Layer(L"Layer_Cube")))
		return E_FAIL;

	return S_OK;
}

_uint CMapScene::Update_Scene(_float fDeltaTime)
{
	CScene::Update_Scene(fDeltaTime);

	return NO_EVENT;
}

_uint CMapScene::LateUpdate_Scene(_float fDeltaTime)
{
	CScene::LateUpdate_Scene(fDeltaTime);

	return NO_EVENT;
}

HRESULT CMapScene::Add_Cube_Layer(const wstring & LayerTag)
{
	CManagement* pManagement = CManagement::GetInstance();
	if (nullptr == pManagement)
		return E_FAIL;

	CTransform::TRANFORM_DESC TransformDesc;

	TransformDesc.vPosition = _float3(0.f, 0.f, 0.f);

	if (FAILED(pManagement->Add_GameObject_ToLayer(
		(_uint)ESceneType::Static,
		L"GameObject_Cube",
		(_uint)ESceneType::Static,
		LayerTag,
		&TransformDesc)))
	{
		return E_FAIL;
	}

	TransformDesc.vPosition = _float3(10.f, 0.f, 0.f);

	if (FAILED(pManagement->Add_GameObject_ToLayer(
		(_uint)ESceneType::Static,
		L"GameObject_Cube",
		(_uint)ESceneType::Static,
		LayerTag,
		&TransformDesc)))
	{
		return E_FAIL;
	}

	return S_OK;
}

CMapScene* CMapScene::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CMapScene* pInstance = new CMapScene(pDevice);
	if (FAILED(pInstance->Ready_Scene()))
	{
		MSG_BOX(L"Failed To Create CMapScene");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CMapScene::Free()
{
	CScene::Free();
}