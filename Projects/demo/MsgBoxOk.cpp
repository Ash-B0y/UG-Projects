// MsgBoxOk.cpp : implementation file
//

#include "stdafx.h"
#include "SSUDemo.h"
#include "MsgBoxOk.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MsgBoxOk dialog


MsgBoxOk::MsgBoxOk(CWnd* pParent /*=NULL*/)
	: CDialog(MsgBoxOk::IDD, pParent)
{
	//{{AFX_DATA_INIT(MsgBoxOk)
	m_msg = _T("");
	//}}AFX_DATA_INIT
}


void MsgBoxOk::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MsgBoxOk)
	DDX_Text(pDX, IDC_EDIT_MSG, m_msg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MsgBoxOk, CDialog)
	//{{AFX_MSG_MAP(MsgBoxOk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MsgBoxOk message handlers

BOOL MsgBoxOk::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetWindowText(m_title);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
