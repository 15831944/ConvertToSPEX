#pragma once
#include "ConvertToSPEXDoc.h"


// CDrawGraph

class CDrawGraph : public CWnd
{
	DECLARE_DYNAMIC(CDrawGraph)

public:
	CDrawGraph();
	virtual ~CDrawGraph();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	CConvertToSPEXDoc* GetMyDocument() const;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


