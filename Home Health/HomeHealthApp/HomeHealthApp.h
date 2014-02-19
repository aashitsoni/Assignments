
// MDFMDIApp.h : main header file for the MDFMDIApp application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include "HomeHealthDatabase.h"


// CHomeHealthApp:
// See MDFMDIApp.cpp for the implementation of this class
//

class CHomeHealthApp : public CWinAppEx
{
public:
	CHomeHealthApp();

	CHomeHealthDatabase healthDB;
	CMultiDocTemplate* m_pDocTemplate;
	long			m_nSelectedPatient;
	SYSTEMTIME		m_localTime;
	TCHAR			m_appCWD[256];

	CView*			m_pBillingView;
	CView*			m_pEditingView;
	CView*			m_pActiveView;

          
// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();
	CHomeHealthDatabase* GetHomeHealthDatabase();
	CView*	SwitchView();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnFileOpen();
	afx_msg void OnFileNew();
//	afx_msg void OnFileSave();
	afx_msg void OnReportsBilling30minutes();
	afx_msg void OnReportsToday();
	afx_msg void OnReportsPatientledger();
	afx_msg void OnViewSwitch();
	afx_msg void OnViewSwitch2();
};

extern CHomeHealthApp theApp;
