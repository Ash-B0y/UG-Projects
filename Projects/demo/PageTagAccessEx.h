#if !defined(AFX_PAGETAGACCESSEX_H__4D2004F9_B96F_4EB8_B713_171747179A1E__INCLUDED_)
#define AFX_PAGETAGACCESSEX_H__4D2004F9_B96F_4EB8_B713_171747179A1E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageTagAccessEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// PageTagAccessEx dialog

class PageTagAccessEx : public CDialog
{
// Construction
public:
	PageTagAccessEx(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(PageTagAccessEx)
	enum { IDD = IDD_PAGE_ACCESS_EX };
	CButton	m_check_kilpwd;
	CButton	m_check_accpwd;
	CEdit	m_edit_write_pwd_kill;
	CEdit	m_edit_write_pwd_access;
	CEdit	m_edit_kill_pwd;
	CEdit	m_edit_write_epc;
	CEdit	m_edit_words_write_usr;
	CEdit	m_edit_words_read_usr;
	CEdit	m_edit_words_read_tid;
	CEdit	m_edit_start_write_usr;
	CEdit	m_edit_start_read_usr;
	CEdit	m_edit_start_read_tid;
	CEdit	m_edit_accpwd;
	CEdit	m_edit_epc;
	CEdit	m_edit_emsg;
	CEdit	m_edit_data_write_usr;
	CEdit	m_edit_data_read_usr;
	CEdit	m_edit_data_read_tid;
	CButton	m_btn_tag_query;
	CButton	m_btn_tag_write_usr;
	CButton	m_btn_tag_write_pwd;
	CButton	m_btn_tag_write_epc;
	CButton	m_btn_tag_read_usr;
	CButton	m_btn_tag_read_tid;
	CButton	m_btn_tag_lock_usr;
	CButton	m_btn_tag_lock_epc;
	CButton	m_btn_tag_kill_ex;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PageTagAccessEx)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:	
	void OnConnect();
	void OnDisconnect();

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(PageTagAccessEx)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnTagquery();
	afx_msg void OnBtnTagReadTid();
	afx_msg void OnBtnTagReadUsr();
	afx_msg void OnBtnTagWritePwd();
	afx_msg void OnBtnTagWriteEpc();
	afx_msg void OnBtnTagWriteUsr();
	afx_msg void OnBtnTagKillEx();
	afx_msg void OnBtnTagLockEpc();
	afx_msg void OnBtnTagLockUsr();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGETAGACCESSEX_H__4D2004F9_B96F_4EB8_B713_171747179A1E__INCLUDED_)
