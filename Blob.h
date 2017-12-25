#pragma once

class Blob {
	int x;
	int y;
	int width;
	int height;
	Mat area;
	public:
	Blob();
	Blob(int x, int y, int width, int height);
	~Blob();
	bool isIn(int x, int y);
	void add(int x, int y);
	void drawBlob(Mat output);
	void drawBlob(Mat output, int i);
	void drawBlob(Mat output, int i, CvScalar color);
	bool greaterThan(int minW, int minH);
	bool greaterThan(int area);
	Mat getArea(Mat totalArea);
};

Blob clacBlob(Mat grayScaleMat, int r, int c);

