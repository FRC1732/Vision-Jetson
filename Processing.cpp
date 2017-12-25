#include "Main.h"
#include "Blob.h"
#include "Processing.h"
#include <list>
#include <iostream>

#include <algorithm>
#include <ctime>

void edgeDetection(Mat original, Mat output, int minVal) {
	for (int r = 1; r < output.rows - 1; r++) {
		for (int c = 1; c < output.cols - 1; c++) {
			byte left = original.at<byte>(r - 1, c);
			byte leftUp = original.at<byte>(r - 1, c - 1);
			byte leftDown = original.at<byte>(r - 1, c + 1);

			byte right = original.at<byte>(r + 1, c);
			byte rightUp = original.at<byte>(r + 1, c - 1);
			byte rightDown = original.at<byte>(r + 1, c + 1);

			byte up = original.at<byte>(r, c - 1);
			byte down = original.at<byte>(r, c + 1);

			int left_right = -leftUp - 2 * left - leftDown + rightUp + 2 * right + rightDown;
			int up_down = -leftUp - 2 * up - leftDown + rightUp + 2 * down + rightDown;

			if (abs(left_right) > minVal || abs(up_down) > minVal - 50) {
				output.at<byte>(r, c) = 0xFF;
			} else {
				output.at<byte>(r, c) = 0x00;
			}

		}
	}
}

void edgeDetectionFast(Mat original, Mat output) {
	for (int r = 0; r < output.rows - 1; r++) {
		for (int c = 0; c < output.cols - 1; c++) {

			byte here = original.at<byte>(r, c);

			byte right = original.at<byte>(r + 1, c);
			byte down = original.at<byte>(r, c + 1);

			if (right != here || down != here) {
				output.at<byte>(r, c) = 0xFF;
			} else {
				output.at<byte>(r, c) = 0x00;
			}

		}
	}
}

void minMax(Mat grayScaleMat, int minVal) {
	for (int r = 0; r < grayScaleMat.rows; r++) {
		for (int c = 0; c < grayScaleMat.cols; c++) {
			//if it is greater, max it
			grayScaleMat.at<byte>(r, c) = (grayScaleMat.at<byte>(r, c) > minVal) ? 0xFF : 0x00;
		}
	}
}

//detect blobs in image
std::list<Blob> detectBlobs(std::list<Blob> l, Mat grayScaleMat) {
	Blob b(0, 0, 0, 0);
	bool done = false;
	l.clear();
	Mat clone;

	int count = 0;
	//for every row/column
	for (int r = 0; r < grayScaleMat.rows - 1; r++) {
		for (int c = 0; c < grayScaleMat.cols - 1; c++) {
			//if should be added to blobs
			if (grayScaleMat.at<byte>(r, c) == 0xFF) {
				/*for (list<Blob>::iterator it = l.begin(); it != l.end() && !done; ++it) {
					b = *it;
					if (!b.isIn(r, c)) {
						done = true;
					}
				}*/
				if (!done) {
					l.push_front(clacBlob(grayScaleMat, r, c));
				}
				done = false;
			}
		}
	}
	std::cout << "Blobs: " << l.size() << std::endl;

	return l;
}

bool shouldRevomeMiddle(Point p1, Point p2, Point p3) {
	return abs((p1.x - p2.x) / (double)(p1.y - p2.y) - (p1.x - p3.x) / (double)(p1.y - p3.y)) < slopeTolerance;
}

bool shouldCombine(Point p1, Point p2) {
	return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y) < minDistSq;
}

int shouldCombineUsing(Point p1, Point p2, int centerx, int centery) {
	if ((centerx - p2.x)*(centerx - p2.x) +
		(centery - p2.y)*(centery - p2.y) <
		(centerx - p1.x)*(centerx - p1.x) +
		(centery - p1.y)*(centery - p1.y)) {
		return 1;
	} else {
		return 0;
	}
}

std::vector< std::vector<Point> > contours; // Vector for storing contour
std::vector<Vec4i> hierarchy;
std::vector<Point> current;
//std::list<Point> simplifiedShape;
std::list<Rect> getBlobs(Mat input, std::list<Rect> list, Mat outputImage) {
	list.clear();

	// Find the contours in the image
	findContours(input, contours, hierarchy, type, method);

	for (std::vector<std::vector<Point>>::iterator it = contours.begin(); it != contours.end(); ++it) {
		//std::cout << (*it).size() << " Hey " << std::endl;

		current = (*it);

		int i = 0;
		int accX = 0;
		int accY = 0;
		while (i < current.size()) {
			if (shouldRevomeMiddle(current[i], current[(i + 1) % current.size()], current[(i + 2) % current.size()])) {
				current.erase(current.begin() + ((i + 1) % current.size()));
				//std::cout << i << std::endl;
				//i++;
			} else {
				accX += current[(i + 1) % current.size()].x;
				accY += current[(i + 1) % current.size()].y;
				i++;
			}
		}
		accX /= current.size();
		accY /= current.size();
		
		i = 0;
		while (i < current.size()) {
			if (shouldCombine(current[i], current[(i + 1) % current.size()])) {
				//(*it)[i].x = ((*it)[(i + 1) % (*it).size()].x + (*it)[i].x) / 2;
				//(*it)[i].y = ((*it)[(i + 1) % (*it).size()].y + (*it)[i].y) / 2;
				//if ((accX - current[(i + 1) % current.size()].x)*(accX - current[(i + 1) % current.size()].x) +
				//	(accY - current[(i + 1) % current.size()].y)*(accY - current[(i + 1) % current.size()].y) <
				//	(accX - current[i].x)*(accX - current[i].x) +
				//	(accY - current[i].y)*(accY - current[i].y)) {
				//	current.erase(current.begin() + ((i + 1) % current.size()));
				//} else {
				//	current.erase(current.begin() + i);
				//}
				current.erase(current.begin() + ((i + shouldCombineUsing(current[i],current[(i + 1) % current.size()],accX,accY)) % current.size()));
				//std::cout << i << std::endl;
				//i++;
			} else {
				i++;
			}
		}
		//for (std::vector<Point>::iterator jt = current.begin(); jt != current.end(); ++jt) {
		//	cv::circle(outputImage, CvPoint((*jt).x, (*jt).y), 4, CvScalar(0, 0xFF));
		//}

		//Rect bounding_rect = boundingRect(*it);
		//list.push_front(bounding_rect);
	}

	return list;
}