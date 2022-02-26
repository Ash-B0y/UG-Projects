#if !defined(AFX_PANENODERS485_H__CC98C812_C225_42C1_975C_E7D105825043__INCLUDED_)
#define AFX_PANENODERS485_H__CC98C812_C225_42C1_975C_E7D105825043__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PaneNodeRS485.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// PaneNodeRS485 dialog

class PaneNodeRS485 : public CDialog
{
// Construction
public:
	PaneNodeRS485(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(PaneNodeRS485)
	enum { IDD = IDD_PANE_NODE_RS485 };
	CEdit	m_edit_comport;
	CButton	m_btn_node_set;
	CButton	m_btn_node_explore;
	CEdit	m_edit_devsn;
	CEdit	m_edit_password;
	CEdit	m_edit_netaddr;
	CListCtrl	m_list_nodes;
	//}}AFX_DATA

	int    m_list_item_selected;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PaneNodeRS485)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	void OnConnect();
	void OnDisconnect();

protected:

	// Generated message map functions
	//{{AFX_MSG(PaneNodeRS485)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnNodeExplore();
	afx_msg void OnBtnNodeSet();
	afx_msg void OnItemchangedListNodes(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PANENODERS485_H__CC98C812_C225_42C1_975C_E7D105825043__INCLUDED_)
