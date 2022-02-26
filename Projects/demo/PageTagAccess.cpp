// PageTagAccess.cpp : implementation file
//

#include "stdafx.h"
#include "SSUDemo.h"
#include "PageTagAccess.h"

#include "SSUDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PageTagAccess dialog


PageTagAccess::PageTagAccess(CWnd* pParent /*=NULL*/)
	: CDialog(PageTagAccess::IDD, pParent)
{
	//{{AFX_DATA_INIT(PageTagAccess)
	//}}AFX_DATA_INIT

	m_should_break = FALSE;
}


void PageTagAccess::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PageTagAccess)
	DDX_Control(pDX, IDC_CHECK_WRITE_CONTINUE, m_check_write_continue);
	DDX_Control(pDX, IDC_EDIT_EMSG, m_edit_emsg);
	DDX_Control(pDX, IDC_CHECK_READ_CONTINUE, m_check_read_continue);
	DDX_Control(pDX, IDC_CHECK_WRITE_ANY, m_chk_writeany);
	DDX_Control(pDX, IDC_CHECK_READ_ANY, m_chk_readany);
	DDX_Control(pDX, IDC_EDIT_PWD_READ, m_edit_pwd_read);
	DDX_Control(pDX, IDC_EDIT_PWD_KILL, m_edit_pwd_kill);
	DDX_Control(pDX, IDC_EDIT_PWD_ACC, m_edit_pwd_acc);
	DDX_Control(pDX, IDC_EDIT_WORDS_WRITE, m_edit_word_write);
	DDX_Control(pDX, IDC_EDIT_WORDS_READ, m_edit_words_read);
	DDX_Control(pDX, IDC_EDIT_START_WRITE, m_edit_start_write);
	DDX_Control(pDX, IDC_EDIT_START_READ, m_edit_start_read);
	DDX_Control(pDX, IDC_EDIT_PWD_WRITE, m_edit_pwd_write);
	DDX_Control(pDX, IDC_EDIT_PWD_LOCK, m_edit_pwd_lock);
	DDX_Control(pDX, IDC_EDIT_EPC, m_edit_epc);
	DDX_Control(pDX, IDC_EDIT_DATA_WRITE, m_edit_data_write);
	DDX_Control(pDX, IDC_EDIT_DATA_READ, m_edit_data_read);
	DDX_Control(pDX, IDC_COMBO_SECT_WRITE, m_combo_sect_write);
	DDX_Control(pDX, IDC_COMBO_SECT_READ, m_combo_sect_read);
	DDX_Control(pDX, IDC_COMBO_SECT_LOCK, m_combo_sect_lock);
	DDX_Control(pDX, IDC_COMBO_OPT_LOCK, m_combo_opt_lock);
	DDX_Control(pDX, IDC_BTN_TAGQUERY, m_btn_tagquery);
	DDX_Control(pDX, IDC_BTN_TAG_WRITE, m_btn_tagwrite);
	DDX_Control(pDX, IDC_BTN_TAG_LOCK, m_btn_taglock);
	DDX_Control(pDX, IDC_BTN_TAG_KILL, m_btn_tagkill);
	DDX_Control(pDX, IDC_BTN_TAG_READ, m_btn_tagread);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PageTagAccess, CDialog)
	//{{AFX_MSG_MAP(PageTagAccess)
	ON_BN_CLICKED(IDC_BTN_TAGQUERY, OnBtnTagquery)
	ON_BN_CLICKED(IDC_BTN_TAG_READ, OnBtnTagRead)
	ON_BN_CLICKED(IDC_BTN_TAG_WRITE, OnBtnTagWrite)
	ON_BN_CLICKED(IDC_BTN_TAG_LOCK, OnBtnTagLock)
	ON_BN_CLICKED(IDC_BTN_TAG_KILL, OnBtnTagKill)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PageTagAccess message handlers

void PageTagAccess::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void PageTagAccess::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	//CDialog::OnCancel();
}

void PageTagAccess::OnConnect()
{
	m_btn_tagquery.EnableWindow(TRUE);
	m_btn_tagread.EnableWindow(TRUE);
	m_btn_tagwrite.EnableWindow(TRUE);
	m_btn_taglock.EnableWindow(TRUE);
	m_btn_tagkill.EnableWindow(TRUE);

	m_edit_emsg.SetWindowText("");
}

void PageTagAccess::OnDisconnect()
{
	m_btn_tagquery.EnableWindow(FALSE);
	m_btn_tagread.EnableWindow(FALSE);
	m_btn_tagwrite.EnableWindow(FALSE);
	m_btn_taglock.EnableWindow(FALSE);
	m_btn_tagkill.EnableWindow(FALSE);
	//m_edit_epc.SetWindowText("");

	//
	{
	CString l_str;
	m_btn_tagread.GetWindowText(l_str);
	if(l_str == "Stop")
	{
		OnBtnTagRead();
	}
	m_btn_tagwrite.GetWindowText(l_str);
	if(l_str == "Stop")
	{
		OnBtnTagWrite();
	}
	}
}

void PageTagAccess::OnBtnTagquery() 
{
	// TODO: Add your control notification handler code here
	CWaitCursor wait;
	unsigned char* n_tag = NULL;
	CString     n_str;

	int n_tag_size = ::SSUTagQuery(((CSSUDemoDlg*)GetParent())->m_reader, &n_tag, NULL);
	if(0 < n_tag_size)
	{
		btoh(n_tag, n_tag_size, n_str);
	}
	m_edit_epc.SetWindowText(n_str);
}

void PageTagAccess::OnBtnTagRead() 
{
	// TODO: Add your control notification handler code here
	CWaitCursor   wait;
	CString       n_tmp_str;

	unsigned char n_tag[SSU_TAGID_MAXSIZE];
	int           n_tag_size;

	int           n_read_bank;
	int           n_read_start;
	int           n_read_words;
	unsigned char n_read_data[256];

	unsigned char n_read_pwd[4];

	m_btn_tagread.GetWindowText(n_tmp_str);

	if(n_tmp_str == "Stop")
	{
		m_should_break = TRUE;
	}
	else
	{
		m_edit_emsg.SetWindowText("");

		if(!m_chk_readany.GetCheck())
		{
			m_edit_epc.GetWindowText(n_tmp_str);
			memset(n_tag, 0, sizeof(n_tag));
			if(0 < n_tmp_str.GetLength())
			{
				n_tag_size = htob(n_tmp_str, n_tmp_str.GetLength(), n_tag, sizeof(n_tag));
			}
			else
			{
				n_tag_size = -1;
			}
		}
		else
		{
			n_tag_size = 0;
		}

		m_edit_pwd_read.GetWindowText(n_tmp_str);
		if(n_tmp_str.GetLength() != 8 || 0 > htob(n_tmp_str, n_tmp_str.GetLength(), n_read_pwd, sizeof(n_read_pwd)))
		{
			n_tag_size = -1;
		}

		n_read_bank = m_combo_sect_read.GetCurSel();
		if(0 <= n_read_bank)
		{
			m_edit_start_read.GetWindowText(n_tmp_str);
			n_read_start = atoi(n_tmp_str);
		}
		else
		{
			n_tag_size = -1;
		}

		m_edit_words_read.GetWindowText(n_tmp_str);
		if(0 < n_tmp_str.GetLength())
		{
			n_read_words = atoi(n_tmp_str);
		}
		else
		{
			n_tag_size = -1;
		}

		if(0 <= n_tag_size)
		{
			if(!m_check_read_continue.GetCheck())
			{
				int l_ret = SSUTagRead(((CSSUDemoDlg*)GetParent())->m_reader, n_read_pwd, n_tag, &n_tag_size, n_read_bank, n_read_start, n_read_words, n_read_data, (-1));
				if(0 <= l_ret)
				{
					if(0 < n_tag_size)
					{
						btoh(n_tag, n_tag_size, n_tmp_str);
						m_edit_epc.SetWindowText(n_tmp_str);
					}
					btoh(n_read_data, n_read_words*2, n_tmp_str);
					m_edit_data_read.SetWindowText(n_tmp_str);

					m_edit_emsg.SetWindowText("Success.");
				}
				else
				{
					n_tmp_str.Format("failed to read tag, error code: %d", l_ret);
					m_edit_emsg.SetWindowText(n_tmp_str);//MessageBox(n_tmp_str, "error", MB_OK);
				}
			}
			else
			{
				m_btn_tagread.SetWindowText("Stop");
				m_should_break = FALSE;

				do
				{
					int l_ret = SSUTagRead(((CSSUDemoDlg*)GetParent())->m_reader, n_read_pwd, n_tag, &n_tag_size, n_read_bank, n_read_start, n_read_words, n_read_data, (-1));
					if(0 <= l_ret)
					{
						if(0 < n_tag_size)
						{
							btoh(n_tag, n_tag_size, n_tmp_str);
							m_edit_epc.SetWindowText(n_tmp_str);
						}
						btoh(n_read_data, n_read_words*2, n_tmp_str);
						m_edit_data_read.SetWindowText(n_tmp_str);

						m_edit_emsg.SetWindowText("Success.");
					}
					else
					{
						n_tmp_str.Format("failed to read tag, error code: %d", l_ret);
						m_edit_emsg.SetWindowText(n_tmp_str);//MessageBox(n_tmp_str, "error", MB_OK);
					}

					//消息泵
					{
						// message pump
						MSG message;   
						while(::PeekMessage(&message,NULL,0,0,PM_REMOVE))   
						{   
							::TranslateMessage(&message);   
							::DispatchMessage(&message);   
						} 
    
						// 模拟空闲处理
						//long iCount = 0;
						//while(AfxGetApp()->OnIdle(iCount++));
					}
				}
				while(!m_should_break);

				m_btn_tagread.SetWindowText("TagRead");
			}
		}
		else
		{
			MsgBox("error", "wrong input!", MB_OK);
		}
	}
}

void PageTagAccess::OnBtnTagWrite() 
{
	// TODO: Add your control notification handler code here
	CWaitCursor   wait;
	CString       n_tmp_str;

	unsigned char n_tag[SSU_TAGID_MAXSIZE];
	int           n_tag_size;

	int           n_write_bank;
	int           n_write_start;
	int           n_write_words;
	unsigned char n_write_data[256];

	unsigned char n_write_pwd[4];

	m_btn_tagwrite.GetWindowText(n_tmp_str);

	if(n_tmp_str == "Stop")
	{
		m_should_break = TRUE;
	}
	else
	{
		m_edit_emsg.SetWindowText("");

		if(!m_chk_writeany.GetCheck())
		{
			m_edit_epc.GetWindowText(n_tmp_str);
			memset(n_tag, 0, sizeof(n_tag));
			if(0 < n_tmp_str.GetLength())
			{
				n_tag_size = htob(n_tmp_str, n_tmp_str.GetLength(), n_tag, sizeof(n_tag));
			}
			else
			{
				n_tag_size = -1;
			}
		}
		else
		{
			n_tag_size = 0;
		}

		m_edit_pwd_write.GetWindowText(n_tmp_str);
		if(n_tmp_str.GetLength() != 8 || 0 > htob(n_tmp_str, n_tmp_str.GetLength(), n_write_pwd, sizeof(n_write_pwd)))
		{
			n_tag_size = -1;
		}

		n_write_bank = m_combo_sect_write.GetCurSel();
		if(0 <= n_write_bank)
		{
			m_edit_start_write.GetWindowText(n_tmp_str);
			n_write_start = atoi(n_tmp_str);
		}
		else
		{
			n_tag_size = -1;
		}

		m_edit_word_write.GetWindowText(n_tmp_str);
		if(0 < n_tmp_str.GetLength())
		{
			n_write_words = atoi(n_tmp_str);
		}
		else
		{
			n_tag_size = -1;
		}

		m_edit_data_write.GetWindowText(n_tmp_str);
		if(0 < n_tmp_str.GetLength() && n_tmp_str.GetLength()%2 == 0)
		{
			if(n_write_words*2 !=  htob(n_tmp_str, n_tmp_str.GetLength(), n_write_data, sizeof(n_write_data)))
			{
				n_tag_size = -1;
			}
		}
		else
		{
			n_tag_size = -1;
		}

		if(0 <= n_tag_size)
		{
			if(!m_check_write_continue.GetCheck())
			{
				int l_ret = SSUTagWrite(((CSSUDemoDlg*)GetParent())->m_reader, n_write_pwd, n_tag, &n_tag_size, n_write_bank, n_write_start, n_write_words, n_write_data, (-1));
				if(0 <= l_ret)
				{
					if(0 < n_tag_size)
					{
						btoh(n_tag, n_tag_size, n_tmp_str);
						m_edit_epc.SetWindowText(n_tmp_str);
					}
					m_edit_emsg.SetWindowText("Success.");
				}
				else
				{
					n_tmp_str.Format("failed to write tag, error: %d", l_ret);
					//MsgBox("error", n_tmp_str, MB_OK);
					m_edit_emsg.SetWindowText(n_tmp_str);
				}
			}
			else if(IDOK == MsgBox("Hint", "if you write the tag too more times, it might be damaged. Continue?", MB_OKCANCEL))
			{
				m_btn_tagwrite.SetWindowText("Stop");
				m_should_break = FALSE;

				do
				{
					int l_ret = SSUTagWrite(((CSSUDemoDlg*)GetParent())->m_reader, n_write_pwd, n_tag, &n_tag_size, n_write_bank, n_write_start, n_write_words, n_write_data, (-1));
					if(0 <= l_ret)
					{
						if(0 < n_tag_size)
						{
							btoh(n_tag, n_tag_size, n_tmp_str);
							m_edit_epc.SetWindowText(n_tmp_str);
						}
						m_edit_emsg.SetWindowText("Success.");
					}
					else
					{
						n_tmp_str.Format("failed to write tag, error: %d", l_ret);
						m_edit_emsg.SetWindowText(n_tmp_str);
					}

					//消息泵
					{
						// message pump
						MSG message;   
						while(::PeekMessage(&message,NULL,0,0,PM_REMOVE))   
						{   
							::TranslateMessage(&message);   
							::DispatchMessage(&message);   
						} 
    
						// 模拟空闲处理
						//long iCount = 0;
						//while(AfxGetApp()->OnIdle(iCount++));
					}

				}
				while(!m_should_break);

				m_btn_tagwrite.SetWindowText("TagWrite");
			}
		}
		else
		{
			MsgBox("error", "wrong input!", MB_OK);
		}
	}
}

void PageTagAccess::OnBtnTagLock() 
{
	// TODO: Add your control notification handler code here
	CWaitCursor   wait;
	CString       n_tmp_str;
	int           n_status;

	unsigned char n_tag[SSU_TAGID_MAXSIZE];
	int           n_tag_size;

	unsigned char  n_data_lock[3];

	unsigned char  n_pwd[4] = {0,0,0,0};
	unsigned char  n_sect = 0;
	unsigned char  n_opt = 0;
	unsigned int   n_lock_mask = 0, n_lock_action = 0;

	m_edit_epc.GetWindowText(n_tmp_str);
	memset(n_tag, 0, sizeof(n_tag));
	if(0 < n_tmp_str.GetLength())
	{
		n_tag_size = htob(n_tmp_str, n_tmp_str.GetLength(), n_tag, sizeof(n_tag));
	}
	else
	{
		n_tag_size = -1;
	}

	m_edit_pwd_lock.GetWindowText(n_tmp_str);
	if(n_tmp_str.GetLength() != 8 || sizeof(n_pwd) != htob(n_tmp_str, n_tmp_str.GetLength(), n_pwd, sizeof(n_pwd)))
	{
		n_tag_size = -1;
	}

	n_sect = m_combo_sect_lock.GetCurSel();
	n_opt = m_combo_opt_lock.GetCurSel();

	switch(n_opt)
	{
	case 0: // 解锁
		n_lock_action = 0x00;
		break;
	case 1: // 加锁
		n_lock_action = 0x02;
		break;
	case 2: // 永久写保护
		n_lock_action = 0x03;
		break;
	default:
		n_lock_action = 0;
		break;
	}
	switch(n_sect)
	{
	case 0: // reserved
		n_lock_mask = ((0x03 << 18) | (0x03 << 16));
		n_lock_action = ((n_lock_action << 8) | (n_lock_action << 6));
		break;
	case 1: // epc
		n_lock_mask = (0x03 << 14);
		n_lock_action = (n_lock_action << 4);
		break;
	case 2: // TID
		n_lock_mask = (0x03 << 12);
		n_lock_action = (n_lock_action << 2);
		break;
	case 3:
		n_lock_mask = (0x03 << 10);
		n_lock_action = (n_lock_action << 0);
		break;
	default:
		n_lock_mask = 0;
		break;
	}

	if(0 < n_tag_size)
	{
		n_data_lock[0] = ((n_lock_mask | n_lock_action) >> 16);
		n_data_lock[1] = ((n_lock_mask | n_lock_action) >> 8);
		n_data_lock[2] = ((n_lock_mask | n_lock_action) >> 0);

		if(0 > (n_status = SSUTagLock(((CSSUDemoDlg*)GetParent())->m_reader, n_pwd, n_tag, n_tag_size, n_data_lock, (-1))))
		{
			n_tmp_str.Format("failed to lock tag, error: %d", n_status);
			m_edit_emsg.SetWindowText(n_tmp_str);
		}
	}
	else
	{
		MsgBox("error", "wrong input", MB_OK);
	}
}

void PageTagAccess::OnBtnTagKill() 
{
	// TODO: Add your control notification handler code here
	CWaitCursor   wait;
	CString       n_tmp_str;
	int           n_status;

	unsigned char n_tag[SSU_TAGID_MAXSIZE];
	int           n_tag_size;

	unsigned char  n_pwd[4] = {0,0,0,0};
	unsigned char  n_pwd_kill[4] = {0,0,0,0};

	m_edit_epc.GetWindowText(n_tmp_str);
	memset(n_tag, 0, sizeof(n_tag));
	if(0 < n_tmp_str.GetLength())
	{
		n_tag_size = htob(n_tmp_str, n_tmp_str.GetLength(), n_tag, sizeof(n_tag));
	}
	else
	{
		n_tag_size = -1;
	}

	m_edit_pwd_acc.GetWindowText(n_tmp_str);
	if(n_tmp_str.GetLength() != 8 || sizeof(n_pwd) != htob(n_tmp_str, n_tmp_str.GetLength(), n_pwd, sizeof(n_pwd)))
	{
		n_tag_size = -1;
	}

	m_edit_pwd_kill.GetWindowText(n_tmp_str);
	if(n_tmp_str.GetLength() != 8 || sizeof(n_pwd_kill) != htob(n_tmp_str, n_tmp_str.GetLength(), n_pwd_kill, sizeof(n_pwd_kill)))
	{
		n_tag_size = -1;
	}


	if(0 < n_tag_size)
	{
		if(0 > (n_status = SSUTagKill(((CSSUDemoDlg*)GetParent())->m_reader, n_pwd, n_pwd_kill, n_tag, n_tag_size, (-1))))
		{
			n_tmp_str.Format("failed to kill tag, error: %d", n_status);
			m_edit_emsg.SetWindowText(n_tmp_str);
		}
	}
	else
	{
		MsgBox("error", "wrong input", MB_OK);
	}	
}

BOOL PageTagAccess::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_edit_epc.SetWindowText("");
	m_edit_start_read.SetWindowText("0");
	m_edit_words_read.SetWindowText("8");
	m_edit_pwd_acc.SetWindowText("00000000");
	m_edit_pwd_kill.SetWindowText("00000000");
	m_edit_pwd_read.SetWindowText("00000000");
	m_edit_pwd_write.SetWindowText("00000000");
	m_edit_pwd_lock.SetWindowText("00000000");

	m_combo_sect_read.SetCurSel(3);
	m_combo_sect_write.SetCurSel(3);
	m_combo_sect_lock.SetCurSel(3);
	m_combo_opt_lock.SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

