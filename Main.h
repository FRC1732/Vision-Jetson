#pragma once
#include "opencv2\opencv.hpp"
#include <stdio.h>
#include <cmath>

typedef unsigned char byte;

using namespace cv;

// the minimun distance allowed between points on the picture
const int minDist = 20;
const int minDistSq = minDist * minDist;

//the toleance for removeing points on the same line, as a slope
const double slopeTolerance = 0.1;

//contours type - an enum value for the cv::findContours function
const int type = CV_RETR_EXTERNAL;

//contour aproxximation method - a cv enum
const int method = CV_CHAIN_APPROX_SIMPLE;