
// MDFMDIAppSet.cpp : implementation of the CHomeHealthSet class
//

#include "stdafx.h"
#include "HomeHealthApp.h"
#include "HomeHealthSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHomeHealthSet implementation

// code generated on Monday, May 06, 2013, 1:39 PM

IMPLEMENT_DYNAMIC(CHomeHealthSet, CRecordset)

CHomeHealthSet::CHomeHealthSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_patient_id = 0;
	m_patient_firstname = L"";
	m_patient_lastname = L"";
	m_patient_address = L"";
	m_patient_town = L"";
	m_patient_state = L"";
	m_nFields = 6;
	m_nDefaultType = dynaset;
}
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CHomeHealthSet::GetDefaultConnect()
{
//	return _T("DSN=MS Access Database;DBQ=C:\\AKS\\SRC\\prj\\HealthDatabse.accdb;DefaultDir=C:\\AKS\\SRC\\prj;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
	CHomeHealthDatabase * pDB = ((CHomeHealthApp*)AfxGetApp())->GetHomeHealthDatabase();
	return pDB->m_szConnectionString;
}

CString CHomeHealthSet::GetDefaultSQL()
{
	return _T("[patient_master]");
}

void CHomeHealthSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[patient_id]"), m_patient_id);
	RFX_Text(pFX, _T("[patient_firstname]"), m_patient_firstname);
	RFX_Text(pFX, _T("[patient_lastname]"), m_patient_lastname);
	RFX_Text(pFX, _T("[patient_address]"), m_patient_address);
	RFX_Text(pFX, _T("[patient_town]"), m_patient_town);
	RFX_Text(pFX, _T("[patient_state]"), m_patient_state);

}
/////////////////////////////////////////////////////////////////////////////
// CHomeHealthSet diagnostics

#ifdef _DEBUG
void CHomeHealthSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CHomeHealthSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

