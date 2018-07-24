#include <iostream>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

//2.1 Image Statistics - Determine Max, Min, Average Pixel Value
void imageStatistics(Mat inputImg) {
	//Initial Declarations
	int total = 0;
	int count = 0;
	int avgPixelValue;

	//Set initial min and max value to first pixel
	int min = (int) inputImg.at<uchar>(0, 0);
	int max = (int) inputImg.at<uchar>(0, 0);

	//Looping through pixels, determining min, max and avgPixelValue
	for (int r = 0; r < inputImg.rows; r++) {
		for (int c = 0; c < inputImg.cols; c++) {
			if ((int) inputImg.at<uchar>(r, c) < min) {
				min = (int) inputImg.at<uchar>(r, c);
			}
			if ((int) inputImg.at<uchar>(r, c) > max) {
				max = (int) inputImg.at<uchar>(r, c);
			}
			total += (int) inputImg.at<uchar>(r, c);
			count++;
		}
	}
	//Display Original Loaded Image
	namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
	imshow("Original Image", inputImg);

	//Print Final Results
	avgPixelValue = total / count;
	cout << "2.1 Image Statistics" << endl;
	cout << "Minimum Pixel Value: " << min << endl;
	cout << "Maximum Pixel Value: " << max << endl;
	cout << "Average Pixel Value: " << avgPixelValue << endl;
	cout << "Display Original Image" << "\n" << endl;
}

//2.2 Image Inversion - Convert Original Image into Negative Image
void imageInversion(Mat inputImg) {
	Mat negImg = inputImg.clone();
	int input;

	//Looping through pixels, inverting pixels
	for (int r = 0; r < inputImg.rows; r++) {
		for (int c = 0; c < inputImg.cols; c++) {
			input = inputImg.at<uchar>(r, c);
			negImg.at<uchar>(r, c) = 255 - input;
		}
	}
	//Print Statements
	cout << "2.2 Image Inversion" << endl;
	cout << "Display Original Image" << endl;
	cout << "Display Inversion Image" << "\n" << endl;

	//Display Original Loaded Image
	namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
	imshow("Original Image", inputImg);

	//Display Negative Image
	namedWindow("Negative Image", CV_WINDOW_AUTOSIZE);
	imshow("Negative Image", negImg);
}

//2.3 Image Flip - Vertical and Horizontal Flips on Original Image
void imageFlip(Mat inputImg) {
	//Create Copy Image for Vertical and Horizontal Flips
	Mat mirroryImg = inputImg.clone();
	Mat mirrorxImg = inputImg.clone();

	//Looping through pixels, fliping pixels
	for (int r = 0; r < inputImg.rows; r++) {
		for (int c = 0; c < inputImg.cols; c++) {
			mirrorxImg.at<uchar>(r, c) = inputImg.at<uchar>(r,
					inputImg.cols - 1 - c);
			mirroryImg.at<uchar>(r, c) = inputImg.at<uchar>(
					inputImg.rows - 1 - r, c);
		}
	}
	//Print Statements
	cout << "2.3 Image Flip" << endl;
	cout << "Display Vertical Flip Image" << endl;
	cout << "Display Horizontal Flip Image" << "\n" << endl;

	//Display Flipped Images
	namedWindow("Vertical Flip Image", CV_WINDOW_AUTOSIZE);
	imshow("Vertical Flip Image", mirrorxImg);
	namedWindow("Horizontal Flip Image", CV_WINDOW_AUTOSIZE);
	imshow("Horizontal Flip Image", mirroryImg);
	//Also, use flip(original_image,flip_image,1);
}

//2.4 Image Merge - Merged Two Inputed Images
void imageMerge(Mat inputImg1, Mat inputImg2) {
	Mat mergedImage;

	//Logical OR of the two images
	bitwise_or(inputImg1, inputImg2, mergedImage);

	//Print Statements
	cout << "2.4 Image Merge" << endl;
	cout << "Display Merged(OR) Image" << "\n" << endl;

	//Display Merged Image
	namedWindow("Merged(OR) Image", CV_WINDOW_AUTOSIZE);
	imshow("Merged(OR) Image", mergedImage);
}

//2.5 Image Difference - Determining subtle changes in a scene
void imageDifference(Mat inputImg1, Mat inputImg2) {
	Mat binaryImage = Mat::zeros(inputImg1.size(), inputImg1.type());
	double thresh = 25;
	int img1Input, img2Input;

	//Looping through pixels, computing difference between both images, filling with white pixels
	for (int i = 0; i < inputImg1.rows; i++) {
		for (int j = 0; j < inputImg1.cols; j++) {
			img1Input = (int) inputImg1.at<uchar>(i, j);
			img2Input = (int) inputImg2.at<uchar>(i, j);
			if (abs(img1Input - img2Input) > thresh) {
				binaryImage.at<uchar>(i, j) = 255;
			}
		}
	}
	//Print Statements
	cout << "2.5 Image Difference" << endl;
	cout << "Display Difference Image" << "\n" << endl;

	//Display Difference Image
	namedWindow("Difference Image", CV_WINDOW_NORMAL);
	imshow("Difference Image", binaryImage);
}

int main(int argc, char **argv) {
	//Load Image into Matrix Image
	Mat lena2Img = imread("lena2.jpg", CV_8UC1);
	Mat octo1Img = imread("octo1.jpg", CV_8UC1);
	Mat octo2Img = imread("octo2.jpg", CV_8UC1);
	Mat messyDesk1Img = imread("messy_desk_A-1.jpg", CV_8UC1);
	Mat messyDesk2Img = imread("messy_desk_B-1.jpg", CV_8UC1);

	//Perform Image Operations (Key press to continue)
	imageStatistics(lena2Img);
	waitKey();

	imageInversion(lena2Img);
	waitKey();

	imageFlip(lena2Img);
	waitKey();

	imageMerge(octo1Img, octo2Img);
	waitKey();

	imageDifference(messyDesk1Img, messyDesk2Img);
	waitKey();

	//End Code
	cout << "End Code." << endl;
	return 0;
}

