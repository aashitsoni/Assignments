// patient_episode.h : Declaration of the Cpatient_episode

#pragma once

// code generated on Wednesday, May 08, 2013, 2:00 PM

class Cpatient_episode : public CRecordset
{
public:
	Cpatient_episode(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(Cpatient_episode)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_patient_episode_code;
	long	m_patient_id;
	CTime	m_episode_start_date;
	CTime	m_episode_end_date;
	BOOL	m_episode_active;
	long	m_episode_total_minutes;
	CTime   m_episode_last_visit;
	CString m_episode_type;

	CString m_episode_dx_codes;
	CString m_episode_hh_agency_name;
	long	m_episode_hh_agency_code;
	CTime	m_episode_last_bill_date;
	CTime	m_episode_oversight_bill_date;
	int		m_episode_billing_status;

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
	int Open(long patient_id);
	int Open();
	int OpenForAdd();
	int OpenForModify(long patient_id,long patient_episode_id);
	int QueryPatientEpisode(long episode_id);
	BOOL SetDB(CDatabase* pDB);
	int OpenExclusive(long patient_id);
	int OpenForModifyWithEpisodeId(long patient_episode_id);



};


