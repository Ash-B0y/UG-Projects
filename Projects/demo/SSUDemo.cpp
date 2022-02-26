// SSUDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "SSUDemo.h"
#include "SSUDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSSUDemoApp

BEGIN_MESSAGE_MAP(CSSUDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CSSUDemoApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSSUDemoApp construction

CSSUDemoApp::CSSUDemoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSSUDemoApp object

CSSUDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSSUDemoApp initialization

unsigned char buf_test[1024];

static
unsigned short crc16( unsigned char* data, int len, unsigned short crcBase)
{//∞¥Œªº∆À„
  int i,j;
  unsigned char  n_tmp;
  //unsigned short n_crc = 0xffff;
  for( i = 0; i < len; i++)
  {  
     n_tmp = *data++;
    for (j = 0;j < 8;j++)
    {
      if((crcBase & 0x8000) ^ ((n_tmp & 0x80) << 8))
        crcBase = ( (crcBase << 1) & 0xffff) ^ 0x1021;
      else
        crcBase = (crcBase << 1) & 0xffff;
      n_tmp <<= 1;
    }		
  }
  return crcBase;
}

BOOL CSSUDemoApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	//unsigned int crc = crc16(buf_test, n_rcv_cursor, 0xffff);


	SSUSetup();


	CSSUDemoDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	SSUShutup();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

/////////////////
int btoh(unsigned char* b, int size, CString& str)
{
	char n_temp_str[1024];
	for( int i = 0; i < size; i++ )
	{
		::sprintf(&n_temp_str[i*2], "%02X", b[i]);
	}
	n_temp_str[i*2] = 0;
	str = n_temp_str;
	return str.GetLength();
}
int htob(const char* hstr, int len, unsigned char* b, int size)
{
	for( int i = 0; i < len/2 && i < size; i++ )
	{
		unsigned char r = HEX(hstr[i*2]);
		unsigned char l = HEX(hstr[i*2+1]);
		if( r != 0xFF && l != 0xFF )
		{
			b[i] = ((r << 4) | l);
		}
		else
		{
			return -1;
		}
	}
	return i;
}
