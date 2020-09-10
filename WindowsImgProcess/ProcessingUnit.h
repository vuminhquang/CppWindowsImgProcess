#pragma once
#include <opencv2/imgproc.hpp>

namespace CppCLRWinformsProjekt
{
	ref class ProcessingUnit
	{
	public:
		void LoopPixels(cv::Mat& img, double yVal, double rVal);
		void rescale(double& r, double& g, double& b, double rate);
		void rgb2lcc(double& r, double& g, double& b);
		void lcc2rgb(double& l, double& c1, double& c2);
		void lcc2orgb(double& l, double& c1, double& c2);
		void orgb2lcc(double& r, double& g, double& b);
	};
}



