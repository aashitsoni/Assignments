// patient_episode.h : Implementation of the Cpatient_episode class



// Cpatient_episode implementation

// code generated on Wednesday, May 08, 2013, 2:00 PM

#include "stdafx.h"
#include "patient_episode.h"
IMPLEMENT_DYNAMIC(Cpatient_episode, CRecordset)

Cpatient_episode::Cpatient_episode(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_patient_episode_code = 0;
	m_patient_id = 0;
	m_episode_start_date = 0;
	m_episode_end_date = 0;
	m_episode_active = FALSE;
	m_episode_total_minutes = 0;
	m_episode_last_visit = 0;
	m_episode_dx_codes = L"";
	m_episode_hh_agency_name= L"" ;
	m_episode_hh_agency_code = 0;
	m_episode_last_bill_date = 0;
	m_episode_oversight_bill_date = 0;	
	m_episode_billing_status = 0;

	m_nFields = 14;
	m_nDefaultType = dynaset;
}
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString Cpatient_episode::GetDefaultConnect()
{
//	return _T("DSN=MS Access Database;DBQ=C:\\aks\\SRC\\Home Health\\HealthDatabse.accdb;DefaultDir=C:\\aks\\SRC\\Home Health;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
	CHomeHealthDatabase * pDB = ((CHomeHealthApp*)AfxGetApp())->GetHomeHealthDatabase();
	return pDB->m_szConnectionString;

}

CString Cpatient_episode::GetDefaultSQL()
{
	return _T("[patient_episode]");
}

void Cpatient_episode::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[patient_episode_code]"), m_patient_episode_code);
	RFX_Long(pFX, _T("[patient_id]"), m_patient_id);
	RFX_Date(pFX, _T("[episode_start_date]"), m_episode_start_date);
	RFX_Date(pFX, _T("[episode_end_date]"), m_episode_end_date);
	RFX_Bool(pFX, _T("[episode_active]"), m_episode_active);
	RFX_Long(pFX, _T("[episode_total_minutes]"), m_episode_total_minutes);
	RFX_Date(pFX, _T("[episode_last_visit]"),m_episode_last_visit);
	RFX_Text(pFX, _T("[episode_type]"),m_episode_type);
	RFX_Text(pFX, _T("[episode_dx_codes]"),m_episode_dx_codes);
	RFX_Text(pFX, _T("[episode_hh_agency_name]"),m_episode_hh_agency_name);
	RFX_Long(pFX, _T("[episode_hh_agency_code]"),m_episode_hh_agency_code);
	RFX_Date(pFX, _T("[episode_last_bill_date]"),m_episode_last_bill_date);
	RFX_Date(pFX, _T("[episode_oversight_bill_date]"),m_episode_oversight_bill_date);
	RFX_Int (pFX, _T("[episode_billing_status]"),m_episode_billing_status);
}
/////////////////////////////////////////////////////////////////////////////
// Cpatient_episode diagnostics

#ifdef _DEBUG
void Cpatient_episode::AssertValid() const
{
	CRecordset::AssertValid();
}

void Cpatient_episode::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


int Cpatient_episode::Open()
{
	if( TRUE == CRecordset::Open(m_nDefaultType,GetDefaultSQL(),CRecordset::readOnly ))
	{
		return 0;
	}
	return -1;

}

BOOL Cpatient_episode::SetDB(CDatabase* pDB)
{
	m_pDatabase = pDB;
	return TRUE;
}
int Cpatient_episode::OpenExclusive(long patient_id)
{
	m_strFilter.Format(_T("patient_id = %ld"),patient_id);

	if( TRUE == CRecordset::Open(m_nDefaultType,GetDefaultSQL(),CRecordset::none ))
	{
		return 0;
	}
	return -1;

}

int Cpatient_episode::Open(long patient_id)
{

	m_strFilter.Format(_T("patient_id = %ld"),patient_id);

	if( TRUE == CRecordset::Open(m_nDefaultType,GetDefaultSQL(),CRecordset::readOnly ))
	{
		return 0;
	}
	return -1;
}


int Cpatient_episode::OpenForAdd()
{
	if( TRUE == CRecordset::Open(m_nDefaultType,GetDefaultSQL(),CRecordset::appendOnly    ))
	{
		return 0;
	}
	return -1;
}

int Cpatient_episode ::OpenForModify(long patient_id,long patient_episode_id)
{
	m_strFilter.Format(_T("patient_episode_code=%ld and patient_id = %ld"),patient_episode_id,patient_id);
	if( TRUE == CRecordset::Open(m_nDefaultType,GetDefaultSQL(),CRecordset::none))
	{
		return 0;
	}
	return -1;

}


int Cpatient_episode::QueryPatientEpisode(long episode_id)
{
	m_strFilter.Format(_T("patient_episode_code=%ld"),episode_id);
	if(TRUE == CRecordset::Open(m_nDefaultType,GetDefaultSQL(),CRecordset::none))
	{
		return 0;
	}
	return -1;
}


int Cpatient_episode::OpenForModifyWithEpisodeId(long patient_episode_id)
{
	m_strFilter.Format(_T("patient_episode_code=%ld"),patient_episode_id);
	if( TRUE == CRecordset::Open(m_nDefaultType,GetDefaultSQL(),CRecordset::none))
	{
		return 0;
	}
	return -1;

}

int Cpatient_episode::OpenForEpisodeId(long patient_episode_id)
{
	m_strFilter.Format(_T("patient_episode_code=%ld"),patient_episode_id);
	if( TRUE == CRecordset::Open(m_nDefaultType,GetDefaultSQL(),CRecordset::readOnly))
	{
		return 0;
	}
	return -1;
}
