#ifndef SHAPE_VERIFICATION_H
#define SHAPE_VERIFICATION_H

#include <QSize>
#include "VerificationMethod.h"
#include "Parameter.h"

namespace cv
{
	class Mat;
}

class ShapeVerification : public VerificationMethod
{
public:
	ShapeVerification(); 
	virtual ~ShapeVerification();

	// Implementation of interface VerificationMethod
	bool run(const cv::Mat*img);
	//Implementation of interface VerificationMethod
	void setParameters(std::vector<Parameter> parameters);
	//Implementation of interface VerificationMethod
	std::vector<Parameter> parameters();
	//Implementation of interface VerificationMethod
	ResultGenerator::ResultMap results();

private:
	//Size of the object
	QSize shapeSize_;

	cv::RotatedRect boundingBox_;
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
#endif // SHAPE_VERIFICATION_H
