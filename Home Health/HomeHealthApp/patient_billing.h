// patient_billin.h : Declaration of the Cpatient_billing

#ifndef _PATIENT_BILLING
#define _PATIENT_BILLING
class Cpatient_billing:public CRecordset
{

public:
	Cpatient_billing(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(Cpatient_billing)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long		m_patient_bill_number;	//unique identifier to patient record
	long		m_patient_id;
	long		m_patient_episode_code;
	CTime		m_patient_bill_date;
	int			m_patient_bill_type;
	long		m_patient_hh_agency_code;
	int			m_patient_sent_fax;
	int			m_patient_sent_email;
// Overrides
	// Wizard generated virtual function overrides
	public:
	virtual CString GetDefaultConnect();	// Default connection string
	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	int OpenExclusive(long patient_id);

};

#endif
