#pragma once



// CDataView 폼 뷰입니다.

class CDataView : public CFormView
{
	DECLARE_DYNCREATE(CDataView)

protected:
	CDataView();           // 동적 만들기에 사용되는 protected 생성자입니다.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton12();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnAcceleratorW();

// 사용자 정의 멤버 변수
private:
	HACCEL m_haccel;
public:
	afx_msg void OnBnClickedSave();
};


