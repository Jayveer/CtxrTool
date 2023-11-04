#include "bmp.h"

BMP::BMP()
{
}

BMP::~BMP()
{
	if (file) delete[] file;
}

void BMP::open(const char* filename)
{
	file = loadFile(filename, &size);
	header = (BMP_HEADER*)file;
	data = (uint8_t*)&header[1];
}

void BMP::create(uint32_t width, uint32_t height, uint8_t* data, int32_t dataSize)
{
	file = new uint8_t[0x36];
	memset(file, 0, 0x36);
	header = (BMP_HEADER*)file;

	header->header.type = 0x4D42;
	header->header.size = dataSize + 0x36;
	header->header.offBits = 0x36;
	
	header->info.size = 0x28;
	header->info.width = width;
	header->info.height = height;
	header->info.planes = 1;
	header->info.bitCount = 32;
	header->info.sizeImage = dataSize;
	header->info.xPelsPerMeter = 2834;
	header->info.yPelsPerMeter = 2834;

	this->data = data;
	this->size = header->header.size;
}

int32_t BMP::getSize()
{
	return size;
}

uint8_t* BMP::getData()
{
	return data;
}

uint32_t BMP::getWidth()
{
	return header->info.width;
}

uint32_t BMP::getHeight()
{
	return header->info.height;
}

void BMP::save(const char* filename)
{
	std::string output = "";
	writeDataToFile((uint8_t*)header, 0x36, filename, output);

	uint8_t* copy = new uint8_t[size - 0x36];
	flipVertical(copy, data, getWidth(), getHeight(), 4);
	writeDataToFile(copy, size - 0x36, filename, output, true);
	delete[] copy;
}