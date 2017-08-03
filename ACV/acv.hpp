#ifndef ACV_HPP
#define ACV_HPP


#include "opencv2/opencv.hpp"

#define _USE_MATH_DEFINES
#include <math.h>



void ACV(cv::Mat img, cv::Point cent, int size, double gauge_max1, double gauge1, double gauge2, double gauge3, double gauge4, double gauge5){
	cv::Mat image(img.size(), img.type(), cv::Scalar::all(0));

	cv::Point center = cent;
	double r1 = size;
	double Rrate = 0.94;
	double r2 = r1 * Rrate;
	double r3 = r1 * 1.04;
	double r4 = r1 * 1.10;
	double r5 = r1 * 1.02;
	double r6 = r1 * 1.05;

	int L = 180;
	int R = 0;
	int R2 = 360;
	int U = 270;
	int D = 90;
	double deg_lro = 10;
	double deg_lri = 11;
	double deg_udi = 3;

	cv::Scalar color1(100, 100, 100);
	cv::Scalar color2(0, 100, 0);
	cv::Scalar color3(0, 0, 100);

	double gauge_ru = std::min(std::max(0.0, gauge1), 1.0);
	double gauge_ru2 = std::min(std::max(0.0, gauge2), 1.0);
	double gauge_rd = std::min(std::max(0.0, gauge3), 1.0);
	double gauge_lu = std::min(std::max(0.0, gauge4), 1.0);
	double gauge_ld = std::min(std::max(0.0, gauge5), 1.0);

	//U circle
	ellipse(image, center, cv::Size(r1, r1), 0, L + deg_lro, R2 - deg_lro, color1, 1, CV_AA);
	//D circle
	ellipse(image, center, cv::Size(r1, r1), 0, R + deg_lro, L - deg_lro, color1, 1, CV_AA);

	//左上
	for (int i = r2 + 1; i < r1; i++){
		ellipse(image, center, cv::Size(i, i), 0,
			U - deg_udi - gauge_lu * ((U - deg_udi) - (L + deg_lri)),
			U - deg_udi,
			color2, 1, CV_AA);
	}
	ellipse(image, center, cv::Size(r2, r2), 0,
		L + deg_lri,
		U - deg_udi,
		color1, 1, CV_AA);
	//右上
	for (int i = r2 + 1; i < r1; i++){
		ellipse(image, center, cv::Size(i, i), 0,
			U + deg_udi,
			U + deg_udi + gauge_ru * ((R2 - deg_lri) - (U + deg_udi)),
			color2, 1, CV_AA);
	}
	for (int i = r5; i < r6; i++){
		ellipse(image, center, cv::Size(i, i), 0,
			U + deg_udi,
			U + deg_udi + gauge_ru2 * ((R2 - deg_lri) - (U + deg_udi) + 1),
			color2, 1, CV_AA);
	}
	ellipse(image, center, cv::Size(r2, r2), 0,
		U + 3,
		R2 - deg_lri,
		color1, 1, CV_AA);
	//右下
	for (int i = r3; i < r4; i++){
		ellipse(image, center, cv::Size(i, i), 0,
			D - deg_udi + gauge_rd * ((R)-(D - deg_udi)),
			D - deg_udi,
			color2, 1, CV_AA);
	}
	ellipse(image, center, cv::Size(r3, r3), 0,
		R,
		D - deg_udi,
		color2, 1, CV_AA);

	ellipse(image, center, cv::Size(r2, r2), 0,
		R + deg_lri,
		D - deg_udi,
		color1, 1, CV_AA);
	//左下
	for (int i = r3; i < r4; i++){
		ellipse(image, center, cv::Size(i, i), 0,
			D + deg_udi,
			D + deg_udi + gauge_ld * ((L)-(D + deg_udi)),
			color2, 1, CV_AA);
	}
	ellipse(image, center, cv::Size(r3, r3), 0,
		D + deg_udi,
		L,
		color2, 1, CV_AA);

	ellipse(image, center, cv::Size(r2, r2), 0,
		D + deg_udi,
		L - deg_lri,
		color1, 1, CV_AA);


	double rate = 0.15;
	double rate2 = 3;
	double angle = deg_lro * M_PI / 180.0;
	//右下
	line(image,
		cv::Point(center.x + r1 * cos(angle), center.y + r1 * sin(angle)),
		cv::Point(center.x + r1 * cos(angle) - (r1 * rate), center.y + r1 * sin(angle)),
		color1, 1, CV_AA);

	//右上
	angle = -deg_lro * M_PI / 180.0;
	line(image,
		cv::Point(center.x + r1 * cos(angle), center.y + r1 * sin(angle)),
		cv::Point(center.x + r1 * cos(angle) - (r1 * rate), center.y + r1 * sin(angle)),
		color1, 1, CV_AA);
	line(image,
		cv::Point(center.x + r1 * cos(angle) + (r5 - r1), center.y + r1 * sin(angle)),
		cv::Point(center.x + r1 * cos(angle) + (r5 - r1) + 2 * (r6 - r5), center.y + r1 * sin(angle)),
		color2, 1, CV_AA);

	//右外
	angle = (L + deg_lro) * M_PI / 180.0;
	line(image,
		cv::Point(center.x + r3, center.y),
		cv::Point(center.x + r4 + (r4 - r3), center.y),
		color2, 1, CV_AA);
	angle = (L + deg_lro) * M_PI / 180.0;
	line(image,
		cv::Point(center.x + r3, center.y - r1 * 0.02),
		cv::Point(center.x + r4 + (r4 - r3), center.y - r1 * 0.02),
		color2, 1, CV_AA);

	//左下
	angle = (L - deg_lro) * M_PI / 180.0;
	line(image,
		cv::Point(center.x + r1 * cos(angle), center.y + r1 * sin(angle)),
		cv::Point(center.x + r1 * cos(angle) + (r1 * rate), center.y + r1 * sin(angle)),
		color1, 1, CV_AA);

	//左上
	angle = (L + deg_lro) * M_PI / 180.0;
	line(image,
		cv::Point(center.x + r1 * cos(angle), center.y + r1 * sin(angle)),
		cv::Point(center.x + r1 * cos(angle) + (r1 * rate), center.y + r1 * sin(angle)),
		color1, 1, CV_AA);

	//左外
	angle = (L + deg_lro) * M_PI / 180.0;
	line(image,
		cv::Point(center.x - r3, center.y),
		cv::Point(center.x - r4 - (r4 - r3), center.y),
		color2, 1, CV_AA);
	angle = (L + deg_lro) * M_PI / 180.0;
	line(image,
		cv::Point(center.x - r3, center.y - r1 * 0.02),
		cv::Point(center.x - r4 - (r4 - r3), center.y - r1 * 0.02),
		color2, 1, CV_AA);

	//下右
	angle = (D - deg_udi) * M_PI / 180.0;
	line(image,
		cv::Point(center.x + r1 * cos(angle), center.y + r1 * sin(angle) + (r4 - r1)),
		cv::Point(center.x + r1 * cos(angle), center.y + r1 * sin(angle) - (r1 * rate)),
		color1, 1, CV_AA);

	//下左
	angle = (D + deg_udi) * M_PI / 180.0;
	line(image,
		cv::Point(center.x + r1 * cos(angle), center.y + r1 * sin(angle) + (r4 - r1)),
		cv::Point(center.x + r1 * cos(angle), center.y + r1 * sin(angle) - (r1 * rate)),
		color1, 1, CV_AA);

	//上左
	angle = (U - deg_udi) * M_PI / 180.0;
	line(image,
		cv::Point(center.x + r1 * cos(angle), center.y + r1 * sin(angle)),
		cv::Point(center.x + r1 * cos(angle), center.y + r1 * sin(angle) + (r1 * rate)),
		color1, 1, CV_AA);

	//上右
	angle = (U + deg_udi) * M_PI / 180.0;
	line(image,
		cv::Point(center.x + r1 * cos(angle), center.y + r1 * sin(angle)),
		cv::Point(center.x + r1 * cos(angle), center.y + r1 * sin(angle) + (r1 * rate)),
		color1, 1, CV_AA);
	//上右2
	angle = (U + deg_udi) * M_PI / 180.0;
	line(image,
		cv::Point(center.x + r1 * cos(angle), center.y + r1 * sin(angle) - (r5 - r1)),
		cv::Point(center.x + r1 * cos(angle), center.y + r1 * sin(angle) - (r5 - r1) - rate2 * (r5 - r1)),
		color1, 1, CV_AA);

	// 中央×
	line(image,
		center + cv::Point(r1 * rate, r1 * rate) / 2,
		center + cv::Point(r1 * rate, r1 * rate),
		color3, 1, CV_AA);
	line(image,
		center + cv::Point(r1 * rate, -r1 * rate) / 2,
		center + cv::Point(r1 * rate, -r1 * rate),
		color3, 1, CV_AA);
	line(image,
		center + cv::Point(-r1 * rate, r1 * rate) / 2,
		center + cv::Point(-r1 * rate, r1 * rate),
		color3, 1, CV_AA);
	line(image,
		center + cv::Point(-r1 * rate, -r1 * rate) / 2,
		center + cv::Point(-r1 * rate, -r1 * rate),
		color3, 1, CV_AA);

	line(image,
		center + cv::Point(r2 * cos(M_PI / 4), r2 * sin(M_PI / 4)),
		center + cv::Point((r2 - (r1 * rate)) * cos(M_PI / 4), (r2 - (r1 * rate)) * sin(M_PI / 4)),
		color3, 1, CV_AA);
	line(image,
		center + cv::Point(r2 * cos(M_PI * 3 / 4), r2 * sin(M_PI * 3 / 4)),
		center + cv::Point((r2 - (r1 * rate)) * cos(M_PI * 3 / 4), (r2 - (r1 * rate)) * sin(M_PI * 3 / 4)),
		color3, 1, CV_AA);
	line(image,
		center + cv::Point(r2 * cos(M_PI * 5 / 4), r2 * sin(M_PI * 5 / 4)),
		center + cv::Point((r2 - (r1 * rate)) * cos(M_PI * 5 / 4), (r2 - (r1 * rate)) * sin(M_PI * 5 / 4)),
		color3, 1, CV_AA);
	line(image,
		center + cv::Point(r2 * cos(M_PI * 7 / 4), r2 * sin(M_PI * 7 / 4)),
		center + cv::Point((r2 - (r1 * rate)) * cos(M_PI * 7 / 4), (r2 - (r1 * rate)) * sin(M_PI * 7 / 4)),
		color3, 1, CV_AA);

	line(image,
		center + cv::Point(r2 * cos(M_PI / 4), r2 * sin(M_PI / 4)),
		center + cv::Point((r2 - (r1 * rate / 2)) * cos(M_PI / 4), (r2 - (r1 * rate / 2)) * sin(M_PI / 4)),
		color3, 2, CV_AA);
	line(image,
		center + cv::Point(r2 * cos(M_PI * 3 / 4), r2 * sin(M_PI * 3 / 4)),
		center + cv::Point((r2 - (r1 * rate / 2)) * cos(M_PI * 3 / 4), (r2 - (r1 * rate / 2)) * sin(M_PI * 3 / 4)),
		color3, 2, CV_AA);
	line(image,
		center + cv::Point(r2 * cos(M_PI * 5 / 4), r2 * sin(M_PI * 5 / 4)),
		center + cv::Point((r2 - (r1 * rate / 2)) * cos(M_PI * 5 / 4), (r2 - (r1 * rate / 2)) * sin(M_PI * 5 / 4)),
		color3, 2, CV_AA);
	line(image,
		center + cv::Point(r2 * cos(M_PI * 7 / 4), r2 * sin(M_PI * 7 / 4)),
		center + cv::Point((r2 - (r1 * rate / 2)) * cos(M_PI * 7 / 4), (r2 - (r1 * rate / 2)) * sin(M_PI * 7 / 4)),
		color3, 2, CV_AA);

	char str1[16], str2[16];
	sprintf_s(str1, "%06.2f", std::min(std::max(0.0, gauge3 * 100.0), 100.0));
	if (gauge3 > 0.3){
		putText(img, str1, cv::Point(center.x + r6, center.y - r6 * 0.04), cv::FONT_HERSHEY_SIMPLEX, r1 * 0.004, color2, 1, CV_AA);
	}
	else {
		putText(img, str1, cv::Point(center.x + r6, center.y - r6 * 0.04), cv::FONT_HERSHEY_SIMPLEX, r1 * 0.004, color3, 1, CV_AA);
	}
	sprintf_s(str2, "%05.0f", std::min(std::max(0.0, gauge5 * gauge_max1), gauge_max1));
	if (gauge5 > 0.3){
		putText(img, str2, cv::Point(center.x - r1 * 1.45, center.y - r6 * 0.04), cv::FONT_HERSHEY_SIMPLEX, r1 * 0.004, color2, 1, CV_AA);
	}
	else{
		putText(img, str2, cv::Point(center.x - r1 * 1.45, center.y - r6 * 0.04), cv::FONT_HERSHEY_SIMPLEX, r1 * 0.004, color3, 1, CV_AA);
	}
	img = img + image;
	return;
}

#endif