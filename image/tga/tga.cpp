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

bool TGA::isFlipped()
{
	return header->descriptor & 8;
}

void TGA::open(const char* filename)
{
	file = loadFile(filename, &size);
	header = (TGA_HEADER*)file;
	data = (uint8_t*)&header[1];
	footer = (TGA_FOOTER*)&((uint8_t*)file)[size - 0x1A];
}

void TGA::create(uint32_t width, uint32_t height, uint8_t* data, int32_t dataSize)
{
	file = new uint8_t[0x2C];

	memset(file, 0, 0x2C);
	header = (TGA_HEADER*)file;

	header->magic  = 0x20000;
	header->width  = width;
	header->height = height;
	header->bpp = 0x20;
	header->descriptor = 0x20;

	this->data = data;
	size = dataSize + 0x2C;


	footer = (TGA_FOOTER*)&((uint8_t*)file)[0x12];
	strncpy_s(footer->signature, "TRUEVISION-XFILE.", 18);

}

void TGA::save(const char* filename)
{
	std::string output = "";
	writeDataToFile((uint8_t*)header, 0x12, filename, output);
	writeDataToFile(data, size - 0x2C, filename, output, true);
	writeDataToFile((uint8_t*)footer, 0x1A, filename, output, true);
}