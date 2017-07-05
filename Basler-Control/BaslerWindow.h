
// Basler-ControlDlg.h : header file
//

#pragma once
#include "PictureControl.h"
#include "Control.h"
#include "BaslerSettingsControl.h"
#include "BaslerCamera.h"
#include "PictureStats.h"
#include "PictureSaver.h"
#include "commonTypes.h"


class BaslerWindow : public CDialogEx
{
	public:
		
		BaslerWindow(CWnd* pParent = NULL);	
		virtual BOOL OnInitDialog();
		void OnPaint();
		HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
		HCURSOR OnQueryDragIcon();
		void OnSize( UINT nType, int cx, int cy );
		void handleArmPress();
		void handleDisarmPress();
		void initializeControls();
		void passExposureMode();
		void passCameraMode();
		afx_msg LRESULT handleNewPics( WPARAM wParam, LPARAM lParam );
		void pictureRangeEditChange( UINT id );
		void OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* scrollbar );
		void handleSoftwareTrigger();
		void OnMouseMove(UINT flags, CPoint point);
	// Dialog Data
	#ifdef AFX_DESIGN_TIME
		enum { IDD = IDD_BASLERCONTROL_DIALOG };
	#endif

	private:
		PictureControl picture;
		BaslerSettingsControl settings;
		BaslerCameras* cameraController;
		PictureStats stats;
		PictureSaver saver;
		unsigned int currentRepNumber;
		std::string runExposureMode;
		std::vector<std::vector<long>> images;
		unsigned int imageWidth;
		brushMap mainBrushes;
		rgbMap mainRGBs;
		fontMap mainFonts;
		bool isRunning;
	protected:
		virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
		HICON m_hIcon;

	DECLARE_MESSAGE_MAP()
};