
// MailServerDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "ListenSocket.h"

// CMailServerDlg 对话框
class CMailServerDlg : public CDialogEx
{
// 构造
public:
	CMailServerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MAILSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox mc_server;
	CListBox mc_mail;
	ListenSocket m_srvrSocket; //监听套接字  
	afx_msg void OnClose();
	CListBox mc_text;
	afx_msg void OnLbnSelchangeList2();
	CStatic mc_picture;
	CString m_filename;
};
