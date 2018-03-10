#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/opencv.hpp>
#include <opencv/cv.hpp>

#include <stdio.h>
#include <iostream>
#include <math.h>

using namespace cv;
using namespace std;

int thresh = 100;

Mat frame;
Mat fgMaskMOG;
Mat canny_output;

void videoDetect(VideoCapture cap);
void testVideo();

//Create Background Subtractor Objects
//Ptr<BackgroundSubtractor> pMOG;
//Alternatively...
Ptr<BackgroundSubtractor> pMOG = createBackgroundSubtractorMOG2();

//Create the cap object
VideoCapture cap("belt2_fg.wmv");

int main(int, char**) {
	//Check if video loaded successfully
	if (!cap.isOpened()) {
		return -1;
	}
	videoDetect(cap);
	//testVideo();
	return 0;
}

void videoDetect(VideoCapture cap) {
	while (1) {
		//Read each video frame.
		cap >> frame;

		//Every frame, calculate the foreground mask and update the background model
		pMOG->apply(frame, fgMaskMOG);

		//GaussianBlur to reduce the noise
		GaussianBlur(fgMaskMOG, fgMaskMOG, Size(3, 3), 0, 0, BORDER_DEFAULT);
		canny_output = fgMaskMOG.clone();

		//Perform Canny Edge Detector
		Canny(fgMaskMOG, canny_output, thresh, thresh * 2, 3);

		//Find Contours
		vector<vector<Point>> contour;
		findContours(canny_output, contour, CV_RETR_EXTERNAL,
				CHAIN_APPROX_NONE);
		//Determine largest contourArea
		double largestArea = 0;
		int largestArea_index = 0;
		for (int i = 0; i < contour.size(); i++) {
			double area = contourArea(contour[i]);
			if (area > largestArea) {
				largestArea = area;
				largestArea_index = i;
			}
		}
		//Determine largest contourArcLength
		double arc = arcLength(contour[largestArea_index], true);
		cout << "Area = " << largestArea << endl;
		cout << "Arc = " << arc << endl;
		if ((largestArea > 5000 && largestArea < 6550)
				&& (arc > 240 && arc < 310)) {
			putText(frame, "Washer", Point(50, 50), FONT_HERSHEY_SIMPLEX, 2,
					Scalar(0, 255, 0), 2);
		} else if ((largestArea > 7000 && largestArea < 9000)
				&& (arc > 420 && arc < 520)) {
			putText(frame, "Queen's", Point(50, 50), FONT_HERSHEY_SIMPLEX, 2,
					Scalar(0, 255, 0), 2);
		} else if ((largestArea > 3800 && largestArea < 4900)
				&& (arc > 180 && arc < 280)) {
			putText(frame, "Peg", Point(50, 50), FONT_HERSHEY_SIMPLEX, 2,
					Scalar(0, 255, 0), 2);
		} else if ((largestArea > 9000 && largestArea < 10500)
				&& (arc > 280 && arc < 420)) {
			putText(frame, "Nut", Point(50, 50), FONT_HERSHEY_SIMPLEX, 2,
					Scalar(0, 255, 0), 2);
		} else if ((largestArea > 4800 && largestArea < 6000)
				&& (arc > 360 && arc < 800)) {
			putText(frame, "Pipe", Point(50, 50), FONT_HERSHEY_SIMPLEX, 2,
					Scalar(0, 255, 0), 2);
		} else if ((largestArea > 9000 && largestArea < 10000)
				&& (arc > 520 && arc < 1000)) {
			putText(frame, "Prong", Point(50, 50), FONT_HERSHEY_SIMPLEX, 2,
					Scalar(0, 255, 0), 2);
		}
		drawContours(frame, contour, largestArea_index, Scalar(0, 0, 254), 1, 8,
				noArray(), INT_MAX, Point(0, 0));

		namedWindow("fgMaskMOG", CV_WINDOW_AUTOSIZE);
		imshow("fgMaskMOG", fgMaskMOG);

		namedWindow("frame", CV_WINDOW_AUTOSIZE);
		imshow("frame", frame);
		//Close if keypress
		if (waitKey(30) >= 0) {
			break;
		}
		//Close at end of video
		bool success = cap.read(frame);
		if (!success) {
			break;
		}
	}
}

void testVideo() {
	while (1) {
		//Read each video frame.
		cap >> frame;

		//Every frame, calculate the foreground mask and update the background model
		pMOG->apply(frame, fgMaskMOG);

		//GaussianBlur to reduce the noise
		GaussianBlur(fgMaskMOG, fgMaskMOG, Size(3, 3), 0, 0, BORDER_DEFAULT);
		canny_output = fgMaskMOG.clone();

		//Perform Canny Edge Detector
		Canny(fgMaskMOG, canny_output, thresh, thresh * 2, 3);

		//Find Contours
		vector<vector<Point>> contour;
		findContours(canny_output, contour, CV_RETR_EXTERNAL,
				CHAIN_APPROX_NONE);
		//Determine largest contourArea
		double largestArea = 0;
		int largestArea_index = 0;
		for (int i = 0; i < contour.size(); i++) {
			double area = contourArea(contour[i]);
			if (area > largestArea) {
				largestArea = area;
				largestArea_index = i;
			}
		}
		//Determine largest contourArcLength
		double arc = arcLength(contour[largestArea_index], true);
		String Area = "Area = " + to_string(largestArea);
		String Arc = "Arc = " + to_string(arc);

		putText(frame, Area, Point(50, 50), FONT_HERSHEY_SIMPLEX, 2,
				Scalar(0, 255, 0), 2);
		putText(frame, Arc, Point(50, 100), FONT_HERSHEY_SIMPLEX, 2,
				Scalar(0, 255, 0), 2);
		//wait for 500ms
		waitKey(500);

		namedWindow("frame", CV_WINDOW_AUTOSIZE);
		imshow("frame", frame);
		//Close if keypress
		if (waitKey(30) >= 0) {
			break;
		}
		//Close at end of video
		bool success = cap.read(frame);
		if (!success) {
			break;

		}
	}
}
