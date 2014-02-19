#pragma once


// CBillingView view

class CBillingView : public CView
{
	DECLARE_DYNCREATE(CBillingView)

public:
	CBillingView();           // protected constructor used by dynamic creation
	virtual ~CBillingView();

public:
	enum{ IDD = IDD_MDFMDIAPP_FORM };

	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


