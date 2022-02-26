// PageTagInventory.cpp : implementation file
//

#include "stdafx.h"
#include "SSUDemo.h"
#include "SSUDemoDlg.h"
#include "PageTagInventory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MY_TIMER_UPDATE_UI 1
/////////////////////////////////////////////////////////////////////////////
// PageTagInventory dialog


PageTagInventory::PageTagInventory(CWnd* pParent /*=NULL*/)
	: CDialog(PageTagInventory::IDD, pParent)
{
	//{{AFX_DATA_INIT(PageTagInventory)
	//}}AFX_DATA_INIT

	m_query_thread_syn_status = -1;
}


void PageTagInventory::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PageTagInventory)
	DDX_Control(pDX, IDC_BTN_CLEAR, m_btn_clear);
	DDX_Control(pDX, IDC_CHECK_INVT_REPORT, m_check_report);
	DDX_Control(pDX, IDC_CHECK_INVT_AUTO, m_check_auto);
	DDX_Control(pDX, IDC_EDIT_TAGCOUNT, m_edit_tagcount);
	DDX_Control(pDX, IDC_LIST_TAGS, m_list_tags);
	DDX_Control(pDX, IDC_BTN_INVENTORY, m_btn_inventory);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PageTagInventory, CDialog)
	//{{AFX_MSG_MAP(PageTagInventory)
	ON_BN_CLICKED(IDC_BTN_INVENTORY, OnBtnInventory)
	ON_BN_CLICKED(IDC_CHECK_INVT_AUTO, OnCheckInvtAuto)
	ON_BN_CLICKED(IDC_BTN_CLEAR, OnBtnClear)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_NOTIFY(HDN_ITEMCLICK, IDC_LIST_TAGS, OnItemclickListTags)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_TAGS, OnDblclkListTags)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PageTagInventory message handlers

int PageTagInventoryThread::InitInstance()
{	
	int            n_status = 0;
	char           n_antNo;
	unsigned char* n_tag = NULL;
	int            n_tag_size;
	int            n_interval = 0;

	m_main_wnd->m_page_inventory.m_query_thread_syn_status = 0;

	while( m_main_wnd->m_page_inventory.m_query_thread_syn_status == 0 )
	{
		n_tag_size = SSUTagQuery(m_main_wnd->m_reader, &n_tag, &n_antNo);
		if( 0 < n_tag_size )
		{
			CString  l_str_temp;

			m_main_wnd->m_page_inventory.m_data_lock.Lock();

			btoh(n_tag, n_tag_size, l_str_temp);
			m_main_wnd->m_page_inventory.m_data_tagid.Add(l_str_temp);
			l_str_temp.Format("%u", ::time(NULL));
			m_main_wnd->m_page_inventory.m_data_tagtime.Add(l_str_temp);
			if(n_antNo == (-1))
				l_str_temp.Format("%s", "");
			else
				l_str_temp.Format("%d", n_antNo);
			m_main_wnd->m_page_inventory.m_data_tagstate.Add(l_str_temp);

			m_main_wnd->m_page_inventory.m_data_lock.Unlock();
		}
		else if(0 == n_tag_size)
		{
			::Sleep(n_interval);
		}
		else
		{
			m_main_wnd->PostErrorMsg("failed to query tags from the reader");
			break;
		}

	}

	m_main_wnd->m_page_inventory.m_query_thread_syn_status = 2;

	return 0;
}


void PageTagInventory::OnBtnInventory() 
{
	// TODO: Add your control notification handler code here
	CWaitCursor  n_wait;

	CString  n_btn_text;

	m_btn_inventory.GetWindowText(n_btn_text);
	if("Query" == n_btn_text)
	{
		if(m_check_auto.GetCheck())
		{
			unsigned char l_enable_report = 0;
			if(m_check_report.GetCheck())
			{
				l_enable_report = 1;
			}
			::SSUTagInvtAuto(((CSSUDemoDlg*)GetParent())->m_reader, l_enable_report);
		}


		m_data_tagid.RemoveAll();
		m_data_tagtime.RemoveAll();
		m_data_tagstate.RemoveAll();

		m_query_thread = new PageTagInventoryThread((CSSUDemoDlg*)GetParent()); //×Ô¶¯delete
		SetTimer(MY_TIMER_UPDATE_UI, 200, NULL);
		if(m_query_thread->CreateThread())
		{
			while( m_query_thread_syn_status == -1 )
			{
				Sleep(10);
			}

			m_check_auto.EnableWindow(FALSE);
			m_check_report.EnableWindow(FALSE);
			m_btn_inventory.SetWindowText("Stop");
		}
		else
		{
			delete m_query_thread;
		}
	}
	else
	{
		if( m_query_thread_syn_status == 0 )
		{
			m_query_thread_syn_status = 1;
		}

		while( m_query_thread_syn_status == 1 )
		{
			Sleep(10);
		}

		if(m_check_auto.GetCheck())
		{
			::SSUTagInvtStop(((CSSUDemoDlg*)GetParent())->m_reader);
		}

		m_query_thread_syn_status = -1;
		KillTimer(MY_TIMER_UPDATE_UI);

		m_btn_inventory.SetWindowText("Query");
		m_check_auto.EnableWindow(TRUE);
		if(m_check_auto.GetCheck())m_check_report.EnableWindow(TRUE);
	}
}

BOOL PageTagInventory::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_list_tags.InsertColumn(0, "TagID", LVCFMT_LEFT, 280); 
	m_list_tags.InsertColumn(1, "First", LVCFMT_LEFT, 100); 
	m_list_tags.InsertColumn(2, "Last", LVCFMT_LEFT, 100); 
	m_list_tags.InsertColumn(3, "Count", LVCFMT_LEFT, 65); 
	m_list_tags.InsertColumn(4, "State", LVCFMT_LEFT, 65); 

	m_edit_tagcount.SetWindowText("0");
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void PageTagInventory::OnCheckInvtAuto() 
{
	// TODO: Add your control notification handler code here
	if(m_check_auto.GetCheck())
	{
		m_check_report.EnableWindow(TRUE);
	}
	else
	{
		m_check_report.EnableWindow(FALSE);
	}
}


void PageTagInventory::OnBtnClear() 
{
	// TODO: Add your control notification handler code here
	m_list_tags.DeleteAllItems();
	m_edit_tagcount.SetWindowText("0");
}

void PageTagInventory::DoRecvQueryData()
{
	int      i, j;
	CString  n_tagid, n_read_count;
	int      n_item = m_list_tags.GetItemCount();

	m_data_lock.Lock();
	for( i = 0; i < m_data_tagid.GetSize(); i++ )
	{
		for(j = m_list_tags.GetItemCount()-1; j >= 0; j-- )
		{
			if( m_data_tagid[i] == m_list_tags.GetItemText(j, 0) )
			{
				CString l_read_count = m_list_tags.GetItemText(j, 3);
				l_read_count.Format("%d", ::atoi(l_read_count)+1);

				m_list_tags.SetItemText(j, 2, m_data_tagtime[i]);
				m_list_tags.SetItemText(j, 3, l_read_count);
				m_list_tags.SetItemText(j, 4, m_data_tagstate[i]);
				break;
			}
		}
		if( j < 0 )
		{
			int l_item = m_list_tags.InsertItem(m_list_tags.GetItemCount(), m_data_tagid[i]);
			m_list_tags.SetItemText(l_item, 1, m_data_tagtime[i]);
			m_list_tags.SetItemText(l_item, 2, m_data_tagtime[i]);
			m_list_tags.SetItemText(l_item, 3, "1");
			m_list_tags.SetItemText(l_item, 4, m_data_tagstate[i]);
			m_list_tags.Scroll(CSize(0, l_item));
		}
	}
	m_data_tagid.RemoveAll();
	m_data_tagtime.RemoveAll();
	m_data_tagstate.RemoveAll();

	m_data_lock.Unlock();

	n_read_count.Format("%d", m_list_tags.GetItemCount());
	m_edit_tagcount.SetWindowText(n_read_count);

	UpdateData(FALSE);
}
void PageTagInventory::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch( nIDEvent )
	{
	case MY_TIMER_UPDATE_UI:
		if( m_query_thread_syn_status >= 0 && m_query_thread_syn_status < 2 )
		{
			DoRecvQueryData();
		}
		else if( m_query_thread_syn_status = 2 )
		{
			OnBtnInventory();
		}
	default:
		break;
	}
	
	CDialog::OnTimer(nIDEvent);
}

void PageTagInventory::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	m_list_tags.Invalidate();
	
	// Do not call CDialog::OnPaint() for painting messages
}

// ÅÅÐò
struct _st_sort_info
{
	CListCtrl*  ctrl;
	int         column;
	bool        asc;
};
static int CALLBACK
MyCompareProc(LPARAM itemA, LPARAM itemB, LPARAM pInfo)
{
   // lParamSort contains a pointer to the list view control.
   // The lParam of an item is just its index.
   struct _st_sort_info* n_info = (struct _st_sort_info*) pInfo;

   if( n_info->asc )
   {
	   return strcmp(n_info->ctrl->GetItemText(itemA, n_info->column), n_info->ctrl->GetItemText(itemB, n_info->column));
   }
   else
   {
	   return strcmp(n_info->ctrl->GetItemText(itemB, n_info->column), n_info->ctrl->GetItemText(itemA, n_info->column));
   }
}
void PageTagInventory::OnItemclickListTags(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	// TODO: Add your control notification handler code here
	int                   i;
	struct _st_sort_info  n_sort_info;

	switch(phdn->iItem)
	{
	case 0:
	case 1:
	case 2:
		m_sort_flag[phdn->iItem] = !m_sort_flag[phdn->iItem];
		n_sort_info.asc = m_sort_flag[phdn->iItem];
		n_sort_info.column = phdn->iItem;
		n_sort_info.ctrl = &m_list_tags;
		for( i = m_list_tags.GetItemCount()-1; i >= 0; i--)
		{
			m_list_tags.SetItemData(i, i);
		}
		m_list_tags.SortItems(MyCompareProc, (LPARAM)&n_sort_info);
		/*
		// Ã°ÅÝÅÅÐò
		for(i = m_list_tags.GetItemCount()-1; i >= 0; i-- )
		{
			int      l_temp_item = i;
			CString  l_temp_item_str = m_list_tags.GetItemText(i, phdn->iItem);
			for(j = i-1; j >= 0; j--)
			{
				if( true )
				{
					if(l_temp_item_str > m_list_tags.GetItemText(j, phdn->iItem))
					{
						l_temp_item_str = m_list_tags.GetItemText(j, phdn->iItem);
						l_temp_item = j;
					}
				}
				else
				{
					if(l_temp_item_str < m_list_tags.GetItemText(j, phdn->iItem))
					{
						l_temp_item_str = m_list_tags.GetItemText(j, phdn->iItem);
						l_temp_item = j;
					}
				}
			}
			if( i != j )
			{
			}
		}
		*/
		break;
	default:
		break;
	}
	*pResult = 0;
}

void PageTagInventory::OnDblclkListTags(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}


void PageTagInventory::OnConnect()
{
	m_btn_inventory.EnableWindow(TRUE);
	m_btn_clear.EnableWindow(TRUE);
}

void PageTagInventory::OnDisconnect()
{
	if(m_query_thread_syn_status >= 0)
	{
		OnBtnInventory();
	}
	m_btn_inventory.EnableWindow(FALSE);
	m_btn_clear.EnableWindow(FALSE);
}
