#include "pch.h"
#include "ProcessingUnit.h"
#include <opencv2/core/mat.hpp>
#include "Pixels.h"

using namespace CppCLRWinformsProjekt;

void ProcessingUnit::LoopPixels(cv::Mat& img)//--> Rename: ColorTransfer
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
				auto& r = (*it)[2];
				auto& g = (*it)[1];
				auto& b = (*it)[0];

				// Color transfer
				// Modify r, g, b values
				// E.g. r = 255; g = 0; b = 0;
				auto rgb_point = to_RGB_point(p);
		        auto lcc_point = RGB_to_LCC(rgb_point);
		        auto orgb_point = LCC_to_ORGB(lcc_point);
		        orgb_point = mean_shift(orgb_point, shift_val);
		        auto inverted_lcc_point = ORGB_to_LCC(orgb_point);
		        auto inverted_rgb_point = LCC_to_RGB(inverted_lcc_point);
		        auto inverted_pixel = to_Pixel(inverted_rgb_point); 
		        p = inverted_pixel;
			}
			break;
		}
	default:
		break;
	}
}

LCCPixel* ProcessingUnit::RGBToLCC(RGBPixel& rgb)
{
	const auto lcc = new LCCPixel();
	lcc->l  = 0.299 * rgb.r + 0.5870*rgb.g + 0.1140 * rgb.b;
    lcc->c1 = 0.5   * rgb.r + 0.5   *rgb.g - 1      * rgb.b;
    lcc->c2 = 0.866 * rgb.r - 0.866 *rgb.g;// +0.0* rgb.b;
	return lcc;
}


ORGBPixel* ProcessingUnit::LCCToORGB(LCCPixel& rgb)
{
	const auto orgb = new ORGBPixel();

	return orgb;
}