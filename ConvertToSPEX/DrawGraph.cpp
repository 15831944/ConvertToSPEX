// DrawGraph.cpp : implementation file
//

#include "stdafx.h"
#include "ConvertToSPEX.h"
#include "DrawGraph.h"

#include <algorithm>
#include <functional>
using std::min_element;
using std::max_element;

// CDrawGraph

IMPLEMENT_DYNAMIC(CDrawGraph, CWnd)

CDrawGraph::CDrawGraph()
{

}

CDrawGraph::~CDrawGraph()
{
}


BEGIN_MESSAGE_MAP(CDrawGraph, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CDrawGraph message handlers


CConvertToSPEXDoc* CDrawGraph::GetMyDocument() const 
{
	CView *pParent = (CView *)GetParent();
	VERIFY(pParent);
	CDocument *m_pDocument = pParent->GetDocument();

	VERIFY(m_pDocument);
	ASSERT_KINDOF(CConvertToSPEXDoc,m_pDocument);
	return (CConvertToSPEXDoc*)m_pDocument;
}

void CDrawGraph::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CConvertToSPEXDoc* pDoc = GetMyDocument();

	dc.MoveTo(0,0);
//	dc.LineTo(10,10);

	if(pDoc->fpdata.empty())
		return;

	float f1 = *min_element(pDoc->fpdata.begin(), pDoc->fpdata.end()); 
	float f2 = *max_element(pDoc->fpdata.begin(), pDoc->fpdata.end()); 
	if(f1 == f2)
		f2++;

	CRect cr;
	GetWindowRect(cr);
	float w = cr.Width();
	float h = cr.Height();

	dc.MoveTo(0,h - (pDoc->fpdata[0]-f1)/(f1-f2)*h);

	for(int i=0; i < pDoc->fpdata.size(); i++)
	{
		dc.LineTo( i*w/pDoc->fpdata.size() , (pDoc->fpdata[i]-f1)/(f2-f1)*-h +h );
	}

}

void CDrawGraph::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CConvertToSPEXDoc* pDoc = GetMyDocument();

	CWnd::OnLButtonDown(nFlags, point);
}
