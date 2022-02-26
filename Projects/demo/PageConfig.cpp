// PageConfig.cpp : implementation file
//

#include "stdafx.h"
#include "SSUDemo.h"
#include "PageConfig.h"

#include "SSUDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PageConfig dialog


PageConfig::PageConfig(CWnd* pParent /*=NULL*/)
	: CDialog(PageConfig::IDD, pParent)
{
	//{{AFX_DATA_INIT(PageConfig)
	//}}AFX_DATA_INIT

	m_netaddr_page = NULL;
	memset(&m_netaddr, 0, sizeof(m_netaddr));
}


void PageConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PageConfig)
	DDX_Control(pDX, IDC_EDIT_INVT_IDLEMIN, m_edit_invt_idle_min);
	DDX_Control(pDX, IDC_EDIT_INVT_IDLEFRACT, m_edit_invt_idle_fract);
	DDX_Control(pDX, IDC_COMBO_IVNT_RSPTM, m_combo_invt_rspTm);
	DDX_Control(pDX, IDC_TAB_NETADDR, m_tab_netaddr);
	DDX_Control(pDX, IDC_BTN_NETADDR_SET, m_btn_netaddr_set);
	DDX_Control(pDX, IDC_BTN_NETADDR_GET, m_btn_netaddr_get);
	DDX_Control(pDX, IDC_BTN_CONNPWD_SET, m_btn_connpwd_set);
	DDX_Control(pDX, IDC_COMBO_RF_GAIN, m_combo_rf_gain);
	DDX_Control(pDX, IDC_COMBO_IVNT_BUFTM, m_combo_invt_buftm);
	DDX_Control(pDX, IDC_COMBO_INVT_QMINTRIES, m_combo_invt_qminTries);
	DDX_Control(pDX, IDC_COMBO_INVT_QMIN, m_combo_invt_qmin);
	DDX_Control(pDX, IDC_COMBO_INVT_QMAX, m_combo_invt_qmax);
	DDX_Control(pDX, IDC_EDIT_RFSTEP, m_edit_rf_step);
	DDX_Control(pDX, IDC_EDIT_RFDeviation, m_edit_rf_deviation);
	DDX_Control(pDX, IDC_EDIT_RFCENTER, m_edit_rf_center);
	DDX_Control(pDX, IDC_EDIT_CONN_PWD, m_edit_conn_pwd);
	DDX_Control(pDX, IDC_CHECK_ANT3, m_check_rf_antmask_b3);
	DDX_Control(pDX, IDC_CHECK_ANT0, m_check_rf_antmask_b0);
	DDX_Control(pDX, IDC_CHECK_ANT2, m_check_rf_antmask_b2);
	DDX_Control(pDX, IDC_CHECK_ANT1, m_check_rf_antmask_b1);
	DDX_Control(pDX, IDC_COMBO_BEEP_ENABLE, m_combo_beep_enable);
	DDX_Control(pDX, IDC_COMBO_INVT_SESS, m_combo_invt_sess);
	DDX_Control(pDX, IDC_BTN_CONFIG_SET, m_btn_config_set);
	DDX_Control(pDX, IDC_BTN_CONFIG_GET, m_btn_config_get);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PageConfig, CDialog)
	//{{AFX_MSG_MAP(PageConfig)
	ON_BN_CLICKED(IDC_BTN_CONFIG_GET, OnBtnConfigGet)
	ON_BN_CLICKED(IDC_BTN_CONFIG_SET, OnBtnConfigSet)
	ON_BN_CLICKED(IDC_BTN_CONNPWD_SET, OnBtnConnpwdSet)
	ON_BN_CLICKED(IDC_BTN_NETADDR_GET, OnBtnNetaddrGet)
	ON_BN_CLICKED(IDC_BTN_NETADDR_SET, OnBtnNetAddrSet)
	ON_EN_CHANGE(IDC_EDIT_RFDeviation, OnChangeEDITRFDeviation)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PageConfig message handlers

void PageConfig::OnConnect()
{
	m_btn_config_get.EnableWindow(TRUE);
	m_btn_connpwd_set.EnableWindow(TRUE);
	m_btn_netaddr_get.EnableWindow(TRUE);
}

void PageConfig::OnDisconnect()
{
	m_btn_config_get.EnableWindow(FALSE);
	m_btn_config_set.EnableWindow(FALSE);
	m_btn_connpwd_set.EnableWindow(FALSE);
	m_btn_netaddr_get.EnableWindow(FALSE);
	m_btn_netaddr_set.EnableWindow(FALSE);

	if(m_netaddr_page)
	{
		m_netaddr_page->CloseWindow();
		m_netaddr_page->DestroyWindow();
		m_tab_netaddr.DeleteAllItems();
		delete m_netaddr_page;
		m_netaddr_page = NULL;
	}
}

void PageConfig::OnBtnConfigGet() 
{
	CWaitCursor wait;

	// TODO: Add your control notification handler code here
	BOOL          n_arg_get_success = FALSE;
	unsigned char n_arg_val_buff[128];

	if(1 == SSUConfigGet(((CSSUDemoDlg*)GetParent())->m_reader, CONFIG_NAME_beepEnable, n_arg_val_buff, sizeof(n_arg_val_buff)))
	{
		m_combo_beep_enable.SetCurSel((0 == n_arg_val_buff[0])?0:1);
		m_combo_beep_enable.EnableWindow(TRUE);
		n_arg_get_success = TRUE;
	}
	else
	{
		m_combo_beep_enable.SetCurSel(-1);
		m_combo_beep_enable.EnableWindow(FALSE);
	}

	if(2 == SSUConfigGet(((CSSUDemoDlg*)GetParent())->m_reader, CONFIG_NAME_rfStep, n_arg_val_buff, sizeof(n_arg_val_buff)))
	{
		CString l_rf_step;
		l_rf_step.Format("%u", (n_arg_val_buff[0] << 8) + (n_arg_val_buff[1]));
		m_edit_rf_step.SetWindowText(l_rf_step);
		m_edit_rf_step.EnableWindow(TRUE);
		n_arg_get_success = TRUE;
	}
	else
	{
		m_edit_rf_step.SetWindowText("");
		m_edit_rf_step.EnableWindow(FALSE);
	}

	if(2 == SSUConfigGet(((CSSUDemoDlg*)GetParent())->m_reader, CONFIG_NAME_rfDeviation, n_arg_val_buff, sizeof(n_arg_val_buff)))
	{
		CString l_rf_deviation;
		l_rf_deviation.Format("%u", (n_arg_val_buff[0] << 8) + (n_arg_val_buff[1]));
		m_edit_rf_deviation.SetWindowText(l_rf_deviation);
		m_edit_rf_deviation.EnableWindow(TRUE);
		n_arg_get_success = TRUE;
	}
	else
	{
		m_edit_rf_deviation.SetWindowText("");
		m_edit_rf_deviation.EnableWindow(FALSE);
	}

	if(4 == SSUConfigGet(((CSSUDemoDlg*)GetParent())->m_reader, CONFIG_NAME_rfCenter, n_arg_val_buff, sizeof(n_arg_val_buff)))
	{
		CString l_rf_center;
		l_rf_center.Format("%u", (n_arg_val_buff[0] << 24) + (n_arg_val_buff[1]<<16) + (n_arg_val_buff[2]<<8) + (n_arg_val_buff[3]<<0));
		m_edit_rf_center.SetWindowText(l_rf_center);
		m_edit_rf_center.EnableWindow(TRUE);
		n_arg_get_success = TRUE;
	}
	else
	{
		m_edit_rf_center.SetWindowText("");
		m_edit_rf_center.EnableWindow(FALSE);
	}

	if(1 == SSUConfigGet(((CSSUDemoDlg*)GetParent())->m_reader, CONFIG_NAME_rfGain, n_arg_val_buff, sizeof(n_arg_val_buff)))
	{
		m_combo_rf_gain.SetCurSel((31 >= n_arg_val_buff[0])?n_arg_val_buff[0]:31);
		m_combo_rf_gain.EnableWindow(TRUE);
		n_arg_get_success = TRUE;
	}
	else
	{
		m_combo_rf_gain.SetCurSel(-1);
		m_combo_rf_gain.EnableWindow(FALSE);
	}

	if(1 == SSUConfigGet(((CSSUDemoDlg*)GetParent())->m_reader, CONFIG_NAME_rfAntMask, n_arg_val_buff, sizeof(n_arg_val_buff)))
	{
		unsigned char l_mask = n_arg_val_buff[0];

		m_check_rf_antmask_b0.SetCheck((0x01 & l_mask) != 0);
		m_check_rf_antmask_b1.SetCheck((0x02 & l_mask) != 0);
		m_check_rf_antmask_b2.SetCheck((0x04 & l_mask) != 0);
		m_check_rf_antmask_b3.SetCheck((0x08 & l_mask) != 0);
		m_check_rf_antmask_b0.EnableWindow(TRUE);
		m_check_rf_antmask_b1.EnableWindow(TRUE);
		m_check_rf_antmask_b2.EnableWindow(TRUE);
		m_check_rf_antmask_b3.EnableWindow(TRUE);
		n_arg_get_success = TRUE;
	}
	else
	{
		m_check_rf_antmask_b0.EnableWindow(FALSE);
		m_check_rf_antmask_b1.EnableWindow(FALSE);
		m_check_rf_antmask_b2.EnableWindow(FALSE);
		m_check_rf_antmask_b3.EnableWindow(FALSE);
	}

	if(1 == SSUConfigGet(((CSSUDemoDlg*)GetParent())->m_reader, CONFIG_NAME_invtQMinTries, n_arg_val_buff, sizeof(n_arg_val_buff)))
	{
		m_combo_invt_qminTries.SetCurSel((15 >= n_arg_val_buff[0])?n_arg_val_buff[0]:15);
		m_combo_invt_qminTries.EnableWindow(TRUE);
		n_arg_get_success = TRUE;
	}
	else
	{
		m_combo_invt_qminTries.SetCurSel(-1);
		m_combo_invt_qminTries.EnableWindow(FALSE);
	}

	if(1 == SSUConfigGet(((CSSUDemoDlg*)GetParent())->m_reader, CONFIG_NAME_invtQMin, n_arg_val_buff, sizeof(n_arg_val_buff)))
	{
		m_combo_invt_qmin.SetCurSel((4 >= n_arg_val_buff[0])?n_arg_val_buff[0]:4);
		m_combo_invt_qmin.EnableWindow(TRUE);
		n_arg_get_success = TRUE;
	}
	else
	{
		m_combo_invt_qmin.SetCurSel(-1);
		m_combo_invt_qmin.EnableWindow(FALSE);
	}

	if(1 == SSUConfigGet(((CSSUDemoDlg*)GetParent())->m_reader, CONFIG_NAME_invtQMax, n_arg_val_buff, sizeof(n_arg_val_buff)))
	{
		m_combo_invt_qmax.SetCurSel((15 >= n_arg_val_buff[0])?n_arg_val_buff[0]:15);
		m_combo_invt_qmax.EnableWindow(TRUE);
		n_arg_get_success = TRUE;
	}
	else
	{
		m_combo_invt_qmax.SetCurSel(-1);
		m_combo_invt_qmax.EnableWindow(FALSE);
	}

	if(1 == SSUConfigGet(((CSSUDemoDlg*)GetParent())->m_reader, CONFIG_NAME_invtBufTm, n_arg_val_buff, sizeof(n_arg_val_buff)))
	{
		m_combo_invt_buftm.SetCurSel((31 >= n_arg_val_buff[0])?n_arg_val_buff[0]:31);
		m_combo_invt_buftm.EnableWindow(TRUE);
		n_arg_get_success = TRUE;
	}
	else
	{
		m_combo_invt_buftm.SetCurSel(-1);
		m_combo_invt_buftm.EnableWindow(FALSE);
	}

	if(1 == SSUConfigGet(((CSSUDemoDlg*)GetParent())->m_reader, CONFIG_NAME_invtSess, n_arg_val_buff, sizeof(n_arg_val_buff)) && n_arg_val_buff[0] < 4)
	{
		m_combo_invt_sess.SetCurSel(n_arg_val_buff[0]);
		m_combo_invt_sess.EnableWindow(TRUE);
		n_arg_get_success = TRUE;
	}
	else
	{
		m_combo_invt_sess.SetCurSel(-1);
		m_combo_invt_sess.EnableWindow(FALSE);
	}

	if(2 == SSUConfigGet(((CSSUDemoDlg*)GetParent())->m_reader, CONFIG_NAME_invtRspTm, n_arg_val_buff, sizeof(n_arg_val_buff)))
	{
		CString l_rsptm;
		short l_invtRspTm = (n_arg_val_buff[0] << 8)|(n_arg_val_buff[1] << 0);

		l_rsptm.Format("%d", l_invtRspTm);
		m_combo_invt_rspTm.SetWindowText(l_rsptm);
		m_combo_invt_rspTm.EnableWindow(TRUE);
		n_arg_get_success = TRUE;
	}
	else
	{
		m_combo_invt_rspTm.SetWindowText("");
		m_combo_invt_rspTm.EnableWindow(FALSE);
	}

	if(1 == SSUConfigGet(((CSSUDemoDlg*)GetParent())->m_reader, CONFIG_NAME_invtIdleMin, n_arg_val_buff, sizeof(n_arg_val_buff)))
	{
		CString l_str;
		unsigned char l_invtIdleMin = (n_arg_val_buff[0]);

		l_str.Format("%d", l_invtIdleMin);
		m_edit_invt_idle_min.SetWindowText(l_str);
		m_edit_invt_idle_min.EnableWindow(TRUE);
		n_arg_get_success = TRUE;
	}
	else
	{
		m_edit_invt_idle_min.SetWindowText("");
		m_edit_invt_idle_min.EnableWindow(FALSE);
	}

	if(1 == SSUConfigGet(((CSSUDemoDlg*)GetParent())->m_reader, CONFIG_NAME_invtIdleFract, n_arg_val_buff, sizeof(n_arg_val_buff)))
	{
		CString l_str;
		unsigned char l_invtIdleFract = (n_arg_val_buff[0]);

		l_str.Format("%d", l_invtIdleFract);
		m_edit_invt_idle_fract.SetWindowText(l_str);
		m_edit_invt_idle_fract.EnableWindow(TRUE);
		n_arg_get_success = TRUE;
	}
	else
	{
		m_edit_invt_idle_fract.SetWindowText("");
		m_edit_invt_idle_fract.EnableWindow(FALSE);
	}

	if(n_arg_get_success)
	{
		m_btn_config_set.EnableWindow(TRUE);
	}
}

void PageConfig::OnBtnConfigSet() 
{
	CWaitCursor wait;
	// TODO: Add your control notification handler code here
	LONG n_wnd_style;
	BOOL          n_arg_set_success = TRUE;
	int           n_arg_end_status = -1;
	unsigned char n_arg_val_buff[128];

	if(0 <= SSUConfigBegin(((CSSUDemoDlg*)GetParent())->m_reader))
	{
		n_wnd_style = ::GetWindowLong(m_combo_beep_enable.GetSafeHwnd(), GWL_STYLE);
		if(0 == (n_wnd_style & WS_DISABLED))
		{
			n_arg_val_buff[0] = m_combo_beep_enable.GetCurSel();
			if(0 != SSUConfigSet(((CSSUDemoDlg*)GetParent())->m_reader, CONFIG_NAME_beepEnable, n_arg_val_buff, 1))
			{
				m_combo_beep_enable.SetCurSel(-1);
				m_combo_beep_enable.EnableWindow(FALSE);
				n_arg_set_success = FALSE;
			}
		}

		n_wnd_style = ::GetWindowLong(m_edit_rf_step.GetSafeHwnd(), GWL_STYLE);
		if(0 == (n_wnd_style & WS_DISABLED))
		{
			CString l_rf_step_str;
			int     l_rf_step;
			m_edit_rf_step.GetWindowText(l_rf_step_str);
			l_rf_step = ::atoi(l_rf_step_str);

			if(0 <= l_rf_step)
			{
				n_arg_val_buff[0] = ((l_rf_step & 0xFF00)>>8);
				n_arg_val_buff[1] = (l_rf_step & 0xFF);
				if(0 != SSUConfigSet(((CSSUDemoDlg*)GetParent())->m_reader, CONFIG_NAME_rfStep, n_arg_val_buff, 2))
				{
					m_edit_rf_step.SetWindowText("");
					m_edit_rf_step.EnableWindow(FALSE);
					n_arg_set_success = FALSE;
				}
			}
		}

		n_wnd_style = ::GetWindowLong(m_edit_rf_deviation.GetSafeHwnd(), GWL_STYLE);
		if(0 == (n_wnd_style & WS_DISABLED))
		{
			CString l_rf_deviation_str;
			int     l_rf_deviation;
			m_edit_rf_deviation.GetWindowText(l_rf_deviation_str);
			l_rf_deviation = ::atoi(l_rf_deviation_str);

			if(0 <= l_rf_deviation)
			{
				n_arg_val_buff[0] = ((l_rf_deviation & 0xFF00)>>8);
				n_arg_val_buff[1] = (l_rf_deviation & 0xFF);
				if(0 != SSUConfigSet(((CSSUDemoDlg*)GetParent())->m_reader, CONFIG_NAME_rfDeviation, n_arg_val_buff, 2))
				{
					m_edit_rf_deviation.SetWindowText("");
					m_edit_rf_deviation.EnableWindow(FALSE);
					n_arg_set_success = FALSE;
				}
			}
		}

		n_wnd_style = ::GetWindowLong(m_edit_rf_center.GetSafeHwnd(), GWL_STYLE);
		if(0 == (n_wnd_style & WS_DISABLED))
		{
			CString l_rf_center_str;
			int     l_rf_center;
			m_edit_rf_center.GetWindowText(l_rf_center_str);
			l_rf_center = ::atoi(l_rf_center_str);

			if(0 <= l_rf_center)
			{
				n_arg_val_buff[0] = ((l_rf_center & 0xFF000000)>>24);
				n_arg_val_buff[1] = ((l_rf_center & 0xFF0000)>>16);
				n_arg_val_buff[2] = ((l_rf_center & 0xFF00)>>8);
				n_arg_val_buff[3] = (l_rf_center & 0xFF);
				if(0 != SSUConfigSet(((CSSUDemoDlg*)GetParent())->m_reader, CONFIG_NAME_rfCenter, n_arg_val_buff, 4))
				{
					m_edit_rf_center.SetWindowText("");
					m_edit_rf_center.EnableWindow(FALSE);
					n_arg_set_success = FALSE;
				}
			}
		}

		n_wnd_style = ::GetWindowLong(m_combo_rf_gain.GetSafeHwnd(), GWL_STYLE);
		if(0 == (n_wnd_style & WS_DISABLED))
		{
			n_arg_val_buff[0] = m_combo_rf_gain.GetCurSel();
			if(0 != SSUConfigSet(((CSSUDemoDlg*)GetParent())->m_reader, CONFIG_NAME_rfGain, n_arg_val_buff, 1))
			{
				m_combo_rf_gain.SetCurSel(-1);
				m_combo_rf_gain.EnableWindow(FALSE);
				n_arg_set_success = FALSE;
			}
		}

		n_wnd_style = ::GetWindowLong(m_check_rf_antmask_b0.GetSafeHwnd(), GWL_STYLE);
		if(0 == (n_wnd_style & WS_DISABLED))
		{
			n_arg_val_buff[0] = 0;
			if(m_check_rf_antmask_b0.GetCheck()){ n_arg_val_buff[0] |= 0x01; }
			if(m_check_rf_antmask_b1.GetCheck()){ n_arg_val_buff[0] |= 0x02; }
			if(m_check_rf_antmask_b2.GetCheck()){ n_arg_val_buff[0] |= 0x04; }
			if(m_check_rf_antmask_b3.GetCheck()){ n_arg_val_buff[0] |= 0x08; }
			if(0 != SSUConfigSet(((CSSUDemoDlg*)GetParent())->m_reader, CONFIG_NAME_rfAntMask, n_arg_val_buff, 1))
			{
				m_check_rf_antmask_b0.EnableWindow(FALSE);
				m_check_rf_antmask_b1.EnableWindow(FALSE);
				m_check_rf_antmask_b2.EnableWindow(FALSE);
				m_check_rf_antmask_b3.EnableWindow(FALSE);
				n_arg_set_success = FALSE;
			}
		}

		n_wnd_style = ::GetWindowLong(m_combo_invt_qminTries.GetSafeHwnd(), GWL_STYLE);
		if(0 == (n_wnd_style & WS_DISABLED))
		{
			n_arg_val_buff[0] = m_combo_invt_qminTries.GetCurSel();
			if(0 != SSUConfigSet(((CSSUDemoDlg*)GetParent())->m_reader, CONFIG_NAME_invtQMinTries, n_arg_val_buff, 1))
			{
				m_combo_invt_qminTries.SetCurSel(-1);
				m_combo_invt_qminTries.EnableWindow(FALSE);
				n_arg_set_success = FALSE;
			}
		}

		n_wnd_style = ::GetWindowLong(m_combo_invt_qmin.GetSafeHwnd(), GWL_STYLE);
		if(0 == (n_wnd_style & WS_DISABLED))
		{
			n_arg_val_buff[0] = m_combo_invt_qmin.GetCurSel();
			if(0 != SSUConfigSet(((CSSUDemoDlg*)GetParent())->m_reader, CONFIG_NAME_invtQMin, n_arg_val_buff, 1))
			{
				m_combo_invt_qmin.SetCurSel(-1);
				m_combo_invt_qmin.EnableWindow(FALSE);
				n_arg_set_success = FALSE;
			}
		}

		n_wnd_style = ::GetWindowLong(m_combo_invt_qmax.GetSafeHwnd(), GWL_STYLE);
		if(0 == (n_wnd_style & WS_DISABLED))
		{
			n_arg_val_buff[0] = m_combo_invt_qmax.GetCurSel();
			if(0 != SSUConfigSet(((CSSUDemoDlg*)GetParent())->m_reader, CONFIG_NAME_invtQMax, n_arg_val_buff, 1))
			{
				m_combo_invt_qmax.SetCurSel(-1);
				m_combo_invt_qmax.EnableWindow(FALSE);
				n_arg_set_success = FALSE;
			}
		}

		n_wnd_style = ::GetWindowLong(m_combo_invt_buftm.GetSafeHwnd(), GWL_STYLE);
		if(0 == (n_wnd_style & WS_DISABLED))
		{
			n_arg_val_buff[0] = m_combo_invt_buftm.GetCurSel();
			if(0 != SSUConfigSet(((CSSUDemoDlg*)GetParent())->m_reader, CONFIG_NAME_invtBufTm, n_arg_val_buff, 1))
			{
				m_combo_invt_buftm.SetCurSel(-1);
				m_combo_invt_buftm.EnableWindow(FALSE);
				n_arg_set_success = FALSE;
			}
		}

		n_wnd_style = ::GetWindowLong(m_combo_invt_sess.GetSafeHwnd(), GWL_STYLE);
		if(0 == (n_wnd_style & WS_DISABLED))
		{
			n_arg_val_buff[0] = m_combo_invt_sess.GetCurSel();
			if(0 != SSUConfigSet(((CSSUDemoDlg*)GetParent())->m_reader, CONFIG_NAME_invtSess, n_arg_val_buff, 1))
			{
				m_combo_invt_sess.SetCurSel(-1);
				m_combo_invt_sess.EnableWindow(FALSE);
				n_arg_set_success = FALSE;
			}
		}

		n_wnd_style = ::GetWindowLong(m_combo_invt_rspTm.GetSafeHwnd(), GWL_STYLE);
		if(0 == (n_wnd_style & WS_DISABLED))
		{
			CString l_rsptm;
			short   l_rsptm_short;

			m_combo_invt_rspTm.GetWindowText(l_rsptm);
			l_rsptm_short = ::atoi(l_rsptm);
			n_arg_val_buff[0] = (l_rsptm_short >> 8);
			n_arg_val_buff[1] = (l_rsptm_short >> 0);

			if(0 != SSUConfigSet(((CSSUDemoDlg*)GetParent())->m_reader, CONFIG_NAME_invtRspTm, n_arg_val_buff, 2))
			{
				m_combo_invt_rspTm.SetWindowText("");
				m_combo_invt_rspTm.EnableWindow(FALSE);
				n_arg_set_success = FALSE;
			}
			else
			{
				l_rsptm.Format("%d", l_rsptm_short);
				m_combo_invt_rspTm.SetWindowText(l_rsptm);
			}
		}

		n_wnd_style = ::GetWindowLong(m_edit_invt_idle_min.GetSafeHwnd(), GWL_STYLE);
		if(0 == (n_wnd_style & WS_DISABLED))
		{
			CString l_str;

			m_edit_invt_idle_min.GetWindowText(l_str);
			n_arg_val_buff[0] = ::atoi(l_str);

			if(0 != SSUConfigSet(((CSSUDemoDlg*)GetParent())->m_reader, CONFIG_NAME_invtIdleMin, n_arg_val_buff, 1))
			{
				m_edit_invt_idle_min.SetWindowText("");
				m_edit_invt_idle_min.EnableWindow(FALSE);
				n_arg_set_success = FALSE;
			}
			else
			{
				l_str.Format("%u", n_arg_val_buff[0]);
				m_edit_invt_idle_min.SetWindowText(l_str);
			}
		}

		n_wnd_style = ::GetWindowLong(m_edit_invt_idle_fract.GetSafeHwnd(), GWL_STYLE);
		if(0 == (n_wnd_style & WS_DISABLED))
		{
			CString l_str;

			m_edit_invt_idle_fract.GetWindowText(l_str);
			n_arg_val_buff[0] = ::atoi(l_str);

			if(0 != SSUConfigSet(((CSSUDemoDlg*)GetParent())->m_reader, CONFIG_NAME_invtIdleFract, n_arg_val_buff, 1))
			{
				m_edit_invt_idle_fract.SetWindowText("");
				m_edit_invt_idle_fract.EnableWindow(FALSE);
				n_arg_set_success = FALSE;
			}
			else
			{
				l_str.Format("%u", n_arg_val_buff[0]);
				m_edit_invt_idle_fract.SetWindowText(l_str);
			}
		}
	}
	else
	{
		n_arg_set_success = FALSE;
	}

	if(0 > (n_arg_end_status = SSUConfigEnd(((CSSUDemoDlg*)GetParent())->m_reader, (n_arg_set_success)?1:0)))
	{
		Sleep(500);
		n_arg_end_status = SSUConfigEnd(((CSSUDemoDlg*)GetParent())->m_reader, (n_arg_set_success)?1:0);
	}

	if(0 != n_arg_end_status)
	{
		MsgBox("Error", "config error. you should try to ensure if it was successful.", MB_OK);
	}
}

void PageConfig::OnBtnConnpwdSet() 
{
	// TODO: Add your control notification handler code here
	CWaitCursor wait;
	CString       n_tmp_str;
	unsigned char n_new_pwd[4];
	unsigned char n_conn_pwd[4];


	((CSSUDemoDlg*)GetParent())->m_edit_password.GetWindowText(n_tmp_str);
	if(n_tmp_str.GetLength() != 8 || 0 > htob(n_tmp_str, n_tmp_str.GetLength(), n_conn_pwd, sizeof(n_conn_pwd)))
	{
		MsgBox("Error", "the old connecting password is formated incorrectly", MB_OK);
		return;
	}

	m_edit_conn_pwd.GetWindowText(n_tmp_str);
	if(n_tmp_str.GetLength() != 8 || 0 > htob(n_tmp_str, n_tmp_str.GetLength(), n_new_pwd, sizeof(n_new_pwd)))
	{
		MsgBox("Error", "the new connecting password is formated incorrectly", MB_OK);
		return;
	}

	if(0 > SSUConnPwdSet(((CSSUDemoDlg*)GetParent())->m_reader, n_conn_pwd, n_new_pwd))
	{
		MsgBox("Error", "there are some errors when modifying the connecting password. you should try to ensure if it was successful.", MB_OK);
		return;
	}
}

BOOL PageConfig::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

#include "PageNetAddrTCPIP.h"
#include "PageNetAddrRS485.h"
void PageConfig::OnBtnNetaddrGet()
{
	// TODO: Add your control notification handler code here
	CWaitCursor wait;
	CString       n_tmp_str;
	SSUNetAddr    n_netaddr;

	if(0 > SSUNetAddrGet(((CSSUDemoDlg*)GetParent())->m_reader, &n_netaddr))
	{
		MsgBox("Error", "failed to get net address.", MB_OK);

		m_btn_netaddr_set.EnableWindow(FALSE);
		if(m_netaddr_page)
		{
			m_netaddr_page->CloseWindow();
			m_netaddr_page->DestroyWindow();
			m_tab_netaddr.DeleteAllItems();
			delete m_netaddr_page;
			m_netaddr_page = NULL;
		}
	}
	else
	{
		if(n_netaddr.netType != m_netaddr.netType && m_netaddr_page)
		{
			m_netaddr_page->CloseWindow();
			m_netaddr_page->DestroyWindow();
			m_tab_netaddr.DeleteAllItems();
			delete m_netaddr_page;
			m_netaddr_page = NULL;
		}

		switch(n_netaddr.netType)
		{
		case SSU_NET_TCPIP:
			{
				PageNetAddrTCPIP* l_page_tcpip;
				if(m_netaddr_page)
				{
					l_page_tcpip = (PageNetAddrTCPIP*)m_netaddr_page;
				}
				else
				{
					m_netaddr = n_netaddr;
					m_netaddr_page = l_page_tcpip = new PageNetAddrTCPIP;
					l_page_tcpip->Create(PageNetAddrTCPIP::IDD, this);//&m_tab_subjects);
				
					m_tab_netaddr.InsertItem(0, "TCPIP");
					m_tab_netaddr.SetCurSel(0);
				}
				l_page_tcpip->SetNetAddr(&n_netaddr);
			}
			break;
		case SSU_NET_RS485:
			{
				PageNetAddrRS485* l_page_rs485;
				if(m_netaddr_page)
				{
					l_page_rs485 = (PageNetAddrRS485*)m_netaddr_page;
				}
				else
				{
					m_netaddr = n_netaddr;
					m_netaddr_page = l_page_rs485 = new PageNetAddrRS485;
					l_page_rs485->Create(PageNetAddrRS485::IDD, this);//&m_tab_subjects);
				
					m_tab_netaddr.InsertItem(0, "RS485");
					m_tab_netaddr.SetCurSel(0);				
				}
				l_page_rs485->SetNetAddr(&n_netaddr);
			}
			break;
		default:
			break;
		}

		if(m_netaddr_page)
		{
			CRect  l_rect_wnd, l_rect_item;

			m_tab_netaddr.GetClientRect(l_rect_wnd);
			m_tab_netaddr.ClientToScreen(l_rect_wnd);
			ScreenToClient(l_rect_wnd);
			m_tab_netaddr.SetWindowPos(m_netaddr_page, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);

			m_tab_netaddr.GetItemRect(0, l_rect_item);
			l_rect_wnd.DeflateRect(2, l_rect_item.Height() + 3, 2, 2);
			//

			//ÒÆµ½ÖÐ¼ä
			m_netaddr_page->GetClientRect(l_rect_item);
			l_rect_item.OffsetRect(l_rect_wnd.left, l_rect_wnd.top);
			if(l_rect_item.Width() <= l_rect_wnd.Width())
			{
				l_rect_item.DeflateRect((l_rect_wnd.Width() - l_rect_item.Width())/2, 0, -(l_rect_wnd.Width() - l_rect_item.Width())/2, 0);
			}
			else
			{
				l_rect_item.right = l_rect_wnd.right;
			}
			if(l_rect_item.Height() <= l_rect_wnd.Height())
			{
				l_rect_item.DeflateRect(0, (l_rect_wnd.Height() - l_rect_item.Height())/2, 0, -(l_rect_wnd.Height() - l_rect_item.Height())/2);
			}
			else
			{
				l_rect_item.bottom = l_rect_wnd.bottom;
			}

			m_netaddr_page->MoveWindow(l_rect_item, FALSE);
			m_netaddr_page->ShowWindow(SW_SHOW);

			m_btn_netaddr_set.EnableWindow(TRUE);
		}
	}
}

void PageConfig::OnBtnNetAddrSet() 
{
	// TODO: Add your control notification handler code here
	CWaitCursor   n_wait;
	SSUNetAddr    n_netaddr;

	if(m_netaddr_page)
	{
		switch(m_netaddr.netType)
		{
		case SSU_NET_TCPIP:
			if(0 > ((PageNetAddrTCPIP*)m_netaddr_page)->GetNetAddr(&n_netaddr))
			{
				MsgBox("Error", "input error.", MB_OK);
			}
			else
			{
				CString       l_tmp_str;
				unsigned char l_conn_pwd[4];
				((CSSUDemoDlg*)GetParent())->m_edit_password.GetWindowText(l_tmp_str);
				if(l_tmp_str.GetLength() != 8 || 0 > htob(l_tmp_str, l_tmp_str.GetLength(), l_conn_pwd, sizeof(l_conn_pwd)))
				{
					MsgBox("Error", "the connecting password is formated incorrectly", MB_OK);
					return;
				}

				if(0 > SSUNetAddrSet(((CSSUDemoDlg*)GetParent())->m_reader, l_conn_pwd, &n_netaddr))
				{
					MsgBox("Error", "there are some errors when set the net address. you should try to ensure if it was successful.", MB_OK);
				}
			}
			break;
		case SSU_NET_RS485:
			if(0 > ((PageNetAddrRS485*)m_netaddr_page)->GetNetAddr(&n_netaddr))
			{
				MsgBox("Error", "input error.", MB_OK);
			}
			else
			{
				CString       l_tmp_str;
				unsigned char l_conn_pwd[4];
				((CSSUDemoDlg*)GetParent())->m_edit_password.GetWindowText(l_tmp_str);
				if(l_tmp_str.GetLength() != 8 || 0 > htob(l_tmp_str, l_tmp_str.GetLength(), l_conn_pwd, sizeof(l_conn_pwd)))
				{
					MsgBox("Error", "the connecting password is formated incorrectly", MB_OK);
					return;
				}

				if(0 > SSUNetAddrSet(((CSSUDemoDlg*)GetParent())->m_reader, l_conn_pwd, &n_netaddr))
				{
					MsgBox("Error", "there are some errors when set the net address. you should try to ensure if it was successful.", MB_OK);
				}
			}
			break;
		default:
			MsgBox("Error", "netType unknown.", MB_OK);
			break;
		}
	}
}

void PageConfig::OnChangeEDITRFDeviation() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	
}
