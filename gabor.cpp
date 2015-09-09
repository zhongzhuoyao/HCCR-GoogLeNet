#include "gabor.h"

cv::Mat getMyGabor(int width, int height, int U, int V, double Kmax, double f,
			   double sigma, int ktype, const string kernel_name)
{
	int half_width = width / 2;
	int half_height = height / 2;
	double Qu = PI*U/8;
	double sqsigma = sigma*sigma;
	double Kv = Kmax/pow(f,V);
	double postmean = exp(-sqsigma/2);

	cv::Mat kernel_re(width, height, ktype);
	cv::Mat kernel_im(width, height, ktype);
	cv::Mat kernel_mag(width, height, ktype);

	double tmp1, tmp2, tmp3;
	for(int j = -half_height; j <= half_height; j++){
		for(int i = -half_width; i <= half_width; i++){
			tmp1 = exp(-(Kv*Kv*(j*j+i*i))/(2*sqsigma));
			tmp2 = cos(Kv*cos(Qu)*i + Kv*sin(Qu)*j) - postmean;
			tmp3 = sin(Kv*cos(Qu)*i + Kv*sin(Qu)*j);

			kernel_re.at<float>(j+half_height, i+half_width) =
				(float)(Kv*Kv*tmp1*tmp2/sqsigma);

			kernel_im.at<float>(j+half_height, i+half_width) =
				(float)(Kv*Kv*tmp1*tmp3/sqsigma);
		}
	}

	magnitude(kernel_re, kernel_im, kernel_mag);

	if(kernel_name.compare("real") == 0)
		return kernel_re;
	else if(kernel_name.compare("imag") == 0)
		return kernel_im;
	else{
		printf("Invalid kernel name!\n");
		return kernel_mag;
	}
}

void gabor_filter(cv::Mat& img,vector<cv::Mat> &featureMaps)
{
	//cv::Mat img input character image
	const int kernel_size = 7; // should be odd
	// variables for gabor filter
	double Kmax = PI/2;
	double f = sqrt(2.0);
	double sigma = 2*PI;
	int U = 0;
	int V = 0;
	int GaborH = kernel_size;
	int GaborW = kernel_size;
	int UStart = 0, UEnd = 8;
	int VStart = 1, VEnd = 2;
	// variables for filter2D
	cv::Point archor(-1,-1);
	int ddepth = CV_32F;//CV_64F
	//double delta = 0;
	//eight orientation in terms of one frequnecy
	for(V = VStart; V < VEnd; V++){
		for(U = UStart; U < UEnd; U++){
			cv::Mat kernel_re, kernel_im;
			cv::Mat dst_re, dst_im, dst_mag;
			kernel_re = getMyGabor(GaborW, GaborH, U, V,
				Kmax, f, sigma, CV_32F, "real");
			kernel_im = getMyGabor(GaborW, GaborH, U, V,
				Kmax, f, sigma, CV_32F, "imag");
			// flip kernel
			// Gabor kernel is symmetric, so do not need flip
			filter2D(img, dst_re, ddepth, kernel_re);
			filter2D(img, dst_im, ddepth, kernel_im);

			dst_mag.create(img.rows, img.cols, CV_32FC1);
			magnitude(cv::Mat(dst_re),cv::Mat(dst_im),
				dst_mag);
			//normalize gabor kernel
			cv::normalize(dst_mag, dst_mag, 0, 255, CV_MINMAX);
			dst_mag.convertTo(dst_mag,CV_8U);		
			featureMaps.push_back(dst_mag);
			kernel_re.release();
			kernel_im.release();
			dst_re.release();
			dst_im.release();
			dst_mag.release();
		}
	}
}
