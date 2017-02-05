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
	//Computation for each result
	QString calibRes(ResultGenerator::ResultMap::iterator it);
	QString circleRes(ResultGenerator::ResultMap::iterator it);
	QString circleCenterRes(ResultGenerator::ResultMap::iterator it);
	QString angleRes(ResultGenerator::ResultMap::iterator it);
	QString objSizeRes(ResultGenerator::ResultMap::iterator it);
	QString	materialRes(ResultGenerator::ResultMap::iterator it);

	cv::Mat loadCalibrationMatrix(const std::string& path);

	//Current settings
	SettingsMap settings_;

	std::string calibmatrixPath_;
	typedef std::map<ResultGenerator::Results, ResultGenerator::Settings> SetResMap;
	typedef std::pair<ResultGenerator::Results, ResultGenerator::Settings> SetResPair;

	//mapping between Results and Settings
	SetResMap mapping_;
};
#endif // !RESULT_GENERATOR_H

