#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CPatientSearchDlg dialog

class CPatientSearchDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPatientSearchDlg)
	// First name	

public:
	CPatientSearchDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPatientSearchDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_PATIENT_OPEN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int		m_nSelectedPatientId;
	CListCtrl m_PatientListCtrl;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnBnClickedButtonMoreSearch();
	afx_msg void OnNMDblclkListPatientSearch(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	CString szPatientFirstName;
	CString szPatientLastName;
};
