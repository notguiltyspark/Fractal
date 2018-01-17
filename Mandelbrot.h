#pragma once
#ifndef MANDELBROT_H
#define MANDELBROT_H

#include <complex>

class Mandelbrot {
public:
	static const int MAX_ITERATIONS = 10500;
public:
	Mandelbrot();
	virtual ~Mandelbrot();

	static int getIterations(double x, double y);


};

#endif