// hh_agency_master.h : Declaration of the Chh_agency_master

#pragma once

// code generated on Sunday, August 18, 2013, 11:51 PM

class Chh_agency_master : public CRecordset
{
public:
	Chh_agency_master(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(Chh_agency_master)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_HH_Agency_code_id;
	CStringW	m_HH_Agency_code_name;
	CStringW	m_HH_Agency_addr;
	CStringW	m_HH_Agency_addr1;
	CStringW	m_HH_Agency_city;
	CStringW	m_HH_Agency_state;
	CStringW	m_HH_Agency_zip;
	CStringW	m_HH_Agency_phone;
	CStringW	m_HH_Agency_fax;
	CStringW	m_HH_Agency_email;
	CStringW	m_HH_Agency_contact_person;

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


