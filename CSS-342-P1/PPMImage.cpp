#include "PPMImage.h"

PPMImage::PPMImage() {
	width = height = 0;
	maxColor = 255;
}
PPMImage::PPMImage(int width1, int height1, int maxColor1) {
    width = width1; height = height1; maxColor = maxColor1;
    lines.resize(height);
    for (int i = 0; i < lines.size(); i++) {
        lines[i].setWidth(width);
        lines[i].setColorMax(maxColor);
    }
}
PPMImage::~PPMImage() {

}
PPMImage::PPMImage(string filename) {
	
}
void PPMImage::loadFile(string filename) {

}
void PPMImage::drawLine(const int& x1, const int& y1, const int& x2, const int& y2, const RGBValue& color) {

    int x = x1;
    int y = y1;
    int differenceX = abs(x2 - x1);
    int differenceY = abs(y2 - y1);
    int moveX;
    int moveY;

    // move direction for x
    if (x1 < x2) {
        moveX = 1;
    }
    else {
        moveX = -1;
    }

    // move direction for y
    if (y1 < y2) {
        moveY = 1;
    }
    else {
        moveY = -1;
    }

    int lineBalance = differenceX - differenceY;

    // draw until we reach the endpoint
    while (true) {
        // plot current pixel
        if (y >= 0 && y < lines.size() && x >= 0 && x < lines[y].getWidth()) {
            lines[y][x] = color;
        }
        else {
            throw exception("invalid coridnates");
        }

        // if we reached the end point, stop
        if (x == x2 && y == y2) {
            break;
        }

        // error adjustment
        int lineBalance2 = 2 * lineBalance;

        if (lineBalance > -differenceY) {
            lineBalance -= differenceY;
            x += moveX;
        }

        if (lineBalance2 < differenceX) {
            lineBalance += differenceX;
            y += moveY;
        }
    }
}
PPMImage& PPMImage::operator = (const PPMImage& rightValue) {
    width = rightValue.width;
    height = rightValue.height;
    maxColor = rightValue.maxColor;
    lines.resize(height);

    for (int i = 0; i < rightValue.lines.size(); i++) {
        lines[i] = rightValue.lines[i];
    }

    return *this;
}
PPMImage PPMImage::operator+(const PPMImage& rightValue) {
    PPMImage result;
    RGBValue newColor;

    int smallerWidth = min(width, rightValue.width);
    int smallerHeight = min(height, rightValue.height);

    if (width >= rightValue.width) {
        result = *this;

        if (height < rightValue.height) {
            for (int i = height; i < rightValue.height; i++) {
                PPMLine newLine;
                newLine.setWidth(width);
                for (int j = 0; j < rightValue.lines[i].getWidth(); j++) {
                    newLine[j] = rightValue.lines[i][j];
                }
                result.lines.push_back(newLine);
                result.height++;
            }
        }
    }
    else {
        result = rightValue;

        if (height > rightValue.height) {
            for (int i = rightValue.height; i < height; i++) {
                PPMLine newLine;
                newLine.setWidth(rightValue.width);
                for (int j = 0; j < lines[i].getWidth(); j++) {
                    newLine[j] = lines[i][j];
                }
                result.lines.push_back(newLine);
                result.height++;
            }
        }
    }

    result.maxColor = max(maxColor, rightValue.maxColor);

    for (int i = 0; i < smallerHeight; i++) {
        for (int j = 0; j < smallerWidth; j++) {
            newColor.red = (lines[i][j].red + rightValue.lines[i][j].red) % (result.maxColor + 1);
            newColor.green = (lines[i][j].green + rightValue.lines[i][j].green) % (result.maxColor + 1);
            newColor.blue = (lines[i][j].blue + rightValue.lines[i][j].blue) % (result.maxColor + 1);
            result.lines[i][j] = newColor;
        }
    }
    return result;
}
PPMImage PPMImage::operator + (const PPMLine& rightValue) {
    if (width == 0 || width != rightValue.getWidth()) {
        throw exception("Image sizes don't line up");
    }
    else {
        PPMImage copy;
        copy = *this;
        copy.lines.push_back(rightValue);
        copy.height++;
        return copy;
    }
}
PPMImage PPMImage::operator - (const PPMImage& rightValue) {
    PPMImage test;
    return test;
}
PPMImage& PPMImage::operator += (const PPMLine& rightValue) {
    PPMImage test;
    return test;
}
PPMImage PPMImage::operator - () const {

    PPMImage invertedCopy = *this;

    for (int i = 0; i < invertedCopy.lines.size(); i++) {
        for (int j = 0; j < invertedCopy.lines[i].getWidth(); j++) {
            invertedCopy.lines[i][j].red = invertedCopy.maxColor - invertedCopy.lines[i][j].red;
            invertedCopy.lines[i][j].green = invertedCopy.maxColor - invertedCopy.lines[i][j].green;
            invertedCopy.lines[i][j].blue = invertedCopy.maxColor - invertedCopy.lines[i][j].blue;
        }
    }
    return invertedCopy;
}
bool PPMImage::operator == (const PPMImage& rightValue) const {
	if (width == rightValue.width && height == rightValue.height) {

	}
    else {
        return false;
    }
}
bool PPMImage::operator != (const PPMImage& rightValue) const {
	if (width == rightValue.width && height == rightValue.height) {

	}
	else {
		return true;
	}
}
ostream& operator << (ostream& out, const PPMImage& image) {
    return out;
}
istream& operator >> (istream& in, PPMImage& image) {
    return in;
}