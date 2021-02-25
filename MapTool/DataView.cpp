// DataView.cpp : ���� �����Դϴ�.
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


// CDataView �����Դϴ�.

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


// CDataView �޽��� ó�����Դϴ�.


void CDataView::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


BOOL CDataView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if (pMsg->message == 'W')
	{
		MSG_BOX(L"pressed W key");
	}

	return CFormView::PreTranslateMessage(pMsg);
}


void CDataView::OnAcceleratorW()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

}


void CDataView::OnBnClickedSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame* pMain = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	CMapToolView* pView = dynamic_cast<CMapToolView*>(pMain->m_MainSplitter.GetPane(0, 1));


	CFileDialog Dlg(FALSE, L"ini", L"*.ini", OFN_OVERWRITEPROMPT, L"Data File(*.ini) | *.ini||", this);
	TCHAR szPath[MAX_PATH] = L"";

	GetCurrentDirectory(MAX_PATH, szPath);
	PathRemoveFileSpec(szPath);
	lstrcatW(szPath, L"\\Data");
}
