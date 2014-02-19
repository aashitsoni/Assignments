// oversight_cpo_code_master.h : Implementation of the Coversight_cpo_code_master class



// Coversight_cpo_code_master implementation

// code generated on Sunday, August 18, 2013, 11:52 PM

#include "stdafx.h"
#include "oversight_cpo_code_master.h"
IMPLEMENT_DYNAMIC(Coversight_cpo_code_master, CRecordset)

Coversight_cpo_code_master::Coversight_cpo_code_master(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_oversight_cpo_code_id = 0;
	m_oversight_cpo_code_name = L"";
	m_oversight_cpo_code_descr = L"";
	m_nFields = 3;
	m_nDefaultType = dynaset;
}
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString Coversight_cpo_code_master::GetDefaultConnect()
{
//	return _T("DSN=MS Access Database;DBQ=C:\\aks\\SRC\\Home Health\\HealthDatabse.accdb;DefaultDir=C:\\aks\\SRC\\Home Health;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
	CHomeHealthDatabase * pDB = ((CHomeHealthApp*)AfxGetApp())->GetHomeHealthDatabase();
	return pDB->m_szConnectionString;
}

CString Coversight_cpo_code_master::GetDefaultSQL()
{
	return _T("[oversight_cpo_code_master]");
}

void Coversight_cpo_code_master::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[oversight_cpo_code_id]"), m_oversight_cpo_code_id);
	RFX_Text(pFX, _T("[oversight_cpo_code_name]"), m_oversight_cpo_code_name);
	RFX_Text(pFX, _T("[oversight_cpo_code_descr]"), m_oversight_cpo_code_descr);

}
/////////////////////////////////////////////////////////////////////////////
// Coversight_cpo_code_master diagnostics

#ifdef _DEBUG
void Coversight_cpo_code_master::AssertValid() const
{
	CRecordset::AssertValid();
}

void Coversight_cpo_code_master::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


