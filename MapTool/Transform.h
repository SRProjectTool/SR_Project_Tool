#pragma once

#include "Component.h"

class CTransform : public CComponent
{
public:
	typedef struct tagTransformDesc
	{
		tagTransformDesc()
		{
			ZeroMemory(this, sizeof(tagTransformDesc));
			vScale = _float3(1.f, 1.f, 1.f);
			D3DXMatrixIdentity(&matWorld);
		}

		_float3 vScale, vRotate, vPosition;
		_float fSpeedPerSec = 0.f, fRotatePerSec = 0.f;
		_float4x4 matWorld;
	}TRANFORM_DESC;

private:
	explicit CTransform(LPDIRECT3DDEVICE9 pDevice);
	explicit CTransform(const CTransform& other);
	virtual ~CTransform() = default;

public: /* Getter */
	const TRANFORM_DESC& Get_TransformDesc() const;

public: /* Setter */
	void Set_Position(const _float3& vPos);
	void Set_WorldMatrix(const _float4x4& matWorld);


public:
	virtual HRESULT Ready_Component_Prototype() override;
	virtual HRESULT Ready_Component(void * pArg = nullptr) override;

public:
	HRESULT Update_Transform();
	void Move_Straight(_float fDeltaTime);
	void Move_Strafe(_float fDeltaTime);
	void Rotate_AxisY(_float fDeltaTime);

public:
	static CTransform* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual CComponent * Clone(void * pArg = nullptr) override;
	virtual void Free() override;

public:
	void Translate(_float3 translation);
		 
	void SetPositionX(_float x) { m_position.x = x; }
	void SetPositionY(_float y) { m_position.y = y; }
	void SetPositionZ(_float z) { m_position.z = z; }
	void SetRotationX(_float x) { m_rotation.x = x; }
	void SetRotationY(_float y) { m_rotation.y = y; }
	void SetRotationZ(_float z) { m_rotation.z = z; }
	void SetAddRotationX(_float x) { m_rotation.x += x; }
	void SetAddRotationY(_float y) { m_rotation.y += y; }
	void SetAddRotationZ(_float z) { m_rotation.z += z; }

private:
	GETTOR_SETTOR(_float3, m_position, _float3(0, 0, 0), Position)
	GETTOR_SETTOR(_float3, m_rotation, _float3(0, 0, 0), Rotation)
	GETTOR_SETTOR(_float3, m_scale, _float3(1, 1, 1), Scale)

private:
	TRANFORM_DESC m_Desc;
};

