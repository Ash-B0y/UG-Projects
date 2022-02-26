#if !defined(AFX_PAGETAGACCESS_H__C35A0849_C2B7_43E1_BBA8_148F88AFFAED__INCLUDED_)
#define AFX_PAGETAGACCESS_H__C35A0849_C2B7_43E1_BBA8_148F88AFFAED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageTagAccess.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// PageTagAccess dialog

class PageTagAccess : public CDialog
{
// Construction
public:
	PageTagAccess(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(PageTagAccess)
	enum { IDD = IDD_PAGE_ACCESS };
	CButton	m_check_write_continue;
	CEdit	m_edit_emsg;
	CButton	m_check_read_continue;
	CButton	m_chk_writeany;
	CButton	m_chk_readany;
	CEdit	m_edit_pwd_read;
	CEdit	m_edit_pwd_kill;
	CEdit	m_edit_pwd_acc;
	CEdit	m_edit_word_write;
	CEdit	m_edit_words_read;
	CEdit	m_edit_start_write;
	CEdit	m_edit_start_read;
	CEdit	m_edit_pwd_write;
	CEdit	m_edit_pwd_lock;
	CEdit	m_edit_epc;
	CEdit	m_edit_data_write;
	CEdit	m_edit_data_read;
	CComboBox	m_combo_sect_write;
	CComboBox	m_combo_sect_read;
	CComboBox	m_combo_sect_lock;
	CComboBox	m_combo_opt_lock;
	CButton	m_btn_tagquery;
	CButton	m_btn_tagwrite;
	CButton	m_btn_taglock;
	CButton	m_btn_tagkill;
	CButton	m_btn_tagread;
	//}}AFX_DATA

	volatile BOOL m_should_break;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PageTagAccess)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
 
public:	
	void OnConnect();
	void OnDisconnect();
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(PageTagAccess)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBtnTagquery();
	afx_msg void OnBtnTagRead();
	afx_msg void OnBtnTagWrite();
	afx_msg void OnBtnTagLock();
	afx_msg void OnBtnTagKill();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGETAGACCESS_H__C35A0849_C2B7_43E1_BBA8_148F88AFFAED__INCLUDED_)
