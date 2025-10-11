#pragma once

#include "PPMLine.h"
#include <string>
#include <iostream>
#include <ostream>
#include <istream>

class PPMImage
{
private:
	vector<PPMLine> lines;
	int width; int height;
	int maxColor;
public:
	PPMImage();
	~PPMImage();
	PPMImage(int width1, int height1, int maxColor1);
	PPMImage(string filename);
	void loadFile(string filename);
	void drawLine(const int& x1, const int& y1, const int& x2, const int& y2, const RGBValue& color);
	PPMImage& operator = (const PPMImage& rightValue);
	PPMImage operator + (const PPMImage& rightValue);
	PPMImage operator + (const PPMLine& rightValue);
	PPMImage operator - (const PPMImage& rightValue);
	PPMImage& operator += (const PPMLine& rightValue);
	PPMImage& operator - ();
	bool operator == (const PPMImage& rightValue) const;
	bool operator != (const PPMImage& rightValue) const;
	friend ostream& operator << (ostream& out, const PPMImage& image);
	friend istream& operator >> (istream& in, PPMImage& image);
};

