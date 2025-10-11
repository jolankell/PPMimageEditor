#pragma once

#include "RGBValue.h";
#include <vector>

using namespace std;

class PPMLine
{
private:
	vector<RGBValue> pixels;
	int maxColorValue;
public:
	PPMLine();
	~PPMLine();
	PPMLine(vector<RGBValue> pixelsIn, int maxColor);
	int getWidth() const;
	void setWidth(int width);
	void setColorMax(int color);
	int getMaxColor() const;
	RGBValue& operator[](int index);
	const RGBValue& operator[](int index) const;
};

