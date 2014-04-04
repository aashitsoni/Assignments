#pragma once
class CEpisodeListDrawHelper
{

	CListCtrl* _listCtrlObj;

public:
	int SetListControlObj(CListCtrl* pObj);

	CEpisodeListDrawHelper();
	int InitializeColumn();
	int PopulateData(long patient_episode_id);

	~CEpisodeListDrawHelper(void);
};

