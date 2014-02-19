// PatientSearchDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HomeHealthApp.h"
#include "PatientSearchDlg.h"
#include "afxdialogex.h"
#include "patient_master.h"


// CPatientSearchDlg dialog

IMPLEMENT_DYNAMIC(CPatientSearchDlg, CDialogEx)

CPatientSearchDlg::CPatientSearchDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPatientSearchDlg::IDD, pParent)
	, szPatientFirstName(_T(""))
	, szPatientLastName(_T(""))
{

	//  szFirstName = 0;
}

CPatientSearchDlg::~CPatientSearchDlg()
{
}

void CPatientSearchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FIRSTNAME, szPatientFirstName);
	DDX_Text(pDX, IDC_EDIT_LASTNAME, szPatientLastName);
	DDX_Control(pDX, IDC_LIST_PATIENT_SEARCH, m_PatientListCtrl);
}


BEGIN_MESSAGE_MAP(CPatientSearchDlg, CDialogEx)
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CPatientSearchDlg::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_MORE_SEARCH, &CPatientSearchDlg::OnBnClickedButtonMoreSearch)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_PATIENT_SEARCH, &CPatientSearchDlg::OnNMDblclkListPatientSearch)
	ON_BN_CLICKED(IDOK, &CPatientSearchDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CPatientSearchDlg message handlers

int CPatientSearchDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}


BOOL CPatientSearchDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	// TODO:  Add extra initialization here
	int iReturn = 0;


	CRect rect;
	m_PatientListCtrl.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);

	m_PatientListCtrl.GetClientRect(&rect);
	int nColInterval = rect.Width()/5;

	m_PatientListCtrl.InsertColumn(0,_T("Patient ID"),LVCFMT_LEFT,nColInterval);
	m_PatientListCtrl.InsertColumn(1,_T("First name"),LVCFMT_LEFT,nColInterval);
	m_PatientListCtrl.InsertColumn(2,_T("Last name"),LVCFMT_LEFT,nColInterval);
	m_PatientListCtrl.InsertColumn(3,_T("Town"),LVCFMT_LEFT,nColInterval);
	m_PatientListCtrl.InsertColumn(4,_T("State"),LVCFMT_LEFT,nColInterval);
	CHomeHealthDatabase* pDB = ((CHomeHealthApp*)AfxGetApp())->GetHomeHealthDatabase();
	Cpatient_master patient(pDB->GetDatabase());

	if(patient.Open() == 0)
	{
		int item = 0;
		LVITEM lvitem;
		CString strItem;

		while(patient.IsEOF() == FALSE)
		{
			lvitem.mask = LVIF_TEXT;
			strItem.Format(_T("%u"),patient.m_patient_id);

			lvitem.iItem = item;
			lvitem.iSubItem = 0;
			lvitem.pszText = (LPTSTR)(LPCTSTR)(strItem);
			m_PatientListCtrl.InsertItem(&lvitem);
			m_PatientListCtrl.SetItemData(item,patient.m_patient_id);



			strItem.Format(_T("%s"),patient.m_patient_firstname);
			lvitem.iSubItem = 1;
			lvitem.pszText= (LPTSTR)(LPCTSTR)(strItem);
			m_PatientListCtrl.SetItem(&lvitem);

			strItem.Format(_T("%s"),patient.m_patient_lastname);
			lvitem.iSubItem = 2;
			lvitem.pszText= (LPTSTR)(LPCTSTR)(strItem);
			m_PatientListCtrl.SetItem(&lvitem);

			strItem.Format(_T("%s"),patient.m_patient_town);
			lvitem.iSubItem = 3;
			lvitem.pszText= (LPTSTR)(LPCTSTR)(strItem);
			m_PatientListCtrl.SetItem(&lvitem);

			strItem.Format(_T("%s"),patient.m_patient_state);
			lvitem.iSubItem = 4;
			lvitem.pszText= (LPTSTR)(LPCTSTR)(strItem);
			m_PatientListCtrl.SetItem(&lvitem);


			patient.MoveNext();
			item ++;

		}
	}
	patient.Close();

	// EXCEPTION: OCX Property Pages should return FALSE
	return TRUE;
}




void CPatientSearchDlg::OnBnClickedButtonSearch()
{

	CHomeHealthDatabase* pDB = ((CHomeHealthApp*)AfxGetApp())->GetHomeHealthDatabase();
	Cpatient_master patient(pDB->GetDatabase());

	m_PatientListCtrl.DeleteAllItems();
	UpdateData(TRUE);
	if (0 == patient.OpenWithSearchOnName(szPatientFirstName,szPatientLastName))
	{
		int item = 0;
		LVITEM lvitem;
		CString strItem;

		while(patient.IsEOF() == FALSE)
		{
			lvitem.mask = LVIF_TEXT;
			strItem.Format(_T("%u"),patient.m_patient_id);

			lvitem.iItem = item;
			lvitem.iSubItem = 0;
			lvitem.pszText = (LPTSTR)(LPCTSTR)(strItem);
			m_PatientListCtrl.InsertItem(&lvitem);
			m_PatientListCtrl.SetItemData(item,patient.m_patient_id);



			strItem.Format(_T("%s"),patient.m_patient_firstname);
			lvitem.iSubItem = 1;
			lvitem.pszText= (LPTSTR)(LPCTSTR)(strItem);
			m_PatientListCtrl.SetItem(&lvitem);

			strItem.Format(_T("%s"),patient.m_patient_lastname);
			lvitem.iSubItem = 2;
			lvitem.pszText= (LPTSTR)(LPCTSTR)(strItem);
			m_PatientListCtrl.SetItem(&lvitem);

			strItem.Format(_T("%s"),patient.m_patient_town);
			lvitem.iSubItem = 3;
			lvitem.pszText= (LPTSTR)(LPCTSTR)(strItem);
			m_PatientListCtrl.SetItem(&lvitem);

			strItem.Format(_T("%s"),patient.m_patient_state);
			lvitem.iSubItem = 4;
			lvitem.pszText= (LPTSTR)(LPCTSTR)(strItem);
			m_PatientListCtrl.SetItem(&lvitem);


			patient.MoveNext();
			item ++;

		}
		patient.Close();
	}

}


void CPatientSearchDlg::OnBnClickedButtonMoreSearch()
{
	// TODO: Add your control notification handler code here
}



void CPatientSearchDlg::OnNMDblclkListPatientSearch(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
		*pResult = 0;
	// TODO: Add your control notification handler code here
	m_nSelectedPatientId = m_PatientListCtrl.GetItemData(pNMItemActivate->iItem);
	*pResult = 0;

	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();

}




void CPatientSearchDlg::OnBnClickedOk()
{
	POSITION pos;
	pos = m_PatientListCtrl.GetFirstSelectedItemPosition();

	if(pos == NULL)
	{
		AfxMessageBox(_T("No Patient is Selected"));
		return;
	}
	else
	{
		int nItem = m_PatientListCtrl.GetNextSelectedItem(pos);
		m_nSelectedPatientId = m_PatientListCtrl.GetItemData(nItem);
	}

	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}
