#pragma once

#ifndef PROCESSING_H
#define PROCESSING_H
#include <list>
#include "Blob.h"
#include "Main.h"

void edgeDetection(Mat original, Mat output, int minVal);
void edgeDetectionFast(Mat original, Mat output);
void minMax(Mat grayScaleMat, int minVal);
std::list<Blob> detectBlobs(std::list<Blob> l, Mat grayScaleMat);
void khtTransform(Mat image, Mat outputImage);
std::list<Rect> getBlobs(Mat input, std::list<Rect> list, Mat outputImage);

#endif
