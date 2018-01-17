
#ifndef BITMAPFILEHEADER_H
#define BITMAPFILEHEADER_H

#include <cstdint>


/* To prevent struct members aligning */
#pragma pack(2)

struct BitmapFileHeader {
	char header[2]{ 'B','M' };
	int32_t fileSize;
	int32_t reserverd = 0;
	int32_t dataOffset;
};

#endif