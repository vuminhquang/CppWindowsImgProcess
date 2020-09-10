
#include "pch.h"
#include "ProcessingUnit.h"
#include <opencv2/core/mat.hpp>
#include "Pixels.h"

using namespace CppCLRWinformsProjekt;

void ProcessingUnit::LoopPixels(cv::Mat& img, double yVal, double rVal)//--> Rename: ColorTransfer
{
	// Accept only char type matrices
	CV_Assert(img.depth() == CV_8U);

	// Get the channel count (3 = rgb, 4 = rgba, etc.)
	const int channels = img.channels();
	switch (channels)
	{
	case 1:
		{
			//Do not work on single color picture
			// Single colour
			//cv::MatIterator_<uchar> it, end;
			// for (it = img.begin<uchar>(), end = img.end<uchar>(); it != end; ++it)
			// 	*it = 255;
			break;
		}
	case 3:
		{
			// RGB Color
			cv::MatIterator_<Pixel> it, end;
			for (it = img.begin<Pixel>(), end = img.end<Pixel>(); it != end; ++it)
			{
				// convert to doubles
				double r = (*it)[2] * 1.0;
				double g = (*it)[1] * 1.0;
				double b = (*it)[0] * 1.0;
				
				rescale(r,g,b,1.0/255);
		        rgb2lcc(r,g,b);
		        lcc2orgb(r,g,b);
		        
				// shifting colors
				g = g + yVal;
				b = b + rVal;

				// clamping
				r = std::min(1.0, std::max(0.0, r));
				g = std::min(1.0, std::max(-1.0, g));
				b = std::min(1.0, std::max(-1.0, b));

		        orgb2lcc(r,g,b);
		        lcc2rgb(r,g,b);

				r = std::min(1.0, std::max(0.0, r));
				g = std::min(1.0, std::max(0.0, g));
				b = std::min(1.0, std::max(0.0, b));

				//0->255
				rescale(r,g,b,255); 

				// reapply
				(*it)[2] = std::round(r);
				(*it)[1] = std::round(g);
				(*it)[0] = std::round(b);

			}
			break;
		}
	default:
		break;
	}
}

void ProcessingUnit::rescale(double& r, double& g, double& b, double rate) 
{
	r = r * rate;
	g = g * rate;
	b = b * rate;
}

void ProcessingUnit::rgb2lcc(double& r, double& g, double& b)
{
	double _r = 0.299*r + 0.5870*g + 0.114*b;
	double _g = 0.5*r + 0.5*g - b;
	double _b = 0.866*r - 0.866*g;

	r = _r; 
	g = _g;
	b = _b;
}

void ProcessingUnit::lcc2rgb(double& l, double& c1, double& c2)
{
	double _l = l + 0.114*c1 + 0.7436*c2;
	double _c1 = l + 0.114*c1 - 0.4111*c2;
	double _c2 = l - 0.886*c1 + 0.1663*c2;
	
	// clamping
	_l = std::min(1.0, std::max(0.0, l));
	_c1 = std::min(1.0, std::max(-1.0, c1));
	_c2 = std::min(1.0, std::max(-1.0, c2));

	l = _l;
	c1 = _c1;
	c2 = _c2;
}

void ProcessingUnit::lcc2orgb(double& l, double& c1, double& c2)
{	
	if (c2 == 0 && c1 == 0) return;

	double theta = atan2(c2, c1);
	double theta0 = 1.5 * theta;
	if ((theta >= CV_PI/3) && (theta <= CV_PI))
	{
		theta0 = 0.75*theta + CV_PI*0.25;
	}
	else if ((theta >= -CV_PI) && (theta <= -CV_PI/3)) 
	{
		theta0 = 0.75*theta - CV_PI*0.25;
	}

	double angle = theta0 - theta;
	double Cyb = c1 * std::cos(angle) - c2 * std::sin(angle);
	double Crg = c1 * std::sin(angle) + c2 * std::cos(angle);

	c1 = Cyb;
	c2 = Crg;
}

void ProcessingUnit::orgb2lcc(double& r, double& g, double& b)
{
	if ((g == 0) && (b == 0)) return;

	double theta = atan2(b, g);
	double theta0 = theta*2.0/3;
	if ((theta >= CV_PI/2) && (theta <= CV_PI))
	{
		theta0 = 4.0/3*theta - CV_PI/3;
	}
	else if ((theta >= -CV_PI) && (theta <= -CV_PI/2)) 
	{
		theta0 = 4.0/3*theta + CV_PI/3;
	}

	double angle = theta0 - theta;
	double _c1 = g * std::cos(angle) - b * std::sin(angle);
	double _c2 = g * std::sin(angle) + b * std::cos(angle);

	// clamp
	g = std::min(1.0, std::max(-1.0, _c1));
	b = std::min(1.0, std::max(-1.0, _c2));
}