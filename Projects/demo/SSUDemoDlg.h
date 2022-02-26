// SSUDemoDlg.h : header file
//

#if !defined(AFX_SSUDEMODLG_H__E340F953_FDFB_42AD_872F_36BCB5487F7B__INCLUDED_)
#define AFX_SSUDEMODLG_H__E340F953_FDFB_42AD_872F_36BCB5487F7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "PageConfig.h"
#include "PageTagAccessEx.h"
#include "PageTagAccess.h"
#include "PageTagInventory.h"
#include "PageNodeExplore.h"

/////////////////////////////////////////////////////////////////////////////
// CSSUDemoDlg dialog

class CSSUDemoDlg : public CDialog
{
// Construction
public:
	CSSUDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSSUDemoDlg)
	enum { IDD = IDD_SSUDEMO_DIALOG };
	CButton	m_check_nocrc;
	CEdit	m_edit_version;
	CEdit	m_edit_model;
	CEdit	m_edit_devsn;
	CStatic	m_static_port;
	CStatic	m_static_nodeaddr;
	CStatic	m_static_ip;
	CStatic	m_static_comport;
	CButton	m_grp_com;
	CButton	m_grp_tcpip;
	CEdit	m_edit_password;
	CEdit	m_edit_customno;
	CButton	m_btn_disconnect;
	CButton	m_btn_connect;
	CEdit	m_edit_comport;
	CEdit	m_edit_port;
	CEdit	m_edit_nodeaddr;
	CEdit	m_edit_ip;
	CButton	m_radio_com;
	CButton	m_radio_rs485;
	CButton	m_radio_tcp;
	CButton	m_radio_udp;
	CTabCtrl	m_tab_pages;
	//}}AFX_DATA

	SSUCtx*          m_reader;
	PageConfig       m_page_config;
	PageTagAccessEx  m_page_tagaccess_ex;
	PageTagAccess    m_page_tagaccess;
	PageTagInventory m_page_inventory;
	PageNodeExplore  m_page_explore;

	CMutex       m_error_lock;
	CString      m_error_msg;
	int          m_error_flag;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSSUDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

public:
	void   PostErrorMsg(LPCSTR errmsg, BOOL error=TRUE);

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSSUDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnSelchangingTabPages(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeTabPages(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnConnect();
	afx_msg void OnBtnDisconnect();
	afx_msg void OnRadioCom();
	afx_msg void OnRadioTcp();
	afx_msg void OnRadioUdp();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg void OnRadioRs485();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SSUDEMODLG_H__E340F953_FDFB_42AD_872F_36BCB5487F7B__INCLUDED_)
