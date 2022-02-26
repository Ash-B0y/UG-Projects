#if !defined(AFX_PAGETAGINVENTORY_H__B37BC0EA_C2F1_451F_8E8D_D8475CB3D058__INCLUDED_)
#define AFX_PAGETAGINVENTORY_H__B37BC0EA_C2F1_451F_8E8D_D8475CB3D058__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageTagInventory.h : header file
//

class CSSUDemoDlg;
/////////////////////////////////////////////////////////////////////////////
// PageTagInventory dialog

class PageTagInventoryThread : public CWinThread
{
public:
	PageTagInventoryThread(CSSUDemoDlg* wnd)
	{
		m_main_wnd = wnd;
	};
	virtual ~PageTagInventoryThread(){};
protected:
	CSSUDemoDlg*  m_main_wnd;

public:
	virtual BOOL InitInstance();
//	virtual int Run();
};

class PageTagInventory : public CDialog
{
// Construction
public:
	PageTagInventory(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(PageTagInventory)
	enum { IDD = IDD_PAGE_INVENTORY };
	CButton	m_btn_clear;
	CButton	m_check_report;
	CButton	m_check_auto;
	CEdit	m_edit_tagcount;
	CListCtrl	m_list_tags;
	CButton	m_btn_inventory;
	//}}AFX_DATA

	CMutex                       m_data_lock;
	CArray<CString, CString&>    m_data_tagid;
	CArray<CString, CString&>    m_data_tagtime;
	CArray<CString, CString&>    m_data_tagstate;

	PageTagInventoryThread*      m_query_thread;
	volatile int                 m_query_thread_syn_status; // -1 未启动, 0 正在运行, 1 停止信号，2 已经停止

	bool                         m_sort_flag[5]; // 排序升降标识，true为升序，list ctrl每列一个。


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PageTagInventory)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	void DoRecvQueryData();

public:	
	void OnConnect();
	void OnDisconnect();
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(PageTagInventory)
	afx_msg void OnBtnInventory();
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckInvtAuto();
	afx_msg void OnBtnClear();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();
	afx_msg void OnItemclickListTags(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListTags(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGETAGINVENTORY_H__B37BC0EA_C2F1_451F_8E8D_D8475CB3D058__INCLUDED_)
