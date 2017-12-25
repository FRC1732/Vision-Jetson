#include "opencv2\opencv.hpp"
#include <stdio.h>

typedef unsigned char byte;
const int B = 0;
const int G = 1;
const int R = 2;
const int A = 3;

using namespace cv;

int readFromCamera(int argv, char** argc) {
	Mat frame;

	VideoCapture vid(1);

	if (!vid.isOpened()) {
		return -1;
	}

	while (vid.read(frame)) {
		//manipulate frame
		//maybe add lines?

		imshow("webCam", frame);

		if (waitKey(100) >= 0) {
			return 1;
		}
	}
}

