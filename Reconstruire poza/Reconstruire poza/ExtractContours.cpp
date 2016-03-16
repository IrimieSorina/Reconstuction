#include "ExtractContours.h"
#include "Histogram.h"
#include "Utils.h"

using namespace cv;
using namespace std;

ExtractContours::ExtractContours()
{
}


ExtractContours::~ExtractContours()
{
}

cv::Mat ExtractContours::Binarization(cv::Mat image, cv::Mat result)
{
	cv::Mat imageGray = image.clone();
	cv::cvtColor(image, imageGray, cv::COLOR_BGR2GRAY);
	cv::bilateralFilter(imageGray, result, 0, 10, 10);
	Histogram histo;
	int nr = histo.Thresh(imageGray);
	//histograma -> pragul pica unde se termina gausianul
	cv::threshold(imageGray, result, nr, 255, CV_ADAPTIVE_THRESH_MEAN_C);
	return result;
}

std::vector<std::vector<cv::Point>> ExtractContours::FindContours(cv::Mat image)
{
	std::vector<std::vector<cv::Point> > contours;
	cv::Mat contourOutput = image.clone();
	cv::findContours(contourOutput, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
	std::vector<std::vector<cv::Point> > contoursResult;
	for (int i = 0; i < contours.size(); i++)
	{
		if (cv::contourArea(contours[i])> 40000)
		{
			contoursResult.push_back(contours[i]);
		}
	}
	return contoursResult;
}

std::vector<ShapeDescriptor> ExtractContours::GetContours(cv::Mat image, cv::Mat result)
{
	std::vector<std::vector<cv::Point> > contours;
	contours = FindContours(image);
	vector<cv::Point> centers(contours.size());

	Utils utils;
	centers = utils.FindCenters(image);
	std::vector<ShapeDescriptor> allDistance;
	for (int i = 0; i < contours.size(); i++)
	{
		/*
	    cv::RotatedRect rr = cv::minAreaRect(contours[i]);

		Point2f * pts = new Point2f[4];
		rr.points(pts);
		for (int j = 0; j < 3; j++)
		{
			cv::line(result, pts[j], pts[j + 1], cv::Scalar(0, 0, 255), 2
		}
		cv::line(result, pts[3], pts[0], cv::Scalar(0, 0, 255), 2);
		*/
        /*
		for (int j = 0; j < contours[i].size(); j++)
		{
			cv::circle(imageContours, contours[i][j], 1, cv::Scalar(j / 3), 2);
		}
		*/

		//cv::approxPolyDP(contours[i], contours[i], contours[i].size()*0.003, true);
		cv::drawContours(result, contours, i, cv::Scalar(255, 255, 255));
		circle(result, centers[i], 4, cv::Scalar(255, 255, 255), -1);

		ShapeDescriptor distance;
		distance.ComputeDescriptorBruteForce(contours[i], centers[i]);
		allDistance.push_back(distance);
	}

	return allDistance;
}

void ExtractContours::Test(std::vector<ShapeDescriptor> des)
{
	ShapeDescriptor s;
	Indexes index;
	std::vector<double> v;
	for (auto i = 0; i < des.size(); i++)
	{
		for (auto j = 0; j < des.size(); j++)
		{
			if (i != j)
			{
				//index = s.CompareTwoDescriptors(des[i], des[j]);
				index = s.CompareTwoDescriptors(des[i], des[j]);
			}
		}
	}

}

cv::Mat ExtractContours::Compute(cv::Mat image)
{
	cv::Mat imageBinarization = image.clone();
	imageBinarization =	Binarization(image, imageBinarization);
	
	cv::erode(imageBinarization, imageBinarization, cv::Mat());
	cv::Mat imageContours(image.size(), CV_8UC3, cv::Scalar(0, 0, 0));
	std::vector<ShapeDescriptor> sd = GetContours(imageBinarization, imageContours);
	Test(sd);
	return imageContours;
}
