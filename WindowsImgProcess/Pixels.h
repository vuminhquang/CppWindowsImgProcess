#pragma once
#include <algorithm>

namespace CppCLRWinformsProjekt
{
//Standard pixel, 255
typedef cv::Vec3b Pixel;

class LCCPixel
{
public:
	double l;
	double c1;
	double c2;
	
	LCCPixel& Clamp()
	{
		l = std::min(1.0, std::max(0.0, l));
		c1 = std::min(1.0, std::max(-1.0, c1));
		c2 = std::min(1.0, std::max(-1.0, c2));
		return *this;
	}
};

class ORGBPixel : LCCPixel
{
	
};
	
//Normalized pixel, 0 -> 1	
class RGBPixel
{
public:
	double r;
	double g;
	double b;

	RGBPixel& Clamp()
	{
		r = std::min(1.0, std::max(0.0, r));
		g = std::min(1.0, std::max(0.0, g));
		b = std::min(1.0, std::max(0.0, b));
		return *this;
	}

	static RGBPixel FromPixel(Pixel& fromPixel)
	{
		auto temp = new RGBPixel();
		temp->r = fromPixel[2] / 255.0;
		temp->g = fromPixel[1] / 255.0;
		temp->b = fromPixel[0] / 255.0;
	}
};

}