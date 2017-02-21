#include "ResultGenerator.h"
#include "ConfigurationStorage.h"
#include "Logger.h"
#include "Configs.h"

#include <opencv2\opencv.hpp>

#include <QSize>

ResultGenerator::ResultGenerator()
{
	mapping_.insert(SetResPair(ResultGenerator::Results::RES_CIRCLE_RADIUS, ResultGenerator::Settings::SET_CIRCLE_RADIUS));
	mapping_.insert(SetResPair(ResultGenerator::Results::RES_OBJ_ANGLE_LEFT, ResultGenerator::Settings::SET_OBJ_ANGLE));
	mapping_.insert(SetResPair(ResultGenerator::Results::RES_OBJ_ANGLE_RIGHT, ResultGenerator::Settings::SET_OBJ_ANGLE));
	mapping_.insert(SetResPair(ResultGenerator::Results::RES_OBJ_SIZE, ResultGenerator::Settings::SET_OBJ_SIZE));

	calibmatrixPath_ = paths::getExecutablePath() + paths::configFolder + paths::cameraFolder + filenames::calibrationName + extensions::calibrationExt;
}

ResultGenerator::~ResultGenerator()
{
}

double ResultGenerator::getCameraPixelRatio()
{
	double pixelRatio = 1.0;	// 1 as default value so that in error cases at
								// least the calculated result of the certain optical 
								// control processes is printed out on the GUI

	// if (RadioButton = Kalibrierverfahren für Berechnung der Ratio verwenden)
	//{
	cv::Mat calibMat = loadCalibrationMatrix(calibmatrixPath_);

	if (calibMat.empty() == false)
	{
		// Calibration matrix contains focal lenght in pixel, so conert to mm. Also calculate
		// mean value to improve results. Focal length should be more or less equal for x and y, because
		// the pixels of the IDS camera sensor have the same size in x and y direction 
		double focalLengthX = CAMERA_PIXEL_SIZE * calibMat.at<double>(0, 0);
		double focalLengthY = CAMERA_PIXEL_SIZE * calibMat.at<double>(1, 1);
		
		double focalLength = (focalLengthX + focalLengthY) / 2.0;	// In mm
		//focalLength = 25.0;	// Or just use focal length of lens without any further calculation 
		LOGGER.log("Focal length: " + QVariant(focalLength).toString());
		

		double g = 0;	// Distance from camera lens to object in mm

		// Calculating the distance between the camera lens and the object. For every
		// calibration image a translation and rotation vector (define the extrinsic parameters
		// of the camera) is stored. So calculate the average length of all translation vectors
		// the get an idead of the overal distance
		std::vector<cv::Mat> extrinsicParameters_Trans = loadMatrices("tvec", calibmatrixPath_);

		if (extrinsicParameters_Trans.empty() == false)
		{
			for (int i = 0; i < extrinsicParameters_Trans.size(); i++)
			{	
				g += getVectorLength(&extrinsicParameters_Trans[i]);
			}

			g /= extrinsicParameters_Trans.size();
		}
		
		// g = 230;	 // Or just use manually measured object distance without any further calculation
		LOGGER.log("Object distance: " + QVariant(g).toString());

		// Use intercept theorem and pinhole camera to calculate the pixel ratio.
		// Pixel ratio is later used to convert a length in a camera image (in pixel)
		// to mm, so the size of one camera pixel on the sensor needs to be considered also
		pixelRatio = 1.0 / (focalLength / (g - focalLength) / CAMERA_PIXEL_SIZE);
	}
	
	// RadioButton = Shape-Verfahren für Berechnung der Ratio verwenden
	//else 
	//{
	// TODO: Kalibrierung durch Shape-Verfahren:
	// Würde folgende Berechnung für Width und Height getrennt machen und dann aus beiden Ergebnissen den Mittelwert bilden,
	// also:
	// ratioHeight = ObjekthöheInMMAusOptions / ObjekthöheInPixelVonShapeVerfahren;
	// ratioWidth = ObjektbreiteInMMAusOptions / ObjektbreiteInPixelVonShapeVerfahren;
	// pixelRatio = (ratioHeight + ratioWidth) / 2.0;
	//
	// pixelRatio sollte in etwa 0.028 sein.
	//
	//}

	LOGGER.log("Pixel ratio: " + QVariant(pixelRatio).toString());

	return pixelRatio;
}


cv::Mat ResultGenerator::loadCalibrationMatrix(const std::string& path)
{
	cv::Mat mat;

	if (!path.empty())
	{
		if (!ConfigurationStorage::instance().read(path, "camera_matrix", mat))
		{
			LOGGER.log("Cannot read calibration matrix (K) from " + path);
		}
	}
	else
	{
		LOGGER.log("Invalid path: " + path + " supplied to load calibration matrix!");
	}
	
	return mat;
}

std::vector<cv::Mat> ResultGenerator::loadMatrices(const std::string& matrixName, const std::string& path)
{
	std::vector<cv::Mat> matrices;

	if (!path.empty())
	{
		bool newMatrixLoaded = true;
		int i = 0;

		// Try to load matrices with the given name as often as possible
		while (newMatrixLoaded)
		{
			cv::Mat mat;

			if (!ConfigurationStorage::instance().read(path, matrixName + std::to_string(i), mat))
			{
				newMatrixLoaded = false;
			}
			else
			{
				// Check if loaded matrix contains values. Because the key word "matrixName" might
				// occur in the calibration file without containing a real matrix!
				if (mat.empty() == false)
				{
					matrices.push_back(mat);
					i++;
				}
				else
				{
					newMatrixLoaded = false;
				}
			}
		}
	}
	else
	{
		LOGGER.log("Invalid path: " + path + " supplied to load calibration matrix!");
	}

	return matrices;
}


double ResultGenerator::getVectorLength(const cv::Mat* vector)
{
	double length = 0;

	if (vector)
	{
		// Only allow calculation for vectors with 1 column and n rows
		if (vector->size().height > 0 && vector->size().width == 1)
		{
			double curResult = 0.0;

			for (int i = 0; i < vector->rows; i++) 
			{
				curResult += vector->at<double>(i) * vector->at<double>(i);
			}

			length = std::sqrt(curResult);
		}
	}
	
	return length;
}


void ResultGenerator::setSettings(ResultGenerator::SettingsMap settings)
{
	settings_ = settings;
}

QString ResultGenerator::calibRes(ResultGenerator::ResultMap::iterator it)
{
	return QString("Calibration error: " + it->second.value_.toString());
}

QString ResultGenerator::circleRes(ResultGenerator::ResultMap::iterator it)
{
	double pixelRatio = getCameraPixelRatio();	// Ratio between one Pixel and one mm
	double radius = settings_.at(mapping_.at(it->first)).value_.toDouble();		// In Pixel
	
	QVariant est = it->second.value_.toDouble() * pixelRatio;
	QVariant dev = radius - est.toDouble();
	QVariant percent = (dev.toDouble() / radius) * 100;

	QString percentString = QString::number(percent.toDouble(), 'f', 2);	// Round percent number

	return QString("Real radius: " + QString::number(radius) + "mm, Estimated radius: " + est.toString() +
		"mm, Deviation: " + dev.toString() + "mm (" + percentString + "%)");
}

QString ResultGenerator::circleCenterRes(ResultGenerator::ResultMap::iterator it)
{
	return QString("Hole centered: " + it->second.value_.toString());
}

QString ResultGenerator::materialRes(ResultGenerator::ResultMap::iterator it)
{
	return QString("Metal: " + it->second.value_.toString());
}

QString ResultGenerator::angleRes(ResultGenerator::ResultMap::iterator it)
{
	QVariant angle = settings_.at(mapping_.at(it->first)).value_;
	QVariant est = it->second.value_.toDouble();
	QVariant dev = angle.toDouble() - est.toDouble();
	QVariant percent = (dev.toDouble() / angle.toDouble()) * 100;

	QString degree = "";			// UTF-8 (HEX) encoding needed to print degree symbol in QString
	degree.append(QChar(0xB0));		// on Windows
	QString percentString = QString::number(percent.toDouble(), 'f', 2);	// Round percent number

	return QString("Real angle: " + angle.toString() + degree + ", Estimated angle: " + est.toString() +
		degree + ", Deviation: " + dev.toString() + degree + " (" + percentString + "%)");
}

QString ResultGenerator::objSizeRes(ResultGenerator::ResultMap::iterator it)
{
	double pixelRatio = getCameraPixelRatio();		// Ratio between one Pixel and one mm
	QSize size = settings_.at(mapping_.at(it->first)).value_.toSize();	// In Pixel
	QSize est = it->second.value_.toSize();

	double estWidth = (double) (est.width() * pixelRatio);
	double estHeight = (double) (est.height() * pixelRatio);

	QString ret = "Real Size:" + QString::number(size.width()) + "x" + QString::number(size.height()) + " (mm), Estimated size: " +
		QString::number(estWidth) + "x" + QString::number(estHeight) + " (mm)";

	return ret;
}

QStringList ResultGenerator::results(QString methodName, ResultGenerator::ResultMap methodResults)
{
	QStringList res;

	res << methodName + ":";

	for (ResultGenerator::ResultMap::iterator it = methodResults.begin(); it != methodResults.end(); it++)
	{
		QString ret;
		switch (it->first)
		{
		case ResultGenerator::RES_CALIBRATION:
			ret = calibRes(it);
			break;
		case ResultGenerator::RES_OBJ_SIZE:
			ret = objSizeRes(it);
			break;
		case ResultGenerator::RES_OBJ_ANGLE_LEFT:
			ret = angleRes(it);
			break;
		case ResultGenerator::RES_OBJ_ANGLE_RIGHT:
			ret = angleRes(it);
			break;
		case ResultGenerator::RES_CIRCLE_MIDDLE:
			ret = circleCenterRes(it);
			break;
		case ResultGenerator::RES_CIRCLE_RADIUS:
			ret = circleRes(it);
			break;
		case ResultGenerator::RES_MATERIAL:
			ret = materialRes(it);
			break;
		default:
			break;
		}

		res << ret;
	}

	return res;
}
