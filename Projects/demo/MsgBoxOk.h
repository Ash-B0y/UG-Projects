#if !defined(AFX_MSGBOXOK_H__6F590A70_34C8_4735_9320_DD0ED03D2EB5__INCLUDED_)
#define AFX_MSGBOXOK_H__6F590A70_34C8_4735_9320_DD0ED03D2EB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsgBoxOk.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MsgBoxOk dialog

class MsgBoxOk : public CDialog
{
// Construction
public:
	MsgBoxOk(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(MsgBoxOk)
	enum { IDD = IDD_DIALOG_MSG_OK };
	CString	m_msg;
	//}}AFX_DATA
	CString m_title;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MsgBoxOk)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(MsgBoxOk)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSGBOXOK_H__6F590A70_34C8_4735_9320_DD0ED03D2EB5__INCLUDED_)
