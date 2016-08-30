// ListenSocket.cpp : 实现文件
//

#include "stdafx.h"
#include "MailServer.h"
#include "ListenSocket.h"
#include "MySocket.h"
#include "MailServerDlg.h"

// ListenSocket

ListenSocket::ListenSocket()
{
}

ListenSocket::~ListenSocket()
{
}


// ListenSocket 成员函数


void ListenSocket::OnAccept(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	CMailServerDlg* dlg = (CMailServerDlg*)theApp.m_pMainWnd; //获取对话框句柄

	dlg->mc_server.AddString(_T("***收到连接请求"));
	dlg->mc_server.AddString(_T("***建立连接"));
	
	
	MySocket *pSocket =new MySocket();  

	if(Accept(*pSocket)){
		pSocket->AsyncSelect(FD_WRITE); //触发OnSend函数
	}

	CAsyncSocket::OnAccept(nErrorCode);
}
