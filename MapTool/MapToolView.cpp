
// MapToolView.cpp : CMapToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MapTool.h"
#endif

#include "MapToolDoc.h"
#include "MapToolView.h"
#include "MainFrm.h"
#include "Management.h"
#include "Cube.h"
#include "VIBuffer.h"
#include "VIBuffer_RectColor.h"
#include "VIBuffer_CubeTexture.h"
#include "MapScene.h"
#include "Transform.h"
#include "Texture.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMapToolView

HWND g_hWND;

IMPLEMENT_DYNCREATE(CMapToolView, CScrollView)

BEGIN_MESSAGE_MAP(CMapToolView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMapToolView 생성/소멸

CMapToolView::CMapToolView()
{
}

CMapToolView::~CMapToolView()
{
	if (CGraphicDevice::DestroyInstance())
	{
		MSG_BOX(L"Failed To DestroyInstance CGraphicDevice");
	}

	if (CManagement::DestroyInstance())
	{
		MSG_BOX(L"Failed To DestroyInstance CManagement");
	}
}

BOOL CMapToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CMapToolView 그리기

void CMapToolView::OnDraw(CDC* /*pDC*/)
{
	CMapToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (m_pManagement->Update_Engine())
		return;

	if (FAILED(m_pManagement->Render_Engine()))
		return;
}


// CMapToolView 인쇄

BOOL CMapToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMapToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMapToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMapToolView 진단

#ifdef _DEBUG
void CMapToolView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMapToolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

HRESULT CMapToolView::ReadyDefaultSetting()
{
	/* 조명 off */
	if (FAILED(m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE)))
		return E_FAIL;

	if (FAILED(m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE)))
		return E_FAIL;

	return S_OK;
}

HRESULT CMapToolView::ReadyResources()
{
	/* For.GameObject_Cube */
	if (FAILED(m_pManagement->Add_GameObject_Prototype(
		(_uint)ESceneType::Static,
		L"GameObject_Cube",
		CCube::Create(m_pDevice))))
	{
		MSG_BOX(L"Failed To Add GameObject_Cube");
		return E_FAIL;
	}

	/* For.Component_VIBuffer_RectColor */
	if (FAILED(m_pManagement->Add_Component_Prototype(
		(_uint)ESceneType::Static,
		L"Component_VIBuffer_RectColor",
		CVIBuffer_RectColor::Create(m_pDevice))))
	{
		MSG_BOX(L"Failed To Add Compoentn_VIBuffer_TriColor");
		return E_FAIL;
	}

	/* For.Component_Transform */
	if (FAILED(m_pManagement->Add_Component_Prototype(
		(_uint)ESceneType::Static,
		L"Component_Transform",
		CTransform::Create(m_pDevice))))
	{
		MSG_BOX(L"Failed To Add Component_Transform");
		return E_FAIL;
	}

	/* For.Component_VIBuffer_CubeTexture */
	if (FAILED(m_pManagement->Add_Component_Prototype(
		(_uint)ESceneType::Static,
		L"Component_VIBuffer_CubeTexture",
		CVIBuffer_CubeTexture::Create(m_pDevice))))
	{
		MSG_BOX(L"Failed To Add Component_VIBuffer_CubeTexture");
		return E_FAIL;
	}

	/* For.Component_Texture_Cube */
	if (FAILED(m_pManagement->Add_Component_Prototype(
		(_uint)ESceneType::Static,
		L"Component_Texture_Cube",
		CTexture::Create(m_pDevice, ETextureType::Cube, L"../Resources/Cube%d.dds", 1))))
	{
		MSG_BOX(L"Failed To Add Component_Texture_Cube");
		return E_FAIL;
	}

	return S_OK;
}

CMapToolDoc* CMapToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapToolDoc)));
	return (CMapToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CMapToolView 메시지 처리기


void CMapToolView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CMainFrame* pMain = static_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	RECT rcMainRect = NONE;
	RECT rcView = NONE;
	_int iGapX = 0;
	_int iGapY = 0;

	g_hWND = m_hWnd;
	SetScrollSizes(MM_TEXT, CSize(TILECX * TILEX, (TILECY >> 1) * TILEY));

	pMain->GetWindowRect(&rcMainRect);
	::SetRect(&rcMainRect,
		0,
		0,
		rcMainRect.right - rcMainRect.left,
		rcMainRect.bottom - rcMainRect.top);
	GetClientRect(&rcView);
	iGapX = rcMainRect.right - rcView.right;
	iGapY = rcMainRect.bottom - rcView.bottom;
	pMain->SetWindowPos(nullptr,
		0,
		0,
		WINCX + iGapX,
		WINCY + iGapY,
		SWP_NOZORDER | SWP_NOMOVE);

	m_pManagement = CManagement::GetInstance();

	if (FAILED(m_pManagement->Ready_Engine((_uint)ESceneType::Max)))
		return;

	m_pDevice = m_pManagement->Get_Device();
	if (nullptr == m_pDevice)
	{
		MSG_BOX(L"m_pDevice is null");
		return;
	}
	
	if (FAILED(ReadyDefaultSetting()))
	{
		MSG_BOX(L"Failed To ReadyDefaultSetting");
		return;
	}

	if (FAILED(ReadyResources()))
	{
		MSG_BOX(L"Failed To ReadyResources");
		return;
	}

	if (FAILED(m_pManagement->SetUp_CurrentScene((_int)ESceneType::Map, CMapScene::Create(m_pDevice))))
	{
		MSG_BOX(L"Failed To SetUp_CurrentScene To MapScene");
		return;
	}
}
