#include "Main.h"
#include "Blob.h"
#include <list>
#include <iostream>

Blob::Blob() {}

Blob::Blob(int x, int y, int width, int height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

Blob::~Blob() {}

bool Blob::isIn(int x, int y) {
	return x >= this->x && y >= this->y && x < this->width + this->x && y < this->height + this->y;
}

void Blob::add(int xI, int yI) {
	if (xI < x) {
		width += x - xI;
		x = xI;
	} else if (xI >= x + width) {
		width = xI - x;
	}
	if (yI < y) {
		height += y - yI;
		y = yI;
	} else if (yI >= y + height) {
		height = yI - y;
	}
}

using namespace std;
const Scalar COLOR(0, 0, 255);

void Blob::drawBlob(Mat output) {
	rectangle(output, cvRect(y, x, height, width), COLOR, 1);
	
	//putText(output, to_string(this->width), Point(this->y, this->x), FONT_HERSHEY_PLAIN, 1.0, COLOR, 2.0);
	//putText(output, to_string(this->height), Point(this->y, this->x + 20), FONT_HERSHEY_PLAIN, 1.0, COLOR, 2.0);
}

void Blob::drawBlob(Mat output, int i) {
	rectangle(output, cvRect(y-2, x-2, height+5, width+5), COLOR, 1);

	putText(output, to_string(i), Point(this->y, this->x), FONT_HERSHEY_PLAIN, 1.0, COLOR, 2.0);
	//putText(output, to_string(this->height), Point(this->y, this->x + 20), FONT_HERSHEY_PLAIN, 1.0, COLOR, 2.0);
}

void Blob::drawBlob(Mat output, int i, CvScalar color) {
	rectangle(output, cvRect(y - 1, x - 1, height + 4, width + 4), color, 1);

	putText(output, to_string(i), Point(this->y, this->x), FONT_HERSHEY_PLAIN, 1.0, color, 2.0);
}

bool Blob::greaterThan(int minW, int minH) {
	return minW <= width && minH <= minH;
}

bool Blob::greaterThan(int area) {
	return area <= width * height;
}

Mat Blob::getArea(Mat totalArea) {
	return totalArea(Rect(this->y-1, this->x-1, this->height+4, this->width+4));
}

Blob clacBlob(Mat grayScaleMat, int r, int c) {
	Blob b(r, c, 1, 1);

	list<Point> points(1, Point(r, c));
	//x = r, y = c

	//while there are points to process
	while (points.size() > 0) {
		Point p = *points.begin();
		//if should be added
		if (p.x < grayScaleMat.rows && p.x >= 0 && p.y < grayScaleMat.cols && p.y >= 0) {//if in image
			if (grayScaleMat.at<byte>(p.x, p.y) == 0xFF) {//if filled
				//add it
				b.add(p.x, p.y);
				//shouldn't be added again
				grayScaleMat.at<byte>(p.x, p.y) = 0xFE;

				//add the 4 adjacent
				points.push_back(Point(p.x + 1, p.y));
				points.push_back(Point(p.x - 1, p.y));
				points.push_back(Point(p.x, p.y + 1));
				points.push_back(Point(p.x, p.y - 1));
			}
		}
		//remove no matter what
		points.pop_front();
	}

	return b;
}