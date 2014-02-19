#pragma once
#include "afxwin.h"


// CAddPatientDlg dialog

class CAddPatientDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddPatientDlg)

public:
	CAddPatientDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAddPatientDlg();

// Dialog Data
	enum { IDD = IDD_ADD_PATIENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_dlgAddressApartment;
	CString m_dlgCellPhone;
	CString m_dlgCommunicationPhone;
	CString m_dlgCountry;
	CString m_dlgFirstName;
	CString m_dlgHomePhone;
	CString m_dlgLastName;
	CString m_dlgMiddleName;
	CComboBox m_dlgSalutation;
	CComboBox m_dlgState;
	CString m_dlgStreet;
	CString m_dlgTown;
	CString m_dlgWorkPhone;
	afx_msg void OnBnClickedOk();

	long m_newPatientId;
private:
	BOOL ValidatePatientInformation();

};
