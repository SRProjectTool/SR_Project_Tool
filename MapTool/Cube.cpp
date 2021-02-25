#include "stdafx.h"
#include "Cube.h"
#include "VIBuffer.h"
#include "VIBuffer_RectColor.h"
#include "Management.h"
#include "Transform.h"
#include "Texture.h"

CCube::CCube(LPDIRECT3DDEVICE9 pDevice)
	: CGameObject(pDevice)
{
}

CCube::CCube(const CCube & other)
	: CGameObject(other)
{
}

HRESULT CCube::Ready_GameObject_Prototype()
{
	CGameObject::Ready_GameObject_Prototype();

	return S_OK;
}

HRESULT CCube::Ready_GameObject(void * pArg/* = nullptr*/)
{
	CGameObject::Ready_GameObject(pArg);

	/* Com_Buffer */
	if (FAILED(CGameObject::Add_Component(
		(_uint)ESceneType::Static,
		L"Component_VIBuffer_CubeTexture",
		L"Com_Buffer",
		(CComponent**)&m_pVIBufferCom)))
		return E_FAIL;

	/* Com_Transform */
	if (FAILED(CGameObject::Add_Component(
		(_uint)ESceneType::Static,
		L"Component_Transform",
		L"Com_Transform",
		(CComponent**)&m_pTransformCom,
		pArg)))
		return E_FAIL;

	/* Com_Texture */
	if (FAILED(CGameObject::Add_Component(
		(_uint)ESceneType::Static,
		L"Component_Texture_Cube",
		L"Com_Texture",
		(CComponent**)&m_pTextureCom)))
		return E_FAIL;

	return S_OK;
}

_uint CCube::Update_GameObject()
{
	CGameObject::Update_GameObject();

	return _uint();
}

_uint CCube::LateUpdate_GameObject()
{
	CGameObject::LateUpdate_GameObject();

	CManagement* pManagement = CManagement::GetInstance();
	if (nullptr == pManagement)
		return 0;

	if (FAILED(pManagement->Add_GameObjectToRenderList(ERenderID::NonAlpha, this)))
		return 0;

	return _uint();
}

HRESULT CCube::Render_GameObject()
{
	CManagement* pManagement = CManagement::GetInstance();
	if (nullptr == pManagement)
		return E_FAIL;

	CGameObject::Render_GameObject();

	if (FAILED(m_pTextureCom->Set_Texture(0)))
		return E_FAIL;
	
	if (FAILED(m_pVIBufferCom->Render_Buffer()))
		return E_FAIL;

	return S_OK;
}

CCube * CCube::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CCube* pInstance = new CCube(pDevice);
	if (FAILED(pInstance->Ready_GameObject_Prototype()))
	{
		MSG_BOX(L"Failed To Create Cube");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CGameObject * CCube::Clone(void * pArg/* = nullptr*/)
{
	CCube* pClone = new CCube(*this);
	if (FAILED(pClone->Ready_GameObject(pArg)))
	{
		MSG_BOX(L"Failed To Clone Cube");
		Safe_Release(pClone);
	}

	return pClone;
}

void CCube::Free()
{
	Safe_Release(m_pVIBufferCom);
	Safe_Release(m_pTransformCom);
	Safe_Release(m_pTextureCom);

	CGameObject::Free();
}
