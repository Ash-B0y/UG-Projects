#if !defined(AFX_PAGECONFIG_H__30AFC4BE_5F06_4A09_9E93_88CA4B9E02B0__INCLUDED_)
#define AFX_PAGECONFIG_H__30AFC4BE_5F06_4A09_9E93_88CA4B9E02B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageConfig.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// PageConfig dialog

class PageConfig : public CDialog
{
// Construction 
public:
	PageConfig(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(PageConfig)
	enum { IDD = IDD_PAGE_CONFIG };
	CEdit	m_edit_invt_idle_min;
	CEdit	m_edit_invt_idle_fract;
	CComboBox	m_combo_invt_rspTm;
	CTabCtrl	m_tab_netaddr;
	CButton	m_btn_netaddr_set;
	CButton	m_btn_netaddr_get;
	CButton	m_btn_connpwd_set;
	CComboBox	m_combo_rf_gain;
	CComboBox	m_combo_invt_buftm;
	CComboBox	m_combo_invt_qminTries;
	CComboBox	m_combo_invt_qmin;
	CComboBox	m_combo_invt_qmax;
	CEdit	m_edit_rf_step;
	CEdit	m_edit_rf_deviation;
	CEdit	m_edit_rf_center;
	CEdit	m_edit_conn_pwd;
	CButton	m_check_rf_antmask_b3;
	CButton	m_check_rf_antmask_b0;
	CButton	m_check_rf_antmask_b2;
	CButton	m_check_rf_antmask_b1;
	CComboBox	m_combo_beep_enable;
	CComboBox	m_combo_invt_sess;
	CButton	m_btn_config_set;
	CButton	m_btn_config_get;
	//}}AFX_DATA

	CWnd*      m_netaddr_page;
	SSUNetAddr m_netaddr;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PageConfig)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:	
	void OnConnect();
	void OnDisconnect();
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(PageConfig)
	afx_msg void OnBtnConfigGet();
	afx_msg void OnBtnConfigSet();
	afx_msg void OnBtnConnpwdSet();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnNetaddrGet();
	afx_msg void OnBtnNetAddrSet();
	afx_msg void OnChangeEDITRFDeviation();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGECONFIG_H__30AFC4BE_5F06_4A09_9E93_88CA4B9E02B0__INCLUDED_)
