
// DbServerModuleDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "TCPServer.h"
#include "XmlParser.h"

// CDbServerModuleDlg 对话框
class CDbServerModuleDlg : public CDialogEx
{
// 构造
public:
	CDbServerModuleDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DBSERVERMODULE_DIALOG };

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
	CEdit m_edState;
	afx_msg void OnEnChangeEdState();
	afx_msg void OnBnClickedBtnStart();

	CTCPServer m_TcpWorkServer;
	afx_msg void OnBnClickedBtnReadfile();

	CXmlParser m_xmlParser;

};
