#include "Image.h"
#include <iostream>
#include <iomanip>
#include <string.h>
#include <fstream>
#include <sstream>

// Size Class Start
namespace ImageProcess {
	Size::Size() {
		width = 0;
		height = 0;
	}

	Size::Size(unsigned int w, unsigned int h) {
		width = w;
		height = h;
	}

	// Size Class End

	// Point Class Start

	Point::Point() {
		x = 0;
		y = 0;
	}

	Point::Point(int x_coord, int y_coord) {
		x = x_coord;
		y = y_coord;
	}

	// Point Class End

	// Rectangle Class Start

	Rectangle::Rectangle() {
		p = Point();
		s = Size();
	}

	Rectangle::Rectangle(Point point, Size size) {
		p = point;
		s = size;
	}

	Rectangle::Rectangle(Point point1, Point point2) {
		p = point1;
		s = Size(point2.x - point1.x, point2.y - point1.y);
	}

	Rectangle Rectangle::operator+(int k) {
		return Rectangle(Point(p.x + k, p.y + k), s);
	}

	Rectangle Rectangle::operator-(int k) {
		return Rectangle(Point(p.x - k, p.y - k), s);
	}

	Rectangle Rectangle::operator&(Rectangle rect) {
		Rectangle result_rectangle;

		// Set the size of the result rectangle
		result_rectangle.s = Size(abs((int)s.width - (int)rect.s.width), abs((int)s.height - (int)rect.s.height));

		// Get starting point of the result rectangle
		if ((p.x > rect.p.x) && (p.y > rect.p.y))
			result_rectangle.p = p;
		else
			result_rectangle.p = rect.p;

		return result_rectangle;
	}

	Rectangle Rectangle::operator|(Rectangle rect) {
		Rectangle result_rectangle;

		// Set the size of the result rectangle
		result_rectangle.s = Size(s.width + rect.s.width, s.height + rect.s.height);

		// Get starting point of the result rectangle
		if (!((p.x > rect.p.x) && (p.y > rect.p.y)))
			result_rectangle.p = p;
		else
			result_rectangle.p = rect.p;

		return result_rectangle;
	}

	// Rectangle Class End

	// Image Class Start

	Image::Image() {
		m_width = 0;
		m_height = 0;
		m_size = Size(m_width, m_height);

		m_data = new unsigned int* [m_height]();

		for (int h = 0; h < m_height; h++)
			m_data[h] = new unsigned int[m_width]();
	}

	Image::Image(unsigned int w, unsigned int h) {
		m_width = w;
		m_height = h;
		m_size = Size(w, h);

		m_data = new unsigned int* [m_height]();

		for (int h = 0; h < m_height; h++)
			m_data[h] = new unsigned int[m_width]();
	}

	Image::Image(const Image& other) {
		m_width = other.m_width;
		m_height = other.m_height;
		m_size = other.m_size;
		m_data = new unsigned int* [m_height]();

		for (int h = 0; h < m_height; h++)
			m_data[h] = new unsigned int[m_width]();

		for (int h = 0; h < m_height; h++)
			for (int w = 0; w < m_width; w++)
				m_data[h][w] = other.m_data[h][w];
	}

	Image& Image::operator=(const Image& other) {
		// free old matrix of pixels
		release();

		m_width = other.m_width;
		m_height = other.m_height;
		m_size = other.m_size;

		// allocate new matrix of pixels
		m_data = new unsigned int* [m_height]();

		for (int h = 0; h < m_height; h++)
			m_data[h] = new unsigned int[m_width]();

		// put pixels from other to this object's matrix
		for (int h = 0; h < m_height; h++)
			for (int w = 0; w < m_width; w++)
				m_data[h][w] = other.m_data[h][w];
		return *this;
	}

	Image::~Image() {
		release();
	}

	unsigned int Image::width() const {
		return m_width;
	}

	unsigned int Image::height() const {
		return m_height;
	}

	Size Image::size() const {
		return m_size;
	}

	bool Image::load(std::string imagePath) {
		unsigned int pgm_width = 0, pgm_height = 0, pgm_max_gray = 0;
		std::string inputLine = "";
		std::ifstream infile(imagePath);
		std::stringstream ss;
		// First line : version
		getline(infile, inputLine);
		if (inputLine.compare("P2") != 0)
		{
			std::cout << "Version Error";
			return false;
		}
		//else
			//std::cout << "Version : " << inputLine << '\n';

		// Second line : comment
		getline(infile, inputLine);
		//std::cout << "Comment : " << inputLine << '\n';

		// Third line : size
		ss << infile.rdbuf();
		ss >> pgm_width >> pgm_height;
		*this = Image(pgm_width, pgm_height);
		//std::cout << "width = " << m_width << " and height = " << m_height << '\n';

		// Fourth line : maximum gray value

		ss >> pgm_max_gray;
		//std::cout << "maximum gray value = " << pgm_max_gray << '\n';

		// Following lines : read pixels
		for (int h = 0; h < m_height; h++)
			for (int w = 0; w < m_width; w++) {
				ss >> m_data[h][w];
				if (m_data[h][w] > pgm_max_gray) {
					std::cout << "Gray value excedeed!";
					return false;
				}
			}

		//std::cout << *this;

		infile.close();
		return true;
	}

	bool Image::save(std::string imagePath) {
		std::ofstream outfile(imagePath);
		std::stringstream ss;

		// First line : version
		outfile << "P2" << '\n';

		// Second line : comment
		outfile << "# This is a saved pgm file." << '\n';

		// Third line : size
		outfile << m_size.width << " " << m_size.height << '\n';

		// Fourth line : maximum gray value
		outfile << "255" << '\n';

		// Following lines : pixels
		for (int h = 0; h < m_height; h++) {
			for (int w = 0; w < m_width; w++)
				outfile << m_data[h][w] << " ";
			outfile << '\n';
		}

		outfile.close();
		return true;
	}

	std::ostream& operator<<(std::ostream& os, const Image& dt) {
		Size sz = dt.size();

		for (int h = 0; h < sz.height; h++) {
			os << std::setw(10);
			for (int w = 0; w < sz.width; w++) {
				os << std::setw(4);
				os << dt.m_data[h][w] << " ";
			}
			os << '\n';
		}

		return os;
	}

	Image Image::operator+(const Image& i) {
		Image result_image = Image(m_width, m_height);
		Size sz = result_image.size();

		for (int h = 0; h < sz.height; h++)
			for (int w = 0; w < sz.width; w++)
				if (m_data[h][w] + i.m_data[h][w] <= 255)
					result_image.m_data[h][w] = m_data[h][w] + i.m_data[h][w];
				else
					result_image.m_data[h][w] = 255;
		return result_image;
	}

	Image Image::operator-(const Image& i) {
		Image result_image = Image(m_width, m_height);
		Size sz = result_image.size();

		for (int h = 0; h < sz.height; h++)
			for (int w = 0; w < sz.width; w++)
				if ((int)m_data[h][w] - (int)i.m_data[h][w] <= 0)
					result_image.m_data[h][w] = m_data[h][w] - i.m_data[h][w];
				else
					result_image.m_data[h][w] = 0;
		return result_image;
	}

	Image Image::operator*(const Image& i) {
		Image result_image = Image(m_width, m_height);
		Size sz = result_image.size();

		for (int h = 0; h < sz.height; h++)
			for (int w = 0; w < sz.width; w++)
				if (m_data[h][w] * i.m_data[h][w] <= 255)
					result_image.m_data[h][w] = m_data[h][w] * i.m_data[h][w];
				else
					result_image.m_data[h][w] = 255;
		return result_image;
	}

	Image Image::operator+(int k) {
		Image result_image = *this;
		Size sz = result_image.size();
		for (int h = 0; h < sz.height; h++)
			for (int w = 0; w < sz.width; w++)
				if (result_image.m_data[h][w] + k <= 255)
					result_image.m_data[h][w] += k;
				else
					result_image.m_data[h][w] = 255;
		return result_image;
	}

	Image Image::operator-(int k) {
		Image result_image = *this;
		Size sz = result_image.size();
		for (int h = 0; h < sz.height; h++)
			for (int w = 0; w < sz.width; w++)
				if ((int)result_image.m_data[h][w] - k >= 0)
					result_image.m_data[h][w] -= k;
				else
					result_image.m_data[h][w] = 0;
		return result_image;
	}

	Image Image::operator*(int k) {
		Image result_image = *this;
		Size sz = result_image.size();
		for (int h = 0; h < sz.height; h++)
			for (int w = 0; w < sz.width; w++)
				if (result_image.m_data[h][w] * k <= 255)
					result_image.m_data[h][w] *= k;
				else
					result_image.m_data[h][w] = 255;
		return result_image;
	}

	bool Image::isEmpty() const {
		Size sz = m_size;

		for (int h = 0; h < sz.height; h++)
			for (int w = 0; w < sz.width; w++)
				if (m_data[h][w] != 0)
					return false;
		return true;
	}

	unsigned int& Image::at(unsigned int x, unsigned int y) {
		return m_data[x][y];
	}

	unsigned int& Image::aat(Point pt) {
		return m_data[pt.x][pt.y];
	}

	unsigned int* Image::get_row(unsigned int r) {
		return m_data[r];
	}

	void Image::release() {
		for (int h = 0; h < m_height; h++)
			delete[] m_data[h];
		delete[] m_data;
	}

	Image Image::getROI(Image& roiImg, Rectangle roiRect) {
		Size result_size = roiRect.s;
		Point result_point = roiRect.p;
		roiImg = Image(result_size.width, result_size.height);
		roiImg.m_size = result_size;

		// Build the new result image
		for (int h = result_point.y, r_h = 0; h < (int)result_point.y + (int)roiImg.height(); h++, r_h++) {
			for (int w = result_point.x, r_w = 0; w < (int)result_point.x + (int)roiImg.width(); w++, r_w++) {
				if ((h >= 0 && h < m_height) && (w >= 0 && w < m_width))
					roiImg.m_data[r_h][r_w] = m_data[h][w];
			}
		}

		return roiImg;
	}

	Image Image::getROI(Image& roiImg, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
		roiImg = Image(width, height);
		Point result_point = Point(x, y);
		roiImg.m_size = Size(width, height);


		// Build the new result image
		for (int h = result_point.y, r_h = 0; h < (int)result_point.y + (int)roiImg.height(); h++, r_h++) {
			for (int w = result_point.x, r_w = 0; w < (int)result_point.x + (int)roiImg.width(); w++, r_w++) {
				if ((h >= 0 && h < m_height) && (w >= 0 && w < m_width))
					roiImg.m_data[r_h][r_w] = m_data[h][w];
			}
		}

		return roiImg;
	}

	Image Image::zeros(unsigned int width, unsigned int height) {
		return Image(width, height);
	}

	Image Image::ones(unsigned int width, unsigned int height) {
		Image result_image = Image(width, height);

		for (int h = 0; h < result_image.height(); h++)
			for (int w = 0; w < result_image.width(); w++)
				result_image.m_data[h][w] = 1;

		return result_image;
	}

	// Image Class End

}