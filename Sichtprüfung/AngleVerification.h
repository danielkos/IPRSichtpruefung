#ifndef ANGLEVERIFICATION_H
#define ANGLEVERIFICATION_H

#include "VerificationMethod.h"
#include "Parameter.h"

#include <opencv2\opencv.hpp>

// PI
#define M_PI 3.14159265358979323846

class AngleVerification : public VerificationMethod
{
public:

	AngleVerification();
	~AngleVerification();

	//Implementation of interface VerificationMethod
	bool run(const cv::Mat* img);
	//Implementation of interface VerificationMethod
	void setParameters(std::vector<Parameter> parameters);
	//Implementation of interface VerificationMethod
	std::vector<Parameter>parameters();
	//Implementation of interface VerificationMethod
	ResultGenerator::ResultMap results();


private:
	int ResolutionWidth_;

	// The measured angle for the left side of the object
	double angleLeft_;

	// The measured angle for the right side of the object
	double angleRight_;
};
#endif