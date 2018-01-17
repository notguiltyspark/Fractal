#include "FractalCreator.h"
#include <iostream>
#include <cassert>
FractalCreator::FractalCreator(int width, int height)
	: _width( width ),
	_height( height ),
	_zoom_l(width, height),
	_bitmap(_width, _height),
	_histogram( Mandelbrot::MAX_ITERATIONS , 0 ),
	_fractal( _width * _height             , 0 )
{
	_zoom_l.add(Zoom(_width/2, _height/2, 4.0/_width));
}


FractalCreator::~FractalCreator() {
}

void FractalCreator::addZoom(const Zoom& zoom) {
	_zoom_l.add(zoom);
}

void FractalCreator::addRange(double rangeEnd, const RGB& rgb) {
	_ranges.push_back(rangeEnd * Mandelbrot::MAX_ITERATIONS);
	_colors.push_back(rgb);

	if (_bGotFirstRange == true) {
		_rangeTotals.push_back(0);
	}

	_bGotFirstRange = true;

}


void FractalCreator::calculateIteration() {

	for (int y = 0; y < _height; y++) {
		for (int x = 0; x < _width; x++) {

			auto coordinates = _zoom_l.doZoom(x, y);
			auto xFractal = coordinates.first;
			auto yFractal = coordinates.second;

			int iterations = Mandelbrot::getIterations(xFractal, yFractal);

			_fractal.at(y * _width + x) = iterations;

			if (iterations != Mandelbrot::MAX_ITERATIONS) {
				_histogram.at(iterations)++;
			}

		}
	}

}

void FractalCreator::calculateTotalIterations() {
	for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++) {
		_total += _histogram.at(i);
	}
}

void FractalCreator::calculateRangeTotals() {
	// fragile for INPUT!!!
	int rangeIndex = 0;

	for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++) {
		int pixels = _histogram[i];
		
		if (i >= _ranges[rangeIndex + 1]) {
			rangeIndex++;
		}
		
		_rangeTotals[rangeIndex] += pixels;

	}

	for (auto value : _rangeTotals) {
		std::cout << "Range total: " << value << std::endl;
	}
}
void FractalCreator::drawFractal() {


	for (int y = 0; y < _height; y++) {
		for (int x = 0; x < _width; x++) {


			uint8_t red = 0;
			uint8_t green = 0;
			uint8_t blue = 0;

			int iterations = _fractal.at(y*_width + x);
			
			int range = getRange(iterations);
			int rangeTotal = _rangeTotals[range];
			int rangeStart = _ranges[range];
			RGB& startColor = _colors[range];
			RGB& endColor = _colors[range + 1];
			RGB colorDiff = endColor - startColor;
			if (iterations != Mandelbrot::MAX_ITERATIONS) {
				uint8_t color = (uint8_t)(256 * (double)iterations / Mandelbrot::MAX_ITERATIONS);

				int totalPixels = 0;

				for (int i = rangeStart; i <= iterations; i++) {
					//hue += ((double)_histogram.at(i)) / _total;
					totalPixels += _histogram[i];
				}

				//green = hue * 255;
				red   = startColor.r + colorDiff.r * (double)totalPixels/rangeTotal;
				green = startColor.g + colorDiff.g * (double)totalPixels / rangeTotal;
				blue  = startColor.b + colorDiff.b * (double)totalPixels / rangeTotal;
				
			}
			
			_bitmap.setPixel(x, y, red, green, blue);

		}
	}
}

void FractalCreator::writeBitmap(const std::string& name) {

	_bitmap.write(name);
}

int FractalCreator::getRange(int iterations) const {
	int range = 0;

	for (int i = 1; i < _ranges.size(); i++) {
		if (_ranges[i] > iterations) {
			range = i - 1;
			break;
		}
	}

	assert(range > -1);
	assert(range < _ranges.size());

	return range;
}