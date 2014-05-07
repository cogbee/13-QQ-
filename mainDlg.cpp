// mainDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "main.h"
#include "mainDlg.h"
#include "start.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CmainDlg 对话框




CmainDlg::CmainDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CmainDlg::IDD, pParent)
	, autostart1(FALSE)
	, autoplay1(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//	DDX_Text(pDX, IDC_EDIT1, m_chessdata);
	DDX_Check(pDX, IDC_CHECK1, autostart1);
	DDX_Check(pDX, IDC_CHECK2, autoplay1);
}

BEGIN_MESSAGE_MAP(CmainDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CmainDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CmainDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_CHECK1, &CmainDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CmainDlg::OnBnClickedCheck2)
END_MESSAGE_MAP()


// CmainDlg 消息处理程序

BOOL CmainDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CmainDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CmainDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CmainDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CmainDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	startGame();


}

void CmainDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}
/*
void CmainDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	HWND gameh=::FindWindow(NULL,gameCaption);
	//获取窗口进程ID
	DWORD processid;
	::GetWindowThreadProcessId(gameh,&processid);
	//打开指定进程
	HANDLE processH=::OpenProcess(PROCESS_CREATE_THREAD|PROCESS_VM_OPERATION|PROCESS_VM_WRITE|PROCESS_VM_READ,false,processid);
	 if (processH==NULL)
		::MessageBox(NULL,"","打开失败",MB_OK);
	//读指定进程 内存数据
    DWORD byread;
	LPCVOID pbase=(LPCVOID)0x00129FB4; //棋盘数据基址
	LPVOID  nbuffer=(LPVOID)&chessdata;    //存放棋盘数据
	::ReadProcessMemory(processH,pbase,nbuffer,11*19,&byread);
	///显示棋盘数据
	char buf[11];
	m_chessdata=""; //清空编辑
	 for (int y=0;y<=10;y++)
	 {
		 for (int x=0;x<=18;x++) //读一行
		 {
		  itoa(chessdata[y][x],buf,16); //转换成字串
		  m_chessdata+=buf;
		  m_chessdata+=" ";
		 }
       //换行
    m_chessdata+="\r\n";
	 }
	UpdateData(false); 
}
*/
void CmainDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	HWND gameh=::FindWindow(NULL,gameCaption);
	//获取窗口进程ID
	DWORD processid;
	::GetWindowThreadProcessId(gameh,&processid);
	//打开指定进程
	HANDLE processH=::OpenProcess(PROCESS_ALL_ACCESS,false,processid);
	//读指定进程 内存数据
    DWORD byread;
	LPCVOID pbase=(LPCVOID)0x00111688;
	LPVOID  nbuffer=(LPVOID)&place;
	::ReadProcessMemory(processH,pbase,nbuffer,1,&byread);
	UpdateData(false); //更新变量的值到 编辑框

}

void CmainDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	//int i;
	updatdChess();
	num = getcount();
	//num = count;
	UpdateData(false);
	
}

void CmainDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
//回调函数
void CALLBACK startProc(
  HWND hwnd, 
  UINT uMsg, 
  UINT idEvent, 
  DWORD dwTime 
)
{
	startGame();
}



const int playID = 111;
const int startID = 112;
void CmainDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码



}
void CALLBACK playProc(
  HWND hwnd, 
  UINT uMsg, 
  UINT idEvent, 
  DWORD dwTime 
)
{
	play();
}
void CmainDlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码


}

void CmainDlg::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if(autostart1)
		SetTimer(startID,3*1000,startProc);
	else
		KillTimer(startID);
}

void CmainDlg::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
		UpdateData(true);
	if(autoplay1)
		SetTimer(playID,100,playProc);
	else
		KillTimer(playID);
}
