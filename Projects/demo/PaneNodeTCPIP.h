#if !defined(AFX_PANENODETCPIP_H__7CAA9EE1_BA9D_4507_A996_11A3B5C394D0__INCLUDED_)
#define AFX_PANENODETCPIP_H__7CAA9EE1_BA9D_4507_A996_11A3B5C394D0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PaneNodeTCPIP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// PaneNodeTCPIP dialog

class PaneNodeTCPIP : public CDialog
{
// Construction
public:
	PaneNodeTCPIP(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(PaneNodeTCPIP)
	enum { IDD = IDD_PANE_NODE_TCPIP };
	CEdit	m_edit_password;
	CEdit	m_edit_devsn;
	CButton	m_btn_node_set;
	CListCtrl	m_list_nodes;
	CIPAddressCtrl	m_edit_netmask;
	CIPAddressCtrl	m_edit_netip;
	CIPAddressCtrl	m_edit_gateway;
	CButton	m_btn_explore;
	//}}AFX_DATA

	int  m_list_item_selected;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PaneNodeTCPIP)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:	
	void OnConnect();
	void OnDisconnect();

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(PaneNodeTCPIP)
	afx_msg void OnBtnNodeExplore();
	afx_msg void OnBtnNodeSet();
	virtual BOOL OnInitDialog();
	afx_msg void OnClickListNodes(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchangedListNodes(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PANENODETCPIP_H__7CAA9EE1_BA9D_4507_A996_11A3B5C394D0__INCLUDED_)
