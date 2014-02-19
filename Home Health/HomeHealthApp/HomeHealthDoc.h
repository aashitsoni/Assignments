
// MDFMDIAppDoc.h : interface of the CHomeHealthDoc class
//


#pragma once
#include "HomeHealthSet.h"


class CHomeHealthDoc : public CDocument
{
protected: // create from serialization only
	CHomeHealthDoc();
	CHomeHealthDoc(int);
	DECLARE_DYNCREATE(CHomeHealthDoc)

// Attributes
public:
	CHomeHealthSet m_MDFMDIAppSet;

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CHomeHealthDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	int m_nPatientId;
//	afx_msg void OnFileOpen();
	virtual void OnCloseDocument();
//	afx_msg void OnFileNew();
//	afx_msg void OnFileSave();
};
