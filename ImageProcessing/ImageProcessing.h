#include "Image.h"
#pragma once

class ImageProcessing {
public:
	void process(const Image& src, Image& dst);
private:
	friend class Image;
};

class ImageBrightnessAndContrast : public ImageProcessing {
public:
	ImageBrightnessAndContrast();
	ImageBrightnessAndContrast(unsigned int g, int b);

	void process(const Image& src, Image& dst);

private:
	unsigned int gain;
	int bias;
};

class ImageGammaCorrection : public ImageProcessing {
public:
	ImageGammaCorrection();
	ImageGammaCorrection(int gamma_encoding_factor);

	void process(const Image& src, Image& dst);

private:
	int gamma;
};

class ImageConvolution : public ImageProcessing {
	ImageConvolution();
	ImageConvolution(unsigned int** kernel);

	void process(const Image& src, Image& dst);

private:
	int K[3][3];
};
