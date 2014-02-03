// ConvertToSPEXDoc.h : interface of the CConvertToSPEXDoc class
//


#pragma once

#include <vector>
using std::vector;


class CConvertToSPEXDoc : public CDocument
{
protected: // create from serialization only
	CConvertToSPEXDoc();
	DECLARE_DYNCREATE(CConvertToSPEXDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CConvertToSPEXDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

  double dMA;  //Modulation amplitute in units of gauss
  double dMF;
  int    nPH;
  double dTC;
  double dRG;
  int    nOF;
  double dCF;  //Center Field in Gauss
  double dSW;  //SWeep width in units of Gauss
  double dTM;  //sweep TiMe in seconds  
  double dDL;  //delay time in second, =0,0.1,0.2,...
  double dFQ;  //microwave frequency;
  double dPW;  //microwave power;
  int    nDA;  //data length=1024,2048 or 4096
  int    nSN;  //scan number, any integer greater than 0
  int    nTE;  //temperature
  int    nPC;  //Phase Calibration scale;
  double dMC;  //Modulation amplitude Calibration scale in float form
  float fmin;
  float fmax;
	int npages;
	CString cstrUserName;
  CString cstrComment;
  CString cstrDateTime;

	CString lastFilenameOpened;

	vector<float> fpdata;

	BOOL ReadPar(CString &parPath);
	BOOL WriteSpx(CString &spxPath);
	void Reset();

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
};


