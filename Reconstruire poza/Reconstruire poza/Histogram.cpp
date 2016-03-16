#include "Histogram.h"


Histogram::Histogram()
{
}


Histogram::~Histogram()
{
}

std::vector<double> Histogram::ComputeHistogram(const cv::Mat& image)
{
	_histogram.resize(256);
	for (size_t i = 0; i < image.cols; i++)
	{
		for (size_t j = 0; j < image.rows; j++)
		{
			uchar value = image.at<uchar>(cv::Point(i, j));
			_histogram[value]++;
		}
	}
	return _histogram;
}



//int Histogram::Thresh(const cv::Mat& image)
//{
//	int sum = 0;
//	int nr = 0;
//	for (size_t i = 0; i < 20; i++)
//	{
//		for (size_t j = 0; j < 20; j++)
//		{
//			sum += image.at<uchar>(cv::Point(i, j));
//			nr++;
//		}
//	}
//	for (size_t i = image.cols-1; i > image.cols - 20; i--)
//	{
//		for (size_t j = image.rows - 1; j < image.cols - 20; j--)
//		{
//			sum += image.at<uchar>(cv::Point(i, j));
//			nr++;
//		}
//	}
//	for (size_t i = 0; i < 20; i++)
//	{
//		for (size_t j = image.rows - 1; j < image.cols - 20; j--)
//		{
//			sum += image.at<uchar>(cv::Point(i, j));
//			nr++;
//		}
//	}
//	int ma = sum / nr;
//	return ma;
//}


int Histogram::Thresh(const cv::Mat& image)
{
	std::vector<double> hist;
	hist = ComputeHistogram(image);
	double maxv, minv;
	cv::Point maxloc, minloc;
	cv::minMaxLoc(hist, &minv, &maxv, &minloc, &maxloc);
	double prag = 0.02 * maxv;
	int thresh = 0;
	for (int i = maxloc.x+1; i < 255; i++)
	{
		if (hist[i] < prag)
		{			
			thresh = i;
			break;
		}
	}
	return thresh;
}