// PageNetAddrTCPIP.cpp : implementation file
//

#include "stdafx.h"
#include "ssudemo.h"
#include "PageNetAddrTCPIP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PageNetAddrTCPIP dialog


PageNetAddrTCPIP::PageNetAddrTCPIP(CWnd* pParent /*=NULL*/)
	: CDialog(PageNetAddrTCPIP::IDD, pParent)
{
	//{{AFX_DATA_INIT(PageNetAddrTCPIP)
	//}}AFX_DATA_INIT
}


void PageNetAddrTCPIP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PageNetAddrTCPIP)
	DDX_Control(pDX, IDC_EDIT_READER_IP, m_edit_netip);
	DDX_Control(pDX, IDC_EDIT_READER_MASK, m_edit_netmask);
	DDX_Control(pDX, IDC_EDIT_READER_GATEWAY, m_edit_gateway);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PageNetAddrTCPIP, CDialog)
	//{{AFX_MSG_MAP(PageNetAddrTCPIP)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PageNetAddrTCPIP message handlers

BOOL PageNetAddrTCPIP::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


int PageNetAddrTCPIP::SetNetAddr(SSUNetAddr* netaddr)
{
	if(IsWindow(GetSafeHwnd()) && SSU_NET_TCPIP == netaddr->netType)
	{
		CString l_str;
		l_str.Format("%u.%u.%u.%u", netaddr->tcpip.netip[0], netaddr->tcpip.netip[1], netaddr->tcpip.netip[2], netaddr->tcpip.netip[3]);
		m_edit_netip.SetWindowText(l_str);
		l_str.Format("%u.%u.%u.%u", netaddr->tcpip.gateway[0], netaddr->tcpip.gateway[1], netaddr->tcpip.gateway[2], netaddr->tcpip.gateway[3]);
		m_edit_gateway.SetWindowText(l_str);
		l_str.Format("%u.%u.%u.%u", netaddr->tcpip.netmask[0], netaddr->tcpip.netmask[1], netaddr->tcpip.netmask[2], netaddr->tcpip.netmask[3]);
		m_edit_netmask.SetWindowText(l_str);

		return 0;
	}
	else
	{
		return -1;
	}
}

int PageNetAddrTCPIP::GetNetAddr(SSUNetAddr* netaddr)
{
	if(IsWindow(GetSafeHwnd()))
	{
		CString l_str;
		m_edit_netip.GetWindowText(l_str);
		if(l_str.IsEmpty()) return -1;
		::sscanf(l_str.LockBuffer(), "%u.%u.%u.%u", &netaddr->tcpip.netip[0], &netaddr->tcpip.netip[1], &netaddr->tcpip.netip[2], &netaddr->tcpip.netip[3]); 
		m_edit_gateway.GetWindowText(l_str);
		if(l_str.IsEmpty()) return -1;
		::sscanf(l_str.LockBuffer(), "%u.%u.%u.%u", &netaddr->tcpip.gateway[0], &netaddr->tcpip.gateway[1], &netaddr->tcpip.gateway[2], &netaddr->tcpip.gateway[3]); 
		m_edit_netmask.GetWindowText(l_str);
		if(l_str.IsEmpty()) return -1;
		::sscanf(l_str.LockBuffer(), "%u.%u.%u.%u", &netaddr->tcpip.netmask[0], &netaddr->tcpip.netmask[1], &netaddr->tcpip.netmask[2], &netaddr->tcpip.netmask[3]); 

		netaddr->netType = SSU_NET_TCPIP;
		return 0;
	}
	else
	{
		return -1;
	}
}
