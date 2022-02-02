// MeasureFocus.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <atlstr.h>
#include <iostream>


/******************************/
////////Opencv 관련/////////////
/******************************/
#include "opencv\\cv.h"
#include "opencv\highgui.h"
#include "opencv2\opencv.hpp"
using namespace cv;  
/******************************/
////////////////////////////////
/******************************/

double OCV_FocusMeasure(Mat &src)
{
	Mat dst, src_gray;
	cv::Scalar mean, stddev;
	
	if (src.channels() == 1)//Mono
	{	
		cv::Laplacian(src, dst, CV_64F);
	}	
	else//RGB
	{		
		cvtColor(src, src_gray, CV_RGB2GRAY);// Convert the image to grayscale
		cv::Laplacian(src_gray, dst, CV_64F);	
	}
	
	cv::meanStdDev(dst, mean, stddev);

	return stddev.val[0] * stddev.val[0];
}

int _tmain(int argc, _TCHAR* argv[])
{
	Mat OrgImage, Test1, Test2, Test3, Test4;	
	CString szChar;
	double dValue[5];
	
	OrgImage = imread("../Image/Org.bmp");//Load Org Image
	Test1 = imread("../Image/Test1.bmp");//Load Test1 Image
	Test2 = imread("../Image/Test2.bmp");//Load Test2 Image
	Test3 = imread("../Image/Test3.bmp");//Load Test3 Image
	Test4 = imread("../Image/Test4.bmp");//Load Test4 Image

	
	dValue[0] = OCV_FocusMeasure(OrgImage);
	dValue[1] = OCV_FocusMeasure(Test1);
	dValue[2] = OCV_FocusMeasure(Test2);
	dValue[3] = OCV_FocusMeasure(Test3);
	dValue[4] = OCV_FocusMeasure(Test4);

	szChar.Format("OrgImage(%.1f)", dValue[0]);
	imshow(szChar.GetBuffer(), OrgImage);

	szChar.Format("Test1(%.1f)", dValue[1]);
	imshow(szChar.GetBuffer(), Test1);

	szChar.Format("Test2(%.1f)", dValue[2]);
	imshow(szChar.GetBuffer(), Test2);

	szChar.Format("Test3(%.1f)", dValue[3]);
	imshow(szChar.GetBuffer(), Test3);

	szChar.Format("Test4(%.1f)", dValue[4]);
	imshow(szChar.GetBuffer(), Test4);

	cv::waitKey(0);
	return 0;
}

