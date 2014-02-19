#pragma once
#include "afxdtctl.h"
#include "afxwin.h"


// CEpisodeDlg dialog

class CEpisodeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEpisodeDlg)
	long findHHAgencyCode(CString& hh_agency_name);	
public:
	CEpisodeDlg(CWnd* pParent = NULL);   // standard constructor
	CEpisodeDlg(Cpatient_episode *episode,Cpatient_master* patient,SYSTEMTIME st,CWnd* pParent = NULL);
	virtual ~CEpisodeDlg();
	unsigned long m_addedEpisode_id;
	Cpatient_episode *m_selectedEpisode;
	Cpatient_master *m_selectedPatient;

// Dialog Data
	enum { IDD = IDD_EPISODE_ADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:

	CString m_patient_name;
	CTime m_episode_start;
	CTime m_episode_end;
	CComboBox m_episode_type;
	afx_msg void OnBnClickedOk();
	CComboBox m_comboHHAgency;
	CString m_szDxCodes;
	afx_msg void OnDtnDatetimechangeEpisodeStart(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnDtnUserstringEpisodeStart(NMHDR *pNMHDR, LRESULT *pResult);
};
