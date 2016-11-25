#pragma once

#include <opencv2\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\objdetect.hpp>
#include "faceDetector.h"
#include "uiFramework.h"
#include "hatOverlay.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
using namespace cv;

const string haarFacePath = "C:\\opencv\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt2.xml";
const string haarEyePath = "C:\\opencv\\opencv\\sources\\data\\haarcascades\\haarcascade_eye.xml";
const string haarSmilePath = "C:\\opencv\\opencv\\sources\\data\\haarcascades\\haarcascade_smile.xml";


int main(int argc, char* argv[])
{
	cv::VideoCapture cap(0);	//creates capture
	if (!cap.isOpened())	//check camera open
	{
		return -1;
	}

	vector<Mat> hats { imread("BlackVikingHelmet.png"), imread("Cosmic_Star_Hat.png"), imread("crown.png"), imread("Mini_Sombrero.png"), imread("Party_Hat.png"), imread("Santa_Hat.png") };
	vector<bool> activeFeatures; //Stores 
	Mat curFrame;	//stores current frame
	Mat bwFrame; //b&w conversion store
	vector<Rect> detectedFaces;
	Mat partFrame; //for faces
	Rect nullPos(0, 0, 0, 0);
	Scalar faceCol = { 0, 255, 0 };
	Scalar eyeCol = { 255, 0, 0 };
	Scalar smileCol = { 0, 0, 255 };
	faceDetector face;
	face = faceDetector(haarFacePath, faceCol);
	faceDetector eye;
	eye = faceDetector(haarEyePath, eyeCol);
	faceDetector smile;
	smile = faceDetector(haarSmilePath, smileCol);

	hatOverlay hatter;
	uiFramework interfaceWindow;


	while (true)
	{
		cap.read(curFrame);
		cvtColor(curFrame, bwFrame, cv::COLOR_BGR2GRAY);

		detectedFaces = face.detect(bwFrame);
		curFrame = face.highlightItems(curFrame, nullPos, 0);
		for (int i = 0; i < detectedFaces.size(); i++){
			partFrame = bwFrame(detectedFaces[i]);
			if (interfaceWindow.sliderValues[0] == 1){
				eye.detect(partFrame);
				curFrame = eye.highlightItems(curFrame, detectedFaces[i], 1);
			}
			if (interfaceWindow.sliderValues[1] == 1){
				smile.detect(partFrame);
				curFrame = smile.highlightItems(curFrame, detectedFaces[i], 1);
			}
		}

		if (interfaceWindow.sliderValues[2] == 1){
			if (face.numItemsDetected() > 1){
				cout << "******FACE OUTPUT*********" << face.numItemsDetected() << endl;
				face.outputDistances();
			}

			if (eye.numItemsDetected() > 1){
				cout << "*******EYE OUTPUT*********" << eye.numItemsDetected() << endl;
				eye.outputDistances();
			}
		}

		if (interfaceWindow.sliderValues[3] != 0 && detectedFaces.size() > 0){
			Mat hatFrame;
			for (int i = 0; i < detectedFaces.size(); i++){
				hatFrame = hatter.overlayTop(curFrame, hats[interfaceWindow.sliderValues[3] - 1], detectedFaces[i]);
				//cout << i << endl;
			}
			interfaceWindow.uiDisplay(hatFrame);
		} 
		else 
		{
			interfaceWindow.uiDisplay(curFrame);
		}

		//Used to test hats loaded correctly
		/*for (int i = 0; i < hats.size(); i++){
			ostringstream convert;
			convert << i;
			imshow(convert.str(), hats[i]);
			cout << i << "hat channels" << hats[i].channels() << endl;
			}*/

		if (cv::waitKey(30) >= 0)
		{
			break;
		}
	}
	return 0;
}