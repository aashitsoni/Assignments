#pragma once
class CPatientBilling
{
	long m_patientId;
public:
	CPatientBilling(long patient_id);
	~CPatientBilling(void);
	int ReportPatientWith30MinsBillTime(void);
};

