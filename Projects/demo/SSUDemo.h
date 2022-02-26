// SSUDemo.h : main header file for the SSUDEMO application
//

#if !defined(AFX_SSUDEMO_H__E33201B1_C95C_4AB3_A413_234CA3E28B5A__INCLUDED_)
#define AFX_SSUDEMO_H__E33201B1_C95C_4AB3_A413_234CA3E28B5A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSSUDemoApp:
// See SSUDemo.cpp for the implementation of this class
//

class CSSUDemoApp : public CWinApp
{
public:
	CSSUDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSSUDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSSUDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#define HEX(ch) (('0' <= ch && ch <= '9')?(ch-'0'):( ('a' <= ch && ch <= 'f')?(ch-'a'+10):( ('A' <= ch && ch <= 'F')?(ch-'A'+10):(0xFF))) )
int btoh(unsigned char* b, int size, CString& str);
int htob(const char* hstr, int len, unsigned char* b, int size);

#include "MsgBoxOk.h"
#include "MsgBoxOkCancel.h"

inline int MsgBox(LPCTSTR title, LPCTSTR msg, UINT type) // type: OKCANCEL, OK, YESNO, YESNOCANCEL
{
	if( type == MB_OKCANCEL )
	{
		MsgBoxOkCancel l_dlg;
		l_dlg.m_title=title;
		l_dlg.m_msg = msg;
		return l_dlg.DoModal();
	}
	else if( type == MB_OK )
	{
		MsgBoxOk l_dlg;
		l_dlg.m_title=title;
		l_dlg.m_msg = msg;
		return l_dlg.DoModal();
	}
	else
	{
		return IDOK;
	}
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.



#endif // !defined(AFX_SSUDEMO_H__E33201B1_C95C_4AB3_A413_234CA3E28B5A__INCLUDED_)
