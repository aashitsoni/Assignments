// BillingView.cpp : implementation file
//

#include "stdafx.h"
#include "HomeHealthApp.h"
#include "BillingView.h"


// CBillingView

IMPLEMENT_DYNCREATE(CBillingView, CView)

CBillingView::CBillingView()
{

}

CBillingView::~CBillingView()
{
}

BEGIN_MESSAGE_MAP(CBillingView, CView)
END_MESSAGE_MAP()


// CBillingView drawing

void CBillingView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CBillingView diagnostics

#ifdef _DEBUG
void CBillingView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CBillingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CBillingView message handlers
