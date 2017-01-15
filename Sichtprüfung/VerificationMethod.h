#ifndef VERIFICATIONMETHOD_H
#define VERIFICATIONMETHOD_H

#include "Parameter.h"
#include "ResultGenerator.h"

#include <opencv2\opencv.hpp>

namespace cv
{
	class Mat;
}

/**
* \brief Interface for verification methods
*/
class VerificationMethod
{
public:
	VerificationMethod();
	virtual ~VerificationMethod();

	/**
	* \brief Pure abstract function which applies the method
	*/
	virtual bool run(const cv::Mat* img) = 0;

	void initializeResultImage(const cv::Mat* img);

	void drawPoint(cv::Point2f& point, const cv::Scalar& color);

	void drawLine(cv::Point2f& start, cv::Point2f& end, const cv::Scalar& color);

	void drawCircle(cv::Point2f& center, size_t radius, const cv::Scalar& color);

	void drawContour(cv::InputArrayOfArrays& contours, size_t index, const cv::Scalar& color);

	void drawRectangle(cv::Point2i& corner1, cv::Point2i& corner2, const cv::Scalar&Color);

	/**
	* \brief Pure abstract function which set the parameters
	*/
	virtual void setParameters(std::vector<Parameter> parameters) = 0;

	/**
	* \brief Pure abstract method which returns the parameters
	*/
	virtual std::vector<Parameter> parameters() = 0;

	/**
	* \brief Returns the results to be processed by the ResultGenerator
	*/
	virtual ResultGenerator::ResultMap results() = 0;

	/**
	* \brief Returns the result image
	*/
	cv::Mat* resultImg();

	/**
	* \brief Returns the processed image
	*/
	cv::Mat* processed();

protected:
	//Result image
	cv::Mat* resImg_;
	cv::Mat* processedImg_;
	//Method parameters
	int parametersSize_;
};

#endif // VERIFICATIONMETHOD_H
