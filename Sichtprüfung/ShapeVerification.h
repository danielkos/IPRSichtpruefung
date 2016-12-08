#ifndef SHAPE_VERIFICATION_H
#define SHAPE_VERIFICATION_H

#include <QSize>
#include "Calibration.h"
#include "Parameter.h"

namespace cv
{
	class Mat;
}

class ShapeVerification : public Calibration
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
};
#endif // !SHAPE_VERIFICATION_H
