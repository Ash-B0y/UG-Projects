// PaneNodeRS485.cpp : implementation file
//

#include "stdafx.h"
#include "ssudemo.h"
#include "PaneNodeRS485.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PaneNodeRS485 dialog


PaneNodeRS485::PaneNodeRS485(CWnd* pParent /*=NULL*/)
	: CDialog(PaneNodeRS485::IDD, pParent)
{
	//{{AFX_DATA_INIT(PaneNodeRS485)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_list_item_selected = -1;
}


void PaneNodeRS485::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PaneNodeRS485)
	DDX_Control(pDX, IDC_EDIT_COMPORT, m_edit_comport);
	DDX_Control(pDX, IDC_BTN_NODE_SET, m_btn_node_set);
	DDX_Control(pDX, IDC_BTN_NODE_EXPLORE, m_btn_node_explore);
	DDX_Control(pDX, IDC_EDIT_DEVSN, m_edit_devsn);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_edit_password);
	DDX_Control(pDX, IDC_EDIT_NETADDR, m_edit_netaddr);
	DDX_Control(pDX, IDC_LIST_NODES, m_list_nodes);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PaneNodeRS485, CDialog)
	//{{AFX_MSG_MAP(PaneNodeRS485)
	ON_BN_CLICKED(IDC_BTN_NODE_EXPLORE, OnBtnNodeExplore)
	ON_BN_CLICKED(IDC_BTN_NODE_SET, OnBtnNodeSet)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_NODES, OnItemchangedListNodes)
	ON_WM_CANCELMODE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PaneNodeRS485 message handlers

BOOL PaneNodeRS485::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_list_nodes.InsertColumn(0, "devSn", LVCFMT_LEFT, 110); 
	m_list_nodes.InsertColumn(1, "netAddr", LVCFMT_LEFT, 80); 
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

static CListCtrl* sg_list_nodes = NULL;
static void NetAddrRecv(unsigned int devSn, SSUNetAddr* netAddr)
{
	if(netAddr->netType == SSU_NET_RS485 && sg_list_nodes)
	{
		int     l_item; 
		CString l_str;

		l_str.Format("%010u", devSn);
		l_item = sg_list_nodes->InsertItem(sg_list_nodes->GetItemCount(), l_str);

		l_str.Format("%u", netAddr->rs485);
		sg_list_nodes->SetItemText(l_item, 1, l_str);
		sg_list_nodes->Scroll(CSize(0, l_item));

		sg_list_nodes->Invalidate(FALSE);
	}
}

void PaneNodeRS485::OnBtnNodeExplore() 
{
	// TODO: Add your control notification handler code here
	CWaitCursor   wait;
	CString       n_tmp_str;

	m_list_nodes.DeleteAllItems();
	m_edit_devsn.SetWindowText("");
	m_edit_netaddr.SetWindowText("");

	m_list_item_selected = -1;

	sg_list_nodes = &m_list_nodes;

	m_edit_comport.GetWindowText(n_tmp_str);
	if(n_tmp_str.IsEmpty())
	{
		MsgBox("Error", "ComPort should not be empty.", MB_OK);
		return;
	}

	n_tmp_str += ":255";
	if(0 > SSUNodeExplore(n_tmp_str, SSU_NET_RS485, 5500, NetAddrRecv))
	{
		MsgBox("Error", "failed to explore nodes.", MB_OK);
	}
	sg_list_nodes = NULL;	
}

void PaneNodeRS485::OnBtnNodeSet() 
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

	n_netaddr.netType = SSU_NET_RS485;
	m_edit_netaddr.GetWindowText(n_str);
	if(n_str.IsEmpty())
	{
		MsgBox("Error", "the NetAddr should not be empty.", MB_OK);
		return;
	}
	n_netaddr.rs485 = atoi(n_str);

	m_edit_password.GetWindowText(n_str);
	if(n_str.GetLength() != 8 || 0 > htob(n_str, n_str.GetLength(), n_password, sizeof(n_password)))
	{
		MsgBox("Error", "the connecting password is formated incorrectly", MB_OK);
		return;
	}

	m_edit_comport.GetWindowText(n_str);
	if(n_str.IsEmpty())
	{
		MsgBox("Error", "ComPort should not be empty.", MB_OK);
		return;
	}

	n_str += ":255";
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
				m_edit_netaddr.GetWindowText(n_str);
				if(!n_str.IsEmpty())
				{
					m_list_nodes.SetItemText(m_list_item_selected, 1, n_str);
				}
			}
		}
	}		
}

void PaneNodeRS485::OnItemchangedListNodes(NMHDR* pNMHDR, LRESULT* pResult) 
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
		m_edit_netaddr.SetWindowText(n_str);
	}
	else
	{
		n_str.Empty();
		m_edit_devsn.SetWindowText(n_str);
		m_edit_netaddr.SetWindowText(n_str);
	}

	*pResult = 0;
}

void PaneNodeRS485::OnConnect()
{
	m_btn_node_explore.EnableWindow(FALSE);
	m_btn_node_set.EnableWindow(FALSE);
	m_edit_netaddr.EnableWindow(FALSE);
	m_list_nodes.EnableWindow(FALSE);
}

void PaneNodeRS485::OnDisconnect()
{
	m_btn_node_explore.EnableWindow(TRUE);
	m_list_nodes.EnableWindow(TRUE);

	m_edit_netaddr.EnableWindow(TRUE);
	m_btn_node_set.EnableWindow(TRUE);
}

void PaneNodeRS485::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	m_list_nodes.Invalidate(FALSE);
	
	// Do not call CDialog::OnPaint() for painting messages
}
