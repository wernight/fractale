// Fractale.h : main header file for the FRACTALE application
//

#if !defined(AFX_FRACTALE_H__33D86465_7DD2_11D3_A413_A5A5A5A5A5A5__INCLUDED_)
#define AFX_FRACTALE_H__33D86465_7DD2_11D3_A413_A5A5A5A5A5A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFractaleApp:
// See Fractale.cpp for the implementation of this class
//

class CFractaleApp : public CWinApp
{
public:
	CFractaleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFractaleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFractaleApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRACTALE_H__33D86465_7DD2_11D3_A413_A5A5A5A5A5A5__INCLUDED_)
