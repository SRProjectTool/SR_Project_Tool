#pragma once

#include "Component.h"

class CCamera : public CComponent
{
public:
	explicit CCamera(LPDIRECT3DDEVICE9 pDevice);
	explicit CCamera(const CCamera& other);
	virtual ~CCamera() = default;

public:
	//Ÿ�ٰ� ī�޶��� �Ÿ�, Ÿ���� ȸ����, Ÿ���� ��ġ
	void CameraTarget(_float3 _targetDistance, _float3 _rotation, _float3 _targetPos);

	//Ÿ�ٰ� ī�޶��� �Ÿ�, Ÿ���� ȸ����, Ÿ���� ��ġ, �ӵ�
	//ī�޶� Ÿ�ٱ��� õõ�� _speed�� �ӵ���ŭ �̵���
	void CameraTarget(_float3 _targetDistance, _float3 _rotation, _float3 _targetPos, _float _speed);

private:
	void CameraMove();
	void CameraRotation();
	void MatrixCalculate();

	SHARED(class CTransform) m_transform;

protected:
	GETTOR_SETTOR(_float4x4, m_matView, {}, ViewMatrix)
	GETTOR_SETTOR(_float4x4, m_matProj, {}, ProjMatrix)

	// ������ġ , ī�޶� �ٶ󺸴°� , ī�޶��� ��� ����
	GETTOR_SETTOR(_float3, m_at, {}, At)
	GETTOR_SETTOR(_float3, m_up, {}, Up)
	POINT centerPt;

	GETTOR_SETTOR(_float, m_moveSpeed, 5, MoveSpeed)
	GETTOR_SETTOR(_float, m_mouseSensitivity, 5.5f, MouseSensitivity)

	GETTOR_SETTOR(_float3, m_tAt, FLOAT3_ZERO, TempAt)
	GETTOR_SETTOR(_float3, m_tUp, FLOAT3_ZERO, TempUp)

	GETTOR_SETTOR(_float, m_near, 1, Near)
	GETTOR_SETTOR(_float, m_far, 1000, Far)
	GETTOR_SETTOR(_float, m_fov, 45, Fov)
};
