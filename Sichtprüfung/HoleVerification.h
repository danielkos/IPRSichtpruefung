#ifndef HOLEVERIFICATION_H
#define HOLEVERIFICATION_H

#include "VerificationMethod.h"

class HoleVerification : public VerificationMethod
{
public:
	HoleVerification();
	~HoleVerification();

	bool run(const cv::Mat* img);
};

#endif // HOLEVERIFICATION_H
