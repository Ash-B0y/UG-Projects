// PaneNodeTCPIP.cpp : implementation file
//

#include "stdafx.h"
#include "ssudemo.h"
#include "PaneNodeTCPIP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PaneNodeTCPIP dialog


PaneNodeTCPIP::PaneNodeTCPIP(CWnd* pParent /*=NULL*/)
	: CDialog(PaneNodeTCPIP::IDD, pParent)
{
	//{{AFX_DATA_INIT(PaneNodeTCPIP)
	//}}AFX_DATA_INIT

	m_list_item_selected = -1;
}


void PaneNodeTCPIP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PaneNodeTCPIP)
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_edit_password);
	DDX_Control(pDX, IDC_EDIT_DEVSN, m_edit_devsn);
	DDX_Control(pDX, IDC_BTN_NODE_SET, m_btn_node_set);
	DDX_Control(pDX, IDC_LIST_NODES, m_list_nodes);
	DDX_Control(pDX, IDC_EDIT_NETMASK, m_edit_netmask);
	DDX_Control(pDX, IDC_EDIT_NETIP, m_edit_netip);
	DDX_Control(pDX, IDC_EDIT_GATEWAY, m_edit_gateway);
	DDX_Control(pDX, IDC_BTN_NODE_EXPLORE, m_btn_explore);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PaneNodeTCPIP, CDialog)
	//{{AFX_MSG_MAP(PaneNodeTCPIP)
	ON_BN_CLICKED(IDC_BTN_NODE_EXPLORE, OnBtnNodeExplore)
	ON_BN_CLICKED(IDC_BTN_NODE_SET, OnBtnNodeSet)
	ON_NOTIFY(NM_CLICK, IDC_LIST_NODES, OnClickListNodes)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_NODES, OnItemchangedListNodes)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PaneNodeTCPIP message handlers

void PaneNodeTCPIP::OnConnect()
{
	m_btn_explore.EnableWindow(FALSE);
	m_btn_node_set.EnableWindow(FALSE);
	m_edit_netip.EnableWindow(FALSE);
	m_edit_gateway.EnableWindow(FALSE);
	m_edit_netmask.EnableWindow(FALSE);
	m_list_nodes.EnableWindow(FALSE);
}

void PaneNodeTCPIP::OnDisconnect()
{
	m_btn_explore.EnableWindow(TRUE);
	m_list_nodes.EnableWindow(TRUE);

	m_edit_netip.EnableWindow(TRUE);
	m_edit_gateway.EnableWindow(TRUE);
	m_edit_netmask.EnableWindow(TRUE);
	m_btn_node_set.EnableWindow(TRUE);
}

static CListCtrl* sg_list_nodes = NULL;
static void NetAddrRecv(unsigned int devSn, SSUNetAddr* netAddr)
{
	if(netAddr->netType == SSU_NET_TCPIP && sg_list_nodes)
	{
		int     l_item; 
		CString l_str;

		l_str.Format("%010u", devSn);
		l_item = sg_list_nodes->InsertItem(sg_list_nodes->GetItemCount(), l_str);

		l_str.Format("%u.%u.%u.%u", netAddr->tcpip.netip[0], netAddr->tcpip.netip[1], netAddr->tcpip.netip[2], netAddr->tcpip.netip[3]);
		sg_list_nodes->SetItemText(l_item, 1, l_str);
		l_str.Format("%u.%u.%u.%u", netAddr->tcpip.gateway[0], netAddr->tcpip.gateway[1], netAddr->tcpip.gateway[2], netAddr->tcpip.gateway[3]);
		sg_list_nodes->SetItemText(l_item, 2, l_str);
		l_str.Format("%u.%u.%u.%u", netAddr->tcpip.netmask[0], netAddr->tcpip.netmask[1], netAddr->tcpip.netmask[2], netAddr->tcpip.netmask[3]);
		sg_list_nodes->SetItemText(l_item, 3, l_str);
		sg_list_nodes->Scroll(CSize(0, l_item));

		sg_list_nodes->Invalidate(FALSE);
	}
}

void PaneNodeTCPIP::OnBtnNodeExplore()
{
	// TODO: Add your control notification handler code here
	CWaitCursor   wait;
	CString       n_tmp_str;

	m_list_nodes.DeleteAllItems();
	m_edit_devsn.SetWindowText("");
	m_edit_netip.SetWindowText("");
	m_edit_gateway.SetWindowText("");
	m_edit_netmask.SetWindowText("");

	m_list_item_selected = -1;

	sg_list_nodes = &m_list_nodes;

	n_tmp_str.Format("255.255.255.255:%u", SSU_TCP_UDP_PORT);
	if(0 > SSUNodeExplore(n_tmp_str, SSU_NET_TCPIP, 2000, NetAddrRecv))
	{
		MsgBox("Error", "failed to explore nodes.", MB_OK);
	}
	sg_list_nodes = NULL;
}

void PaneNodeTCPIP::OnBtnNodeSet()
{
	// TODO: Add your control notification handler code here
	CWaitCursor  n_wait;

	CString       n_str;
	unsigned int  n_devSn;
	unsigned char n_password[4];
	SSUNetAddr    n_netaddr;

	m_edit_devsn.GetWindowText(n_str);
	if(n_str.IsEmpty())
	{
		MsgBox("Error", "the DevSN is empty.", MB_OK);
		return;
	}
	n_devSn = atoi(n_str);

	n_netaddr.netType = SSU_NET_TCPIP;
	m_edit_netip.GetWindowText(n_str);
	if(n_str.IsEmpty())
	{
		MsgBox("Error", "the NetIP is empty.", MB_OK);
		return;
	}
	::sscanf(n_str.LockBuffer(), "%u.%u.%u.%u", &n_netaddr.tcpip.netip[0], &n_netaddr.tcpip.netip[1], &n_netaddr.tcpip.netip[2], &n_netaddr.tcpip.netip[3]); 

	m_edit_gateway.GetWindowText(n_str);
	if(n_str.IsEmpty())
	{
		MsgBox("Error", "the GateWay is empty.", MB_OK);
		return;
	}
	::sscanf(n_str.LockBuffer(), "%u.%u.%u.%u", &n_netaddr.tcpip.gateway[0], &n_netaddr.tcpip.gateway[1], &n_netaddr.tcpip.gateway[2], &n_netaddr.tcpip.gateway[3]); 

	m_edit_netmask.GetWindowText(n_str);
	if(n_str.IsEmpty())
	{
		MsgBox("Error", "the NetMask is empty.", MB_OK);
		return;
	}
	::sscanf(n_str.LockBuffer(), "%u.%u.%u.%u", &n_netaddr.tcpip.netmask[0], &n_netaddr.tcpip.netmask[1], &n_netaddr.tcpip.netmask[2], &n_netaddr.tcpip.netmask[3]); 

	m_edit_password.GetWindowText(n_str);
	if(n_str.GetLength() != 8 || 0 > htob(n_str, n_str.GetLength(), n_password, sizeof(n_password)))
	{
		MsgBox("Error", "the connecting password is formated incorrectly", MB_OK);
		return;
	}

	n_str.Format("255.255.255.255:%u", SSU_TCP_UDP_PORT);
	if(0 > SSUNodeSet(n_str, n_password, n_devSn, &n_netaddr, 3000))
	{
		MsgBox("Error", "there are some errors when set the net address of node. you should try to ensure if it was successful.", MB_OK);
	}
	else
	{
		if(m_list_item_selected >= 0)
		{
			m_edit_devsn.GetWindowText(n_str);
			if(n_str == m_list_nodes.GetItemText(m_list_item_selected, 0))
			{
				m_edit_netip.GetWindowText(n_str);
				if(!n_str.IsEmpty())
				{
					m_list_nodes.SetItemText(m_list_item_selected, 1, n_str);
				}
				m_edit_gateway.GetWindowText(n_str);
				if(!n_str.IsEmpty())
				{
					m_list_nodes.SetItemText(m_list_item_selected, 2, n_str);
				}
				m_edit_netmask.GetWindowText(n_str);
				if(!n_str.IsEmpty())
				{
					m_list_nodes.SetItemText(m_list_item_selected, 3, n_str);
				}
			}
		}
	}	
}

BOOL PaneNodeTCPIP::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_list_nodes.InsertColumn(0, "devSn", LVCFMT_LEFT, 60); 
	m_list_nodes.InsertColumn(1, "netip", LVCFMT_LEFT, 90); 
	m_list_nodes.InsertColumn(2, "gateway", LVCFMT_LEFT, 90); 
	m_list_nodes.InsertColumn(3, "netmask", LVCFMT_LEFT, 90); 
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void PaneNodeTCPIP::OnClickListNodes(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void PaneNodeTCPIP::OnItemchangedListNodes(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here

	CString     n_str;

	m_list_item_selected = pNMListView->iItem;

	if(m_list_item_selected >= 0)
	{
		n_str = m_list_nodes.GetItemText(m_list_item_selected, 0);
		m_edit_devsn.SetWindowText(n_str);
		
		n_str = m_list_nodes.GetItemText(m_list_item_selected, 1);
		m_edit_netip.SetWindowText(n_str);

		n_str = m_list_nodes.GetItemText(m_list_item_selected, 2);
		m_edit_gateway.SetWindowText(n_str);

		n_str = m_list_nodes.GetItemText(m_list_item_selected, 3);
		m_edit_netmask.SetWindowText(n_str);
	}
	else
	{
		n_str.Empty();
		m_edit_devsn.SetWindowText(n_str);
		m_edit_netip.SetWindowText(n_str);
		m_edit_gateway.SetWindowText(n_str);
		m_edit_netmask.SetWindowText(n_str);
	}

	*pResult = 0;
}

void PaneNodeTCPIP::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	m_list_nodes.Invalidate();
	
	// Do not call CDialog::OnPaint() for painting messages
}
