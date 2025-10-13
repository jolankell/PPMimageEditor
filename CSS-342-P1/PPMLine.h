#pragma once

#include "RGBValue.h";
#include <vector>
#include <stdexcept>

using namespace std;

class PPMLine
{
private:
	vector<RGBValue> pixels;
	int maxColorValue;
public:

	// default constructor
	PPMLine();
	
	// destructor
	~PPMLine();

	// custom constructor
	PPMLine(vector<RGBValue> pixelsIn, int maxColor);
	
	// returns width / x value of the line
	int getWidth() const;
	
	// sets the width / x value
	void setWidth(int width);
	
	// sets max color value of the line
	void setColorMax(int color);
	
	// returns the max color value of the line
	int getMaxColor() const;
	
	// returns a editable pixel
	RGBValue& operator[](int index);
	
	// returns a non editable pixel
	const RGBValue& operator[](int index) const;
};

