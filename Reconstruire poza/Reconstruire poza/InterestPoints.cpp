#include "InterestPoints.h"
#include "ExtractContours.h"
using namespace cv;
using namespace std;

InterestPoints::InterestPoints()
{
}


InterestPoints::~InterestPoints()
{
}

//void InterestPoints::getGaussianDerivs(double sigma, int M, vector<double>& gaussian, vector<double>& dg, vector<double>& d2g) {
//	int L = (M - 1) / 2;
//	double sigma_sq = sigma * sigma;
//	double sigma_quad = sigma_sq*sigma_sq;
//	dg.resize(M); 
//	d2g.resize(M); 
//	gaussian.resize(M);
//
//	Mat_<double> g = getGaussianKernel(M, sigma, CV_64F);
//	for (double i = -L; i < L + 1.0; i += 1.0)
//	{
//		int idx = (int)(i + L);
//		gaussian[idx] = g(idx);
//		dg[idx] = (-i / sigma_sq) * g(idx);
//		d2g[idx] = (-sigma_sq + i*i) / sigma_quad * g(idx);
//	}
//}
//
//void InterestPoints::getdX(vector<double> x,
//	int n,
//	double sigma,
//	double& gx,
//	double& dgx,
//	double& d2gx,
//	vector<double> g,
//	vector<double> dg,
//	vector<double> d2g,
//	bool isOpen = false)
//{
//	int L = (g.size() - 1) / 2;
//
//	gx = dgx = d2gx = 0.0;
//	for (int k = -L; k < L + 1; k++) {
//		double x_n_k = 0;
//		if (n - k < 0) {
//			if (isOpen) {
//				//open curve - mirror values on border
//				x_n_k = x[-(n - k)];
//			}
//			else {
//				//closed curve - take values from end of curve
//				x_n_k = x[x.size() + (n - k)];
//			}
//		}
//		else if (n - k > x.size() - 1) {
//			if (isOpen) {
//				//mirror value on border
//				x_n_k = x[n + k];
//			}
//			else {
//				x_n_k = x[(n - k) - (x.size())];
//			}
//		}
//		else {
//			x_n_k = x[n - k];
//		}
//
//		gx += x_n_k * g[k + L]; //gaussians go [0 -> M-1]
//		dgx += x_n_k * dg[k + L];
//		d2gx += x_n_k * d2g[k + L];
//	}
//}
//
//void InterestPoints::getdXcurve(vector<double> x,
//	double sigma,
//	vector<double>& gx,
//	vector<double>& dx,
//	vector<double>& d2x,
//	vector<double> g,
//	vector<double> dg,
//	vector<double> d2g,
//	bool isOpen = false)
//{
//	gx.resize(x.size());
//	dx.resize(x.size());
//	d2x.resize(x.size());
//	for (int i = 0; i<x.size(); i++) {
//		double gausx, dgx, d2gx; getdX(x, i, sigma, gausx, dgx, d2gx, g, dg, d2g, isOpen);
//		gx[i] = gausx;
//		dx[i] = dgx;
//		d2x[i] = d2gx;
//	}
//}
//
//void InterestPoints::PolyLineSplit(const vector<Point2d>& pl, vector<double>& contourx, vector<double>& contoury) {
//	contourx.resize(pl.size());
//	contoury.resize(pl.size());
//
//	for (int j = 0; j<pl.size(); j++)
//	{
//		contourx[j] = (double)(pl[j].x);
//		contoury[j] = (double)(pl[j].y);
//	}
//}
//
//void InterestPoints::PolyLineMerge(vector<Point2d>& pl, const vector<double>& contourx, const vector<double>& contoury) {
//	assert(contourx.size() == contoury.size());
//	pl.resize(contourx.size());
//	for (int j = 0; j<contourx.size(); j++) {
//		pl[j].x = contourx[j];
//		pl[j].y = contoury[j];
//	}
//}
//
//void InterestPoints::ResampleCurve(const vector<double>& curvex, const vector<double>& curvey,
//	vector<double>& resampleX, vector<double>& resampleY, int N, bool isOpen)
//{
//	assert(curvex.size()>0 && curvey.size()>0 && curvex.size() == curvey.size());
//
//	vector<Point2d> resamplepl(N);
//	resamplepl[0].x = curvex[0]; resamplepl[0].y = curvey[0];
//	vector<Point2i> pl; 
//	PolyLineMerge(pl, curvex, curvey);
//
//	double pl_length = arcLength(pl, false);
//	double resample_size = pl_length / (double)N;
//	int curr = 0;
//	double dist = 0.0;
//	for (int i = 1; i<N;) {
//		assert(curr < pl.size() - 1);
//		double last_dist = norm(pl[curr] - pl[curr + 1]);
//		dist += last_dist;
//		if (dist >= resample_size) {
//			//put a point on line
//			double _d = last_dist - (dist - resample_size);
//			Point2d cp(pl[curr].x, pl[curr].y), cp1(pl[curr + 1].x, pl[curr + 1].y);
//			Point2d dirv = cp1 - cp; dirv = dirv * (1.0 / norm(dirv));
//			assert(i < resamplepl.size());
//			resamplepl[i] = cp + dirv * _d;
//			i++;
//
//			dist = last_dist - _d; //remaining dist         
//
//			//if remaining dist to next point needs more sampling... (within some epsilon)
//			while (dist - resample_size > 1e-3) {
//				assert(i < resamplepl.size());
//				resamplepl[i] = resamplepl[i - 1] + dirv * resample_size;
//				dist -= resample_size;
//				i++;
//			}
//		}
//
//		curr++;
//	}
//
//	PolyLineSplit(resamplepl, resampleX, resampleY);
//}
//
///* compute curvature of curve after gaussian smoothing
//from "Shape similarity retrieval under affine transforms", Mokhtarian & Abbasi 2002
//curvex - x position of points
//curvey - y position of points
//kappa - curvature coeff for each point
//sigma - gaussian sigma
//*/
//void InterestPoints::ComputeCurveCSS(const vector<double>& curvex,
//	const vector<double>& curvey,
//	vector<double>& kappa,
//	vector<double>& smoothX, vector<double>& smoothY,
//	double sigma,
//	bool isOpen
//	)
//{
//	int M = round((10.0*sigma + 1.0) / 2.0) * 2 - 1;
//	assert(M % 2 == 1); //M is an odd number
//
//	vector<double> g, dg, d2g; getGaussianDerivs(sigma, M, g, dg, d2g);
//
//	vector<double> X, XX, Y, YY;
//	getdXcurve(curvex, sigma, smoothX, X, XX, g, dg, d2g, isOpen);
//	getdXcurve(curvey, sigma, smoothY, Y, YY, g, dg, d2g, isOpen);
//
//	kappa.resize(curvex.size());
//	for (int i = 0; i<curvex.size(); i++) {
//		// Mokhtarian 02' eqn (4)
//		kappa[i] = (X[i] * YY[i] - XX[i] * Y[i]) / pow(X[i] * X[i] + Y[i] * Y[i], 1.5);
//	}
//}
//
//vector<int> InterestPoints::FindCSSInterestPoints(const vector<double>& kappa) {
//	vector<int> crossings;
//	for (int i = 0; i<kappa.size() - 1; i++) {
//		if ((kappa[i] < 0 && kappa[i + 1] > 0) || kappa[i] > 0 && kappa[i + 1] < 0) {
//			crossings.push_back(i);
//		}
//	}
//	return crossings;
//}