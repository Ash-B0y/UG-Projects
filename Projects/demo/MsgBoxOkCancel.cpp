// MsgBoxOkCancel.cpp : implementation file
//

#include "stdafx.h"
#include "SSUDemo.h"
#include "MsgBoxOkCancel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MsgBoxOkCancel dialog


MsgBoxOkCancel::MsgBoxOkCancel(CWnd* pParent /*=NULL*/)
	: CDialog(MsgBoxOkCancel::IDD, pParent)
{
	//{{AFX_DATA_INIT(MsgBoxOkCancel)
	m_msg = _T("");
	//}}AFX_DATA_INIT
}


void MsgBoxOkCancel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MsgBoxOkCancel)
	DDX_Text(pDX, IDC_EDIT_MSG, m_msg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MsgBoxOkCancel, CDialog)
	//{{AFX_MSG_MAP(MsgBoxOkCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MsgBoxOkCancel message handlers



BOOL MsgBoxOkCancel::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetWindowText(m_title);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
