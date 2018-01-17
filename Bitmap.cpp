#include "Bitmap.h"
#include "BitmapInfoHeader.h"
#include "BitmapFileHeader.h"
#include <fstream>

Bitmap::Bitmap(int width, int height)
	: _width{ width },
	_height{ height },
	_pPixels{ new uint8_t[width * height * 3]{ 0 } } {

	// move new operator here to check exceptions?
}

void Bitmap::setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue) {
	uint8_t* pPixel = _pPixels.get();

	pPixel += 3 * (_width * y + x);

	pPixel[0] = blue;
	pPixel[1] = green;
	pPixel[2] = red;


}

bool Bitmap::write(std::string filename) {

	/* ---- Info filling ----- */

	BitmapFileHeader bFileH;
	BitmapInfoHeader bInfoH;

	bFileH.fileSize = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader)
		+ _width * _height * 3;
	bFileH.dataOffset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);

	bInfoH.width = _width;
	bInfoH.height = _height;

	/* ---- File writing ---- */

	std::ofstream file;
	file.open(filename, std::ios::out | std::ios::binary);

	if (!file) {
		return false;
	}
	//? change char*
	file.write((char*)&bFileH, sizeof(bFileH));
	file.write((char*)&bInfoH, sizeof(bInfoH));
	file.write((char*)_pPixels.get(), _width * _height * 3);

	file.close();


	if (!file) {
		return false;
	}
	return true;

}


Bitmap::~Bitmap()
{
}
