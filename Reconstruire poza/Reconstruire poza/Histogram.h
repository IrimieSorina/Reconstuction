#pragma once
#include "Stdafx.h"

class Histogram
{
public:
	Histogram();
	~Histogram();
	std::vector<double> ComputeHistogram(const cv::Mat& image);
	int Thresh(const cv::Mat& image);
	

private:
	std::vector<double> _histogram;
};

