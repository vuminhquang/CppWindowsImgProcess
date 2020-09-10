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
	openFileDialog1->Filter = "PNG files (*.png)|*.png|JPEG files (*.jpg)|*.jpg";
	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		pictureBox1->ImageLocation = openFileDialog1->FileName;
	}
}
System::Void Form1::button2_Click(System::Object^ sender, System::EventArgs^ e)
{
	auto yVal = Convert::ToDouble(txtYellow->Text);
	auto rVal = Convert::ToDouble(txtRed->Text);

	if (openFileDialog1->FileName != String::Empty)
	{
		String^ fileName1 = openFileDialog1->FileName;
		
		cv::Mat src = cv::imread(ToUnmanagedString(fileName1), cv::IMREAD_COLOR); //, CV_LOAD_IMAGE_COLOR);
		
		ProcessingUnit^ processingUnit = gcnew ProcessingUnit();
		processingUnit->LoopPixels(src, yVal, rVal);

		cv::cvtColor(src, src, cv::COLOR_BGR2BGRA);
		HBITMAP hBit = CreateBitmap(src.cols, src.rows, 1, 32, src.data);
		Bitmap^ bmp = Bitmap::FromHbitmap((IntPtr)hBit);
		pictureBox2->Image = bmp;
	}
}


std::string Form1::ToUnmanagedString(String^ stringIncoming)
{
	std::string unmanaged = msclr::interop::marshal_as<std::string>(stringIncoming);
	return unmanaged;
}