#include "HoleParameter.h"

std::vector<cv::Vec3f> HoleParameter::CheckParameter(cv::Mat img)
{
	cv::Mat gray;
	cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);	//change image to gray scale
	cv::medianBlur(gray, gray, 5);					//blure image
	std::vector<cv::Vec3f> circles;					//wektor of 3 elements vektors
	HoughCircles(gray, circles, cv::HOUGH_GRADIENT, 1,		//funktion which detects circles
		gray.rows / 8, // change this value to detect circles with different distances to each other
		100, 30, 30, 90 // change the last two parameters
						// (min_radius & max_radius) to detect larger circles (in pixels)
	);

	for (size_t i = 0; i < circles.size(); i++)
	{
		cv::Vec3i c = circles[i];
		circle(img, cv::Point(c[0], c[1]), c[2], cv::Scalar(0, 0, 255), 1, cv::LINE_AA); //draws circle on image
		circle(img, cv::Point(c[0], c[1]), 2, cv::Scalar(0, 255, 0), 3, cv::LINE_AA);	//draw middle of the circle on the image
	}
	return circles;//return values in vektors, x y radius in pixels.
}
