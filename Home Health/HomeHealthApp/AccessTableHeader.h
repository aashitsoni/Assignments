
// access table declaration

#pragma once

template <class T> HealthTable : public CRecordset {
public :
	HealthTable(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(HealthTable);

	T _obj;

	virtual CString GetDefaultConnect();
	virtual CString GetDefaultSQL();
	virtual CString DoFieldExchange(CFieldExchange* pFX);
	int Open();
	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext) const;
#endif
};
