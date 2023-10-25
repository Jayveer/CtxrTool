#include "dds.h"

DDS::DDS()
{

}

DDS::~DDS()
{
	if (file) delete[] file;
}


void DDS::open(const char* filename)
{
	file   = loadFile(filename, &size);
	header = (DDS_HEADER*)file;
	data   = (uint8_t*)&header[1];
}

void DDS::create(uint32_t width, uint32_t height, uint32_t pitch, uint32_t n_mipmaps, uint32_t flags, uint8_t *data, int32_t dataSize)
{
	file = new uint8_t[0x80];

	memset(file, 0, 0x80);
	header = (DDS_HEADER*)file;

	header->magic     = 0x20534444;
	header->hdrSize   = 0x7C;
	header->flags     = flags;
	header->width     = width;
	header->height    = height;
	header->pitch     = 0;
	header->n_mipmaps = n_mipmaps;

	header->format.flags    = (DDPF_RGB | DDPF_ALPHAPIXELS);
	header->format.bitCount = 32;
	header->format.rBitmask = 255 << 16;
	header->format.gBitmask = 255 << 8;
	header->format.bBitmask = 255;
	header->format.aBitmask = 255 << 24;

	header->caps = header->n_mipmaps > 0 ? DDSCAPS_COMPLEX | DDSCAPS_MIPMAP | DDSCAPS_TEXTURE : DDSCAPS_TEXTURE;

	this->data = data;
	size = dataSize + 0x80;
}

uint32_t DDS::getWidth()
{
	return header->width;
}

uint32_t DDS::getHeight()
{
	return header->height;
}

uint32_t DDS::getNMipMaps()
{
	return header->n_mipmaps;
}

uint8_t* DDS::getData()
{
	return data;
}

int32_t DDS::getSize()
{
	return size;
}


void DDS::save(const char* filename)
{
	std::string output = "";
	writeDataToFile((uint8_t*)header, 0x80, filename, output);
	writeDataToFile(data, size - 0x80, filename, output, true);
}