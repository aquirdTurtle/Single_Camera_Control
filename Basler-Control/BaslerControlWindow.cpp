
// Basler-ControlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BaslerControlApp.h"
#include "BaslerControlWindow.h"
#include "afxdialogex.h"
#include "constants.h"


BEGIN_MESSAGE_MAP( BaslerControlWindow, CDialogEx )
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_COMMAND( IDC_ARM_BASLER_BUTTON, BaslerControlWindow::handleArmPress )
	ON_COMMAND( IDC_DISARM_BASLER_BUTTON, BaslerControlWindow::handleDisarmPress )
	ON_COMMAND( ID_SOFTWARE_TRIGGER, BaslerControlWindow::handleSoftwareTrigger )
	ON_REGISTERED_MESSAGE( ACE_PIC_READY, &BaslerControlWindow::handleNewPics )
	ON_CBN_SELENDOK( IDC_EXPOSURE_MODE_COMBO, BaslerControlWindow::passExposureMode )
	ON_CBN_SELENDOK(IDC_CAMERA_MODE_COMBO, BaslerControlWindow::passCameraMode)
	ON_CONTROL_RANGE( EN_CHANGE, IDC_BASLER_MIN_SLIDER_MIN_EDIT, IDC_BASLER_MIN_SLIDER_MIN_EDIT, &BaslerControlWindow::handlePictureRangeEditChange )
	ON_CONTROL_RANGE( EN_CHANGE, IDC_BASLER_MIN_SLIDER_MAX_EDIT, IDC_BASLER_MIN_SLIDER_MAX_EDIT, &BaslerControlWindow::handlePictureRangeEditChange )
	ON_WM_MOUSEMOVE()

END_MESSAGE_MAP()

void BaslerControlWindow::OnMouseMove( UINT flags, CPoint point )
{
	picture.handleMouse( point );
}

void BaslerControlWindow::handleSoftwareTrigger()
{
	try
	{
		camera->softwareTrigger();
	}
	catch (Pylon::TimeoutException& err)
	{
		errBox( "Software trigger timed out!" );
	}
}

void BaslerControlWindow::OnVScroll( UINT nSBCode, UINT nPos, CScrollBar* scrollbar )
{
	if (nSBCode == SB_THUMBPOSITION || nSBCode == SB_THUMBTRACK)
	{
		int id = scrollbar->GetDlgCtrlID();
		picture.handleScroll( id, nPos );
	}
}

void BaslerControlWindow::handlePictureRangeEditChange( UINT id )
{
	picture.handleEditChange( id );
}


void BaslerControlWindow::handleDisarmPress()
{
	camera->disarm();
}


LRESULT BaslerControlWindow::handleNewPics( WPARAM wParam, LPARAM lParam )
{
	long size = long( wParam );
	std::vector<long>* image = (std::vector<long>*) lParam;
	try
	{
		picture.drawBitmap( GetDC(), *image );
		if (settings.getCurrentSettings().exposureMode == "Auto Exposure Continuous")
		{
			settings.updateExposure( camera->getCurrentExposure() );
		}
		stats.update( image, 0, { 0,0 }, settings.getCurrentSettings().dimensions.horBinNumber, 0, 0 );
		saver.save( image, settings.getCurrentSettings().dimensions.horBinNumber );
	}
	catch (Error* err)
	{
		errBox( err->what() );
	}
	// always delete
	delete image;
	return 0;
}

void BaslerControlWindow::passCameraMode()
{
	settings.handleCameraMode();
}


void BaslerControlWindow::passExposureMode()
{
	settings.handleExposureMode();
}

void BaslerControlWindow::handleArmPress()
{
	try
	{
		camera->setParameters( settings.getCurrentSettings() );
		picture.updateGridSpecs( settings.getCurrentSettings().dimensions );
		HWND* win = new HWND;
		win = &m_hWnd;
		camera->armCamera( win );
	}
	catch (Error& err)
	{
		errBox( err.what() );
	}
}

void BaslerControlWindow::OnSize( UINT nType, int cx, int cy )
{
	CDialog::OnSize( nType, cx, cy );
	picture.redrawImage( this );
}

BaslerControlWindow::BaslerControlWindow( CWnd* pParent /*=NULL*/ ) : CDialogEx( IDD_BASLERCONTROL_DIALOG, pParent )
{
	m_hIcon = AfxGetApp()->LoadIcon( IDR_MAINFRAME );
}

void BaslerControlWindow::DoDataExchange( CDataExchange* pDX )
{
	CDialogEx::DoDataExchange( pDX );
}

BOOL BaslerControlWindow::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	ShowWindow( SW_SHOWMAXIMIZED );

	initializeControls();

	return TRUE;  // return TRUE  unless you set the focus to a control
}


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void BaslerControlWindow::OnPaint()
{
	//picture.drawBackground( this );
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR BaslerControlWindow::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void BaslerControlWindow::initializeControls()
{
	CMenu menu;
	menu.LoadMenu( IDR_MENU1 );
	SetMenu( &menu );

	HWND* temp = new HWND( GetSafeHwnd() );
	camera = new BaslerCameras( temp );
	int id = 1000;
	POINT pos = { 0,0 };
	settings.initialize( pos, id, this );
	settings.setSettings( camera->getDefaultSettings() );
	std::unordered_map<std::string, CFont*> fontDummy;
	std::vector<CToolTipCtrl*> toolTipDummy;
	stats.initialize( pos, this, id, fontDummy, toolTipDummy);
	saver.initialize( pos, id, this );
	POINT picPos = { 300, 0 };
	POINT dims = camera->getCameraDimensions();
	picture.initialize( picPos, this, id, dims.x + picPos.x + 100, dims.y + picPos.y);
	picture.updateGridSpecs( camera->getDefaultSettings().dimensions );
	picture.drawBackground( this );
	
}
