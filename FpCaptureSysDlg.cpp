
// FpCaptureSysDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "FpCaptureSys.h"
#include "FpCaptureSysDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <numeric>
#include "png.h"
#include <io.h>
#include <direct.h>
#include <Eigen/Core>
#include <Eigen/Geometry>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 一些宏定义
using namespace std;
//#define Language_EN
#define  IMAGE_PRE_WIDTH   800
#define  IMAGE_PRE_HEIGHT  750
#define  IMAGE_PRE_SIZE    IMAGE_PRE_WIDTH*IMAGE_PRE_HEIGHT
#define  IMAGE_RESULT_WIDTH   1600
#define  IMAGE_RESULT_HEIGHT  1500
#define  IMAGE_RESULT_SIZE  IMAGE_RESULT_HEIGHT*IMAGE_RESULT_WIDTH

vector<int> CapFreq = {1, 10, 20, 50, 100};
const double ARC_TO_DEG = 57.29577951308238;
const double DEG_TO_ARC = 0.0174532925199433;

BOOL g_AutoCapture = FALSE;
BOOL g_bisRoll = FALSE;
BOOL Setmodeindexfirst = FALSE; //setmode flag
int g_iQuality = 0;
const UINT SLEEP_TIME_INTERVAL = 5;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFpCaptureSysDlg 对话框



CFpCaptureSysDlg::CFpCaptureSysDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FPCAPTURESYS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFpCaptureSysDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFpCaptureSysDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_INIT, &CFpCaptureSysDlg::OnBnClickedButtonInit)
	ON_BN_CLICKED(IDC_BUTTON_START, &CFpCaptureSysDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CFpCaptureSysDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CFpCaptureSysDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CFpCaptureSysDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_DEINIT, &CFpCaptureSysDlg::OnBnClickedButtonDeinit)
	ON_CBN_SELCHANGE(IDC_COMBO_RATE_GYRO, &CFpCaptureSysDlg::OnCbnSelchangeComboRateGyro)
	ON_CBN_SELCHANGE(IDC_COMBO_DEV_GYRO, &CFpCaptureSysDlg::OnCbnSelchangeComboDevGyro)
	ON_CBN_SELCHANGE(IDC_COMBO_FREQ, &CFpCaptureSysDlg::OnCbnSelchangeComboFreq)
	ON_BN_CLICKED(IDC_BUTTON_RELEASE, &CFpCaptureSysDlg::OnBnClickedButtonRelease)
	ON_CBN_SELCHANGE(IDC_COMBO_DEV_GYRO2, &CFpCaptureSysDlg::OnCbnSelchangeComboDevGyro2)
	ON_BN_CLICKED(IDC_BUTTON_ALIGN, &CFpCaptureSysDlg::OnBnClickedButtonAlign)
END_MESSAGE_MAP()


// CFpCaptureSysDlg 消息处理程序

BOOL CFpCaptureSysDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	Initparam();

	bool is_ready = RefreshDevList();

	// can be edit
	GetDlgItem(IDC_COMBO_DEV_IMAGE)->EnableWindow(is_ready);
	GetDlgItem(IDC_COMBO_DEV_GYRO)->EnableWindow(is_ready);
	GetDlgItem(IDC_COMBO_DEV_GYRO2)->EnableWindow(is_ready);
	GetDlgItem(IDC_COMBO_RATE_GYRO)->EnableWindow(is_ready);
	GetDlgItem(IDC_BUTTON_INIT)->EnableWindow(is_ready);

	// not ready
	GetDlgItem(IDC_BUTTON_DEINIT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ALIGN)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_FOG)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_FREQ)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_DETTHRESH)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_RELEASE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(FALSE);

	((CComboBox*)GetDlgItem(IDC_COMBO_FREQ))->ResetContent();
	for (int i = 0; i < CapFreq.size(); i++) {
		((CComboBox*)GetDlgItem(IDC_COMBO_FREQ))->AddString(FormatString(CapFreq[i]));
	}
	((CComboBox*)GetDlgItem(IDC_COMBO_FREQ))->SetCurSel(3);
	cap_freq = CapFreq[3];

	GetDlgItem(IDC_EDIT_DETTHRESH)->SetWindowTextA(FormatString(det_thresh));

	return is_ready;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

CString CFpCaptureSysDlg::FormatString(int num) {
	CString str;
	str.Format("%d", num);
	return str;
}

CString CFpCaptureSysDlg::FormatString(float num) {
	CString str;
	str.Format("%.4f", num);
	return str;
}

CString CFpCaptureSysDlg::FormatString(double num) {
	CString str;
	str.Format("%.4f", num);
	return str;
}

bool CFpCaptureSysDlg::RefreshDevList()
{
	// check fingerprint scanner list
	int nRc;
	DTFMScannerExist sScannerList;
	nRc = M_Main_GetConnectedScanner(&sScannerList);
	if (nRc != STATUS_OK) {
		MessageBox("没找到指纹图像采集设备", "提示");
		return FALSE;
	}

	// check gyro list (comm port)
	HKEY hkey;
	int nCount = 0;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("Hardware\\DeviceMap\\SerialComm"), NULL, KEY_READ, &hkey) == ERROR_SUCCESS) {
		while (true) {
			char portName[_MAX_PATH], commName[_MAX_PATH];
			DWORD nValueSize = _MAX_PATH;
			DWORD nDataSize = _MAX_PATH;
			DWORD nType;

			if (::RegEnumValue(hkey, nCount, portName, &nValueSize, NULL, &nType, (LPBYTE)commName, &nDataSize) == ERROR_NO_MORE_ITEMS) {
				break;
			}

			sz_comm.m_PortNameList.push_back(commName);
			sz_comm2.m_PortNameList.push_back(commName);
			nCount++;
		}
	} else {
		MessageBox("没找到陀螺仪数据采集设备", "提示");
		return FALSE;
	}

	// refresh scanner combox
	((CComboBox*)GetDlgItem(IDC_COMBO_DEV_IMAGE))->ResetContent();
	for (int i = 0; i < MAX_DEVICE_NUM; i++) {
		if (sScannerList.scannerType[i] == SCANNER_DF500) {
			((CComboBox*)GetDlgItem(IDC_COMBO_DEV_IMAGE))->AddString("BioSlap");
			handle_dev_image_list.push_back(0);
		}
	}
	((CComboBox*)GetDlgItem(IDC_COMBO_DEV_IMAGE))->SetCurSel(0);
	cur_dev_image_idx = 0;

	// refresh gyro combox
	((CComboBox*)GetDlgItem(IDC_COMBO_DEV_GYRO))->ResetContent();
	for (int i = 0; i < sz_comm.m_PortNameList.size(); i++) {
		((CComboBox*)GetDlgItem(IDC_COMBO_DEV_GYRO))->AddString(sz_comm.m_PortNameList[i]);
	}
	((CComboBox*)GetDlgItem(IDC_COMBO_DEV_GYRO))->SetCurSel(0);
	cur_dev_gyro_idx = 0;

	((CComboBox*)GetDlgItem(IDC_COMBO_DEV_GYRO2))->ResetContent();
	for (int i = 0; i < sz_comm2.m_PortNameList.size(); i++) {
		((CComboBox*)GetDlgItem(IDC_COMBO_DEV_GYRO2))->AddString(sz_comm2.m_PortNameList[i]);
	}
	((CComboBox*)GetDlgItem(IDC_COMBO_DEV_GYRO2))->SetCurSel(0);
	cur_dev_gyro2_idx = 1;

	for (int i = 0; i < sz_comm.m_PortRateList.size(); i++) {
		((CComboBox*)GetDlgItem(IDC_COMBO_RATE_GYRO))->AddString(FormatString(sz_comm.m_PortRateList[i]));
	}
	((CComboBox*)GetDlgItem(IDC_COMBO_RATE_GYRO))->SetCurSel(2); // set 9600
	cur_gyro_rate_idx = 2;

	return TRUE;
}

CString GetProgramPath()
{
	CString  strProgramPath;
	GetModuleFileName(NULL, strProgramPath.GetBuffer(MAX_PATH), MAX_PATH);
	strProgramPath.ReleaseBuffer(MAX_PATH);
	int nPathPos = strProgramPath.ReverseFind('\\');
	strProgramPath = strProgramPath.Left(nPathPos + 1);
	return strProgramPath;
}

void CFpCaptureSysDlg::Initparam()
{
	m_pImagePre = NULL;
	m_pImageResult = NULL;

	cur_dataDir = GetProgramPath() + "../Data";
	if (_access(cur_dataDir, 0) == -1) {
		_mkdir(cur_dataDir);
	}

	UpdateData();
}

void CFpCaptureSysDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFpCaptureSysDlg::OnPaint()
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
HCURSOR CFpCaptureSysDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CFpCaptureSysDlg::SetInfo(char* chInfo, int ierrCode)
{
	CString strinfo;
	strinfo.Format("%s  ret= %d", chInfo, ierrCode);
	SetDlgItemText(IDC_STATIC_STATUS, strinfo);
}

void CFpCaptureSysDlg::SetInfo(CString chInfo, int ierrCode)
{
	CString strinfo;
	strinfo.Format("  ret= %d", ierrCode);
	SetDlgItemText(IDC_STATIC_STATUS, chInfo + strinfo);
}


//Register callback
BOOL CFpCaptureSysDlg::InitCallBFuctions() {
	M_Capture_RegisterCallbackPreviewImage(
		handle_dev_image_list[cur_dev_image_idx],
		OnPreviewImageAvailable,
		this
	);
	M_Capture_RegisterCallbackTakingResultImage(
		handle_dev_image_list[cur_dev_image_idx],
		OnTakingResultImage,
		this
	);

	/*DTF_M_Capture_RegisterCallbackObjectQuality(
	handle_dev_image[cur_dev_image_idx],
	OnResultFingersQuality,
	this
	);*/

	m_pImagePre = new BYTE[IMAGE_PRE_SIZE * 2];
	m_pImageResult = new BYTE[IMAGE_RESULT_SIZE];
	return TRUE;
}
void CFpCaptureSysDlg::StorePreData() {
	if (is_receive == true) {
		// change status of storing temp data
		int sum = accumulate(m_pImagePre, m_pImagePre + img_width * img_height, 0, [](int a, BYTE b) {return a + int(b < 255 * 0.6); });
		if (!is_store && sum >= det_thresh) {
			is_store = TRUE;
			is_saved = FALSE;
			SetInfo("开始收集数据", 1);
		}
		else if (is_store && sum < det_thresh) {
			is_store = FALSE;
			StopCaptureFp("停止收集数据");
			OnBnClickedButtonSave();
		}
		
		if (is_store) {
			// TODO: store image and pose data
			BYTE* image_array = new BYTE[img_width * img_height];
			memcpy(image_array, m_pImagePre, img_width * img_height);
			tmp_image_list.push_back(image_array);
			tmp_roll_list.push_back(sz_comm.Angle[0]);
			tmp_pitch_list.push_back(sz_comm.Angle[1]);
			tmp_yaw_list.push_back(sz_comm.Angle[2]);
			tmp_accx_list.push_back(sz_comm.Acc[0]);
			tmp_accy_list.push_back(sz_comm.Acc[1]);
			tmp_accz_list.push_back(sz_comm.Acc[2]);
			tmp_magx_list.push_back(sz_comm.Mag[0]);
			tmp_magy_list.push_back(sz_comm.Mag[1]);
			tmp_magz_list.push_back(sz_comm.Mag[2]);
			tmp_roll2_list.push_back(sz_comm2.Angle[0]);
			tmp_pitch2_list.push_back(sz_comm2.Angle[1]);
			tmp_yaw2_list.push_back(sz_comm2.Angle[2]);
		}
	}

	GetDlgItem(IDC_EDIT_ROLL2)->SetWindowTextA(FormatString(sz_comm2.Angle[0]));
	GetDlgItem(IDC_EDIT_PITCH2)->SetWindowTextA(FormatString(sz_comm2.Angle[1]));
	GetDlgItem(IDC_EDIT_YAW2)->SetWindowTextA(FormatString(sz_comm2.Angle[2]));

	GetDlgItem(IDC_EDIT_ROLL)->SetWindowTextA(FormatString(sz_comm.Angle[0]));
	GetDlgItem(IDC_EDIT_PITCH)->SetWindowTextA(FormatString(sz_comm.Angle[1]));
	GetDlgItem(IDC_EDIT_YAW)->SetWindowTextA(FormatString(sz_comm.Angle[2]));

	GetDlgItem(IDC_EDIT_ACCX)->SetWindowTextA(FormatString(sz_comm.Acc[0]));
	GetDlgItem(IDC_EDIT_ACCY)->SetWindowTextA(FormatString(sz_comm.Acc[1]));
	GetDlgItem(IDC_EDIT_ACCZ)->SetWindowTextA(FormatString(sz_comm.Acc[2]));

	GetDlgItem(IDC_EDIT_MAGX)->SetWindowTextA(FormatString(sz_comm.Mag[0]));
	GetDlgItem(IDC_EDIT_MAGY)->SetWindowTextA(FormatString(sz_comm.Mag[1]));
	GetDlgItem(IDC_EDIT_MAGZ)->SetWindowTextA(FormatString(sz_comm.Mag[2]));
}

void CFpCaptureSysDlg::StopCaptureFp(char* chInfo) {
	sz_comm.StopListen();
	sz_comm2.StopListen();
	cap_timer.stop();
	is_receive = FALSE;
	is_store = FALSE;

	int nRc = 0;
	nRc = M_Capture_Abort(handle_dev_image_list[cur_dev_image_idx]);
	if (nRc != STATUS_OK) {
		MessageBox("Abort capture image failed!", "Information");
		//m_bTakeResultImage = FALSE;		
	}
	SetInfo(chInfo, nRc);

	GetDlgItem(IDC_CHECK_FOG)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO_FREQ)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_DETTHRESH)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_RELEASE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(TRUE);
}

void CFpCaptureSysDlg::OnPreviewImageAvailable(void* pContext, const ImageData image) {
	int nRc;
	CFpCaptureSysDlg* pCurInst = reinterpret_cast<CFpCaptureSysDlg*>(pContext);

	if (pCurInst != NULL) {
		memcpy(pCurInst->m_pImagePre, image.Buffer, image.Height * image.Width);
		//if (g_bisRoll) {
		//	//pCurInst->DrawImageRoll(pCurInst->m_pImagePre, image.Width, image.Height, 1, IDC_STATIC_IMG);
		//	pCurInst->DrawImage(pCurInst->m_pImagePre, image.Width, image.Height, 1, IDC_STATIC_IMG);
		//} else {
		//	pCurInst->DrawImage(pCurInst->m_pImagePre, image.Width, image.Height, 1, IDC_STATIC_IMG);
		//}

		pCurInst->DrawImage(pCurInst->m_pImagePre, image.Width, image.Height, 1, IDC_STATIC_IMG);

		//int sum = accumulate(pCurInst->m_pImagePre, pCurInst->m_pImagePre + image.Width * image.Height, 0, [](int a, BYTE b) {return a + int(b < 255*0.6); });
		//pCurInst->GetDlgItem(IDC_EDIT_YAW)->SetWindowTextA(pCurInst->FormatString(sum));
	}
	//pCurInsttemp = reinterpret_cast<CFpCaptureSysDlg *>(pContext);

	//if (pCurInsttemp != NULL)
	//{
	//	memcpy(pCurInsttemp->m_pImagePre,image.Buffer,image.Height*image.Width);

	//	pCurInsttemp->m_iWtemp=image.Width;
	//	pCurInsttemp->m_iHtemp=image.Height;
	//	g_temp = TRUE;
	//}
}

void CFpCaptureSysDlg::OnTakingResultImage(void* pContext)
{
	CFpCaptureSysDlg* pCurInst = reinterpret_cast<CFpCaptureSysDlg*>(pContext);
	M_Controls_Beeper(pCurInst->handle_dev_image_list[pCurInst->cur_dev_image_idx], 0);
}

void CFpCaptureSysDlg::DrawImage(BYTE* image, int W, int H, int icolor, int nID) {
	int ww = W;
	int hh = H;

	BITMAPINFO* m_pBmpInfo;
	memset(m_chBmpBuf, 0, 2048);
	m_pBmpInfo = (BITMAPINFO*)m_chBmpBuf;

	//位图信息头
	m_pBmpInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pBmpInfo->bmiHeader.biWidth = ww;
	m_pBmpInfo->bmiHeader.biHeight = hh;
	m_pBmpInfo->bmiHeader.biPlanes = 1;
	//if (m_color == 1)
	if (icolor == 1) {
		m_pBmpInfo->bmiHeader.biBitCount = 8;

		//位图颜色
		for (int i = 0; i < 256; i++) {
			ASSERT(i == BYTE(i));
			m_pBmpInfo->bmiColors[i].rgbBlue = BYTE(i);
			m_pBmpInfo->bmiColors[i].rgbGreen = BYTE(i);
			m_pBmpInfo->bmiColors[i].rgbRed = BYTE(i);
			m_pBmpInfo->bmiColors[i].rgbReserved = 0;
		}
	} else if (icolor == 2) {
		m_pBmpInfo->bmiHeader.biBitCount = 32;
	} else {
		m_pBmpInfo->bmiHeader.biBitCount = 24;
	}

	// 	m_pBmpInfo->bmiHeader.biCompression   = BI_RGB;
	// 	m_pBmpInfo->bmiHeader.biSizeImage     = 0;
	// 	m_pBmpInfo->bmiHeader.biXPelsPerMeter = 0;
	// 	m_pBmpInfo->bmiHeader.biYPelsPerMeter = 0;
	// 	m_pBmpInfo->bmiHeader.biClrUsed       = 0;
	//  m_pBmpInfo->bmiHeader.biClrImportant  = 0;

	HWND hwndPreview = NULL;
	GetDlgItem(nID, &hwndPreview);

	HDC hdcPreview = ::GetDC(hwndPreview);
	PAINTSTRUCT ps;
	::BeginPaint(hwndPreview, &ps);

	SetStretchBltMode(hdcPreview, HALFTONE);  // COLORONCOLOR); //STRETCH_HALFTONE

	HWND hwnd = NULL;
	GetDlgItem(nID, &hwnd);

	RECT rc;
	::GetClientRect(hwnd, &rc);

	int re;
	re = ::StretchDIBits(hdcPreview,
		rc.left,
		rc.top,
		rc.right - rc.left,
		rc.bottom - rc.top,
		0,
		0,
		ww,
		abs(hh),
		image,
		m_pBmpInfo,
		DIB_RGB_COLORS, SRCCOPY);

	::EndPaint(hwndPreview, &ps);
	::ReleaseDC(hwndPreview, hdcPreview);
}


void CFpCaptureSysDlg::DrawImageRoll(BYTE* image, int W, int H, int icolor, int nID) {
	int ww, hh;
	ww = W;
	hh = H;

	BITMAPINFO* m_pBmpInfo;
	memset(m_chBmpBuf, 0, 2048);
	m_pBmpInfo = (BITMAPINFO*)m_chBmpBuf;

	//位图信息头
	m_pBmpInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	m_pBmpInfo->bmiHeader.biWidth = ww;
	m_pBmpInfo->bmiHeader.biHeight = hh;
	m_pBmpInfo->bmiHeader.biPlanes = 1;
	//if (m_color == 1)
	if (icolor == 1) {
		m_pBmpInfo->bmiHeader.biBitCount = 8;

		//位图颜色
		for (int i = 0; i < 256; i++) {
			ASSERT(i == BYTE(i));
			m_pBmpInfo->bmiColors[i].rgbBlue = BYTE(i);
			m_pBmpInfo->bmiColors[i].rgbGreen = BYTE(i);
			m_pBmpInfo->bmiColors[i].rgbRed = BYTE(i);
			m_pBmpInfo->bmiColors[i].rgbReserved = 0;
		}
	}
	else {
		m_pBmpInfo->bmiHeader.biBitCount = 24;
	}

	// 	m_pBmpInfo->bmiHeader.biCompression   = BI_RGB;
	// 	m_pBmpInfo->bmiHeader.biSizeImage     = 0;
	// 	m_pBmpInfo->bmiHeader.biXPelsPerMeter = 0;
	// 	m_pBmpInfo->bmiHeader.biYPelsPerMeter = 0;
	// 	m_pBmpInfo->bmiHeader.biClrUsed       = 0;
	//  m_pBmpInfo->bmiHeader.biClrImportant  = 0;

	HWND hwndPreview = NULL;
	GetDlgItem(nID, &hwndPreview);

	HDC hdcPreview = ::GetDC(hwndPreview);
	PAINTSTRUCT ps;
	::BeginPaint(hwndPreview, &ps);

	SetStretchBltMode(hdcPreview, HALFTONE);  // COLORONCOLOR); //STRETCH_HALFTONE

	HWND hwnd = NULL;
	GetDlgItem(nID, &hwnd);

	RECT rc;
	::GetClientRect(hwnd, &rc);
	///////////////////////

	CBrush br(0x888888);
	//::FillRect( hdcPreview,&rc, br );

	RECT rctop;
	rctop.left = rc.left;
	rctop.top = rc.top;
	rctop.right = rc.right - rc.left;
	rctop.bottom = (rc.bottom - rc.top) / 6;

	//  (rc.left,rc.top, rc.right - rc.left,(rc.bottom - rc.top)/4);
	//CBrush br(0x888888);
	::FillRect(hdcPreview, &rctop, br);


	RECT rcbot;
	rcbot.left = rc.left;
	rcbot.top = (rc.bottom - rc.top) / 6 * 5;
	rcbot.right = rc.right - rc.left;
	rcbot.bottom = rc.bottom;

	//  (rc.left,rc.top, rc.right - rc.left,(rc.bottom - rc.top)/4);

	::FillRect(hdcPreview, &rcbot, br);

	////////////////////////////////
	int ix, iy, iw, ih;
	ih = rc.bottom - (rcbot.bottom - rcbot.top) - (rctop.bottom - rctop.top);
	iw = ih * 1.5;
	if (iw > rc.right - rc.left)
		iw = rc.right - rc.left;
	ix = rc.left + ((rc.right - rc.left - iw) / 2);
	iy = rc.top + rctop.bottom;

	RECT rcleft;
	rcleft.left = rc.left;
	rcleft.top = iy;
	rcleft.right = ix;
	rcleft.bottom = iy + ih;
	::FillRect(hdcPreview, &rcleft, br);

	RECT rcright;
	rcright.left = ix + iw;
	rcright.top = iy;
	rcright.right = rc.right;
	rcright.bottom = iy + ih;
	::FillRect(hdcPreview, &rcright, br);

	int re;
	re = ::StretchDIBits(hdcPreview,
		ix,
		iy,
		iw,
		ih,//高度
		0,
		0,
		ww,
		abs(hh),
		image,
		m_pBmpInfo,
		DIB_RGB_COLORS, SRCCOPY);
	//re = ::StretchDIBits( hdcPreview, 
	//	rc.left, 
	//	rc.top+rctop.bottom, 
	//	rc.right - rc.left,
	//	rc.bottom-(rcbot.bottom-rcbot.top)-(rctop.bottom-rctop.top),//高度
	//	0,
	//	0,
	//	ww,
	//	abs(hh),
	//	image,
	//	m_pBmpInfo, 
	//	DIB_RGB_COLORS, SRCCOPY);

	::EndPaint(hwndPreview, &ps);
	::ReleaseDC(hwndPreview, hdcPreview);
}

void CFpCaptureSysDlg::OnBnClickedButtonInit()
{
	// TODO: 在此添加控件通知处理程序代码

	// com initialization (gyro)
	if (cur_dev_gyro_idx == cur_dev_gyro2_idx) {
		MessageBox("参考陀螺仪选择错误!", "提示");
		SetInfo("Wrong reference serial port selected", 0);
		return;
	}
	bool is_opencomm = sz_comm.OpenCom(cur_dev_gyro_idx, cur_gyro_rate_idx);
	double test_angle[3];
	if (!is_opencomm || !sz_comm.ReadAngle(test_angle)) {
		MessageBox("无法接受串口数据!", "提示");
		SetInfo("Can't receive data from serial port", 0);
		return;
	}
	is_opencomm = sz_comm2.OpenCom(cur_dev_gyro2_idx, cur_gyro_rate_idx);
	if (!is_opencomm || !sz_comm2.ReadAngle(test_angle)) {
		MessageBox("无法接受参考陀螺仪的串口数据!", "提示");
		SetInfo("Can't receive data from serial port", 0);
		return;
	}

	// df500 initialization
	SetInfo("正在初始化设备，请不要放手指！", 0);

	//m_dlgMsg.Create(NULL,"Initializing device,please wait and don't put finger");
	//m_dlgMsg.Create(NULL,"正在初始化设备，请不要放手指");
	int nRc = M_Main_Initialize(cur_dev_image_idx, &handle_dev_image_list[cur_dev_image_idx]);

	if (nRc == -607) {
		MessageBox("您已经进行了初始化!", "提示");
		SetInfo("M_Main_Initialize", nRc);
		return;
	}
	else if (nRc != STATUS_OK) {
		SetInfo("M_Main_Initialize", nRc);
		return;
	}

	InitCallBFuctions();

	//m_dlgMsg.SetMsg("Calibrating the scanner,please wait and don't put finger");
	//m_dlgMsg.SetMsg("指纹仪校准，请不要放手指");

	CString buff;
	DFRollParameters tDTFRollParm;
	// Calibration 设置曝光值
	nRc = M_Capture_Calibration(handle_dev_image_list[cur_dev_image_idx]);
	if (nRc != STATUS_OK) {
		buff.Format("校准失败!");
		MessageBox(buff, "Infomation");
		SetInfo("Capture_Calibration", nRc);
		//m_dlgMsg.DestroyWindow();
		return;
	}

	//设置滚指参数
	tDTFRollParm.MaxFrameNumber = 100;
	tDTFRollParm.SlideDetectionStatus = 1;
	tDTFRollParm.SlidingPixelCounter = 25000;
	tDTFRollParm.SlidingPercentageThreshold = (float)0.115;
	tDTFRollParm.SlidingSADMeanThreshlod = 36;
	tDTFRollParm.RollBackThreshold = -200;
	tDTFRollParm.CheckSensorThreshold = 400;
	nRc = M_Capture_SetRollParameters(handle_dev_image_list[cur_dev_image_idx], tDTFRollParm);
	if (nRc != STATUS_OK) {
		MessageBox(buff, "提示");
		SetInfo("M_Capture_SetRollParameters", nRc);
		//m_dlgMsg.DestroyWindow();
		return;
	}
	//M_Controls_Beeper(handle_dev_image_list[cur_dev_image_idx], 0);
	DTFPropertyInfo info;
	nRc = M_Main_GetDeviceInfo(handle_dev_image_list[cur_dev_image_idx], &info);

	SetInfo("初始化成功", 1);
	MessageBox("初始化成功!");

	GetDlgItem(IDC_COMBO_DEV_IMAGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_DEV_GYRO)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_DEV_GYRO2)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_RATE_GYRO)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_INIT)->EnableWindow(FALSE);

	GetDlgItem(IDC_BUTTON_DEINIT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_ALIGN)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHECK_FOG)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO_FREQ)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_DETTHRESH)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_RELEASE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(FALSE);
}


int CFpCaptureSysDlg::SetCaptureMode(int iMode)
{
	int nRc = 0;
	nRc = M_Capture_Abort(handle_dev_image_list[cur_dev_image_idx]);
	//Set mode
	BOOL AutoContrast = FALSE;
	DTFImageType imageType;
	DTFImageResolution imageResolution = IMAGE_RESOLUTION_500;
	int nCount = 1;
	int ledValue = 0;

	if (iMode == 2) //Right 4
	{
		imageType = FLAT_RIGHT_FINGERS;
		nCount = 4;
		//m_nFinMask = 1;//Mask
		//m_nFpos = 15;
		ledValue = 27;
	}

	else if (iMode == 1) //Left 4
	{
		//imageType = DTF_FLAT_LEFT_FINGERS;先都用下面的这个参数DTF_FLAT_RIGHT_FINGERS
		imageType = FLAT_LEFT_FINGERS;
		nCount = 4;
		//m_nFinMask = 1;//Mask
		//m_nFpos = 15;
		ledValue = 27;
	}

	else if (iMode == 4)//Roll
	{
		imageType = ROLL_SINGLE_FINGER;
		nCount = 1;
		ledValue = 27;
		//g_bisRoll = TRUE;
	}
	else if (iMode == 5)//2 Thumbs
	{
		imageType = FLAT_TWO_THUMBS;
		nCount = 2;
		ledValue = 27;
	}
	else if (iMode == 3)//Single
	{
		imageType = FLAT_RIGHT_THUMB;
		nCount = 1;
		ledValue = 27;
	}

	nRc = M_Capture_SetMode(
		handle_dev_image_list[cur_dev_image_idx],
		imageType,
		imageResolution,
		g_AutoCapture,
		AutoContrast,
		&img_width,
		&img_height,
		&img_base_resolutionx,
		&img_base_resolutiony
	);

	if (nRc != STATUS_OK) {
		M_Main_DeInitialize(handle_dev_image_list[cur_dev_image_idx]);
	}

	//DTF_M_Controls_SetFingerLEDs(handle_dev_image[cur_dev_image_idx],imageType,LED_COLOR_GREEN);
	return nRc;
}

void CFpCaptureSysDlg::ResetMyCtrl()
{
	//刷新对话框
	UpdateData();
}

void CFpCaptureSysDlg::OnBnClickedButtonStart()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedButtonRelease();

	UpdateData();

	//if (((CButton*)GetDlgItem(IDC_CHECK_AUTO))->GetCheck())
	//	g_AutoCapture = TRUE;
	//else
	//	g_AutoCapture = FALSE;

	if (((CButton*)GetDlgItem(IDC_CHECK_FOG))->GetCheck())
		M_Control_RemoveFog(handle_dev_image_list[cur_dev_image_idx], TRUE);
	else
		M_Control_RemoveFog(handle_dev_image_list[cur_dev_image_idx], FALSE);

	// roll fingerprint
	int m_nCount = 1;
	int iImageType = 4;
	int nRc = SetCaptureMode(iImageType);
	if (nRc != STATUS_OK) {
		MessageBox("设定模式失败!", "提示");
		return;
	}
	SetInfo("M_Capture_SetMode", nRc);

	//以下是start里的内容
	int nRc1 = 0;
	nRc1 = M_Capture_Start(handle_dev_image_list[cur_dev_image_idx], m_nCount, g_AutoCapture);
	SetInfo("M_Capture_Start", nRc1);

	if (nRc1 == STATUS_OK && g_bisRoll)
		nRc1 = M_Capture_SetStartRollingFlag(handle_dev_image_list[cur_dev_image_idx], TRUE);

	Setmodeindexfirst = TRUE;

	ResetMyCtrl();

	det_thresh = GetDlgItemInt(IDC_EDIT_DETTHRESH);

	sz_comm.StartListen(7);
	sz_comm2.StartListen(20);
	cap_timer.start(1000.0 / cap_freq, std::bind(&CFpCaptureSysDlg::StorePreData, this));
	is_receive = true;
	cur_dataFileName = COleDateTime::GetCurrentTime().Format("%Y%m%d%H%M%S");

	GetDlgItem(IDC_CHECK_FOG)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_FREQ)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_DETTHRESH)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_RELEASE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(FALSE);
}


void CFpCaptureSysDlg::OnBnClickedButtonStop()
{
	// TODO: 在此添加控件通知处理程序代码
	is_store = FALSE;
	StopCaptureFp("停止采集指纹");
	OnBnClickedButtonSave();
}

void CFpCaptureSysDlg::SaveImage(CString strPreDir, int idx, CString strFileName) {
	//CString strFileName;
	//strFileName.Format("1%05d_0", idx); // 留一个扩展位
	strFileName = strPreDir + "/" + strFileName + ".png";

	FILE* fp = NULL;
	png_structp png_ptr = NULL;
	png_infop info_ptr = NULL;

	if (fopen_s(&fp, strFileName, "wb")) {
		MessageBox("无法写入数据");
		return;
	}

	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png_ptr == NULL) {
		MessageBox("保存数据失败");
		fclose(fp);
		return;
	}

	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		MessageBox("保存数据失败");
		fclose(fp);
		png_destroy_write_struct(&png_ptr, NULL);
		return;
	}

	if (setjmp(png_jmpbuf(png_ptr))) {
		MessageBox("保存数据失败");
		fclose(fp);
		png_destroy_write_struct(&png_ptr, NULL);
		return;
	}

	png_init_io(png_ptr, fp);
	png_set_IHDR(png_ptr, info_ptr, img_width, img_height, 8, PNG_COLOR_TYPE_GRAY, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
	png_write_info(png_ptr, info_ptr);

	if (setjmp(png_jmpbuf(png_ptr))) {
		MessageBox("保存数据失败");
		fclose(fp);
		png_destroy_write_struct(&png_ptr, NULL);
		return;
	}

	png_bytepp rows = (png_bytepp)png_malloc(png_ptr, img_height * sizeof(png_bytep));
	for (int i = 0; i < img_height; ++i)
	{
		rows[img_height - 1 - i] = (png_bytep)(tmp_image_list[idx] + i * img_width);
	}

	png_write_image(png_ptr, rows);
	delete[] rows;
	png_write_end(png_ptr, info_ptr);
	png_destroy_write_struct(&png_ptr, &info_ptr);
	fclose(fp);
}

void CFpCaptureSysDlg::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	if (tmp_image_list.size() == 0) {
		return;
	}

	if (tmp_image_list.size() < 10) {
		MessageBox("图像过少，请重新采集!");
		ReleaseTmpData();
		return;
	}

	if (!(tmp_image_list.size() == tmp_yaw_list.size())) {
		MessageBox("图像与姿态列表数目不一致，请重新采集!");
		ReleaseTmpData();
		//OnBnClickedButtonStop();
		return;
	}

	CString strPreDir = cur_dataDir + "/" + cur_dataFileName;

	if (_access(strPreDir, 0) == -1) {
		int flag = _mkdir(strPreDir);
		if (flag != 0) {
			MessageBox("创建图片目录失败，请重试！");
			return;
		}
	}
	else {
		MessageBox("数据已存在，请重新采集！");
		ReleaseTmpData();
		return;
	}

	// save data
	FILE *fp1, *fp2;
	if (fopen_s(&fp1, strPreDir + "/" + "pose.txt", "wb")) {
		MessageBox("无法写入数据");
		return;
	}
	if (fopen_s(&fp2, strPreDir + "/" + "pose_align.txt", "wb")) {
		MessageBox("无法写入数据");
		return;
	}
	fprintf(fp1, "File for finger pose in 3D space, from left to right: id,roll,pitch,yaw. The frequence of capturing is %dHz\n", cap_freq);
	fprintf(fp2, "File for aligned finger pose in 3D space, from left to right: id,roll,pitch,yaw. The frequence of capturing is %dHz\n", cap_freq);
	double mean_roll2 = accumulate(begin(tmp_roll2_list), end(tmp_roll2_list), 0.0) / tmp_roll2_list.size();
	double mean_pitch2 = accumulate(begin(tmp_pitch2_list), end(tmp_pitch2_list), 0.0) / tmp_pitch2_list.size();
	double mean_yaw2 = accumulate(begin(tmp_yaw2_list), end(tmp_yaw2_list), 0.0) / tmp_yaw2_list.size();
	//// 欧拉角 -> 旋转矩阵
	//Eigen::Vector3d euler_angle2(mean_roll2 * DEG_TO_ARC, mean_pitch2 * DEG_TO_ARC, mean_yaw2 * DEG_TO_ARC);
	//Eigen::Matrix3d rotation_matrix1, rotation_matrix2;
	//rotation_matrix2 = Eigen::AngleAxisd(euler_angle2[2], Eigen::Vector3d::UnitZ()) * Eigen::AngleAxisd(euler_angle2[1], Eigen::Vector3d::UnitY()) * Eigen::AngleAxisd(euler_angle2[0], Eigen::Vector3d::UnitX());
	////rotation_matrix2 = q.toRotationMatrix();
	for (int i = 0; i < tmp_image_list.size(); i++) {
		CString strFileName;
		strFileName.Format("1%05d_0", i); // 留一个扩展位
		SaveImage(strPreDir, i, strFileName);

		fprintf(fp1, "%s\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\t%.4f\n", strFileName, tmp_roll_list[i], tmp_pitch_list[i], tmp_yaw_list[i], tmp_accx_list[i], tmp_accy_list[i], tmp_accz_list[i], tmp_magx_list[i], tmp_magx_list[i], tmp_magx_list[i]);

		//Eigen::Vector3d euler_angle1(tmp_roll_list[i] * DEG_TO_ARC, tmp_pitch_list[i] * DEG_TO_ARC, tmp_yaw_list[i] * DEG_TO_ARC);
		//rotation_matrix1 = Eigen::AngleAxisd(euler_angle1[2], Eigen::Vector3d::UnitZ()) * Eigen::AngleAxisd(euler_angle1[1], Eigen::Vector3d::UnitY()) * Eigen::AngleAxisd(euler_angle1[0], Eigen::Vector3d::UnitX());
		////rotation_matrix1 = q.toRotationMatrix();
		//Eigen::Matrix3d rotation_matrix_align = rotation_matrix2.transpose() * rotation_matrix1;
		//Eigen::Vector3d euler_angle_align = rotation_matrix_align.eulerAngles(2, 1, 0);
		//fprintf(fp2, "%s\t%.4f\t%.4f\t%.4f\n", strFileName, euler_angle_align[2] * ARC_TO_DEG, euler_angle_align[1] * ARC_TO_DEG, euler_angle_align[0] * ARC_TO_DEG);

		fprintf(fp2, "%s\t%.4f\t%.4f\t%.4f\n", strFileName, tmp_roll2_list[i] - tmp_roll_list[i], tmp_pitch2_list[i] - tmp_pitch_list[i], tmp_yaw2_list[i] - tmp_yaw_list[i]);
	}
	fclose(fp1);
	fclose(fp2);

	SetInfo("保存数据'" + strPreDir + "'成功", 1);
	is_saved = TRUE;
}

void CFpCaptureSysDlg::ReleaseTmpData() {
	if (tmp_image_list.size()) {
		for (int i = 0; i < tmp_image_list.size(); i++) {
			delete[] tmp_image_list[i];
		}
		vector<BYTE*>().swap(tmp_image_list);

		vector<double>().swap(tmp_roll_list);
		vector<double>().swap(tmp_pitch_list);
		vector<double>().swap(tmp_yaw_list);
		vector<double>().swap(tmp_roll2_list);
		vector<double>().swap(tmp_pitch2_list);
		vector<double>().swap(tmp_yaw2_list);
		vector<double>().swap(tmp_accx_list);
		vector<double>().swap(tmp_accy_list);
		vector<double>().swap(tmp_accz_list);
		vector<double>().swap(tmp_magx_list);
		vector<double>().swap(tmp_magy_list);
		vector<double>().swap(tmp_magz_list);
	}

	is_saved = TRUE;
}


void CFpCaptureSysDlg::OnBnClickedButtonExit()
{
	// TODO: 在此添加控件通知处理程序代码
	sz_comm.StopListen();
	sz_comm2.StopListen();
	cap_timer.stop();
	is_receive = FALSE;

	OnBnClickedButtonDeinit();
	CDialogEx::OnCancel();
}


void CFpCaptureSysDlg::OnBnClickedButtonDeinit()
{
	// TODO: 在此添加控件通知处理程序代码
	if (handle_dev_image_list.size() > 0 && handle_dev_image_list[cur_dev_image_idx] >= 0)
		M_Main_DeInitialize(handle_dev_image_list[cur_dev_image_idx]);

	OnBnClickedButtonRelease();
	if (m_pImagePre) { delete[] m_pImagePre; m_pImagePre = NULL; }
	if (m_pImageResult) { delete[] m_pImageResult; m_pImageResult = NULL; }

	sz_comm.CloseCom();
	sz_comm2.CloseCom();

	GetDlgItem(IDC_COMBO_DEV_IMAGE)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO_DEV_GYRO)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO_DEV_GYRO2)->EnableWindow(TRUE);
	GetDlgItem(IDC_COMBO_RATE_GYRO)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_INIT)->EnableWindow(TRUE);

	GetDlgItem(IDC_BUTTON_DEINIT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_ALIGN)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_FOG)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_FREQ)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_DETTHRESH)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_RELEASE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SAVE)->EnableWindow(FALSE);
}


void CFpCaptureSysDlg::OnCbnSelchangeComboRateGyro()
{
	// TODO: 在此添加控件通知处理程序代码
	cur_gyro_rate_idx = ((CComboBox*)GetDlgItem(IDC_COMBO_RATE_GYRO))->GetCurSel();
}


void CFpCaptureSysDlg::OnCbnSelchangeComboDevGyro()
{
	// TODO: 在此添加控件通知处理程序代码
	cur_dev_gyro_idx = ((CComboBox*)GetDlgItem(IDC_COMBO_DEV_GYRO))->GetCurSel();
}


void CFpCaptureSysDlg::OnCbnSelchangeComboFreq()
{
	// TODO: 在此添加控件通知处理程序代码
	cap_freq = CapFreq[((CComboBox*)GetDlgItem(IDC_COMBO_FREQ))->GetCurSel()];
}


void CFpCaptureSysDlg::OnBnClickedButtonRelease()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!is_saved && MessageBox("是否保存现有数据？", "请确认", MB_OKCANCEL) == IDOK) {
		OnBnClickedButtonSave();
	}

	SetInfo("清除缓存", 1);
}


void CFpCaptureSysDlg::OnCbnSelchangeComboDevGyro2()
{
	// TODO: 在此添加控件通知处理程序代码
	cur_dev_gyro2_idx = ((CComboBox*)GetDlgItem(IDC_COMBO_DEV_GYRO2))->GetCurSel();
}


void CFpCaptureSysDlg::OnBnClickedButtonAlign()
{
	// TODO: 在此添加控件通知处理程序代码
	double pose_angles[3];
	double pose2_angles[3];
	sz_comm.ReadAngle(pose_angles);
	sz_comm2.ReadAngle(pose2_angles);
	roll = pose_angles[0];
	pitch = pose_angles[1];
	yaw = pose_angles[2];
	roll2 = pose2_angles[0];
	pitch2 = pose2_angles[1];
	yaw2 = pose2_angles[2];
}
