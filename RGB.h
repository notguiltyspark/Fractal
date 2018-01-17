#pragma once

#ifndef RGB_H
#define RGB_H


struct RGB{
	double r; 
	double g;
	double b;
	RGB(double r, double g, double b) : r(r), g(g), b(b) {};
	//~RGB();
};

// rule of 3?
// move semantics etc???
RGB operator-(const RGB& first, const RGB& second);

#endif