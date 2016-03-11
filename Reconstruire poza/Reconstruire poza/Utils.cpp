#include "Utils.h"
#include "ExtractContours.h"
#include "Histogram.h"
using namespace cv;
using namespace std;

Utils::Utils()
{
}


Utils::~Utils()
{
}
double Utils::GetDistance(const cv::Point &a, const cv::Point &b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}
cv::Mat Utils::FindLines(const cv::Mat& image)
{
	vector<Vec4i> lines;
	cv::Mat result = image.clone();
	cv::Mat finalResult = image.clone();
	cvtColor(result, result, CV_BGR2GRAY);

	HoughLinesP(result, lines, 1, CV_PI / 180, 120, 70, 50);
	for (size_t i = 0; i < lines.size(); i++)
	{
		/*cv::Vec4i v = lines[i];
		lines[i][0] = 0;
		lines[i][1] = ((float)v[1] - v[3]) / (v[0] - v[2]) * -v[0] + v[1];
		lines[i][2] = image.cols;
		lines[i][3] = ((float)v[1] - v[3]) / (v[0] - v[2]) * (image.cols - v[2]) + v[3];*/
		line(finalResult, Point(lines[i][0], lines[i][1]), Point(lines[i][2], lines[i][3]), Scalar(0, 0, 255), 1, 8);
	}
	return finalResult;
}

std::vector<cv::Point> Utils::FindCenters(const cv::Mat& image)
{
	ExtractContours extract;
	std::vector<std::vector<cv::Point> > contours;
	cv::Mat imageGray = image.clone();
	contours = extract.FindContours(imageGray);
	vector<cv::Point> center(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		vector<Moments> mu(contours[i].size());
		mu[i] = moments(contours[i], false);

		center[i] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
	}

	return center;
}

std::vector<std::vector<float>> Utils::FindDistance(cv::Mat image)
{
	ExtractContours extract;
	std::vector<std::vector<cv::Point> > contours;
	cv::Mat imageGray = image.clone();
	cv::cvtColor(image, imageGray, cv::COLOR_BGR2GRAY);

	cv::Mat imageBinarization = imageGray.clone();
	Histogram histo;
	int nr = histo.Thresh(imageBinarization);
	cv::threshold(imageBinarization, imageBinarization, nr, 255, THRESH_BINARY);

	contours = extract.FindContours(imageBinarization);
	vector<cv::Point> center = FindCenters(imageBinarization);

	std::vector<std::vector<float>> distance(contours.size());
	for (int i = 0; i < contours.size(); i++)
	{
		for (int j = 0; j < contours[i].size(); j++)
		{
			distance[i].push_back(sqrt((center[i].x - contours[i][j].x)*(center[i].x - contours[i][j].x) + 
				(center[i].y - contours[i][j].y)*(center[i].y - contours[i][j].y)));
		}
	}
	return distance;
}