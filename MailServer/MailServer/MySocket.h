#pragma once
#include <string>
#include <atlimage.h>
#include <vector>
// MySocket 命令目标



class MySocket : public CAsyncSocket
{
public:
	MySocket();
	virtual ~MySocket();
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);


	 
    UINT m_nLength;			// 消息长度 
	char m_szBuffer[524288];//消息内容
	int m_count;			// 用于计数,同步Send()和Receive()，表示当前执行到第几歩
	bool  m_state;			//标记状态，false：表示由Send打开，true标记由Receive()打开
	CString Text_DecodeBase64(CString inpt,int * len);	//base64解码函数
	void ShowData();		//显示邮件正文
	CString m_content_string;
	CImage m_image;
	void ShowImage(void);
	CString m_filename;			//附件名称
	void MySocket::Image_DecodeBase64(CString dataFromPicStart, std::vector<char>& bytes);
};

