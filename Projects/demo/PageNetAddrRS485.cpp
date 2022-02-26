// PageNetAddrRS485.cpp : implementation file
//

#include "stdafx.h"
#include "ssudemo.h"
#include "PageNetAddrRS485.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PageNetAddrRS485 dialog


PageNetAddrRS485::PageNetAddrRS485(CWnd* pParent /*=NULL*/)
	: CDialog(PageNetAddrRS485::IDD, pParent)
{
	//{{AFX_DATA_INIT(PageNetAddrRS485)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void PageNetAddrRS485::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PageNetAddrRS485)
	DDX_Control(pDX, IDC_EDIT_NODE_SN, m_edit_node_sn);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PageNetAddrRS485, CDialog)
	//{{AFX_MSG_MAP(PageNetAddrRS485)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PageNetAddrRS485 message handlers
int PageNetAddrRS485::SetNetAddr(SSUNetAddr* netaddr)
{
	if(IsWindow(GetSafeHwnd()) && SSU_NET_RS485 == netaddr->netType)
	{
		CString l_str;
		l_str.Format("%u", netaddr->rs485);
		m_edit_node_sn.SetWindowText(l_str);

		return 0;
	}
	else
	{
		return -1;
	}
}

int PageNetAddrRS485::GetNetAddr(SSUNetAddr* netaddr)
{
	if(IsWindow(GetSafeHwnd()))
	{
		CString l_str;
		m_edit_node_sn.GetWindowText(l_str);
		if(l_str.IsEmpty()) return -1;
		netaddr->rs485 = atoi(l_str); 

		netaddr->netType = SSU_NET_RS485;
		return 0;
	}
	else
	{
		return -1;
	}
}
