#pragma once
#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>

class Size {
public:
	Size();
	Size(unsigned int w, unsigned int h);

	unsigned int width;
	unsigned int height;
private:
	friend class Image;
};

class Point {
public:
	Point();
	Point(unsigned int x_coord, unsigned int y_coord);

	int x;
    int y;
private:
	friend class Image;
};

class Rectangle {
public:
	Rectangle();
	Rectangle(Point point, Size size);

	Point p;
	Size s;
private:
	friend class Image;
};

class Image {
public:
	Image();
	Image(unsigned int w, unsigned int h);
	Image(const Image& other);

	~Image();

	bool load(std::string imagePath);
	bool save(std::string imagePath);

	Image& operator=(const Image& other);
	Image operator+(const Image& i);
	Image operator-(const Image& i);
	Image operator*(const Image& i);

	Image operator+(int k);
	Image operator-(int k);
	Image operator*(int k);

	Image getROI(Image& roiImg, Rectangle roiRect);
	Image getROI(Image& roiImg, unsigned int x, unsigned int y, unsigned int width, unsigned int height);

	bool isEmpty() const;

	Size size() const;

	unsigned int width() const;
	unsigned int height() const;

	unsigned int& at(unsigned int x, unsigned int y);
	unsigned int& aat(Point pt);

	unsigned int* get_row(unsigned int r);

	void release();

	friend std::ostream& operator<<(std::ostream& os, const Image& dt);
	
	static Image zeros(unsigned int width, unsigned int height);
	static Image ones(unsigned int width, unsigned int height);

private:
	unsigned int** m_data;
	unsigned int m_width;
	unsigned int m_height;
	Size m_size;
	friend class Size;
	friend class ImageProcessing;
	friend class ImageBrightnessAndContrast;
	friend class ImageGammaCorrection;
	friend class ImageConvolution;
};