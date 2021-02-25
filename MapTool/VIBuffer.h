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
	����ڰ� �����س��� ���ؽ����� �迭�� ���� �� �����ϴ� Com��ü�� ������
	*/
	LPDIRECT3DVERTEXBUFFER9	m_pVB = nullptr;
	_size m_iVertexCount = 0; // ��������
	_size m_iVertexSize = 0;  // ������ ���� �޸� ũ��
	_size m_iTriCount = 0; // ������ ����
	_uint m_iFVF = 0; // Flexible Vertex Format	

	/*
	LPDIRECT3DINDEXBUFFER9:
	����ڰ� �����س��� �ε������� �迭�� ���� �� �����ϴ� Com��ü�� ������
	*/
	LPDIRECT3DINDEXBUFFER9 m_pIB = nullptr;
	D3DFORMAT m_IndexFMT = D3DFMT_INDEX16;
	_size m_iIndexSize = 0; /* �ε��� �ڷ����� ũ�� */

	_float3* m_pVertices = nullptr;
	_float3* m_pConvertVertices = nullptr;
};

