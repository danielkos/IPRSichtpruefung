#ifndef VERIFICATIONMETHOD_H
#define VERIFICATIONMETHOD_H

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
	* \brief Abstract method which applies the method
	*/
	virtual bool run(const cv::Mat* img) = 0;
	/**
	* \brief Returns the result image
	*/
	cv::Mat* getResult();

protected:
	//Result image
	cv::Mat* resImg_;
};

#endif // VERIFICATIONMETHOD_H
