#pragma once
#include "Stdafx.h"
#include "Utils.h"
class ShapeDescriptor
{
public:
	int length;

	ShapeDescriptor();
	~ShapeDescriptor();
	double CalculateMaxim(ShapeDescriptor a);
	std::vector<ShapeDescriptor> Normalize(ShapeDescriptor a, ShapeDescriptor b);
	void ComputeDescriptorBruteForce(const std::vector<cv::Point> &contour, const cv::Point &center);
	Indexes CompareTwoDescriptors(ShapeDescriptor a, ShapeDescriptor b);
	//void MatchShapes(cv::Mat image);

public:
	std::vector<double> _descriptor;
	
	
};

