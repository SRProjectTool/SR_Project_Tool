#pragma once

#include "Component.h"

class CVIBuffer abstract : public CComponent
{
protected:
	explicit CVIBuffer(LPDIRECT3DDEVICE9 pDevice);
	explicit CVIBuffer(const CVIBuffer& other);
	virtual ~CVIBuffer() = default;

public:
	virtual HRESULT Ready_Component_Prototype() = 0;
	virtual HRESULT Ready_Component(void * pArg = nullptr) = 0;
	virtual HRESULT Render_Buffer() = 0;

public:
	template<typename T>
	HRESULT CVIBuffer::Set_Transform(
		const _float4x4* pWorldMatrix,
		const _float4x4* pViewMatrix,
		const _float4x4* pProjMatrix)
	{
		T* pVertices = nullptr;
		m_pVB->Lock(0, 0, (void**)&pVertices, 0);

		for (_size i = 0; i < m_iVertexCount; ++i)
		{
			D3DXVec3TransformCoord(
				&m_pConvertVertices[i],
				&m_pVertices[i],
				pWorldMatrix);

			D3DXVec3TransformCoord(
				&m_pConvertVertices[i],
				&m_pConvertVertices[i],
				pViewMatrix);

			if (1.f < m_pConvertVertices[i].z)
			{
				D3DXVec3TransfromCoord(
					&m_pConvertViertices[i],
					&m_pConvertViertices[i],
					pProjMatrix);
			}

			((T*)pVertices)[i].vPosition = m_pConvertVertices[i];
		}
	}

public:
	virtual CComponent * Clone(void * pArg = nullptr) = 0;
	virtual void Free() = 0;

protected:
	/*
	LPDIRECT3DVERTEXBUFFER9:
	사용자가 생성해놓은 버텍스들을 배열로 보관 및 관리하는 Com객체의 포인터
	*/
	LPDIRECT3DVERTEXBUFFER9	m_pVB = nullptr;
	_size m_iVertexCount = 0; // 정점개수
	_size m_iVertexSize = 0;  // 정점의 개당 메모리 크기
	_size m_iTriCount = 0; // 폴리곤 개수
	_uint m_iFVF = 0; // Flexible Vertex Format	

	/*
	LPDIRECT3DINDEXBUFFER9:
	사용자가 생성해놓은 인덱스들을 배열로 보관 및 관리하는 Com객체의 포인터
	*/
	LPDIRECT3DINDEXBUFFER9 m_pIB = nullptr;
	D3DFORMAT m_IndexFMT = D3DFMT_INDEX16;
	_size m_iIndexSize = 0; /* 인덱스 자료형의 크기 */

	_float3* m_pVertices = nullptr;
	_float3* m_pConvertVertices = nullptr;
};

