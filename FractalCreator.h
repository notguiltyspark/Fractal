#pragma once

#ifndef FRACTALCREATOR_H
#define FRACTALCREATOR_H

#include "Bitmap.h"
#include "Mandelbrot.h"
#include "Zoom.h"
#include "ZoomList.h"
#include "RGB.h"

#include <string>
#include <vector>
#include <cstdint>
#include <memory>
#include <math.h>

class FractalCreator {
private:

	int _width;
	int _height;
	int _total = 0;

	std::vector<int>    _histogram;
	std::vector<int>    _fractal;
	std::vector<int>    _ranges;
	std::vector<RGB>    _colors;
	std::vector<int>	_rangeTotals;

	bool _bGotFirstRange = false;

	Bitmap   _bitmap;
	ZoomList _zoom_l;



public:

	FractalCreator(int width, int height);
	virtual ~FractalCreator();

	void addRange(double rangeEnd, const RGB& rgb);
	void addZoom(const Zoom& zoom);
	void calculateIteration();
	void calculateTotalIterations();
	void calculateRangeTotals();
	void drawFractal();
	void writeBitmap(const std::string& name);
	int getRange(int iterations) const;
};

#endif