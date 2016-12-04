#ifndef HOLEPARAMETER_H
#define HOLEPARAMETER_H

#include "VerificationMethod.h"
#include "Parameter.h"

#include <opencv2\opencv.hpp>

class HoleVerification : public VerificationMethod
{
public:

	HoleVerification();
	~HoleVerification();

	// Implementation of interface VerificationMethod
	bool run(const cv::Mat*img);
	// Implementation of interface VerificationMethod
	void setParameters(std::vector<Parameter> parameters);
	// Implementation of interface VerificationMethod
	std::vector<Parameter>parameters();
	// Implementation of interface VerificationMethod
	ResultGenerator::ResultMap results();


private:

	// Minimal and maximal radius of circles to look for in the image
	int minRadius_;
	int maxRadius_;

	// Vector with the detected circles from the Hough Transformation:
	// Vec3f content: first two values define the x and y coordinate of
	// the center of the circle. The third value defines the radius of 
	// the circle (radius size in pixel)
	std::vector<cv::Vec3f> circles;

};
#endif