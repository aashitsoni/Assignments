// patient_billing.h : Implementation of the Cpatient_billing class



// Cpatient_master implementation


#include "stdafx.h"
#include "patient_billing.h"

IMPLEMENT_DYNAMIC(Cpatient_billing, CRecordset)

Cpatient_billing::Cpatient_billing(CDatabase* pdb)
	: CRecordset(pdb)
{

	m_patient_bill_number = 0;
	m_patient_id = 0;
	m_patient_episode_code = 0;
	m_patient_bill_date = 0;
	m_patient_bill_type = 0;
	m_patient_hh_agency_code = 0;
	m_patient_sent_fax = 0;
	m_patient_sent_email = 0;
	m_patient_last_seen = 0;
	m_patient_bill_minutes = 0;
	m_nFields = 10;
	m_nDefaultType = dynaset;

}

//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString Cpatient_billing::GetDefaultConnect()
{
	CHomeHealthDatabase * pDB = ((CHomeHealthApp*)AfxGetApp())->GetHomeHealthDatabase();
	return pDB->m_szConnectionString;

//	return _T("DSN=MS Access Database;DBQ=C:\\aks\\SRC\\Home Health\\HealthDatabse.accdb;DefaultDir=C:\\aks\\SRC\\Home Health;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
}


CString Cpatient_billing::GetDefaultSQL()
{
	return _T("[patient_billing]");
}


void Cpatient_billing::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[patient_bill_number]"), m_patient_bill_number);
	RFX_Long(pFX, _T("[patient_id]"), m_patient_id);
	RFX_Long(pFX, _T("[patient_episode_code]"), m_patient_episode_code);
	RFX_Date(pFX, _T("[patient_bill_date]"),m_patient_bill_date);
	RFX_Int (pFX, _T("[patient_bill_type]"),m_patient_bill_type);
	RFX_Long(pFX, _T("[patient_hh_agency_code]"), m_patient_hh_agency_code);
	RFX_Int (pFX, _T("[patient_sent_fax]"),m_patient_sent_fax);
	RFX_Int (pFX, _T("[patient_sent_email]"),m_patient_sent_email);
	RFX_Date(pFX, _T("[patient_last_seen]"),m_patient_last_seen);
	RFX_Int (pFX, _T("[patient_bill_minutes]"),m_patient_bill_minutes);

}

#ifdef _DEBUG
void Cpatient_billing::AssertValid() const
{
	CRecordset::AssertValid();
}

void Cpatient_billing::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

int Cpatient_billing::OpenExclusive(long patient_id)
{
	m_strFilter.Format(_T("patient_id = %ld"),patient_id);
	if( TRUE == CRecordset::Open(m_nDefaultType,GetDefaultSQL(),CRecordset::none|CRecordset::useBookmarks))
	{
		return 0;
	}
	return -1;
}

int Cpatient_billing::OpenbyBillNumber(long patient_bill_number)
{
	m_strFilter.Format(_T("patient_bill_number = %ld"),patient_bill_number);
	if( TRUE == CRecordset::Open(m_nDefaultType,GetDefaultSQL(),CRecordset::readOnly))
	{
		return 0;
	}
	return -1;
}

