
// MDFMDIAppView.cpp : implementation of the CHomeHealthView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#include "HomeHealthSet.h"
#include "HomeHealthDoc.h"
#include "patient_billing.h"
#include "patient_master.h"
#include "patient_episode.h"
#include "patient_billing.h"
#include "oversight_billing.h"
#include "oversightRecordDlg.h"
#include "EpisodeDlg.h"
#include "InitialBillingDlg.h"
#include "OversightBillingDlg.h"
#include "HomeHealthView.h"

#ifndef SHARED_HANDLERS
#include "HomeHealthApp.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHomeHealthView

IMPLEMENT_DYNCREATE(CHomeHealthView, CRecordView)

BEGIN_MESSAGE_MAP(CHomeHealthView, CRecordView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CHomeHealthView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_NOTIFY(NM_DBLCLK, IDC_PATIENT_EPISODE, &CHomeHealthView::OnNMDblclkPatientEpisode)
	ON_WM_CREATE()
	ON_NOTIFY(NM_CLICK, IDC_PATIENT_EPISODE, &CHomeHealthView::OnClickPatientEpisode)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_PATIENT_EPISODE, &CHomeHealthView::OnLvnItemchangedPatientEpisode)
	ON_NOTIFY(LVN_KEYDOWN, IDC_PATIENT_EPISODE, &CHomeHealthView::OnLvnKeydownPatientEpisode)
	ON_BN_CLICKED(IDC_BUTTON_ADD_OVERSIGHT, &CHomeHealthView::OnBnClickedButtonAddOversight)
	ON_BN_CLICKED(IDC_BUTTON_ADD_EPISODE, &CHomeHealthView::OnBnClickedButtonAddEpisode)
	ON_NOTIFY(NM_RCLICK, IDC_PATIENT_EPISODE, &CHomeHealthView::OnNMRClickPatientEpisode)
	ON_COMMAND(ID_EPISODE_EDIT, &CHomeHealthView::OnEpisodeEdit)
	ON_COMMAND(ID_EPISODE_DELETE, &CHomeHealthView::OnEpisodeDelete)
	ON_COMMAND(ID_FILE_SAVE, &CHomeHealthView::OnFileSave)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_OVERSIGHT, &CHomeHealthView::OnRclickListOversight)
	ON_COMMAND(ID_EPISODE_ADD, &CHomeHealthView::OnEpisodeAdd)
	ON_COMMAND(ID_OVERSIGHT_ADD, &CHomeHealthView::OnOversightAdd)
	ON_COMMAND(ID_REPORTS_PATIENTLEDGER, &CHomeHealthView::OnReportsPatientledger)
	ON_COMMAND(ID_EPISODE_ADDOVERSIGHT, &CHomeHealthView::OnEpisodeAddoversight)
	ON_BN_CLICKED(IDC_BUTTONBill, &CHomeHealthView::OnBnClickedButtonbill)
	ON_COMMAND(ID_PRINTED_BILL,&CHomeHealthView::OnCompletePrintingBill)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_PATIENT_LAST_VISIT, &CHomeHealthView::OnDtnDatetimechangePatientLastVisit)
	ON_COMMAND(ID_OVERSIGHT_EDIT, &CHomeHealthView::OnOversightEdit)
	ON_COMMAND(ID_OVERSIGHT_DELETE, &CHomeHealthView::OnOversightDelete)
END_MESSAGE_MAP()

// CHomeHealthView construction/destruction

CHomeHealthView::CHomeHealthView()
	: CRecordView(CHomeHealthView::IDD)
	, m_szPatientID(_T(""))
	, m_szPatientAddress(_T(""))
	, m_szPatientTown(_T(""))
	, m_szPatientName(_T(""))
	, m_szTotalMinutes(_T(""))
	//, m_szCountry(_T(""))
	, m_szApartment(_T(""))
	, m_szMiddleName(_T(""))
	, m_szFirstName(_T(""))
	, m_datePatientLastBill(COleDateTime::GetCurrentTime())
	, m_datePatientRegistration(COleDateTime::GetCurrentTime())
	, m_datePatientLastVisit(COleDateTime::GetCurrentTime())
	, m_szCellPhone(_T(""))
	, m_szHomePhone(_T(""))
	, m_szWorkPhone(_T(""))
	, m_szPatientZip(_T(""))
	, m_PatientDOB(1977,1,1,1,1,1)
	, homehealth_printmode(homehealth_print_none)
{
	CHomeHealthApp*pApp = (CHomeHealthApp*)AfxGetApp();
	CHomeHealthDatabase* pDB = pApp->GetHomeHealthDatabase();

	m_pSet = NULL;
	m_patient_id = -1;
	m_patient_billing_status = EPISODE_BILLING_STATUS_NA;
	cpo_master = new Coversight_cpo_code_master(pDB->GetDatabase());
	m_ActivePatient = NULL;
	m_activePatientEpisode = NULL;
	cpo_master->Open();
	m_dbOpened = FALSE;

}

CHomeHealthView::~CHomeHealthView()
{
	if(m_ActivePatient)
	{
		m_ActivePatient->Close();
		delete m_ActivePatient;
	}
	if(m_activePatientEpisode)
	{
		m_activePatientEpisode->Close();
		delete m_activePatientEpisode;
	}
	if(m_activeBilling)
	{
		m_activeBilling->Close();
		delete m_activeBilling;
	}

	cpo_master->Close();
	delete cpo_master;
}

void CHomeHealthView::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);
	// you can insert DDX_Field* functions here to 'connect' your controls to the database fields, ex.
	// See MSDN and ODBC samples for more information
	DDX_Control(pDX, IDC_PATIENT_EPISODE, m_episodeListCtrl);
	DDX_Control(pDX, IDC_LIST_OVERSIGHT, m_OverSightListCtrl);
	DDX_Text(pDX, IDC_EDIT_PATIENT_ID, m_szPatientID);
	DDX_Text(pDX, IDC_EDIT_PATIENT_ADDR, m_szPatientAddress);
	DDX_Text(pDX, IDC_EDIT_PATIENT_TOWN, m_szPatientTown);
	DDX_Text(pDX, IDC_EDIT_PATIENT_LASTNAME, m_szPatientName);
	DDX_Text(pDX, IDC_EDIT_TOTAL_MINS, m_szTotalMinutes);
	DDX_Control(pDX, IDC_COMBO_TITLE, m_comboTitle);
	DDX_Control(pDX, IDC_COMBO_STATE, m_comboState);
	DDX_Text(pDX, IDC_EDIT_APARTMENT, m_szApartment);
	DDX_Text(pDX, IDC_EDIT_PAT_MIDDLE_NAME, m_szMiddleName);
	DDX_Text(pDX, IDC_PATIENT_FIRST_NAME, m_szFirstName);
	DDX_DateTimeCtrl(pDX, IDC_PATIENT_LAST_BILL, m_datePatientLastBill);
	DDX_DateTimeCtrl(pDX, IDC_PATIENT_LAST_VISIT, m_datePatientLastVisit);
	DDX_DateTimeCtrl(pDX, IDC_PATIENT_REGISTRATION, m_datePatientRegistration);
	DDX_Text(pDX, IDC_EDIT_CELL_PHONE, m_szCellPhone);
	DDX_Text(pDX, IDC_EDIT_HOME_PHONE, m_szHomePhone);
	DDX_Text(pDX, IDC_EDIT_WORK_PHONE, m_szWorkPhone);
	DDX_Text(pDX, IDC_PATIENT_ZIP, m_szPatientZip);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPATIENTDOB, m_PatientDOB);
	DDX_Control(pDX, IDC_BUTTON_BILL_CONTROL, m_btnBillIndicator);
	DDX_Control(pDX, IDC_BILL_LIST, m_listEpisodeBill);
	DDX_Control(pDX, IDC_COMBO_SEX, m_comboSex);
}

BOOL CHomeHealthView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRecordView::PreCreateWindow(cs);
}


// temporory function may not need later on.
BOOL CHomeHealthView::AdjustPatientBillableMinutes(int billableMinutes)
{
	Cpatient_master patient(m_pHealthDB->GetDatabase());
	if(0 == patient.OpenForModify(m_patient_id))
	{
		if(patient.m_patient_billable_minutes != billableMinutes)
		{
			patient.Edit();
			patient.m_patient_billable_minutes = billableMinutes;
			patient.Update();
			m_szTotalMinutes.Format(_T("%d"),patient.m_patient_billable_minutes);
		}
		patient.Close();
	}
	return TRUE;
}


BOOL CHomeHealthView::CreateEpisodeControlColumns()
{
	CRect rect;
	m_episodeListCtrl.GetClientRect(&rect);
	int nColInterval = rect.Width()/7;

	m_episodeListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);

	m_episodeListCtrl.InsertColumn(0,_T("Id"),LVCFMT_LEFT,nColInterval);
	m_episodeListCtrl.InsertColumn(1,_T("Type"),LVCFMT_LEFT,nColInterval);
	m_episodeListCtrl.InsertColumn(2,_T("Start"),LVCFMT_LEFT,nColInterval);
	m_episodeListCtrl.InsertColumn(3,_T("End"),LVCFMT_LEFT,nColInterval);
	m_episodeListCtrl.InsertColumn(4,_T("IsActive"),LVCFMT_LEFT,nColInterval);
	m_episodeListCtrl.InsertColumn(5,_T("Total Minutes"),LVCFMT_LEFT,nColInterval);
	m_episodeListCtrl.InsertColumn(6,_T("Dx codes"),LVCFMT_LEFT,nColInterval);

	return TRUE;

}



int CHomeHealthView::PopulateEpisodeControlData()
{
	Cpatient_episode episode(m_pHealthDB->GetDatabase());
	int nActiveItem  = 0;
	CHomeHealthApp *pApp = (CHomeHealthApp*) AfxGetApp();
	m_currentDate = CTime::GetCurrentTime();
	int item = 0;
	LVITEM lvitem;
	CString strItem;
	
 	m_episodeListCtrl.DeleteAllItems();

	if(m_activePatientEpisode->GetRecordCount() > 0)
	{
		m_activePatientEpisode->SetAbsolutePosition(1);

		while(m_activePatientEpisode->IsEOF() == FALSE)
		{
			lvitem.mask = LVIF_TEXT;
			strItem.Format(_T("%u"),m_activePatientEpisode->m_patient_episode_code);

			lvitem.iItem = item;
			lvitem.iSubItem = 0;
			lvitem.pszText = (LPTSTR)(LPCTSTR)(strItem);
			m_episodeListCtrl.InsertItem(&lvitem);
			m_episodeListCtrl.SetItemData(item,m_activePatientEpisode->m_patient_episode_code);

			strItem.Format(_T("%s"),m_activePatientEpisode->m_episode_type);
			lvitem.iSubItem = 1;
			lvitem.pszText= (LPTSTR)(LPCTSTR)(strItem);
			m_episodeListCtrl.SetItem(&lvitem);

			strItem.Format(_T("%d/%d/%d"),m_activePatientEpisode->m_episode_start_date.GetMonth(),m_activePatientEpisode->m_episode_start_date.GetDay(),m_activePatientEpisode->m_episode_start_date.GetYear());
			lvitem.iSubItem = 2;
			lvitem.pszText= (LPTSTR)(LPCTSTR)(strItem);
			m_episodeListCtrl.SetItem(&lvitem);



			strItem.Format(_T("%d/%d/%d"),m_activePatientEpisode->m_episode_end_date.GetMonth(),m_activePatientEpisode->m_episode_end_date.GetDay(),m_activePatientEpisode->m_episode_end_date.GetYear());
			lvitem.iSubItem = 3;
			lvitem.pszText= (LPTSTR)(LPCTSTR)(strItem);
			m_episodeListCtrl.SetItem(&lvitem);


			if(m_activePatientEpisode->m_episode_active == TRUE)
			{
				strItem.Format(_T("Active"));
				m_active_episode_id = m_activePatientEpisode->m_patient_episode_code;
				nActiveItem = item;
				m_patient_episode_end_date = m_activePatientEpisode->m_episode_end_date;
				m_patient_episode_start_date = m_activePatientEpisode->m_episode_start_date;
				m_patient_episode_id = m_activePatientEpisode->m_patient_episode_code;
				m_patient_billing_status = m_activePatientEpisode->m_episode_billing_status;
			}
			else
			{
				strItem.Format(_T("Inactive"));
				m_patient_episode_end_date		= 0;
				m_patient_episode_start_date	= 0;
			}

			lvitem.iSubItem = 4;
			lvitem.pszText= (LPTSTR)(LPCTSTR)(strItem);
			m_episodeListCtrl.SetItem(&lvitem);

			strItem.Format(_T("%d"),m_activePatientEpisode->m_episode_total_minutes);
			lvitem.iSubItem = 5;
			lvitem.pszText= (LPTSTR)(LPCTSTR)(strItem);
			m_episodeListCtrl.SetItem(&lvitem);

			
			CString szToken,szString;
			szString.Format(_T("%s"),m_activePatientEpisode->m_episode_dx_codes);
			strItem.Empty();
			if(szString.GetLength() > 0)
			{
				int curPos = 0;
				szToken = szString.Tokenize(_T("\r\n"),curPos);
				while(szToken !=_T(""))
				{
					strItem += szToken;
					strItem += _T(" ");
					szToken = szString.Tokenize(_T("\r\n"),curPos);
				}

			}
			lvitem.iSubItem = 6;
			lvitem.pszText= (LPTSTR)(LPCTSTR)(strItem);
			m_episodeListCtrl.SetItem(&lvitem);
			

			m_activePatientEpisode->MoveNext();
			item ++;

		}

		m_activePatientEpisode->SetAbsolutePosition(nActiveItem+1); // set the index on the record set to be acitve one
		m_episodeListCtrl.SetItemState(nActiveItem,LVIS_SELECTED,LVIS_SELECTED);
		m_episodeListCtrl.SetSelectionMark(nActiveItem);

		// Check if the status is oversight billing or not
		if(m_activePatientEpisode->m_episode_billing_status == EPISODE_BILLING_STATUS_NA)
		{
			if(m_activePatientEpisode->m_episode_total_minutes >= EPISODE_OVERSIGHT_BILLING_MINUTES)
			{
				CTimeSpan ts = m_currentDate - m_activePatientEpisode->m_episode_last_bill_date;
				if(ts.GetDays() >= EPISODE_BILLING_DAYS)
				{
					m_activePatientEpisode->Edit();
					m_activePatientEpisode->m_episode_billing_status = EPISODE_BILLING_STATUS_OVERSIGHT;
					m_patient_billing_status = EPISODE_BILLING_STATUS_OVERSIGHT;
					m_activePatientEpisode->Update();
				}
			}
		}

	// set up the bit map based on the status
	if(m_patient_billing_status == EPISODE_BILLING_STATUS_NA)
		{
		HBITMAP hBitmap = ::LoadBitmap(pApp->m_hInstance,MAKEINTRESOURCE(IDB_BITMAP_GREEN_SMALL));
		m_btnBillIndicator.SetBitmap(hBitmap);
		GetDlgItem(IDC_BUTTONBill)->EnableWindow(FALSE);
		}
	else 
		{
		HBITMAP hBitmap = ::LoadBitmap(pApp->m_hInstance,MAKEINTRESOURCE(IDB_BITMAP_RED_SMALL));
		m_btnBillIndicator.SetBitmap(hBitmap);
		GetDlgItem(IDC_BUTTONBill)->EnableWindow(TRUE);
		}


		return item;
	}
	else
	{
		// set up the bit map based on the status
		if(m_patient_billing_status == EPISODE_BILLING_STATUS_NA)
			{
			HBITMAP hBitmap = ::LoadBitmap(pApp->m_hInstance,MAKEINTRESOURCE(IDB_BITMAP_GREEN_SMALL));
			m_btnBillIndicator.SetBitmap(hBitmap);
			GetDlgItem(IDC_BUTTONBill)->EnableWindow(FALSE);
			}
		else 
			{
			HBITMAP hBitmap = ::LoadBitmap(pApp->m_hInstance,MAKEINTRESOURCE(IDB_BITMAP_RED_SMALL));
			m_btnBillIndicator.SetBitmap(hBitmap);
			GetDlgItem(IDC_BUTTONBill)->EnableWindow(TRUE);
			}
	}

	return nActiveItem;
	
}

BOOL CHomeHealthView::findCPOCodeName(int code,CString& szCPOCodeName)
{

	cpo_master->MoveFirst();

	while(cpo_master->IsEOF() == FALSE)
	{
		if(code == cpo_master->m_oversight_cpo_code_id)
		{
			szCPOCodeName = cpo_master->m_oversight_cpo_code_name;
			return TRUE;
		}
		cpo_master->MoveNext();

	}
	return FALSE;
}

BOOL CHomeHealthView::CreateOversightConrolColumns()
{
	CRect rect;
	int nColInterval;
	m_OverSightListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_OverSightListCtrl.GetClientRect(&rect);
	nColInterval = rect.Width()/6;

	m_OverSightListCtrl.InsertColumn(0,_T("Oversight ID"),LVCFMT_LEFT,nColInterval);
	m_OverSightListCtrl.InsertColumn(1,_T("CPO code"),LVCFMT_LEFT,nColInterval);
	m_OverSightListCtrl.InsertColumn(2,_T("CPO Name"),LVCFMT_LEFT,nColInterval+nColInterval);
	m_OverSightListCtrl.InsertColumn(3,_T("Date"),LVCFMT_LEFT,nColInterval);
	m_OverSightListCtrl.InsertColumn(4,_T("Minutes"),LVCFMT_LEFT,nColInterval);
	return TRUE;
}


BOOL CHomeHealthView::CreatePatientBillingControlColumns()
{
	CRect rect;
	int nColInterval;
	m_listEpisodeBill.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_listEpisodeBill.GetClientRect(&rect);
	nColInterval = rect.Width()/2;

	m_listEpisodeBill.InsertColumn(0,_T("Date"),LVCFMT_LEFT,nColInterval);
	m_listEpisodeBill.InsertColumn(1,_T("Bill Type"),LVCFMT_LEFT,nColInterval);
	return TRUE;
}


BOOL CHomeHealthView::PopulateEpisodeBilling()
{
	CString szBillType[]={_T("None"),_T("G0180"),_T("G0179"),_T("G0181")};

	int item = 0;
	LVITEM lvitem;
	CString strItem;

	// requery the patient billing
	m_activeBilling->Close();

	m_activeBilling->OpenExclusive(m_ActivePatient->m_patient_id);
	if(m_activeBilling->GetRecordCount() > 0)
	{

		m_listEpisodeBill.DeleteAllItems();
		m_activeBilling->SetAbsolutePosition(1);



		while(m_activeBilling->IsEOF() == FALSE)
		{

			lvitem.mask = LVIF_TEXT;

			strItem.Format(_T("%02d/%02d/%d"),m_activeBilling->m_patient_bill_date.GetMonth(),
  											m_activeBilling->m_patient_bill_date.GetDay(),
											m_activeBilling->m_patient_bill_date.GetYear());
			lvitem.iItem = item;
			lvitem.iSubItem = 0;
			lvitem.pszText = (LPTSTR)(LPCTSTR)(strItem);
			m_listEpisodeBill.InsertItem(&lvitem);

			strItem.Format(_T("%s"),szBillType[m_activeBilling->m_patient_bill_type]);
			lvitem.iSubItem = 1;
			lvitem.pszText= (LPTSTR)(LPCTSTR)(strItem);
			m_listEpisodeBill.SetItem(&lvitem);

			m_activeBilling->MoveNext();

		}
	}
	return TRUE;

}


BOOL CHomeHealthView::PopulateOversightControlData()
{
	Coversight_billing  billing(m_pHealthDB->GetDatabase());

	m_OverSightListCtrl.DeleteAllItems();

	if(billing.Open(m_patient_id,m_patient_episode_id) == 0)
	{
		int item = 0;
		LVITEM lvitem;
		CString strItem;

		while(billing.IsEOF() == FALSE)
		{
			lvitem.mask = LVIF_TEXT;
			strItem.Format(_T("%u"),billing.m_patient_oversight_id);

			lvitem.iItem = item;
			lvitem.iSubItem = 0;
			lvitem.pszText = (LPTSTR)(LPCTSTR)(strItem);
			m_OverSightListCtrl.InsertItem(&lvitem);
			m_OverSightListCtrl.SetItemData(item,billing.m_patient_oversight_id);


			strItem.Format(_T("%d"),billing.m_patient_oversight_cpo_code);
			lvitem.iSubItem = 1;
			lvitem.pszText= (LPTSTR)(LPCTSTR)(strItem);
			m_OverSightListCtrl.SetItem(&lvitem);

			findCPOCodeName(billing.m_patient_oversight_cpo_code,strItem);
			lvitem.iSubItem = 2;
			lvitem.pszText= (LPTSTR)(LPCTSTR)(strItem);
			m_OverSightListCtrl.SetItem(&lvitem);

			strItem.Format(_T("%d/%d/%d"),billing.m_patient_oversight_date.GetMonth(),billing.m_patient_oversight_date.GetDay(),billing.m_patient_oversight_date.GetYear());
			lvitem.iSubItem = 3;
			lvitem.pszText= (LPTSTR)(LPCTSTR)(strItem);
			m_OverSightListCtrl.SetItem(&lvitem);

			strItem.Format(_T("%d"),billing.m_patient_oversight_minute);
			lvitem.iSubItem = 4;
			lvitem.pszText= (LPTSTR)(LPCTSTR)(strItem);
			m_OverSightListCtrl.SetItem(&lvitem);
			billing.MoveNext();
			item ++;
		}

	}
	billing.Close();

	PopulateEpisodeBilling();


	return TRUE;
}



void CHomeHealthView::PopulateView()
{
	int nActiveItem = 0;
	CHomeHealthApp *pApp = (CHomeHealthApp*)(AfxGetApp());

	CString strTitle; 
	CHomeHealthDoc *pDoc = 	(CHomeHealthDoc *)GetDocument();

	m_szPatientID.Format(_T("%d"),m_ActivePatient->m_patient_id);
	m_szPatientName= m_ActivePatient->m_patient_lastname;
	m_szFirstName = m_ActivePatient->m_patient_firstname;
	m_szMiddleName = m_ActivePatient->m_patient_middlename;
	m_comboTitle.SelectString(0,m_ActivePatient->m_patient_salutation);

	strTitle = m_szFirstName +_T(" ")+ m_szPatientName;

	m_szPatientAddress = m_ActivePatient->m_patient_address;
	m_szApartment = m_ActivePatient->m_patient_address_apartment;
	m_comboState.SelectString(0,m_ActivePatient->m_patient_state);
	m_comboSex.SelectString(0,m_ActivePatient->m_patient_sex);
	m_szPatientTown = m_ActivePatient->m_patient_town;
	m_szPatientZip = m_ActivePatient->m_patient_zip;

	m_szCellPhone = m_ActivePatient->m_patient_cell_phone;
	m_szHomePhone = m_ActivePatient->m_patient_home_phone;
	m_szWorkPhone = m_ActivePatient->m_patient_work_phone;

	m_PatientDOB = m_ActivePatient->m_patient_dob;

	m_szTotalMinutes.Format(L"%d",m_ActivePatient->m_patient_billable_minutes);
	m_datePatientLastBill = m_ActivePatient->m_patient_last_bill_date;
	m_datePatientRegistration = m_ActivePatient->m_patient_registration_date;
	m_datePatientLastVisit = m_ActivePatient->m_patient_last_visit;

	pDoc->SetTitle(strTitle);

	GetDlgItem(IDC_EDIT_PATIENT_ID)->EnableWindow(FALSE);
	GetDlgItem(IDC_PATIENT_REGISTRATION)->EnableWindow(FALSE);
	GetDlgItem(IDC_PATIENT_LAST_VISIT)->EnableWindow(FALSE);
	GetDlgItem(IDC_PATIENT_LAST_BILL)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_TOTAL_MINS)->EnableWindow(FALSE);

	GetDlgItem(IDC_BUTTON_ADD_EPISODE)->EnableWindow(TRUE);
	GetDlgItem(IDC_PATIENT_EPISODE)->EnableWindow(TRUE);
		
	CreateEpisodeControlColumns();
	CreateOversightConrolColumns();
	CreatePatientBillingControlColumns();
	nActiveItem = PopulateEpisodeControlData();
	PopulateOversightControlData();

	if(nActiveItem == 0)
		{
		GetDlgItem(IDC_BUTTON_OVERSIGHT_HEALTH)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_ADD_OVERSIGHT)->EnableWindow(FALSE);
		GetDlgItem(IDC_LIST_OVERSIGHT)->EnableWindow(TRUE);
		}
	else
		{
		GetDlgItem(IDC_BUTTON_OVERSIGHT_HEALTH)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_ADD_OVERSIGHT)->EnableWindow(TRUE);
		GetDlgItem(IDC_LIST_OVERSIGHT)->EnableWindow(TRUE);
		}


	m_episodeListCtrl.SetFocus();

	return;
}


void CHomeHealthView::PopulateNewForm()
{
	CHomeHealthApp*pApp = (CHomeHealthApp*)AfxGetApp();
	GetDlgItem(IDC_EDIT_PATIENT_ID)->EnableWindow(FALSE);

	if(m_patient_id == -1)
	{
		m_comboTitle.SelectString(0,L"Mr");		
		m_comboState.SelectString(0,L"MA");
		m_comboSex.SelectString(0,L"Male");
		m_datePatientRegistration = pApp->m_localTime;
		m_datePatientLastBill = pApp->m_localTime;
		m_datePatientLastVisit = pApp->m_localTime;

		GetDlgItem(IDC_PATIENT_REGISTRATION)->EnableWindow(FALSE);
		GetDlgItem(IDC_PATIENT_LAST_VISIT)->EnableWindow(FALSE);
		GetDlgItem(IDC_PATIENT_LAST_BILL)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_TOTAL_MINS)->EnableWindow(FALSE);

		GetDlgItem(IDC_BUTTON_ADD_EPISODE)->EnableWindow(FALSE);
		GetDlgItem(IDC_PATIENT_EPISODE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_OVERSIGHT_HEALTH)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_ADD_OVERSIGHT)->EnableWindow(FALSE);
		GetDlgItem(IDC_LIST_OVERSIGHT)->EnableWindow(FALSE);
	
		HBITMAP hBitmap = ::LoadBitmap(pApp->m_hInstance,MAKEINTRESOURCE(IDB_BITMAP_GREEN_SMALL));
		m_btnBillIndicator.SetBitmap(hBitmap);
		GetDlgItem(IDC_BUTTONBill)->EnableWindow(FALSE);
	}

	CString strTitle(_T("New Patient")); 
	CHomeHealthDoc *pDoc = 	(CHomeHealthDoc *)GetDocument();
	pDoc->SetTitle(strTitle);
}



BOOL CHomeHealthView::OpenPatientRecords()
{

	if(m_dbOpened == FALSE)
	{
		m_ActivePatient = new Cpatient_master(m_pHealthDB->GetDatabase());
		m_activePatientEpisode = new Cpatient_episode(m_pHealthDB->GetDatabase());
		m_activeBilling = new Cpatient_billing(m_pHealthDB->GetDatabase());

		if (0 != m_ActivePatient->OpenExclusive(m_patient_id))
			return FALSE;

		if(0 != m_activePatientEpisode->OpenExclusive(m_patient_id))
			return FALSE;

		if(0 != m_activeBilling->OpenExclusive(m_patient_id))
			return FALSE;

		m_dbOpened = TRUE;
	}
	return TRUE;
}


void CHomeHealthView::OnInitialUpdate()
{
	m_pSet = &GetDocument()->m_MDFMDIAppSet;
	// This record set is not need to be updated
	CRecordView::OnInitialUpdate();
	CHomeHealthApp*pApp = (CHomeHealthApp*)AfxGetApp();
	CHomeHealthDatabase* pDB = pApp->GetHomeHealthDatabase();
	m_pHealthDB = pDB;

	m_patient_id = pApp->m_nSelectedPatient;
	m_active_episode_id = -1;

	if(m_patient_id != -1)
		OpenPatientRecords();

	ReOpenView();

}


void CHomeHealthView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	// TODO: Add your specialized code here and/or call the base class
	
	CRecordView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}


// CHomeHealthView printing


void CHomeHealthView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CHomeHealthView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);

}

void CHomeHealthView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	long lfHtTitle1 = 20;
	long lfHtTitle2 = 16;
	long lfHtText = 12;

	fntTitle1 = new CFont;
	fntTitle2 = new CFont;
	fntText = new CFont;

	fntHeader = 0;

	if(homehealth_printmode == homehealth_print_initial_bill)
	{
		lfHtTitle1 = MulDiv(20, pDC->GetDeviceCaps(LOGPIXELSY), 72); 
		lfHtTitle2 = MulDiv(14, pDC->GetDeviceCaps(LOGPIXELSY), 72); 
		lfHtText   = MulDiv(10, pDC->GetDeviceCaps(LOGPIXELSY), 72); 
		fntTitle1->CreateFont(lfHtTitle1, 0, 0, 0,
					  FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET,
					OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
					DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,
					_T("Times New Roman"));

		fntTitle2->CreateFont(lfHtTitle2, 0, 0, 0,
					  FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET,
					OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
					DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,
					_T("Times New Roman"));

		fntText->CreateFont(lfHtText, 0, 0, 0,
					  FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET,
					OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
					DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,
					_T("Courier New"));
	}
	else if(homehealth_printmode == homehealth_print_oversight_bill)
	{
		fntHeader = new CFont;

		lfHtTitle1 = MulDiv(18, pDC->GetDeviceCaps(LOGPIXELSY), 72); 
		lfHtTitle2 = MulDiv(12, pDC->GetDeviceCaps(LOGPIXELSY), 72); 
		lfHtText   = MulDiv(10, pDC->GetDeviceCaps(LOGPIXELSY), 72); 
		fntTitle1->CreateFont(lfHtTitle1, 0, 0, 0,
					  FW_NORMAL, FALSE, TRUE, FALSE, ANSI_CHARSET,
					OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
					DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,
					_T("Times New Roman"));

		fntTitle2->CreateFont(lfHtTitle2, 0, 0, 0,
					  FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET,
					OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
					DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,
					_T("Times New Roman"));

		fntText->CreateFont(lfHtText, 0, 0, 0,
					  FW_NORMAL, FALSE, FALSE, FALSE, ANSI_CHARSET,
					OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
					DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,
					_T("Courier New"));

		fntHeader->CreateFont(lfHtTitle2, 0, 0, 0,
					  FW_NORMAL, FALSE, TRUE, FALSE, ANSI_CHARSET,
					OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
					DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,
					_T("Times New Roman"));

	}


	// TODO: add extra initialization before printing
}

void CHomeHealthView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	if(fntText)
		delete fntText;
	if(fntTitle1)
		delete fntTitle1;
	if(fntTitle2)
		delete fntTitle2;
	if(fntHeader)
		delete fntHeader;
	// TODO: add cleanup after printing
}

void CHomeHealthView::printInitialBilling(CDC* pDC,CPrintInfo* pInfo)
{

	int page_x, page_y;
	int oldMapMode = pDC->SetMapMode(MM_TEXT);

	int margin = 500;
	int row_margin = 200;
	int title_space = 20;
	page_y = pDC->GetDeviceCaps(VERTRES);
	page_x = pDC->GetDeviceCaps(HORZRES);

	margin = page_x/10;

	if(pInfo->m_nCurPage == 1)
	{
		CString szDrName, szFormTitle;
		CString szDrDept,szDrAddr1,szDrAddr2,szDrPhone;
		CString szText;
		TEXTMETRIC tm; 
		int pos_x = 0,row_height = 0;
		int pos_y = margin;
		szDrName.LoadStringW(IDS_TITLE_NAME);
		szFormTitle.LoadStringW(IDS_TITLE_BILL);
		szDrDept.LoadStringW(IDS_DOCTOR_DEPT);
		szDrAddr1.LoadStringW(IDS_DOCTOR_ADDR1);
		szDrAddr2.LoadStringW(IDS_DOCTOR_ADDR2);
		szDrPhone.LoadStringW(IDS_DOCTOR_PHONE);
		
		CFont* fntOld = pDC->SelectObject(fntTitle1);
		pDC->GetTextMetrics(&tm);
		row_height = tm.tmHeight + tm.tmExternalLeading;
		pos_x  = (page_x - (szDrName.GetLength()*tm.tmAveCharWidth))/2;		
		pDC->TextOutW(pos_x,pos_y,szDrName,szDrName.GetLength());
		
		pDC->SelectObject(fntTitle2);
		pDC->GetTextMetrics(&tm);
		pos_x  = (page_x - (szDrDept.GetLength()*tm.tmAveCharWidth))/2;		
		pos_y += (row_height + title_space);
		pDC->TextOutW(pos_x,pos_y,szDrDept,szDrDept.GetLength());

		row_height = tm.tmHeight + tm.tmExternalLeading;

		pos_x  = (page_x - (szDrAddr1.GetLength()*tm.tmAveCharWidth))/2;		
		pos_y += (row_height + title_space);
		pDC->TextOutW(pos_x,pos_y,szDrAddr1,szDrAddr1.GetLength());

		pos_x  = (page_x - (szDrAddr2.GetLength()*tm.tmAveCharWidth))/2;		
		pos_y += (row_height + title_space);
		pDC->TextOutW(pos_x,pos_y,szDrAddr2,szDrAddr2.GetLength());

		pos_x  = (page_x - (szDrPhone.GetLength()*tm.tmAveCharWidth))/2;		
		pos_y += (row_height + title_space);
		pDC->TextOutW(pos_x,pos_y,szDrPhone,szDrPhone.GetLength());

		pos_x  = (page_x - (szFormTitle.GetLength()*tm.tmAveCharWidth))/2;		
		pos_y += (row_height + row_margin);
		pDC->TextOutW(pos_x,pos_y,szFormTitle,szFormTitle.GetLength());

		pDC->SelectObject(fntText);
		pDC->GetTextMetrics(&tm);

		szText.Format(L"Date: %02d/%02d/%d",m_currentDate.GetMonth(),m_currentDate.GetDay(),m_currentDate.GetYear());
		pos_x  = (page_x - (szText.GetLength()*tm.tmAveCharWidth)-margin);		
		pos_y += (row_height + row_margin*2);
		pDC->TextOutW(pos_x,pos_y,szText,szText.GetLength());

		row_height = tm.tmHeight + tm.tmExternalLeading;


		szText.Format(L"Home Health Agency: %s",m_activePatientEpisode->m_episode_hh_agency_name);
		pos_x  = margin;		
		pos_y += (row_height + row_margin);
		pDC->TextOutW(pos_x,pos_y,szText,szText.GetLength());

		szText.Format(L"Patient Name: %s %s",m_ActivePatient->m_patient_firstname,m_ActivePatient->m_patient_lastname);
		pos_x  = margin;		
		pos_y += (row_height + row_margin);
		pDC->TextOutW(pos_x,pos_y,szText,szText.GetLength());

		szText.Format(L"Episode of Service From: %02d/%02d/%d to %02d/%02d/%d",m_activePatientEpisode->m_episode_start_date.GetMonth()
			,m_activePatientEpisode->m_episode_start_date.GetDay()
			,m_activePatientEpisode->m_episode_start_date.GetYear()
			,m_activePatientEpisode->m_episode_end_date.GetMonth()
			,m_activePatientEpisode->m_episode_end_date.GetDay()
			,m_activePatientEpisode->m_episode_end_date.GetYear());

		pos_x  = margin;		
		pos_y += (row_height + row_margin);
		pDC->TextOutW(pos_x,pos_y,szText,szText.GetLength());

		szText.Format(L"DX Codes: %s",m_activePatientEpisode->m_episode_dx_codes);
		pos_x  = margin;		
		pos_y += (row_height + row_margin);
		pDC->TextOutW(pos_x,pos_y,szText,szText.GetLength());

		if(m_activePatientEpisode->m_episode_type.CompareNoCase(L"ReCertification") == 0) 
			szText.Format(L"_____________ Review and Signature of HH Plan for %s G0179",m_activePatientEpisode->m_episode_type);
		else
			szText.Format(L"_____________ Review and Signature of HH Plan for %s G0180",m_activePatientEpisode->m_episode_type);

		pos_x  = margin;		
		pos_y += (row_height + row_margin*3);
		pDC->TextOutW(pos_x,pos_y,szText,szText.GetLength());
	
		szText.Format(L"Signature of MD:____________________",m_activePatientEpisode->m_episode_type);
		pos_x  = margin;		
		pos_y += (row_height + row_margin);
		pDC->TextOutW(pos_x,pos_y,szText,szText.GetLength());

		pDC->SelectObject(fntOld);
		this->PostMessageW(WM_COMMAND,ID_PRINTED_BILL);
	}
	else
	{

	}

	pDC->SetMapMode(oldMapMode);
}


CString CHomeHealthView::GetCurrentMonth()
{
	CHomeHealthApp* pApp = (CHomeHealthApp*) AfxGetApp();
	switch(pApp->m_localTime.wMonth)
	{
	case 1:
		return CString(L"January");
	case 2:
		return CString(L"February");
	case 3:
		return CString(L"March");
	case 4:
		return CString(L"April");
	case 5:
		return CString(L"May");
	case 6:
		return CString(L"June");
	case 7:
		return CString(L"July");
	case 8:
		return CString(L"August");
	case 9:
		return CString(L"September");
	case 10:
		return CString(L"October");
	case 11:
		return CString(L"November");
	case 12:
		return CString(L"December");
	}
	return CString(L"Error");
}

// printing oversight bill
void CHomeHealthView::printOversightBilling(CDC* pDC,CPrintInfo* pInfo)
{
	int page_x, page_y;
	int oldMapMode = pDC->SetMapMode(MM_TEXT);

	int margin = 500;
	int row_margin = 200;
	int title_space = 50;
	int right_margin = 0;
	int column1,column2,column3;
	page_y = pDC->GetDeviceCaps(VERTRES);
	page_x = pDC->GetDeviceCaps(HORZRES);

	margin = page_x/10;
	right_margin = margin * 6;
	column1 = margin;
	column2 = margin*6;
	column3 = column2 + 2*margin;


	if(pInfo->m_nCurPage == 1)
	{
		CString szText;
		TEXTMETRIC tm; 
		int pos_x = 0,row_height = 0;
		int pos_y = margin;
		

		// printing HH Agency Title
		szText.Format(_T("Home Health Agency: %s"),m_activePatientEpisode->m_episode_hh_agency_name);
		CFont* fntOld = pDC->SelectObject(fntTitle1);
		pDC->GetTextMetrics(&tm);
		row_height = tm.tmHeight + tm.tmExternalLeading;
		pos_x  = (page_x - (szText.GetLength()*tm.tmAveCharWidth))/2;		
		pDC->TextOutW(pos_x,pos_y,szText,szText.GetLength());
		
		
		szText.Format(_T("Physician Oversight Billing for Medicare Home Health"));
		pDC->SelectObject(fntHeader);
		pDC->GetTextMetrics(&tm);
		pos_x  = (page_x - (szText.GetLength()*tm.tmAveCharWidth))/2;		
		pos_y += (row_height + title_space);
		pDC->TextOutW(pos_x,pos_y,szText,szText.GetLength());

		row_height = tm.tmHeight + tm.tmExternalLeading;

		pDC->SelectObject(fntTitle2);
		pDC->GetTextMetrics(&tm);

		szText.Format(_T("Patient Name: %s %s"),m_ActivePatient->m_patient_firstname,m_ActivePatient->m_patient_lastname);
		pos_x  = margin + margin;		
		pos_y += (row_height + title_space + row_margin);
		pDC->TextOutW(pos_x,pos_y,szText,szText.GetLength());

		szText.Format(_T("DOB: %02d/%02d/%d"),m_ActivePatient->m_patient_dob.GetMonth()
			,m_ActivePatient->m_patient_dob.GetDay()
			,m_ActivePatient->m_patient_dob.GetYear());
		pos_x  = right_margin;		
		pDC->TextOutW(pos_x,pos_y,szText,szText.GetLength());


		szText.Format(_T("Month: %s"),GetCurrentMonth());
		pos_x  = margin + margin;		
		pos_y += (row_height + title_space );
		pDC->TextOutW(pos_x,pos_y,szText,szText.GetLength());

		szText.Format(_T("Last Seen: %02d/%02d/%d"),m_activePatientEpisode->m_episode_last_visit.GetMonth()
			,m_activePatientEpisode->m_episode_last_visit.GetDay()
			,m_activePatientEpisode->m_episode_last_visit.GetYear());
		pos_x  = right_margin;		
		pDC->TextOutW(pos_x,pos_y,szText,szText.GetLength());

		if(m_activePatientEpisode->m_episode_type.CompareNoCase(_T("Recertification")) == 0) 
			szText.Format(_T("Activity: Recertification (G0179)"));
		else
			szText.Format(_T("Activity: Initial Certification (G0180)"));
		pos_x  = margin + margin;		
		pos_y += (row_height + title_space );
		pDC->TextOutW(pos_x,pos_y,szText,szText.GetLength());

		szText.Format(_T("Episode: %02d/%02d/%d - %02d/%02d/%d"),m_activePatientEpisode->m_episode_start_date.GetMonth()
			,m_activePatientEpisode->m_episode_start_date.GetDay()
			,m_activePatientEpisode->m_episode_start_date.GetYear()
			,m_activePatientEpisode->m_episode_end_date.GetMonth()
			,m_activePatientEpisode->m_episode_end_date.GetDay()
			,m_activePatientEpisode->m_episode_end_date.GetYear());
		pos_x  = right_margin;		
		pDC->TextOutW(pos_x,pos_y,szText,szText.GetLength());


//		pDC->SelectObject(fntHeader);
//		pDC->GetTextMetrics(&tm);
		szText.Format(_T("Oversight CPO Code"));
		pos_x  = column1;		
		pos_y += (row_height + title_space + row_margin);
		pDC->TextOutW(pos_x,pos_y,szText,szText.GetLength());

		szText.Format(_T("Date"));
		pos_x  = column2;		
		pDC->TextOutW(pos_x,pos_y,szText,szText.GetLength());

		szText.Format(_T("Minutes"));
		pos_x  = column3;		
		pDC->TextOutW(pos_x,pos_y,szText,szText.GetLength());


		Coversight_billing oversight;
		oversight.OpenForOversightBilling(m_activePatientEpisode->m_patient_episode_code);
		row_height = (tm.tmHeight + tm.tmExternalLeading);

		pDC->SelectObject(fntText);
		pDC->GetTextMetrics(&tm);

		szText.Format(_T("________________________________________________________________________________________"));
		pos_y += (row_height + title_space);
		pDC->TextOutW(column1,pos_y,szText,szText.GetLength());

		row_height += (tm.tmHeight + tm.tmExternalLeading);

		while(oversight.IsEOF() == FALSE)
		{
	
			findCPOCodeName(oversight.m_patient_oversight_cpo_code,szText);
			pos_y += (row_height + title_space);
			pDC->TextOutW(column1,pos_y,szText,szText.GetLength());

			szText.Format(_T("%02d/%02d/%d"),oversight.m_patient_oversight_date.GetMonth(),
				oversight.m_patient_oversight_date.GetDay(),
				oversight.m_patient_oversight_date.GetYear());
			pDC->TextOutW(column2,pos_y,szText,szText.GetLength());

			szText.Format(_T("%d"),oversight.m_patient_oversight_minute);
			pDC->TextOutW(column3,pos_y,szText,szText.GetLength());

			row_height = tm.tmHeight + tm.tmExternalLeading;
			oversight.MoveNext();
		}


		oversight.Close();

		szText.Format(_T("________________________________________________________________________________________"));
		pos_y += (row_height + title_space);
		pDC->TextOutW(column1,pos_y,szText,szText.GetLength());

		szText.Format(_T("Total Monthly Minutes: %d"),m_activePatientEpisode->m_episode_total_minutes);
		pos_x  = margin;		
		pos_y += (row_height + row_margin);
		pDC->TextOutW(pos_x,pos_y,szText,szText.GetLength());

		szText.Format(_T("*CPO time spent must be equal to at least 30 minutes in a calendar month to bill medicare"));
		pos_x  = margin;		
		pos_y += (row_height + title_space);
		pDC->TextOutW(pos_x,pos_y,szText,szText.GetLength());

		szText.Format(_T("Physician Signature:__________________________      Date: %02d/%02d/%d")
			,m_currentDate.GetMonth()
			,m_currentDate.GetDay()
			,m_currentDate.GetYear());

		pos_x  = margin;		
		pos_y += (row_height + row_margin);
		pDC->TextOutW(pos_x,pos_y,szText,szText.GetLength());

		szText.Format(_T("Diagnosis:__________________________"));
		pos_x  = (page_x - (szText.GetLength()*tm.tmAveCharWidth))/2;		
		pos_y += (row_height + row_margin);
		pDC->TextOutW(pos_x,pos_y,szText,szText.GetLength());


		pDC->SelectObject(fntOld);
		this->PostMessageW(WM_COMMAND,ID_PRINTED_BILL);
	}
	else
	{

	}

	pDC->SetMapMode(oldMapMode);

}
void CHomeHealthView::printPatientLeadger(CDC* pDC,CPrintInfo* pInfo)
{

}

void CHomeHealthView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{

	switch(homehealth_printmode)
	{
	case homehealth_print_initial_bill:
		printInitialBilling(pDC,pInfo);
		break;
	case homehealth_print_oversight_bill:
		printOversightBilling(pDC,pInfo);
		break;
	case homehealth_print_patient_record:
		break;
	default:
		break;
	}
	CRecordView::OnPrint(pDC, pInfo);
}

void CHomeHealthView::OnDraw(CDC* /*pDC*/)
{
	// TODO: Add your specialized code here and/or call the base class
}


void CHomeHealthView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CHomeHealthView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CHomeHealthView diagnostics

#ifdef _DEBUG
void CHomeHealthView::AssertValid() const
{
	CRecordView::AssertValid();
}

void CHomeHealthView::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}

CHomeHealthDoc* CHomeHealthView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHomeHealthDoc)));
	return (CHomeHealthDoc*)m_pDocument;
}
#endif //_DEBUG


// CHomeHealthView database support
CRecordset* CHomeHealthView::OnGetRecordset()
{
	return m_pSet;
}



// CHomeHealthView message handlers


void CHomeHealthView::OnNMDblclkPatientEpisode(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
		*pResult = 0;
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


int CHomeHealthView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CRecordView::OnCreate(lpCreateStruct) == -1)
		return -1;

		return 0;
}





void CHomeHealthView::OnClickPatientEpisode(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	*pResult = 0;
	if(pNMItemActivate->iItem == -1)
		return;

	m_patient_episode_id =  m_episodeListCtrl.GetItemData(pNMItemActivate->iItem);

	CWnd* pAddButton = GetDlgItem(IDC_BUTTON_ADD_OVERSIGHT);

	if(m_patient_episode_id == m_active_episode_id)
	{
		pAddButton->EnableWindow(TRUE);
		// enable button
	}
	else
	{
		// disable button
		pAddButton->EnableWindow(FALSE);
	}

	PopulateOversightControlData();
}


void CHomeHealthView::OnLvnItemchangedPatientEpisode(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	if(pNMLV->uNewState == 3 && pNMLV->uOldState == 0)
	{
		m_patient_episode_id =  m_episodeListCtrl.GetItemData(pNMLV->iItem);
		PopulateOversightControlData();
	}

	*pResult = 0;
}


void CHomeHealthView::OnLvnKeydownPatientEpisode(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	// TODO: Add your control notification handler code here
	*pResult = 0;
//	m_patient_episode_id =  m_episodeListCtrl.GetItemData(pNMItemActivate->iItem);

//	PopluateOversightList();
}


void CHomeHealthView::AddNewOversightBilling()
{
	int total_billed = 0;
	CTime	last_billed_date = 0;
	CTimeSpan timediff = 0;
	CTime last_visit = 0;
	COversightRecordDlg oversightRecordDlg(m_patient_id,m_patient_episode_id,m_patient_episode_start_date,m_patient_episode_end_date,this);
	if(IDOK == oversightRecordDlg.DoModal())
	{
		// invalide the list view and show the new row up there.
		if(oversightRecordDlg.m_Oversight_billing_mintues > 0 )
		{
			// populate the field back with the new value and also the report list with the new values
			m_activePatientEpisode->Edit();
			m_ActivePatient->Edit();

			m_activePatientEpisode->m_episode_total_minutes += oversightRecordDlg.m_Oversight_billing_mintues;
			m_ActivePatient->m_patient_billable_minutes = m_activePatientEpisode->m_episode_total_minutes;
	
			// if last visit is later date then only update the last visit date
			if(m_ActivePatient->m_patient_last_visit < oversightRecordDlg.m_OversightDateTime)
			{
				m_ActivePatient->m_patient_last_visit = oversightRecordDlg.m_OversightDateTime;
				m_activePatientEpisode->m_episode_last_visit = oversightRecordDlg.m_OversightDateTime;
				m_datePatientLastVisit = oversightRecordDlg.m_OversightDateTime;
			}

			m_szTotalMinutes.Format(_T("%d"),m_ActivePatient->m_patient_billable_minutes);

			// bill date assignments
			if(m_ActivePatient->m_patient_last_bill_date == 0)
				last_billed_date = m_ActivePatient->m_patient_registration_date;
			else
				last_billed_date = m_ActivePatient->m_patient_oversight_bill_date;

			
			if(m_activePatientEpisode->m_episode_billing_status == EPISODE_BILLING_STATUS_NA)
			{
				if(m_activePatientEpisode->m_episode_total_minutes >=EPISODE_OVERSIGHT_BILLING_MINUTES)
				{
					CTimeSpan ts = m_currentDate - last_billed_date;
					if(ts.GetDays() > EPISODE_BILLING_DAYS)
						m_activePatientEpisode->m_episode_billing_status = EPISODE_BILLING_STATUS_OVERSIGHT; 
				}
			}

			total_billed = m_ActivePatient->m_patient_billable_minutes;
			last_visit = m_ActivePatient->m_patient_last_visit;

			m_activePatientEpisode->Update();
			m_ActivePatient->Update();
		}
		PopulateEpisodeControlData();
		PopulateOversightControlData();
		UpdateData(FALSE);

	}

	timediff = last_visit - last_billed_date;
	if(timediff.GetDays() >= 30)
	{
		if(total_billed >= 30)
		{
			AfxMessageBox(_T("Patient can be billed for the episode"));
		}
	}
}


// adding new ovesight reccord
void CHomeHealthView::OnBnClickedButtonAddOversight()
{
	return AddNewOversightBilling();
}


// when adding a new episode. Please take care of handling spill over
void CHomeHealthView::AddNewEpisode()
{
	// TODO: Add your control notification handler code here
	CString szFullName = m_szFirstName+_T(" ")+ m_szPatientName;
	SYSTEMTIME stLocalTime = ((CHomeHealthApp*)AfxGetApp())->m_localTime;

	CEpisodeDlg episodeDlg(m_activePatientEpisode,m_ActivePatient,stLocalTime);
	if(IDOK == episodeDlg.DoModal())
		{
		m_active_episode_id = episodeDlg.m_addedEpisode_id;
		m_activePatientEpisode->Close();
		m_activePatientEpisode->OpenExclusive(m_ActivePatient->m_patient_id);

//		m_activePatientEpisode->Requery();
		PopulateEpisodeControlData();
		PopulateOversightControlData();
		UpdateData(FALSE);
		}
}

void CHomeHealthView::OnBnClickedButtonAddEpisode()
{
	AddNewEpisode();

}


void CHomeHealthView::OnNMRClickPatientEpisode(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here

	if(-1 != pNMItemActivate->iItem)
		m_patient_episode_id =  m_episodeListCtrl.GetItemData(pNMItemActivate->iItem);

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	
	CMenu menu;
	menu.LoadMenu(IDR_EPISODE_CONTEXT); // our context menu
	CMenu* pContextMenu = menu.GetSubMenu(0);
	POINT p;
	p.x = pNMListView->ptAction.x;
	p.y = pNMListView->ptAction.y;
	::ClientToScreen(pNMHDR->hwndFrom, &p);
	int nID = pContextMenu->TrackPopupMenu( TPM_LEFTALIGN | TPM_LEFTBUTTON , p.x, p.y, this);
	*pResult = 1;
}


void CHomeHealthView::OnEpisodeEdit()
{
	// TODO: Add your command handler code here
	AfxMessageBox(L"Episode Edit functionality is not implemented yet !!");
}


void CHomeHealthView::OnEpisodeDelete()
{
	// TODO: Add your command handler code here
	AfxMessageBox(L"Episode Delete functionality is not implemented yet !!");

}



void CHomeHealthView::ReOpenView()
{
	CHomeHealthApp*pApp = (CHomeHealthApp*)AfxGetApp();

	GetDlgItem(IDC_BUTTON_ADD_OVERSIGHT)->EnableWindow(FALSE);

	if(m_patient_id != -1)
		PopulateView();
	else
		PopulateNewForm();

	UpdateData(FALSE);
	
}
BOOL CHomeHealthView::ValidatePatientInformation()
{

	return TRUE;

}

void CHomeHealthView :: OnPatientSaveNew()
{
	if(IDOK != AfxMessageBox(AFX_IDS_ADD_PATIENT_CONFIRMATION,MB_OKCANCEL) )
		return;

	// Add the data into Patient registration table and close the table

	if(m_ActivePatient != NULL)
	{
		AfxMessageBox(IDS_PATIENT_MASTER_ERROR,MB_OK);
		return;
	}

	OpenPatientRecords();

	m_ActivePatient->AddNew();
	int sel = 0;
	m_ActivePatient->m_patient_firstname = m_szFirstName;
	m_ActivePatient->m_patient_lastname = m_szPatientName;
	m_ActivePatient->m_patient_address = m_szPatientAddress;
	m_ActivePatient->m_patient_address_apartment = m_szApartment;
	m_ActivePatient->m_patient_town = m_szPatientTown;

	sel = m_comboState.GetCurSel();
	m_comboState.GetLBText(sel,m_ActivePatient->m_patient_state);

	sel = m_comboSex.GetCurSel();
	m_comboState.GetLBText(sel,m_ActivePatient->m_patient_sex);

	m_ActivePatient->m_patient_middlename = m_szMiddleName;

	sel = m_comboTitle.GetCurSel();
	m_comboTitle.GetLBText(sel,m_ActivePatient->m_patient_salutation);

	m_ActivePatient->m_patient_dob = m_PatientDOB;
	m_ActivePatient->m_patient_home_phone = m_szHomePhone;
	m_ActivePatient->m_patient_cell_phone = m_szCellPhone;
	m_ActivePatient->m_patient_work_phone = m_szWorkPhone;
	m_ActivePatient->m_patient_communication_phone = m_szHomePhone;
	m_ActivePatient->m_patient_zip = m_szPatientZip;
	m_ActivePatient->m_patient_registration_date = ((CHomeHealthApp*)AfxGetApp())->m_localTime;
	m_ActivePatient->m_patient_last_visit = m_ActivePatient->m_patient_registration_date;
	m_ActivePatient->m_patient_last_bill_date = 0;
	m_ActivePatient->m_patient_billable_minutes = 0;
	m_ActivePatient->m_patient_oversight_bill_date = 0;

	m_ActivePatient->Update();

	m_ActivePatient->SetAbsolutePosition(-1);

	m_patient_id = m_ActivePatient->m_patient_id;

	
	CString str;
	str.Format(_T("Patient's record Successfully created : %s %s"),m_szFirstName, m_szPatientName);
	AfxMessageBox(str);
	// close the view and re-open it again.

	ReOpenView();

}


/*Edit patient's information*/
void CHomeHealthView::OnPatientSaveEdit()
{
	if(IDOK != AfxMessageBox(AFX_IDS_PATIENT_EDIT_CONFIRM,MB_OKCANCEL) )
		return;

	// Add the data into Patient registration table and close the table
	Cpatient_master patient_master;
	
	if (patient_master.OpenForModify(m_patient_id) == -1)
	{
		AfxMessageBox(IDS_PATIENT_MASTER_ERROR,MB_OK);
		return;
	}

	patient_master.Edit();
	int sel = 0;
	patient_master.m_patient_firstname = m_szFirstName;
	patient_master.m_patient_lastname = m_szPatientName;
	patient_master.m_patient_address = m_szPatientAddress; 
	patient_master.m_patient_address_apartment  = m_szApartment;
	patient_master.m_patient_town = m_szPatientTown;

	sel = m_comboState.GetCurSel();
	m_comboState.GetLBText(sel,patient_master.m_patient_state);

	sel = m_comboSex.GetCurSel();
	m_comboSex.GetLBText(sel,patient_master.m_patient_sex);

	patient_master.m_patient_middlename = m_szMiddleName;

	sel = m_comboTitle.GetCurSel();
	m_comboTitle.GetLBText(sel,patient_master.m_patient_salutation);

	patient_master.m_patient_dob = m_PatientDOB;
	patient_master.m_patient_home_phone = m_szHomePhone;
	patient_master.m_patient_cell_phone = m_szCellPhone;
	patient_master.m_patient_work_phone = m_szWorkPhone;
	patient_master.m_patient_communication_phone = m_szHomePhone;
	//patient_master.m_patient_country = m_szCountry;
	patient_master.m_patient_zip = m_szPatientZip;

	patient_master.Update();
	patient_master.Close();

	// close the view and re-open it again.

	ReOpenView();

}
/* On file save, is effective for the new patient saving.
When a new patient registration is requested, User enters required details. about Name,
Address, their telephone number and etc.
To commit the record into database. User has to call save record. Until users saves the record
One can not create episode information or oversight billing information.

Once the record is saved, It is valid for the additional transaction. The main point to remember
is that with the record commited. It will have its own patient id and the name of the title tab
has to be named accordingly, may be patient name or something.
*/
void CHomeHealthView::OnFileSave()
{
	// TODO: Add your command handler code here

	// validate the data and then ask use if he wants to create a new record for the patient.
	UpdateData(TRUE);

	if( FALSE == ValidatePatientInformation())
	{
		return;

	}


	if(-1 == m_patient_id)
		OnPatientSaveNew();
	else
		OnPatientSaveEdit();



}


void CHomeHealthView::OnRclickListOversight(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here

#if 0
	if(-1 != pNMItemActivate->iItem)
		m_patient_episode_id =  m_episodeListCtrl.GetItemData(pNMItemActivate->iItem);
#endif
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	
	CMenu menu;
	menu.LoadMenu(IDR_EPISODE_CONTEXT); // our context menu
	CMenu* pContextMenu = menu.GetSubMenu(1);
	POINT p;
	p.x = pNMListView->ptAction.x;
	p.y = pNMListView->ptAction.y;
	::ClientToScreen(pNMHDR->hwndFrom, &p);
	int nID = pContextMenu->TrackPopupMenu( TPM_LEFTALIGN | TPM_LEFTBUTTON , p.x, p.y, this);
	*pResult = 1;
}



// On Episode Add event handler
void CHomeHealthView::OnEpisodeAdd()
{
	// TODO: Add your command handler code here
	return AddNewEpisode();

}

// On Oversight add event handler
void CHomeHealthView::OnOversightAdd()
{
	return AddNewOversightBilling();
	// TODO: Add your command handler code here
}

// On produce patient ledger
void CHomeHealthView::OnReportsPatientledger()
{
	AfxMessageBox(_T("Patient Ledger report is not yet Implemented"));
}


void CHomeHealthView::OnEpisodeAddoversight()
{
	return AddNewOversightBilling();

}


// walk through billing record and find out open bill records to shoot email / fax
void CHomeHealthView::OnBnClickedButtonbill()
{

	// check if what is the status of the bill code -
	// if it is G0179 or G0180, Then it is initial billing or recertification billing. of TX(485) 
	// Otherwise it is G0181 or G0182, that is oversight billing.
	if(m_activePatientEpisode->m_episode_billing_status == 1) // Initial Billing
	{
		CInitialBillingDlg dlg(m_ActivePatient,m_activePatientEpisode);
		if(IDOK == dlg.DoModal())
			{
			homehealth_printmode = homehealth_print_initial_bill;
			PostMessage(WM_COMMAND,ID_FILE_PRINT);
			}
	}
	else if (m_activePatientEpisode->m_episode_billing_status == 2) // eligible for oversight billing
	{
		COversightBillingDlg dlg(this,m_ActivePatient,m_activePatientEpisode);
		if(IDOK == dlg.DoModal())
		{
			homehealth_printmode = homehealth_print_oversight_bill;
			PostMessage(WM_COMMAND,ID_FILE_PRINT);
		}
	}
	else
	{

	}

	return;
}



void CHomeHealthView::OnCompleteInitialBillPrintingCommon()
{
	m_activeBilling->AddNew();

	m_activeBilling->m_patient_bill_date = m_currentDate;
	m_activeBilling->m_patient_id = m_ActivePatient->m_patient_id;
	m_activeBilling->m_patient_episode_code = m_activePatientEpisode->m_patient_episode_code;
	if(m_activePatientEpisode->m_episode_billing_status  == 1)
	{
		if(m_activePatientEpisode->m_episode_type.CompareNoCase(L"Recertification")  == 0)
			m_activeBilling->m_patient_bill_type = 2;
		else
			m_activeBilling->m_patient_bill_type = 1;
	}
	else
		m_activeBilling->m_patient_bill_type = 3;

	m_activeBilling->m_patient_hh_agency_code = m_activePatientEpisode->m_episode_hh_agency_code;
	m_activeBilling->m_patient_sent_fax = 1;
	m_activeBilling->m_patient_sent_email = 0;

	m_activeBilling->Update();



}

// completion of Oversight billing
void CHomeHealthView::OnCompleteOversightBillPrinting()
{
	OnCompleteInitialBillPrintingCommon();

	// update the billing status back to normal 
	m_activePatientEpisode->Edit();

	// for spill over 
	//m_activePatientEpisode->m_episode_total_minutes-=EPISODE_OVERSIGHT_BILLING_MINUTES;
	m_activePatientEpisode->m_episode_total_minutes = 0;
	m_activePatientEpisode->m_episode_billing_status = EPISODE_BILLING_STATUS_NA; 
	m_activePatientEpisode->m_episode_last_bill_date = m_currentDate;
	m_patient_billing_status = m_activePatientEpisode->m_episode_billing_status;
	m_activePatientEpisode->Update();
	homehealth_printmode = homehealth_print_none;

	// update the patient files
	m_ActivePatient->Edit();
	m_ActivePatient->m_patient_last_bill_date = m_currentDate;
	m_ActivePatient->m_patient_billable_minutes = 0; // may be we can store a spill over here as well
	m_ActivePatient->Update();

	// update the oversight billing records now.

	Coversight_billing oversight;

	if (oversight.OpenForOversightBilling(m_activePatientEpisode->m_patient_episode_code) !=0)
	{
		AfxMessageBox(L"Error Opening oversight billing records",MB_OK);
		return;
	}


	while(oversight.IsEOF() == FALSE)
	{
		oversight.Edit();
		oversight.m_patient_oversight_billed = TRUE;
		oversight.Update();
		oversight.MoveNext();
	}
	oversight.Close();
	homehealth_printmode = homehealth_print_none;

}


// compleltion of Initial billing
void CHomeHealthView::OnCompleteInitialBillPrinting()
{
	OnCompleteInitialBillPrintingCommon();

	// update the billing status back to normal 
	m_activePatientEpisode->Edit();

	// Dont only check for the 30 minutes, also check for the lapses of 30 days for the billing cycle.
	if(m_activePatientEpisode->m_episode_total_minutes >=30)
	{
		CTimeSpan ts  = m_currentDate - m_activePatientEpisode->m_episode_last_bill_date;
		if(ts.GetDays() >= EPISODE_BILLING_DAYS)
			m_activePatientEpisode->m_episode_billing_status = EPISODE_BILLING_STATUS_OVERSIGHT; 
		else
			m_activePatientEpisode->m_episode_billing_status = EPISODE_BILLING_STATUS_NA; 
	}
	else
		m_activePatientEpisode->m_episode_billing_status = EPISODE_BILLING_STATUS_NA;

	m_patient_billing_status = m_activePatientEpisode->m_episode_billing_status;

	m_activePatientEpisode->m_episode_last_bill_date = m_activePatientEpisode->m_episode_start_date;
	m_activePatientEpisode->Update();

	m_ActivePatient->Edit();
	m_ActivePatient->m_patient_last_bill_date = m_activePatientEpisode->m_episode_start_date;
	m_ActivePatient->Update();  

	homehealth_printmode = homehealth_print_none;
}

// when the bill print is fired
void CHomeHealthView::OnCompletePrintingBill()
{

	if(homehealth_printmode == homehealth_print_initial_bill)
		OnCompleteInitialBillPrinting();
	else if(homehealth_printmode == homehealth_print_oversight_bill)
		OnCompleteOversightBillPrinting();
	
	this->PopulateEpisodeBilling();

	// set up the bit map based on the status
	if(m_patient_billing_status == EPISODE_BILLING_STATUS_NA)
		{
		HBITMAP hBitmap = ::LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_BITMAP_GREEN_SMALL));
		m_btnBillIndicator.SetBitmap(hBitmap);
		GetDlgItem(IDC_BUTTONBill)->EnableWindow(FALSE);
		}
	else 
		{
		HBITMAP hBitmap = ::LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_BITMAP_RED_SMALL));
		m_btnBillIndicator.SetBitmap(hBitmap);
		GetDlgItem(IDC_BUTTONBill)->EnableWindow(TRUE);
		}
	m_datePatientLastBill = m_ActivePatient->m_patient_last_bill_date;

	UpdateData(FALSE);

}



void CHomeHealthView::OnDtnDatetimechangePatientLastVisit(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void CHomeHealthView::OnOversightEdit()
{
	// TODO: Add your command handler code here
}


void CHomeHealthView::OnOversightDelete()
{

	// extract the oversight id : delete it from database.
	// go to the episode, and remove the oversight from the episode and adjust the minutes. accordingly. 
	// this 

	POSITION pos_selected = m_OverSightListCtrl.GetFirstSelectedItemPosition();
	if(pos_selected == NULL)
	{
		AfxMessageBox(_T("Oversight delete:No oversight is selected"));
		return;
	}
	int nItem = m_OverSightListCtrl.GetNextSelectedItem(pos_selected);

	long sel_oversight_id = m_OverSightListCtrl.GetItemData(nItem);
	CString szMsg;
	szMsg.Format(_T("Are you sure want to delete Oversight id: %lu"),sel_oversight_id);
	if(IDCANCEL == AfxMessageBox(szMsg,MB_OKCANCEL))
	{
		return;
	}

	Coversight_billing oversight;
	Cpatient_episode episode;

	if(0 == oversight.OpenForOversightDelete(sel_oversight_id))
		{
		if(oversight.m_patient_oversight_billed == TRUE)
			{
			AfxMessageBox(_T("Oversight is already billed. It can not be removed now"),MB_OK);
			return;
			}
		else
			{
			if(0 == episode.OpenForModifyWithEpisodeId(oversight.m_patient_episode_id))
				{
				episode.Edit();
				episode.m_episode_total_minutes -=oversight.m_patient_oversight_minute;
				episode.Update();
				episode.Close();
				}
			oversight.Delete();
			UpdateData(FALSE);
			}
		oversight.Close();
		}
	return;
}
