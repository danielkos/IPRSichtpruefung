#include "ConfigurationStorage.h"
#include "Logger.h"

ConfigurationStorage::ConfigurationStorage()
{

}

ConfigurationStorage& ConfigurationStorage::instance()
{
	static ConfigurationStorage storage;
	return storage;
}

bool ConfigurationStorage::exists(const std::string& configPath)
{
	struct stat buf;
	if (stat(configPath.c_str(), &buf) != -1)
	{
		return true;
	}
	return false;
}

bool ConfigurationStorage::write(const std::string& configPath, std::string node, QVariant value)
{
	bool ret = true;
	QSettings settings(QString::fromStdString(configPath), QSettings::IniFormat);
	QString key = QString::fromStdString(node);
	int status = settings.status();

	if (status == QSettings::Status::NoError)
	{
		if (!key.isEmpty())
		{
			settings.setValue(key, value);
		}
		else
		{
			ret = false;
		}
	}
	else
	{
		switch (status)
		{
		case QSettings::Status::AccessError:
			LOGGER.log("Cannot access the file located at " + configPath);
			break;
		case QSettings::Status::FormatError:
			LOGGER.log("File located at " + configPath + "is malformed");
			break;
		}

		ret = false;
	}

	return ret;
}

bool ConfigurationStorage::write(const std::string& configPath, std::string node, cv::Mat& matrix)
{
	bool ret = true;
	QSettings settings(QString::fromStdString(configPath), QSettings::IniFormat);
	QString key = QString::fromStdString(node);
	int status = settings.status();
	int curElem = 0;

	if (status == QSettings::Status::NoError)
	{
		if (!key.isEmpty())
		{
			settings.beginWriteArray(key);
			for (int i = 0; i < matrix.rows; ++i) 
			{
				for (int k = 0; k < matrix.cols; k++)
				{
					curElem = i * matrix.cols + k;
					settings.setArrayIndex(curElem);
					double elem = matrix.at<double>(i, k);
					settings.setValue(key + QString::number(i) + QString::number(k), elem);
				}
			}
			settings.endArray();

			settings.setValue(key + "/rows", matrix.rows);
			settings.setValue(key + "/cols", matrix.cols);
		}
		else
		{
			ret = false;
		}
	}
	else
	{
		switch (status)
		{
		case QSettings::Status::AccessError:
			LOGGER.log("Cannot access the file located at " + configPath);
			break;
		case QSettings::Status::FormatError:
			LOGGER.log("File located at " + configPath + "is malformed");
			break;
		}

		ret = false;
	}

	return ret;
}

bool ConfigurationStorage::read(const std::string& configPath, const std::string& node, QVariant& value)
{
	bool ret = true;
	QSettings settings(QString::fromStdString(configPath), QSettings::IniFormat);
	QString key = QString::fromStdString(node);
	int status = settings.status();

	if (status == QSettings::Status::NoError)
	{
		if (!key.isEmpty() && settings.contains(key))
		{
			value = settings.value(key);
		}
		else
		{
			ret = false;
		}
	}
	else
	{
		switch (status)
		{
		case QSettings::Status::AccessError:
			LOGGER.log("Cannot access the file located at " + configPath);
			break;
		case QSettings::Status::FormatError:
			LOGGER.log("File located at " + configPath + "is malformed");
			break;
		}

		ret = false;
	}
	
	return ret;
}

bool ConfigurationStorage::read(const std::string& configPath, std::string node, cv::Mat& matrix)
{
	bool ret = true;
	QSettings settings(QString::fromStdString(configPath), QSettings::IniFormat);
	QString key = QString::fromStdString(node);
	int status = settings.status();
	int curElem = 0;
	int size = matrix.rows * matrix.cols;
	double *data = new double[size];

	if (status == QSettings::Status::NoError)
	{
		QStringList list = settings.allKeys().filter(key);
		if (!key.isEmpty() && !list.empty() && !matrix.empty())
		{
			QString rows = key + "/rows";
			QString cols = key + "/cols";
			if (settings.contains(rows) && settings.contains(cols))
			{
				matrix = cv::Mat(settings.value(rows).toInt(), settings.value(cols).toInt(), CV_64F);

				settings.beginReadArray(key);
				for (int i = 0; i < matrix.rows; ++i)
				{
					for (int k = 0; k < matrix.cols; k++)
					{
						curElem = i * matrix.cols + k;
						settings.setArrayIndex(curElem);
						data[curElem] = settings.value(key + QString::number(i) + QString::number(k)).toDouble();
					}
				}
				settings.endArray();
				std::memcpy(matrix.data, data, sizeof(double) * size);
			}
		}
		else
		{
			ret = false;
		}
	}
	else
	{
		switch (status)
		{
		case QSettings::Status::AccessError:
			LOGGER.log("Cannot access the file located at " + configPath);
			break;
		case QSettings::Status::FormatError:
			LOGGER.log("File located at " + configPath + "is malformed");
			break;
		}

		ret = false;
	}
	
	if (data)
	{
		delete data;
	}

	return ret;
}