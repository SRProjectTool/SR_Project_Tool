#pragma once



// CMiniMapView �� ���Դϴ�.

class CMiniMapView : public CFormView
{
	DECLARE_DYNCREATE(CMiniMapView)

protected:
	CMiniMapView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CMiniMapView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MINIMAPVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};


