#pragma once

#include "faceDetector.h"

faceDetector::faceDetector(){};

faceDetector::faceDetector(string cascade, Scalar col)
{
	itemHighlightCol = col;
	detector.load(cascade);
}

vector<Rect> faceDetector::detect(Mat tarFrame){	//operates on a bw Mat
	detector.detectMultiScale(tarFrame, detectedItems, 1.1, 10, CV_HAAR_SCALE_IMAGE | CV_HAAR_DO_CANNY_PRUNING);
	//cout << "detect rrun" << endl;
	return detectedItems;
}


Mat faceDetector::highlightItems(Mat curFrame, Rect offset, int highlightType){
	Point pointTopLeft;
	Point pointBottomRight;
	Point center;
	for (int i = 0; i < detectedItems.size(); i++)
	{
		switch (highlightType)
		{
		case 0:
			pointTopLeft = Point(detectedItems[i].x, detectedItems[i].y);
			pointBottomRight = Point(detectedItems[i].x + detectedItems[i].width, detectedItems[i].y + detectedItems[i].height);
			rectangle(curFrame, pointTopLeft, pointBottomRight, itemHighlightCol, 2, 8, 0);
			break;
		case 1:
			center = Point(detectedItems[i].x + detectedItems[i].width*0.5 + offset.x, detectedItems[i].y + detectedItems[i].height*0.5 + offset.y);
			circle(curFrame, center, detectedItems[i].width / 2, itemHighlightCol, 2, 8, 0);
			break;
		default:
			cout << "highlight type not available" << endl;
		}
	}
	return curFrame;
}

void faceDetector::outputDistances(){
	float distValue;
	for (int i = 0; i < detectedItems.size(); i++){
		for (int j = i; j < detectedItems.size(); j++){
			if (i != j){
				distValue = sqrt(pow((detectedItems[i].x - detectedItems[j].x), 2) + pow((detectedItems[i].y - detectedItems[j].y), 2));
				cout << "Item Number: " << i << " Target Face: " << j << " Distance: " << distValue << endl;
			}
		}
	}
}

int faceDetector::numItemsDetected(){
	return detectedItems.size();
}

//remeber 157  