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

std::vector<ShapeDescriptor> ShapeDescriptor::Normalize(ShapeDescriptor a, ShapeDescriptor b)
{
	double normalize = 0;
	double firstMax = CalculateMaxim(a);
	double secondMax = CalculateMaxim(b);
	std::vector<ShapeDescriptor> v;
	if (firstMax > secondMax)
	{
		normalize = firstMax - secondMax;
		for (auto i = 0; i < b.length; i++)
		{
			b._descriptor[i] = b._descriptor[i] + normalize;
		}
	}
	else if (secondMax > firstMax)
	{
		normalize = secondMax - firstMax;
		for (auto i = 0; i < a.length; i++)
		{
			a._descriptor[i] = a._descriptor[i] + normalize;
		}	
	}

	v.push_back(a);
	v.push_back(b);
	return v;
}

Indexes ShapeDescriptor::CompareTwoDescriptors(ShapeDescriptor a, ShapeDescriptor b)
{
	std::vector<ShapeDescriptor> shape;
	ShapeDescriptor s;
	shape = s.Normalize(a, b);
	std::vector<std::vector<double>> vector;
	int indexVector = 0;
	for (auto i = 0; i < shape[0].length; i++)//237
	{
		for (auto j = 0; j < shape[1].length; j++)//2400
		{
			std::cout << i <<"+"<<j << std::endl;
			int nr = 0;
			if ((int)shape[0]._descriptor[i] == (int)shape[1]._descriptor[j])
			{
				indexVector++;
				vector.resize(indexVector);
			}
			while ((int)shape[0]._descriptor[i] == (int)shape[1]._descriptor[j])
			{
				
				if (i != shape[0].length - 1 && j != shape[1].length - 1)
				{
					nr++; i++; j++;
				}
				else
					break;
				//if (j != shape[1].length -1)
					//j++;
				//else
					//break;
				vector[indexVector - 1].push_back(shape[0]._descriptor[i]);
			}
			if (nr != 0 && nr < 10)
			{
				for (auto k = 0; k < nr; k++)
				{
					i--; j--;
				}
				indexVector--;
				vector[indexVector].clear();
			}
		}
	}

	int max = vector[0].size();
	int maxLoc = 0;
	for (auto i = 0; i < vector.size(); i++)
	{
		if (max < vector[i].size())
		{
			max = vector[i].size();
			maxLoc = i;
		}
	}

	Indexes index;
	index.first.x = vector[maxLoc][0];
	index.second.x = vector[maxLoc][vector[maxLoc].size() - 1];
	return index;
}

//Indexes ShapeDescriptor::CompareTwoDescriptors(ShapeDescriptor a, ShapeDescriptor b)
//{
//	std::vector<ShapeDescriptor> shape;
//	ShapeDescriptor s;
//	shape = s.Normalize(a, b);
//	std::vector<std::vector<double>> vector(shape[0].length*shape[1].length);
//	Indexes ind;
//	int indiceVector = -1;
//	for (auto i = 0; i < shape[0].length; i++)
//	{
//		for (auto j = 0; j < shape[1].length; j++)
//		{
//			int ii = i, jj = j;
//			if ((int)shape[0]._descriptor[i] == (int)shape[1]._descriptor[j])
//			{
//				indiceVector++;
//				ind.first.x = shape[0]._descriptor[i];
//			}
//
//			while ((int)shape[0]._descriptor[i] == (int)shape[1]._descriptor[j])
//			{
//				
//				vector[indiceVector].push_back(shape[0]._descriptor[j]);
//				if (i != shape[0].length && j != shape[1].length)
//				{
//					i++;
//					j++;
//				}
//				else break;
//				ind.second.x = shape[0]._descriptor[i];
//			}
//			if (indiceVector != -1 && vector[indiceVector].size() < 20)
//			{
//				vector.erase(vector.begin() + indiceVector);
//				indiceVector--;
//			}
//			if (i<shape[0].length && j<shape[1].length)
//			i = ii; j = jj;
//		}
//	}
//	return ind;
//}

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