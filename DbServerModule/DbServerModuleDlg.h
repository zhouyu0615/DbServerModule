
// DbServerModuleDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "TCPServer.h"

// CDbServerModuleDlg �Ի���
class CDbServerModuleDlg : public CDialogEx
{
// ����
public:
	CDbServerModuleDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DBSERVERMODULE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
};
