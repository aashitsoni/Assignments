// oversight_billing.h : Implementation of the Coversight_billing class



// Coversight_billing implementation

// code generated on Thursday, May 09, 2013, 2:34 PM

#include "stdafx.h"
#include "oversight_billing.h"
IMPLEMENT_DYNAMIC(Coversight_billing, CRecordset)

Coversight_billing::Coversight_billing(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_patient_oversight_id = 0;
	m_patient_episode_id = 0;
	m_patient_id = 0;
	m_patient_oversight_date;
	m_patient_oversight_minute = 0;
	m_patient_oversight_cpo_code = 0;
	m_patient_oversight_cpo_desc = L"";
	m_patient_oversight_diagnosis = L"";
	m_patient_oversight_billed = FALSE;
	m_nFields = 9;
	m_nDefaultType = dynaset;
}
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString Coversight_billing::GetDefaultConnect()
{
	//return _T("DSN=MS Access Database;DBQ=C:\\aks\\SRC\\Home Health\\HealthDatabse.accdb;DefaultDir=C:\\aks\\SRC\\Home Health;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
	CHomeHealthDatabase * pDB = ((CHomeHealthApp*)AfxGetApp())->GetHomeHealthDatabase();
	return pDB->m_szConnectionString;

}

CString Coversight_billing::GetDefaultSQL()
{
	return _T("[oversight_billing]");
}

void Coversight_billing::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[patient_oversight_id]"), m_patient_oversight_id);
	RFX_Long(pFX, _T("[patient_episode_id]"), m_patient_episode_id);
	RFX_Long(pFX, _T("[patient_id]"), m_patient_id);
	RFX_Date(pFX, _T("[patient_oversight_date]"), m_patient_oversight_date);
	RFX_Long(pFX, _T("[patient_oversight_minute]"), m_patient_oversight_minute);
	RFX_Long(pFX, _T("[patient_oversight_cpo_code]"), m_patient_oversight_cpo_code);
	RFX_Text(pFX, _T("[patient_oversight_cpo_desc]"), m_patient_oversight_cpo_desc);
	RFX_Text(pFX, _T("[patient_oversight_diagnosis]"),m_patient_oversight_diagnosis);
	RFX_Bool(pFX, _T("[patient_oversight_billed]"),m_patient_oversight_billed);

}
/////////////////////////////////////////////////////////////////////////////
// Coversight_billing diagnostics

#ifdef _DEBUG
void Coversight_billing::AssertValid() const
{
	CRecordset::AssertValid();
}

void Coversight_billing::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


int Coversight_billing::Open()
{
	if( TRUE == CRecordset::Open(m_nDefaultType,GetDefaultSQL(),CRecordset::readOnly ))
	{
		return 0;
	}
	return -1;

}

int Coversight_billing::Open(int patient_id,int patient_episode_id)
{

	m_strFilter.Format(_T("patient_id = %d and patient_episode_id = %d"),patient_id, patient_episode_id);

	if( TRUE == CRecordset::Open(m_nDefaultType,GetDefaultSQL(),CRecordset::readOnly ))
	{
		return 0;
	}
	return -1;
}

int Coversight_billing::OpenForAdd()
{
	if( TRUE == CRecordset::Open(m_nDefaultType,GetDefaultSQL(),CRecordset::appendOnly    ))
	{
		return 0;
	}
	return -1;
}

int Coversight_billing::InsertNew()
{

	
	return 0;
}


int Coversight_billing::OpenForOversightBilling(int patient_episode_id)
{
	m_strFilter.Format(_T("patient_episode_id = %d and patient_oversight_billed = FALSE"), patient_episode_id);
	if( TRUE == CRecordset::Open(m_nDefaultType,GetDefaultSQL(),CRecordset::none ))
	{
		return 0;
	}
	return -1;

}


int Coversight_billing::OpenForOversightDelete(long patient_oversight_id)
{
	m_strFilter.Format(_T("patient_oversight_id = %ld"), patient_oversight_id);
	if( TRUE == CRecordset::Open(m_nDefaultType,GetDefaultSQL(),CRecordset::none ))
	{
		return 0;
	}
	return -1;
}
