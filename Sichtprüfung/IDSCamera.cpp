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
#include "IDSCamera.h"
#include "Logger.h"
#include "Configs.h"
#include <opencv2\core\mat.hpp>

#include <QSettings>

#include <string>
#include <locale>
#include <codecvt>

IDSCamera::IDSCamera()
{
	parameterFilePath_ = paths::getExecutablePath() + paths::configFolder + paths::cameraFolder + filenames::cameraConfig;

	m_pcImageMemory = NULL;
	currentImg_ = NULL;
	m_lMemoryId = 0;
	m_hCam = 0;
	m_nSizeX = 0;
	m_nSizeY = 0;
	m_nRenderMode = IS_RENDER_NORMAL;

	terminate_ = false;
}

IDSCamera::~IDSCamera()
{
	ExitCamera();
}

/*cv::Mat IDSCamera::currentImage()
{
	cv::Mat img;
	imgLock_.lock();
	img = cv::cvarrToMat(currentImg_);
	imgLock_.unlock();
		
	//cvShowImage("A", &img);
	//cv::waitKey(1);

	return img;
}*/

cv::Mat IDSCamera::currentImage()
{
	cv::Mat img;
	imgLock_.lock();

	if (CV_IS_IMAGE(currentImg_))
	{
		int depth = IPL2CV_DEPTH(currentImg_->depth);
		size_t esz;
		img.cols = currentImg_->width;
		img.rows = currentImg_->height;
		
		img.flags = cv::Mat::MAGIC_VAL + CV_MAKETYPE(depth, currentImg_->nChannels); //magic_val from prior cv versions
		esz = CV_ELEM_SIZE(img.flags);
		img.step[0] = currentImg_->widthStep;

		img.datastart = (uchar*)currentImg_->imageData;
		img.data = (uchar*)currentImg_->imageData;
		img.datalimit = img.datastart + img.step.p[0] * img.rows;
		img.dataend = img. datastart + img.step.p[0] * (img.rows - 1) + esz * img.cols;

		img.flags |= (img.cols*esz == img.step.p[0] || img.rows == 1 ? CV_MAT_CONT_FLAG : 0);
		img.step[1] = esz;
	}

	imgLock_.unlock();
	return img;
}

void IDSCamera::AcquireImage()
{
	int success = -1;

	if (m_hCam == 0)
	{
		OpenCamera();
	}
	
	if (m_hCam != 0)
	{
		if (is_FreezeVideo(m_hCam, IS_WAIT) == IS_SUCCESS)
		{
			if (m_pcImageMemory)
			{
				imgLock_.lock();

				currentImg_ = cvCreateImageHeader(cvSize(m_nSizeX, m_nSizeY), IPL_DEPTH_8U, 4);
				currentImg_->nSize = sizeof(IplImage);
				currentImg_->dataOrder = 0; //has to be 0 for intervealed images
				currentImg_->depth = IPL_DEPTH_8U;
				currentImg_->ID = 0; //actually ignored

				currentImg_->width = m_nSizeX;
				currentImg_->height = m_nSizeY;
				currentImg_->nChannels = 4;
				currentImg_->widthStep = currentImg_->nChannels * currentImg_->width;
				currentImg_->imageSize = currentImg_->height * currentImg_->widthStep;

				currentImg_->origin = 0; //top-left corner
				currentImg_->maskROI = NULL;
				currentImg_->roi = NULL;
				currentImg_->tileInfo = NULL;

				currentImg_->imageId = NULL;
				currentImg_->imageData = m_pcImageMemory;
				currentImg_->imageDataOrigin = m_pcImageMemory;

				imgLock_.unlock();

				Q_EMIT newCameraImage(&currentImage());
			}
		}
	}
}

void IDSCamera::storeImage()
{
	IMAGE_FILE_PARAMS ImageFileParams;
	ImageFileParams.pwchFileName = NULL;
	ImageFileParams.pnImageID = NULL;
	ImageFileParams.ppcImageMem = NULL;
	ImageFileParams.nQuality = 0;
	ImageFileParams.pwchFileName = L"C:\\Users\\Sven\\Desktop\\test.jpg";	// Just for testing
	ImageFileParams.nFileType = IS_IMG_JPG;
	ImageFileParams.nQuality = 80;

	is_ImageFile(m_hCam, IS_IMAGE_FILE_CMD_SAVE, (void*)&ImageFileParams,
		sizeof(ImageFileParams));
}


void IDSCamera::GetMaxImageSize(INT *pnSizeX, INT *pnSizeY)
{
	// Check if the camera supports an arbitrary AOI
	// Only the ueye xs does not support an arbitrary AOI
	INT nAOISupported = 0;
	BOOL bAOISupported = TRUE;
	if (is_ImageFormat(m_hCam,
		IMGFRMT_CMD_GET_ARBITRARY_AOI_SUPPORTED,
		(void*)&nAOISupported,
		sizeof(nAOISupported)) == IS_SUCCESS)
	{
		bAOISupported = (nAOISupported != 0);
	}

	if (bAOISupported)
	{
		// All other sensors
		// Get maximum image size
		SENSORINFO sInfo;
		is_GetSensorInfo(m_hCam, &sInfo);
		*pnSizeX = sInfo.nMaxWidth;
		*pnSizeY = sInfo.nMaxHeight;
	}
	else
	{
		// Only ueye xs
		// Get image size of the current format
		IS_SIZE_2D imageSize;
		is_AOI(m_hCam, IS_AOI_IMAGE_GET_SIZE, (void*)&imageSize, sizeof(imageSize));

		*pnSizeX = imageSize.s32Width;
		*pnSizeX = imageSize.s32Height;
	}
}


bool IDSCamera::OpenCamera()
{
	if (m_hCam != 0)
	{
		//free old image mem.
		is_FreeImageMem(m_hCam, m_pcImageMemory, m_lMemoryId);
		is_ExitCamera(m_hCam);
	}

	// init camera
	m_hCam = (HIDS)0;						// open next camera
	m_Ret = InitCamera(&m_hCam, NULL);		// init camera - no window handle required

	if (m_Ret == IS_SUCCESS)
	{
		// Get sensor info
		is_GetSensorInfo(m_hCam, &m_sInfo);

		GetMaxImageSize(&m_nSizeX, &m_nSizeY);

		// setup the color depth to the current windows setting
		//is_GetColorDepth(m_hCam, &m_nBitsPerPixel, &m_nColorMode); //Probably dont need this, because we need RGBA32
		m_nColorMode = IS_CM_BGRA8_PACKED; // opencv uses  this mode
		is_SetColorMode(m_hCam, m_nColorMode);

		// memory initialization
		is_AllocImageMem(m_hCam,
			m_nSizeX,
			m_nSizeY,
			m_nBitsPerPixel,
			&m_pcImageMemory,
			&m_lMemoryId);
		is_SetImageMem(m_hCam, m_pcImageMemory, m_lMemoryId);	// set memory active

		// display initialization
		IS_SIZE_2D imageSize;
		imageSize.s32Width = m_nSizeX;
		imageSize.s32Height = m_nSizeY;

		is_AOI(m_hCam, IS_AOI_IMAGE_SET_SIZE, (void*)&imageSize, sizeof(imageSize));

		is_SetDisplayMode(m_hCam, IS_SET_DM_DIB);

		// enable the dialog based error report
		m_Ret = is_SetErrorReport(m_hCam, IS_ENABLE_ERR_REP); //IS_DISABLE_ERR_REP);
		if (m_Ret != IS_SUCCESS)
		{
			LOGGER.log("Can not enable the automatic uEye error report!");
			return false;
		}

		LoadParameters();
	}
	else
	{
		LOGGER.log("Can not open uEye camera!");
		return false;
	}

	return true;
}


void IDSCamera::ExitCamera()
{
	if (m_hCam != 0)
	{
		// Disable messages
		is_EnableMessage(m_hCam, IS_FRAME, NULL);

		// Stop live video
		is_StopLiveVideo(m_hCam, IS_WAIT);

		// Free the allocated buffer
		if (m_pcImageMemory != NULL)
		{ 
			is_FreeImageMem(m_hCam, m_pcImageMemory, m_lMemoryId);
		}
			
		m_pcImageMemory = NULL;

		// Close camera
		is_ExitCamera(m_hCam);
		m_hCam = NULL;
	}
}


void IDSCamera::AppendParameters(const std::string& cameraConfigPath)
{
	if (!cameraConfigPath.empty())
	{
		parameterFilePath_ = cameraConfigPath;
	}
	
	if (m_hCam == 0)
	{
		OpenCamera();
	}

	// Append the loaded parameters on the camera frames
	if (m_hCam != 0)
	{
		//If the conversion should not worl then change &path to &parameterFilePath_
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		std::wstring path = converter.from_bytes(parameterFilePath_); 

		if (is_ParameterSet(m_hCam, IS_PARAMETERSET_CMD_LOAD_FILE, &path, NULL) == IS_SUCCESS && m_pcImageMemory != NULL)
		{
			// determine live capture
			BOOL bWasLive = (BOOL)(is_CaptureVideo(m_hCam, IS_GET_LIVE));
			if (bWasLive)
			{
				is_StopLiveVideo(m_hCam, IS_FORCE_VIDEO_STOP);
			}

			// realloc image mem with actual sizes and depth.
			imgLock_.lock();
			is_FreeImageMem(m_hCam, m_pcImageMemory, m_lMemoryId);
			imgLock_.unlock();

			IS_SIZE_2D imageSize;
			is_AOI(m_hCam, IS_AOI_IMAGE_GET_SIZE, (void*)&imageSize, sizeof(imageSize));

			INT nAllocSizeX = 0;
			INT nAllocSizeY = 0;

			m_nSizeX = nAllocSizeX = imageSize.s32Width;
			m_nSizeY = nAllocSizeY = imageSize.s32Height;

			UINT nAbsPosX = 0;
			UINT nAbsPosY = 0;

			// absolute pos?
			is_AOI(m_hCam, IS_AOI_IMAGE_GET_POS_X_ABS, (void*)&nAbsPosX, sizeof(nAbsPosX));
			is_AOI(m_hCam, IS_AOI_IMAGE_GET_POS_Y_ABS, (void*)&nAbsPosY, sizeof(nAbsPosY));

			if (nAbsPosX)
			{
				nAllocSizeX = m_sInfo.nMaxWidth;
			}
			if (nAbsPosY)
			{
				nAllocSizeY = m_sInfo.nMaxHeight;
			}

			switch (is_SetColorMode(m_hCam, IS_GET_COLOR_MODE))
			{
			case IS_CM_RGBA12_UNPACKED:
			case IS_CM_BGRA12_UNPACKED:
				m_nBitsPerPixel = 64;
				break;

			case IS_CM_RGB12_UNPACKED:
			case IS_CM_BGR12_UNPACKED:
			case IS_CM_RGB10_UNPACKED:
			case IS_CM_BGR10_UNPACKED:
				m_nBitsPerPixel = 48;
				break;

			case IS_CM_RGBA8_PACKED:
			case IS_CM_BGRA8_PACKED:
			case IS_CM_RGB10_PACKED:
			case IS_CM_BGR10_PACKED:
			case IS_CM_RGBY8_PACKED:
			case IS_CM_BGRY8_PACKED:
				m_nBitsPerPixel = 32;
				break;

			case IS_CM_RGB8_PACKED:
			case IS_CM_BGR8_PACKED:
				m_nBitsPerPixel = 24;
				break;

			case IS_CM_BGR565_PACKED:
			case IS_CM_UYVY_PACKED:
			case IS_CM_CBYCRY_PACKED:
				m_nBitsPerPixel = 16;
				break;

			case IS_CM_BGR5_PACKED:
				m_nBitsPerPixel = 15;
				break;

			case IS_CM_MONO16:
			case IS_CM_SENSOR_RAW16:
			case IS_CM_MONO12:
			case IS_CM_SENSOR_RAW12:
			case IS_CM_MONO10:
			case IS_CM_SENSOR_RAW10:
				m_nBitsPerPixel = 16;
				break;

			case IS_CM_RGB8_PLANAR:
				m_nBitsPerPixel = 24;
				break;

			case IS_CM_MONO8:
			case IS_CM_SENSOR_RAW8:
			default:
				m_nBitsPerPixel = 8;
				break;
			}

			// memory initialization
			imgLock_.lock();
			is_AllocImageMem(m_hCam, nAllocSizeX, nAllocSizeY, m_nBitsPerPixel, &m_pcImageMemory, &m_lMemoryId);
			imgLock_.unlock();

			// set memory active
			is_SetImageMem(m_hCam, m_pcImageMemory, m_lMemoryId);

			// display initialization
			imageSize.s32Width = m_nSizeX;
			imageSize.s32Height = m_nSizeY;

			// Set the AOI with the correct size
			is_AOI(m_hCam, IS_AOI_IMAGE_SET_SIZE, (void*)&imageSize, sizeof(imageSize));

			// run live image again
			if (bWasLive)
			{ 
				is_CaptureVideo(m_hCam, IS_DONT_WAIT);
			}
		}
	}
}

void IDSCamera::terminateCameraStream()
{
	terminate_ = true;
}



void IDSCamera::aquireImageWithParams(const std::string& cameraConfigPath)
{
	AppendParameters(cameraConfigPath);
	
	while (!terminate_)
	{
		AcquireImage();
	} 
}


void IDSCamera::LoadParameters()
{
	if (m_hCam == NULL)
	{
		return;
	}

	int nGainR, nGainG, nGainB, nGainM;

	nGainM = is_SetHardwareGain(m_hCam, (int)IS_GET_DEFAULT_MASTER, -1, -1, -1);
	nGainR = is_SetHardwareGain(m_hCam, (int)IS_GET_DEFAULT_RED, -1, -1, -1);
	nGainG = is_SetHardwareGain(m_hCam, (int)IS_GET_DEFAULT_GREEN, -1, -1, -1);
	nGainB = is_SetHardwareGain(m_hCam, (int)IS_GET_DEFAULT_BLUE, -1, -1, -1);

	// Read parameters of ini file with Qt
	QSettings cameraParameters (QString::fromStdString(parameterFilePath_), QSettings::IniFormat);
	
	int nPixelClock = cameraParameters.value("Timing/Pixelclock", 10).toInt();
	double nFrameRate = cameraParameters.value("Timing/Framerate", 5).toDouble();
	double nExposureTime = cameraParameters.value("Timing/Exposure", 100).toDouble();
	nGainM = cameraParameters.value("Gain/Master", nGainM).toInt();
	nGainR = cameraParameters.value("Gain/Red", nGainR).toInt();
	nGainG = cameraParameters.value("Gain/Green", nGainG).toInt();
	nGainB = cameraParameters.value("Gain/Blue", nGainB).toInt();
	int nColorCorrection = cameraParameters.value("Processing/color correction", IS_CCOR_DISABLE).toInt();
	int nBayerMode = cameraParameters.value("Processing/Bayer Conversion", IS_SET_BAYER_CV_NORMAL).toInt();

	m_Ret = is_PixelClock(m_hCam, IS_PIXELCLOCK_CMD_SET, (void*)&nPixelClock, sizeof(nPixelClock));
	m_Ret = is_SetFrameRate(m_hCam, (double)nFrameRate, NULL);

	double dTemp = 0.0;
	dTemp = (double)nExposureTime;
	m_Ret = is_Exposure(m_hCam, IS_EXPOSURE_CMD_SET_EXPOSURE, (void*)&dTemp, sizeof(dTemp));

	m_Ret = is_SetHardwareGain(m_hCam, nGainM, nGainR, nGainG, nGainB);
	m_Ret = is_SetColorCorrection(m_hCam, nColorCorrection, NULL);
	m_Ret = is_SetBayerConversion(m_hCam, nBayerMode);
}



INT IDSCamera::InitCamera(HIDS *hCam, HWND hWnd)
{
	INT nRet = is_InitCamera(hCam, hWnd);
	/************************************************************************************************/
	/*                                                                                              */
	/*  If the camera returns with "IS_STARTER_FW_UPLOAD_NEEDED", an upload of a new firmware       */
	/*  is necessary. This upload can take several seconds. We recommend to check the required      */
	/*  time with the function is_GetDuration().                                                    */
	/*                                                                                              */
	/*  In this case, the camera can only be opened if the flag "IS_ALLOW_STARTER_FW_UPLOAD"        */
	/*  is "OR"-ed to m_hCam. This flag allows an automatic upload of the firmware.                 */
	/*                                                                                              */
	/************************************************************************************************/
	if (nRet == IS_STARTER_FW_UPLOAD_NEEDED)
	{
		// Time for the firmware upload = 25 seconds by default
		INT nUploadTime = 25000;
		is_GetDuration(*hCam, IS_STARTER_FW_UPLOAD, &nUploadTime);
		
		LOGGER.log("This camera requires a new firmware!");

		// Try again to open the camera. This time we allow the automatic upload of the firmware by
		// specifying "IS_ALLOW_STARTER_FIRMWARE_UPLOAD"
		*hCam = (HIDS)(((INT)*hCam) | IS_ALLOW_STARTER_FW_UPLOAD);
		nRet = is_InitCamera(hCam, hWnd);
	}

	return nRet;
}

