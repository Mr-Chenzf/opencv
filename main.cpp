//#include<opencv2/opencv.hpp>  
//#include<iostream>
//#include<math.h>
//
//using namespace cv;
//using namespace std; 
//
//int main(int argc, char* argv)
//{
//	VideoCapture capture(0); 
//	Mat frame;
//	while (capture.read(frame))
//	{
//		cvtColor(frame, frame, COLOR_BGR2GRAY);
//		blur(frame, frame, Size(3, 3));
//		Canny(frame, frame, 3, 9, 3);
//		HoughCircles(frame, frame,HOUGH_GRADIENT,1,10);
//		imshow("camera demo", frame); 
//		char c = waitKey(50);
//		if (c == 27)
//		{
//			break;
//		}  
//	}
//	waitKey(0);
//	return 0;
//}
//int detectColor(Mat image)
//{
//    Mat mask;
//    cvtColor(image, image, COLOR_BGR2HSV);
//    const Scalar hsvRedLo(10, 193, 198);
//    const Scalar hsvRedHi(28, 220, 206);
//
//    const Scalar hsvGreenLo(72, 242, 186);
//    const Scalar hsvGreenHi(90, 255, 255);
//
//    const Scalar hsvYellowLo(24, 219, 196);
//    const Scalar hsvYellowHi(32, 255, 217);
//
//    vector<Scalar> hsvLo{ hsvRedLo,hsvGreenLo,hsvYellowLo };
//    vector<Scalar> hsvHi{ hsvRedHi,hsvGreenHi,hsvYellowHi };
//
//    inRange(image, hsvLo[1], hsvHi[1], mask);
//    inRange(image, hsvLo[2], hsvHi[2], mask);
//    inRange(image, hsvLo[0], hsvHi[0], mask);
//
//    Mat redBlur, greenBlur, yellowBlur;
//    medianBlur(mask, redBlur, 5);
//    medianBlur(mask, greenBlur, 5);
//    medianBlur(mask, yellowBlur, 5);
//    int red, green, yellow, lightColor;
//    red = countNonZero(redBlur);
//    green = countNonZero(greenBlur);
//    yellow = countNonZero(yellowBlur);
//    lightColor = (red > green) ? (red > yellow ? red : yellow) : (green > yellow ? 
//        green : yellow);
//    if (lightColor == red)
//        return 1;
//    else if (lightColor == green)
//        return 2;
//    else if (lightColor == yellow)
//        return 3;
//    else return 0;
//}
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <string.h>
using namespace std;
using namespace cv;
double redcontours, greencontours, yellowcontours;
void red(Mat srcImage)
{
	Mat midImage;
	cvtColor(srcImage, midImage, COLOR_BGR2HSV);
	inRange(midImage, Scalar(2, 43, 46), Scalar(7, 255, 255), midImage);
	GaussianBlur(midImage, midImage, Size(5, 5), 0, 0);
	vector<vector<Point>>contours;
	vector<Vec4i>hierarchy;
	findContours(midImage, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
	double largest_area = 0;
	double largest_contour_index = 0;
	Rect bounding_rect;
	for (size_t i = 0; i < contours.size(); i++)
	{
		double area = contourArea(contours[i]);
		if (area > largest_area)
		{
			largest_area = area;
			largest_contour_index = i;
			bounding_rect = boundingRect(contours[i]);
			redcontours = area;
		}
	}
};
void yellow(Mat srcImage)
{
	Mat midImage;
	cvtColor(srcImage, midImage, COLOR_BGR2HSV);
	inRange(midImage, Scalar(20, 43, 46), Scalar(23, 255, 255), midImage);
	GaussianBlur(midImage, midImage, Size(5, 5), 0, 0);
	vector<vector<Point>>contours;
	vector<Vec4i>hierarchy;
	findContours(midImage, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
	double largest_area = 0;
	double largest_contour_index = 0;
	Rect bounding_rect;
	for (size_t i = 0; i < contours.size(); i++)
	{
		double area = contourArea(contours[i]);
		if (area > largest_area)
		{
			largest_area = area;
			largest_contour_index = i;
			bounding_rect = boundingRect(contours[i]);
			yellowcontours = area;
		}
	}
};
void green(Mat srcImage)
{
	Mat midImage;
	cvtColor(srcImage, midImage, COLOR_BGR2HSV);
	inRange(midImage, Scalar(26, 73, 100), Scalar(64, 255, 255), midImage);
	GaussianBlur(midImage, midImage, Size(5, 5), 0, 0);
	vector<vector<Point>>contours;
	vector<Vec4i>hierarchy;
	findContours(midImage, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
	double largest_area = 0;
	double largest_contour_index = 0;
	Rect bounding_rect;
	for (size_t i = 0; i < contours.size(); i++)
	{
		double area = contourArea(contours[i]);
		if (area > largest_area)
		{
			largest_area = area;
			largest_contour_index = i;
			bounding_rect = boundingRect(contours[i]);
			greencontours = area;
		}
	}
};
// int thresholds = 0;
// int thresholds1 = 0;
// int thresholds2 = 0;
// int thresholds3 = 180;
// int thresholds4 = 255;
// int thresholds5 = 255;
// Mat image1;
// void distinguish(int, void*)
// {
// 	Mat image;
// 	//inRange(image1, Scalar(0, 3, 138),
// 	//Scalar(57, 110, 255), image);
// 	inRange(image1, Scalar(thresholds, thresholds1, thresholds2),
// 		Scalar(thresholds3, thresholds4, thresholds5), image);
// 	imshow("视频", image);
// };
int main(int argc,char** argv) 
{
	VideoCapture capture(1);
	//double fps = capture.get(CV_CAP_PROP_FPS);
	//unsigned int ImageCount = 0;
	//Mat edges;
	bool stop = false;
	int sign;
	//Mat imageROI;
	//Mat	blackimage;
	while (!stop)
	{
		int64 time0 = getTickCount();
		Mat srcImage, midImage, blackimage, imageROI;
		namedWindow("视频", WINDOW_NORMAL);
		namedWindow("视频1", WINDOW_NORMAL);
		namedWindow("视频2", WINDOW_NORMAL);
		//namedWindow("视频3", WINDOW_NORMAL);
		capture >> srcImage;
		image1 = srcImage;
			/*resize(srcImage, srcImage, Size(640, 480));
		inRange(midImage, Scalar(0, 43, 46),
				Scalar(10, 255, 255), midImage);
		inRange(midImage, Scalar(0, 180, 0),
			Scalar(43, 46, 220), midImage);*/
		cvtColor(srcImage, midImage, COLOR_BGR2HSV);
		inRange(midImage, Scalar(0, 255, 14),
			Scalar(64, 255, 70), midImage);
// 		inRange(midImage, Scalar(thresholds, thresholds1, thresholds2),
// 				Scalar(thresholds3, thresholds4, thresholds5), midImage);
// 		createTrackbar("Hmin：", "视频", &thresholds, 255, distinguish);
// 		createTrackbar("Smin：", "视频", &thresholds1, 255, distinguish);
// 		createTrackbar("Vmin：", "视频", &thresholds2, 255, distinguish);
// 		createTrackbar("Hmax：", "视频", &thresholds3, 255, distinguish);
// 		createTrackbar("Smax：", "视频", &thresholds4, 255, distinguish);
// 		createTrackbar("Vmax：", "视频", &thresholds5, 255, distinguish); 
// 		distinguish(0,0);
		GaussianBlur(midImage, midImage, Size(5, 5), 60, 60);
		vector<vector<Point>>contours;
		vector<Vec4i>hierarchy;
		//threshold(midImage, midImage, 75, 155, THRESH_BINARY);
		findContours(midImage, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
		//Mat element = getStructuringElement(MORPH_RECT, Size(7, 7));
		//dilate(midImage, midImage, element);
		//erode(midImage, midImage, element);
		double largest_area = 0;
		double largest_contour_index = 0;
		Rect bounding_rect, boundrect;
		for (size_t i = 0; i < contours.size(); i++)
		{
			double area = contourArea(contours[i]);
			if (area > largest_area)
			{
				largest_area = area;
				largest_contour_index = i;
				bounding_rect = boundingRect(contours[i]);
			}
		}
		Point point1, point2;
		point1.x = bounding_rect.tl().x;
		point1.y = bounding_rect.tl().y;
		point2.x = bounding_rect.br().x;
		point2.y = bounding_rect.br().y;
		imageROI = srcImage(Rect(point1.x, point1.y, point2.x-point1.x, point2.y-point1.y));

		//image1 = imageROI;
		//cvtColor(imageROI, blackimage, COLOR_BGR2HSV);
		//inRange(blackimage, Scalar(thresholds, thresholds1, thresholds2),
		//	Scalar(thresholds3, thresholds4, thresholds5), blackimage);
		//GaussianBlur(blackimage, blackimage, Size(5, 5), 30, 30);
		//vector<vector<Point>>contours1;
		//vector<Vec4i>hierarchy1;
		////threshold(midImage, midImage, 75, 155, THRESH_BINARY);
		//findContours(blackimage, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
		//createTrackbar("Hmin：", "视频3", &thresholds, 255, distinguish);
		//createTrackbar("Smin：", "视频3", &thresholds1, 255, distinguish);
		//createTrackbar("Vmin：", "视频3", &thresholds2, 255, distinguish);
		//createTrackbar("Hmax：", "视频3", &thresholds3, 255, distinguish);
		//createTrackbar("Smax：", "视频3", &thresholds4, 255, distinguish);
		//createTrackbar("Vmax：", "视频3", &thresholds5, 255, distinguish); 
		//distinguish(0,0);
		//double largest_area1 = 0;
		//double largest_contour_index1 = 0;
		//Rect bounding_rect1, boundrect1;
		//for (size_t i = 0; i < contours.size(); i++)
		//{
		//	double area1 = contourArea(contours[i]);
		//	if (area1 > largest_area1)
		//	{
		//		largest_area1 = area1;
		//		largest_contour_index1 = i;
		//		bounding_rect1 = boundingRect(contours[i]);
		//	}
		//}
		//Point point3, point4;
		//point3.x = bounding_rect1.tl().x;
		//point3.y = bounding_rect1.tl().y;
		//point4.x = bounding_rect1.br().x;
		//point4.y = bounding_rect1.br().y;
		//blackimage = imageROI(Rect(point3.x, point3.y, point4.x - point3.x, point4.y - point3.y));
		rectangle(srcImage, bounding_rect.tl(), bounding_rect.br(), Scalar(255, 0, 0),
			2, 8, 0);
		imshow("视频1", imageROI);
		//Canny(edges, edges, 0, 30, 3);
		red(imageROI);
		green(imageROI);
		yellow(imageROI);
		if (redcontours > yellowcontours&& redcontours > greencontours)
			sign= 1;
		else
		{
			if (redcontours == yellowcontours && redcontours > greencontours)
				sign = 2;
			else {
				if (greencontours > redcontours && greencontours > yellowcontours)
					sign = 3;
				else
					if(greencontours > redcontours && greencontours == yellowcontours)
					sign = 4;
			}
		}
		cout << sign << endl;
		imshow("视频", midImage);
		imshow("视频2", srcImage);
		//imshow("视频3", blackimage);
		cout << "当前帧率为:" << getTickFrequency() / (getTickCount() - time0) << endl;
		if (waitKey(30) >= 0)
			stop = true;
	}
	return 0;
}
