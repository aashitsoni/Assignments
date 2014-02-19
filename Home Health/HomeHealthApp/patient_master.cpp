// patient_master.h : Implementation of the Cpatient_master class



// Cpatient_master implementation

// code generated on Monday, May 06, 2013, 3:17 PM

#include "stdafx.h"
#include "patient_master.h"

IMPLEMENT_DYNAMIC(Cpatient_master, CRecordset)

Cpatient_master::Cpatient_master(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_patient_id = 0;
	m_patient_firstname = L"";
	m_patient_lastname = L"";
	m_patient_address = L"";
	m_patient_town = L"";
	m_patient_state = L"";
	m_patient_middlename = L"";	/*7*/
	m_patient_salutation = L"";	/*8*/
	m_patient_home_phone = L"";	/*9*/
	m_patient_cell_phone = L"";	/*10*/
	m_patient_work_phone = L"";	/*11*/
	m_patient_communication_phone = L"";/*12*/
	m_patient_country = L"";	/*13*/
	m_patient_registration_date = 0;	/*14*/
	m_patient_last_visit = 0;			/*15*/
	m_patient_last_bill_date = 0;		/*16*/
	m_patient_billable_minutes = 0;		/*17*/
	m_patient_address_apartment = L"";
	m_patient_zip = L"";
//	m_patient_dob = 0;
	m_patient_oversight_bill_date = 0;
	m_patient_sex = L"";
	m_nFields = 22;
	m_nDefaultType = dynaset;
}
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString Cpatient_master::GetDefaultConnect()
{
	CHomeHealthDatabase * pDB = ((CHomeHealthApp*)AfxGetApp())->GetHomeHealthDatabase();
	return pDB->m_szConnectionString;

//	return _T("DSN=MS Access Database;DBQ=C:\\aks\\SRC\\Home Health\\HealthDatabse.accdb;DefaultDir=C:\\aks\\SRC\\Home Health;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
}

CString Cpatient_master::GetDefaultSQL()
{
	return _T("[patient_master]");
}

CString Cpatient_master::GePatientIdSearchSQL(int patient_id)
{
	CString szSQL;
	szSQL.Format(_T("[patient_master where patient_id=%d]"),patient_id);

	return szSQL;
}

BOOL Cpatient_master::SetDB(CDatabase* pDatabase)
{
	m_pDatabase = pDatabase;
	return TRUE;
}


void Cpatient_master::DoFieldExchange(CFieldExchange* pFX)
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
	RFX_Text(pFX, _T("[patient_middlename]"),m_patient_middlename );
	RFX_Text(pFX, _T("[patient_salutation]"),m_patient_salutation);
	RFX_Text(pFX, _T("[patient_home_phone]"),m_patient_home_phone);
	RFX_Text(pFX, _T("[patient_cell_phone]"),m_patient_cell_phone);
	RFX_Text(pFX, _T("[patient_work_phone]"),m_patient_work_phone);
	RFX_Text(pFX, _T("[patient_communication_phone]"),m_patient_communication_phone);
	RFX_Text(pFX, _T("[patient_country]"),m_patient_country);
	RFX_Date(pFX, _T("[patient_registration_date]"),m_patient_registration_date);
	RFX_Date(pFX, _T("[patient_last_visit]"),m_patient_last_visit);
	RFX_Date(pFX, _T("[patient_last_bill_date]"),m_patient_last_bill_date);
	RFX_Long(pFX, _T("[patient_billable_minutes]"),m_patient_billable_minutes);
	RFX_Text(pFX, _T("[patient_address_apartment]"),m_patient_address_apartment);
	RFX_Date(pFX, _T("[patient_dob]"),m_patient_dob);
	RFX_Text(pFX, _T("[patient_zip]"),m_patient_zip);
	RFX_Date(pFX, _T("[patient_oversight_bill_date]"),m_patient_oversight_bill_date);
	RFX_Text(pFX, _T("[patient_male]"),m_patient_sex);
	
}
/////////////////////////////////////////////////////////////////////////////
// Cpatient_master diagnostics

#ifdef _DEBUG
void Cpatient_master::AssertValid() const
{
	CRecordset::AssertValid();
}

void Cpatient_master::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

int Cpatient_master::OpenExclusive()
{
	if( TRUE == CRecordset::Open(m_nDefaultType,GetDefaultSQL(),CRecordset::none|CRecordset::useBookmarks))
	{
		return 0;
	}
	return -1;
}

int Cpatient_master::OpenExclusive(unsigned long patient_id)
{
	m_strFilter.Format(_T("patient_id = %ld"),patient_id);
	if( TRUE == CRecordset::Open(m_nDefaultType,GetDefaultSQL(),CRecordset::none|CRecordset::useBookmarks))
	{
		return 0;
	}
	return -1;
}

int Cpatient_master::Open()
{
	if( TRUE == CRecordset::Open(m_nDefaultType,GetDefaultSQL(),CRecordset::readOnly ))
	{
		return 0;
	}
	return -1;

}

int Cpatient_master::Open(unsigned long patient_id)
{

	m_strFilter.Format(_T("patient_id = %ld"),patient_id);

	if( TRUE == CRecordset::Open(snapshot,GetDefaultSQL(),CRecordset::readOnly ))
	{
		return 0;
	}
	return -1;
}

int Cpatient_master::OpenForAdd()
{
	if( TRUE == CRecordset::Open(m_nDefaultType,GetDefaultSQL(),CRecordset::appendOnly|CRecordset::useBookmarks))
	{
		return 0;
	}
	return -1;
}


int Cpatient_master ::OpenForModify(unsigned long patient_id)
{
	m_strFilter.Format(_T("patient_id = %ld"),patient_id);
	if( TRUE == CRecordset::Open(m_nDefaultType,GetDefaultSQL(),CRecordset::none))
	{
		return 0;
	}
	return -1;

}

int Cpatient_master::OpenWithSearchOnName(CString& szFirstName,CString& szLastName)
{
	if(szFirstName.GetLength() > 0 && szLastName.GetLength() > 0)
		m_strFilter.Format(_T("patient_firstname like \'%s%%\'"),szFirstName);
	else if(szFirstName.GetLength() > 0 && szLastName.GetLength() == 0)
		m_strFilter.Format(_T("patient_firstname like \'%s%%\'"),szFirstName);
	else if(szFirstName.GetLength() == 0 && szLastName.GetLength() > 0)
		m_strFilter.Format(_T("patient_lastname like \'%s%%\'"),szLastName);
		 

	if(TRUE == CRecordset::Open(snapshot,GetDefaultSQL(),readOnly))
		return 0;


	return -1;

}