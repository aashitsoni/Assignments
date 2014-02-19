// oversight_cpo_code_master.h : Declaration of the Coversight_cpo_code_master

#pragma once

// code generated on Sunday, August 18, 2013, 11:52 PM

class Coversight_cpo_code_master : public CRecordset
{
public:
	Coversight_cpo_code_master(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(Coversight_cpo_code_master)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_oversight_cpo_code_id;
	CStringW	m_oversight_cpo_code_name;
	CStringW	m_oversight_cpo_code_descr;

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


