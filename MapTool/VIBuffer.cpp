#include "stdafx.h"
#include "VIBuffer.h"


CVIBuffer::CVIBuffer(LPDIRECT3DDEVICE9 pDevice)
	: CComponent(pDevice)
{
}

CVIBuffer::CVIBuffer(const CVIBuffer & other)
	: CComponent(other)
	, m_pVB(other.m_pVB)
	, m_pIB(other.m_pIB)
	, m_iVertexCount(other.m_iVertexCount)
	, m_iVertexSize(other.m_iVertexSize)
	, m_iTriCount(other.m_iTriCount)
	, m_iFVF(other.m_iFVF)
	, m_iIndexSize(other.m_iIndexSize)
	, m_IndexFMT(other.m_IndexFMT)
	, m_pVertices(other.m_pVertices)
	, m_pConvertVertices(other.m_pConvertVertices)
{
	Safe_AddRef(m_pVB);
	Safe_AddRef(m_pIB);
}

HRESULT CVIBuffer::Ready_Component_Prototype()
{
	/* ���ؽ����� Com��ü ���� �Լ� */
	if (FAILED(m_pDevice->CreateVertexBuffer(
		m_iVertexCount * m_iVertexSize, /* ���ؽ� �迭�� �� �޸� ������ */
		0, /* ����� D3DUSAGE_DYNAMIC���� �μ����� �������۸� �ǹ� */
		m_iFVF,
		D3DPOOL_MANAGED, /* �޸� ���� ��� */
		&m_pVB,
		nullptr)))
	{
		MSG_BOX(L"Failed To CreateVertexBuffer");
		return E_FAIL;
	}

	/* �ε������� Com��ü ���� �Լ� */
	if (FAILED(m_pDevice->CreateIndexBuffer(
		m_iTriCount * m_iIndexSize, /* �ε��� �迭�� �� �޸� ������ */
		0, /* ����� D3DUSAGE_DYNAMIC���� �μ����� �������۸� �ǹ� */
		m_IndexFMT,
		D3DPOOL_MANAGED, /* �޸� ���� ��� */
		&m_pIB,
		nullptr)))
	{
		MSG_BOX(L"Failed To CreateIndexBuffer");
		return E_FAIL;
	}

	m_pVertices = new _float3[m_iVertexCount];
	m_pConvertVertices = new _float3[m_iVertexCount];

	return S_OK;
}

HRESULT CVIBuffer::Ready_Component(void * pArg/* = nullptr*/)
{
	return S_OK;
}

HRESULT CVIBuffer::Render_Buffer()
{
	/* ��ġ���� ���� ���ؽ����۸� �Ѱ��ش�. */
	if (FAILED(m_pDevice->SetStreamSource(0, m_pVB, 0, m_iVertexSize)))
		return E_FAIL;

	/* ��ġ���� FVF ���� */
	if (FAILED(m_pDevice->SetFVF(m_iFVF)))
		return E_FAIL;

	/* ��ġ���� �ε��� ���� ���� */
	if (FAILED(m_pDevice->SetIndices(m_pIB)))
		return E_FAIL;

	return S_OK;
}

void CVIBuffer::Free()
{
	if (!m_IsClone)
	{
		Safe_Delete_Array(m_pVertices);
		Safe_Delete_Array(m_pConvertVertices);
	}

	Safe_Release(m_pVB);
	Safe_Release(m_pIB);

	CComponent::Free();
}
