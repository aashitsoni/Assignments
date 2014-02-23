// AddPatientDlg.cpp : implementation file
// to make one revisition here ; aashit soni

#include "stdafx.h"
#include "HomeHealthApp.h"
#include "AddPatientDlg.h"
#include "afxdialogex.h"
#include "patient_master.h"

// CAddPatientDlg dialog

IMPLEMENT_DYNAMIC(CAddPatientDlg, CDialogEx)

CAddPatientDlg::CAddPatientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddPatientDlg::IDD, pParent)
	, m_dlgAddressApartment(_T(""))
	, m_dlgCellPhone(_T(""))
	, m_dlgCommunicationPhone(_T(""))
	, m_dlgCountry(_T(""))
	, m_dlgFirstName(_T(""))
	, m_dlgHomePhone(_T(""))
	, m_dlgLastName(_T(""))
	, m_dlgMiddleName(_T(""))
	, m_dlgStreet(_T(""))
	, m_dlgTown(_T(""))
	, m_dlgWorkPhone(_T(""))
{

}

CAddPatientDlg::~CAddPatientDlg()
{
}

void CAddPatientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PAT_ADD_APT, m_dlgAddressApartment);
	DDX_Text(pDX, IDC_PAT_ADD_CELL_PHONE, m_dlgCellPhone);
	DDX_Text(pDX, IDC_PAT_ADD_COMMUNICATION_PHONE, m_dlgCommunicationPhone);
	DDX_Text(pDX, IDC_PAT_ADD_COUNTRY, m_dlgCountry);
	DDX_Text(pDX, IDC_PAT_ADD_FIRST_NAME, m_dlgFirstName);
	DDX_Text(pDX, IDC_PAT_ADD_HOME_PHONE, m_dlgHomePhone);
	DDX_Text(pDX, IDC_PAT_ADD_LAST_NAME, m_dlgLastName);
	DDX_Text(pDX, IDC_PAT_ADD_MIDDLE_NAME, m_dlgMiddleName);
	DDX_Control(pDX, IDC_PAT_ADD_SALUTATION, m_dlgSalutation);
	DDX_Control(pDX, IDC_PAT_ADD_STATE, m_dlgState);
	DDX_Text(pDX, IDC_PAT_ADD_STREET, m_dlgStreet);
	DDX_Text(pDX, IDC_PAT_ADD_TOWN, m_dlgTown);
	DDX_Text(pDX, IDC_PAT_ADD_WORK_PHONE, m_dlgWorkPhone);
}


BEGIN_MESSAGE_MAP(CAddPatientDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAddPatientDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CAddPatientDlg message handlers


BOOL CAddPatientDlg::ValidatePatientInformation()
{

	return TRUE;

}

void CAddPatientDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	// validate the data and then ask use if he wants to create a new record for the patient.
	UpdateData(TRUE);

	if( FALSE == ValidatePatientInformation())
	{
		return;

	}


	if(IDOK != AfxMessageBox(L"Confirm for creating new patient record",MB_OKCANCEL) )
	{
		CDialogEx::OnCancel();
		return;
	}

	// Add the data into Patient registration table and close the table
	Cpatient_master patient_master;
	if (patient_master.OpenForAdd() == -1)
	{
		AfxMessageBox(L"Patient database problem",MB_OK);
		CDialogEx::OnCancel();
		return;
	}
	patient_master.AddNew();
	int sel = 0;
	patient_master.m_patient_firstname = m_dlgFirstName;
	patient_master.m_patient_lastname = m_dlgLastName;
	patient_master.m_patient_address = m_dlgStreet +L" "+ m_dlgAddressApartment;
	patient_master.m_patient_town = m_dlgTown;

	sel = m_dlgState.GetCurSel();
	m_dlgState.GetLBText(sel,patient_master.m_patient_state);

	patient_master.m_patient_middlename = m_dlgMiddleName;

	sel = m_dlgSalutation.GetCurSel();
	m_dlgSalutation.GetLBText(sel,patient_master.m_patient_salutation);

	patient_master.m_patient_home_phone = m_dlgHomePhone;
	patient_master.m_patient_cell_phone = m_dlgCellPhone;
	patient_master.m_patient_work_phone = m_dlgWorkPhone;
	patient_master.m_patient_communication_phone = m_dlgCommunicationPhone;
	patient_master.m_patient_country = m_dlgCountry;
	patient_master.m_patient_registration_date = ((CHomeHealthApp*)AfxGetApp())->m_localTime;
	patient_master.m_patient_last_visit = patient_master.m_patient_registration_date;
	patient_master.m_patient_last_bill_date = patient_master.m_patient_registration_date; // just assign last bill date as registration date
	patient_master.m_patient_billable_minutes = 0;
	patient_master.m_patient_oversight_bill_date = 0;
	patient_master.Update();

	patient_master.SetAbsolutePosition(-1);

	m_newPatientId = patient_master.m_patient_id;

	patient_master.Close();
	CDialogEx::OnOK();
}
