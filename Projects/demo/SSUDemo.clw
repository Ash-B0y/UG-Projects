; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=PageTagAccessEx
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ssudemo.h"
LastPage=0

ClassCount=13
Class1=MsgBoxOk
Class2=MsgBoxOkCancel
Class3=PageConfig
Class4=PageTagAccess
Class5=PageTagInventory
Class6=CSSUDemoApp
Class7=CSSUDemoDlg

ResourceCount=13
Resource1=IDD_PAGE_INVENTORY
Resource2=IDD_PAGE_CONFIG
Resource3=IDD_PAGE_NODE_EXPLORE
Resource4=IDD_PAGE_ACCESS_EX
Resource5=IDD_PANE_NODE_TCPIP
Resource6=IDD_PANE_NODE_RS485
Resource7=IDD_DIALOG_MSG_OKCANCEL
Resource8=IDD_PAGE_NETADDR_TCPIP
Class8=PageNetAddrTCPIP
Resource9=IDD_SSUDEMO_DIALOG
Class9=PaneNodeTCPIP
Class10=PageNodeExplore
Resource10=IDD_DIALOG_MSG_OK
Class11=PageTagAccessEx
Resource11=IDD_PAGE_ACCESS
Class12=PaneNodeRS485
Resource12=IDD_PAGE_CONFIG_PRIV
Class13=PageNetAddrRS485
Resource13=IDD_PAGE_NETADDR_RS485

[CLS:MsgBoxOk]
Type=0
BaseClass=CDialog
HeaderFile=MsgBoxOk.h
ImplementationFile=MsgBoxOk.cpp

[CLS:MsgBoxOkCancel]
Type=0
BaseClass=CDialog
HeaderFile=MsgBoxOkCancel.h
ImplementationFile=MsgBoxOkCancel.cpp

[CLS:PageConfig]
Type=0
BaseClass=CDialog
HeaderFile=PageConfig.h
ImplementationFile=PageConfig.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_BTN_CONFIG_GET

[CLS:PageTagAccess]
Type=0
BaseClass=CDialog
HeaderFile=PageTagAccess.h
ImplementationFile=PageTagAccess.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_BTN_TAG_KILL

[CLS:PageTagInventory]
Type=0
BaseClass=CDialog
HeaderFile=PageTagInventory.h
ImplementationFile=PageTagInventory.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT_INTERVAL

[CLS:CSSUDemoApp]
Type=0
BaseClass=CWinApp
HeaderFile=SSUDemo.h
ImplementationFile=SSUDemo.cpp

[CLS:CSSUDemoDlg]
Type=0
BaseClass=CDialog
HeaderFile=SSUDemoDlg.h
ImplementationFile=SSUDemoDlg.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_STATIC_NODEADDR

[DLG:IDD_DIALOG_MSG_OK]
Type=1
Class=MsgBoxOk
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_EDIT_MSG,edit,1344342020

[DLG:IDD_DIALOG_MSG_OKCANCEL]
Type=1
Class=MsgBoxOkCancel
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT_MSG,edit,1344342020

[DLG:IDD_PAGE_CONFIG]
Type=1
Class=PageConfig
ControlCount=48
Control1=IDC_BTN_CONFIG_SET,button,1476460544
Control2=IDC_EDIT_CONN_PWD,edit,1350631584
Control3=IDC_STATIC,static,1342308354
Control4=IDC_BTN_CONFIG_GET,button,1476460544
Control5=IDC_STATIC,static,1342308354
Control6=IDC_STATIC,static,1342308354
Control7=IDC_STATIC,static,1342308354
Control8=IDC_STATIC,static,1342308354
Control9=IDC_STATIC,static,1342308354
Control10=IDC_STATIC,static,1342308354
Control11=IDC_STATIC,static,1342308354
Control12=IDC_STATIC,static,1342308354
Control13=IDC_STATIC,static,1342308354
Control14=IDC_STATIC,static,1342308354
Control15=IDC_STATIC,static,1342308354
Control16=IDC_STATIC,static,1342308354
Control17=IDC_COMBO_BEEP_ENABLE,combobox,1344339971
Control18=IDC_EDIT_RFCENTER,edit,1350639746
Control19=IDC_EDIT_RFDeviation,edit,1350639746
Control20=IDC_EDIT_RFSTEP,edit,1350639746
Control21=IDC_CHECK_ANT0,button,1342243331
Control22=IDC_CHECK_ANT1,button,1342243331
Control23=IDC_CHECK_ANT2,button,1342243331
Control24=IDC_CHECK_ANT3,button,1342243331
Control25=IDC_COMBO_IVNT_RSPTM,combobox,1344339970
Control26=IDC_COMBO_INVT_SESS,combobox,1344339971
Control27=IDC_COMBO_RF_GAIN,combobox,1344339971
Control28=IDC_COMBO_INVT_QMAX,combobox,1344339971
Control29=IDC_COMBO_INVT_QMIN,combobox,1344339971
Control30=IDC_COMBO_IVNT_BUFTM,combobox,1344339971
Control31=IDC_COMBO_INVT_QMINTRIES,combobox,1344339971
Control32=IDC_STATIC,static,1342177296
Control33=IDC_BTN_CONNPWD_SET,button,1476460544
Control34=IDC_STATIC,static,1342177296
Control35=IDC_STATIC,static,1342177296
Control36=IDC_TAB_NETADDR,SysTabControl32,1342177280
Control37=IDC_BTN_NETADDR_SET,button,1476460544
Control38=IDC_BTN_NETADDR_GET,button,1476460544
Control39=IDC_STATIC,static,1342308352
Control40=IDC_STATIC,static,1342308352
Control41=IDC_STATIC,static,1342308352
Control42=IDC_STATIC,static,1342308352
Control43=IDC_STATIC,static,1342308352
Control44=IDC_EDIT_INVT_IDLEMIN,edit,1350639746
Control45=IDC_EDIT_INVT_IDLEFRACT,edit,1350639746
Control46=IDC_STATIC,static,1342308354
Control47=IDC_STATIC,static,1342308354
Control48=IDC_STATIC,static,1342308352

[DLG:IDD_PAGE_ACCESS]
Type=1
Class=PageTagAccess
ControlCount=45
Control1=IDC_BTN_TAGQUERY,button,1476460544
Control2=IDC_BTN_TAG_READ,button,1476460544
Control3=IDC_BTN_TAG_WRITE,button,1476460544
Control4=IDC_EDIT_EPC,edit,1350633600
Control5=IDC_EDIT_START_READ,edit,1350639746
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT_WORDS_READ,edit,1350639746
Control8=IDC_STATIC,static,1342308352
Control9=IDC_EDIT_DATA_READ,edit,1352730628
Control10=IDC_STATIC,static,1342308352
Control11=IDC_EDIT_DATA_WRITE,edit,1350631552
Control12=IDC_BTN_TAG_LOCK,button,1476460544
Control13=IDC_STATIC,static,1342308352
Control14=IDC_COMBO_SECT_READ,combobox,1344339971
Control15=IDC_STATIC,static,1342308352
Control16=IDC_EDIT_START_WRITE,edit,1350639746
Control17=IDC_STATIC,static,1342308352
Control18=IDC_EDIT_WORDS_WRITE,edit,1350639746
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_COMBO_SECT_WRITE,combobox,1344339971
Control22=IDC_EDIT_PWD_WRITE,edit,1350631552
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_COMBO_SECT_LOCK,combobox,1344339971
Control26=IDC_STATIC,static,1342308352
Control27=IDC_COMBO_OPT_LOCK,combobox,1344339971
Control28=IDC_EDIT_PWD_LOCK,edit,1350631552
Control29=IDC_STATIC,static,1342308352
Control30=IDC_STATIC,static,1342177296
Control31=IDC_STATIC,static,1342177296
Control32=IDC_STATIC,static,1342177296
Control33=IDC_BTN_TAG_KILL,button,1476460544
Control34=IDC_EDIT_PWD_ACC,edit,1350631552
Control35=IDC_STATIC,static,1342308352
Control36=IDC_STATIC,static,1342177296
Control37=IDC_EDIT_PWD_KILL,edit,1350631552
Control38=IDC_STATIC,static,1342308352
Control39=IDC_EDIT_PWD_READ,edit,1350631552
Control40=IDC_STATIC,static,1342308352
Control41=IDC_CHECK_READ_ANY,button,1342242819
Control42=IDC_CHECK_WRITE_ANY,button,1342242819
Control43=IDC_CHECK_READ_CONTINUE,button,1342242819
Control44=IDC_CHECK_WRITE_CONTINUE,button,1342242819
Control45=IDC_EDIT_EMSG,edit,1342244993

[DLG:IDD_PAGE_INVENTORY]
Type=1
Class=PageTagInventory
ControlCount=7
Control1=IDC_BTN_INVENTORY,button,1476460544
Control2=IDC_LIST_TAGS,SysListView32,1350631425
Control3=IDC_CHECK_INVT_AUTO,button,1342242819
Control4=IDC_CHECK_INVT_REPORT,button,1476460547
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_TAGCOUNT,edit,1342253186
Control7=IDC_BTN_CLEAR,button,1476460544

[DLG:IDD_SSUDEMO_DIALOG]
Type=1
Class=CSSUDemoDlg
ControlCount=29
Control1=IDC_TAB_PAGES,SysTabControl32,1342177280
Control2=IDC_BTN_CONNECT,button,1342242816
Control3=IDC_GRP_COM,button,1342177287
Control4=IDC_STATIC_COMPORT,static,1342308352
Control5=IDC_STATIC_NODEADDR,static,1073872896
Control6=IDC_EDIT_NODEADDR,edit,1216422016
Control7=IDC_EDIT_COMPORT,edit,1350631552
Control8=IDC_GRP_TCPIP,button,1342177287
Control9=IDC_STATIC_IP,static,1342308352
Control10=IDC_STATIC_PORT,static,1342308352
Control11=IDC_EDIT_PORT,edit,1216422016
Control12=IDC_EDIT_IP,edit,1350631552
Control13=IDC_BTN_DISCONNECT,button,1476460544
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_EDIT_PASSWORD,edit,1350631584
Control17=IDC_EDIT_CUSTOMNO,edit,1350639746
Control18=IDC_RADIO_COM,button,1342177289
Control19=IDC_RADIO_RS485,button,1342177289
Control20=IDC_RADIO_CAN,button,1476395017
Control21=IDC_RADIO_TCP,button,1342177289
Control22=IDC_RADIO_UDP,button,1342177289
Control23=IDC_STATIC,static,1342308353
Control24=IDC_STATIC,static,1342308353
Control25=IDC_STATIC,static,1342308353
Control26=IDC_EDIT_VERSION,edit,1342244864
Control27=IDC_EDIT_MODEL,edit,1342244864
Control28=IDC_EDIT_DEVSN,edit,1342244864
Control29=IDC_CHECK_NOCRC,button,1342242851

[DLG:IDD_PAGE_CONFIG_PRIV]
Type=1
Class=?
ControlCount=35
Control1=IDC_BTN_TIMING_SET,button,1476460544
Control2=IDC_EDIT_CONN_PWD,edit,1350631552
Control3=IDC_STATIC,static,1342308354
Control4=IDC_BTN_PRIVCONF_GET,button,1476460544
Control5=IDC_STATIC,static,1342308354
Control6=IDC_STATIC,static,1342308354
Control7=IDC_STATIC,static,1342308354
Control8=IDC_STATIC,static,1342308354
Control9=IDC_STATIC,static,1342308354
Control10=IDC_STATIC,static,1342308354
Control11=IDC_STATIC,static,1342308354
Control12=IDC_STATIC,static,1342308354
Control13=IDC_STATIC,static,1342308354
Control14=IDC_STATIC,static,1342308354
Control15=IDC_STATIC,static,1342308354
Control16=IDC_STATIC,static,1342308354
Control17=IDC_COMBO_BEEP_ENABLE,combobox,1344340226
Control18=IDC_EDIT_RFCENTER,edit,1350631552
Control19=IDC_EDIT_RFDeviation,edit,1350631552
Control20=IDC_EDIT_RFSTEP,edit,1350631552
Control21=IDC_EDIT_RFGAIN,edit,1350631552
Control22=IDC_EDIT_INVT_BUFTM,edit,1350631552
Control23=IDC_CHECK_ANT0,button,1342242819
Control24=IDC_CHECK_ANT1,button,1342242819
Control25=IDC_CHECK_ANT2,button,1342242819
Control26=IDC_CHECK_ANT3,button,1342242819
Control27=IDC_COMBO_IVNT_AUTO,combobox,1344340226
Control28=IDC_COMBO_INVT_SESS,combobox,1344340226
Control29=IDC_EDIT_INVT_QMAX,edit,1350631552
Control30=IDC_EDIT_INVT_QMIN,edit,1350631552
Control31=IDC_EDIT_INVT_QMINTRIES,edit,1350631552
Control32=IDC_STATIC,static,1342177296
Control33=IDC_STATIC,static,1342308354
Control34=IDC_STATIC,static,1342308354
Control35=IDC_STATIC,static,1342308354

[DLG:IDD_PAGE_NETADDR_TCPIP]
Type=1
Class=PageNetAddrTCPIP
ControlCount=6
Control1=IDC_EDIT_READER_IP,SysIPAddress32,1342242816
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT_READER_MASK,SysIPAddress32,1342242816
Control6=IDC_EDIT_READER_GATEWAY,SysIPAddress32,1342242816

[CLS:PageNetAddrTCPIP]
Type=0
HeaderFile=PageNetAddrTCPIP.h
ImplementationFile=PageNetAddrTCPIP.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT_READER_IP
VirtualFilter=dWC

[DLG:IDD_PAGE_NODE_EXPLORE]
Type=1
Class=PageNodeExplore
ControlCount=1
Control1=IDC_TAB_PANES,SysTabControl32,1342177280

[DLG:IDD_PANE_NODE_TCPIP]
Type=1
Class=PaneNodeTCPIP
ControlCount=15
Control1=IDC_BTN_NODE_EXPLORE,button,1342242816
Control2=IDC_LIST_NODES,SysListView32,1350631437
Control3=IDC_EDIT_NETIP,SysIPAddress32,1342242816
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT_NETMASK,SysIPAddress32,1342242816
Control8=IDC_EDIT_GATEWAY,SysIPAddress32,1342242816
Control9=IDC_BTN_NODE_SET,button,1342242816
Control10=IDC_STATIC,button,1342177287
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STATIC,static,1342308352
Control13=IDC_EDIT_DEVSN,edit,1350633600
Control14=IDC_STATIC,static,1342308352
Control15=IDC_EDIT_PASSWORD,edit,1350631584

[CLS:PaneNodeTCPIP]
Type=0
HeaderFile=PaneNodeTCPIP.h
ImplementationFile=PaneNodeTCPIP.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT_PASSWORD
VirtualFilter=dWC

[CLS:PageNodeExplore]
Type=0
HeaderFile=PageNodeExplore.h
ImplementationFile=PageNodeExplore.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_TAB_PANES
VirtualFilter=dWC

[DLG:IDD_PAGE_ACCESS_EX]
Type=1
Class=PageTagAccessEx
ControlCount=40
Control1=IDC_BTN_TAGQUERY,button,1476460544
Control2=IDC_BTN_TAG_READ_TID,button,1476460544
Control3=IDC_BTN_TAG_WRITE_USR,button,1476460544
Control4=IDC_EDIT_EPC,edit,1350631552
Control5=IDC_EDIT_START_READ_TID,edit,1350639746
Control6=65535,static,1342308352
Control7=IDC_EDIT_WORDS_READ_TID,edit,1350639746
Control8=65535,static,1342308352
Control9=IDC_EDIT_DATA_READ_TID,edit,1350633472
Control10=65535,static,1342308352
Control11=IDC_BTN_TAG_LOCK_USR,button,1476460544
Control12=IDC_BTN_TAG_KILL_EX,button,1476460544
Control13=IDC_EDIT_KILL_PWD,edit,1350631552
Control14=IDC_EDIT_EMSG,edit,1342244993
Control15=IDC_BTN_TAG_READ_USR,button,1476460544
Control16=IDC_EDIT_START_READ_USR,edit,1350639746
Control17=65535,static,1342308352
Control18=IDC_EDIT_WORDS_READ_USR,edit,1350639746
Control19=65535,static,1342308352
Control20=IDC_EDIT_DATA_READ_USR,edit,1352730628
Control21=65535,static,1342308352
Control22=65535,button,1342177287
Control23=65535,button,1342177287
Control24=IDC_EDIT_ACCPWD,edit,1350631552
Control25=65535,static,1342308354
Control26=IDC_BTN_TAG_WRITE_EPC,button,1476460544
Control27=IDC_BTN_TAG_WRITE_PWD,button,1476460544
Control28=IDC_EDIT_START_WRITE_USR,edit,1350639746
Control29=65535,static,1342308352
Control30=IDC_EDIT_WORDS_WRITE_USR,edit,1350639746
Control31=65535,static,1342308352
Control32=IDC_EDIT_DATA_WRITE_USR,edit,1352728580
Control33=65535,static,1342308352
Control34=IDC_EDIT_WRITE_PWD_ACCESS,edit,1350631552
Control35=IDC_EDIT_WRITE_EPC,edit,1350631552
Control36=IDC_BTN_TAG_LOCK_EPC,button,1476460544
Control37=IDC_EDIT_WRITE_PWD_KILL,edit,1350631552
Control38=IDC_CHECK_ACCPWD,button,1342243107
Control39=IDC_CHECK_KILPWD,button,1342243107
Control40=65535,static,1342308352

[CLS:PageTagAccessEx]
Type=0
HeaderFile=PageTagAccessEx.h
ImplementationFile=PageTagAccessEx.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT_WRITE_PWD_KILL
VirtualFilter=dWC

[DLG:IDD_PANE_NODE_RS485]
Type=1
Class=PaneNodeRS485
ControlCount=13
Control1=IDC_BTN_NODE_EXPLORE,button,1342242816
Control2=IDC_LIST_NODES,SysListView32,1350631437
Control3=IDC_STATIC,static,1342308352
Control4=IDC_BTN_NODE_SET,button,1342242816
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_DEVSN,edit,1350633600
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT_PASSWORD,edit,1350631584
Control11=IDC_EDIT_NETADDR,edit,1350631552
Control12=IDC_EDIT_COMPORT,edit,1350631552
Control13=IDC_STATIC,static,1342308352

[CLS:PaneNodeRS485]
Type=0
HeaderFile=PaneNodeRS485.h
ImplementationFile=PaneNodeRS485.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_BTN_NODE_EXPLORE
VirtualFilter=dWC

[DLG:IDD_PAGE_NETADDR_RS485]
Type=1
Class=PageNetAddrRS485
ControlCount=2
Control1=65535,static,1342308352
Control2=IDC_EDIT_NODE_SN,edit,1350631552

[CLS:PageNetAddrRS485]
Type=0
HeaderFile=PageNetAddrRS485.h
ImplementationFile=PageNetAddrRS485.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=65535

