#pragma once

#include "hatOverlay.h"

hatOverlay::hatOverlay(){

};

Mat hatOverlay::overlayTop(Mat &mainImage, Mat &overImage, Rect face){
	Mat overImageSized;
	resize(overImage, overImageSized, face.size(), 0, 0, INTER_AREA);

	//cout << "overlay Attempt" << endl;

	int startY = face.tl().y - overImageSized.rows;
	int startX = face.tl().x;
	int overlayYOffset = 0;

	//cout << "tl: " << face.tl() << " startY: " << startY << " startX: " << startX << " overImageSized dims: " << overImageSized.rows << endl;

	int yIterateLimit = startY;

	if (startY < 0){
		cout << "-ve overlay correction" << startY << endl;
		overlayYOffset = (startY *-1 )+1;
		startY = 1;
	}

	
	cout << "startY" << startY << endl; 
	cout << "overlay"<< overlayYOffset << endl;
	cout << "Image rows" << overImageSized.rows << endl; 
	
	

	for (int y = startY; y < (overImageSized.rows + yIterateLimit); y++){
		int overlayX = 0;
		for (int x = startX; x < (overImageSized.cols + startX); x++){
			mainImage.at<Vec3b>(Point(x, y)) = overImageSized.at<Vec3b>(Point(overlayX, overlayYOffset));
			//cout << "X" << x << "Y" << y << "OverlayX" << overlayX << "overlayYoffset" << overlayYOffset << endl;
			overlayX++;
		}
		overlayYOffset++;
		//cout << "Row " << overlayYOffset << endl;
	}


	//Old code - didn't work
	////for lines in main image
	//for (int y = max(face.tl().y, 0); y < overImageSized.rows; y++){
	//	int overY = y - face.tl().y;
	//	//if reached end of overlay break
	//	if (overY >= overImageSized.rows){
	//		break;
	//	}
	//
	//	for (int x = max(face.tl().x, 0); x < overImageSized.cols; x++){
	//		int overX = x - face.tl().x;
	//		//break if outside mainImage
	//		if (overX >= overImageSized.cols){
	//			break;
	//		}
	//
	//		//mainImage.at<uchar>(face.tl()) 
	//
	//	}
	//}

	return mainImage;
};
