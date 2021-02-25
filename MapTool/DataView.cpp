// DataView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MapTool.h"
#include "DataView.h"

#include "MainFrm.h"
#include "MapToolView.h"

// CDataView

IMPLEMENT_DYNCREATE(CDataView, CFormView)

CDataView::CDataView()
	: CFormView(IDD_DATAVIEW)
{

}

CDataView::~CDataView()
{
}

void CDataView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDataView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CDataView::OnBnClickedButton1)
	ON_COMMAND(ID_ACCELERATOR32771, &CDataView::OnAcceleratorW)
	ON_BN_CLICKED(IDC_BUTTON9, &CDataView::OnBnClickedSave)
END_MESSAGE_MAP()


// CDataView 진단입니다.

#ifdef _DEBUG
void CDataView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDataView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDataView 메시지 처리기입니다.


void CDataView::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


BOOL CDataView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == 'W')
	{
		MSG_BOX(L"pressed W key");
	}

	return CFormView::PreTranslateMessage(pMsg);
}


void CDataView::OnAcceleratorW()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

}


void CDataView::OnBnClickedSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CMapToolView* pView = dynamic_cast<CMapToolView*>(pMain->m_MainSplitter.GetPane(0, 1));


	CFileDialog Dlg(FALSE, L"ini", L"*.ini", OFN_OVERWRITEPROMPT, L"Data File(*.ini) | *.ini||", this);
	TCHAR szPath[MAX_PATH] = L"";

	GetCurrentDirectory(MAX_PATH, szPath);
	PathRemoveFileSpec(szPath);
	lstrcatW(szPath, L"\\Data");
}
