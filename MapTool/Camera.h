#pragma once

#include "Component.h"

class CCamera : public CComponent
{
public:
	explicit CCamera(LPDIRECT3DDEVICE9 pDevice);
	explicit CCamera(const CCamera& other);
	virtual ~CCamera() = default;

public:
	//타겟과 카메라의 거리, 타겟의 회전값, 타겟의 위치
	void CameraTarget(_float3 _targetDistance, _float3 _rotation, _float3 _targetPos);

	//타겟과 카메라의 거리, 타겟의 회전값, 타겟의 위치, 속도
	//카메라가 타겟까지 천천히 _speed의 속도만큼 이동함
	void CameraTarget(_float3 _targetDistance, _float3 _rotation, _float3 _targetPos, _float _speed);

private:
	void CameraMove();
	void CameraRotation();
	void MatrixCalculate();

	SHARED(class CTransform) m_transform;

protected:
	GETTOR_SETTOR(_float4x4, m_matView, {}, ViewMatrix)
	GETTOR_SETTOR(_float4x4, m_matProj, {}, ProjMatrix)

	// 현재위치 , 카메라가 바라보는곳 , 카메라의 상방 벡터
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
