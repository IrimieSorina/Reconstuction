#include "ShapeDescriptor.h"
#include "ExtractContours.h"

ShapeDescriptor::ShapeDescriptor()
{
}


ShapeDescriptor::~ShapeDescriptor()
{
}

void ShapeDescriptor::ComputeDescriptorBruteForce(const std::vector<cv::Point> &contour, const cv::Point &center)
{
	_descriptor.clear();
	for (auto i = 0; i < contour.size(); i++)
	{
		_descriptor.push_back(Utils::GetDistance(center, contour[i]));
		std::cout << _descriptor[i] << std::endl;
	}

}

//
//void ShapeDescriptor::MatchShapes(cv::Mat image)
//{
//	std::vector<std::vector<cv::Point>> contours;
//	ExtractContours extract;
//	cv::Mat imageBinarization = image.clone();
//	imageBinarization = extract.Binarization(image, imageBinarization);
//	contours = extract.FindContours(imageBinarization);
//	std::vector<std::vector<double>> res(contours.size());
//	for (int i = 0; i < contours.size(); i++)
//	{
//		for (int j = 0; j < contours.size(); j++)
//		{
//			if (contours[i] != contours[j])
//			{
//				res[i].push_back(cv::matchShapes(contours[i], contours[j], CV_CONTOURS_MATCH_I1, 0));
//			}
//			else
//				res[i].push_back(100);
//		}
//	}
//}