
// MDFMDIApp.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "afxpriv.h"

#include "HomeHealthApp.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "HomeHealthSet.h"
#include "HomeHealthDoc.h"
#include "HomeHealthView.h"
#include "PatientSearchDlg.h"
#include "AddPatientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHomeHealthApp

BEGIN_MESSAGE_MAP(CHomeHealthApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CHomeHealthApp::OnAppAbout)
	// Standard file based document commands
//	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
//	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
	ON_COMMAND(ID_FILE_OPEN, &CHomeHealthApp::OnFileOpen)
	ON_COMMAND(ID_FILE_NEW, &CHomeHealthApp::OnFileNew)
//	ON_COMMAND(ID_FILE_SAVE, &CHomeHealthApp::OnFileSave)
ON_COMMAND(ID_REPORTS_BILLING30MINUTES, &CHomeHealthApp::OnReportsBilling30minutes)
ON_COMMAND(ID_REPORTS_TODAY, &CHomeHealthApp::OnReportsToday)
ON_COMMAND(ID_REPORTS_PATIENTLEDGER, &CHomeHealthApp::OnReportsPatientledger)
ON_COMMAND(ID_VIEW_SWITCH, &CHomeHealthApp::OnViewSwitch)
ON_COMMAND(ID_VIEW_SWITCH32796, &CHomeHealthApp::OnViewSwitch2)
END_MESSAGE_MAP()


// CHomeHealthApp construction

CHomeHealthApp::CHomeHealthApp()
{
	m_bHiColorIcons = TRUE;

	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// If the application is built using Common Language Runtime support (/clr):
	//     1) This additional setting is needed for Restart Manager support to work properly.
	//     2) In your project, you must add a reference to System.Windows.Forms in order to build.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("MDFMDIApp.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CHomeHealthApp object

CHomeHealthApp theApp;


// CHomeHealthApp initialization

BOOL CHomeHealthApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction();

	// AfxInitRichEdit2() is required to use RichEdit control	
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Home Health Applicaiton"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	m_pDocTemplate = new CMultiDocTemplate(IDR_MDFMDIAppTYPE,
		RUNTIME_CLASS(CHomeHealthDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CHomeHealthView));
	if (!m_pDocTemplate)
		return FALSE;
	AddDocTemplate(m_pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;

	m_nSelectedPatient = -1;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	// Dont process any command line info
#if 0
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
#endif


	CDocument* pCurrentDoc = ((CFrameWnd*)m_pMainWnd)->GetActiveDocument();

	// Initialize a CCreateContext to point to the active document. 
	// With this context, the new view is added to the document 
	// when the view is created in CView::OnCreate().
	CCreateContext newContext;
	newContext.m_pNewViewClass = NULL;
	newContext.m_pNewDocTemplate = NULL;
	newContext.m_pLastView = NULL;
	newContext.m_pCurrentFrame = NULL;
	newContext.m_pCurrentDoc = pCurrentDoc;

	// The ID of the initial active view is AFX_IDW_PANE_FIRST. 
	// Incrementing this value by one for additional views works 
	// in the standard document/view case but the technique cannot 
	// be extended for the CSplitterWnd case.
	UINT viewID = AFX_IDW_PANE_FIRST + 1;
	CRect rect(0, 0, 0, 0); // Gets resized later. 


	healthDB.Init();
	if(-1 == healthDB.Open())
	{
		AfxMessageBox(L"Database connection Issue",MB_OK);
		// exit the application
		return FALSE;

	}

	GetLocalTime(&m_localTime);

	_tgetcwd(m_appCWD,256);
//	AfxMessageBox(cur_dir);

	// The main window has been initialized, so show and update it
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();
	
	AfxMessageBox(m_appCWD);

	return TRUE;
}


CView* CHomeHealthApp::SwitchView( )
{
   CView* pActiveView = ((CFrameWnd*) m_pMainWnd)->GetActiveView();

   CView* pNewView = NULL;
   if(pActiveView == m_pBillingView)
      m_pActiveView = m_pEditingView;
   else
      m_pActiveView = m_pBillingView;

   if(pActiveView == 0)
   {
	   m_pActiveView = pActiveView = m_pBillingView;
	   
   }
   // Exchange view window IDs so RecalcLayout() works.
   #ifndef _WIN32
   UINT temp = ::GetWindowWord(pActiveView->m_hWnd, GWW_ID);
   ::SetWindowWord(pActiveView->m_hWnd, GWW_ID, ::GetWindowWord(pNewView->m_hWnd, GWW_ID));
   ::SetWindowWord(pNewView->m_hWnd, GWW_ID, temp);
   #else
   UINT temp = ::GetWindowLong(pActiveView->m_hWnd, GWL_ID);

   ::SetWindowLong(pActiveView->m_hWnd, GWL_ID, ::GetWindowLong(m_pActiveView->m_hWnd, GWL_ID));
   ::SetWindowLong(m_pActiveView->m_hWnd, GWL_ID, temp);
   #endif

   pActiveView->ShowWindow(SW_HIDE);
   m_pActiveView->ShowWindow(SW_SHOW);
   ((CFrameWnd*) m_pMainWnd)->SetActiveView(m_pActiveView);
   ((CFrameWnd*) m_pMainWnd)->RecalcLayout();
   m_pActiveView->Invalidate();
   return pActiveView;
} 


int CHomeHealthApp::ExitInstance()
{
	healthDB.Close();

	//TODO: handle additional resources you may have added
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CHomeHealthApp message handlers


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnReportsPatientledger();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_COMMAND(ID_REPORTS_PATIENTLEDGER, &CAboutDlg::OnReportsPatientledger)
END_MESSAGE_MAP()

// App command to run the dialog
void CHomeHealthApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CHomeHealthApp customization load/save methods

void CHomeHealthApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CHomeHealthApp::LoadCustomState()
{
}

void CHomeHealthApp::SaveCustomState()
{
}

// CHomeHealthApp message handlers

CHomeHealthDatabase* CHomeHealthApp::GetHomeHealthDatabase()
{
	return &healthDB;
}


// CHomeHealthApp message handlers File Open
void CHomeHealthApp::OnFileOpen()
{
	// TODO: Add your command handler code here
	CPatientSearchDlg patientSearchDlg;

	if(IDOK == patientSearchDlg.DoModal())
	{
		m_nSelectedPatient = patientSearchDlg.m_nSelectedPatientId;
		m_pDocTemplate->OpenDocumentFile(NULL);
	}
	else
	{
	}

}


// Message handler for new file
void CHomeHealthApp::OnFileNew()
{
	m_nSelectedPatient = -1; // set this to invalid ID,

	// open a dialog box. that accepts new patient, 
#if 0
	CAddPatientDlg newPatientDlg;
	if(IDOK == newPatientDlg.DoModal())
	{
		m_nSelectedPatient = newPatientDlg.m_newPatientId;
		m_pDocTemplate->OpenDocumentFile(NULL);

	}
#endif
	// Once we created a new patient, open up his view to set up the episode and oversight billing 

		CWinAppEx::OnFileNew();
	// TODO: Add your command handler code here
}


//void CHomeHealthApp::OnFileSave()
//{
//	// TODO: Add your command handler code here
//}


void CHomeHealthApp::OnReportsBilling30minutes()
{
	// TODO: Add your command handler code here
}



void CHomeHealthApp::OnReportsToday()
{
	// TODO: Add your command handler code here
}


void CHomeHealthApp::OnReportsPatientledger()
{
	// TODO: Add your command handler code here
}


void CHomeHealthApp::OnViewSwitch()
{

	this->SwitchView();
	// TODO: Add your command handler code here
}


void CHomeHealthApp::OnViewSwitch2()
{
	this->SwitchView();
	// TODO: Add your command handler code here
}
