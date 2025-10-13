#pragma once

#include "PPMLine.h"
#include <string>

class PPMImage
{
private:
	vector<PPMLine> lines;
	int width; int height;
	int maxColor;
public:
	// default constructor
	PPMImage();

	// destructor
	~PPMImage();
	
	// testing constructor
	PPMImage(int width1, int height1, int maxColor1);
	
	// creates a PPMImage from a PPM file given through the paramater filename
	// if a bad file is given an excpetion will be thrown
	PPMImage(string filename);
	
	// loads the PPM file with the name defined in the string, If the file does 
	// not exist, an exception is thrown
	void LoadFile(string filename);
	
	// draws a line from (startX, startY) to (endX, endY) with the color of color,
	// if either point is outside the existing image, an exception is thrown
	void DrawLine(const int& x1, const int& y1, const int& x2, const int& y2, const RGBValue& color);
	
	// copy constructor
	PPMImage& operator = (const PPMImage& rightValue);
	
	// overlays two images such that the resulting image has the x dimension 
	// of the image with the greater x dimension and the y dimension of the greater 
	// y dimension. pixels are added together and % by the Maximum color size +1
	PPMImage operator + (const PPMImage& rightValue);
	
	// appends a PPMLine object to the end of an existing image.  If the 
	// existing image has an X pixel value of 0, an exception is thrown, 
	// if the PPMLine object does not have the same X value as the existing 
	// image, an exception is also thrown
	PPMImage operator + (const PPMLine& rightValue);
	
	// Removes the PPMImage from the existing image such that resulting image 
	// has the x dimension of the image with the greater x dimension and the y 
	// dimension of the greater y dimension. Pixel colors change: left image - 
	// right image % max color value + 1
	PPMImage operator - (const PPMImage& rightValue);
	
	// performs the + PPMLine functionality, but instead of returning a new PPMImage, it modifies the existing image
	PPMImage& operator += (const PPMLine& rightValue);
	
	// returns an image so that every pixel has the value of [Maximum color 
	// size - the original pixel value]
	PPMImage operator - () const;

	// returns true if the images are the same, otherwise false
	bool operator == (const PPMImage& rightValue) const;

	// returns true if the images are different, otherwise false
	bool operator != (const PPMImage& rightValue) const;
	
	// outputs the raw data (this needs to work for both file output and cout)
	friend ostream& operator << (ostream& out, const PPMImage& image);
	
	// reads the data from either a file stream or cin
	friend istream& operator >> (istream& in, PPMImage& image);
};

