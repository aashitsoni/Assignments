// oversight_billing.h : Declaration of the Coversight_billing

#pragma once

// code generated on Thursday, May 09, 2013, 2:34 PM

class Coversight_billing : public CRecordset
{
public:
	Coversight_billing(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(Coversight_billing)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_patient_oversight_id;
	long	m_patient_episode_id;
	long	m_patient_id;
	CTime	m_patient_oversight_date;
	long	m_patient_oversight_minute;
	long	m_patient_oversight_cpo_code;
	CString m_patient_oversight_cpo_desc;
	CString	m_patient_oversight_diagnosis;
	BOOL	m_patient_oversight_billed;
	long	m_patient_bill_number;


// Overrides
	// Wizard generated virtual function overrides
	public:
	virtual CString GetDefaultConnect();	// Default connection string

	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support
	int Open();
	int Open(int patient_id, int patient_episode_id);
	int OpenForAdd();
	int InsertNew();
	int OpenForOversightBilling(int patient_episode_id);
	int OpenForOversightDelete(long patient_oversight_id);
	int OpenByBillingid(long patient_billing_id);



// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


