#include "stdafx.h"
#include "Camera.h"

CCamera::CCamera(LPDIRECT3DDEVICE9 pDevice)
	: CComponent(pDevice)
{
}

CCamera::CCamera(const CCamera & other)
	: CComponent(other)
{
}

void CCamera::CameraTarget(_float3 _targetDistance, _float3 _rotation, _float3 _targetPos)
{
	D3DXMATRIX matWorld, matDir, matRotX, matRotY, matRotZ, matPos;

	//거리
	D3DXMatrixTranslation(&matDir, _targetDistance.x, _targetDistance.y, _targetDistance.z);
	// 회전

	D3DXMatrixRotationX(&matRotX, _rotation.x);
	D3DXMatrixRotationY(&matRotY, _rotation.y);
	D3DXMatrixRotationZ(&matRotZ, _rotation.z);
	// 위치
	D3DXMatrixTranslation(&matPos, _targetPos.x, _targetPos.y, _targetPos.z);
	matWorld = matDir * matRotX * matRotY * matRotZ * matPos;
	_float3 eye = _float3(matWorld._41, matWorld._42, matWorld._43);

	//GetOwner()->GetComponent<CTransformComponent>()->SetPosition(eye);
}

void CCamera::CameraTarget(_float3 _targetDistance, _float3 _rotation, _float3 _targetPos, _float _speed)
{
	//if (GetOwner()->GetComponent<CTransformComponent>()->GetPosition() == _targetPos)
	//	return;

	//D3DXMATRIX matWorld, matDir, matRotX, matRotY, matRotZ, matPos;

	////거리
	//D3DXMatrixTranslation(&matDir, _targetDistance.x, _targetDistance.y, _targetDistance.z);
	//// 회전

	//D3DXMatrixRotationX(&matRotX, _rotation.x);
	//D3DXMatrixRotationY(&matRotY, _rotation.y);
	//D3DXMatrixRotationZ(&matRotZ, _rotation.z);
	//// 위치
	//D3DXMatrixTranslation(&matPos, _targetPos.x, _targetPos.y, _targetPos.z);
	//matWorld = matDir * matRotX * matRotY * matRotZ * matPos;

	//_float3 dir = GetOwner()->GetComponent<CTransformComponent>()->GetPosition() - _targetPos;
	//D3DXVec3Normalize(&dir, &dir);
	//dir *= GET_DT * _speed;

	//GetOwner()->GetComponent<CTransformComponent>()->SetPosition(GetOwner()->GetComponent<CTransformComponent>()->GetPosition() + dir);
}

void CCamera::CameraMove()
{
	//#define __CAMERAMOVE_ON

#ifdef __CAMERAMOVE_ON
	if (GetAsyncKeyState(0x57)) // 'W' key, front move
	{
		GetOwner()->GetComponent<CTransformComponent>()->Translate(FLOAT3_FORWARD * GET_DT);
	}

	if (GetAsyncKeyState(0x53)) // 'S' key, back move
	{
		GetOwner()->GetComponent<CTransformComponent>()->Translate(FLOAT3_BACK * GET_DT);
	}

	if (GetAsyncKeyState(0x41)) // 'A' key, left move
	{
		GetOwner()->GetComponent<CTransformComponent>()->Translate(FLOAT3_LEFT * GET_DT);
	}

	if (GetAsyncKeyState(0x44)) // 'D' key, right move
	{
		GetOwner()->GetComponent<CTransformComponent>()->Translate(FLOAT3_RIGHT * GET_DT);
	}
#endif // __CAMERAMOVE_ON
}

void CCamera::CameraRotation()
{
	//// 바라보는곳 수정
	//POINT curPt;
	//GetCursorPos(&curPt);
	//SetCursorPos(centerPt.x, centerPt.y);
	////centerPt = CInputManager::GetInstance()->GetMousePos();


	//// 카메라 회전
	//if (curPt.y < centerPt.y) // mouse up look
	//{
	//	_float angleY = GET_DT * (abs(curPt.y - centerPt.y) * m_mouseSensitivity);
	//	GetOwner()->GetComponent<CTransformComponent>()->SetAddRotationX(-1 * angleY);
	//}

	//if (curPt.y > centerPt.y) // mouse down look
	//{
	//	_float angleY = GET_DT * (abs(curPt.y - centerPt.y) * m_mouseSensitivity);
	//	GetOwner()->GetComponent<CTransformComponent>()->SetAddRotationX(angleY);
	//}

	//if (curPt.x < centerPt.x) // mouse left look
	//{
	//	_float angleX = CFRC::GetInstance()->GetDeltaTime() * (abs(curPt.x - centerPt.x) * m_mouseSensitivity);
	//	GetOwner()->GetComponent<CTransformComponent>()->SetAddRotationY(-1 * angleX);
	//}

	//if (curPt.x > centerPt.x) // mouse right look
	//{
	//	_float angleX = CFRC::GetInstance()->GetDeltaTime() * (abs(curPt.x - centerPt.x) * m_mouseSensitivity);
	//	GetOwner()->GetComponent<CTransformComponent>()->SetAddRotationY(angleX);
	//}
}

void CCamera::MatrixCalculate()
{
	//m_tAt = m_at;
	//m_tUp = m_up;

	//_float4x4 rotationMatrix;
	//D3DXMatrixRotationYawPitchRoll(&rotationMatrix, D3DXToRadian(GetOwner()->GetComponent<CTransformComponent>()->GetRotation().y), D3DXToRadian(GetOwner()->GetComponent<CTransformComponent>()->GetRotation().x), D3DXToRadian(GetOwner()->GetComponent<CTransformComponent>()->GetRotation().z));
	//D3DXVec3TransformCoord(&m_tAt, &m_tAt, &rotationMatrix);
	//D3DXVec3TransformCoord(&m_tUp, &m_tUp, &rotationMatrix);

	//m_tAt += GetOwner()->GetComponent<CTransformComponent>()->GetPosition();
}
