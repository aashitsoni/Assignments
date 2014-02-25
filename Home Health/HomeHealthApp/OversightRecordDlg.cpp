// OversightBillingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HomeHealthApp.h"
#include "oversightRecordDlg.h"
#include "afxdialogex.h"
#include "oversight_billing.h"
#include "HomeHealthDatabase.h"
#include "oversight_cpo_code_master.h"

// COversightBillingDlg dialog

IMPLEMENT_DYNAMIC(COversightRecordDlg, CDialogEx)

COversightRecordDlg::COversightRecordDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COversightRecordDlg::IDD, pParent)
	, m_Oversight_minutes(_T(""))
	, m_szEpisode_id(_T(""))
	, m_szEpisodeStartDate(_T(""))
	, m_szEpisodeEndDate(_T(""))
	, m_szCPODescr(_T(""))
	, m_szDiagnosis(_T(""))
{

		CTime ctLocalTime(((CHomeHealthApp* )AfxGetApp())->m_localTime);
		m_OversightDateTime = ctLocalTime;
	
		m_patient_id = -1;
		m_episode_id = -1;
}

COversightRecordDlg::COversightRecordDlg(long patient_id,long episode_id,CTime& episode_start_date,CTime& episode_end_date,CWnd* pParent)
	: CDialogEx(COversightRecordDlg::IDD, pParent)
	, m_Oversight_minutes(_T(""))
	, m_szEpisode_id(_T(""))
	, m_szEpisodeStartDate(_T(""))
	, m_szEpisodeEndDate(_T(""))
	, m_szCPODescr(_T(""))
	, m_szDiagnosis(_T(""))
{
		CTime ctLocalTime(((CHomeHealthApp* )AfxGetApp())->m_localTime);

		m_OversightDateTime = ctLocalTime;
		m_patient_id = patient_id;
		m_episode_id = episode_id;
		m_ct_episode_start = episode_start_date;
		m_ct_episode_end = episode_end_date;

		m_szEpisodeStartDate.Format(_T("%d/%d/%d"),episode_start_date.GetMonth(),episode_start_date.GetDay(),episode_start_date.GetYear());
		m_szEpisodeEndDate.Format(_T("%d/%d/%d"),episode_end_date.GetMonth(),episode_end_date.GetDay(),episode_end_date.GetYear());

}



COversightRecordDlg::~COversightRecordDlg()
{
}

void COversightRecordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_EPISODEID, m_szEpisode_id);
	DDX_Text(pDX, IDC_EDIT_EPISODE_START_DATE, m_szEpisodeStartDate);
	DDX_Text(pDX, IDC_EDIT_EPISODE_END_DATE, m_szEpisodeEndDate);

	DDX_DateTimeCtrl(pDX, IDC_DATETIME_OVERSIGHT, m_OversightDateTime);
	DDX_Text(pDX, IDC_EDIT_OVERSIGHT_MINS, m_Oversight_minutes);
	DDX_Control(pDX, IDC_COMBO_CPO_CODE, m_ComboBoxCPOBox);
	DDX_Text(pDX, IDC_CPO_CODE_DESCR, m_szCPODescr);
}


BEGIN_MESSAGE_MAP(COversightRecordDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &COversightRecordDlg::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_CPO_CODE, &COversightRecordDlg::OnCbnSelchangeComboCpoCode)
END_MESSAGE_MAP()


// COversightBillingDlg message handlers


long COversightRecordDlg::findCPOCode(CString& szCPOCode)
{
	CHomeHealthApp*pApp = (CHomeHealthApp*)AfxGetApp();
	CHomeHealthDatabase* pDB = pApp->GetHomeHealthDatabase();
	Coversight_cpo_code_master cpo_code_master(pDB->GetDatabase());

	long cpo_code = -1;
	cpo_code_master.Open();
	while(cpo_code_master.IsEOF() == FALSE)
	{
		if(cpo_code_master.m_oversight_cpo_code_name == szCPOCode)
		{
			cpo_code = cpo_code_master.m_oversight_cpo_code_id;
			break;
		}

		cpo_code_master.MoveNext();
	}
	cpo_code_master.Close();
	
	return cpo_code; 
}


BOOL COversightRecordDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CHomeHealthApp*pApp = (CHomeHealthApp*)AfxGetApp();
	CHomeHealthDatabase* pDB = pApp->GetHomeHealthDatabase();
	CString szFirstString;

	m_szEpisode_id.Format(_T("%ld"), m_episode_id);

	Coversight_cpo_code_master cpo_code_master(pDB->GetDatabase());
	if( TRUE == cpo_code_master.Open())
	{
		szFirstString = cpo_code_master.m_oversight_cpo_code_name;
		while(cpo_code_master.IsEOF() == FALSE)
		{
			m_ComboBoxCPOBox.AddString(cpo_code_master.m_oversight_cpo_code_name);
			cpo_code_master.MoveNext();
		}
		cpo_code_master.Close();
	}

	m_ComboBoxCPOBox.SelectString(0,szFirstString);

	UpdateData(FALSE);
	
	return TRUE;
}


void COversightRecordDlg::OnCbnSelchangeComboCpoCode()
{
	int sel = m_ComboBoxCPOBox.GetCurSel();
	CString szText;

	m_ComboBoxCPOBox.GetLBText(sel,szText);
	if(szText == _T("Others, please describe"))
	{
		GetDlgItem(IDC_CPO_CODE_DESCR)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_CPO_CODE_DESCR)->EnableWindow(FALSE);
	}

	// TODO: Add your control notification handler code here
}

void COversightRecordDlg::OnBnClickedOk()
{
	CHomeHealthApp*pApp = (CHomeHealthApp*)AfxGetApp();
	CHomeHealthDatabase* pDB = pApp->GetHomeHealthDatabase();
	Coversight_billing  billing(pDB->GetDatabase());
	TCHAR min[5];
	CString szCPOCode;
	long iMinutes = 0,cpo_code = 0;

	if(m_patient_id == -1 || m_episode_id == -1)
	{
		AfxMessageBox(_T("Oversight Record is not properly initialized"),MB_OK,MB_ICONERROR);
		CDialogEx::OnCancel();
		return;
	}

	UpdateData(TRUE);

	if(m_OversightDateTime < m_ct_episode_start || m_OversightDateTime > m_ct_episode_end)
	{
		CString szMsg;
		szMsg.Format(_T("Oversight Date shall be in range: %s - %s"),m_szEpisodeStartDate,m_szEpisodeEndDate);
		AfxMessageBox(szMsg,MB_OK,MB_ICONERROR);
		GetDlgItem(IDC_DATETIME_OVERSIGHT)->SetFocus();
		return;
	}

	iMinutes = _ttoi(m_Oversight_minutes);
	if(iMinutes <= 0)
	{
		AfxMessageBox(_T("Invalid Oversight billing minutes"),MB_OK,MB_ICONERROR);
		GetDlgItem(IDC_EDIT_OVERSIGHT_MINS)->SetFocus();
		return;
	}

	// select the CPO code and descriptions
	int sel = m_ComboBoxCPOBox.GetCurSel();
	m_ComboBoxCPOBox.GetLBText(sel,szCPOCode);
	cpo_code = findCPOCode(szCPOCode);

	if(szCPOCode == _T("Others, please describe"))
	{
		GetDlgItem(IDC_CPO_CODE_DESCR)->GetWindowText(szCPOCode);
	}


	billing.OpenForAdd();
	billing.AddNew();

	// initialize the values
	billing.m_patient_oversight_date = m_OversightDateTime;


	billing.m_patient_oversight_minute = iMinutes;
	billing.m_patient_id = m_patient_id;
	billing.m_patient_episode_id = m_episode_id;
	
	billing.m_patient_oversight_cpo_code = cpo_code;
	billing.m_patient_oversight_cpo_desc = szCPOCode;

	m_Oversight_billing_mintues = billing.m_patient_oversight_minute;

	billing.Update();


	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}

