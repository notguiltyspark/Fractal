
#include "ZoomList.h"
#include "FractalCreator.h"

#include <iostream>
#include <vector>
#include <cmath>
#include <exception>

int main() {
	int WIDTH = 800;
	int HEIGHT = 600;
	try {
		FractalCreator fractalCreator(WIDTH, HEIGHT);

		fractalCreator.addRange(0.0, RGB(0, 0, 255));
		fractalCreator.addRange(0.05, RGB(255, 99, 71));
		fractalCreator.addRange(0.08, RGB(255, 215, 0));
		fractalCreator.addRange(1.0, RGB(255, 255, 255));

		fractalCreator.addZoom(Zoom(295, 202, 0.1));
		fractalCreator.addZoom(Zoom(312, 304, 0.1));

		fractalCreator.calculateIteration();
		fractalCreator.calculateTotalIterations();
		fractalCreator.calculateRangeTotals();
		fractalCreator.drawFractal();
		fractalCreator.writeBitmap("test.bmp");
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}