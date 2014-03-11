
// MDFMDIAppView.h : interface of the CHomeHealthView class
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "atlcomtime.h"
#include "atltime.h"
#include "oversight_cpo_code_master.h"
#include "patient_master.h"
#include "patient_episode.h"
#include "patient_billing.h"
#include "oversight_billing.h"

class CHomeHealthSet;

enum homehealth_doc_print_mode
{
    homehealth_print_none,
    homehealth_print_initial_bill,
    homehealth_print_oversight_bill,
    homehealth_print_patient_record,
};

class CHomeHealthView : public CRecordView
{
    homehealth_doc_print_mode homehealth_printmode;
    CFont* fntTitle1;
    CFont* fntTitle2;
    CFont* fntText;
    CFont* fntHeader;

    BOOL m_dbOpened ;

protected: // create from serialization only
    CHomeHealthView();
    DECLARE_DYNCREATE(CHomeHealthView)
    void OnCompleteOversightBillPrinting();
    BOOL PopulateEpisodeBilling();
    BOOL CreatePatientBillingControlColumns();

public:
    enum{ IDD = IDD_MDFMDIAPP_FORM };
    CHomeHealthSet* m_pSet;
    CString GetCurrentMonth();
    void OnCompleteInitialBillPrinting();
    long OnCompleteInitialBillPrintingCommon();
// Attributes
public:
    CHomeHealthDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
    virtual CRecordset* OnGetRecordset();
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual void OnInitialUpdate(); // called first time after construct
    virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
    virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
    virtual ~CHomeHealthView();
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    CHomeHealthDatabase* m_pHealthDB;
    Cpatient_master* m_ActivePatient;
    Cpatient_episode* m_activePatientEpisode;
    Cpatient_billing* m_activeBilling;

    

// Generated message map functions
protected:
    afx_msg void OnFilePrintPreview();
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
    DECLARE_MESSAGE_MAP()
public:
    CListCtrl m_episodeListCtrl;
    afx_msg void OnNMDblclkPatientEpisode(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    CListCtrl m_OverSightListCtrl;
    afx_msg void OnClickPatientEpisode(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnCompletePrintingBill();
private:
    int         m_patient_billing_status;
    long        m_patient_id;
    long        m_patient_episode_id;
    long        m_active_episode_id;
    CTime       m_patient_episode_start_date;
    CTime       m_patient_episode_end_date;
	long		m_patient_bill_code;
	Cpatient_episode* m_printPatientEpisode;
	Coversight_billing* m_printPatientOversight;


    CString m_szPatientID;
    CString m_szPatientAddress;
    CString m_szPatientTown;
    CString m_szTotalMinutes;
	CTime	m_lastDateSeen;

    Coversight_cpo_code_master *cpo_master;
    void AddNewEpisode();
    void AddNewOversightBilling();
    CTime   m_currentDate;
    void printInitialBilling(CDC* pDC,CPrintInfo* pInfo);
    void printOversightBilling(CDC* pDC,CPrintInfo* pInfo);
    void printPatientLeadger(CDC* pDC,CPrintInfo* pInfo);
	void formatPatientEpisodeDXCode();

public:
	CString m_szPatientEpisodeOneLineDXCodes;
    BOOL findCPOCodeName(Coversight_billing* oversight,CString& szCPOCodeName);

public:
    afx_msg void OnLvnItemchangedPatientEpisode(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnLvnKeydownPatientEpisode(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnBnClickedButtonAddOversight();
    afx_msg void OnBnClickedButtonAddEpisode();
private:
    BOOL CreateEpisodeControlColumns();
    BOOL PopulateEpisodeControlData();
    BOOL CreateOversightConrolColumns();
    BOOL PopulateOversightControlData();
    void PopulateView();
    void PopulateNewForm();
    BOOL ValidatePatientInformation();
    void ReOpenView();
    BOOL AdjustPatientBillableMinutes(int billableMinutes);
    void OnPatientSaveNew();
    void OnPatientSaveEdit();

    BOOL OpenPatientRecords();

public:
    afx_msg void OnNMRClickPatientEpisode(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnEpisodeEdit();
    afx_msg void OnEpisodeDelete();
    afx_msg void OnFileSave();
    CString m_szPatientName;
    CComboBox m_comboTitle;
    CComboBox m_comboState;
    //CString m_szCountry;
    CString m_szApartment;
    CString m_szMiddleName;
    CString m_szFirstName;
    CTime m_datePatientLastBill;
    CTime m_datePatientLastVisit;
    CTime m_datePatientRegistration;
    CString m_szCellPhone;
    CString m_szHomePhone;
    CString m_szWorkPhone;
    afx_msg void OnRclickListOversight(NMHDR *pNMHDR, LRESULT *pResult);
    virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
    CString m_szPatientZip;
    COleDateTime m_PatientDOB;
    afx_msg void OnEpisodeAdd();
    afx_msg void OnOversightAdd();
    afx_msg void OnReportsPatientledger();
    afx_msg void OnEpisodeAddoversight();
//  CButton m_btnBillSignal;
//  CStatic m_billIndicator;
    CButton m_btnBillIndicator;
    afx_msg void OnBnClickedButtonbill();
    virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
    virtual void OnDraw(CDC* /*pDC*/);
    afx_msg void OnDtnDatetimechangePatientLastVisit(NMHDR *pNMHDR, LRESULT *pResult);
    CListCtrl m_listEpisodeBill;
    CComboBox m_comboSex;
    afx_msg void OnOversightEdit();
    afx_msg void OnOversightDelete();
//	afx_msg void OnCbnSelchangeCombo2();
private:
	CComboBox m_comboCommunication;
};

#ifndef _DEBUG  // debug version in MDFMDIAppView.cpp
inline CHomeHealthDoc* CHomeHealthView::GetDocument() const
   { return reinterpret_cast<CHomeHealthDoc*>(m_pDocument); }
#endif

