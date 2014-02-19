
// MDFMDIAppDoc.cpp : implementation of the CHomeHealthDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "HomeHealthApp.h"
#endif

#include "HomeHealthSet.h"
#include "HomeHealthDoc.h"

#include <propkey.h>

#include "PatientSearchDlg.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CHomeHealthDoc

IMPLEMENT_DYNCREATE(CHomeHealthDoc, CDocument)

BEGIN_MESSAGE_MAP(CHomeHealthDoc, CDocument)
//	ON_COMMAND(ID_FILE_SAVE, &CHomeHealthDoc::OnFileSave)
END_MESSAGE_MAP()


// CHomeHealthDoc construction/destruction

CHomeHealthDoc::CHomeHealthDoc()
{
	// TODO: add one-time construction code here

}
CHomeHealthDoc::CHomeHealthDoc(int patient_id)
{
	m_nPatientId = patient_id;
}

CHomeHealthDoc::~CHomeHealthDoc()
{
}

BOOL CHomeHealthDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
#if 0
	CHomeHealthApp *pApp = CHomeHealthApp *)AfxGetApp();
	if(pApp->m_nSelectedPatient == -1)
	{
		SetTitle(_T("New Patient"));
	}
	else
	{
		CString strTitle; 
		strTitle.Format(_T("Patient id %d"),pApp->m_nSelectedPatient);
		SetTitle(strTitle);
	}

	return TRUE;
#endif
	return TRUE;
}




// CHomeHealthDoc serialization

void CHomeHealthDoc::Serialize(CArchive& ar)
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

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CHomeHealthDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CHomeHealthDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CHomeHealthDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CHomeHealthDoc diagnostics

#ifdef _DEBUG
void CHomeHealthDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHomeHealthDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CHomeHealthDoc commands


void CHomeHealthDoc::OnCloseDocument()
{
	// TODO: Add your specialized code here and/or call the base class

	CDocument::OnCloseDocument();
}



//void CHomeHealthDoc::OnFileSave()
//{
//	// TODO: Add your command handler code here
//}
