#ifndef ANGLEVERIFICATION_H
#define ANGLEVERIFICATION_H

#include "VerificationMethod.h"
#include "Parameter.h"

#include <opencv2\opencv.hpp>


// Defines a Hough-Line for the angle calculation
struct HoughLine
{
	// The Hough-Line (described by two 2d points: start and end of line)
	cv::Vec4i line_;

	// The angle between the line and the horizontal x axis
	double angle_;

	// Constructor with default values
	HoughLine() : line_(cv::Vec4i(0, 0, 1, 0)), angle_(0.0)
	{
	}

	// Creates a Hough-Line object with the given values
	void setUp(cv::Vec4i line, double angle)
	{
		line_ = line;
		angle_ = angle;
	}
};


class AngleVerification : public VerificationMethod
{
public:

	AngleVerification();
	~AngleVerification();

	// Implementation of interface VerificationMethod
	bool run(const cv::Mat* img);
	// Implementation of interface VerificationMethod
	void setParameters(std::vector<Parameter> parameters);
	// Implementation of interface VerificationMethod
	std::vector<Parameter>parameters();
	// Implementation of interface VerificationMethod
	ResultGenerator::ResultMap results();


private:

	// Parameters of the algorithm:

	// Lower threshold for the canny edge detection
	double cannyLowerThresh_;

	// Upper threshold for the canny edge detection
	double cannyUpperThresh_;

	// Tolerance value that defines when two angles are assumed
	// to be equal
	double angleTolerance_;


	// Result values:

	// The measured angle for the left "Schwalbenschwanznut" of the object
	double angleLeft_;

	// The measured angle for the right "Schwalbenschwanznut" of the object
	double angleRight_;
	

	/*
	 * Calculates the angle between the given line and the x axis.
	 *
	 * /param line a line in 2d. Consists of two 2d points that
	 * define the minimum (start) and maximum (end) point of the line.
	 * /return the angle between the given line and the horizonzal x axis
	 */
	double getAngleBtwLineAndXAxis(cv::Vec4i line);

	/*
	* Calculates the median of all angles of all given lines.
	* 
	* /param lines a set of lines
	* /return the median of all angles of all lines or 0.0 if
	*			given vector is empty
	*/
	double calculateMedianAngle(std::vector<HoughLine> *lines);

};
#endif