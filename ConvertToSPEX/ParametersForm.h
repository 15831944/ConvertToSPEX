#pragma once
#include "afxwin.h"

#include "ConvertToSPEXDoc.h"
#include "DrawGraph.h"


// CParametersForm form view

class CParametersForm : public CFormView
{
	DECLARE_DYNCREATE(CParametersForm)

protected:
	CParametersForm();           // protected constructor used by dynamic creation
	virtual ~CParametersForm();

public:
	enum { IDD = IDD_FORMVIEW1 };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit c_EditCF;
	CEdit c_EditSW;

	afx_msg void OnEnKillfocusEditCf();
	CConvertToSPEXDoc* GetMyDocument() const;
	afx_msg void OnEnKillfocusEditSw();
protected:
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	CDrawGraph c_DrawArea;
};


