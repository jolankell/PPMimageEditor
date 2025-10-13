#include "PPMImage.h"
#include "fstream"
#include <iostream>
#include <ostream>
#include <istream>
#include <sstream>

// default constructor
PPMImage::PPMImage() {
	width = height = 0;
	maxColor = 255;
}

// testing constructor
PPMImage::PPMImage(int width1, int height1, int maxColor1) {
    width = width1; height = height1; maxColor = maxColor1;
    lines.resize(height);
    for (int i = 0; i < lines.size(); i++) {
        lines[i].setWidth(width);
        lines[i].setColorMax(maxColor);
    }
}

// destructor
PPMImage::~PPMImage() {

}

// custom constructor creates a PPMImage from a PPM file given through the 
// paramater filename if a bad file is given an excpetion will be thrown
PPMImage::PPMImage(string filename) {
    LoadFile(filename);
}

// loads the PPM file with the name defined in the string, If the file does 
// not exist, an exception is thrown
void PPMImage::LoadFile(string filename) {
    ifstream in(filename, ios::binary);
    if (!in) {
        throw runtime_error("Bad File");
    }

    in >> *this;
    in.close();
}

// draws a line from (startX, startY) to (endX, endY) with the color of color,
// if either point is outside the existing image, an exception is thrown
void PPMImage::DrawLine(const int& x1, const int& y1, const int& x2, const int& y2, const RGBValue& color) {

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
            throw runtime_error("invalid coridnates");
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

// copy constructor
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

// overlays two images such that the resulting image has the x dimension 
// of the image with the greater x dimension and the y dimension of the greater 
// y dimension. pixels are added together and % by the Maximum color size +1
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

// appends a PPMLine object to the end of an existing image.  If the 
// existing image has an X pixel value of 0, an exception is thrown, 
// if the PPMLine object does not have the same X value as the existing 
// image, an exception is also thrown
PPMImage PPMImage::operator + (const PPMLine& rightValue) {
    if (width == 0 || width != rightValue.getWidth()) {
        throw runtime_error("Image sizes don't line up");
    }
    else {
        PPMImage copy;
        copy = *this;
        copy.lines.push_back(rightValue);
        copy.height++;
        return copy;
    }
}

// Removes the PPMImage from the existing image such that resulting image 
// has the x dimension of the image with the greater x dimension and the y 
// dimension of the greater y dimension. Pixel colors change: left image - 
// right image % max color value + 1
PPMImage PPMImage::operator - (const PPMImage& rightValue) {
    PPMImage result;
    const PPMImage* widerImage;
    const PPMImage* tallerImage;
    RGBValue newColor;

    int smallerWidth = min(width, rightValue.width);
    int smallerHeight = min(height, rightValue.height);

    if (width >= rightValue.width) {
        widerImage = this;
        tallerImage = this;
        result = *this;

        if (height < rightValue.height) {
            tallerImage = &rightValue;
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
        widerImage = &rightValue;
        tallerImage = &rightValue;
        result = rightValue;

        if (height > rightValue.height) {
            tallerImage = this;
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
            newColor.red = ((lines[i][j].red - rightValue.lines[i][j].red) + (result.maxColor + 1)) % (result.maxColor + 1);
            newColor.green = ((lines[i][j].green - rightValue.lines[i][j].green) + (result.maxColor + 1)) % (result.maxColor + 1);
            newColor.blue = ((lines[i][j].blue - rightValue.lines[i][j].blue) + (result.maxColor + 1)) % (result.maxColor + 1);
            result.lines[i][j] = newColor;
        }
    }

    for (int i = 0; i < widerImage->height; i++) {
        for (int j = smallerWidth; j < widerImage->width; j++) {
            newColor.red = ((0 - widerImage->lines[i][j].red) + (result.maxColor + 1)) % (result.maxColor + 1);
            newColor.green = ((0 - widerImage->lines[i][j].green) + (result.maxColor + 1)) % (result.maxColor + 1);
            newColor.blue = ((0 - widerImage->lines[i][j].blue) + (result.maxColor + 1)) % (result.maxColor + 1);
            result.lines[i][j] = newColor;
        }
    }

    for (int i = smallerHeight; i < tallerImage->height; i++) {
        for (int j = 0; j < tallerImage->width; j++) {
            newColor.red = ((0 - tallerImage->lines[i][j].red) + (result.maxColor + 1)) % (result.maxColor + 1);
            newColor.green = ((0 - tallerImage->lines[i][j].green) + (result.maxColor + 1)) % (result.maxColor + 1);
            newColor.blue = ((0 - tallerImage->lines[i][j].blue) + (result.maxColor + 1)) % (result.maxColor + 1);
            result.lines[i][j] = newColor;
        }
    }
    return result;
}

// performs the + PPMLine functionality, but instead of returning a new PPMImage, it modifies the existing image
PPMImage& PPMImage::operator += (const PPMLine& rightValue) {
    if (width == 0 || width != rightValue.getWidth()) {
        throw runtime_error("Image sizes don't line up");
    }
    else {
        lines.push_back(rightValue);
        height++;
        return *this;
    }
}

// returns an image so that every pixel has the value of [Maximum color 
// size - the original pixel value]
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

// returns true if the images are the same, otherwise false
bool PPMImage::operator == (const PPMImage& rightValue) const {
    if (width == rightValue.width && height == rightValue.height) {
        if (width == 0 && height == 0) {
            return true;
        }
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (this->lines[i][j].red != rightValue.lines[i][j].red ||
                    this->lines[i][j].green != rightValue.lines[i][j].green ||
                    this->lines[i][j].blue != rightValue.lines[i][j].blue) {
                    return false;
                }
            }
        }
    }
    else {
        return false;
    }
    return true;
}

// returns true if the images are different, otherwise false
bool PPMImage::operator != (const PPMImage& rightValue) const {
	if (width == rightValue.width && height == rightValue.height) {
        if (width == 0 && height == 0) {
            return false;
        }
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {

                if (this->lines[i][j].red != rightValue.lines[i][j].red ||
                    this->lines[i][j].green != rightValue.lines[i][j].green ||
                    this->lines[i][j].blue != rightValue.lines[i][j].blue) {
                    return true;
                }
            }
        }
	}
	else {
		return true;
	}
    return false;
}

// outputs the raw data (this needs to work for both file output and cout)
ostream& operator << (ostream& out, const PPMImage& image) {
    out << "P6\n"
        << image.width << " " << image.height << "\n"
        << image.maxColor << "\n";

    if (image.maxColor < 256) { // 8 bit color
        for (int i = 0; i < image.height; i++) {
            for (int j = 0; j < image.width; j++) {
                RGBValue pixel = image.lines[i][j];
                unsigned char r = static_cast<unsigned char>(pixel.red);
                unsigned char g = static_cast<unsigned char>(pixel.green);
                unsigned char b = static_cast<unsigned char>(pixel.blue);
                out.write(reinterpret_cast<char*>(&r), 1);
                out.write(reinterpret_cast<char*>(&g), 1);
                out.write(reinterpret_cast<char*>(&b), 1);
            }
        }
    }
    else { // 16 bit color
        for (int i = 0; i < image.height; i++) {
            for (int j = 0; j < image.width; j++) {
                RGBValue pixel = image.lines[i][j];
                unsigned short r = static_cast<unsigned short>(pixel.red);
                unsigned short g = static_cast<unsigned short>(pixel.green);
                unsigned short b = static_cast<unsigned short>(pixel.blue);
                out.put(static_cast<char>((r >> 8) & 0xFF));
                out.put(static_cast<char>(r & 0xFF));
                out.put(static_cast<char>((g >> 8) & 0xFF));
                out.put(static_cast<char>(g & 0xFF));
                out.put(static_cast<char>((b >> 8) & 0xFF));
                out.put(static_cast<char>(b & 0xFF));
            }
        }
    }

    return out;
}

// reads the data from either a file stream or cin
istream& operator >> (istream& in, PPMImage& image) {
    string startNumber;
    in >> startNumber;

    if (!in || startNumber != "P6") {
        throw runtime_error("Bad file");
    }
    
    in >> image.width;
    in >> image.height;
    in >> image.maxColor;

    char ch;
    in.get(ch);

    // resize PPMImage storage
    image.lines.clear();
    image.lines.resize(image.height);
    for (int i = 0; i < image.height; i++) {
        image.lines[i].setWidth(image.width);
    }

    // read pixel data
    if (image.maxColor < 256 ) { // 8 bit color
        for (int i = 0; i < image.height; i++) {
            for (int j = 0; j < image.width; j++) {
                unsigned char r, g, b;
                in.read(reinterpret_cast<char*>(&r), 1);
                in.read(reinterpret_cast<char*>(&g), 1);
                in.read(reinterpret_cast<char*>(&b), 1);
                image.lines[i][j].red = static_cast<int>(r);
                image.lines[i][j].green = static_cast<int>(g);
                image.lines[i][j].blue = static_cast<int>(b);
            }
        }
    }
    else { // 16 bit color
        for (int i = 0; i < image.height; i++) {
            for (int j = 0; j < image.width; j++) {
                unsigned char bytes[6];
                in.read(reinterpret_cast<char*>(bytes), 6);

                image.lines[i][j].red = (bytes[0] << 8) | bytes[1];
                image.lines[i][j].green = (bytes[2] << 8) | bytes[3];
                image.lines[i][j].blue = (bytes[4] << 8) | bytes[5];
            }
        }
    }
    return in;
}