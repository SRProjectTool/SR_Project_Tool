// MiniMapView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MapTool.h"
#include "MiniMapView.h"


// CMiniMapView

IMPLEMENT_DYNCREATE(CMiniMapView, CFormView)

CMiniMapView::CMiniMapView()
	: CFormView(IDD_MINIMAPVIEW)
{

}

CMiniMapView::~CMiniMapView()
{
}

void CMiniMapView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMiniMapView, CFormView)
END_MESSAGE_MAP()


// CMiniMapView 진단입니다.

#ifdef _DEBUG
void CMiniMapView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMiniMapView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMiniMapView 메시지 처리기입니다.
