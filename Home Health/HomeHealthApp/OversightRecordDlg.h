#pragma once
#include "atlcomtime.h"
#include "afxwin.h"



// COversightBillingDlg dialog

class COversightRecordDlg : public CDialogEx
{
	DECLARE_DYNAMIC(COversightRecordDlg)
	long findCPOCode(CString& szCPOCode);
	CTime m_ct_episode_start;
	CTime m_ct_episode_end;

public:
	COversightRecordDlg(CWnd* pParent = NULL);   // standard constructor
	COversightRecordDlg(long patient_id,long episode_id,CTime& episode_start_date,CTime& episode_end_date,CWnd* pParent);   // customize constructor

	virtual ~COversightRecordDlg();

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();

// Dialog Data
	enum { IDD = IDD_DIALOG_OVERSIGHT_RECORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	long		m_patient_id;
	long		m_episode_id;
	int			m_Oversight_billing_mintues;

	CTime		m_OversightDateTime;
	CString		m_Oversight_minutes;
	CString		m_szDiagnosis;
	CComboBox	m_ComboBoxCPOBox;
	CString		m_szCPODescr;
	CString		m_szEpisode_id;
	CString		m_szEpisodeStartDate;
	CString		m_szEpisodeEndDate;

	afx_msg void OnCbnSelchangeComboCpoCode();
};
