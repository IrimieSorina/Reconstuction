#pragma once
#include "Stdafx.h"
//#include "ShapeDescriptor.h"
using namespace std;

struct Indexes
{
	cv::Point first;
	cv::Point second;

};

class Utils
{
public:
	Utils();
	~Utils();
	
	//Indexes CompareTwoDescriptors(ShapeDescriptor a, ShapeDescriptor b);
	static double GetDistance(const cv::Point &x, const cv::Point &y);
	static cv::Mat FindLines(const cv::Mat& image);
	static std::vector<cv::Point> FindCenters(const cv::Mat& image);
	static std::vector<std::vector<float>> FindDistance(cv::Mat image);
};

