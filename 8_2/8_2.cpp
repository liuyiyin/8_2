// 8_2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	cv::Mat src = imread("D:\\die_on_chip.png", 0);
	cv::Mat dst;

	threshold(src, dst, 150, 250, THRESH_BINARY);

	vector<vector<Point>> contours;
	findContours(dst, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	for (int i = 0; i < contours.size(); i++) {

		RotatedRect rbox = minAreaRect(contours[i]);
		rbox.angle = 0;
		float width = rbox.size.width;
		float height = rbox.size.height;
		float a = width / height;

		if (a > 0.9&&a< 1.1) {
			drawContours(src, contours, i, Scalar(0, 255, 255), 1, 8);
			cv::Point2f vtx[4];
			rbox.points(vtx);
			for (int i = 0; i < 4; ++i) {
				cv::line(src, vtx[i], vtx[i < 3 ? i + 1 : 0], cv::Scalar(0, 0, 255), 2, CV_AA);
			}
		}
	}

	cv::imshow("src", src);
	waitKey(0);
	return 0;
}

