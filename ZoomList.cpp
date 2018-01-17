#include "ZoomList.h"

//#include <iostream>

//ZoomList::ZoomList(int width, int height) : _width( width ), _height( height ) {}

void ZoomList::add(const Zoom& z) {
	zooms.push_back(z);    // push_back or emaplce back or move?

	_xCenter +=  (z._x - _width / 2)  * _scale;
	_yCenter += -(z._y - _height / 2) * _scale;
	_scale *= z._scale;

}


std::pair<double, double> ZoomList::doZoom(int x, int y) {

	double xFractal = (x - _width / 2) * _scale + _xCenter;
	double yFractal = (y - _height / 2) * _scale + _yCenter;

	return std::pair<double, double>{xFractal, yFractal};
}
