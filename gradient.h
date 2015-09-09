#include <string>
#include <vector>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

//judge the gradient area in terms of (x,y)
template <typename _T>
int Judge( _T x, _T y);

void FeaExtractByGradient(cv::Mat img,vector<cv::Mat> &featureMaps);
