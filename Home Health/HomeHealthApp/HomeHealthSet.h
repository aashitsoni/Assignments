
// MDFMDIAppSet.h: interface of the CHomeHealthSet class
//


#pragma once

// code generated on Monday, May 06, 2013, 1:39 PM

class CHomeHealthSet : public CRecordset
{
public:
	CHomeHealthSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CHomeHealthSet)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_patient_id;	//unique identifier to patient record
	CStringW	m_patient_firstname;
	CStringW	m_patient_lastname;
	CStringW	m_patient_address;
	CStringW	m_patient_town;
	CStringW	m_patient_state;

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

};

