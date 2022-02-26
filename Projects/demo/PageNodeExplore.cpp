// PageNodeExplore.cpp : implementation file
//

#include "stdafx.h"
#include "ssudemo.h"
#include "PageNodeExplore.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PageNodeExplore dialog


PageNodeExplore::PageNodeExplore(CWnd* pParent /*=NULL*/)
	: CDialog(PageNodeExplore::IDD, pParent)
{
	//{{AFX_DATA_INIT(PageNodeExplore)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void PageNodeExplore::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PageNodeExplore)
	DDX_Control(pDX, IDC_TAB_PANES, m_tab_panes);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PageNodeExplore, CDialog)
	//{{AFX_MSG_MAP(PageNodeExplore)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_PANES, OnSelchangeTabPanes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PageNodeExplore message handlers

void PageNodeExplore::OnConnect()
{
	m_tab_panes.EnableWindow(FALSE);
	m_pane_tcpip.OnConnect();
	m_pane_rs485.OnConnect();
}

void PageNodeExplore::OnDisconnect()
{
	m_tab_panes.EnableWindow(TRUE);
	m_pane_tcpip.OnDisconnect();
	m_pane_rs485.OnDisconnect();
}



BOOL PageNodeExplore::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_pane_tcpip.Create(PaneNodeTCPIP::IDD, this);//&m_tab_subjects);
	m_pane_rs485.Create(PaneNodeRS485::IDD, this);//&m_tab_subjects);
	
	m_tab_panes.InsertItem(0, "TCPIP");
	m_tab_panes.InsertItem(1, "RS485");
	m_tab_panes.SetCurSel(0);
	m_pane_tcpip.ShowWindow(SW_SHOW);

	{
		CRect  l_rect_wnd, l_rect_item;
		m_tab_panes.GetClientRect(l_rect_wnd);
		m_tab_panes.GetItemRect(0, l_rect_item);
		l_rect_wnd.DeflateRect(2, l_rect_item.Height() + 3, 2, 2);

		//
		m_tab_panes.ClientToScreen(l_rect_wnd);
		ScreenToClient(l_rect_wnd);
		//

		m_pane_tcpip.MoveWindow(l_rect_wnd, FALSE);
		m_pane_rs485.MoveWindow(l_rect_wnd, FALSE);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void PageNodeExplore::OnSelchangeTabPanes(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CWaitCursor n_wait;
	// TODO: Add your control notification handler code here
	int n_cur_sel = m_tab_panes.GetCurSel();

	m_pane_tcpip.ShowWindow(SW_HIDE);
	m_pane_rs485.ShowWindow(SW_HIDE);

	switch(n_cur_sel)
	{
	case 0:
		m_pane_tcpip.ShowWindow(SW_SHOW);
		break;
	case 1:
		m_pane_rs485.ShowWindow(SW_SHOW);
		break;
	default:
		break;
	}
	
	*pResult = 0;
}
