#ifdef _DEBUG
//Debugモードの場合
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc12\\lib\\opencv_world300d.lib")            // opencv_core
#else
//Releaseモードの場合
#pragma comment(lib,"C:\\opencv\\build\\x86\\vc12\\lib\\opencv_world300.lib") 
#endif

#include "acv.hpp"

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;
using namespace cv;


int main(){
	Mat image;
	double i = 0;

	VideoCapture cap(0);
	while (1){
		cap >> image;
		ACV(image, Point(255, 255), 150, 42589,
			sin(i) + 0.1 * rand() / double(RAND_MAX),
			cos(i) + 0.1 * rand() / double(RAND_MAX),
			tan(i) + 0.1 * rand() / double(RAND_MAX),
			-cos(i) + 0.1 * rand() / double(RAND_MAX),
			-sin(i) + 0.1 * rand() / double(RAND_MAX));

		imshow("a", image);
		waitKey(10);
		i += 0.01;
	}
}