﻿// Created by Mark Brown
#include "stdafx.h"
#include "PixisCamera.h"
#include "Matrix.h"
#include "Single_Camera_Control_App.h"
#include <memory> 
#include "CodeTimer.h"


PixisCamera::PixisCamera ( bool safemode ) : flume ( safemode )
{
	flume.InitializeLibrary ( );
}


PixisCamera::~PixisCamera ( )
{
	flume.CloseCamera ( );
	flume.UninitializeLibrary ( );
}


double PixisCamera::getExposure ( )
{
	return flume.getExposure ( );
}


POINT PixisCamera::getCameraDimensions ( )
{
	auto constraint = flume.getCameraRoiConstraints ( );
	return { (long)constraint->width_constraint.maximum, (long)constraint->height_constraint.maximum };
}


UINT PixisCamera::getRepCounts ( )
{
	return repCounts;
}


UINT __stdcall PixisCamera::pictureWatcherProcedure ( void* inputPtr )
{
	pictureWatcherInput* input = ( pictureWatcherInput* ) inputPtr;
	auto stride = input->flume->getReadoutStride ( );
	auto rois = input->flume->getRois ( );
	input->flume->startAcquisition();
	CodeTimer timer;
	UINT counter = 0;
	try
	{
		while ( *input->running )
		{
			timer.tick(str(counter));
			auto data = input->flume->acquisitionUpdate();
			if (data.readout_count == 0)
			{
				continue;
			}
			//auto data = input->flume->Aquire ( );
			timer.tick(str(counter)+"f");
			Matrix<long>* dataM = new Matrix<long> (
				int ( rois[ 0 ].height / rois[ 0 ].y_binning ), int ( rois[ 0 ].width / rois[ 0 ].x_binning ),
				std::vector<long> ( (USHORT*) data.initial_readout,
				(USHORT*) data.initial_readout + stride / sizeof ( USHORT ) ) );
			input->parent->PostMessageA ( PIC_READY, dataM->size ( ), reinterpret_cast<LPARAM> ( dataM ) );
		}
	}
	catch ( Error& err )
	{
		if ( *input->running )
		{
			errBox ( err.what ( ) );
		}
		// else probably just something related to stopAcquisition timing not working out.
	}
	errBox(timer.getTimingMessage());
	return 0;
}


void PixisCamera::armCamera ( )
{
	pictureWatcherInput* input;
	input = new pictureWatcherInput;
	input->flume = &flume;
	input->parent = parentWindow;
	input->repCounts = &repCounts;
	input->running = &runningFlag;
	UINT threadID;
	runningFlag = true;
	auto threadHandle = (HANDLE)_beginthreadex ( 0, 0, PixisCamera::pictureWatcherProcedure, (void*) input, 0, &threadID );
	//WaitForSingleObject ( threadHandle, INFINITE );
}


void PixisCamera::disarm ( )
{
	runningFlag = false;
	flume.StopAquisition ( );
}


void PixisCamera::setParameters ( CameraSettings settings )
{
	// todo
	try
	{
		repCounts = settings.repCount;
		if (settings.cameraMode == "Continuous Acquisition")
		{
			flume.setRepetitions(LLONG_MAX);
		}
		else
		{
			flume.setRepetitions(settings.repCount);
		}
		flume.setExposure ( settings.exposureTime );
		//
		flume.setAmplifierSettings();
		flume.setReadoutSettings();
		//
		if ( settings.triggerMode == "External Trigger" )
		{
			flume.setStandardTrigger ( );
		}
		else
		{
			flume.turnOffTrigger ( );
		}

		// Handle Region of Interest
		auto region = flume.getRois ( );
		region[ 0 ].height = settings.dimensions.vertRawPixelNumber;
		region[ 0 ].width = settings.dimensions.horRawPixelNumber;

		region[ 0 ].x = settings.dimensions.leftBorder;
		region[ 0 ].y = settings.dimensions.topBorder;

		region[ 0 ].x_binning = settings.dimensions.horPixelsPerBin;
		region[ 0 ].y_binning = settings.dimensions.vertPixelsPerBin;
		flume.setRois ( region );		
		flume.commitParams ( );

		flume.displayTrigParams();
		
	}
	catch ( Error& err )
	{
		errBox ( err.what ( ) );
	}
}


void PixisCamera::setTemperatureSetPoint ( double temperature )
{
	//flume.unlockTemperature();
	flume.setTemperatureSetPoint ( temperature );
}


double PixisCamera::getCurrentTemperature ( )
{
	flume.commitParams();
	return flume.getCurrentTemperature ( );
}


std::string PixisCamera::getTemperatureStatus ( )
{
	return flume.getTemperatureStatus ( );
}


double PixisCamera::getSetTemperature ( )
{
	
	return flume.getTemperatureSetPoint ( );
}



CameraSettings PixisCamera::getDefaultSettings ( )
{
	// todo
	return CameraSettings ( );
}


void PixisCamera::initialize ( CWnd* parent )
{
	parentWindow = parent;
	try
	{
		flume.OpenFirstCamera ( );
		camID = flume.GetCameraID ( );
	}
	catch ( Error& err )
	{
		errBox ( "No Pixis Camera Detected (" + err.whatStr() + "), opening demo camera!" );
		flume.ConnectAndOpenDemoCamera ( camID );
	}
}

