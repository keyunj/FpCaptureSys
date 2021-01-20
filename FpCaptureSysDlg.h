
// FpCaptureSysDlg.h: 头文件
//

#pragma once
#include "DTFEssentialsApiM.h"
#include "CommUtils.h"
#include "afxwin.h"
#include "Timer.hpp"
#include <vector>

using namespace std;

// CFpCaptureSysDlg 对话框
class CFpCaptureSysDlg : public CDialogEx
{
// 构造
public:
	CFpCaptureSysDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FPCAPTURESYS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	// my variables
	CString cur_dataDir = "../Data";
	CString cur_dataFileName;

	BYTE* m_pImagePre, * m_pImageResult;
	int cur_dev_image_idx = 0;
	int cur_dev_gyro_idx = 0;
	int cur_dev_gyro2_idx = 0;
	int cur_gyro_rate_idx = 2;
	char m_chBmpBuf[2048];
	int cap_freq = 20;
	int det_thresh = 200;
	bool is_receive = FALSE; // if start to receive data
	bool is_store = FALSE; // if start to store data
	bool is_saved = TRUE; // if the temp data is saved

	int img_width = 800;
	int img_height = 750;
	int img_base_resolutionx = 500;
	int img_base_resolutiony = 500;

	Timer cap_timer;
	CommUtils sz_comm;
	CommUtils sz_comm2;
	double roll = 0;
	double pitch = 0;
	double yaw = 0;
	double roll2 = 0;
	double pitch2 = 0;
	double yaw2 = 0;
	
	vector<int> handle_dev_image_list;

	// temp data (to be saved)

	vector<BYTE*> tmp_image_list;
	vector<double> tmp_yaw_list;
	vector<double> tmp_pitch_list;
	vector<double> tmp_roll_list;
	vector<double> tmp_yaw2_list;
	vector<double> tmp_pitch2_list;
	vector<double> tmp_roll2_list;
	vector<double> tmp_accx_list;
	vector<double> tmp_accy_list;
	vector<double> tmp_accz_list;
	vector<double> tmp_magx_list;
	vector<double> tmp_magy_list;
	vector<double> tmp_magz_list;

	typedef struct StateTipTxt {
		CString cTipsStr[10];
		int		iID[10];
		int		iColorState[10];
	} STATETIPTXT;
	STATETIPTXT m_StatTipStr;

	// Callback functions:
	static void CALLBACK OnPreviewImageAvailable(
		void* pContext,
		const ImageData image
	);
	static void CALLBACK OnTakingResultImage(
		void* pContext
	);
	void Initparam();
	bool RefreshDevList();
	void SetInfo(char* chInfo, int ierrCode);
	void SetInfo(CString chInfo, int ierrCode);
	BOOL InitCallBFuctions();
	void DrawImageRoll(BYTE* image, int W, int H, int icolor, int nID);
	void DrawImage(BYTE* image, int W, int H, int icolor, int nID);
	int SetCaptureMode(int iMode);
	void ResetMyCtrl();
	CString FormatString(int num);
	CString FormatString(float num);
	CString FormatString(double num);
	void StorePreData();
	void StopCaptureFp(char* chInfo);
	void ReleaseTmpData();
	void SaveImage(CString strPreDir, int idx, CString strFileName);

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
	afx_msg void OnBnClickedButtonInit();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnBnClickedButtonDeinit();
	afx_msg void OnCbnSelchangeComboRateGyro();
	afx_msg void OnCbnSelchangeComboDevGyro();
	afx_msg void OnCbnSelchangeComboFreq();
	afx_msg void OnBnClickedButtonRelease();
	afx_msg void OnCbnSelchangeComboDevGyro2();
	afx_msg void OnBnClickedButtonAlign();
};
