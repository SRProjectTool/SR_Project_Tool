#pragma once



// CDataView �� ���Դϴ�.

class CDataView : public CFormView
{
	DECLARE_DYNCREATE(CDataView)

protected:
	CDataView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CDataView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DATAVIEW };
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
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton12();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnAcceleratorW();

// ����� ���� ��� ����
private:
	HACCEL m_haccel;
public:
	afx_msg void OnBnClickedSave();
};


