#include <string>
#include <vector>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

const double PI = 3.14159265;

cv::Mat getMyGabor(int width, int height, int U, int V, double Kmax, double f,
			   double sigma, int ktype, const string kernel_name);

void gabor_filter(cv::Mat& img,vector<cv::Mat> &featureMaps);
