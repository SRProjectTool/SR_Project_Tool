
// MapToolView.h : CMapToolView 클래스의 인터페이스
//

#pragma once


class CMapToolView : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CMapToolView();
	DECLARE_DYNCREATE(CMapToolView)

// 특성입니다.
public:
	class CMapToolDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMapToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// 사용자 정의 함수
public:
	HRESULT ReadyDefaultSetting();
	HRESULT ReadyResources();

// 사용자 정의 멤버변수
protected:
	LPDIRECT3DDEVICE9 m_pDevice = nullptr;
	class CManagement* m_pManagement = nullptr;

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // MapToolView.cpp의 디버그 버전
inline CMapToolDoc* CMapToolView::GetDocument() const
   { return reinterpret_cast<CMapToolDoc*>(m_pDocument); }
#endif

