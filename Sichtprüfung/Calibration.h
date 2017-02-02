#ifndef CALIBRATION_H
#define CALIBRATION_H

#include "VerificationMethod.h"
#include "Parameter.h"
#include "IDSCamera.h"
#include <opencv2\opencv.hpp>

namespace cv
{
	class Mat;
}

/*
 * \brief Method to calibrate a camera. The camera is calibrated by using a chessboard
 *			calibration pattern.
 *
 * See http://docs.opencv.org/2.4/modules/calib3d/doc/camera_calibration_and_3d_reconstruction.html
 * for more information about the calibration process with OpenCV.
 */
class Calibration : public VerificationMethod
{

public:
	Calibration();
	virtual ~Calibration();

	//Implementation of interface VerificationMethod
	bool run(const cv::Mat* img);
	//Implementation of interface VerificationMethod
	void setParameters(std::vector<Parameter> parameters);
	//Implementation of interface VerificationMethod
	std::vector<Parameter> parameters();
	//Implementation of interface VerificationMethod
	ResultGenerator::ResultMap results();

private:

	// The name of the window that displays the current calibration image
	const std::string CALIB_WINDOW_NAME = "Calibration Image";

	// Calibration success
	bool calibSuccess_;
	// Number of images that should be captured and used for calibration
	int numImgs_;
	// Number of corners in x and y of inner squares
	int numCornersH_;
	int numConrersV_;
	// Size of a one square in mm
	double sizeSquare_;
	// Size of the whole board
	cv::Size boardSize_;
	// Corner location in 2D
	std::vector<std::vector<cv::Point2f> > imagePoints_; 
	// Corners on the chessboard
	std::vector<cv::Point2f> corners_;

	// The calibration error
	double calibrationError_;
};

#endif
