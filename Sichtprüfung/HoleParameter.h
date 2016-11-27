#ifndef HOLEPARAMETER_H
#define HOLEPARAMETER_H

#include "VerificationMethod.h"
#include "Parameter.h"

class HoleParameter : public VerificationMethod
{
public:

	HoleParameter();
	~HoleParameter();

	//Implementation of interface VerificationMethod
	bool run(const cv::Mat*img);
	//Implementation of interface VerificationMethod
	void setParameters(std::vector<Parameter> parameters);
	//Implementation of interface VerificationMethod
	std::vector<Parameter>parameters();
	//Implementation of interface VerificationMethod
	ResultGenerator::ResultMap results();


private:
	//minimal and maximal radius of detected circles
	int minRadius_;
	int maxRadius_;

};
#endif