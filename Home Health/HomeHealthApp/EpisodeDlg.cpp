// EpisodeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HomeHealthApp.h"
#include "patient_episode.h"
#include "patient_master.h"
#include "EpisodeDlg.h"
#include "afxdialogex.h"
#include "hh_agency_master.h"

// CEpisodeDlg dialog

IMPLEMENT_DYNAMIC(CEpisodeDlg, CDialogEx)

CEpisodeDlg::CEpisodeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEpisodeDlg::IDD, pParent)
	, m_patient_name(_T(""))
	, m_szDxCodes(_T(""))
{

}


CEpisodeDlg::CEpisodeDlg(Cpatient_episode* episode,Cpatient_master* patient,SYSTEMTIME st,CWnd* pParent /*=NULL*/)
	: CDialogEx(CEpisodeDlg::IDD, pParent)
	, m_episode_start(st)
	, m_episode_end(st)
	, m_szDxCodes(_T(""))
	, m_selectedPatient(patient)
	, m_selectedEpisode(episode)
{
	m_episode_end+=(60*24*60*60); // Add two months to the episode. by default
}

CEpisodeDlg::~CEpisodeDlg()
{
}

void CEpisodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PATIENT_NAME, m_patient_name);
	DDX_DateTimeCtrl(pDX, IDC_EPISODE_START, m_episode_start);
	DDX_DateTimeCtrl(pDX, IDC_EPISODEEND, m_episode_end);
	DDX_Control(pDX, IDC_COMBO_EPISODE_TYPE, m_episode_type);
	DDX_Control(pDX, IDC_COMBO_HHAGENCY, m_comboHHAgency);
	DDX_Text(pDX, IDC_DXCODES, m_szDxCodes);
}


BEGIN_MESSAGE_MAP(CEpisodeDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CEpisodeDlg::OnBnClickedOk)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_EPISODE_START, &CEpisodeDlg::OnDtnDatetimechangeEpisodeStart)
	ON_NOTIFY(DTN_USERSTRING, IDC_EPISODE_START, &CEpisodeDlg::OnDtnUserstringEpisodeStart)
END_MESSAGE_MAP()


BOOL CEpisodeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	GetDlgItem(IDC_EPISODEEND)->EnableWindow(FALSE);

	CHomeHealthApp*pApp = (CHomeHealthApp*)AfxGetApp();
	CHomeHealthDatabase* pDB = pApp->GetHomeHealthDatabase();

	Chh_agency_master hh_agency(pDB->GetDatabase());
	CString szFirstString;
	m_patient_name = m_selectedPatient->m_patient_firstname + L" " + m_selectedPatient->m_patient_lastname;

	if(hh_agency.Open() == TRUE)
	{
		szFirstString = hh_agency.m_HH_Agency_code_name;
		while(hh_agency.IsEOF() == FALSE)
		{
			m_comboHHAgency.AddString(hh_agency.m_HH_Agency_code_name);
			hh_agency.MoveNext();
		}

		hh_agency.Close();
	}
	
	m_episode_type.SelectString(0,_T("Initial"));
	m_comboHHAgency.SelectString(0,szFirstString);

	UpdateData(FALSE);

	return TRUE;
}



// CEpisodeDlg message handlers


long CEpisodeDlg::findHHAgencyCode(CString& hh_agency_name)
{

	CHomeHealthApp*pApp = (CHomeHealthApp*)AfxGetApp();
	CHomeHealthDatabase* pDB = pApp->GetHomeHealthDatabase();

	Chh_agency_master hh_agency(pDB->GetDatabase());
	long hh_agency_id = 0;

	if(hh_agency.Open() == 0)
	{
		while(hh_agency.IsEOF() == FALSE)
		{
			if(hh_agency_name == hh_agency.m_HH_Agency_code_name)
			{
				hh_agency_id = hh_agency.m_HH_Agency_code_id;
				break;
			}
			hh_agency.MoveNext();
		}
		hh_agency.Close();
	}
	return hh_agency_id;

}

void CEpisodeDlg::OnBnClickedOk()
{
	unsigned long patient_id = m_selectedEpisode->m_patient_id;
	int nSelectedHHCode = 0;
	int selectedRec = 0;
	CDBVariant varBookmark;
	UpdateData(TRUE);

	
	if(m_selectedEpisode->m_episode_active == TRUE)
	{
		m_selectedEpisode->Edit();
		m_selectedEpisode->m_episode_active = FALSE;
		m_selectedEpisode->Update();
	}

	if(m_szDxCodes.IsEmpty())
	{
		if(IDYES != AfxMessageBox(_T("DxCodes are not filled in, Are you sure want to continue?"),MB_YESNO))
			return;

	}

	m_selectedEpisode->AddNew();

	int sel = m_episode_type.GetCurSel();
	m_selectedEpisode->m_patient_id = m_selectedPatient->m_patient_id;
	m_selectedEpisode->m_episode_start_date = m_episode_start;
	m_selectedEpisode->m_episode_end_date = m_episode_end;
	m_selectedEpisode->m_episode_total_minutes = 0;
	m_selectedEpisode->m_episode_active = TRUE; // set based on the current date and episode time selected
	m_selectedEpisode->m_episode_last_visit = 0;
	nSelectedHHCode = m_comboHHAgency.GetCurSel();
	m_comboHHAgency.GetLBText(nSelectedHHCode,m_selectedEpisode->m_episode_hh_agency_name);
	m_selectedEpisode->m_episode_hh_agency_code = findHHAgencyCode(m_selectedEpisode->m_episode_hh_agency_name);
	m_selectedEpisode->m_episode_dx_codes = m_szDxCodes;

	// set the billing dates to start of the episode. - for the timebeing, once there is more claritiy
	// we need to revise this logic
//	episode.m_episode_billing_status = EPISODE_BILLING_STATUS_NA; // set the billing status to initial state
	m_selectedEpisode->m_episode_billing_status = EPISODE_BILLING_STATUS_INITIAL;


	m_selectedEpisode->m_episode_last_bill_date = m_episode_start;
	m_selectedEpisode->m_episode_oversight_bill_date = m_episode_start;

	m_episode_type.GetLBText(sel,m_selectedEpisode->m_episode_type);

	if(FALSE == m_selectedEpisode->Update())
	{
		AfxMessageBox(_T("Not able to update the database"));
		return CDialogEx::OnCancel();
	}
	m_selectedEpisode->SetAbsolutePosition(-1);


	m_addedEpisode_id = m_selectedEpisode->m_patient_episode_code;

	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}



void CEpisodeDlg::OnDtnDatetimechangeEpisodeStart(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	*pResult = 0;
	// TODO: Add your control notification handler code here

	m_episode_end=pDTChange->st;
	m_episode_end += EPISODE_TOTAL_TIME; // Add 59 days for the episode. It is two months period

	CDateTimeCtrl* wndEndDate = (CDateTimeCtrl*)GetDlgItem(IDC_EPISODEEND);
	wndEndDate->SetTime(&m_episode_end);

	*pResult = 0;
}

void CEpisodeDlg::OnDtnUserstringEpisodeStart(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	*pResult = 0;
	// TODO: Add your control notification handler code here

	m_episode_end=pDTChange->st;
	m_episode_end += EPISODE_TOTAL_TIME; // Add 59 days for the episode. It is two months period

	CDateTimeCtrl* wndEndDate = (CDateTimeCtrl*)GetDlgItem(IDC_EPISODEEND);
	wndEndDate->SetTime(&m_episode_end);

	*pResult = 0;
}


