#ifndef RESULT_GENERATOR_H
#define RESULT_GENERATOR_H

#include <vector>
#include <QVariant>
#include "Parameter.h"

namespace cv
{
	class Mat;
}

class ResultGenerator
{
public:
	//Defines all possible results
	enum Results
	{
		RES_CALIBRATION,
		RES_OBJ_SIZE,
		RES_OBJ_ANGLE_LEFT,
		RES_OBJ_ANGLE_RIGHT,
		RES_CIRCLE_MIDDLE,
		RES_CIRCLE_RADIUS,
		RES_MATERIAL
	};

	//Defines all possible settings
	enum Settings
	{
		SET_OBJ_SIZE,
		SET_CIRCLE_RADIUS,
		SET_OBJ_ANGLE,
	};

	//Storage for results from methods
	typedef std::map<Results, Parameter> ResultMap;
	typedef std::pair<Results, Parameter> ResultPair;

	//Storage for settings
	typedef std::map<Settings, Parameter> SettingsMap;
	typedef std::pair<Settings, Parameter> SettingsPair;

	ResultGenerator();
	virtual ~ResultGenerator();

	/**
	* \brief Sets the settings which will be used later
	*/
	void setSettings(ResultGenerator::SettingsMap settings);

	/**
	* \brief Returns the generated results
	*/
	QStringList results(QString methodName, ResultGenerator::ResultMap methodResults);

private:

	// If the shape verification method should be used for calculating the pixel ratio. If false
	// the real calibration method is use.
	const bool USE_SHAPE_VERIFICATION = true;

	// The size of a single pixel of the camera image sensor in mm
	// Value just valid for IDS UI-1460LE camera (https://en.ids-imaging.com/store/ui-1460le.html)!
	const double CAMERA_PIXEL_SIZE = 0.0032;


	//Computation for each result
	QString calibRes(ResultGenerator::ResultMap::iterator it);
	QString circleRes(ResultGenerator::ResultMap::iterator it);
	QString circleCenterRes(ResultGenerator::ResultMap::iterator it);
	QString angleRes(ResultGenerator::ResultMap::iterator it);
	QString objSizeRes(ResultGenerator::ResultMap::iterator it);
	QString	materialRes(ResultGenerator::ResultMap::iterator it);

	// Calculates the ratio between Pixel and mm. 
	// It is returned how many Pixel describe one mm in the real world.
	// Use this method to calculate real-world values!
	double getCameraPixelRatio();

	// Loads the calibration matrix from the given path from the local file system. 
	// Returned matrix might be empty if calibration matrix could not be loaded.
	cv::Mat loadCalibrationMatrix(const std::string& path);

	// Loads all matrices with the given name. A number (0..INT_MAX) is appended to the
	// given name to create a new matrix name and the matrix is loaded. This is repeated
	// until no matrix with the newly created name doesn't exist anymore.
	// => E.g. loads all the matrices with the name "mat0", "mat1", "mat2",...
	// The list with the loaded matrices is returned.
	std::vector<cv::Mat> loadMatrices(const std::string& matrixName, const std::string& path);

	// Calculates the length of the given vector and returns it.
	// The vector is given as a cv::Mat with 1 column and n rows, otherwise or if
	// no result could be calculated 0 is returned.
	double getVectorLength(const cv::Mat* vector);


	//Current settings
	SettingsMap settings_;

	std::string calibmatrixPath_;
	typedef std::map<ResultGenerator::Results, ResultGenerator::Settings> SetResMap;
	typedef std::pair<ResultGenerator::Results, ResultGenerator::Settings> SetResPair;

	//mapping between Results and Settings
	SetResMap mapping_;
};
#endif // !RESULT_GENERATOR_H

