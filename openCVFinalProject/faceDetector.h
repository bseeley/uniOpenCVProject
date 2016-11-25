#pragma once

#include <opencv2\imgproc.hpp>
#include <opencv2\objdetect.hpp>
#include <iostream>
#include <fstream>
#include <vector>


using namespace std;
using namespace cv;

//A general class for all the harr cascade detectors
class faceDetector
{
public:
	faceDetector();
	faceDetector(string cascade, Scalar col);
	vector<Rect> detect(Mat curFrame);
	Mat highlightItems(Mat curFrame, Rect offset, int highlightType);
	void outputDistances();
	int numItemsDetected();
private:
	Scalar itemHighlightCol;
	CascadeClassifier detector;			//actual classifier
	vector<Rect> detectedItems;
};
