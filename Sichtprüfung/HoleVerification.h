#ifndef HOLEPARAMETER_H
#define HOLEPARAMETER_H

#include "VerificationMethod.h"
#include "Parameter.h"

#include <opencv2\opencv.hpp>

class HoleVerification : public VerificationMethod
{
public:

	HoleVerification();
	virtual ~HoleVerification();

	// Implementation of interface VerificationMethod
	bool run(const cv::Mat*img);
	// Implementation of interface VerificationMethod
	void setParameters(std::vector<Parameter> parameters);
	// Implementation of interface VerificationMethod
	std::vector<Parameter>parameters();
	// Implementation of interface VerificationMethod
	ResultGenerator::ResultMap results();


private:

	// Minimal and maximal radius of circles to look for in the image (in pixel)
	int minRadius_;
	int maxRadius_;

	// Tolerance value, how close the center of a detected circle and the center
	// of the object need to be, to be reported as equal (tolerance in pixel)
	double centerEqualTolerance_;

	//Parameters for canny edge detection
	double cannyLowerThresh_;
	double cannyUpperThresh_;
	//Interations of the morph close operation
	int morphIterations_;

	double houghUpperCannyThresh_;
	double centerThresh_;

	// Vector with the detected circles from the Hough Transformation:
	// Vec3f content: first two values define the x and y coordinate of
	// the center of the circle. The third value defines the radius of 
	// the circle (radius size in pixel)
	std::vector<cv::Vec3f> circles_;

	// If the center of the detected circles are "equal" to the center of the object
	// see also centerTolerance_ parameter
	std::vector<bool> circlesCentered_;

};
#endif