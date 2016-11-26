#ifndef CALIBRATION_H
#define CALIBRATION_H

#include "VerificationMethod.h"
#include "Parameter.h"

namespace cv
{
	class Mat;
}

class Calibration : public VerificationMethod
{
public:
	Calibration();
	~Calibration();

	//Implementation of interface VerificationMethod
	bool run(const cv::Mat* img);
	//Implementation of interface VerificationMethod
	void setParameters(std::vector<Parameter> parameters);
	//Implementation of interface VerificationMethod
	std::vector<Parameter> parameters();

private:
	//Parameters for canny edge detection
	double cannyLowerThresh_;
	double cannyUpperThresh_;
	//Interations of the morph close operation
	int morphIterations_;
	//Size of contour to ignore
	int ignoreContourSize_;
	//Size of a contour in pixel
	int contourSize_;
};

#endif
