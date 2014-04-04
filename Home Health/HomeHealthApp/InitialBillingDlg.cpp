// InitialBillingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HomeHealthApp.h"
#include "patient_master.h"
#include "patient_episode.h"
#include "patient_billing.h"
#include "InitialBillingDlg.h"
#include "afxdialogex.h"



// CInitialBillingDlg dialog

IMPLEMENT_DYNAMIC(CInitialBillingDlg, CDialogEx)

CInitialBillingDlg::CInitialBillingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInitialBillingDlg::IDD, pParent)
	, m_patientname(_T(""))
	, m_hhAgency(_T(""))
	, m_episode_from(_T(""))
	, m_episode_to(_T(""))
{

}

CInitialBillingDlg::~CInitialBillingDlg()
{
}

CInitialBillingDlg::	CInitialBillingDlg(Cpatient_master* patient,Cpatient_episode* episode,Cpatient_billing* patient_billing)
	:CDialogEx(CInitialBillingDlg::IDD,NULL),
	m_selectedPatient(patient),
	m_selectedEpisode(episode),
	m_selectedPatientBill(patient_billing)
{
}


void CInitialBillingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PATIENTNAME, m_patientname);
	DDX_Text(pDX, IDC_HHAGENCY, m_hhAgency);
	DDX_Text(pDX, IDC_EOS_FROM, m_episode_from);
	DDX_Text(pDX, IDC_EOS_TO, m_episode_to);
	//  DDX_Control(pDX, IDC_DXCODES_LIST, m_dx_codes);
	DDX_Text(pDX, IDC_DX_EDITBOX, m_dx_codes);
}


BEGIN_MESSAGE_MAP(CInitialBillingDlg, CDialogEx)
END_MESSAGE_MAP()


// CInitialBillingDlg message handlers
BOOL CInitialBillingDlg::OnInitDialog()
{

	CDialogEx::OnInitDialog();
	// populate the dialog with the billing informaiton

	CString strText;

	strText.LoadStringW(IDS_TITLE_NAME);
	this->GetDlgItem(IDC_DOCTOR_NAME)->SetWindowTextW(strText);

	strText.LoadStringW(IDS_DOCTOR_DEPT);
	this->GetDlgItem(IDC_DOCTOR_DEPT)->SetWindowTextW(strText);

	strText.LoadStringW(IDS_DOCTOR_ADDR1);
	this->GetDlgItem(IDC_DOCTOR_ADDR)->SetWindowTextW(strText);

	strText.LoadStringW(IDS_DOCTOR_ADDR2);
	this->GetDlgItem(IDC_DOCTOR_TOWN)->SetWindowTextW(strText);

	strText.LoadStringW(IDS_DOCTOR_PHONE);
	this->GetDlgItem(IDC_DOCTOR_PHONE)->SetWindowTextW(strText);

	m_patientname = m_selectedPatient->m_patient_firstname + " " + m_selectedPatient->m_patient_lastname;
	m_episode_from.Format(L"%d/%d/%d",m_selectedEpisode->m_episode_start_date.GetMonth(),
									m_selectedEpisode->m_episode_start_date.GetDay(),
									m_selectedEpisode->m_episode_start_date.GetYear());

	m_episode_to.Format(L"%d/%d/%d",m_selectedEpisode->m_episode_end_date.GetMonth(),
									m_selectedEpisode->m_episode_end_date.GetDay(),
									m_selectedEpisode->m_episode_end_date.GetYear());

	m_hhAgency = m_selectedEpisode->m_episode_hh_agency_name;
	m_dx_codes = m_selectedEpisode->m_episode_dx_codes;

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
}
