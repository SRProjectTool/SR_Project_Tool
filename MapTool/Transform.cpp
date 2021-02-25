#include "stdafx.h"
#include "Transform.h"

CTransform::CTransform(LPDIRECT3DDEVICE9 pDevice)
	: CComponent(pDevice)
{
	ZeroMemory(&m_Desc, sizeof(TRANFORM_DESC));
	m_Desc.vScale = _float3(1.f, 1.f, 1.f);
}

CTransform::CTransform(const CTransform & other)
	: CComponent(other)
	, m_Desc(other.m_Desc)
{
}

const CTransform::TRANFORM_DESC & CTransform::Get_TransformDesc() const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_Desc;
}

void CTransform::Set_Position(const _float3 & vPos)
{
	m_Desc.vPosition = vPos;
}

void CTransform::Set_WorldMatrix(const _float4x4 & matWorld)
{
	m_Desc.matWorld = matWorld;
}

HRESULT CTransform::Ready_Component_Prototype()
{
	return S_OK;
}

HRESULT CTransform::Ready_Component(void * pArg/* = nullptr*/)
{
	if (pArg)
	{
		memcpy(&m_Desc, pArg, sizeof(TRANFORM_DESC));
	}

	return S_OK;
}

HRESULT CTransform::Update_Transform()
{
	_float4x4 matScale, matRotX, matRotY, matRotZ, matTrans;
	D3DXMatrixScaling(&matScale, m_Desc.vScale.x, m_Desc.vScale.y, m_Desc.vScale.z);
	D3DXMatrixRotationX(&matRotX, m_Desc.vRotate.x);
	D3DXMatrixRotationY(&matRotY, m_Desc.vRotate.y);
	D3DXMatrixRotationZ(&matRotZ, m_Desc.vRotate.z);
	D3DXMatrixTranslation(&matTrans, m_Desc.vPosition.x, m_Desc.vPosition.y, m_Desc.vPosition.z);

	m_Desc.matWorld = matScale * matRotX * matRotY * matRotZ * matTrans;

	return S_OK;
}

void CTransform::Move_Straight(_float fDeltaTime)
{
	_float3 vLook;
	memcpy(&vLook, &m_Desc.matWorld.m[2][0], sizeof(_float3));
	D3DXVec3Normalize(&vLook, &vLook);

	m_Desc.vPosition += vLook * m_Desc.fSpeedPerSec * fDeltaTime;
}

void CTransform::Move_Strafe(_float fDeltaTime)
{
	_float3 vRight;
	memcpy(&vRight, &m_Desc.matWorld.m[0][0], sizeof(_float3));
	D3DXVec3Normalize(&vRight, &vRight);

	m_Desc.vPosition += vRight * m_Desc.fSpeedPerSec * fDeltaTime;
}

void CTransform::Rotate_AxisY(_float fDeltaTime)
{
	m_Desc.vRotate.y += m_Desc.fRotatePerSec * fDeltaTime;
}

CTransform * CTransform::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CTransform* pInstance = new CTransform(pDevice);
	if (FAILED(pInstance->Ready_Component_Prototype()))
	{
		MSG_BOX(L"Failed To Create Transform");
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CTransform::Clone(void * pArg/* = nullptr*/)
{
	CTransform* pClone = new CTransform(*this);
	if (FAILED(pClone->Ready_Component(pArg)))
	{
		MSG_BOX(L"Failed To Clone Transform");
		Safe_Release(pClone);
	}

	return pClone;
}

void CTransform::Free()
{
	CComponent::Free();
}

void CTransform::Translate(_float3 translation)
{
	_float4x4 rotate;

	D3DXMatrixRotationYawPitchRoll(&rotate, D3DXToRadian(m_rotation.y), D3DXToRadian(m_rotation.x), D3DXToRadian(m_rotation.z));
	D3DXVec3TransformCoord(&translation, &translation, &rotate);
	m_position += translation;
}
