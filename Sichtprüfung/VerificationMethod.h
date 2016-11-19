#ifndef VERIFICATIONMETHOD_H
#define VERIFICATIONMETHOD_H

namespace cv
{
	class Mat;
}

class VerificationMethod
{
public:
	VerificationMethod();
	virtual ~VerificationMethod();

	virtual bool run(const cv::Mat* img) = 0;
	
	cv::Mat* getResult();
protected:
	cv::Mat* resImg_;
};

#endif // VERIFICATIONMETHOD_H
