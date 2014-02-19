#pragma once
#include "afxwin.h"


// CInitialBillingDlg dialog

class CInitialBillingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInitialBillingDlg)

public:
	CInitialBillingDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CInitialBillingDlg();
	CInitialBillingDlg(Cpatient_master*,Cpatient_episode*);


// Dialog Data
	enum { IDD = IDD_INIT_BILLING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	Cpatient_master* m_selectedPatient;
	Cpatient_episode* m_selectedEpisode;
public:
	virtual BOOL OnInitDialog();
	CString m_patientname;
	CString m_hhAgency;
	CString m_episode_from;
	CString m_episode_to;
	CListBox m_dx_codes;
};
