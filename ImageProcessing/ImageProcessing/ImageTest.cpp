#include "ImageTest.h"
using namespace ImageProcess;

std::string testName(int test) {
	if (test == 1)
		return "Test_Create";
	if (test == 2)
		return "Test_Save";
	if (test == 3)
		return "Test_Addition";
	if (test == 4)
		return "Test_ScalarAddition";
	if (test == 5)
		return "Test_Subtraction";
	if (test == 6)
		return "Test_ScalarSubtraction";
	if (test == 7)
		return "Test_Multiplication";
	if (test == 8)
		return "Test_ScalarMultiplication";
	if (test == 9)
		return "Test_GetRoi";
	if (test == 10)
		return "Test_isEmpty";
	if (test == 11)
		return "Test_Processing";
	if (test == 12)
		return "Test_Drawing";

	return "";
}

int run_test(int test) {
	switch (test)
	{
	case 1:
	{
		{
			Image img = Image();
			for (int i = 0; i < img.height(); i++) {
				unsigned int* current_row = img.get_row(i);
				for (int j = 0; j < img.width(); j++)
					if (current_row[j] != 0)
						return 1;
			}
		}

		{
			Image img = Image(3, 3);
			if (img.width() != 3)
				return 2;
			if (img.height() != 3)
				return 2;
		}

		{
			Image img = Image();
			img.load("test1.pgm");
			for (int i = 0; i < img.height(); i++) {
				unsigned int* current_row = img.get_row(i);
				for (int j = 0; j < img.width(); j++)
					if (current_row[j] != j + 1)
						return 3;
			}
		}
		return 0;
	}

	case 2:
	{
		{
			Image img = Image();
			img.load("test1.pgm");
			img.save("test1_saved.pgm");
			Image result_img = Image();
			result_img.load("test1_saved.pgm");

			for (int i = 0; i < img.height(); i++) {
				unsigned int* current_row = img.get_row(i);
				unsigned int* current_saved_row = result_img.get_row(i);
				for (int j = 0; j < img.width(); j++)
					if (current_row[j] != current_saved_row[j])
						return 1;
			}
		}
		return 0;
	}

	case 3:
	{
		{
			Image img1 = Image(), img2 = Image();
			Image img3 = img1 + img2;

			for (int i = 0; i < img3.height(); i++) {
				unsigned int* current_row = img3.get_row(i);
				for (int j = 0; j < img3.width(); j++)
					if (current_row[j] != 0)
						return 1;
			}
		}

		{
			Image img1 = Image(), img2 = Image();
			img1.load("test1.pgm");
			img2.load("test1.pgm");
			Image img3 = img1 + img2;

			for (int i = 0; i < img3.height(); i++) {
				unsigned int* current_row = img3.get_row(i);
				unsigned int* current_result_row = img1.get_row(i);
				for (int j = 0; j < img3.width(); j++)
					if (current_row[j] != current_result_row[j] * 2)
						return 2;
			}
		}
		return 0;
	}

	case 4:
	{
		{
			Image img = Image();
			img = img + 1;

			for (int i = 0; i < img.height(); i++) {
				unsigned int* current_row = img.get_row(i);
				for (int j = 0; j < img.width(); j++)
					if (current_row[j] != 1)
						return 1;
			}
		}

		{
			Image img = Image();
			img = img + 256;

			for (int i = 0; i < img.height(); i++) {
				unsigned int* current_row = img.get_row(i);
				for (int j = 0; j < img.width(); j++)
					if (current_row[j] != 255)
						return 2;
			}
		}
		return 0;
	}

	case 5:
	{
		{
			Image img1 = Image(), img2 = Image();
			Image img3 = img1 - img2;

			for (int i = 0; i < img3.height(); i++) {
				unsigned int* current_row = img3.get_row(i);
				for (int j = 0; j < img3.width(); j++)
					if (current_row[j] != 0)
						return 1;
			}
		}

		{
			Image img1 = Image(), img2 = Image();
			img1.load("test1.pgm");
			img2.load("test1.pgm");
			Image img3 = img1 - img2;

			for (int i = 0; i < img3.height(); i++) {
				unsigned int* current_row = img3.get_row(i);
				unsigned int* current_result_row = img1.get_row(i);
				for (int j = 0; j < img3.width(); j++)
					if (current_row[j] != 0)
						return 2;
			}
		}
		return 0;
	}

	case 6:
	{
		{
			Image img = Image();
			img = img - 1;

			for (int i = 0; i < img.height(); i++) {
				unsigned int* current_row = img.get_row(i);
				for (int j = 0; j < img.width(); j++)
					if (current_row[j] != 0)
						return 1;
			}
		}

		{
			Image img = img.ones(4, 4);
			img = img - 1;

			for (int i = 0; i < img.height(); i++) {
				unsigned int* current_row = img.get_row(i);
				for (int j = 0; j < img.width(); j++)
					if (current_row[j] != 0)
						return 2;
			}
		}
		return 0;
	}

	case 7:
	{
		{
			Image img1 = img1.ones(4, 4), img2 = img2.zeros(4, 4);
			Image img3 = img1 * img2;

			for (int i = 0; i < img3.height(); i++) {
				unsigned int* current_row = img3.get_row(i);
				for (int j = 0; j < img3.width(); j++)
					if (current_row[j] != 0)
						return 1;
			}
		}

		{
			Image img1 = img1.ones(4, 4), img2 = Image();
			img2.load("test1.pgm");
			Image img3 = img1 * img2;
			
			for (int i = 0; i < img3.height(); i++) {
				unsigned int* current_row = img3.get_row(i);
				unsigned int* current_result_row = img2.get_row(i);
				for (int j = 0; j < img3.width(); j++)
					if (current_row[j] != current_result_row[j])
						return 2;
			}
		}
		return 0;
	}

	case 8:
	{
		{
			Image img1 = img1.ones(4, 4);
			img1 = img1 * 2;

			for (int i = 0; i < img1.height(); i++) {
				unsigned int* current_row = img1.get_row(i);
				for (int j = 0; j < img1.width(); j++)
					if (current_row[j] != 2)
						return 1;
			}
		}

		{
			Image img1 = img1.ones(4, 4);
			img1 = img1 * 256;

			for (int i = 0; i < img1.height(); i++) {
				unsigned int* current_row = img1.get_row(i);
				for (int j = 0; j < img1.width(); j++)
					if (current_row[j] != 255)
						return 2;
			}
		}
		return 0;
	}

	case 9:
	{
		{
			Image img1 = img1.ones(3, 3);
			Image img2 = Image();
			img2 = img1.getROI(img2, Rectangle(Point(0, 0), Size(2, 2)));
			if (img2.height() != 2)
				return 1;
			if (img2.width() != 2)
				return 1;
		}

		{
			Image img1 = img1.ones(3, 3);
			Image img2 = Image();
			img1.getROI(img2, Rectangle(Point(0, 0), Size(2, 2)));

			for (int i = 0; i < img2.height(); i++) {
				unsigned int* current_row = img2.get_row(i);
				for (int j = 0; j < img2.width(); j++)
					if (current_row[j] != 1)
						return 2;
			}
		}
		return 0;
	}

	case 10:
	{
		{
			Image img = img.zeros(2, 2);
			bool empty = img.isEmpty();
			
			if (!empty)
				return 1;
		}

		{
			Image img = img.ones(2, 2);
			bool empty = img.isEmpty();

			if (empty)
				return 2;
		}
		return 0;
	}

	case 11:
	{
		// Image Brightness and Contrast Start

		{
			Image img1 = img1.ones(4, 4), img2;
			ImageBrightnessAndContrast ImgMod = ImageBrightnessAndContrast(1, 1);
			ImgMod.process(img1, img2);

			for (int i = 0; i < img2.height(); i++) {
				unsigned int* current_row = img2.get_row(i);
				unsigned int* current_result_row = img1.get_row(i);
				for (int j = 0; j < img2.width(); j++)
					if (current_row[j] != 1 * current_result_row[j] + 1)
						return 1;
			}
		}

		{
			Image img1 = img1.ones(4, 4), img2;
			ImageBrightnessAndContrast ImgMod = ImageBrightnessAndContrast(1, 300);
			ImgMod.process(img1, img2);

			for (int i = 0; i < img2.height(); i++) {
				unsigned int* current_row = img2.get_row(i);
				for (int j = 0; j < img2.width(); j++)
					if (current_row[j] != 255)
						return 2;
			}
		}

		// Image Brightness and Constrast End

		// Image Gamma Correction Start

		{
			Image img1 = img1.ones(4, 4), img2 = img1;
			ImageGammaCorrection ImgMod = ImageGammaCorrection(1);
			ImgMod.process(img1, img2);

			for (int i = 0; i < img2.height(); i++) {
				unsigned int* current_row = img2.get_row(i);
				unsigned int* current_result_row = img1.get_row(i);
				for (int j = 0; j < img2.width(); j++)
					if (current_row[j] != current_result_row[j])
						return 3;
			}
		}

		{
			Image img1 = img1.ones(4, 4), img2 = img1;
			ImageGammaCorrection ImgMod = ImageGammaCorrection(2);
			ImgMod.process(img1, img2);

			for (int i = 0; i < img2.height(); i++) {
				unsigned int* current_row = img2.get_row(i);
				unsigned int* current_result_row = img1.get_row(i);
				for (int j = 0; j < img2.width(); j++)
					if (current_row[j] != pow(current_result_row[j], 2))
						return 4;
			}
		}

		// Image Gamma Correction End

		// Image Convolution Start

		{
			int K[3][3] = { {0, 0, 0}, {0, 1, 0}, {0, 0, 0} }; // Identity Kernel
			Image img1 = img1.ones(3, 3), img2;
			ImageConvolution ImgMod = ImageConvolution(K);
			ImgMod.process(img1, img2);
			
			for (int i = 0; i < img2.height(); i++) {
				unsigned int* current_row = img2.get_row(i);
				for (int j = 0; j < img2.width(); j++)
					if (current_row[i] != 1)
						return 5;
			}
		}

		// Image Convolution End
		

		return 0;
	}

	default:
		break;

	};
}

void run_tests() {
	for (int i = 0; i < 11; i++)
	{
		if (run_test(i + 1) != 0)
			std::cout << testName(i + 1) << " " << run_test(i + 1) << " FAILED" << '\n';
		else
			std::cout << testName(i + 1) << " PASSED" << '\n';
	}
}