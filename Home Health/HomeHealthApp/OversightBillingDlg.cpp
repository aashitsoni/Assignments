// OversightBillingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HomeHealthApp.h"
#include "HomeHealthDoc.h"
#include "HomeHealthView.h"
#include "patient_master.h"
#include "patient_episode.h"
#include "oversight_billing.h"
#include "OversightBillingDlg.h"
#include "afxdialogex.h"

// COversightBillingDlg dialog

IMPLEMENT_DYNAMIC(COversightBillingDlg, CDialogEx)

COversightBillingDlg::COversightBillingDlg(void* pView
										   ,Cpatient_master* patient
										   ,Cpatient_episode* episode
										   ,CWnd* pParent /*=NULL*/)
	: CDialogEx(COversightBillingDlg::IDD, pParent)
	,m_patient(patient)
	,m_episode(episode)
	,m_pView(pView)
{

}

COversightBillingDlg::~COversightBillingDlg()
{
	if(m_oversight)
		delete m_oversight;
}

void COversightBillingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OVERSIGHT_LIST, m_oversightList);
}


BEGIN_MESSAGE_MAP(COversightBillingDlg, CDialogEx)
END_MESSAGE_MAP()


// COversightBillingDlg message handlers

CString COversightBillingDlg::GetCurrentMonth()
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
	

void COversightBillingDlg::PopulateOversightBillingList()
{
	CRect rect;
	m_oversightList.GetClientRect(&rect);
	int nColInterval = rect.Width()/6;
	int item = 0;
	LVITEM lvitem;
	CString strItem;

	m_oversightList.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);

	m_oversightList.InsertColumn(0,_T("Oversight CPO code"),LVCFMT_LEFT,nColInterval*3);
	m_oversightList.InsertColumn(1,_T("Date"),LVCFMT_LEFT,nColInterval);
	m_oversightList.InsertColumn(2,_T("Minutes"),LVCFMT_LEFT,nColInterval);
	m_oversightList.InsertColumn(3,_T("Billed"),LVCFMT_LEFT,nColInterval);

	while(m_oversight->IsEOF() == FALSE)
	{
		lvitem.mask = LVIF_TEXT;
		((CHomeHealthView*)m_pView)->findCPOCodeName(m_oversight->m_patient_oversight_cpo_code,strItem);

		lvitem.iItem = item;
		lvitem.iSubItem = 0;
		lvitem.pszText = (LPTSTR)(LPCTSTR)(strItem);
		m_oversightList.InsertItem(&lvitem);

		strItem.Format(_T("%02d/%02d/%d"),m_oversight->m_patient_oversight_date.GetMonth()
										 ,m_oversight->m_patient_oversight_date.GetDay()
										 ,m_oversight->m_patient_oversight_date.GetYear());
		lvitem.iSubItem = 1;
		lvitem.pszText= (LPTSTR)(LPCTSTR)(strItem);
		m_oversightList.SetItem(&lvitem);

		strItem.Format(_T("%d"),m_oversight->m_patient_oversight_minute);
		lvitem.iSubItem = 2;
		lvitem.pszText= (LPTSTR)(LPCTSTR)(strItem);
		m_oversightList.SetItem(&lvitem);

		if(m_oversight->m_patient_oversight_billed == FALSE)
			strItem.Format(_T("No"));
		else
			strItem.Format(_T("Yes"));

		lvitem.iSubItem = 3;
		lvitem.pszText= (LPTSTR)(LPCTSTR)(strItem);
		m_oversightList.SetItem(&lvitem);

		m_oversight->MoveNext();
		item++;
	}
}

BOOL COversightBillingDlg::OnInitDialog()
{
	CString szText;
	CDialogEx::OnInitDialog();
	CHomeHealthApp* pApp = (CHomeHealthApp*) AfxGetApp();

	m_oversight = new Coversight_billing();

	if (m_oversight->OpenForOversightBilling(m_episode->m_patient_episode_code) !=0)
	{
		AfxMessageBox(L"Error Opening oversight billing records",MB_OK);
		return FALSE;
	}
	GetDlgItem(IDC_HH_AGENCY)->SetWindowTextW(m_episode->m_episode_hh_agency_name);
	szText.Format(L"%s %s",m_patient->m_patient_firstname,m_patient->m_patient_lastname);

	GetDlgItem(IDC_NAME)->SetWindowTextW(szText);

	//Patient DOB
	szText.Format(L"%02d/%02d/%d",m_patient->m_patient_dob.GetMonth()
								  ,m_patient->m_patient_dob.GetDay()
								  ,m_patient->m_patient_dob.GetYear());
	GetDlgItem(IDC_DOB)->SetWindowTextW(szText);

	//Patient episode Activity type
	if(m_episode->m_episode_type.CompareNoCase(L"Recertification") == 0)
	{
		szText.Format(L"%s (G0179)",m_episode->m_episode_type);
	}
	else
	{
		szText.Format(L"%s (G0180)",m_episode->m_episode_type);
	}
	GetDlgItem(IDC_ACTIVITY)->SetWindowTextW(szText);

	
	GetDlgItem(IDC_MONTH)->SetWindowTextW(GetCurrentMonth());

	szText.Format(L"%02d/%02d/%d",m_episode->m_episode_last_visit.GetMonth()
								,m_episode->m_episode_last_visit.GetDay()
								,m_episode->m_episode_last_visit.GetYear());
	GetDlgItem(IDC_LAST_SEEN)->SetWindowTextW(szText);

	szText.Format(L"%02d/%02d/%d-%02d/%02d/%d",m_episode->m_episode_start_date.GetMonth()
											  ,m_episode->m_episode_start_date.GetDay()
											  ,m_episode->m_episode_start_date.GetYear()
											  ,m_episode->m_episode_end_date.GetMonth()
											  ,m_episode->m_episode_end_date.GetDay()
											  ,m_episode->m_episode_end_date.GetYear());


	PopulateOversightBillingList();

	szText.Format(_T("%d"),m_episode->m_episode_total_minutes);
	GetDlgItem(IDC_TOTAL_MINS)->SetWindowTextW(szText);

	szText.Format(_T("%02d/%02d/%d"),pApp->m_localTime.wMonth,
									 pApp->m_localTime.wDay,
									 pApp->m_localTime.wYear);
	
	GetDlgItem(IDC_BILL_DATE)->SetWindowTextW(szText);

	m_oversight->Close();

	return TRUE;  // return TRUE unless you set the focus to a control
}


