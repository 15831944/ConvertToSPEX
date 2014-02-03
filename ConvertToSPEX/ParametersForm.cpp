// ParametersForm.cpp : implementation file
//

#include "stdafx.h"
#include "ConvertToSPEX.h"
#include "ParametersForm.h"


// CParametersForm

IMPLEMENT_DYNCREATE(CParametersForm, CFormView)

CParametersForm::CParametersForm()
	: CFormView(CParametersForm::IDD)
{

}

CParametersForm::~CParametersForm()
{
}

void CParametersForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_CF, c_EditCF);
	DDX_Control(pDX, IDC_EDIT_SW, c_EditSW);
	DDX_Control(pDX, IDC_HIDDEN, c_DrawArea);
}

BEGIN_MESSAGE_MAP(CParametersForm, CFormView)
	ON_EN_KILLFOCUS(IDC_EDIT_CF, &CParametersForm::OnEnKillfocusEditCf)
	ON_EN_KILLFOCUS(IDC_EDIT_SW, &CParametersForm::OnEnKillfocusEditSw)
END_MESSAGE_MAP()


// CParametersForm diagnostics

#ifdef _DEBUG
void CParametersForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CParametersForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


CConvertToSPEXDoc* CParametersForm::GetMyDocument() const 
{
	CDocument *m_pDocument = GetDocument();

	VERIFY(m_pDocument);
	ASSERT_KINDOF(CConvertToSPEXDoc,m_pDocument);
	return (CConvertToSPEXDoc*)m_pDocument;
}

// CParametersForm message handlers

void CParametersForm::OnEnKillfocusEditCf()
{
	CConvertToSPEXDoc* pDoc = GetMyDocument();

	CString str;
	c_EditCF.GetWindowText(str);
	pDoc->dCF = atof( str );
	pDoc->UpdateAllViews(NULL);
}

void CParametersForm::OnEnKillfocusEditSw()
{
	CConvertToSPEXDoc* pDoc = GetMyDocument();

	CString str;
	c_EditCF.GetWindowText(str);
	pDoc->dCF = atof( str );
	pDoc->UpdateAllViews(NULL);
}

void CParametersForm::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	CConvertToSPEXDoc* pDoc = GetMyDocument();

	CString str;
	str.Format("%f", pDoc->dCF);
	c_EditCF.SetWindowText(str);

	str.Format("%f", pDoc->dSW);
	c_EditSW.SetWindowText(str);

	c_DrawArea.Invalidate();
}
