// ConvertToSPEXView.cpp : implementation of the CConvertToSPEXView class
//

#include "stdafx.h"
#include "ConvertToSPEX.h"

#include "ConvertToSPEXDoc.h"
#include "ConvertToSPEXView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CConvertToSPEXView

IMPLEMENT_DYNCREATE(CConvertToSPEXView, CView)

BEGIN_MESSAGE_MAP(CConvertToSPEXView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CConvertToSPEXView construction/destruction

CConvertToSPEXView::CConvertToSPEXView()
{
	// TODO: add construction code here

}

CConvertToSPEXView::~CConvertToSPEXView()
{
}

BOOL CConvertToSPEXView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CConvertToSPEXView drawing

void CConvertToSPEXView::OnDraw(CDC* /*pDC*/)
{
	CConvertToSPEXDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CConvertToSPEXView printing

BOOL CConvertToSPEXView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CConvertToSPEXView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CConvertToSPEXView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CConvertToSPEXView diagnostics

#ifdef _DEBUG
void CConvertToSPEXView::AssertValid() const
{
	CView::AssertValid();
}

void CConvertToSPEXView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CConvertToSPEXDoc* CConvertToSPEXView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CConvertToSPEXDoc)));
	return (CConvertToSPEXDoc*)m_pDocument;
}
#endif //_DEBUG


// CConvertToSPEXView message handlers
