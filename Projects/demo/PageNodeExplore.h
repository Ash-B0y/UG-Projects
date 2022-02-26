#if !defined(AFX_PAGENODEEXPLORE_H__4E2D1004_70B9_4118_BBF1_BC36A47F729C__INCLUDED_)
#define AFX_PAGENODEEXPLORE_H__4E2D1004_70B9_4118_BBF1_BC36A47F729C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageNodeExplore.h : header file
//

#include "PaneNodeTCPIP.h"
#include "PaneNodeRS485.h"

/////////////////////////////////////////////////////////////////////////////
// PageNodeExplore dialog

class PageNodeExplore : public CDialog
{
// Construction
public:
	PageNodeExplore(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(PageNodeExplore)
	enum { IDD = IDD_PAGE_NODE_EXPLORE };
	CTabCtrl	m_tab_panes;
	//}}AFX_DATA

	PaneNodeTCPIP m_pane_tcpip;
	PaneNodeRS485 m_pane_rs485;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PageNodeExplore)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

public:	
	void OnConnect();
	void OnDisconnect();

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(PageNodeExplore)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTabPanes(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGENODEEXPLORE_H__4E2D1004_70B9_4118_BBF1_BC36A47F729C__INCLUDED_)
