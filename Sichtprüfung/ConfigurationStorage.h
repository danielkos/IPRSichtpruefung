#ifndef CONFIGURATION_STORAGE_H
#define CONFIGURATION_STORAGE_H

#include <sys/stat.h>
#include <opencv2\core\core.hpp>
#include <QVariant>
#include <QSettings>
class ConfigurationStorage
{
public:

	static ConfigurationStorage& instance();

	bool exists(const std::string& configPath);

	/** \brief Write the \a value into the config at \a configPath
	*  The file will be rewritten and not realeased!
	*  \param configPath a path to the config file
	*  \param node node which will be created in the config file
	*  \param value value to be written
	*/
	bool write(const std::string& configPath, const std::string node, QVariant value);

	bool write(const std::string& configPath, const std::string node, cv::Mat& matrix);
	
	/** \brief Read the \a value from \a node in the config at \a configPath
	*  The variable \a value will be read
	*  \param configPath a path to the config file
	*  \param node node which will be created in the config file
	*  \param type value type from QMetaType
	*  \param value value readed at \a node 
	*/
	bool read(const std::string& configPath,  const std::string& node, QVariant& value);

	bool read(const std::string& configPath, const std::string node, cv::Mat& matrix);


private:
	ConfigurationStorage();
	QSettings settings_;

	
};
#endif // !1

