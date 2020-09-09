#include "pch.h"
#include <msclr\marshal_cppstd.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "Form1.h"

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
	       cv::Mat src = cv::imread(ToUnmanagedString(fileName1), cv::IMREAD_UNCHANGED);//, CV_LOAD_IMAGE_COLOR);
		   //cv::cvtColor(src, src, cv::COLOR_RGB2XYZ);
			uint8_t* pixelPtr = (uint8_t*)src.data;
			int cn = src.channels();
			cv::Scalar_<uint8_t> bgrPixel;

			for(int i = 0; i < src.rows; i++)
			{
			    for(int j = 0; j < src.cols; j++)
			    {
			        //float z = pixelPtr[i*src.cols*cn + j*cn + 0] / 255.f; // B => Z
			        //float y = pixelPtr[i*src.cols*cn + j*cn + 1] / 255.f; // G => Y
			        //float x = pixelPtr[i*src.cols*cn + j*cn + 2] / 255.f; // R => X
			        //
			        //float _b = powf(pixelPtr[i*src.cols*cn + j*cn + 0]/255.0, 2.2f);
			        float _b = pixelPtr[i*src.cols*cn + j*cn + 0] /255.f;
			    	//float _g = powf(pixelPtr[i*src.cols*cn + j*cn + 1]/255.0, 2.2f);
			    	float _g = pixelPtr[i*src.cols*cn + j*cn + 1] /255.f;
			    	//float _r = powf(pixelPtr[i*src.cols*cn + j*cn + 2]/255.f, 2.2f);
			    	float _r = pixelPtr[i*src.cols*cn + j*cn + 2] /255.f;

			    	/*_b = (_b > 1)? 1 :_b;
			    	_b = (_b < 0) ? 0: _b;
			    	_g = (_g > 1) ? 1 : _g;
			    	_g = (_g < 0) ? 0: _g;
			    	_r = (_r > 1)? 1 :_r;
					_r = (_r < 0) ? 0: _r;*/
			    	//float _r = pixelPtr[i*src.cols*cn + j*cn + 2];
			    	

			    	/*float _r = 3.2406255 * x - 1.537208 * y - 0.4986286 * z;
			    	_r = (_r > 1)? 1 :_r;
			    	_r = (_r < 0) ? 0: _r;
					float _g = -0.9689307 * x + 1.8757561 * y + 0.0415175 * z;
			    	_g = (_g > 1) ? 1 : _g;
			    	_g = (_g < 0) ? 0: _g;
			    	float _b = 0.0557101 * x - 0.2040211 * y + 1.0569959 * z;
			    	_b = (_b > 1)? 1 :_b;
			    	_b = (_b < 0) ? 0: _b;*/
			  //  	

			    	/*pixelPtr[i*src.cols*cn + j*cn + 0] = _b * 255;
					pixelPtr[i*src.cols*cn + j*cn + 1] = _g * 255;
					pixelPtr[i*src.cols*cn + j*cn + 2] = _r * 255;*/
			  //  	//pixelPtr[i*src.cols*cn + j*cn + 3] = 255.0f;

			    	float L = _r * 0.299 + _g * 0.587 + _b * 0.114;
			    	float C1 = _r * 0.5 + _g * 0.5 + _b * -1.0;
			    	float C2 = _r * 0.866 + _g * -0.866;

			    	float theta = atan2f(C2, C1);
			    	float theta0 = 1.5 * theta;
			    	if (theta <= Math::PI && theta >= Math::PI/3)
			    	{
			    		theta0 = Math::PI * 0.5 + 0.75 * (theta - Math::PI/3);
			    	}
			    	float _theta = theta0 - theta;

			    	float Cyb = C1*Math::Cos(_theta) - C2*Math::Sin(_theta);
			    	float Crg = C1*Math::Sin(_theta) + C2*Math::Cos(_theta);

			    	Cyb = (Cyb > 1) ? 1 : Cyb;
			    	Cyb = (Cyb < 0) ? 0 : Cyb;
			    	Crg = (Crg > 1) ? 1 : Crg;
			    	Crg = (Crg < 0) ? 0 : Crg;

			    	pixelPtr[i*src.cols*cn + j*cn + 0] = Crg * 255;
					pixelPtr[i*src.cols*cn + j*cn + 1] = Cyb * 255;
					pixelPtr[i*src.cols*cn + j*cn + 2] = L * 255;
			        // do something with BGR values...
			    }
			}

			

			//for(int i = 0; i < src.rows; i++)
			//{
			//    for(int j = 0; j < src.cols; j++)
			//    {
			//        
			//        float _r = pixelPtr[i*src.cols*cn + j*cn + 0];
			//    	float _g = pixelPtr[i*src.cols*cn + j*cn + 1];
			//    	float _b = pixelPtr[i*src.cols*cn + j*cn + 2];

			//    	float L = _r * 0.299 + _g * 0.587 + _b * 0.114;
			//    	float C1 = _r * 0.5 + _g * 0.5 + _b * -1.0;
			//    	float C2 = _r * 0.866 + _g * 0.866;

			//    	pixelPtr[i*src.cols*cn + j*cn + 0] = L;
			//		pixelPtr[i*src.cols*cn + j*cn + 1] = C1;
			//		pixelPtr[i*src.cols*cn + j*cn + 2] = C2;
			//    	//pixelPtr[i*src.cols*cn + j*cn + 3] = 255.0f;

			//        // do something with BGR values...
			//    }
			//}

			//float dA[] = {
			//			     0.299,     0.587,     0.114,
			//			     0.5,     0.5,     -1.0,
			//			     0.866,     0.866,     0
			//			};
			//cv::Mat filter = cv::Mat(3,3,CV_32F,dA);
			//src = filter * src;
	       
        HBITMAP hBit = CreateBitmap(src.cols, src.rows, 1, 32, src.data);
        //
        Bitmap^ bmp = Bitmap::FromHbitmap((IntPtr)hBit);
        pictureBox1->Image = bmp;

}
	
	//cv::Mat image = cv::Mat::zeros(300, 600, CV_8UC3);
	//circle(image, cv::Point(250, 150), 100, cv::Scalar(0, 255, 128), -100);
	//circle(image, cv::Point(350, 150), 100, cv::Scalar(255, 255, 255), -100);
}


 std::string Form1::ToUnmanagedString(String^ stringIncoming)
 {
	std::string unmanaged = msclr::interop::marshal_as<std::string>(stringIncoming);
    return unmanaged;
 }