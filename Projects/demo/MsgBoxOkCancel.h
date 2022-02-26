#if !defined(AFX_MSGBOXOKCANCEL_H__A200C9D9_9012_4305_BB1F_92CA20FBE179__INCLUDED_)
#define AFX_MSGBOXOKCANCEL_H__A200C9D9_9012_4305_BB1F_92CA20FBE179__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgBoxOkCancel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MsgBoxOkCancel dialog

class MsgBoxOkCancel : public CDialog
{
// Construction
public:
	MsgBoxOkCancel(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(MsgBoxOkCancel)
	enum { IDD = IDD_DIALOG_MSG_OKCANCEL };
	CString	m_msg;
	//}}AFX_DATA
	CString m_title;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MsgBoxOkCancel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MsgBoxOkCancel)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGBOXOKCANCEL_H__A200C9D9_9012_4305_BB1F_92CA20FBE179__INCLUDED_)
