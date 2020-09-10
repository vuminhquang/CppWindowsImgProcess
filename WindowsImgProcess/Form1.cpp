#include "pch.h"
#include <msclr\marshal_cppstd.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "Form1.h"
#include "ProcessingUnit.h"

using namespace CppCLRWinformsProjekt;



System::Void Form1::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	//MessageBox::Show("aaaaaaaaaaaaaaa");

	openFileDialog1->Filter = "PNG files (*.png)|*.png|JPEG files (*.jpg)|*.jpg";
	if(openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		String^ fileName1 = openFileDialog1->FileName;
		// //tostdString converts to std string see link ^^
		//
		cv::Mat src = cv::imread(ToUnmanagedString(fileName1), cv::IMREAD_COLOR); //, CV_LOAD_IMAGE_COLOR);
		//cv::cvtColor(src, src, cv::COLOR_RGB2BGR);

		ProcessingUnit^ processingUnit = gcnew ProcessingUnit();
		processingUnit->LoopPixels(src, 0.0, 0.0);
		
		// src *= 1./255;
		// src.forEach<Pixel>(Operator());
		//cv::cvtColor(src, src, cv::COLOR_RGB2XYZ);
		uint8_t* pixelPtr = (uint8_t*)src.data;
		int cn = src.channels();
		cv::Scalar_<uint8_t> bgrPixel;
		cv::cvtColor(src, src, cv::COLOR_RGB2RGBA);
		HBITMAP hBit = CreateBitmap(src.cols, src.rows, 1, 32, src.data);
		//
		Bitmap^ bmp = Bitmap::FromHbitmap((IntPtr)hBit);
		pictureBox1->Image = bmp;
	}
}


 std::string Form1::ToUnmanagedString(String^ stringIncoming)
 {
	std::string unmanaged = msclr::interop::marshal_as<std::string>(stringIncoming);
    return unmanaged;
 }