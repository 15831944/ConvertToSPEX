// ConvertToSPEXView.h : interface of the CConvertToSPEXView class
//


#pragma once


class CConvertToSPEXView : public CView
{
protected: // create from serialization only
	CConvertToSPEXView();
	DECLARE_DYNCREATE(CConvertToSPEXView)

// Attributes
public:
	CConvertToSPEXDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CConvertToSPEXView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ConvertToSPEXView.cpp
inline CConvertToSPEXDoc* CConvertToSPEXView::GetDocument() const
   { return reinterpret_cast<CConvertToSPEXDoc*>(m_pDocument); }
#endif

