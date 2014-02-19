#pragma once
class CHomeHealthDatabase
{
	CString m_connectionString;
	CDatabase* m_pDatabase;

public:
	CHomeHealthDatabase(CString* szConnectionString = NULL);
	~CHomeHealthDatabase(void);
	int Open();
	int Close();
	int Commit();
	int Rollback();
	CDatabase* GetDatabase();
	int Init();

//DSN=MS Access Database;DBQ=C:\\aks\\SRC\\Home Health\\HealthDatabse.accdb;DefaultDir=C:\\aks\\SRC\\Home Health\\;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;
	CString m_szDSN;
	CString m_szDBQ;
	CString m_szDefaultDIR;
	int		m_nDriverID;
	CString m_szFIL;
	int		m_nMaxBuffer;
	int		m_nPageTimeout;
	CString m_szUID;
	CString m_szConnectionString;



};

