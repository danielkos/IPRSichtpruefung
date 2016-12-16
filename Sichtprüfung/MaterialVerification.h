#ifndef MATERIALVERIFICATION_H
#define MATERIALVERIFICATION_H

#include "VerificationMethod.h"
#include "Parameter.h"

class MaterialVerification : public VerificationMethod
{
public:

MaterialVerification();
~MaterialVerification();

//Implementation of interface VerificationMethod
bool run(const cv::Mat*img);
//Implementation of interface VerificationMethod
void setParameters(std::vector<Parameter> parameters);
//Implementation of interface VerificationMethod
std::vector<Parameter>parameters();
//Implementation of interface VerificationMethod
ResultGenerator::ResultMap results();


private:
	//minimal value of pixel considered as reflection
	int minBrightness_;
	// ratio between sides of rectangle higher than ratio_ is describing metall reflection
	float ratio_;
	//if material is metal
	bool materialMetal_;
	//amount of pixels within biggest reflection area
	int pixelAmount_;
};
#endif