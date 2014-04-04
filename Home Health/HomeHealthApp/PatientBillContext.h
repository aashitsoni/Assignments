#pragma once
#include "patient_master.h"
#include "patient_billing.h"
#include "patient_episode.h"
#include "oversight_billing.h"


class CPatientBillContext
{
	Cpatient_master* _patient;
	Cpatient_billing* _billing;
	Cpatient_episode* _episode;
	Coversight_billing* _oversight;

	int patient_billing_context;
	int patient_bill_number;


public:

	int setContextType(int print_type);
	int setPatientBillNumber(long bill_number);
	int OpenBillingContext();

	Cpatient_master* GetPatient();
	Cpatient_episode* GetEpisode();
	Coversight_billing* GetOversight();
	Cpatient_billing* GetPatientBill();


	CPatientBillContext(void);
	~CPatientBillContext(void);
};

