#include "tga.h"

TGA::TGA()
{
}

TGA::~TGA()
{
	if (file) delete[] file;
}

uint8_t* TGA::getData()
{
	return data;
}

int32_t TGA::getSize()
{
	return size;
}

uint32_t TGA::getWidth()
{
	return header->width;
}

uint32_t TGA::getHeight()
{
	return header->height;
}

uint32_t TGA::getNMipMaps()
{
	return 0;
}


void TGA::open(const char* filename)
{
	file = loadFile(filename, &size);
	header = (TGA_HEADER*)file;
	data = (uint8_t*)&header[1];
}

void TGA::create(uint32_t width, uint32_t height, uint8_t* data, int32_t dataSize)
{
	file = new uint8_t[0x12];

	memset(file, 0, 0x12);
	header = (TGA_HEADER*)file;

	header->magic = 0x20000;
	header->width = width;
	header->height = height;
	header->twenty = 0x2020;

	this->data = data;
	size = dataSize + 0x12;
}

void TGA::save(const char* filename)
{
	std::string output = "";
	writeDataToFile((uint8_t*)header, 0x12, filename, output);
	writeDataToFile(data, size - 0x12, filename, output, true);
}