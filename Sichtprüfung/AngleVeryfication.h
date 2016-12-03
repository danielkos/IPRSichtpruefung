#ifndef ANGLEVERYFICATION_H
#define ANGLEVERYFICATION_H

#include "VerificationMethod.h"
#include "Parameter.h"
#include <opencv2\opencv.hpp>

class AngleVeryfication : public VerificationMethod
{
public:

	AngleVeryfication();
	~AngleVeryfication();

	//Implementation of interface VerificationMethod
	bool run(const cv::Mat*img);
	//Implementation of interface VerificationMethod
	void setParameters(std::vector<Parameter> parameters);
	//Implementation of interface VerificationMethod
	std::vector<Parameter>parameters();
	//Implementation of interface VerificationMethod
	ResultGenerator::ResultMap results();


private:
	int ResolutionWidth_;
};
#endif