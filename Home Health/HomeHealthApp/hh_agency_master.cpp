// hh_agency_master.h : Implementation of the Chh_agency_master class



// Chh_agency_master implementation

// code generated on Sunday, August 18, 2013, 11:51 PM

#include "stdafx.h"
#include "hh_agency_master.h"
IMPLEMENT_DYNAMIC(Chh_agency_master, CRecordset)

Chh_agency_master::Chh_agency_master(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_HH_Agency_code_id = 0;
	m_HH_Agency_code_name = L"";
	m_HH_Agency_addr = L"";
	m_HH_Agency_addr1 = L"";
	m_HH_Agency_city = L"";
	m_HH_Agency_state = L"";
	m_HH_Agency_zip = L"";
	m_HH_Agency_phone = L"";
	m_HH_Agency_fax = L"";
	m_HH_Agency_email = L"";
	m_HH_Agency_contact_person = L"";
	m_nFields = 11;
	m_nDefaultType = dynaset;
}
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString Chh_agency_master::GetDefaultConnect()
{
//	return _T("DSN=MS Access Database;DBQ=C:\\aks\\SRC\\Home Health\\HealthDatabse.accdb;DefaultDir=C:\\aks\\SRC\\Home Health;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
	CHomeHealthDatabase * pDB = ((CHomeHealthApp*)AfxGetApp())->GetHomeHealthDatabase();
	return pDB->m_szConnectionString;

}

CString Chh_agency_master::GetDefaultSQL()
{
	return _T("[hh_agency_master]");
}

void Chh_agency_master::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[HH_Agency_code_id]"), m_HH_Agency_code_id);
	RFX_Text(pFX, _T("[HH_Agency_code_name]"), m_HH_Agency_code_name);
	RFX_Text(pFX, _T("[HH_Agency_addr]"), m_HH_Agency_addr);
	RFX_Text(pFX, _T("[HH_Agency_addr1]"), m_HH_Agency_addr1);
	RFX_Text(pFX, _T("[HH_Agency_city]"), m_HH_Agency_city);
	RFX_Text(pFX, _T("[HH_Agency_state]"), m_HH_Agency_state);
	RFX_Text(pFX, _T("[HH_Agency_zip]"), m_HH_Agency_zip);
	RFX_Text(pFX, _T("[HH_Agency_phone]"), m_HH_Agency_phone);
	RFX_Text(pFX, _T("[HH_Agency_fax]"), m_HH_Agency_fax);
	RFX_Text(pFX, _T("[HH_Agency_email]"), m_HH_Agency_email);
	RFX_Text(pFX, _T("[HH_Agency_contact_person]"), m_HH_Agency_contact_person);

}
/////////////////////////////////////////////////////////////////////////////
// Chh_agency_master diagnostics

#ifdef _DEBUG
void Chh_agency_master::AssertValid() const
{
	CRecordset::AssertValid();
}

void Chh_agency_master::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


