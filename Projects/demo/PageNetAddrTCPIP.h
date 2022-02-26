#if !defined(AFX_PAGENETADDRTCPIP_H__1E8EAB9A_D349_4CED_8A37_3DF7C42DED18__INCLUDED_)
#define AFX_PAGENETADDRTCPIP_H__1E8EAB9A_D349_4CED_8A37_3DF7C42DED18__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageNetAddrTCPIP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// PageNetAddrTCPIP dialog

class PageNetAddrTCPIP : public CDialog
{
// Construction
public:
	PageNetAddrTCPIP(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(PageNetAddrTCPIP)
	enum { IDD = IDD_PAGE_NETADDR_TCPIP };
	CIPAddressCtrl	m_edit_netip;
	CIPAddressCtrl	m_edit_netmask;
	CIPAddressCtrl	m_edit_gateway;
	//}}AFX_DATA


public:
	int  SetNetAddr(SSUNetAddr* netaddr);
	int  GetNetAddr(SSUNetAddr* netaddr);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PageNetAddrTCPIP)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(PageNetAddrTCPIP)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGENETADDRTCPIP_H__1E8EAB9A_D349_4CED_8A37_3DF7C42DED18__INCLUDED_)
