// PageTagAccessEx.cpp : implementation file
//

#include "stdafx.h"
#include "ssudemo.h"
#include "PageTagAccessEx.h"

#include "SSUDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PageTagAccessEx dialog


PageTagAccessEx::PageTagAccessEx(CWnd* pParent /*=NULL*/)
	: CDialog(PageTagAccessEx::IDD, pParent)
{
	//{{AFX_DATA_INIT(PageTagAccessEx)
	//}}AFX_DATA_INIT
}


void PageTagAccessEx::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PageTagAccessEx)
	DDX_Control(pDX, IDC_CHECK_KILPWD, m_check_kilpwd);
	DDX_Control(pDX, IDC_CHECK_ACCPWD, m_check_accpwd);
	DDX_Control(pDX, IDC_EDIT_WRITE_PWD_KILL, m_edit_write_pwd_kill);
	DDX_Control(pDX, IDC_EDIT_WRITE_PWD_ACCESS, m_edit_write_pwd_access);
	DDX_Control(pDX, IDC_EDIT_KILL_PWD, m_edit_kill_pwd);
	DDX_Control(pDX, IDC_EDIT_WRITE_EPC, m_edit_write_epc);
	DDX_Control(pDX, IDC_EDIT_WORDS_WRITE_USR, m_edit_words_write_usr);
	DDX_Control(pDX, IDC_EDIT_WORDS_READ_USR, m_edit_words_read_usr);
	DDX_Control(pDX, IDC_EDIT_WORDS_READ_TID, m_edit_words_read_tid);
	DDX_Control(pDX, IDC_EDIT_START_WRITE_USR, m_edit_start_write_usr);
	DDX_Control(pDX, IDC_EDIT_START_READ_USR, m_edit_start_read_usr);
	DDX_Control(pDX, IDC_EDIT_START_READ_TID, m_edit_start_read_tid);
	DDX_Control(pDX, IDC_EDIT_ACCPWD, m_edit_accpwd);
	DDX_Control(pDX, IDC_EDIT_EPC, m_edit_epc);
	DDX_Control(pDX, IDC_EDIT_EMSG, m_edit_emsg);
	DDX_Control(pDX, IDC_EDIT_DATA_WRITE_USR, m_edit_data_write_usr);
	DDX_Control(pDX, IDC_EDIT_DATA_READ_USR, m_edit_data_read_usr);
	DDX_Control(pDX, IDC_EDIT_DATA_READ_TID, m_edit_data_read_tid);
	DDX_Control(pDX, IDC_BTN_TAGQUERY, m_btn_tag_query);
	DDX_Control(pDX, IDC_BTN_TAG_WRITE_USR, m_btn_tag_write_usr);
	DDX_Control(pDX, IDC_BTN_TAG_WRITE_PWD, m_btn_tag_write_pwd);
	DDX_Control(pDX, IDC_BTN_TAG_WRITE_EPC, m_btn_tag_write_epc);
	DDX_Control(pDX, IDC_BTN_TAG_READ_USR, m_btn_tag_read_usr);
	DDX_Control(pDX, IDC_BTN_TAG_READ_TID, m_btn_tag_read_tid);
	DDX_Control(pDX, IDC_BTN_TAG_LOCK_USR, m_btn_tag_lock_usr);
	DDX_Control(pDX, IDC_BTN_TAG_LOCK_EPC, m_btn_tag_lock_epc);
	DDX_Control(pDX, IDC_BTN_TAG_KILL_EX, m_btn_tag_kill_ex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PageTagAccessEx, CDialog)
	//{{AFX_MSG_MAP(PageTagAccessEx)
	ON_BN_CLICKED(IDC_BTN_TAGQUERY, OnBtnTagquery)
	ON_BN_CLICKED(IDC_BTN_TAG_READ_TID, OnBtnTagReadTid)
	ON_BN_CLICKED(IDC_BTN_TAG_READ_USR, OnBtnTagReadUsr)
	ON_BN_CLICKED(IDC_BTN_TAG_WRITE_PWD, OnBtnTagWritePwd)
	ON_BN_CLICKED(IDC_BTN_TAG_WRITE_EPC, OnBtnTagWriteEpc)
	ON_BN_CLICKED(IDC_BTN_TAG_WRITE_USR, OnBtnTagWriteUsr)
	ON_BN_CLICKED(IDC_BTN_TAG_KILL_EX, OnBtnTagKillEx)
	ON_BN_CLICKED(IDC_BTN_TAG_LOCK_EPC, OnBtnTagLockEpc)
	ON_BN_CLICKED(IDC_BTN_TAG_LOCK_USR, OnBtnTagLockUsr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PageTagAccessEx message handlers
void PageTagAccessEx::OnConnect()
{
	m_btn_tag_query.EnableWindow(TRUE);
	m_btn_tag_read_tid.EnableWindow(TRUE);
	m_btn_tag_read_usr.EnableWindow(TRUE);
	m_btn_tag_write_usr.EnableWindow(TRUE);
	m_btn_tag_write_epc.EnableWindow(TRUE);
	m_btn_tag_write_pwd.EnableWindow(TRUE);
	m_btn_tag_lock_epc.EnableWindow(TRUE);
	m_btn_tag_lock_usr.EnableWindow(TRUE);
	m_btn_tag_kill_ex.EnableWindow(TRUE);

	m_edit_emsg.SetWindowText("");
}

void PageTagAccessEx::OnDisconnect()
{
	m_btn_tag_query.EnableWindow(FALSE);
	m_btn_tag_read_tid.EnableWindow(FALSE);
	m_btn_tag_read_usr.EnableWindow(FALSE);
	m_btn_tag_write_usr.EnableWindow(FALSE);
	m_btn_tag_write_epc.EnableWindow(FALSE);
	m_btn_tag_write_pwd.EnableWindow(FALSE);
	m_btn_tag_lock_epc.EnableWindow(FALSE);
	m_btn_tag_lock_usr.EnableWindow(FALSE);
	m_btn_tag_kill_ex.EnableWindow(FALSE);
}


BOOL PageTagAccessEx::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void PageTagAccessEx::OnBtnTagquery() 
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

void PageTagAccessEx::OnBtnTagReadTid() 
{
	// TODO: Add your control notification handler code here
	CWaitCursor   wait;
	CString       n_tmp_str;

	unsigned char n_tag[SSU_TAGID_MAXSIZE];
	int           n_tag_size;

	int           n_read_start;
	int           n_read_words;
	unsigned char n_read_data[256];

	m_edit_emsg.SetWindowText("");

	m_edit_epc.GetWindowText(n_tmp_str);
	if(!n_tmp_str.IsEmpty())
	{
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

	m_edit_start_read_tid.GetWindowText(n_tmp_str);
	if(0 < n_tmp_str.GetLength())
	{
		n_read_start = atoi(n_tmp_str);
		if(0 > n_read_start)
		{
			n_tag_size = -1;
		}
	}
	else
	{
		n_tag_size = -1;
	}

	m_edit_words_read_tid.GetWindowText(n_tmp_str);
	if(0 < n_tmp_str.GetLength())
	{
		n_read_words = atoi(n_tmp_str);
		if(0 >= n_read_words)
		{
			n_tag_size = -1;
		}
	}
	else
	{
		n_tag_size = -1;
	}

	if(0 < n_tag_size)
	{
		int l_ret = SSUTagReadTID(((CSSUDemoDlg*)GetParent())->m_reader, n_tag, &n_tag_size, n_read_start, n_read_words, n_read_data);
		if(0 <= l_ret)
		{
			CString l_msg;

			btoh(n_read_data, n_read_words*2, n_tmp_str);
			m_edit_data_read_tid.SetWindowText(n_tmp_str);

			btoh(n_tag, n_tag_size, n_tmp_str);
			l_msg.Format("Success to read the sector TID of tag [%s]", n_tmp_str.LockBuffer());
			n_tmp_str.UnlockBuffer();
			m_edit_emsg.SetWindowText(l_msg);
		}
		else
		{
			n_tmp_str.Format("failed to read tag, error code: %d", l_ret);
			m_edit_emsg.SetWindowText(n_tmp_str);//MessageBox(n_tmp_str, "error", MB_OK);
		}
	}
	else
	{
		MsgBox("error", "wrong input!", MB_OK);
	}
}

void PageTagAccessEx::OnBtnTagReadUsr() 
{
	// TODO: Add your control notification handler code here
	CWaitCursor   wait;
	CString       n_tmp_str;

	unsigned char n_tag[SSU_TAGID_MAXSIZE];
	int           n_tag_size;

	int           n_read_start;
	int           n_read_words;
	unsigned char n_read_data[256];

	m_edit_emsg.SetWindowText("");

	m_edit_epc.GetWindowText(n_tmp_str);
	if(!n_tmp_str.IsEmpty())
	{
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

	m_edit_start_read_usr.GetWindowText(n_tmp_str);
	if(0 < n_tmp_str.GetLength())
	{
		n_read_start = atoi(n_tmp_str);
		if(0 > n_read_start)
		{
			n_tag_size = -1;
		}
	}
	else
	{
		n_tag_size = -1;
	}

	m_edit_words_read_usr.GetWindowText(n_tmp_str);
	if(0 < n_tmp_str.GetLength())
	{
		n_read_words = atoi(n_tmp_str);
		if(0 >= n_read_words)
		{
			n_tag_size = -1;
		}
	}
	else
	{
		n_tag_size = -1;
	}

	if(0 < n_tag_size)
	{
		int l_ret = SSUTagReadUSR(((CSSUDemoDlg*)GetParent())->m_reader, n_tag, &n_tag_size, n_read_start, n_read_words, n_read_data);
		if(0 <= l_ret)
		{
			CString l_msg;

			btoh(n_read_data, n_read_words*2, n_tmp_str);
			m_edit_data_read_usr.SetWindowText(n_tmp_str);

			btoh(n_tag, n_tag_size, n_tmp_str);
			l_msg.Format("Success to read the sector USER of tag [%s]", n_tmp_str.LockBuffer());
			n_tmp_str.UnlockBuffer();
			m_edit_emsg.SetWindowText(l_msg);
		}
		else
		{
			n_tmp_str.Format("failed to read tag, error code: %d", l_ret);
			m_edit_emsg.SetWindowText(n_tmp_str);//MessageBox(n_tmp_str, "error", MB_OK);
		}
	}
	else
	{
		MsgBox("error", "wrong input!", MB_OK);
	}	
}

void PageTagAccessEx::OnBtnTagWritePwd() 
{
	// TODO: Add your control notification handler code here
	CWaitCursor   wait;
	CString       n_tmp_str;

	unsigned char n_tag[SSU_TAGID_MAXSIZE];
	int           n_tag_size;

	CString       n_access_pwd;
	CString       n_write_pwd_access;
	CString       n_write_pwd_kill;

	m_edit_emsg.SetWindowText("");

	m_edit_epc.GetWindowText(n_tmp_str);
	if(!n_tmp_str.IsEmpty())
	{
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

	m_edit_accpwd.GetWindowText(n_access_pwd);

	if(m_check_accpwd.GetCheck())
	{
		m_edit_write_pwd_access.GetWindowText(n_write_pwd_access);
	}

	if(m_check_kilpwd.GetCheck())
	{
		m_edit_write_pwd_kill.GetWindowText(n_write_pwd_kill);
	}

	if(!m_check_accpwd.GetCheck() && !m_check_kilpwd.GetCheck())
	{
		n_tag_size = -1;
	}

	if(0 < n_tag_size)
	{
		int         l_ret = 0;
		const char* l_pwd_acc = NULL;
		const char* l_pwd_kil = NULL;

		if(m_check_accpwd.GetCheck())
		{
			l_pwd_acc = n_write_pwd_access.LockBuffer();
		}
		if(m_check_kilpwd.GetCheck())
		{
			l_pwd_kil = n_write_pwd_kill.LockBuffer();
		}

		l_ret = SSUTagResetPWD(((CSSUDemoDlg*)GetParent())->m_reader, n_access_pwd, n_tag, n_tag_size, l_pwd_acc, l_pwd_kil);
		if(0 <= l_ret)
		{
			CString l_msg;

			btoh(n_tag, n_tag_size, n_tmp_str);
			l_msg.Format("Success to write the Password of tag [%s]", n_tmp_str.LockBuffer());
			n_tmp_str.UnlockBuffer();
			m_edit_emsg.SetWindowText(l_msg);
		}
		else
		{
			n_tmp_str.Format("failed to write tag, error code: %d", l_ret);
			m_edit_emsg.SetWindowText(n_tmp_str);//MessageBox(n_tmp_str, "error", MB_OK);
		}

		if(m_check_accpwd.GetCheck())
		{
			n_write_pwd_access.UnlockBuffer();
		}
		if(m_check_kilpwd.GetCheck())
		{
			n_write_pwd_kill.UnlockBuffer();
		}
	}
	else
	{
		MsgBox("error", "wrong input!", MB_OK);
	}
}

void PageTagAccessEx::OnBtnTagWriteEpc() 
{
	// TODO: Add your control notification handler code here
	CWaitCursor   wait;
	CString       n_tmp_str;

	unsigned char n_tag[SSU_TAGID_MAXSIZE];
	int           n_tag_size;

	unsigned char n_epc[SSU_TAGID_MAXSIZE];
	int           n_epc_size;

	CString       n_access_pwd;

	m_edit_emsg.SetWindowText("");

	m_edit_epc.GetWindowText(n_tmp_str);
	if(!n_tmp_str.IsEmpty())
	{
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

	m_edit_accpwd.GetWindowText(n_access_pwd);

	m_edit_write_epc.GetWindowText(n_tmp_str);
	if(!n_tmp_str.IsEmpty())
	{
		memset(n_epc, 0, sizeof(n_epc));
		if(0 < n_tmp_str.GetLength())
		{
			if(0 >= (n_epc_size = htob(n_tmp_str, n_tmp_str.GetLength(), n_epc, sizeof(n_epc))))
			{
				n_tag_size = -1;
			}
		}
		else
		{
			n_tag_size = -1;
		}
	}
	else
	{
		n_tag_size = -1;
	}


	if(0 < n_tag_size)
	{
		int l_ret = SSUTagResetEPC(((CSSUDemoDlg*)GetParent())->m_reader, n_access_pwd, n_tag, n_tag_size, n_epc, n_epc_size);
		if(0 <= l_ret)
		{
			CString l_msg;

			btoh(n_tag, n_tag_size, n_tmp_str);
			l_msg.Format("Success to write the sector EPC of tag [%s]", n_tmp_str.LockBuffer());
			n_tmp_str.UnlockBuffer();
			m_edit_emsg.SetWindowText(l_msg);
		}
		else
		{
			n_tmp_str.Format("failed to write tag, error code: %d", l_ret);
			m_edit_emsg.SetWindowText(n_tmp_str);//MessageBox(n_tmp_str, "error", MB_OK);
		}
	}
	else
	{
		MsgBox("error", "wrong input!", MB_OK);
	}
}

void PageTagAccessEx::OnBtnTagWriteUsr() 
{
	// TODO: Add your control notification handler code here
	CWaitCursor   wait;
	CString       n_tmp_str;

	unsigned char n_tag[SSU_TAGID_MAXSIZE];
	int           n_tag_size;

	int           n_write_start;
	int           n_write_words;
	unsigned char n_write_data[256];

	CString       n_access_pwd;

	m_edit_emsg.SetWindowText("");

	m_edit_epc.GetWindowText(n_tmp_str);
	if(!n_tmp_str.IsEmpty())
	{
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

	m_edit_accpwd.GetWindowText(n_access_pwd);

	m_edit_start_write_usr.GetWindowText(n_tmp_str);
	if(0 < n_tmp_str.GetLength())
	{
		n_write_start = atoi(n_tmp_str);
		if(0 > n_write_start)
		{
			n_tag_size = -1;
		}
	}
	else
	{
		n_tag_size = -1;
	}

	m_edit_words_write_usr.GetWindowText(n_tmp_str);
	if(0 < n_tmp_str.GetLength())
	{
		n_write_words = atoi(n_tmp_str);
		if(0 >= n_write_words)
		{
			n_tag_size = -1;
		}
	}
	else
	{
		n_tag_size = -1;
	}

	m_edit_data_write_usr.GetWindowText(n_tmp_str);
	if(!n_tmp_str.IsEmpty())
	{
		memset(n_write_data, 0, sizeof(n_write_data));
		if(0 < n_tmp_str.GetLength())
		{
			if(n_write_words * 2 != htob(n_tmp_str, n_tmp_str.GetLength(), n_write_data, sizeof(n_write_data)))
			{
				n_tag_size = -1;
			}
		}
		else
		{
			n_tag_size = -1;
		}
	}
	else
	{
		n_tag_size = -1;
	}


	if(0 < n_tag_size)
	{
		int l_ret = SSUTagWriteUSR(((CSSUDemoDlg*)GetParent())->m_reader, n_access_pwd, n_tag, &n_tag_size, n_write_start, n_write_words, n_write_data);
		if(0 <= l_ret)
		{
			CString l_msg;

			btoh(n_tag, n_tag_size, n_tmp_str);
			l_msg.Format("Success to write the sector USER of tag [%s]", n_tmp_str.LockBuffer());
			n_tmp_str.UnlockBuffer();
			m_edit_emsg.SetWindowText(l_msg);
		}
		else
		{
			n_tmp_str.Format("failed to write tag, error code: %d", l_ret);
			m_edit_emsg.SetWindowText(n_tmp_str);//MessageBox(n_tmp_str, "error", MB_OK);
		}
	}
	else
	{
		MsgBox("error", "wrong input!", MB_OK);
	}
}

void PageTagAccessEx::OnBtnTagLockEpc() 
{
	// TODO: Add your control notification handler code here
	CWaitCursor   wait;
	CString       n_tmp_str;

	unsigned char n_tag[SSU_TAGID_MAXSIZE];
	int           n_tag_size;

	CString       n_access_pwd;

	m_edit_emsg.SetWindowText("");

	m_edit_epc.GetWindowText(n_tmp_str);
	if(!n_tmp_str.IsEmpty())
	{
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
		n_tag_size = -1;
	}

	m_edit_accpwd.GetWindowText(n_access_pwd);

	if(0 < n_tag_size)
	{
		if(IDOK == MsgBox("Hint", "if you execute the function SSUTagLockEPC, the sector EPC will be protected from writing. continue?", MB_OKCANCEL))
		{
			int l_ret = SSUTagSolitifyEPC(((CSSUDemoDlg*)GetParent())->m_reader, n_access_pwd, n_tag, n_tag_size);
			if(0 <= l_ret)
			{
				CString l_msg;

				btoh(n_tag, n_tag_size, n_tmp_str);
				l_msg.Format("Success to permamently lock the sector EPC of tag [%s]", n_tmp_str.LockBuffer());
				n_tmp_str.UnlockBuffer();
				m_edit_emsg.SetWindowText(l_msg);
			}
			else
			{
				n_tmp_str.Format("failed to permanently lock the tag, error code: %d", l_ret);
				m_edit_emsg.SetWindowText(n_tmp_str);//MessageBox(n_tmp_str, "error", MB_OK);
			}
		}
	}
	else
	{
		MsgBox("error", "wrong input!", MB_OK);
	}	
}

void PageTagAccessEx::OnBtnTagLockUsr() 
{
	// TODO: Add your control notification handler code here
	CWaitCursor   wait;
	CString       n_tmp_str;

	unsigned char n_tag[SSU_TAGID_MAXSIZE];
	int           n_tag_size;

	CString       n_access_pwd;

	m_edit_emsg.SetWindowText("");

	m_edit_epc.GetWindowText(n_tmp_str);
	if(!n_tmp_str.IsEmpty())
	{
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
		n_tag_size = -1;
	}

	m_edit_accpwd.GetWindowText(n_access_pwd);

	if(0 < n_tag_size)
	{
		if(IDOK == MsgBox("Hint", "if you execute the function SSUTagLockUSR, the sector USER will be protected from writing. continue?", MB_OKCANCEL))
		{
			int l_ret = SSUTagSolitifyUSR(((CSSUDemoDlg*)GetParent())->m_reader, n_access_pwd, n_tag, n_tag_size);
			if(0 <= l_ret)
			{
				CString l_msg;

				btoh(n_tag, n_tag_size, n_tmp_str);
				l_msg.Format("Success to permamently lock the sector USER of tag [%s]", n_tmp_str.LockBuffer());
				n_tmp_str.UnlockBuffer();
				m_edit_emsg.SetWindowText(l_msg);
			}
			else
			{
				n_tmp_str.Format("failed to permanently lock the tag, error code: %d", l_ret);
				m_edit_emsg.SetWindowText(n_tmp_str);//MessageBox(n_tmp_str, "error", MB_OK);
			}
		}
	}
	else
	{
		MsgBox("error", "wrong input!", MB_OK);
	}	
}

void PageTagAccessEx::OnBtnTagKillEx() 
{
	// TODO: Add your control notification handler code here
	CWaitCursor   wait;
	CString       n_tmp_str;

	unsigned char n_tag[SSU_TAGID_MAXSIZE];
	int           n_tag_size;

	CString       n_access_pwd;
	CString       n_kill_pwd;

	m_edit_emsg.SetWindowText("");

	m_edit_epc.GetWindowText(n_tmp_str);
	if(!n_tmp_str.IsEmpty())
	{
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
		n_tag_size = -1;
	}

	m_edit_accpwd.GetWindowText(n_access_pwd);

	m_edit_kill_pwd.GetWindowText(n_kill_pwd);

	if(0 <= n_tag_size)
	{
		if(IDOK == MsgBox("Hint", "if you execute the function SSUTagKillEx, the tag will be killed and never be identified. continue?", MB_OKCANCEL))
		{
			int         l_ret = 0;
			l_ret = SSUTagKillEx(((CSSUDemoDlg*)GetParent())->m_reader, n_access_pwd, n_kill_pwd, n_tag, n_tag_size);
			if(0 <= l_ret)
			{
				CString l_msg;

				btoh(n_tag, n_tag_size, n_tmp_str);
				l_msg.Format("Success to kill the tag [%s]", n_tmp_str.LockBuffer());
				n_tmp_str.UnlockBuffer();
				m_edit_emsg.SetWindowText(l_msg);
			}
			else
			{
				n_tmp_str.Format("failed to kill tag, error code: %d", l_ret);
				m_edit_emsg.SetWindowText(n_tmp_str);//MessageBox(n_tmp_str, "error", MB_OK);
			}
		}
	}
	else
	{
		MsgBox("error", "wrong input!", MB_OK);
	}	
}

