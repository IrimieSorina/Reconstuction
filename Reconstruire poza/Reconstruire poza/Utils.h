#pragma once
#include "Stdafx.h"
using namespace std;

class Utils
{
public:
	Utils();
	~Utils();
	static double GetDistance(const cv::Point &x, const cv::Point &y);
	cv::Mat FindLines(const cv::Mat& image);
	std::vector<cv::Point> FindCenters(const cv::Mat& image);
	std::vector<std::vector<float>> FindDistance(cv::Mat image);
};

