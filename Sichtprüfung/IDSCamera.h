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

#include <opencv2\opencv.hpp>
#include <QImage>
#include <mutex>
#include <QObject>


class IDSCamera : public QObject
{
	Q_OBJECT

public:

	// Constructor
	IDSCamera();

	// Destructor
	virtual ~IDSCamera();

	// Opens a handle to a connected camera
	bool OpenCamera();
	
	// Returns the current camera frame
	cv::Mat currentImage();

	// Extracts a single frame from the continuous video stream.
	void AcquireImage();

	// Extracts a single frame from the continuous video stream, but also
	// applies the parameters from the config file
	void aquireImageWithParams(const std::string& cameraConfigPath = "");

	// Stores the current camera frame on the local file system
	void storeImage();

	// Appends the loaded camera parameters on the camera stream.
	// Calls LoadParameters() internally to read the .ini file with the
	// camera parameters
	void AppendParameters(const std::string& cameraConfigPath = "");
	
	// Kills the camera video stream
	void terminateCameraStream();

	// Exists the instance of the camera
	void ExitCamera();

Q_SIGNALS:

	void newCameraImage(cv::Mat* img);

	
private:

	// Time delay (in milliseconds) between the recording of two camera frames.
	const long CAMERA_RECORD_DELAY = 500;

	// The path to the .ini file with the camera parameters
	std::string parameterFilePath_;

	// uEye varibles
	HIDS	m_hCam;			// handle to camera
	INT		m_nSizeX;
	INT		m_nSizeY;
	INT		m_Ret;			// return value of uEye SDK functions
	INT		m_nColorMode;	// Y8/RGB16/RGB24/REG32
	INT		m_nBitsPerPixel;// number of bits needed store one pixel
	INT		m_lMemoryId;	// grabber memory - buffer ID
	char*	m_pcImageMemory;// grabber memory - pointer to buffer
	INT     m_nRenderMode;  // render  mode
	SENSORINFO m_sInfo;	    // sensor information struct

	// If the camera video stream should be terminated or not
	bool terminate_;
	
	// Mutex lock, because this camera class runs in a separate thread (see MainGui)
	std::mutex imgLock_;
	
	// The current camera frame
	IplImage* currentImg_;

	// Returns the maximum image size of a single camera frame
	void GetMaxImageSize(INT *pnSizeX, INT *pnSizeY);



	// Loads the camera parameters from an .ini file from the local file system
	void LoadParameters();

	// Initializes the camera
	INT InitCamera(HIDS *hCam, HWND hWnd);

};
Q_DECLARE_METATYPE(cv::Mat*);
#endif