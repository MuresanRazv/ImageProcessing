#pragma once
#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>

namespace ImageProcess {
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
		Point(int x_coord, int y_coord);

		int x;
		int y;
	private:
		friend class Image;
	};

	class Rectangle : public Point, Size {
	public:
		Rectangle();
		Rectangle(Point point, Size size);
		Rectangle(Point point1, Point point2);

		Rectangle operator+(int k);
		Rectangle operator-(int k);

		Rectangle operator&(Rectangle rect);
		Rectangle operator|(Rectangle rect);

		Point p;
		Size s;
	private:
		friend class Image;
	};

	class Image : public Rectangle {
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

		friend void drawCircle(Image& img, Point center, int radius, unsigned char color);
		friend void drawLine(Image& img, Point p1, Point p2, unsigned char color);
		friend void drawRectangle(Image& img, Rectangle r, unsigned char color);
		friend void drawRectangle(Image& img, Point tl, Point br, unsigned char color);

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

	class ImageProcessing : public Rectangle {
	public:
		void process(const Image& src, Image& dst);
	private:
		friend class Image;
	};

	class ImageBrightnessAndContrast : public ImageProcessing {
	public:
		ImageBrightnessAndContrast();
		ImageBrightnessAndContrast(double g, double b);

		void process(const Image& src, Image& dst);

	private:
		double gain;
		double bias;
	};

	class ImageGammaCorrection : public ImageProcessing {
	public:
		ImageGammaCorrection();
		ImageGammaCorrection(double gamma_encoding_factor);

		void process(const Image& src, Image& dst);

	private:
		double gamma;
	};

	class ImageConvolution : public ImageProcessing {
	public:
		ImageConvolution();
		ImageConvolution(int kernel[3][3]);

		void process(const Image& src, Image& dst);

		bool compare(int ker1[3][3], int ker2[3][3]);

	private:
		int K[3][3];
	};

	void drawCircle(Image& img, Point center, int radius, unsigned char color);
	void drawLine(Image& img, Point p1, Point p2, unsigned char color);
	void drawRectangle(Image& img, Rectangle r, unsigned char color);
	void drawRectangle(Image& img, Point tl, Point br, unsigned char color);
}