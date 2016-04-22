// ComMonitor2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "ComMonitor2.h"
#include "ComMonitor2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComMonitor2Dlg dialog

CComMonitor2Dlg::CComMonitor2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CComMonitor2Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CComMonitor2Dlg)
	m_BaudRate = _T("9600");
	m_ByteSize = _T("8");
	m_Parity = _T("N");
	m_Port = _T("COM1");
	m_Stopbits = _T("1");
	m_RxString = _T("");
	m_TxString = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CComMonitor2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CComMonitor2Dlg)
	DDX_Control(pDX, IDC_BUTTON_Open, m_BtnOpen);
	DDX_Control(pDX, IDC_MSCOMM1, m_Comm1);
	DDX_CBString(pDX, IDC_COMBO_BaudRate, m_BaudRate);
	DDX_CBString(pDX, IDC_COMBO_ByteSize, m_ByteSize);
	DDX_CBString(pDX, IDC_COMBO_Parity, m_Parity);
	DDX_CBString(pDX, IDC_COMBO_Port, m_Port);
	DDX_CBString(pDX, IDC_COMBO_Stopbits, m_Stopbits);
	DDX_Text(pDX, IDC_EDIT_Rx, m_RxString);
	DDX_Text(pDX, IDC_EDIT_Tx, m_TxString);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CComMonitor2Dlg, CDialog)
	//{{AFX_MSG_MAP(CComMonitor2Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Open, OnBtnOpen)
	ON_BN_CLICKED(IDC_BUTTON_Send, OnBtnSend)
	ON_CBN_DROPDOWN(IDC_COMBO_Port, OnDropdownCOMBOPort)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComMonitor2Dlg message handlers

BOOL CComMonitor2Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CComMonitor2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CComMonitor2Dlg::OnPaint() 
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
HCURSOR CComMonitor2Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BEGIN_EVENTSINK_MAP(CComMonitor2Dlg, CDialog)
    //{{AFX_EVENTSINK_MAP(CComMonitor2Dlg)
	ON_EVENT(CComMonitor2Dlg, IDC_MSCOMM1, 1 /* OnComm */, OnOnCommMscomm, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CComMonitor2Dlg::FindCommPort()
{
    HKEY hKey;
    int rtn;
    //m_cmbComm.ResetContent();
	CComboBox *box = (CComboBox *)GetDlgItem(IDC_COMBO_Port);
	box->ResetContent();
    rtn = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Hardware\\DeviceMap\\SerialComm", NULL, KEY_READ, &hKey);  //   �򿪴���ע��� 
    if( rtn == ERROR_SUCCESS) {
        int   i=0;
        char   portName[256],commName[256];
        DWORD   dwLong,dwSize;
        while(1) {
            dwSize = sizeof(portName);
            dwLong = dwSize;
            rtn = RegEnumValue( hKey, i, portName, &dwLong, NULL, NULL, (PUCHAR)commName, &dwSize );
            if( rtn == ERROR_NO_MORE_ITEMS )   //   ö�ٴ���
                break;
            i++;
			//TRACE(commName);TRACE("\n");
			//m_Port.ResetContent();
			box->AddString(commName);
        }
        RegCloseKey(hKey); 
    }   
}

void CComMonitor2Dlg::OnBtnOpen() 
{
	// TODO: Add your control notification handler code here
	if(m_Comm1.GetPortOpen()) {
		m_Comm1.SetPortOpen(FALSE);
	}
	UpdateData(TRUE);
	short port = 0;
	CString conf = m_BaudRate + "," + m_Parity + "," + m_ByteSize + "," + m_Stopbits;
	sscanf(m_Port, "COM%d", &port);
	TRACE("conf %s m_Port %s port %d\n", conf, m_Port, port);
	m_Comm1.SetCommPort(port);            //ѡ��com1���ɸ��ݾ����������
	m_Comm1.SetInBufferSize(1024);     //�������뻺�����Ĵ�С��Bytes
	m_Comm1.SetOutBufferSize(1024);    //�������뻺�����Ĵ�С��Bytes//
	m_Comm1.SetSettings(conf); //������9600����У�飬8������λ��1��ֹͣλ
	m_Comm1.SetInputMode(1);           //1����ʾ�Զ����Ʒ�ʽ��ȡ����
	m_Comm1.SetRThreshold(1); 
	//����1��ʾÿ�����ڽ��ջ��������ж��ڻ����1���ַ�ʱ������һ���������ݵ�OnComm�¼�
	m_Comm1.SetInputLen(0);            //���õ�ǰ���������ݳ���Ϊ0
	if(!m_Comm1.GetPortOpen()) {
		m_Comm1.SetPortOpen(TRUE);     //�򿪴���
	}
	else {
		AfxMessageBox("cannot open serial port");
	}
	m_Comm1.GetInput();                //��Ԥ���������������������
	//UpdateData(false);
}

void CComMonitor2Dlg::OnOnCommMscomm() 
{
	// TODO: Add your control notification handler code here
    COleSafeArray safearray_inp;
    LONG len,k;
    BYTE rxdata[2048]; //����BYTE���� An 8-bit integerthat is not signed.
	BYTE *data;
    CString strtemp;
    if(m_Comm1.GetCommEvent()==2) { //�¼�ֵΪ2��ʾ���ջ����������ַ�   
		//��������Ը����Լ���ͨ��Э����봦�����
        safearray_inp = m_Comm1.GetInput();    //��������
        len = safearray_inp.GetOneDimSize(); //�õ���Ч���ݳ���
        //for(k=0;k<len;k++) {
        //    safearray_inp.GetElement(&k,rxdata+k);//ת��ΪBYTE������
		//}
		safearray_inp.AccessData((void **)&data);
		memcpy(rxdata, data, len);
		safearray_inp.UnaccessData();
		GetDlgItemInt(IDC_EDIT_Rx);
		m_RxString += CString((LPCSTR)data, len);
        //for(k=0;k<len;k++) {                 //������ת��ΪCstring�ͱ���
        //    BYTE bt=*(char*)(rxdata+k);      //�ַ���
        //    strtemp.Format("%c",bt);         //���ַ�������ʱ����strtemp���
        //    m_RxString+=strtemp;             //������ձ༭���Ӧ�ַ��� 
        //}
    }
    //UpdateData(FALSE); //���±༭������
	//��ʹ��UpdateData(FALSE);��ԭ���Ǹú�����ˢ�������Ի�������ݣ���SetDlgItemText()ֻ���½��ձ༭������ݡ�
	SetDlgItemText(IDC_EDIT_Rx, m_RxString);
}

void CComMonitor2Dlg::OnBtnSend() 
{
	// TODO: Add your control notification handler code here
	// UpdateData(TRUE); //��ȡ�༭������
	GetDlgItemInt(IDC_EDIT_Tx);
	m_Comm1.SetOutput(COleVariant(m_TxString));//��������
}

void CComMonitor2Dlg::OnDropdownCOMBOPort() 
{
	// TODO: Add your control notification handler code here
	FindCommPort();
}
