// oversight_health.h : Implementation of the Coversight_health class



// Coversight_health implementation

// code generated on Sunday, August 18, 2013, 11:52 PM

#include "stdafx.h"
#include "oversight_health.h"
IMPLEMENT_DYNAMIC(Coversight_health, CRecordset)

Coversight_health::Coversight_health(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_patient_oversight_id = 0;
	m_patient_episode_id = 0;
	m_patient_id = L"";
	m_studies_echo = FALSE;
	m_oversight_health_date;
	m_studies_EKG = FALSE;
	m_oversight_hh_agency_code = 0;
	m_studies_MRI_Brain = FALSE;
	m_oversight_chart_reviewed = FALSE;
	m_oversight_medication_reviewed = FALSE;
	m_oversight_studies_reviewed = FALSE;
	m_oversight_studies_echo = FALSE;
	m_oversight_studies_ekg = FALSE;
	m_oversight_studies_mri_brain = FALSE;
	m_oversight_studies_carotid = FALSE;
	m_oversight_studies_art_dopler = FALSE;
	m_oversight_studies_venous_dopler = FALSE;
	m_oversight_studies_abi = FALSE;
	m_oversight_studies_cxr = FALSE;
	m_oversight_studies_abd_xray = FALSE;
	m_oversight_studies_mra_neck = FALSE;
	m_oversight_studies_ct_scan_brain = FALSE;
	m_oversight_studies_ct_scan_abd_pelvis = FALSE;
	m_oversight_studies_ct_scan_other = FALSE;
	m_oversight_studies_ct_scan_other_desc = L"";
	m_oversight_need_appointment = FALSE;
	m_oversight_next_appointment;
	m_oversight_last_appointment;
	m_oversight_labs_ordered = FALSE;
	m_oversight_labs_chem12 = FALSE;
	m_oversight_labs_cbc = FALSE;
	m_oversight_labs_b12_folate = FALSE;
	m_oversight_labs_cxr = FALSE;
	m_oversight_labs_vita_d2_3 = FALSE;
	m_oversight_labs_flp = FALSE;
	m_oversight_labs_hepatitis_panel = FALSE;
	m_oversight_labs_hbg_ac = FALSE;
	m_oversight_labs_24hr_urine_ccl = FALSE;
	m_oversight_labs_urine_microabulmin = FALSE;
	m_oversight_labs_va_with_cs = FALSE;
	m_oversight_labs_pth = FALSE;
	m_oversight_labs_spep = FALSE;
	m_oversight_labs_spiep = FALSE;
	m_oversight_labs_24hr_urine_uiep_upep = FALSE;
	m_oversight_labs_tsh = FALSE;
	m_oversight_labs_tft = FALSE;
	m_oversight_labs_arthritis_panel = FALSE;
	m_oversight_labs_anemia_profile = FALSE;
	m_oversight_labs_hemoccult_stools_x3 = FALSE;
	m_oversight_labs_echo = FALSE;
	m_oversight_labs_ekg = FALSE;
	m_oversight_labs_venous_doppler = FALSE;
	m_oversight_labs_abi_w_excercise = FALSE;
	m_oversight_labs_art_doppler = FALSE;
	m_oversight_instruction = L"";
	m_nFields = 55;
	m_nDefaultType = dynaset;
}
// #error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString Coversight_health::GetDefaultConnect()
{
//	return _T("DSN=MS Access Database;DBQ=C:\\aks\\SRC\\Home Health\\HealthDatabse.accdb;DefaultDir=C:\\aks\\SRC\\Home Health;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
	CHomeHealthDatabase * pDB = ((CHomeHealthApp*)AfxGetApp())->GetHomeHealthDatabase();
	return pDB->m_szConnectionString;
}

CString Coversight_health::GetDefaultSQL()
{
	return _T("[oversight_health]");
}

void Coversight_health::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[patient_oversight_id]"), m_patient_oversight_id);
	RFX_Long(pFX, _T("[patient_episode_id]"), m_patient_episode_id);
	RFX_Text(pFX, _T("[patient_id]"), m_patient_id);
	RFX_Bool(pFX, _T("[studies_echo]"), m_studies_echo);
	RFX_Date(pFX, _T("[oversight_health_date]"), m_oversight_health_date);
	RFX_Bool(pFX, _T("[studies_EKG]"), m_studies_EKG);
	RFX_Long(pFX, _T("[oversight_hh_agency_code]"), m_oversight_hh_agency_code);
	RFX_Bool(pFX, _T("[studies_MRI_Brain]"), m_studies_MRI_Brain);
	RFX_Bool(pFX, _T("[oversight_chart_reviewed]"), m_oversight_chart_reviewed);
	RFX_Bool(pFX, _T("[oversight_medication_reviewed]"), m_oversight_medication_reviewed);
	RFX_Bool(pFX, _T("[oversight_studies_reviewed]"), m_oversight_studies_reviewed);
	RFX_Bool(pFX, _T("[oversight_studies_echo]"), m_oversight_studies_echo);
	RFX_Bool(pFX, _T("[oversight_studies_ekg]"), m_oversight_studies_ekg);
	RFX_Bool(pFX, _T("[oversight_studies_mri_brain]"), m_oversight_studies_mri_brain);
	RFX_Bool(pFX, _T("[oversight_studies_carotid]"), m_oversight_studies_carotid);
	RFX_Bool(pFX, _T("[oversight_studies_art_dopler]"), m_oversight_studies_art_dopler);
	RFX_Bool(pFX, _T("[oversight_studies_venous_dopler]"), m_oversight_studies_venous_dopler);
	RFX_Bool(pFX, _T("[oversight_studies_abi]"), m_oversight_studies_abi);
	RFX_Bool(pFX, _T("[oversight_studies_cxr]"), m_oversight_studies_cxr);
	RFX_Bool(pFX, _T("[oversight_studies_abd_xray]"), m_oversight_studies_abd_xray);
	RFX_Bool(pFX, _T("[oversight_studies_mra_neck]"), m_oversight_studies_mra_neck);
	RFX_Bool(pFX, _T("[oversight_studies_ct_scan_brain]"), m_oversight_studies_ct_scan_brain);
	RFX_Bool(pFX, _T("[oversight_studies_ct_scan_abd_pelvis]"), m_oversight_studies_ct_scan_abd_pelvis);
	RFX_Bool(pFX, _T("[oversight_studies_ct_scan_other]"), m_oversight_studies_ct_scan_other);
	RFX_Text(pFX, _T("[oversight_studies_ct_scan_other_desc]"), m_oversight_studies_ct_scan_other_desc);
	RFX_Bool(pFX, _T("[oversight_need_appointment]"), m_oversight_need_appointment);
	RFX_Date(pFX, _T("[oversight_next_appointment]"), m_oversight_next_appointment);
	RFX_Date(pFX, _T("[oversight_last_appointment]"), m_oversight_last_appointment);
	RFX_Bool(pFX, _T("[oversight_labs_ordered]"), m_oversight_labs_ordered);
	RFX_Bool(pFX, _T("[oversight_labs_chem12]"), m_oversight_labs_chem12);
	RFX_Bool(pFX, _T("[oversight_labs_cbc]"), m_oversight_labs_cbc);
	RFX_Bool(pFX, _T("[oversight_labs_b12_folate]"), m_oversight_labs_b12_folate);
	RFX_Bool(pFX, _T("[oversight_labs_cxr]"), m_oversight_labs_cxr);
	RFX_Bool(pFX, _T("[oversight_labs_vita_d2_3]"), m_oversight_labs_vita_d2_3);
	RFX_Bool(pFX, _T("[oversight_labs_flp]"), m_oversight_labs_flp);
	RFX_Bool(pFX, _T("[oversight_labs_hepatitis_panel]"), m_oversight_labs_hepatitis_panel);
	RFX_Bool(pFX, _T("[oversight_labs_hbg_ac]"), m_oversight_labs_hbg_ac);
	RFX_Bool(pFX, _T("[oversight_labs_24hr_urine_ccl]"), m_oversight_labs_24hr_urine_ccl);
	RFX_Bool(pFX, _T("[oversight_labs_urine_microabulmin]"), m_oversight_labs_urine_microabulmin);
	RFX_Bool(pFX, _T("[oversight_labs_va_with_cs]"), m_oversight_labs_va_with_cs);
	RFX_Bool(pFX, _T("[oversight_labs_pth]"), m_oversight_labs_pth);
	RFX_Bool(pFX, _T("[oversight_labs_spep]"), m_oversight_labs_spep);
	RFX_Bool(pFX, _T("[oversight_labs_spiep]"), m_oversight_labs_spiep);
	RFX_Bool(pFX, _T("[oversight_labs_24hr_urine_uiep_upep]"), m_oversight_labs_24hr_urine_uiep_upep);
	RFX_Bool(pFX, _T("[oversight_labs_tsh]"), m_oversight_labs_tsh);
	RFX_Bool(pFX, _T("[oversight_labs_tft]"), m_oversight_labs_tft);
	RFX_Bool(pFX, _T("[oversight_labs_arthritis_panel]"), m_oversight_labs_arthritis_panel);
	RFX_Bool(pFX, _T("[oversight_labs_anemia_profile]"), m_oversight_labs_anemia_profile);
	RFX_Bool(pFX, _T("[oversight_labs_hemoccult_stools_x3]"), m_oversight_labs_hemoccult_stools_x3);
	RFX_Bool(pFX, _T("[oversight_labs_echo]"), m_oversight_labs_echo);
	RFX_Bool(pFX, _T("[oversight_labs_ekg]"), m_oversight_labs_ekg);
	RFX_Bool(pFX, _T("[oversight_labs_venous_doppler]"), m_oversight_labs_venous_doppler);
	RFX_Bool(pFX, _T("[oversight_labs_abi_w_excercise]"), m_oversight_labs_abi_w_excercise);
	RFX_Bool(pFX, _T("[oversight_labs_art_doppler]"), m_oversight_labs_art_doppler);
	RFX_Text(pFX, _T("[oversight_instruction]"), m_oversight_instruction);

}
/////////////////////////////////////////////////////////////////////////////
// Coversight_health diagnostics

#ifdef _DEBUG
void Coversight_health::AssertValid() const
{
	CRecordset::AssertValid();
}

void Coversight_health::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


