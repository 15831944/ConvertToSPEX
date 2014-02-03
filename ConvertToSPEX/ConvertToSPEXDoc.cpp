// ConvertToSPEXDoc.cpp : implementation of the CConvertToSPEXDoc class
//

#include "stdafx.h"
#include "ConvertToSPEX.h"

#include "ConvertToSPEXDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MY_MAX(x,y) ((x)>(y)?(x):(y))
#define MY_MIN(x,y) ((x)<(y)?(x):(y))

#include <cmath>
using std::fabs;
using std::ceil;
using std::log10;

// CConvertToSPEXDoc

IMPLEMENT_DYNCREATE(CConvertToSPEXDoc, CDocument)

BEGIN_MESSAGE_MAP(CConvertToSPEXDoc, CDocument)
//	ON_COMMAND(ID_FILE_OPEN, &CConvertToSPEXDoc::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CConvertToSPEXDoc::OnFileSave)
END_MESSAGE_MAP()


// CConvertToSPEXDoc construction/destruction

CConvertToSPEXDoc::CConvertToSPEXDoc()
{

	Reset();
}

CConvertToSPEXDoc::~CConvertToSPEXDoc()
{
}

BOOL CConvertToSPEXDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CConvertToSPEXDoc serialization

void CConvertToSPEXDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CConvertToSPEXDoc diagnostics

#ifdef _DEBUG
void CConvertToSPEXDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CConvertToSPEXDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CConvertToSPEXDoc commands

void CConvertToSPEXDoc::OnFileOpen()
{
	char strFilter[] = { "Bruker files (*.par)|*.par|All Files (*.*)|*.*||" };

  CFileDialog dlg(
		TRUE,			  // BOOL bOpenFileDialog, 
		NULL,       // LPCTSTR lpszDefExt = NULL, 
		NULL,		  	// LPCTSTR lpszFileName = NULL, 
		OFN_FILEMUSTEXIST | OFN_EXPLORER,
		strFilter
		);

  if(IDCANCEL==dlg.DoModal())
    return;

	CString s = dlg.GetPathName();

	lastFilenameOpened = dlg.GetFileName();

	ReadPar(s);

	UpdateAllViews(NULL);

}

void CConvertToSPEXDoc::Reset()
{
	dMA = -1;  
	dMF = 100;
	nPH = 0;
	dTC = -1;
	dRG = -1;
	nOF = 0;
	dCF = -1;  
	dSW = -1;  
	dTM = -1;  
	dDL = -1;  
	dFQ = 9.8;  
	dPW = 1.0;  
	nDA = 1024;  
	nSN = 1;  
	nTE = 300;  
	nPC = -1;  
	dMC = -1;  
	fmin = 0;
	fmax = 0;
	npages = 1;

	cstrUserName = "Default";
  cstrComment  = "Converted from Bruker file";
}


BOOL CConvertToSPEXDoc::ReadPar(CString &parPath)
{

  CString spcPath = parPath.Left(parPath.GetLength()-3)+_T("SPC");
  CString cstrMsg;

  // for reading

	Reset();
	fpdata.clear();

  char buff1[1024];
  char buff2[1024];
  float fVal = 0;
  int   nVal = 0;
  

  // read parameters from Bruker parameter file
  FILE *fp = fopen((LPCTSTR)parPath,"rt");
  if(fp == NULL)
  {
    cstrMsg=_T("Can not open the file: \r\n");
    cstrMsg+=parPath;
    AfxMessageBox((LPCTSTR)cstrMsg);
    return FALSE;
  }

  int len = 1; 
  int count = 0;

  len = fscanf(fp,"%s\t",buff1);
  while(len != EOF)
  {
    if(strcmp(buff1,"DOS") == 0)
      fscanf(fp,"%s\n",buff2);
    else if(strcmp(buff1,"ANZ") == 0)
      fscanf(fp,"%d\n",&nDA);
    else if(strcmp(buff1,"MIN") == 0)
      fscanf(fp,"%f\n",&fmin);
    else if(strcmp(buff1,"MAX") == 0)
      fscanf(fp,"%f\n",&fmax);
    else if(strcmp(buff1,"JSS") == 0)
      fscanf(fp,"%d\n", &nVal);
    else if(strcmp(buff1,"SSX") == 0)
      fscanf(fp,"%d\n",&nVal);
    else if(strcmp(buff1,"SSY") == 0)
    {
      fscanf(fp,"%d\n",&npages);
      nDA = nDA/npages;
    }
    else if(strcmp(buff1,"XXLB") == 0)
    {
      fscanf(fp,"%f\n",&fVal);
      dCF = fVal;
    }
    else if(strcmp(buff1,"XXWI") == 0)
    {
      fscanf(fp,"%f\n", &fVal);
      dSW = fVal;
      dCF = dCF - dSW/2;
    }
    else if(strcmp(buff1,"XYLB") == 0)
      fscanf(fp,"%f\n",&fVal);
    else if(strcmp(buff1,"XYWI") == 0)
      fscanf(fp,"%f\n",&fVal);
    else if(strcmp(buff1,"XXUN") == 0)
      fscanf(fp,"%s\n",buff2);
    else if(strcmp(buff1,"XYUN") == 0)
      buff2[0] = 0;

    else if(strcmp(buff1,"GST") == 0)
      fscanf(fp,"%f\n", &fVal);
    else if(strcmp(buff1,"GSI") == 0)
      fscanf(fp,"%f\n", &fVal);
    else if(strcmp(buff1,"JUN") == 0)
      fscanf(fp,"%s\n",buff2);
    else if(strcmp(buff1,"JON") == 0)
    {
      int ch;
      cstrUserName.Empty();
      ch = fgetc(fp);
      while(ch!='\n' && ch!= '\r' && ch!= EOF)
      {
        cstrUserName.Insert(cstrComment.GetLength(),(char)ch);
        ch = fgetc(fp);
      }
    }
    else if(strcmp(buff1,"JCO") == 0)
    {
      int ch;
      cstrComment.Empty();
      ch = fgetc(fp);
      while(ch!='\n' && ch!= '\r' && ch!= EOF)
      {
        cstrComment.Insert(cstrComment.GetLength(),(char)ch);
        ch = fgetc(fp);
      }
    }
    else if(strcmp(buff1,"JDA") == 0)
    {
      fscanf(fp,"%s\n",buff2);
      cstrDateTime = buff2;
      cstrDateTime.Replace('/','-');
    }
    else if(strcmp(buff1,"JTM") == 0)
    {
      fscanf(fp,"%s\n",buff2);
      cstrDateTime = cstrDateTime + _T(" ") + buff2 + _T(":00");
    }
    else if(strcmp(buff1,"JRE") == 0)
    {
      int ch;
      int i=0;
      CString cstr;
      ch = fgetc(fp);
      while(ch!='\n' && ch!= '\r' && ch!= EOF)
      {      
        buff2[i] = (char)ch;
        ch = fgetc(fp);
        i++;
        i=(i>1022)?1022:i;
      }
      buff2[i] = 0;

    }
    else if(strcmp(buff1,"JEX") == 0)
      fscanf(fp,"%s\n",buff2);

    else if(strcmp(buff1,"JEY") == 0)
      fscanf(fp,"%s\n",buff2);

    else if(strcmp(buff1,"REY") == 0)
      fscanf(fp,"%d\n",&nVal);

		else if(strcmp(buff1,"RES") == 0)
      fscanf(fp,"%d\n",&nVal);

    else if(strcmp(buff1,"JNS") == 0)
      fscanf(fp,"%d\n",&nSN);
    else if(strcmp(buff1,"JSD") == 0)
      fscanf(fp,"%d\n",&nVal);
    else if(strcmp(buff1,"HCF") == 0)
    {
      fscanf(fp,"%f\n", &fVal);
      dCF = fVal;
    }
    else if(strcmp(buff1,"HSW") == 0)
    {
      fscanf(fp,"%f\n", &fVal);
      dSW = fVal;
    }
    else if(strcmp(buff1,"EMF") == 0)
      fscanf(fp,"%f\n",&fVal);
    else if(strcmp(buff1,"RCT") == 0)
    {
      fscanf(fp,"%f\n", &fVal);
      dTM = nDA * fVal/1000;
    }
    else if(strcmp(buff1,"RTC") == 0)
    {
      fscanf(fp,"%f\n", &fVal);
      dTC = fVal/1000;
    }
    else if(strcmp(buff1,"RRG") == 0)
    {
      fscanf(fp,"%f\n", &fVal);
      dRG = fVal;
    }
    else if(strcmp(buff1,"RMA") == 0)
    {
      len = fscanf(fp,"%f\n", &fVal);
      dMA = fVal;
    }
    else if(strcmp(buff1,"MF") == 0)
    {
      fscanf(fp,"%f\n", &fVal);
      dFQ = fVal;
    }
    else if(strcmp(buff1,"MP") == 0)
    {
      len = fscanf(fp,"%f\n", &fVal);
      dPW = fVal;
    }
    else
    {
      //fclose(fp);

			fscanf(fp,"%s\n",buff2);
			CString temp;
			temp.Format("Unknown parameter found: %s %s",buff1,buff2);
      AfxMessageBox(temp);

      //return FALSE;
    }    
    len = fscanf(fp,"%s\t",buff1);
  }
    
  fclose(fp);

	  // read spectral data from *.spc file
  fp = fopen((LPCTSTR)spcPath,"rb");
  if(fp == NULL)
  {
    cstrMsg=_T("Can not open the file: \r\n");
    cstrMsg+=spcPath;
    AfxMessageBox((LPCTSTR)cstrMsg);
    return FALSE;
  }

  fpdata.resize(npages*nDA);
  
  fread(&fpdata[0],sizeof(float),npages*nDA,fp);
  fclose(fp);


	return TRUE;
}

BOOL CConvertToSPEXDoc::WriteSpx(CString &spxPath)
{
  // write a spx file

  // for writing 
  short myint16;
  float ftemp;
  int   ntemp;
  CFile SpexFile;

  char buff[1024];
  
  CString cstrT, cstrMsg;
  int nY,nM,nD,nh,nm,ns;

  cstrT = cstrDateTime.Mid(0,2);
  nM = atoi((LPCTSTR)cstrT);
  cstrT = cstrDateTime.Mid(3,2);
  nD = atoi((LPCTSTR)cstrT);
  cstrT = cstrDateTime.Mid(6,4);
  nY = atoi((LPCTSTR)cstrT);

	cstrT = cstrDateTime.Mid(11,2);
	nh = atoi((LPCTSTR)cstrT);
	cstrT = cstrDateTime.Mid(14,2);
	nm = atoi((LPCTSTR)cstrT);
	cstrT = cstrDateTime.Mid(17,2);
	ns = atoi((LPCTSTR)cstrT);

	COleDateTime startTime(nY,nM,nD,nh,nm,ns);


	if(NULL==SpexFile.Open((LPCTSTR)spxPath,CFile::modeCreate|CFile::modeWrite| CFile::typeBinary))
	{
		cstrMsg=_T("Can not create file:\r\n");
		cstrMsg=cstrMsg+spxPath;
		AfxMessageBox((LPCTSTR)cstrMsg);
		return FALSE;
	}

	FillMemory(buff,1024,0);
	SpexFile.Write(buff,444);
	//skip id
	SpexFile.Seek(64,CFile::begin);
	//write comments;
	SpexFile.Write((LPCTSTR)cstrComment,MY_MIN(64,cstrComment.GetLength()));
	//skip fl,dr
	SpexFile.Seek(176,CFile::begin);
	//write operator
	SpexFile.Write((LPCTSTR)cstrUserName,MY_MIN(16,cstrUserName.GetLength()));
	SpexFile.Seek(192,CFile::begin);
	//data length
	myint16=nDA;  
	SpexFile.Write(&myint16,sizeof(WORD));
	//scan num
	myint16=nSN;
	SpexFile.Write(&myint16,sizeof(WORD));
	//CF
	ftemp=(float)dCF;
	SpexFile.Write(&ftemp,sizeof(float));
	//SW
	ftemp=(float)dSW;
	SpexFile.Write(&ftemp,sizeof(float));
	//TM
	ftemp=(float)dTM;
	SpexFile.Write(&ftemp,sizeof(float));
	//FQ  
	ftemp=(float)dFQ;
	SpexFile.Write(&ftemp,sizeof(float));
	//RG
	ftemp=(float)dRG;
	SpexFile.Write(&ftemp,sizeof(float));
	//MA
	ftemp=(float)dMA;
	SpexFile.Write(&ftemp,sizeof(float));
	//MF
	ftemp=(float)dMF;
	SpexFile.Write(&ftemp,sizeof(float));
	//PW
	ftemp=(float)dPW;
	SpexFile.Write(&ftemp,sizeof(float));
	//TC
	ftemp=(float)dTC;
	SpexFile.Write(&ftemp,sizeof(float));
	//PH
	myint16=nPH;
	SpexFile.Write(&myint16,sizeof(WORD));
	//OF
	myint16=nOF;
	SpexFile.Write(&myint16,sizeof(WORD));
	//TE
	ftemp=(float)nTE;
	SpexFile.Write(&ftemp,sizeof(float));


	int np=0;
	COleDateTimeSpan pastTime(0L,0,0, (int)(dTM*np+0.5));
	COleDateTime curTime = startTime + pastTime;

	cstrDateTime.Format(_T("%02d-%02d-%04d %02d:%02d:%02d"),
		curTime.GetMonth(), curTime.GetDay(),
		curTime.GetYear (), curTime.GetHour(),
		curTime.GetMinute(),curTime.GetSecond());

	//DATE
	SpexFile.Write((LPCTSTR)cstrDateTime.Left(10),10);             //DATE
	//TIME
	SpexFile.Seek(6,CFile::current);
	SpexFile.Write((LPCTSTR)cstrDateTime.Right(8),8);             //DATE
	SpexFile.Seek(444,CFile::begin);

	for(int i=np*nDA;i<(np+1)*nDA;i++)
	{
		if(fpdata[i]>0)
			ntemp=(int)(fpdata[i]+0.5);
		else
			ntemp=(int)(fpdata[i]-0.5);
		SpexFile.Write(&ntemp,sizeof(int));
	}

	ntemp=int(MY_MAX(fmax,fabs(fmin))+0.5);
	ntemp=(int)((ceil)(log10((double)ntemp)/log10(2.0)));

	SpexFile.Seek(434,CFile::begin);
	SpexFile.Write(&ntemp,sizeof(int));

	SpexFile.Close();


  return TRUE;
};

void CConvertToSPEXDoc::OnFileSave()
{
	char strFilter[] = { "SPEX files (*.spx)|*.spx|All Files (*.*)|*.*||" };

	CString suggestedFilename;

	if(!lastFilenameOpened.IsEmpty())
		suggestedFilename = lastFilenameOpened.Left(lastFilenameOpened.GetLength()-4) + _T(".spx");

  CFileDialog dlg(
		FALSE,			  // BOOL bOpenFileDialog, 
		NULL,       // LPCTSTR lpszDefExt = NULL, 
		suggestedFilename,		  	// LPCTSTR lpszFileName = NULL, 
		OFN_OVERWRITEPROMPT | OFN_EXPLORER,
		strFilter
		);

  if(IDCANCEL==dlg.DoModal())
    return;

	CString s = dlg.GetPathName();

	WriteSpx(s);

	UpdateAllViews(NULL);
}

BOOL CConvertToSPEXDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// automatically open and convert the file
	lastFilenameOpened = lpszPathName;
	if (!ReadPar(lastFilenameOpened))
		return FALSE;

	CString suggestedFilename = lastFilenameOpened.Left(lastFilenameOpened.GetLength()-4) + _T(".spx");

	if (!WriteSpx(suggestedFilename))
		return FALSE;

	CString msg;
	msg.Format("Successfully converted %s to %s.", lastFilenameOpened, suggestedFilename);
	AfxMessageBox(msg);

	return TRUE;
}
