#pragma once
#include "Stdafx.h"
#include "ShapeDescriptor.h"
class ExtractContours
{
public:
	ExtractContours();
	~ExtractContours();
	std::vector<std::vector<cv::Point>> FindContours(cv::Mat image);
	std::vector<ShapeDescriptor> GetContours(cv::Mat image, cv::Mat result);
	cv::Mat Compute(cv::Mat image);
	cv::Mat Binarization(cv::Mat image, cv::Mat result);
	
};

