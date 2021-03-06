

#include "stdafx.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cmath>
#include <iostream>



static double angle(cv::Point pt1, cv::Point pt2, cv::Point pt0)
{
	double dx1 = pt1.x - pt0.x;
	double dy1 = pt1.y - pt0.y;
	double dx2 = pt2.x - pt0.x;
	double dy2 = pt2.y - pt0.y;
	return (dx1*dx2 + dy1 * dy2) / sqrt((dx1*dx1 + dy1 * dy1)*(dx2*dx2 + dy2 * dy2) + 1e-10);
}


void setLabel(cv::Mat& im, const std::string label, std::vector<cv::Point>& contour)
{
	int fontface = cv::FONT_HERSHEY_SIMPLEX;
	double scale = 0.4;
	int thickness = 1;
	int baseline = 0;

	cv::Size text = cv::getTextSize(label, fontface, scale, thickness, &baseline);
	cv::Rect r = cv::boundingRect(contour);

	cv::Point pt(r.x + ((r.width - text.width) / 2), r.y + ((r.height + text.height) / 2));
	cv::rectangle(im, pt + cv::Point(0, baseline), pt + cv::Point(text.width, -text.height), CV_RGB(255, 255, 255), CV_FILLED);
	cv::putText(im, label, pt, fontface, scale, CV_RGB(0, 0, 0), thickness, 8);
}

int main()
{
	cv::Mat frame;
	/*std::string vidUrl;
	std::cin >> vidUrl;
	std::cout << vidUrl;
	//cv::VideoCapture vid("http://192.168.0.19:8080/video");*/
	cv::Mat src;
	
		
		src = cv::imread("8.jpg");
		cv::Point der(0, 270);
		cv::Point da(1800, 2400);
		src = src(cv::Rect(der, da));

		// Convert to grayscale
		cv::Mat gray;
		cv::cvtColor(src, gray, CV_BGR2GRAY);

		// Use Canny instead of threshold to catch squares with gradient shading
		cv::Mat bw;
		cv::Mat ds;
		
		cv::threshold(gray, ds, 94, 255, 3);
		
		cv::Canny(ds, bw, 6, 20, 5);
		cv::namedWindow("bwW", CV_WINDOW_FREERATIO);
		cv::imshow("bwW", ds);
	
		
		
		// Find contours
		std::vector<std::vector<cv::Point> > contours;
		cv::findContours(bw.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	
		std::vector<cv::Point> approx;
		cv::Mat dst = src.clone();
	
		for (int i = 0; i < contours.size(); i++)
		{
			
			// Approximate contour with accuracy proportional
			// to the contour perimeter
			cv::approxPolyDP(cv::Mat(contours[i]), approx, cv::arcLength(cv::Mat(contours[i]), true)*0.02, true);
			
		
			// Skip small or non-convex objects 
			if (std::fabs(cv::contourArea(contours[i])) < 100 || !cv::isContourConvex(approx))
				continue;
			

			if (approx.size() == 3)
			{
				setLabel(dst, "TRI", contours[i]);    // Triangles
			}
			
		
		}
		cv::namedWindow("srcW", CV_WINDOW_FREERATIO);
		cv::imshow("srcW", src);
		cv::namedWindow("dstW", CV_WINDOW_FREERATIO);
		cv::imshow("dstW", dst);
		
	
	
	cv::waitKey();
	
	
	return 0;
	}
	/*
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

/// Global variables

Mat src, src_gray;
Mat dst, detected_edges;

int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int ratio = 8;
int kernel_size = 3;
const char* window_name = "Edge Map";



void CannyThreshold(int, void*)
{

	/// Reduce noise with a kernel 3x3
	blur(src, detected_edges, Size(50, 50));

	cv::namedWindow("niper", CV_WINDOW_FREERATIO);
	cv::imshow("niper", detected_edges);
	
	

	cvtColor(src, detected_edges, CV_BGR2GRAY);




	cv::namedWindow("nipera", CV_WINDOW_FREERATIO);
	imshow("nipera", src);
	
	
	/// Canny detector
	Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size);

	/// Using Canny's output as a mask, we display our result
	dst = Scalar::all(0);

	src.copyTo(dst, detected_edges);
	imshow(window_name, dst);
}



int main(int argc, char** argv)
{
	/// Load an image
	src = imread("7.jpg");

	cv::Point der(0, 270);
	cv::Point da(1800, 2400);
	src = src(cv::Rect(der, da));

	if (!src.data)
	{
		return -1;
	}


	/// Create a matrix of the same type and size as src (for dst)
	dst.create(src.size(), src.type());

	/// Convert the image to grayscale
	cvtColor(src, src_gray, CV_BGR2GRAY);

	/// Create a window
	namedWindow(window_name, CV_WINDOW_FREERATIO);

	/// Create a Trackbar for user to enter threshold
	createTrackbar("Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold);

	/// Show the image
	CannyThreshold(0, 0);

	/// Wait until user exit program by pressing a key
	waitKey(0);

	return 0;
} */

