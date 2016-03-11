#pragma once
#include "Stdafx.h"
#include "Utils.h"
class ShapeDescriptor
{
public:
	ShapeDescriptor();
	~ShapeDescriptor();
	void ComputeDescriptorBruteForce(const std::vector<cv::Point> &contour, const cv::Point &center);

private:
	std::vector<double> _descriptor;

	//void findAllObjectLocationsShapeBasedMatching(cv::Mat image, cv::Mat temp, int thresh, cv::Vec);
	//void MatchShapes(cv::Mat image);
};

