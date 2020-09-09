#pragma once
#include <opencv2/core/types.hpp>

#include "Pixels.h"

namespace CppCLRWinformsProjekt
{
	ref class ProcessingUnit
	{
	public:
		void LoopPixels(cv::Mat& img);
		static LCCPixel* ProcessingUnit::RGBToLCC(RGBPixel& rgb);
		ORGBPixel* LCCToORGB(LCCPixel& rgb);
	};
}



// struct Operator {
//     void operator ()(Pixel &pixel, const int * position) const 
//     {           
//           
//     }
// };




