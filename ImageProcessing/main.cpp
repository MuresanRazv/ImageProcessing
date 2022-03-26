#include <iostream>
#include <string.h>
#include "Image.h"
#include "ImageProcessing.h"

int main() {
	Image img1 = Image(4, 5);
	img1.load("example.pgm");
	Image img2 = Image();
	Rectangle r = Rectangle(Point(2, -1), Size(4, 8));
	img1.getROI(img2, r);
	std::cout << img2;
	return 0;
}