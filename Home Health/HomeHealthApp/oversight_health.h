// oversight_health.h : Declaration of the Coversight_health

#pragma once

// code generated on Sunday, August 18, 2013, 11:52 PM

class Coversight_health : public CRecordset
{
public:
	Coversight_health(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(Coversight_health)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_patient_oversight_id;
	long	m_patient_episode_id;
	CStringW	m_patient_id;
	BOOL	m_studies_echo;
	CTime	m_oversight_health_date;
	BOOL	m_studies_EKG;
	long	m_oversight_hh_agency_code;	//foreign key to hh_agency_master
	BOOL	m_studies_MRI_Brain;
	BOOL	m_oversight_chart_reviewed;
	BOOL	m_oversight_medication_reviewed;
	BOOL	m_oversight_studies_reviewed;
	BOOL	m_oversight_studies_echo;
	BOOL	m_oversight_studies_ekg;
	BOOL	m_oversight_studies_mri_brain;
	BOOL	m_oversight_studies_carotid;
	BOOL	m_oversight_studies_art_dopler;
	BOOL	m_oversight_studies_venous_dopler;
	BOOL	m_oversight_studies_abi;
	BOOL	m_oversight_studies_cxr;
	BOOL	m_oversight_studies_abd_xray;
	BOOL	m_oversight_studies_mra_neck;
	BOOL	m_oversight_studies_ct_scan_brain;
	BOOL	m_oversight_studies_ct_scan_abd_pelvis;
	BOOL	m_oversight_studies_ct_scan_other;
	CStringW	m_oversight_studies_ct_scan_other_desc;
	BOOL	m_oversight_need_appointment;
	CTime	m_oversight_next_appointment;
	CTime	m_oversight_last_appointment;
	BOOL	m_oversight_labs_ordered;
	BOOL	m_oversight_labs_chem12;
	BOOL	m_oversight_labs_cbc;
	BOOL	m_oversight_labs_b12_folate;
	BOOL	m_oversight_labs_cxr;
	BOOL	m_oversight_labs_vita_d2_3;
	BOOL	m_oversight_labs_flp;
	BOOL	m_oversight_labs_hepatitis_panel;
	BOOL	m_oversight_labs_hbg_ac;
	BOOL	m_oversight_labs_24hr_urine_ccl;
	BOOL	m_oversight_labs_urine_microabulmin;
	BOOL	m_oversight_labs_va_with_cs;
	BOOL	m_oversight_labs_pth;
	BOOL	m_oversight_labs_spep;
	BOOL	m_oversight_labs_spiep;
	BOOL	m_oversight_labs_24hr_urine_uiep_upep;
	BOOL	m_oversight_labs_tsh;
	BOOL	m_oversight_labs_tft;
	BOOL	m_oversight_labs_arthritis_panel;
	BOOL	m_oversight_labs_anemia_profile;
	BOOL	m_oversight_labs_hemoccult_stools_x3;
	BOOL	m_oversight_labs_echo;
	BOOL	m_oversight_labs_ekg;
	BOOL	m_oversight_labs_venous_doppler;
	BOOL	m_oversight_labs_abi_w_excercise;
	BOOL	m_oversight_labs_art_doppler;
	CStringW	m_oversight_instruction;

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


