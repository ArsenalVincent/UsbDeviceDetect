// usbDetectDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "usbDetect.h"
#include "usbDetectDlg.h"
#include<setupapi.h>
#pragma comment(lib,"setupapi.lib")
#include<usbiodef.h>
#include<usbioctl.h>
#include<dbt.h>
extern "C"
{
	#include<hidsdi.h>
}
#pragma comment(lib,"hid.lib")
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


// CusbDetectDlg 对话框




CusbDetectDlg::CusbDetectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CusbDetectDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CusbDetectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CusbDetectDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CusbDetectDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CusbDetectDlg 消息处理程序

BOOL CusbDetectDlg::OnInitDialog()
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

void CusbDetectDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CusbDetectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
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

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CusbDetectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CusbDetectDlg::FindUsbDevice()
{
	HDEVINFO hDev = SetupDiGetClassDevsW(NULL,NULL,NULL,DIGCF_ALLCLASSES | DIGCF_PRESENT);

	if (INVALID_HANDLE_VALUE == hDev)
	{
		AfxMessageBox(_T("获取系统设备列表失败"));
		return;
	}

	SP_DEVINFO_DATA sDevInfoData;
	sDevInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

	TCHAR szDIS[MAX_PATH];
	DWORD nSize = 0;
	for(int i = 0; SetupDiEnumDeviceInfo(hDev,i,&sDevInfoData); i++)
	{
		nSize = 0;
		if(!SetupDiGetDeviceInstanceId(hDev,&sDevInfoData,szDIS,sizeof(szDIS),&nSize))
		{
			AfxMessageBox(_T("获取设备识别字符串失败"));
			break;
		}
		CString strDIS(szDIS);
		strDIS.MakeUpper();
		if( strDIS.Left(3) ==_T("USB"))
		{
			int pos = strDIS.ReverseFind('\\');
			CString DeviceSer = strDIS.Right(strDIS.GetLength()-pos-1);
			AfxMessageBox(strDIS);
		}

	}
	
	SetupDiDestroyDeviceInfoList(hDev);
}

void CusbDetectDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	FindUsbDevice();
}
