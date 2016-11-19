#ifndef HOLEVERIFICATION_H
#define HOLEVERIFICATION_H

#include "VerificationMethod.h"

/**
* \brief Method to verify the holes
* Implements VerificationMethod
*/

class HoleVerification : public VerificationMethod
{
public:
	HoleVerification();
	~HoleVerification();
	
	//Implementation of abstract function
	bool run(const cv::Mat* img);
};

#endif // HOLEVERIFICATION_H
