#include "ImageProcessing.h"
#include "Image.h"
#include <iostream>

// Brightness and Constrast subclass Start

ImageBrightnessAndContrast::ImageBrightnessAndContrast() {
	gain = 1;
	bias = 0;
}

ImageBrightnessAndContrast::ImageBrightnessAndContrast(unsigned int g, int b) {
	gain = g;
	bias = b;
}

void ImageBrightnessAndContrast::process(const Image& src, Image& dst) {
	// Initialize destination Image with source Image
	dst = src;

	// Go through each pixel and set their corresponding value
	for (int h = 0; h < dst.height(); h++)
		for (int w = 0; w < dst.width(); w++) {
			dst.m_data[h][w] = gain * dst.m_data[h][w] + bias;
			if (dst.m_data[h][w] > 255)
				dst.m_data[h][w] = 255;
		}
}

// Brightness and Constrast subclass End

// Gamma Correction subclass Start

ImageGammaCorrection::ImageGammaCorrection() {
	gamma = 0;
}

ImageGammaCorrection::ImageGammaCorrection(int gamma_encoding_factor) {
	gamma = gamma_encoding_factor;
}

void ImageGammaCorrection::process(const Image& src, Image& dst) {
	// Initialize destination Image with source Image
	dst = src;

	// Go through each pixel and set their corresponding value
	for (int h = 0; h < dst.height(); h++)
		for (int w = 0; w < dst.width(); w++)
			if (gamma != 0)
				dst.m_data[h][w] = pow(dst.m_data[h][w], gamma);
}

// Gamma Correction subclass End

// Convolution subclass Start

ImageConvolution::ImageConvolution() {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			K[i][j] = 1;
}

ImageConvolution::ImageConvolution(unsigned int** kernel) {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			K[i][j] = kernel[i][j];
}

void ImageConvolution::process(const Image& src, Image& dst) {
	// Initialize destination Image with source Image
	dst = src;

	// Go through each pixel and set their corresponding value
	for (int h = 0; h < dst.height(); h++)
		for (int w = 0; w < dst.width(); w++)
			dst.m_data[h][w];
}

// Convolution subclass End