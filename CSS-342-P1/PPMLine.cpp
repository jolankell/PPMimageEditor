#include "PPMLine.h"

PPMLine::PPMLine() {
	maxColorValue = 255;
}
PPMLine::~PPMLine() {

}
PPMLine::PPMLine(vector<RGBValue> pixelsIn, int maxColor) {
	pixels = pixelsIn;
	maxColorValue = maxColor;
}
int PPMLine::getWidth() const {
	return pixels.size();
}
void PPMLine::setWidth(int width) {
	pixels.resize(width);
}
int PPMLine::getMaxColor() const {
	return maxColorValue;
}
void PPMLine::setColorMax(int color) {
	maxColorValue = color;
}
RGBValue& PPMLine::operator[](int index) {
	if (index < 0 || index >= pixels.size()) {
		throw exception("Index out of range");
	}
	else {
		return pixels[index];
	}
}
const RGBValue& PPMLine::operator[](int index) const {
	if (index < 0 || index >= pixels.size()) {
		throw exception("Index out of range");
	}
	else {
		return pixels[index];
	}
}