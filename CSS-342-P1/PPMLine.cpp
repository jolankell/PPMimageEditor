#include "PPMLine.h"

// default constructor
PPMLine::PPMLine() {
	maxColorValue = 255;
}

// destructor
PPMLine::~PPMLine() {

}

// custom constructor
PPMLine::PPMLine(vector<RGBValue> pixelsIn, int maxColor) {
	pixels = pixelsIn;
	maxColorValue = maxColor;
}

// returns width / x value of the line
int PPMLine::getWidth() const {
	return pixels.size();
}

// sets the width / x value
void PPMLine::setWidth(int width) {
	pixels.resize(width);
}

// sets max color value of the line
void PPMLine::setColorMax(int color) {
	maxColorValue = color;
}

// returns the max color value of the line
int PPMLine::getMaxColor() const {
	return maxColorValue;
}

// returns a editable pixel
RGBValue& PPMLine::operator[](int index) {
	if (index < 0 || index >= pixels.size()) {
		throw runtime_error("Index out of range");
	}
	else {
		return pixels[index];
	}
}

// returns a non editable pixel
const RGBValue& PPMLine::operator[](int index) const {
	if (index < 0 || index >= pixels.size()) {
		throw runtime_error("Index out of range");
	}
	else {
		return pixels[index];
	}
}