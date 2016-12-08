#include "ShapeVerification.h"
#include <opencv2\opencv.hpp>

ShapeVerification::ShapeVerification()
{
	shapeSize_ = QSize(0, 0);
	drawLines_ = false;
}

ShapeVerification::~ShapeVerification()
{
}

void ShapeVerification::setParameters(std::vector<Parameter> parameters)
{
	//Check if the size of the returned paramers is right
	//The order is determined by parameters()
	if (parameters.size() == parametersSize_)
	{
		cannyLowerThresh_ = parameters[0].value_.toDouble();
		cannyUpperThresh_ = parameters[1].value_.toDouble();
		morphIterations_ = parameters[2].value_.toInt();
		ignoreContourSize_ = parameters[3].value_.toInt();
		contourSize_ = parameters[4].value_.toInt();
		drawLines_ = parameters[5].value_.toBool();
	}
}

std::vector<Parameter> ShapeVerification::parameters()
{
	
	std::vector<Parameter> parameters;
	
	Parameter param;
	//Setup parameter, name will be displayed on gui
	param.setUp("Lower Threshold", QVariant(cannyLowerThresh_), QMetaType::Double);
	parameters.push_back(param);

	param.setUp("Upper Threshold", QVariant(cannyUpperThresh_), QMetaType::Double);
	parameters.push_back(param);

	param.setUp("Morph Close Iterations", QVariant(morphIterations_), QMetaType::Int);
	parameters.push_back(param);

	param.setUp("Ignore Contour Size", QVariant(ignoreContourSize_), QMetaType::Int);
	parameters.push_back(param);

	param.setUp("Contour Size(pixel)", QVariant(contourSize_), QMetaType::Int);
	parameters.push_back(param);

	param.setUp("Draw bounding rect", QVariant(drawLines_), QMetaType::Bool);
	parameters.push_back(param);

	parametersSize_ = parameters.size();

	return parameters;
}

ResultGenerator::ResultMap ShapeVerification::results()
{
	ResultGenerator::ResultMap results;
	Parameter param;

	param.setUp("Object size", shapeSize_, QMetaType::QSize);

	//Set a paramter definied for the generator
	results.insert(ResultGenerator::ResultPair(ResultGenerator::Results::RES_OBJ_SIZE, param));

	return results;
}

bool ShapeVerification::run(const cv::Mat* img)
{
	Calibration::setParameters(parameters());

	bool ret = Calibration::run(img);

	if (ret)
	{
		cv::RotatedRect* rect = Calibration::boundingBox();
		shapeSize_ = QSize(rect->size.width, rect->size.height);
	}

	return ret;
}