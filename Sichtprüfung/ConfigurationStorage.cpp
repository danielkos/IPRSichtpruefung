#include "ConfigurationStorage.h"

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
	if (!storage_.isOpened())
	{
		ret = storage_.open(configPath, cv::FileStorage::WRITE);
	}

	if (value.isNull() && !node.empty())
	{
		storage_ << node.c_str();
	}
	else if (!value.isNull() && !node.empty())
	{
		switch (value.type())
		{
		case QMetaType::Int:
			storage_ << node << value.toInt();
			break;
		case QMetaType::Double:
			storage_ << node << value.toDouble();
			break;
		case QMetaType::Bool:
			storage_ << node << value.toInt();
			break;
		case QVariant::String:
			storage_ << node << value.toString().toStdString();
			break;
		}
	}
	else
	{
		ret = false;
	}
	return ret;
}

bool ConfigurationStorage::write(const std::string& configPath, std::string node, cv::Mat& matrix)
{
	bool ret = true;
	if (!storage_.isOpened())
	{
		ret = storage_.open(configPath, cv::FileStorage::WRITE);
	}
	else if (!matrix.empty() && !node.empty())
	{
		storage_ << node << matrix;
	}
	else
	{
		ret = false;
	}
	return ret;
}

bool ConfigurationStorage::read(const std::string& configPath, const std::string& node, int type, QVariant& value)
{
	bool ret = true;
	if (storage_.open(configPath, cv::FileStorage::READ))
	{
		if (!node.empty())
		{
			switch (type)
			{
			case QMetaType::Int:
				value = QVariant((int)storage_[node]);
				break;
			case QMetaType::Double:
				value = QVariant((double)storage_[node]);
				break;
			case QMetaType::Bool:
				value = QVariant((int)storage_[node]);
				break;
			case QMetaType::Char:
				value = QVariant(QString::fromStdString((std::string)storage_[node]));
				break;
			}
		}
		storage_.release();
	}
	else
	{
		ret = false;
	}
	return ret;
}

void ConfigurationStorage::realease()
{
	storage_.release();
}