#if !defined(AFX_PAGENETADDRRS485_H__F041A1A9_35BA_4E59_90EB_1B55053E998B__INCLUDED_)
#define AFX_PAGENETADDRRS485_H__F041A1A9_35BA_4E59_90EB_1B55053E998B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageNetAddrRS485.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// PageNetAddrRS485 dialog

class PageNetAddrRS485 : public CDialog
{
// Construction
public:
	PageNetAddrRS485(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(PageNetAddrRS485)
	enum { IDD = IDD_PAGE_NETADDR_RS485 };
	CEdit	m_edit_node_sn;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PageNetAddrRS485)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	int SetNetAddr(SSUNetAddr* netaddr);
	int GetNetAddr(SSUNetAddr* netaddr);

protected:

	// Generated message map functions
	//{{AFX_MSG(PageNetAddrRS485)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGENETADDRRS485_H__F041A1A9_35BA_4E59_90EB_1B55053E998B__INCLUDED_)
