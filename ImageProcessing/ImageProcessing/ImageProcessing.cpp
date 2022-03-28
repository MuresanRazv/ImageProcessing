#include "Image.h"
#include <iostream>

// Brightness and Constrast subclass Start
namespace ImageProcess {
	ImageBrightnessAndContrast::ImageBrightnessAndContrast() {
		gain = 1;
		bias = 0;
	}

	ImageBrightnessAndContrast::ImageBrightnessAndContrast(double g, double b) {
		gain = g;
		bias = b;
	}

	void ImageBrightnessAndContrast::process(const Image& src, Image& dst) {
		// Initialize destination Image with source Image
		dst = src;

		// Go through each pixel and set their corresponding value
		for (int h = 0; h < dst.height(); h++)
			for (int w = 0; w < dst.width(); w++) {
				dst.m_data[h][w] = (int)(gain * dst.m_data[h][w] + bias);
				if (dst.m_data[h][w] > 255)
					dst.m_data[h][w] = 255;
				if (dst.m_data[h][w] < 0)
					dst.m_data[h][w] = 0;
			}
	}

	// Brightness and Constrast subclass End

	// Gamma Correction subclass Start

	ImageGammaCorrection::ImageGammaCorrection() {
		gamma = 0;
	}

	ImageGammaCorrection::ImageGammaCorrection(double gamma_encoding_factor) {
		gamma = gamma_encoding_factor;
	}

	void ImageGammaCorrection::process(const Image& src, Image& dst) {
		// Initialize destination Image with source Image
		dst = src;

		// Go through each pixel and set their corresponding value
		for (int h = 0; h < dst.height(); h++)
			for (int w = 0; w < dst.width(); w++) {
				if (gamma != 0)
					dst.m_data[h][w] = (int)pow(dst.m_data[h][w], gamma);
				if (dst.m_data[h][w] > 255)
					dst.m_data[h][w] = 255;
			}
	}

	// Gamma Correction subclass End

	// Convolution subclass Start

	ImageConvolution::ImageConvolution() {
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				K[i][j] = 1;
	}

	ImageConvolution::ImageConvolution(int kernel[3][3]) {
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				K[i][j] = kernel[i][j];
	}

	bool ImageConvolution::compare(int ker1[3][3], int ker2[3][3]) {
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (ker1[i][j] != ker2[i][j])
					return false;
		return true;
	}

	void ImageConvolution::process(const Image& src, Image& dst) {
		// Initialize destination Image with source Image
		dst = src;

		// Create all Kernel types in order to get the correct convolution result
		int MEAN_BLUR_KERNEL[3][3]{ {1, 1, 1}, {1, 1, 1}, {1, 1, 1} };
		int GAUSSIAN_BLUR_KERNEL[3][3]{ {1, 2, 1}, {2, 4, 2}, {1, 2, 1} };
		int HORIZONTAL_SOBEL_KERNEL[3][3]{ {1, 2, 1}, {0, 0, 0}, {-1, -2, -1} };
		int VERTICAL_SOBEL_KERNEL[3][3]{ {-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1} };


		// Go through each pixel and set their corresponding value
		for (int h = 0; h < dst.height(); h++)
			for (int w = 0; w < dst.width(); w++) {
				// Take a 3x3 portion of the image to convolute it with the kernel
				Rectangle conv_rect = Rectangle(Point(w - 1, h - 1), Size(3, 3));
				Image c_image;
				dst.getROI(c_image, conv_rect);

				int convoluted_pixel = 0;
				for (int i = 0; i < 3; i++)
					for (int j = 0; j < 3; j++)
						convoluted_pixel += (K[i][j] * c_image.m_data[i][j]);

				if (compare(K,MEAN_BLUR_KERNEL))
					convoluted_pixel /= 9;
				if (compare(K,GAUSSIAN_BLUR_KERNEL))
					convoluted_pixel /= 16;
				if (compare(K,HORIZONTAL_SOBEL_KERNEL)) {
					if (convoluted_pixel < 0)
						convoluted_pixel /= -4;
					else
						convoluted_pixel /= 4;
				}
				if (compare(K,VERTICAL_SOBEL_KERNEL)) {
					if (convoluted_pixel < 1)
						convoluted_pixel /= -4;
					else
						convoluted_pixel /= 4;
				}

				if (convoluted_pixel > 255)
					dst.m_data[h][w] = 255;
				else
					dst.m_data[h][w] = convoluted_pixel;
			}
	}
	
	// Convolution subclass End

	// Drawing modules start

	void drawCircle(Image& img, Point center, int radius, unsigned char color) {
		for (int h = center.y - radius; h < center.y + radius; h++)
			for (int w = center.x - radius; w < center.x + radius; w++)
				if ((w - center.x) * (w - center.x) + (h - center.y) * (h - center.y) <= radius * radius)
					img.m_data[h][w] = color;
	}

	void drawLine(Image& img, Point p1, Point p2, unsigned char color) {
		for (int h = p1.y; h <= p2.y; h++)
			for (int w = p1.x; w <= p2.x; w++)
				img.m_data[h][w] = color;
	}

	void drawRectangle(Image& img, Rectangle r, unsigned char color) {
		for (int h = r.p.y; h <= r.p.y + r.s.height - 1; h++)
			for (int w = r.p.x; w <= r.p.x + r.s.width - 1; w++)
				img.m_data[h][w] = color;
	}

	void drawRectangle(Image& img, Point tl, Point br, unsigned char color) {
		for (int h = br.y; h <= tl.y; h++)
			for (int w = tl.x; w <= br.x; w++)
				img.m_data[h][w] = color;
	}

	// Drawing modules end
}