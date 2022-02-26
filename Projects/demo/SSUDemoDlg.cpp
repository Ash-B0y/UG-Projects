// SSUDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SSUDemo.h"
#include "SSUDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define MY_TIMER_SHOW_ERRMSG          1
#define MY_TIMER_SHOW_ERRSMG_INTERVAL 100

/////////////////////////////////////////////////////////////////////////////
// CSSUDemoDlg dialog

CSSUDemoDlg::CSSUDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSSUDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSSUDemoDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_reader = NULL;
}

void CSSUDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSSUDemoDlg)
	DDX_Control(pDX, IDC_CHECK_NOCRC, m_check_nocrc);
	DDX_Control(pDX, IDC_EDIT_VERSION, m_edit_version);
	DDX_Control(pDX, IDC_EDIT_MODEL, m_edit_model);
	DDX_Control(pDX, IDC_EDIT_DEVSN, m_edit_devsn);
	DDX_Control(pDX, IDC_STATIC_PORT, m_static_port);
	DDX_Control(pDX, IDC_STATIC_NODEADDR, m_static_nodeaddr);
	DDX_Control(pDX, IDC_STATIC_IP, m_static_ip);
	DDX_Control(pDX, IDC_STATIC_COMPORT, m_static_comport);
	DDX_Control(pDX, IDC_GRP_COM, m_grp_com);
	DDX_Control(pDX, IDC_GRP_TCPIP, m_grp_tcpip);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_edit_password);
	DDX_Control(pDX, IDC_EDIT_CUSTOMNO, m_edit_customno);
	DDX_Control(pDX, IDC_BTN_DISCONNECT, m_btn_disconnect);
	DDX_Control(pDX, IDC_BTN_CONNECT, m_btn_connect);
	DDX_Control(pDX, IDC_EDIT_COMPORT, m_edit_comport);
	DDX_Control(pDX, IDC_EDIT_PORT, m_edit_port);
	DDX_Control(pDX, IDC_EDIT_NODEADDR, m_edit_nodeaddr);
	DDX_Control(pDX, IDC_EDIT_IP, m_edit_ip);
	DDX_Control(pDX, IDC_RADIO_COM, m_radio_com);
	DDX_Control(pDX, IDC_RADIO_RS485, m_radio_rs485);
	DDX_Control(pDX, IDC_RADIO_TCP, m_radio_tcp);
	DDX_Control(pDX, IDC_RADIO_UDP, m_radio_udp);
	DDX_Control(pDX, IDC_TAB_PAGES, m_tab_pages);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSSUDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CSSUDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGING, IDC_TAB_PAGES, OnSelchangingTabPages)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_PAGES, OnSelchangeTabPages)
	ON_BN_CLICKED(IDC_BTN_CONNECT, OnBtnConnect)
	ON_BN_CLICKED(IDC_BTN_DISCONNECT, OnBtnDisconnect)
	ON_BN_CLICKED(IDC_RADIO_COM, OnRadioCom)
	ON_BN_CLICKED(IDC_RADIO_UDP, OnRadioTcp)
	ON_BN_CLICKED(IDC_RADIO_UDP, OnRadioUdp)
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_RADIO_TCP, OnRadioTcp)
	ON_BN_CLICKED(IDC_RADIO_RS485, OnRadioRs485)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSSUDemoDlg message handlers
void CSSUDemoDlg::PostErrorMsg(LPCSTR errmsg, int flag)
{
	m_error_lock.Lock();
	m_error_flag = flag;
	m_error_msg = errmsg;
	m_error_lock.Unlock();
}

BOOL CSSUDemoDlg::OnInitDialog()
{
	CString  n_tmp_str;
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_edit_password.SetWindowText("00000000");
	m_edit_customno.SetWindowText("0");
	m_edit_comport.SetWindowText("COM3");
	n_tmp_str.Format("%u", SSU_TCP_UDP_PORT);
	m_edit_port.SetWindowText(n_tmp_str);
	m_radio_com.SetCheck(TRUE);
	OnRadioCom();

	m_page_config.Create(PageConfig::IDD, this);//&m_tab_subjects);
	m_page_tagaccess_ex.Create(PageTagAccessEx::IDD, this);//&m_tab_subjects);
	m_page_tagaccess.Create(PageTagAccess::IDD, this);//&m_tab_subjects);
	m_page_inventory.Create(PageTagInventory::IDD, this);//&m_tab_subjects);
	m_page_explore.Create(PageNodeExplore::IDD, this);//&m_tab_subjects);
	
	m_tab_pages.InsertItem(0, "NodeExplore");
	m_tab_pages.InsertItem(1, "TagInventory");
	m_tab_pages.InsertItem(2, "TagAccess");
	m_tab_pages.InsertItem(3, "TagAccessEx");
	m_tab_pages.InsertItem(4, "Config");
	m_tab_pages.SetCurSel(0);

	{
		CRect  l_rect_wnd, l_rect_item;
		m_tab_pages.GetClientRect(l_rect_wnd);
		m_tab_pages.GetItemRect(0, l_rect_item);
		l_rect_wnd.DeflateRect(2, l_rect_item.Height() + 3, 2, 2);

		//
		m_tab_pages.ClientToScreen(l_rect_wnd);
		ScreenToClient(l_rect_wnd);
		//

		m_page_explore.MoveWindow(l_rect_wnd, FALSE);
		m_page_explore.ShowWindow(SW_SHOW);

		m_page_inventory.MoveWindow(l_rect_wnd, FALSE);
		m_page_inventory.ShowWindow(SW_HIDE);

		m_page_tagaccess.MoveWindow(l_rect_wnd, FALSE);
		m_page_tagaccess.ShowWindow(SW_HIDE);

		m_page_tagaccess_ex.MoveWindow(l_rect_wnd, FALSE);
		m_page_tagaccess_ex.ShowWindow(SW_HIDE);

		m_page_config.MoveWindow(l_rect_wnd, FALSE);
		m_page_config.ShowWindow(SW_HIDE);

	}

	SetTimer(MY_TIMER_SHOW_ERRMSG, MY_TIMER_SHOW_ERRSMG_INTERVAL, NULL);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSSUDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSSUDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSSUDemoDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CSSUDemoDlg::OnSelchangingTabPages(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CWaitCursor   n_wait_cursor;
	TCHITTESTINFO n_hittest;
	//void*       n_reader_ctx = NULL;

	int n_new_sel;
	int n_cur_sel = m_tab_pages.GetCurSel();
	
	GetCursorPos(&n_hittest.pt);
	m_tab_pages.ScreenToClient(&n_hittest.pt);
	n_new_sel = m_tab_pages.HitTest(&n_hittest);

	if((n_new_sel == 0 && m_reader != NULL)
		|| (n_new_sel != 0 && m_reader == NULL))
	{
		*pResult = -1;
	}
	else
	{
		*pResult = 0;
	}
}

void CSSUDemoDlg::OnSelchangeTabPages(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CWaitCursor n_wait_cursor;
	int n_cur_sel = m_tab_pages.GetCurSel();

	m_page_explore.ShowWindow(SW_HIDE);
	m_page_inventory.ShowWindow(SW_HIDE);
	m_page_tagaccess.ShowWindow(SW_HIDE);
	m_page_tagaccess_ex.ShowWindow(SW_HIDE);
	m_page_config.ShowWindow(SW_HIDE);
	switch(n_cur_sel)
	{
	case 0:
		m_page_explore.ShowWindow(SW_SHOW);

		m_page_explore.OnDisconnect();
		m_page_inventory.OnDisconnect();
		m_page_tagaccess.OnDisconnect();
		//m_page_tagaccess_ex.OnDisconnect();
		//m_page_config.OnDisconnect();
		break;
	case 1:
		m_page_inventory.ShowWindow(SW_SHOW);

		m_page_inventory.OnConnect();
		m_page_explore.OnConnect();
		m_page_tagaccess.OnDisconnect();
		//m_page_tagaccess_ex.OnDisconnect();
		//m_page_config.OnDisconnect();
		break;
	case 2:
		m_page_tagaccess.ShowWindow(SW_SHOW);

		m_page_tagaccess.OnConnect();
		m_page_explore.OnConnect();
		m_page_inventory.OnDisconnect();
		//m_page_tagaccess_ex.OnDisconnect();
		//m_page_config.OnDisconnect();
		break;
	case 3:
		m_page_tagaccess_ex.ShowWindow(SW_SHOW);

		//m_page_tagaccess_ex.OnConnect();
		m_page_explore.OnConnect();
		m_page_inventory.OnDisconnect();
		m_page_tagaccess.OnDisconnect();
		//m_page_config.OnDisconnect();
		break;
	case 4:
		m_page_config.ShowWindow(SW_SHOW);

		//m_page_config.OnConnect();
		m_page_explore.OnConnect();
		m_page_inventory.OnDisconnect();
		m_page_tagaccess.OnDisconnect();
		//m_page_tagaccess_ex.OnDisconnect();
		break;
	default:
		break;
	}
	*pResult = 0;
}

void CSSUDemoDlg::OnBtnConnect() 
{
	// TODO: Add your control notification handler code here
	CWaitCursor wait;
	unsigned int  n_customNo;
	unsigned char n_conn_pwd[4];
	CString       n_tmp_str;
	SSUDevInfo    n_dev_info;

	if(!m_reader)
	{
		m_edit_password.GetWindowText(n_tmp_str);
		if(n_tmp_str.GetLength() != 8 || 0 > htob(n_tmp_str, n_tmp_str.GetLength(), n_conn_pwd, sizeof(n_conn_pwd)))
		{
			MsgBox("Error", "password is formated incorrectly", MB_OK);
			return;
		}

		m_edit_customno.GetWindowText(n_tmp_str);
		n_customNo = atoi(n_tmp_str);

		if(m_radio_com.GetCheck())
		{
			CString l_comport, l_nodeaddr;

			m_edit_comport.GetWindowText(l_comport);
			//m_edit_nodeaddr.GetWindowText(l_nodeaddr);
			if(m_check_nocrc.GetCheck())
			{
				l_nodeaddr = "1";
			}
			else
			{
				l_nodeaddr = "0";
			}
			l_comport += ":"; l_comport += l_nodeaddr;
			m_reader = SSUConnect( l_comport, SSU_ADDR_RS232, 1000, n_conn_pwd, n_customNo, &n_dev_info);
		}
		else if(m_radio_rs485.GetCheck())
		{
			CString l_comport, l_nodeaddr;

			m_edit_comport.GetWindowText(l_comport);
			m_edit_nodeaddr.GetWindowText(l_nodeaddr);
			l_comport += ":"; l_comport += l_nodeaddr;
			m_reader = SSUConnect( l_comport, SSU_ADDR_RS485, 1000, n_conn_pwd, n_customNo, &n_dev_info);
		}
		else if(m_radio_tcp.GetCheck())
		{
			CString l_addr, l_port;

			m_edit_ip.GetWindowText(l_addr);
			m_edit_port.GetWindowText(l_port);
			l_addr = l_addr + ":" + l_port;
			//m_reader = SSUConnect( l_addr, SSU_ADDR_TCP, SSU_PWD_EMPTY, 0 );
			m_reader = SSUConnect( l_addr, SSU_ADDR_TCP, 3000, n_conn_pwd, n_customNo, &n_dev_info );
		}
		else if(m_radio_udp.GetCheck())
		{
			CString l_addr, l_port;

			m_edit_ip.GetWindowText(l_addr);
			m_edit_port.GetWindowText(l_port);
			l_addr = l_addr + ":" + l_port;
			//m_reader = SSUConnect( l_addr, SSU_ADDR_UDP, SSU_PWD_EMPTY, 0 );
			m_reader = SSUConnect( l_addr, SSU_ADDR_UDP, 3000, n_conn_pwd, n_customNo, &n_dev_info );
		}
		else
		{
			MsgBox("Error", "please select a communication type", MB_OK);
			return;
		}

		if(m_reader)
		{
			CString l_str;
			l_str.Format("%u.%u.%u", ((n_dev_info.version >> 24) & 0xFF), ((n_dev_info.version >> 16) & 0xFF), (n_dev_info.version & 0xFFFF));
			m_edit_version.SetWindowText(l_str);
			l_str.Format("%010u", n_dev_info.devSN);
			m_edit_devsn.SetWindowText(l_str);
			m_edit_model.SetWindowText(n_dev_info.devModel);

			m_btn_connect.EnableWindow(FALSE);
			m_btn_disconnect.EnableWindow(TRUE);
			m_radio_com.EnableWindow(FALSE);
			m_radio_tcp.EnableWindow(FALSE);
			m_radio_udp.EnableWindow(FALSE);
			m_radio_rs485.EnableWindow(FALSE);
			//m_radio_can.EnableWindow(FALSE);
			m_edit_password.EnableWindow(FALSE);
			m_edit_customno.EnableWindow(FALSE);

			m_page_explore.OnConnect();
			m_page_inventory.OnConnect();
			m_page_tagaccess.OnConnect();
			m_page_tagaccess_ex.OnConnect();
			m_page_config.OnConnect();

			m_tab_pages.SetCurSel(1);
			m_page_explore.ShowWindow(SW_HIDE);
			m_page_inventory.ShowWindow(SW_SHOW);
			m_page_tagaccess.ShowWindow(SW_HIDE);
			m_page_tagaccess_ex.ShowWindow(SW_HIDE);
			m_page_config.ShowWindow(SW_HIDE);
		}
	}
}

void CSSUDemoDlg::OnBtnDisconnect() 
{
	CWaitCursor n_wait;
	// TODO: Add your control notification handler code here

	m_page_explore.OnDisconnect();
	m_page_inventory.OnDisconnect();
	m_page_tagaccess.OnDisconnect();
	m_page_tagaccess_ex.OnDisconnect();
	m_page_config.OnDisconnect();

	if(m_reader)
	{
		SSUDisconnect(m_reader, 1);
		m_reader = NULL;
	}

	m_btn_connect.EnableWindow(TRUE);
	m_btn_disconnect.EnableWindow(FALSE);	
	m_radio_com.EnableWindow(TRUE);
	m_radio_tcp.EnableWindow(TRUE);
	m_radio_udp.EnableWindow(TRUE);
	m_radio_rs485.EnableWindow(TRUE);
	m_edit_password.EnableWindow(TRUE);
	m_edit_customno.EnableWindow(TRUE);

	m_tab_pages.SetCurSel(0);
	m_page_explore.ShowWindow(SW_SHOW);
	m_page_inventory.ShowWindow(SW_HIDE);
	m_page_tagaccess.ShowWindow(SW_HIDE);
	m_page_tagaccess_ex.ShowWindow(SW_HIDE);
	m_page_config.ShowWindow(SW_HIDE);

	m_edit_version.SetWindowText("");
	m_edit_devsn.SetWindowText("");
	m_edit_model.SetWindowText("");
}

void CSSUDemoDlg::OnRadioCom() 
{
	// TODO: Add your control notification handler code here
	m_edit_comport.EnableWindow(TRUE);
	m_check_nocrc.EnableWindow(TRUE);
	m_edit_nodeaddr.EnableWindow(FALSE);
	m_edit_ip.EnableWindow(FALSE);
	//m_edit_port.EnableWindow(FALSE);

	m_grp_com.ShowWindow(SW_SHOW);
	m_static_comport.ShowWindow(SW_SHOW);
	m_edit_comport.ShowWindow(SW_SHOW);
	m_check_nocrc.ShowWindow(SW_SHOW);
	m_static_nodeaddr.ShowWindow(SW_HIDE);
	m_edit_nodeaddr.ShowWindow(SW_HIDE);
	m_grp_tcpip.ShowWindow(SW_HIDE);
	m_static_ip.ShowWindow(SW_HIDE);
	m_static_port.ShowWindow(SW_HIDE);
	m_edit_ip.ShowWindow(SW_HIDE);
	m_edit_port.ShowWindow(SW_HIDE);
}

void CSSUDemoDlg::OnRadioRs485() 
{
	// TODO: Add your control notification handler code here
	m_edit_comport.EnableWindow(TRUE);
	m_edit_nodeaddr.EnableWindow(TRUE);
	m_check_nocrc.EnableWindow(FALSE);
	m_edit_ip.EnableWindow(FALSE);
	//m_edit_port.EnableWindow(FALSE);

	m_grp_com.ShowWindow(SW_SHOW);
	m_static_comport.ShowWindow(SW_SHOW);
	m_static_nodeaddr.ShowWindow(SW_SHOW);
	m_edit_comport.ShowWindow(SW_SHOW);
	m_edit_nodeaddr.ShowWindow(SW_SHOW);
	m_check_nocrc.ShowWindow(SW_HIDE);
	m_grp_tcpip.ShowWindow(SW_HIDE);
	m_static_ip.ShowWindow(SW_HIDE);
	m_static_port.ShowWindow(SW_HIDE);
	m_edit_ip.ShowWindow(SW_HIDE);
	m_edit_port.ShowWindow(SW_HIDE);	
}


void CSSUDemoDlg::OnRadioTcp() 
{
	// TODO: Add your control notification handler code here
	m_edit_comport.EnableWindow(FALSE);
	m_check_nocrc.EnableWindow(FALSE);
	m_edit_nodeaddr.EnableWindow(FALSE);
	m_edit_ip.EnableWindow(TRUE);
	//m_edit_port.EnableWindow(TRUE);
	
	m_grp_tcpip.ShowWindow(SW_SHOW);
	m_static_ip.ShowWindow(SW_SHOW);
	m_static_port.ShowWindow(SW_SHOW);
	m_edit_ip.ShowWindow(SW_SHOW);
	m_edit_port.ShowWindow(SW_SHOW);
	m_grp_com.ShowWindow(SW_HIDE);
	m_static_comport.ShowWindow(SW_HIDE);
	m_static_nodeaddr.ShowWindow(SW_HIDE);
	m_edit_comport.ShowWindow(SW_HIDE);
	m_check_nocrc.ShowWindow(SW_HIDE);
	m_edit_nodeaddr.ShowWindow(SW_HIDE);
}

void CSSUDemoDlg::OnRadioUdp() 
{
	// TODO: Add your control notification handler code here
	m_edit_comport.EnableWindow(FALSE);
	m_check_nocrc.EnableWindow(FALSE);
	m_edit_nodeaddr.EnableWindow(FALSE);
	m_edit_ip.EnableWindow(TRUE);
	//m_edit_port.EnableWindow(TRUE);	
	
	m_grp_tcpip.ShowWindow(SW_SHOW);
	m_static_ip.ShowWindow(SW_SHOW);
	m_static_port.ShowWindow(SW_SHOW);
	m_edit_ip.ShowWindow(SW_SHOW);
	m_edit_port.ShowWindow(SW_SHOW);
	m_grp_com.ShowWindow(SW_HIDE);
	m_static_comport.ShowWindow(SW_HIDE);
	m_static_nodeaddr.ShowWindow(SW_HIDE);
	m_edit_comport.ShowWindow(SW_HIDE);
	m_check_nocrc.ShowWindow(SW_HIDE);
	m_edit_nodeaddr.ShowWindow(SW_HIDE);
}

void CSSUDemoDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent)
	{
	case MY_TIMER_SHOW_ERRMSG:
		KillTimer(MY_TIMER_SHOW_ERRMSG);
		m_error_lock.Lock();
		if( m_error_msg.GetLength() )
		{
//			MessageBox(m_error_msg, "Error", MB_OK|MB_ICONERROR);
			if( m_error_flag < 0 )
			{
				MsgBox("Error", m_error_msg, MB_OK);
			}
			else if( m_error_flag > 0 )
			{
				MsgBox("Hint", m_error_msg, MB_OK);
			}
			m_error_msg = "";
			m_error_flag = 0;
		}
		m_error_lock.Unlock();
		SetTimer(MY_TIMER_SHOW_ERRMSG, MY_TIMER_SHOW_ERRSMG_INTERVAL, NULL);
		break;
	default:
		break;
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CSSUDemoDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	OnPaint();
}

void CSSUDemoDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	OnBtnDisconnect();
	CDialog::OnClose();
}

