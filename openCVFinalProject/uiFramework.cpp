#pragma once

#include "uiFramework.h"

uiFramework::uiFramework(){
	binSliderMax = 1;
	hatSliderMax = 6;
	for (int i = 0; i <= sliderCount; i++){
		sliderValues[i] = 0;
	}
	initialiseWindow();
}

void uiFramework::initialiseWindow(){
	namedWindow("uiWindow", WINDOW_AUTOSIZE);
	createTrackbar("Eye Detect", "uiWindow", &sliderValues[0], binSliderMax);
	createTrackbar("Smile Detect", "uiWindow", &sliderValues[1], binSliderMax);
	createTrackbar("Text Output", "uiWindow", &sliderValues[2], binSliderMax);
	createTrackbar("Hats", "uiWindow", &sliderValues[3], hatSliderMax);
}


void uiFramework::uiDisplay(Mat &Stream){
	imshow("uiWindow", Stream);
}