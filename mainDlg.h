// mainDlg.h : 头文件
//

#pragma once


// CmainDlg 对话框
class CmainDlg : public CDialog
{
// 构造
public:
	CmainDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MAIN_DIALOG };

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
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	CString m_chessdata;
	afx_msg void OnBnClickedButton2();
	BYTE place;
	afx_msg void OnBnClickedButton3();
	int num;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnEnChangeEdit2();
	bool autostart;
	bool autoplay;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	BOOL autostart1;
	BOOL autoplay1;
};
