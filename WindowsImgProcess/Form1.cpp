#include "pch.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "Form1.h"

using namespace CppCLRWinformsProjekt;

System::Void Form1::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	MessageBox::Show("aaaaaaaaaaaaaaa");

	openFileDialog1->Filter = "JPEG files (*.jpg)|*.jpg|Bitmap files (*.bmp)|*.bmp";
if(openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
{
	cv::Mat img;
    // img = cv::imread(openFileDialog1->FileName, CV_LOAD_IMAGE_COLOR);
    // pictureBox1->Image = (gcnew Bitmap(img.size().width,
    //                                         img.size().height,
    //                                         img.widthStep,
    //                                         Imaging::PixelFormat::Format24bppRgb,
    //                                         (IntPtr)img.data));

}
	
	cv::Mat image = cv::Mat::zeros(300, 600, CV_8UC3);
	circle(image, cv::Point(250, 150), 100, cv::Scalar(0, 255, 128), -100);
	circle(image, cv::Point(350, 150), 100, cv::Scalar(255, 255, 255), -100);
}