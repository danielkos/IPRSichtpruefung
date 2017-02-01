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

protected:
	//Calibration success
	bool calibSuccess_;
	//Number of captured img for calibration
	int numImgs_;
	//Number of corners in x and y
	int numCornersH_;
	int numConrersV_;
	//Number of squares
	int numSquares_;
	//Size of a Square
	int sizeSquare_;
	//Size of the whole board
	cv::Size boardSize_;
	//Corner location in 3D
	std::vector<std::vector<cv::Point3f> > objectPoints_; 
	//Corner location in 2D
	std::vector<std::vector<cv::Point2f> > imagePoints_; 
	//Corners on the chessboard
	std::vector<cv::Point2f> corners_;
};

#endif
