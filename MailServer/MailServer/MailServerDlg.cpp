
// MailServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MailServer.h"
#include "MailServerDlg.h"
#include "afxdialogex.h"
#include "ListenSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMailServerDlg 对话框



CMailServerDlg::CMailServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMailServerDlg::IDD, pParent)
	, m_filename(_T("暂无附件"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMailServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, mc_server);
	DDX_Control(pDX, IDC_LIST2, mc_mail);
	DDX_Control(pDX, IDC_LIST3, mc_text);
	DDX_Control(pDX, IDC_PICTURE, mc_picture);
	DDX_Text(pDX, IDC_EDIT1, m_filename);
}

BEGIN_MESSAGE_MAP(CMailServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_LBN_SELCHANGE(IDC_LIST2, &CMailServerDlg::OnLbnSelchangeList2)
END_MESSAGE_MAP()


// CMailServerDlg 消息处理程序

BOOL CMailServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码
	mc_server.SetHorizontalExtent(1000);
	mc_mail.SetHorizontalExtent(1000);
	mc_text.SetHorizontalExtent(1000);

	if(m_srvrSocket.m_hSocket ==INVALID_SOCKET){

		//创建监听套接字,激发FD_ACCEPT事件,在TCP的25端口守候,
		BOOL bFlag =m_srvrSocket.Create(25,SOCK_STREAM,FD_ACCEPT);
		if(!bFlag)  
        {  
			MessageBox(_T("Socket创建失败!"),L"提醒",MB_OK|MB_ICONSTOP);
            m_srvrSocket.Close();   
            return TRUE;  
        }  
        
		mc_server.AddString(_T("***SMTP服务器准备好"));
		mc_server.AddString(_T("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"));

		//监听成功,等待连接请求  
		if(!m_srvrSocket.Listen())//如果监听失败 
		{
			int nErrorCode =m_srvrSocket.GetLastError();    //检测错误信息
			if(nErrorCode !=WSAEWOULDBLOCK)             //如果不是线程阻塞
			{  
				MessageBox(_T("Socket错误!"),L"提醒",MB_OK|MB_ICONSTOP);
                m_srvrSocket.Close();  
                return TRUE;  
            }  
		}
	}


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMailServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMailServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}    

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMailServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMailServerDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//关闭套接字
	m_srvrSocket.Close();

	CDialogEx::OnClose();
}


void CMailServerDlg::OnLbnSelchangeList2()
{
	// TODO: 在此添加控件通知处理程序代码
}
