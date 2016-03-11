#pragma once
#include <opencv2\core.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <iostream>
#include "Histogram.h"
#include "ExtractContours.h"
#include "Utils.h"
#include "ShapeDescriptor.h"

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
	cv::Mat image = cv::imread("D:/PROJECTS/anul3.1/Proiect licenta/poze/8.bmp");
	ExtractContours extract;
	cv::Mat result = extract.Compute(image);
	
	Utils utils;
	//std::vector<std::vector<float>> distance = utils.FindDistance(image);
	cv::Mat lines = utils.FindLines(result);

	ShapeDescriptor shape;
	


	return 0;
}