#pragma once

#include <opencv2\imgproc.hpp>
#include <opencv2\objdetect.hpp>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
using namespace cv;

class hatOverlay
{
public:
	hatOverlay();
	Mat overlayTop(Mat &mainImage, Mat &overImage, Rect face);

};
