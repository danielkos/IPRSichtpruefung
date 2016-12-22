#ifndef IDSCAMERA_H
#define IDSCAMERA_H

// Original code to get image from IDS camera was retrieved from the SimpleLive demo
// application from IDS. Code was altered for personal use to work with own program.
//
//===========================================================================//
//                                                                           //
//  Copyright (C) 2004 - 2016                                                //
//  IDS Imaging GmbH                                                         //
//  Dimbacherstr. 6-8                                                        //
//  D-74182 Obersulm-Willsbach                                               //
//                                                                           //
//  The information in this document is subject to change without            //
//  notice and should not be construed as a commitment by IDS Imaging GmbH.  //
//  IDS Imaging GmbH does not assume any responsibility for any errors       //
//  that may appear in this document.                                        //
//                                                                           //
//  This document, or source code, is provided solely as an example          //
//  of how to utilize IDS software libraries in a sample application.        //
//  IDS Imaging GmbH does not assume any responsibility for the use or       //
//  reliability of any portion of this document or the described software.   //
//                                                                           //
//  General permission to copy or modify, but not for profit, is hereby      //
//  granted,  provided that the above copyright notice is included and       //
//  reference made to the fact that reproduction privileges were granted	 //
//	by IDS Imaging GmbH.				                                     //
//                                                                           //
//  IDS cannot assume any responsibility for the use or misuse of any        //
//  portion of this software for other than its intended diagnostic purpose	 //
//  in calibrating and testing IDS manufactured cameras and software.		 //
//                                                                           //
//===========================================================================//
#include "uEye.h"

#include <QString>
#include <QSettings>

class IDSCamera
{
public:

	// Constructor
	IDSCamera();

	// Destructor
	virtual ~IDSCamera();

	// Extracts a single frame from the continuous video stream.
	void AcquireImage();

	// Appends the loaded camera parameters on the camera stream.
	// Calls LoadParameters() internally to read the .ini file with the
	// camera parameters
	void AppendParameters();
	
private:

	// The path to the .ini file with the camera parameters
	QString parameterFilePath;

	// uEye varibles
	HIDS	m_hCam;			// handle to camera
	HWND	m_hWndDisplay;	// handle to diplay window
	INT		m_Ret;			// return value of uEye SDK functions
	INT		m_nColorMode;	// Y8/RGB16/RGB24/REG32
	INT		m_nBitsPerPixel;// number of bits needed store one pixel
	INT		m_nSizeX;		// width of video 
	INT		m_nSizeY;		// height of video
	INT		m_nPosX;		// left offset of image
	INT		m_nPosY;		// right offset of image
	INT		m_lMemoryId;	// grabber memory - buffer ID
	char*	m_pcImageMemory;// grabber memory - pointer to buffer
	INT     m_nRenderMode;  // render  mode
	SENSORINFO m_sInfo;	    // sensor information struct
	

	// Opens a handle to a connected camera
	bool OpenCamera();

	// Returns the maximum image size of a single camera frame
	void GetMaxImageSize(INT *pnSizeX, INT *pnSizeY);

	// Exists the instance of the camera
	void ExitCamera();

	// Loads the camera parameters from an .ini file from the local file system
	void LoadParameters();

	// Initializes the camera
	INT InitCamera(HIDS *hCam, HWND hWnd);

};
#endif