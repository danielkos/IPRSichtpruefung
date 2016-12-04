#include "ResultGenerator.h"

#include <QSize>

ResultGenerator::ResultGenerator()
{
	mapping_.insert(SetResPair(ResultGenerator::Results::RES_CIRCLE_RADIUS, ResultGenerator::Settings::SET_CIRCLE_RADIUS));
	mapping_.insert(SetResPair(ResultGenerator::Results::RES_OBJ_ANGLE_LEFT, ResultGenerator::Settings::SET_OBJ_ANGLE));
	mapping_.insert(SetResPair(ResultGenerator::Results::RES_OBJ_ANGLE_RIGHT, ResultGenerator::Settings::SET_OBJ_ANGLE));
	mapping_.insert(SetResPair(ResultGenerator::Results::RES_OBJ_SIZE, ResultGenerator::Settings::SET_OBJ_METRICS));
	mapping_.insert(SetResPair(ResultGenerator::Results::RES_CALIBRATION, ResultGenerator::Settings::SET_REF_SIZE));
}

ResultGenerator::~ResultGenerator()
{
}

void ResultGenerator::setSettings(ResultGenerator::SettingsMap settings)
{
	settings_ = settings;
}

QString ResultGenerator::calibRes(ResultGenerator::ResultMap::iterator it)
{
	QSize refSize = settings_.at(mapping_.at(it->first)).value_.toSize();
	QSize objSize = it->second.value_.toSize();
	
	QVariant widthRatio = (double)refSize.width() / objSize.width();
	QVariant heightRatio = (double)refSize.height() / objSize.height();

	pixelRatio_ = (widthRatio.toDouble() + heightRatio.toDouble()) / 2;

	return QString("Ratio between 1 cm and 1 Pixel is: " + pixelRatio_.toString());
}

QString ResultGenerator::circleRes(ResultGenerator::ResultMap::iterator it)
{
	QVariant radius = settings_.at(mapping_.at(it->first)).value_;
	QVariant est = it->second.value_.toDouble() * pixelRatio_.toDouble();
	QVariant dev = radius.toDouble() - est.toDouble();
	QVariant percent = (dev.toDouble() / radius.toDouble()) * 100;

	QString percentString = QString::number(percent.toDouble(), 'f', 2);	// Round percent number

	return QString("Real radius: " + radius.toString() + "cm, Estimated radius: " + est.toString() + 
					"cm, Deviation: " + dev.toString() + "cm (" + percentString + "%)");
}

QString ResultGenerator::circleCenterRes(ResultGenerator::ResultMap::iterator it)
{
	return QString("Hole centered: " + it->second.value_.toString());
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
	QSize size = settings_.at(mapping_.at(it->first)).value_.toSize();
	QSize est = it->second.value_.toSize();

	est.setWidth(est.width() * pixelRatio_.toDouble());
	est.setHeight(est.height() * pixelRatio_.toDouble());

	return QString("Real Size:" + QString(size.width()) + "x" + QString(size.height()) + ", Estimated size: " +
					QString(est.width()) + "x" + QString(est.height()));
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
		default:
			break;
		}
		
		res << ret;
	}
	
	return res;
}
