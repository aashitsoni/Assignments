#include "stdafx.h"
#include "HomeHealthDatabase.h"


CHomeHealthDatabase::CHomeHealthDatabase(CString * pSzConnectionString)
{
	m_pDatabase = 0;
}


CHomeHealthDatabase::~CHomeHealthDatabase(void)
{
	if(m_pDatabase)
		m_pDatabase->Close();
}

int CHomeHealthDatabase::Init()
{
		CString szPath,szDB;
		HANDLE hFind = INVALID_HANDLE_VALUE;
		WIN32_FIND_DATA FindFileData;

		szPath.LoadString(IDS_STRING_DATABASE_PATH);
		szDB.LoadString(IDS_STRING_HOMEHEALTH_DATABASE);

	//	m_connectionString = 	_T("DSN=MS Access Database;DBQ=C:\\aks\\SRC\\Home Health\\HealthDatabse.accdb;DefaultDir=C:\\aks\\SRC\\Home Health\\;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");

		m_szDSN = _T("MS Access Database");
		m_szDBQ = szPath+szDB;
		m_szDefaultDIR = szPath;
		m_nDriverID = 25;
		m_szFIL = _T("MS Access");
		m_nMaxBuffer = 2048;
		m_nPageTimeout = 5;
		m_szUID = _T("Admin");

		hFind = FindFirstFile(m_szDBQ,&FindFileData);
		

		if(hFind == INVALID_HANDLE_VALUE)
		{
			// File not found.

			//Lets do something up here

			m_szConnectionString = _T("");
		}
		else
		{
		m_szConnectionString.Format(_T("DSN=%s;DBQ=%s;DefaultDir=%s;DriverId=%d;FIL=%s;MaxBufferSize=%d;PageTimeout=%d;UID=%s;"),
			m_szDSN,
			m_szDBQ,
			m_szDefaultDIR,
			m_nDriverID,
			m_szFIL,
			m_nMaxBuffer,
			m_nPageTimeout,
			m_szUID),
		m_connectionString = m_szConnectionString;
		}

	return 0;
}


int CHomeHealthDatabase::Open()
{
	if(m_szConnectionString.GetLength() <= 0)
	{

		CFileDialog FileDlg(TRUE,_T("accdb"),_T("HealthDatabase"));
		if(IDOK == FileDlg.DoModal())
		{
			CString szFileName = FileDlg.GetFileName();
			CString szFilePath = FileDlg.GetPathName();

			m_szConnectionString = szFilePath;
			m_connectionString = m_szConnectionString;

		}
		else
			return -1;


		// Lets advise user to point to the home health database.
	}


	if(m_szConnectionString.GetLength() > 0)
	{
		m_pDatabase = new CDatabase();
		if(NULL == m_pDatabase)
			return -1;
		if( 0 == m_pDatabase->OpenEx(m_connectionString,CDatabase::noOdbcDialog))
			return -1;
	}
	else
		return -1;

	return 0;
}

int CHomeHealthDatabase::Close()
{
	if(m_pDatabase->IsOpen() == TRUE)
		m_pDatabase->Close();
	return 0;
}
int CHomeHealthDatabase::Commit()
{
	if(m_pDatabase->IsOpen() == TRUE)
		if( TRUE == m_pDatabase->CommitTrans())
			return 0;
	return -1;
}

int CHomeHealthDatabase::Rollback()
{
	if(m_pDatabase->IsOpen() == TRUE)
		if(TRUE == m_pDatabase->Rollback())
			return 0;
	return -1;
}

CDatabase* CHomeHealthDatabase::GetDatabase()
{
	return m_pDatabase;
}