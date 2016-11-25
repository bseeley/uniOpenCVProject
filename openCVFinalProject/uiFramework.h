#pragma once

#include <opencv2\highgui.hpp>

using namespace std;
using namespace cv;

class uiFramework
{
public:
	uiFramework();
	void uiDisplay(Mat &Stream);
	int sliderValues[4];

private:
	void initialiseWindow();
	void activeFreatureEdit(int val);
	int binSliderMax;
	int hatSliderMax;
	const int sliderCount = 3;
};