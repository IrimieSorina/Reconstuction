#include "ShapeDescriptor.h"
#include "ExtractContours.h"

ShapeDescriptor::ShapeDescriptor()
{
}


ShapeDescriptor::~ShapeDescriptor()
{
}

double ShapeDescriptor::CalculateMaxim(ShapeDescriptor a)
{
	double maxim = 0;
	for (auto i = 0; i < a.length; i++)
	{
		if (a._descriptor[i] > maxim)
			maxim = a._descriptor[i];
	}
	return maxim;
}

void ShapeDescriptor::Normalize(ShapeDescriptor& a)
{
	double max = CalculateMaxim(a);
	
	for (auto i = 0; i < a.length; i++)
    {
		a._descriptor[i] = 10000*a._descriptor[i] / (double)max;
	}
	
	
}

Indexes ShapeDescriptor::CompareTwoDescriptors(ShapeDescriptor a, ShapeDescriptor b)
{

	std::vector<Indexes> indexes;
	
	for (auto i = 0; i < a.length; i++)
	{
		for (auto j = 0; j < b.length; j++)
		{
			if (abs((int)a._descriptor[i] - (int)b._descriptor[j]) < 2)
			{
				int nr = 0;
				Indexes aux;
				aux.first.x = i;
				aux.second.x = j;
				while (abs((int)a._descriptor[i+nr] - (int)b._descriptor[j+nr]) < 2)
				{

					if (i+nr != a.length - 1 && j+nr != b.length - 1)
					{
						nr++; 
					}
					else
						break;
					
				}
				aux.first.y = i+nr;
				aux.second.y = j+nr;
				indexes.push_back(aux);
			}
			
		}
	}

	int max = 0;
	int maxLoc = 0;
	for (auto i = 0; i < indexes.size(); i++)
	{
		if (indexes[i].first.y - indexes[i].first.x > max)
		{
			max = indexes[i].first.y - indexes[i].first.x;
			maxLoc = i;
		}
	}
	
	return indexes[maxLoc];
}

void ShapeDescriptor::ComputeDescriptorBruteForce(const std::vector<cv::Point> &contour, const cv::Point &center)
{
	_descriptor.clear();
	for (auto i = 0; i < contour.size(); i++)
	{
		_descriptor.push_back(Utils::GetDistance(center, contour[i]));
		//std::cout << _descriptor[i] << std::endl;
	}
	length = contour.size();
}


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