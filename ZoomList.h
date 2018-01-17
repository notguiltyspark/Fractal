#pragma once

#ifndef ZOOMLIST_H
#define ZOOMLIST_H

#include "Zoom.h"
#include <vector>
#include <utility>

class ZoomList {
private:

	double _xCenter = 0;
	double _yCenter = 0;
	double _scale = 1;

	int _width = 0;
	int _height = 0;

	std::vector<Zoom> zooms;

public:

	ZoomList(int width, int height) : _width(width), _height(height) {}

	void add(const Zoom& zoom);
	std::pair<double, double> doZoom(int x, int y);
	//int zoomsSize() { return zooms.size(); };
};

#endif