// patient_master.h : Declaration of the Cpatient_master

#pragma once

// code generated on Monday, May 06, 2013, 3:17 PM

class Cpatient_master : public CRecordset
{

		CString GePatientIdSearchSQL(int patient_id);
public:
	Cpatient_master(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(Cpatient_master)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long		m_patient_id;	//unique identifier to patient record
	CStringW	m_patient_firstname;	/*2 */
	CStringW	m_patient_lastname;		/*3*/
	CStringW	m_patient_address;		/*4*/
	CStringW	m_patient_town;			/*5*/
	CStringW	m_patient_state;		/*6*/
	CStringW	m_patient_middlename;	/*7*/
	CStringW    m_patient_salutation;	/*8*/
	CStringW	m_patient_home_phone;	/*9*/
	CStringW	m_patient_cell_phone;	/*10*/
	CStringW	m_patient_work_phone;	/*11*/
	CStringW	m_patient_communication_phone;/*12*/
	CStringW	m_patient_country;	/*13*/
	CTime		m_patient_registration_date;	/*14*/
	CTime		m_patient_last_visit;			/*15*/
	CTime		m_patient_last_bill_date;		/*16*/
	long		m_patient_billable_minutes;		/*17*/
	CStringW	m_patient_address_apartment;	/*18*/
	COleDateTime	m_patient_dob;					/*19*/
	CStringW	m_patient_zip;				/*20*/
	CTime		m_patient_oversight_bill_date; /*21*/
	CStringW    m_patient_sex;			/*22*/
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
	int Open();
	int Open(unsigned long patient_id);
	int OpenForAdd();
	int OpenForModify(unsigned long patient_id);
	int OpenExclusive(unsigned long patient_id);
	int OpenExclusive();
	int OpenWithSearchOnName(CString& szFirstName,CString& szLastName);
	BOOL SetDB(CDatabase* pDatabase);

};


